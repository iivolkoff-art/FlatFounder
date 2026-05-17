import json
from aiogram import Bot, Dispatcher, types
from aiogram.filters import CommandStart
from DBHandler import DbHandler
import asyncio

class TcpTgBot:
    def __init__(self, config_path: str):
        with open(config_path, 'r') as f:
            config = json.load(f)["TGBotSettings"]
        self.token = config["TGToken"]
        self.db = DbHandler(config["BDName"])
        self.ip = config["IP"]
        self.port = config["Port"]
        self.bot = Bot(token=self.token)
        self.dp = Dispatcher()
        self.dp.message(CommandStart())(self.start_handler)


    async def start_handler(self, message: types.Message):
        self.db.add_user(message.from_user.id)
        await message.answer("Добро пожаловать Ivan Cool бота!")

    async def handle_tcp_client(self, reader, writer):
        print("Новое подключение")
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
                        print("Ошибка: Ожидался JSON-объект")
                        continue

                    json_array = json_data.get("FlatFounder")

                    if not isinstance(json_array, list):
                        print("Ошибка: Ключ 'FlatFounder' не найден или не является массивом")
                        continue

                    users = self.db.get_all_users()
                    if not users:
                        continue

                    for item in json_array:
                        link = item.get("link")
                        image = item.get("image")
                        price = item.get("price")
                        date = item.get("date")
                        currency = item.get("currency")
                        if not link:
                            continue

                        for user_id_tuple in users:
                            user_id = user_id_tuple[0] if isinstance(user_id_tuple, tuple) else user_id_tuple
                            try:
                                await self.bot.send_photo(chat_id=user_id, photo=image,
                                                          caption=f"Квартира: {link} \nЦена: {price} {currency} \nВремя публикации: {date}")
                            except Exception as e:
                                print(f"Ошибка отправки пользователю {user_id}: {e}")

                except json.JSONDecodeError as je:
                    print(f"Ошибка парсинга JSON: {je}")
                    print(f"Сырые данные: {json_str[:100]}...")

        except Exception as e:
            print(f"Ошибка в TCP-обработчике: {e}")
        finally:
            writer.close()
            await writer.wait_closed()
            print("Соединение закрыто")

    async def run(self):
        server = await asyncio.start_server(self.handle_tcp_client, self.ip, self.port)
        print(f"Ожидаются сообщения по {self.ip}:{self.port}")

        async with server:
            await self.dp.start_polling(self.bot)