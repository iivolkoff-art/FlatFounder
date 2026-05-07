#include "OnlinerRequestGenerator.h"
#include <QUrlQuery>

OnlinerRequestGenerator::OnlinerRequestGenerator() {}

QUrl OnlinerRequestGenerator::generate(const FlatFilters& filter)
{
    QUrl url("https://r.onliner.by/sdapi/ak.api/search/apartments");
    QUrlQuery query;


    QStringList rooms;
    for (const auto& r : filter.roomsCount) {
        rooms << QString::number(r);
    }
    for (int r : filter.roomsCount) {
        query.addQueryItem("rent_type[]", QString::number(r) + "_room" + (r > 1 ? "s" : ""));
    }

    query.addQueryItem("price[min]", QString::number(filter.minPrice));
    query.addQueryItem("price[max]", QString::number(filter.maxPrice));

    switch(filter.currency){
    case 1:
        query.addQueryItem("currency", "BYN");
        break;
    default:
        query.addQueryItem("currency", "BYN");
        break;
    }


    query.addQueryItem("only_owner", filter.isOwner ? "true" : "false");

    if(filter.isNearMetro){
        query.addQueryItem("metro[]", "red_line");
        query.addQueryItem("metro[]", "blue_line");
        query.addQueryItem("metro[]", "green_line");
    }

    query.addQueryItem("bounds[lb][lat]", "53.71580928395326");
    query.addQueryItem("bounds[lb][long]", "27.33055114746094");
    query.addQueryItem("bounds[rt][lat]", "54.08758999370116");
    query.addQueryItem("bounds[rt][long]", "27.79403686523438");

    if(filter.isPhoto){
        query.addQueryItem("page", "1");
    }

    query.addQueryItem("order", "created_at:desc");


    query.addQueryItem("v", "0.8146960835907123");

    query.addQueryItem("limit", QString::number(filter.adsNumber));


    url.setQuery(query.query(QUrl::FullyEncoded));

    url.setQuery(query);
    return url;
}

