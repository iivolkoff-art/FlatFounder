#include "KufarRequestGenerator.h"
#include <QUrlQuery>

KufarRequestGenerator::KufarRequestGenerator() {}

QUrl KufarRequestGenerator::generate(const FlatFilters& filter)
{
    QUrl url("https://api.kufar.by/search-api/v2/search/rendered-paginated");
    QUrlQuery query;


    QStringList rooms;
    for (const auto& r : filter.roomsCount) {
        rooms << QString::number(r);
    }


    query.addQueryItem("sort", "lst.d");
    query.addQueryItem("size", QString::number(filter.adsNumber));
    query.addQueryItem("prc", "r:" + QString::number(filter.minPrice * 100) + "," + QString::number(filter.maxPrice * 100)); // цена
    query.addQueryItem("st", "r:" + QString::number(filter.minFlatSize) + "," + QString::number(filter.maxFlatSize)); //квадраты квартиы общей площади
    query.addQueryItem("rms", "v.or:" + rooms.join(","));

    switch(filter.houseType){
    case 1:
        query.addQueryItem("cat", "1010");
        break;
    default:
        query.addQueryItem("cat", "1010");
        break;
    }

    switch(filter.transactionType){
    case 1:
        query.addQueryItem("typ", "let");
        break;
    default:
        query.addQueryItem("typ", "let");
        break;
    }

    switch(filter.currency){
    case 1:
        query.addQueryItem("cur", "BYN");
        break;
    case 2:
        query.addQueryItem("cur", "USD");
    default:
        query.addQueryItem("cur", "BYN");
        break;
    }


    switch(filter.rgn){
    case 1: // Brest
        query.addQueryItem("rgn",  "1");
        query.addQueryItem("ar",  "1");
        break;
    case 2: // Vitebsk
        query.addQueryItem("rgn",  "6");
        query.addQueryItem("ar",  "18");
        break;
    case 3: //Gomel
        query.addQueryItem("rgn",  "2");
        query.addQueryItem("ar",  "5");
        break;
    case 4: // Grodno
        query.addQueryItem("rgn",  "3");
        query.addQueryItem("ar",  "9");
        break;
    case 6: // Mogilev
        query.addQueryItem("rgn",  "4");
        query.addQueryItem("ar",  "13");
        break;
    case 7: // Minsk
        query.addQueryItem("rgn",  "7");
        break;
    }

    if(filter.isPhoto){
        query.addQueryItem("oph", "1");
    }
    if(filter.isOwner){
        query.addQueryItem("cmp", "0");
    }
    if(filter.isNearMetro){
        query.addQueryItem("mee", "v.or%3A3%2C6%2C5%2C36%2C7%2C10%2C11%2C14%2C13%2C15%2C16%2C17%2C20%2C21%2C22%2C23%2C33%2C29%2C26%2C34%2C27%2C28%2C25%2C24%2C19%2C35%2C12%2C18%2C8%2C4%2C32%2C2%2C9"); // метро
    }
    url.setQuery(query.query(QUrl::FullyEncoded));


    url.setQuery(query);
    return url;
}
