#include "RealtRequestGenerator.h"
#include <QUrlQuery>

RealtRequestGenerator::RealtRequestGenerator() {}


//https://realt.by/rent-flat-for-long/object/*id*/

QUrl RealtRequestGenerator::generate(const FlatFilters& filter)
{
    //https://realt.by/_next/data/-o1BUGVgd9-BmYmShILGu/belarus/rent/flat-for-long.json?

    QUrl url;
    QUrlQuery query;

    url = "https://realt.by/rent/flat-for-long/?addressV2=%5B%7B\"townUuid\"%3A\"4cb07174-7b00-11eb-8943-0cc47adabd66\"%7D%5D";

    QStringList rooms;
    for (const auto& r : filter.roomsCount) {
        query.addQueryItem("rooms", QString::number(r));
    }

    query.addQueryItem("sortType", "createdAt");


    //query.addQueryItem("size", QString::number(filter.adsNumber));

    query.addQueryItem("priceFrom", QString::number(filter.minPrice));
    query.addQueryItem("priceTo", QString::number(filter.maxPrice));
    switch(filter.currency){
    case 1:
        query.addQueryItem("priceType", "933"); // BYN
        break;
    case 2:
        query.addQueryItem("priceType", "840"); //USD
        break;
    default:
        query.addQueryItem("priceType", "933");
        break;
    }

    query.addQueryItem("areaTotalFrom", QString::number(filter.minFlatSize)); //квадраты квартиы общей площади
    query.addQueryItem("areaTotalTo", QString::number(filter.maxFlatSize));


    if(filter.isPhoto){
        query.addQueryItem("hasImages", "true");
    }
    if(filter.isOwner){
        query.addQueryItem("isNotAgency", "true");
    }
    if(filter.isNearMetro){
        //query.addQueryItem("addressV2", "%5B%7B%22metroStationUuid%22%3A%22481c9f9e-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481ca613-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481caca1-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb2fe-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb3f0-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb72e-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb91d-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cbafb-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cbf4b-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cc223-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cc5e4-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%2282355720-a674-11eb-963d-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481ca4ae-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481ca9de-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481caba5-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cada1-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cae9a-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb081-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb170-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb4e6-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cbc5a-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cc130-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cc404-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cc4f8-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%2251ca0078-a674-11eb-963d-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481ca729-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481ca889-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481caf96-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb5df-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cb824-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cba0d-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cbd4f-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cbe47-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cc03e-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22481cc312-7b00-11eb-8943-0cc47adabd66%22%7D%2C%7B%22metroStationUuid%22%3A%22c27127ef-a674-11eb-963d-0cc47adabd66%22%7D%5D"); // метро
    }
    url.setQuery(query.query(QUrl::FullyEncoded));


    url.setQuery(query);
    //qDebug() << url;
    return url;
}
