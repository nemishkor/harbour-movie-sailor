#include "movieservice.h"

MovieService::MovieService(Api &api, System &system, QObject *parent) :
    QObject(parent),
    api(api),
    system(system),
    model(new Movie(this)),
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
    api.toggleFavorite(*model);
}

void MovieService::toggleWatchlist()
{
    api.toggleWatchlist(*model);
}

void MovieService::addRating(int rating)
{
    model->setRating(rating);
    api.addRating(*model, rating);
}

void MovieService::removeRating()
{
    model->setRating(0);
    api.removeRating(*model);
}

void MovieService::load(int id)
{
    model->setId(id);
    api.loadMovie(model->getId());
}

void MovieService::fillWithListItemAndLoad(const MediaListItem &result)
{
    qDebug() << "MovieService: fill" << result.getId();
    if (model->getId() == result.getId())
        return;

    model->setId(result.getId());
    model->setBackdropPath(result.getBackdropPath());
    model->setBudget("");
    model->setGenres(result.getGenres());
    model->setHomepage("");
    model->setImdbId("");
    model->setOriginalLanguage("");
    model->setOriginalTitle(result.getOriginalTitle());
    model->setOverview(result.getOverview());
    model->setPosterPath(result.getPosterPath());
    model->setReleaseDate("");
    model->setRevenue("");
    model->setRuntimeHours(0);
    model->setRuntimeMinutes(0);
    model->setStatus("");
    model->setTagline("");
    model->setTitle(result.getTitle());
    model->setVoteAvarage(result.getVoteAvarage());
    model->setVoteCount(result.getVoteCount());
    model->getBelongsToCollection()->setId(0);
    model->getBelongsToCollection()->setName("");
    model->getBelongsToCollection()->setPosterPath("");
    model->getBelongsToCollection()->setBackdropPath("");
    model->getProductionCompanies()->clear();
    model->getProductionCountries()->clear();
    model->getSpokenLanguages()->clear();
    model->setFavorite(false);
    model->setRating(0);
    model->setWatchlist(false);
    model->getCredits()->getCast()->clear();
    model->getCredits()->getCrew()->clear();
    qDebug() << "MovieService: load" << result.getId();
    api.loadMovie(model->getId());
}

Movie *MovieService::getModel() const
{
    return model;
}

RequestInfo *MovieService::getRequest() const
{
    return request;
}

void MovieService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "MovieService: movie is loaded";

    QJsonObject obj = QJsonDocument::fromJson(data).object();
    qlonglong money = obj["budget"].toVariant().toLongLong();
    model->setBudget(money == 0 ? "?" : system.getLocale().toCurrencyString(money, "$"));
    model->setHomepage(obj["homepage"].toString());
    model->setImdbId(obj["imdb_id"].toString());
    model->setOriginalLanguage(obj["original_language"].toString());
    model->setReleaseDate(obj["release_date"].toString());
    money = obj["revenue"].toVariant().toLongLong();
    model->setRevenue(money == 0 ? "?" : system.getLocale().toCurrencyString(money, "$"));
    int runtime = obj["runtime"].toInt();
    model->setRuntimeHours((int) (runtime / 60));
    model->setRuntimeMinutes(runtime - model->getRuntimeHours() * 60);
    model->setStatus(obj["status"].toString());
    model->setTagline(obj["tagline"].toString());

    if (obj["belongs_to_collection"].isObject()) {
        QJsonObject belongsToCollection = obj["belongs_to_collection"].toObject();
        model->getBelongsToCollection()->setId(belongsToCollection["id"].toInt());
        model->getBelongsToCollection()->setName(belongsToCollection["name"].toString());
        model->getBelongsToCollection()->setPosterPath(belongsToCollection["poster_path"].toString());
        model->getBelongsToCollection()->setBackdropPath(belongsToCollection["backdrop_path"].toString());
    }

    QJsonArray items;
    QJsonArray::const_iterator it;
    QJsonObject item;

    qDebug() << "MovieService: set production companies";
    if (obj["production_companies"].isArray()) {
        items = obj["production_companies"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            item = it->toObject();
            model->getProductionCompanies()->add(Company(
                    item["id"].toInt(),
                    item["logo_path"].toString(),
                    item["name"].toString(),
                    item["origin_country"].toString()));
        }
    }

    qDebug() << "MovieService: set production countries";
    if (obj["production_countries"].isArray()) {
        items = obj["production_countries"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            item = it->toObject();
            model->getProductionCountries()->add(CountryListItem(
                    item["iso_3166_1"].toString(),
                    item["name"].toString()));
        }
    }

    qDebug() << "MovieService: set spoken languages";
    if (obj["spoken_languages"].isArray()) {
        items = obj["spoken_languages"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            item = it->toObject();
            QString name = item["name"].toString();
            QString englishName = item["english_name"].toString();
            if (englishName != name)
                name.append(" (" + englishName + ")");
            model->getSpokenLanguages()->add(LanguageListItem(item["iso_639_1"].toString(), name));
        }
    }

    qDebug() << "MovieService: set account states";
    if (obj.contains("account_states")) {
        item = obj["account_states"].toObject();
        model->setFavorite(item["favorite"].toBool());
        if (item["rated"].isObject()) {
            model->setRating((int)item["rated"].toObject()["value"].toVariant().toFloat());
        }
        model->setWatchlist(item["watchlist"].toBool());
    }

    qDebug() << "MovieService: set credits";
    if (obj.contains("credits")) {
        QJsonObject credits = obj["credits"].toObject();
        items = credits["cast"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            item = it->toObject();
            model->getCredits()->getCast()->add(CastListItem(
                    item["id"].toInt(),
                    item["name"].toString(),
                    item["original_name"].toString(),
                    item["profile_path"].toString(),
                    item["character"].toString()));
        }

        QList<CrewListItem> crewList;

        items = credits["crew"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            item = it->toObject();
            crewList.append(CrewListItem(
                                item["id"].toInt(),
                                item["name"].toString(),
                                item["original_name"].toString(),
                                item["profile_path"].toString(),
                                item["department"].toString(),
                                item["job"].toString()));
        }

        std::sort(crewList.begin(), crewList.end(), [](const CrewListItem &a, const CrewListItem &b)
        {
            return (a.getDepartment() + a.getName()) < (b.getDepartment() + b.getName());
        });

        for (int i = 0; i < crewList.count(); i++) {
            model->getCredits()->getCrew()->add(crewList.at(i));
        }
    }
    qDebug() << "MovieService: load from API - done";
}

void MovieService::favoriteDone(const QByteArray &data)
{
    qDebug() << "MovieService: favorite done";
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    if (obj["success"].toBool()) {
        model->setFavorite(!model->getFavorite());
    }
}

void MovieService::toggleWatchlistDone(const QByteArray &data)
{
    qDebug() << "MovieService: toggle watchlist done";
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    if (obj["success"].toBool()) {
        model->setWatchlist(!model->getWatchlist());
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
