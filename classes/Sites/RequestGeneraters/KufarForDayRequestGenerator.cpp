#include "KufarForDayRequestGenerator.h"
#include <QUrlQuery>

KufarForDayRequestGenerator::KufarForDayRequestGenerator() {}


QUrl KufarForDayRequestGenerator::generate(const FlatFilters& filter)
{
    QUrl url("https://api.kufar.by/booking/auth-bypass/v2/search/geo");
    QUrlQuery query;
    switch(filter.rgn){
    case 1: // Brest
        query.addQueryItem("gtsy",  "country-belarus~province-brestskaja_oblast~locality-brest");
        break;
    case 2: // Vitebsk
        query.addQueryItem("address",  "country-belarus~province-vitebskaja_oblast~locality-vitebsk");
        break;
    case 3: //Gomel
        query.addQueryItem("address",  "country-belarus~province-gomelskaja_oblast~locality-gomel");
        break;
    case 4: // Grodno
        query.addQueryItem("address",  "country-belarus~province-grodnenskaja_oblast~locality-grodno");
        break;
    case 6: // Mogilev
        query.addQueryItem("address",  "country-belarus~province-mogilyovskaja_oblast~locality-mogilyov");
        break;
    case 7: // Minsk
    default:
        query.addQueryItem("address",  "country-belarus~province-minsk~locality-minsk");
        break;
    }


    query.addQueryItem("prc", "r:" + QString::number(filter.minPrice * 100) + "," + QString::number(filter.maxPrice * 100));

    query.addQueryItem("bkat",  "v.or:1,1");
    query.addQueryItem("bkbt",  "v.or:1,5,10");
    query.addQueryItem("bkcl", QString::fromStdString(std::format("rn:{},{},1,0", calculateCurrentDays(), calculateCurrentDays() + 1)));

    addBasicParams(query, filter);


    if(filter.isNearMetro){
        query.addQueryItem("mee", "v.or%3A3%2C6%2C5%2C36%2C7%2C10%2C11%2C14%2C13%2C15%2C16%2C17%2C20%2C21%2C22%2C23%2C33%2C29%2C26%2C34%2C27%2C28%2C25%2C24%2C19%2C35%2C12%2C18%2C8%2C4%2C32%2C2%2C9"); // метро
    }
    url.setQuery(query.query(QUrl::FullyEncoded));

    //qDebug() << url;
    return url;
}


const int KufarForDayRequestGenerator::calculateCurrentDays(){
    const QDate constDay(2026, 7, 13);
    const int constIntDay = 20647;

    QDate currentDay = QDate::currentDate();

    return constIntDay + (constDay.daysTo(currentDay));
}
