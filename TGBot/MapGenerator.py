import sys
import re
from typing import Optional, Tuple
from geopy.geocoders import Nominatim
from geopy.exc import GeocoderTimedOut, GeocoderUnavailable
from staticmap import StaticMap, CircleMarker


class MapGenerator:

    def __init__(self, user_agent: str = "my_map_bot", timeout: int = 10):
        self.user_agent = user_agent
        self.timeout = timeout
        self.geolocator = Nominatim(user_agent=user_agent)
        self.last_coordinates = None
        self.last_address = None

    def _normalize_address(self, address: str) -> str:
        address = re.sub(r'\s+', ' ', address).strip()

        address = re.sub(r'([\w\s-]+)\b(ул|улица)\b', r'улица \1', address, flags=re.IGNORECASE)
        address = re.sub(r'([\w\s-]+)\b(пр|проспект)\b', r'проспект \1', address, flags=re.IGNORECASE)
        address = re.sub(r'([\w\s-]+)\b(пер|переулок)\b', r'переулок \1', address, flags=re.IGNORECASE)

        address = re.sub(r'(\d+)\s*[кК](?:орп)?\.?\s*(\d+)', r'\1/\2', address)
        address = re.sub(r'\s+', ' ', address).strip()

        if 'беларусь' not in address.lower() and 'belarus' not in address.lower():
            address += ', Беларусь'

        return address

    def _get_coordinates(self, address: str, verbose: bool = False) -> Optional[Tuple[float, float]]:
        self.last_address = address
        normalized = self._normalize_address(address)

        variants = [
            address,
            normalized,
            normalized.replace('/', ' корпус '),
            normalized.replace('/', 'к'),
            address + ', Беларусь'
        ]
        variants = list(dict.fromkeys(variants))

        for attempt, variant in enumerate(variants, 1):
            if verbose:
                print(f"🔍 Попытка {attempt}: {variant}")

            try:
                location = self.geolocator.geocode(
                    variant,
                    timeout=self.timeout,
                    country_codes="by"
                )
                if location:
                    self.last_coordinates = (location.latitude, location.longitude)
                    if verbose:
                        print(f"✅ Найдено! Координаты: {self.last_coordinates}")
                    return self.last_coordinates
            except (GeocoderTimedOut, GeocoderUnavailable) as e:
                if verbose:
                    print(f"⚠️ Ошибка сети: {e}")
                continue

        if verbose:
            print("❌ Адрес окончательно не найден.")
        return None

    def get_coordinates_silent(self, address: str) -> Optional[Tuple[float, float]]:
        return self._get_coordinates(address, verbose=False)

    def generate_map(
            self,
            lat: float,
            lon: float,
            filename: str = "map.png",
            zoom: int = 11,
            width: int = 600,
            height: int = 400,
            marker_color: str = 'red',
            marker_size: int = 12,
            url_template: str = 'http://tile.openstreetmap.org/{z}/{x}/{y}.png'
    ) -> Optional[str]:
        try:
            m = StaticMap(width, height, url_template=url_template)
            marker = CircleMarker((lon, lat), marker_color, marker_size)
            m.add_marker(marker)
            image = m.render(zoom=zoom)
            image.save(filename)
            return filename
        except Exception as e:
            print(f"❌ Ошибка при генерации карты: {e}")
            return None

    def generate_map_from_address(
            self,
            address: str,
            filename: str = "map.png",
            zoom: int = 11,
            width: int = 600,
            height: int = 400,
            verbose: bool = False
    ) -> Optional[str]:
        coords = self._get_coordinates(address, verbose=verbose)
        if coords is None:
            return None

        lat, lon = coords
        return self.generate_map(lat, lon, filename, zoom, width, height)

    def get_last_coordinates(self) -> Optional[Tuple[float, float]]:
        return self.last_coordinates

    def get_last_address(self) -> Optional[str]:
        return self.last_address