import json
import asyncio
from aiogram import Bot, Dispatcher, types
from aiogram.filters import CommandStart
from aiogram.exceptions import TelegramRetryAfter
from DBHandler import DbHandler
from TgChannelsOperator import TgChannelsOperator


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

    async def start_handler(self, message: types.Message):
        self.__db.add_user(message.from_user.id)
        await message.answer("Welcome to Ivan Cool bot!")

    async def queue_worker(self):
        while True:
            item, user_id = await self.__queue.get()
            link = item.get("link")
            image = item.get("image")
            price = item.get("price")
            date = item.get("date")
            currency = item.get("currency")

            try:
                await self.__bot.send_photo(
                    chat_id=user_id,
                    photo=image,
                    caption=f'Источник<a href="{link}"🔎 \nЦена💵: {price} {currency} \nВремя публикации🕒: {date}'
                )
                if str(user_id).startswith("-100"):
                    await asyncio.sleep(3.5)
                else:
                    await asyncio.sleep(0.2)
            except TelegramRetryAfter as e:
                print(f"Rate limit exceeded! Worker sleeping for {e.retry_after} seconds...")
                await asyncio.sleep(e.retry_after)
                try:
                    await self.__bot.send_photo(
                        chat_id=user_id, photo=image,
                        caption=f'Источник<a href="{link}"🔎 \nЦена💵: {price} {currency} \nВремя публикации🕒: {date}'
                    )
                except Exception as re_err:
                    print(f"Error: Retry sending failed: {re_err}")
            except Exception as e:
                print(f"Error: Error sending to the user {user_id}: {e}")
            finally:
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
        server = await asyncio.start_server(self.handle_tcp_client, self.__ip, self.__port)
        print(f"Current address: {self.__ip}:{self.__port}")

        asyncio.create_task(self.queue_worker())

        async with server:
            await self.__dp.start_polling(self.__bot)

    def _read_json_setting_file(self):
        config = {}
        with open(self.__config_path, 'r') as f:
            config = json.load(f)["TGBotSettings"]
        return config
