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
    query.addQueryItem("cat", QString::number(filter.houseType)); // квартира
    query.addQueryItem("typ", QString::fromStdString(filter.transactionType)); // аренда
    query.addQueryItem("rgn",  QString::number(filter.rgn)); // регион Минск
    //query.addQueryItem("pue", "1");
    query.addQueryItem("sort", "lst.d"); // сортировать по дате
    query.addQueryItem("size", QString::number(filter.adsNumber)); // 30 объявлений
    query.addQueryItem("cur", QString::fromStdString(filter.currency)); // бел руб
    query.addQueryItem("prc", "r:" + QString::number(filter.minPrice * 100) + "," + QString::number(filter.maxPrice * 100)); // цена
    query.addQueryItem("st", "r:" + QString::number(filter.minFlatSize) + "," + QString::number(filter.maxFlatSize)); //квадраты квартиы общей площади
    query.addQueryItem("rms", "v.or:" + rooms.join(",")); // количество комнат

    if(filter.isPhoto){
        query.addQueryItem("oph", "1"); // с фоткой
    }
    if(filter.isOwner){
        query.addQueryItem("ot", "1"); // собственник
    }
    if(filter.isNearMetro){
        query.addQueryItem("mee", "v.or%3A3%2C6%2C5%2C36%2C7%2C10%2C11%2C14%2C13%2C15%2C16%2C17%2C20%2C21%2C22%2C23%2C33%2C29%2C26%2C34%2C27%2C28%2C25%2C24%2C19%2C35%2C12%2C18%2C8%2C4%2C32%2C2%2C9"); // метро
    }
    url.setQuery(query.query(QUrl::FullyEncoded));

    //url.setQuery(query);
    return url;
}
