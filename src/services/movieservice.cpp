#include "movieservice.h"

MovieService::MovieService(Api &api, System &system, QObject *parent) :
    QObject(parent),
    api(api),
    system(system),
    movie(new Movie(this)),
    request(api.getRequestInfo(Api::LoadMovie))
{
    connect(&api, &Api::movieDone, this, &MovieService::apiRequestDone);
    connect(&api, &Api::favoriteDone, this, &MovieService::favoriteDone);
    connect(&api, &Api::toggleWatchlistDone, this, &MovieService::toggleWatchlistDone);
    connect(&api, &Api::addRatingDone, this, &MovieService::addRatingDone);
    connect(&api, &Api::removeRatingDone, this, &MovieService::removeRatingDone);
}

void MovieService::toggleFavorite()
{
    api.toggleFavorite(*movie);
}

void MovieService::toggleWatchlist()
{
    api.toggleWatchlist(*movie);
}

void MovieService::addRating(int rating)
{
    movie->setRating(rating);
    api.addRating(*movie, rating);
}

void MovieService::removeRating()
{
    movie->setRating(0);
    api.removeRating(*movie);
}

void MovieService::fillWithListItemAndLoad(const MovieListItem &result)
{
    if (movie->getId() == result.getId())
        return;
    movie->setId(result.getId());
    movie->setBackdropPath(result.getBackdropPath());
    movie->setGenres(result.getGenres());
    movie->setHomepage("");
    movie->setImdbId("");
    movie->setOriginalLanguage("");
    movie->setOriginalTitle(result.getOriginalTitle());
    movie->setOverview(result.getOverview());
    movie->setPosterPath(result.getPosterPath());
    movie->setReleaseDate("");
    movie->setRevenue("");
    movie->setRuntimeHours(0);
    movie->setRuntimeMinutes(0);
    movie->setStatus("");
    movie->setTagline("");
    movie->setTitle(result.getTitle());
    movie->setVoteAvarage(result.getVoteAvarage());
    movie->setVoteCount(result.getVoteCount());
    movie->getBelongsToCollection()->setId(0);
    movie->getBelongsToCollection()->setName("");
    movie->getBelongsToCollection()->setPosterPath("");
    movie->getBelongsToCollection()->setBackdropPath("");
    movie->getProductionCompanies()->clear();
    movie->getProductionCountries()->clear();
    movie->getSpokenLanguages()->clear();
    movie->setFavorite(false);
    movie->setRating(0);
    movie->setWatchlist(false);
    api.loadMovie(movie->getId());
}

Movie *MovieService::getMovie() const
{
    return movie;
}

RequestInfo *MovieService::getRequest() const
{
    return request;
}

void MovieService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "movie is loaded from API";
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    movie->setBudget(system.getLocale().toCurrencyString(obj["budget"].toVariant().toLongLong(), "$"));
    movie->setHomepage(obj["homepage"].toString());
    movie->setImdbId(obj["imdb_id"].toString());
    movie->setOriginalLanguage(obj["original_language"].toString());
    movie->setReleaseDate(obj["release_date"].toString());
    movie->setRevenue(system.getLocale().toCurrencyString(obj["revenue"].toVariant().toLongLong(), "$"));
    int runtime = obj["runtime"].toInt();
    movie->setRuntimeHours((int) (runtime / 60));
    movie->setRuntimeMinutes(runtime - movie->getRuntimeHours() * 60);
    movie->setStatus(obj["status"].toString());
    movie->setTagline(obj["tagline"].toString());

    if (obj["belongs_to_collection"].isObject()) {
        QJsonObject belongsToCollection = obj["belongs_to_collection"].toObject();
        movie->getBelongsToCollection()->setId(belongsToCollection["id"].toInt());
        movie->getBelongsToCollection()->setName(belongsToCollection["name"].toString());
        movie->getBelongsToCollection()->setPosterPath(belongsToCollection["poster_path"].toString());
        movie->getBelongsToCollection()->setBackdropPath(belongsToCollection["backdrop_path"].toString());
    }

    QJsonArray items;
    QJsonArray::const_iterator it;

    if (obj["production_companies"].isArray()) {
        items = obj["production_companies"].toArray();
        QJsonArray::const_iterator it;
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            QJsonObject company = it->toObject();
            movie->getProductionCompanies()->add(Company(
                    company["id"].toInt(),
                    company["logo_path"].toString(),
                    company["name"].toString(),
                    company["origin_country"].toString()));
        }
    }

    if (obj["production_countries"].isArray()) {
        items = obj["production_countries"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            QJsonObject item = it->toObject();
            movie->getProductionCountries()->add(CountryListItem(
                    item["iso_3166_1"].toString(),
                    item["name"].toString()));
        }
    }

    if (obj["spoken_languages"].isArray()) {
        items = obj["spoken_languages"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            QJsonObject item = it->toObject();
            QString name = item["name"].toString();
            QString englishName = item["english_name"].toString();
            if (englishName != name)
                name.append(" (" + englishName + ")");
            movie->getSpokenLanguages()->add(LanguageListItem(item["iso_639_1"].toString(), name));
        }
    }

    if (obj.contains("account_states")) {
        QJsonObject accountStates = obj["account_states"].toObject();
        movie->setFavorite(accountStates["favorite"].toBool());
        if (accountStates["rated"].isObject()) {
            movie->setRating((int)accountStates["rated"].toObject()["value"].toDouble());
        }
        movie->setWatchlist(accountStates["watchlist"].toBool());
    }
}

void MovieService::favoriteDone(const QByteArray &data)
{
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    if (obj["success"].toBool()) {
        movie->setFavorite(!movie->getFavorite());
    }
}

void MovieService::toggleWatchlistDone(const QByteArray &data)
{
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    if (obj["success"].toBool()) {
        movie->setWatchlist(!movie->getWatchlist());
    }
}

void MovieService::addRatingDone(const QByteArray &data)
{
    qDebug() << data;
}

void MovieService::removeRatingDone(const QByteArray &data)
{
    qDebug() << data;
}
