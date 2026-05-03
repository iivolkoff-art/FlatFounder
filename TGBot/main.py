from TcpTgBot import TcpTgBot
import asyncio

if __name__ == "__main__":
    bot_app = TcpTgBot("Settings.json")
    asyncio.run(bot_app.run())