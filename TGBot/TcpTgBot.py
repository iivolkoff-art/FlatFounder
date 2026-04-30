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
                data = await reader.read(1024)
                if not data:
                    break

                messages = data.decode().strip().split('\n')

                users = self.db.get_all_users()
                for msg in messages:
                    if not msg: continue

                    for user_id_tuple in users:
                        user_id = user_id_tuple[0] if isinstance(user_id_tuple, tuple) else user_id_tuple
                        try:
                            await self.bot.send_message(user_id, f"Получено: {msg}")
                        except Exception as e:
                            print(f"Ошибка отправки {user_id}: {e}")
        finally:
            writer.close()
            await writer.wait_closed()
            print("Соединение закрыто")

    async def run(self):
        server = await asyncio.start_server(self.handle_tcp_client, self.ip, self.port)
        print(f"Ожидаются сообщения по {self.ip}:{self.port}")

        async with server:
            await self.dp.start_polling(self.bot)