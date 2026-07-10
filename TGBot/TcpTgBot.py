import json
from aiogram import Bot, Dispatcher, types
from aiogram.filters import CommandStart
from DBHandler import DbHandler
from TgChannelsOperator import TgChannelsOperator
import asyncio

class TcpTgBot:
    def __init__(self, config_path: str):
        self.__config_path = config_path
        self.__config = self._read_json_setting_file()
        self.__token = self.__config["TGToken"]
        self.__db = DbHandler(self.__config["DataBase/BDName"])
        self.__channels = TgChannelsOperator("TGChannels/Channels.json")
        self.__ip = self.__config["IP"]
        self.__port = self.__config["Port"]
        self.__bot = Bot(token=self.__token)
        self.__dp = Dispatcher()
        self.__dp.message(CommandStart())(self.start_handler)



    async def start_handler(self, message: types.Message):
        self.__db.add_user(message.from_user.id)
        await message.answer("Добро пожаловать Ivan Cool бота!")

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

                    json_name:str = next(iter(json_data))
                    json_array = json_data.get(json_name)

                    if not isinstance(json_array, list):
                        print("Error: Key 'FlatFounder' is not found")
                        continue

                    users = self.__db.get_all_users()
                    users += self.__channels.get_channels()[json_name]
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
                                await self.__bot.send_photo(chat_id=user_id, photo=image,
                                                          caption=f"Квартира: {link} \nЦена: {price} {currency} \nВремя публикации: {date}")
                            except Exception as e:
                                print(f"Error: Error sending to the user {user_id}: {e}")

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

        async with server:
            await self.__dp.start_polling(self.__bot)


    def _read_json_setting_file(self):
        config = {}
        with open(self.__config_path, 'r') as f:
            config = json.load(f)["TGBotSettings"]
        return config