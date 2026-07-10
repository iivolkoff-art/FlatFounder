import json

class TgChannelsOperator:
    def __init__(self, tg_channels_file_path: str):
        self.__channels:dict[str, str] = {}
        self.__tg_channels_file_path = tg_channels_file_path
        self._read_file()

    def get_channels(self):
        return self.__channels

    def _read_file(self):
        json_file_data = ""
        with open(self.__tg_channels_file_path, 'r') as f:
            json_file_data = json.load(f)
        for name, key in json_file_data.items():
            self.__channels[name] = key