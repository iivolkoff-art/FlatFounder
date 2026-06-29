#include "OnlinerRequestGenerator.h"
#include <QUrlQuery>

OnlinerRequestGenerator::OnlinerRequestGenerator() {}

QUrl OnlinerRequestGenerator::generate(const FlatFilters& filter)
{
    QUrl url;

    QUrlQuery query;
    switch(filter.transactionType){
    case 1:
        url = "https://r.onliner.by/sdapi/ak.api/search/apartments";
        for (int r : filter.roomsCount) {
            query.addQueryItem("rent_type[]", QString::number(r) + "_room" + (r > 1 ? "s" : ""));
        }
        break;
    case 2:
        url = "https://r.onliner.by/sdapi/pk.api/search/apartments";
        for (int r : filter.roomsCount) {
            query.addQueryItem("number_of_rooms[]", QString::number(r));
        }
        break;
    default:
        url = "https://r.onliner.by/sdapi/ak.api/search/apartments";
        for (int r : filter.roomsCount) {
            query.addQueryItem("rent_type", QString::number(r) + "_room" + (r > 1 ? "s" : ""));
        }
        break;
    }



    query.addQueryItem("price[min]", QString::number(filter.minPrice));
    query.addQueryItem("price[max]", QString::number(filter.maxPrice));

    switch(filter.currency){
    case 1:
        query.addQueryItem("currency", "BYN");
        break;
    case 2:
        query.addQueryItem("currency", "USD");
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

    switch(filter.rgn){
    case 1: //Brest
        query.addQueryItem("bounds[lb][lat]", "51.952517832627976");
        query.addQueryItem("bounds[lb][long]", "23.560867309570312");
        query.addQueryItem("bounds[rt][lat]", "52.223593353839426");
        query.addQueryItem("bounds[rt][long]", "23.858528137207035");
        break;
    case 2://Vitebcsk
        query.addQueryItem("bounds[lb][lat]", "55.09585520061626");
        query.addQueryItem("bounds[lb][long]", "29.982376098632812");
        query.addQueryItem("bounds[rt][lat]", "55.34749863966165");
        query.addQueryItem("bounds[rt][long]", "30.41152954101563");
        break;
    case 3://Gomel
        query.addQueryItem("bounds[lb][lat]", "52.313516199748086");
        query.addQueryItem("bounds[lb][long]", "30.73459625244141");
        query.addQueryItem("bounds[rt][lat]", "52.58240003673654");
        query.addQueryItem("bounds[rt][long]", "31.163749694824222");
        break;
    case 4://Grodno
        query.addQueryItem("bounds[lb][lat]", "53.54867146686364");
        query.addQueryItem("bounds[lb][long]", "23.63193511962891");
        query.addQueryItem("bounds[rt][lat]", "53.80997698903499");
        query.addQueryItem("bounds[rt][long]", "24.061088562011722");
        break;
    case 6://Mogilev
        query.addQueryItem("bounds[lb][lat]", "53.753176917802385");
        query.addQueryItem("bounds[lb][long]", "30.134468078613285");
        query.addQueryItem("bounds[rt][lat]", "54.013215989893766");
        query.addQueryItem("bounds[rt][long]", "30.563621520996097");
        break;
    case 7: // Minsk
        query.addQueryItem("bounds[lb][lat]", "53.71580928395326");
        query.addQueryItem("bounds[lb][long]", "27.33055114746094");
        query.addQueryItem("bounds[rt][lat]", "54.08758999370116");
        query.addQueryItem("bounds[rt][long]", "27.79403686523438");
        break;
    }


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

