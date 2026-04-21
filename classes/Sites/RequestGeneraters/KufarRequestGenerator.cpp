#include "KufarRequestGenerator.h"
#include <QUrlQuery>

KufarRequestGenerator::KufarRequestGenerator() {}

QUrl KufarRequestGenerator::generate(const FlatFilters& filter_)
{
    QUrl url("https://api.kufar.by/search-api/v2/search/rendered-paginated");
    QUrlQuery query;
    QStringList rooms = {"1", "2", "3", "4"};


    query.addQueryItem("cat", "1010"); // квартира
    query.addQueryItem("typ", "let"); // аренда
    query.addQueryItem("rgn", "7"); // регион Минск
    query.addQueryItem("ot", "1"); // собственник
    //query.addQueryItem("pue", "1");
    query.addQueryItem("sort", "lst.d"); // сортировать по дате
    query.addQueryItem("size", "30"); // 30 объявлений
    query.addQueryItem("cur", "BYR"); // бел руб
    query.addQueryItem("prc", "r:80000,130000"); // от 800р до 1300
    query.addQueryItem("st", "r:35,1000"); // 35 - 1000 квадратолв общей площади
    query.addQueryItem("rms", "v.or:" + rooms.join(",")); // количество комнат
    query.addQueryItem("oph", "1"); // с фоткой
    query.addQueryItem("mee", "v.or%3A3%2C6%2C5%2C36%2C7%2C10%2C11%2C14%2C13%2C15%2C16%2C17%2C20%2C21%2C22%2C23%2C33%2C29%2C26%2C34%2C27%2C28%2C25%2C24%2C19%2C35%2C12%2C18%2C8%2C4%2C32%2C2%2C9"); // с фоткой
    url.setQuery(query.query(QUrl::FullyEncoded));


    //url.setQuery(query);
    return url;
}
