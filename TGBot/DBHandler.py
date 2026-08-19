import sqlite3

class DbHandler:
    def __init__(self, db_name: str):
        self.__conn = sqlite3.connect(db_name)
        self.__cursor = self.__conn.cursor()
        self.__cursor.execute('CREATE TABLE IF NOT EXISTS users (user_id INTEGER PRIMARY KEY)')
        self.__conn.commit()

    def add_user(self, user_id: int):
        self.__cursor.execute('INSERT OR IGNORE INTO users (user_id) VALUES (?)', (user_id,))
        self.__conn.commit()

    def get_all_users(self) -> list[int]:
        self.__cursor.execute('SELECT user_id FROM users')
        return [row[0] for row in self.__cursor.fetchall()]