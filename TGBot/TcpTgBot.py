import json
import asyncio
import os
import shutil
import re
import requests
from datetime import datetime
from io import BytesIO
from aiogram import Bot, Dispatcher, types
from aiogram.filters import CommandStart
from aiogram.exceptions import TelegramRetryAfter
from aiogram.types import InputMediaPhoto
from DBHandler import DbHandler
from TgChannelsOperator import TgChannelsOperator
from MapGenerator import MapGenerator
from geopy.exc import GeocoderRateLimited


class TcpTgBot:
    def __init__(self, config_path: str):
        self.__config_path = config_path
        self.__config = self._read_json_setting_file()
        self.__token = self.__config["TGToken"]
        db_filename = self.__config["BDName"]
        self.__db = DbHandler(f"./DataBase/{db_filename}")
        self.__channels = TgChannelsOperator("./TGChannels/Channels.json")
        self.__ip = self.__config["IP"]
        self.__port = self.__config["Port"]
        self.__bot = Bot(token=self.__token)
        self.__dp = Dispatcher()
        self.__dp.message(CommandStart())(self.start_handler)
        self.__queue = asyncio.Queue()
        self.__map_generator = MapGenerator()
        self.__name_images_folder = "images"

    async def start_handler(self, message: types.Message):
        self.__db.add_user(message.from_user.id)
        await message.answer("Welcome to Ivan Cool bot!")

    async def weekly_cleaner(self):
        while True:
            now = datetime.now()
            if now.weekday() == 0 and now.hour == 4 and now.minute == 0 and now.second == 0:
                print("🧹 Запущена еженедельная полная очистка папки картинок...")
                if os.path.exists(self.__name_images_folder):
                    try:
                        shutil.rmtree(self.__name_images_folder)
                        os.makedirs(self.__name_images_folder, exist_ok=True)
                        print("✅ Папка images успешно очищена.")
                    except Exception as e:
                        print(f"❌ Ошибка при еженедельной очистке: {e}")
                await asyncio.sleep(60)
            await asyncio.sleep(1)

    async def queue_worker(self):
        while True:
            item, user_id = await self.__queue.get()
            link = item.get("link")
            image_url = item.get("image")
            price = item.get("price")
            date = item.get("date")
            address = item.get("address")
            currency = item.get("currency")
            rooms_count = item.get("roomsCount")

            map_filename = None
            if address:
                safe_address = re.sub(r'[^\w\s,.-]', '', address)
                safe_address = re.sub(r'[,\s]+', '_', safe_address)
                safe_address = re.sub(r'_+', '_', safe_address).strip('_')

                os.makedirs(self.__name_images_folder, exist_ok=True)
                map_filename = os.path.join(self.__name_images_folder, f"{safe_address}.png")

                try:
                    self.__map_generator.generate_map_from_address(address, map_filename)
                    await asyncio.sleep(1.0)
                except GeocoderRateLimited:
                    print("⚠️ Nominatim Rate Limit (429). Ожидание 5 секунд...")
                    await asyncio.sleep(5.0)
                    try:
                        self.__map_generator.generate_map_from_address(address, map_filename)
                        await asyncio.sleep(1.0)
                    except Exception:
                        map_filename = None
                except Exception as e:
                    print(f"❌ Ошибка геокодера: {e}")
                    map_filename = None

            caption = (
                f'<a href="{link}">Источник</a>\n'
                f'Цена: {price} {currency}\n'
                f'Время: {date}\n'
                f'Адрес: {address}\n'
                f'Комнат: {rooms_count}'
            )

            try:
                if map_filename and os.path.exists(map_filename):
                    response = requests.get(image_url)
                    original_photo = BytesIO(response.content)

                    media = [
                        InputMediaPhoto(
                            media=types.BufferedInputFile(original_photo.getvalue(), filename="original.png"),
                            caption=caption,
                            parse_mode="HTML"
                        ),
                        InputMediaPhoto(
                            media=types.FSInputFile(map_filename)
                        )
                    ]

                    await self.__bot.send_media_group(
                        chat_id=user_id,
                        media=media
                    )
                else:
                    await self.__bot.send_photo(
                        chat_id=user_id,
                        photo=image_url,
                        caption=caption,
                        parse_mode="HTML"
                    )

                if str(user_id).startswith("-100"):
                    await asyncio.sleep(3.5)
                else:
                    await asyncio.sleep(0.2)

            except TelegramRetryAfter as e:
                print(f"Rate limit exceeded! Worker sleeping for {e.retry_after} seconds...")
                await asyncio.sleep(e.retry_after)
                try:
                    if map_filename and os.path.exists(map_filename):
                        from PIL import Image

                        response = requests.get(image_url)
                        img1 = Image.open(BytesIO(response.content))
                        img2 = Image.open(map_filename)

                        width = max(img1.width, img2.width)

                        if img1.width != width:
                            h1 = int(img1.height * (width / img1.width))
                            img1 = img1.resize((width, h1), Image.Resampling.LANCZOS)
                        if img2.width != width:
                            h2 = int(img2.height * (width / img2.width))
                            img2 = img2.resize((width, h2), Image.Resampling.LANCZOS)

                        total_height = img1.height + img2.height
                        combined_img = Image.new("RGB", (width, total_height))
                        combined_img.paste(img1, (0, 0))
                        combined_img.paste(img2, (0, img1.height))

                        output_buffer = BytesIO()
                        combined_img.save(output_buffer, format="JPEG", quality=85)
                        output_buffer.seek(0)

                        await self.__bot.send_photo(
                            chat_id=user_id,
                            photo=types.BufferedInputFile(output_buffer.getvalue(), filename="combined.jpg"),
                            caption=caption,
                            parse_mode="HTML"
                        )
                    else:
                        await self.__bot.send_photo(
                            chat_id=user_id,
                            photo=image_url,
                            caption=caption,
                            parse_mode="HTML"
                        )

                    if str(user_id).startswith("-100"):
                        await asyncio.sleep(3.5)
                    else:
                        await asyncio.sleep(0.2)
                except Exception as re_err:
                    print(f"Error: Retry sending failed: {re_err}")

            except Exception as e:
                print(f"Error: Error sending to the user {user_id}: {e}")
            finally:
                if map_filename and os.path.exists(map_filename):
                    try:
                        os.remove(map_filename)
                    except Exception:
                        pass
                self.__queue.task_done()

    async def handle_tcp_client(self, reader, writer):
        print("NEW CONNECTION!")
        try:
            while True:
                data = await reader.readline()
                if not data:
                    break

                json_str = data.decode('utf-8').strip()
                if not json_str:
                    continue

                try:
                    json_data = json.loads(json_str)

                    if not isinstance(json_data, dict):
                        print("Error: A JSON object was expected")
                        continue

                    json_name: str = next(iter(json_data))
                    json_array = json_data.get(json_name)

                    if not isinstance(json_array, list):
                        print("Error: Targeted key array is not found")
                        continue

                    users = self.__db.get_all_users()
                    channel_id = self.__channels.get_channels().get(json_name)

                    if channel_id:
                        users.append(channel_id)

                    if not users:
                        continue

                    for item in json_array:
                        if not item.get("link"):
                            continue
                        for user_id in users:
                            await self.__queue.put((item, user_id))

                except json.JSONDecodeError as je:
                    print(f"JSON parsing error: {je}")
                    print(f"Raw Data: {json_str[:100]}...")

        except Exception as e:
            print(f"Error in TCP handler: {e}")
        finally:
            writer.close()
            await writer.wait_closed()
            print("Connection is closed")

    async def run(self):
        if os.path.exists(self.__name_images_folder):
            shutil.rmtree(self.__name_images_folder)
        os.makedirs(self.__name_images_folder, exist_ok=True)

        server = await asyncio.start_server(self.handle_tcp_client, self.__ip, self.__port)
        print(f"Current address: {self.__ip}:{self.__port}")

        asyncio.create_task(self.queue_worker())
        asyncio.create_task(self.weekly_cleaner())

        async with server:
            await self.__bot.delete_webhook(drop_pending_updates=True)
            await self.__dp.start_polling(self.__bot)

    def _read_json_setting_file(self):
        config = {}
        with open(self.__config_path, 'r') as f:
            config = json.load(f)["TGBotSettings"]
        return config
