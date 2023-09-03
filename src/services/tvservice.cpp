#include "tvservice.h"

TvService::TvService(Api &api, QObject *parent) :
    QObject(parent),
    api(api),
    model(new Tv(this)),
    request(api.getRequestInfo(Api::LoadTv)),
    requestFavorite(api.getRequestInfo(Api::ToggleFavoriteTv)),
    requestWatchlist(api.getRequestInfo(Api::ToggleWatchlistTv)),
    requestAddRating(api.getRequestInfo(Api::AddRatingTv)),
    requestRemoveRating(api.getRequestInfo(Api::RemoveRatingTv))
{
    connect(&api, &Api::loadTvDone, this, &TvService::apiRequestDone);
    connect(&api, &Api::toggleFavoriteTvDone, this, &TvService::favoriteDone);
    connect(&api, &Api::toggleWatchlistTvDone, this, &TvService::toggleWatchlistDone);
    connect(&api, &Api::addRatingTvDone, this, &TvService::addRatingDone);
    connect(&api, &Api::removeRatingTvDone, this, &TvService::removeRatingDone);
}

void TvService::toggleFavorite()
{
    api.toggleFavorite(*model);
}

void TvService::toggleWatchlist()
{
    api.toggleWatchlist(*model);
}

void TvService::addRating(int rating)
{
    qDebug() << "set rating" << rating << "for the TV show" << model->getId();
    model->setRating(rating);
    api.addRating(*model, rating);
}

void TvService::removeRating()
{
    model->setRating(0);
    api.removeRating(*model);
}

void TvService::fillWithListItemAndLoad(const MediaListItem &result)
{
    if (model->getId() == result.getId())
        return;

    model->setAdult(result.getAdult());
    model->setBackdropPath(result.getBackdropPath());
    model->getCreatedBy()->clear();
    model->setEpisodeRunTimeHours(0);
    model->setEpisodeRunTimeMinutes(0);
    model->setFirstAirDate("");
    model->setGenres(result.getGenres());
    model->setHomepage("");
    model->setId(result.getId());
    model->setInProduction(false);
    model->setLanguages(QList<QString>());
    model->setLastAirDate("");
    model->getLastEpisodeOnAir()->clear();
    model->setName(result.getTitle());
    model->getNextEpisodeOnAir()->clear();
    model->getNetworks()->clear();
    model->setNumberOfEpisodes(0);
    model->setNumberOfSeasons(0);
    model->setOriginCountry(QList<QString>());
    model->setOriginLanguage("");
    model->setOriginName(result.getOriginalTitle());
    model->setOverview(result.getOverview());
    model->setPopularity(0.0);
    model->setPosterPath(result.getPosterPath());
    model->getProductionCompanies()->clear();
    model->getProductionCountries()->clear();
    model->getSeasons()->clear();
    model->getSpokenLanguages()->clear();
    model->setStatus("");
    model->setTagline("");
    model->setType("");
    model->setVoteAvarage(result.getVoteAvarage());
    model->setVoteCount(result.getVoteCount());
    model->setFavorite(false);
    model->setRating(0);
    model->setWatchlist(false);

    api.loadTv(model->getId());
}

Tv *TvService::getModel() const
{
    return model;
}

RequestInfo *TvService::getRequest() const
{
    return request;
}

RequestInfo *TvService::getRequestFavorite() const
{
    return requestFavorite;
}

RequestInfo *TvService::getRequestWatchlist() const
{
    return requestWatchlist;
}

RequestInfo *TvService::getRequestAddRating() const
{
    return requestAddRating;
}

RequestInfo *TvService::getRequestRemoveRating() const
{
    return requestRemoveRating;
}

void TvService::apiRequestDone(QByteArray &data)
{
    QJsonObject obj = QJsonDocument::fromJson(data).object();

    QJsonArray items;
    QJsonArray::const_iterator it;

    if (obj["created_by"].isArray()) {
        items = obj["created_by"].toArray();
        QJsonArray::const_iterator it;
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            QJsonObject item = it->toObject();
            model->getCreatedBy()->add(PersonListItem(
                    item["id"].toInt(),
                    item["credit_id"].toString(),
                    item["name"].toString(),
                    item["gender"].toInt(),
                    item["profile_path"].toString()));
        }
    }

    QJsonArray episodeRunTimeJson = obj["created_by"].toArray();

    for (QJsonArray::const_iterator it = episodeRunTimeJson.constBegin(); it != episodeRunTimeJson.constEnd(); it++) {
        int runtime = it->toInt();
        model->setEpisodeRunTimeHours((int) (runtime / 60));
        model->setEpisodeRunTimeMinutes(runtime - model->getEpisodeRunTimeHours() * 60);
        break;
    }

    model->setFirstAirDate(obj["first_air_date"].toString());
    model->setHomepage(obj["homepage"].toString());
    model->setInProduction(obj["in_production"].toBool());

    QStringList languages;
    QJsonArray languagesJson = obj["languages"].toArray();

    for (QJsonArray::const_iterator it = languagesJson.constBegin(); it != languagesJson.constEnd(); it++) {
        languages.append(it->toString());
    }

    model->setLanguages(languages);
    model->setLastAirDate(obj["last_air_date"].toString());

    QJsonObject episode = obj["last_episode_to_air"].toObject();

    if (!episode.isEmpty()) {
        model->getLastEpisodeOnAir()->setAirDate(episode["air_date"].toString());
        model->getLastEpisodeOnAir()->setEpisodeNumber(episode["episode_number"].toInt());
        model->getLastEpisodeOnAir()->setEpisodeType(episode["episode_type"].toString());
        model->getLastEpisodeOnAir()->setId(episode["id"].toInt());
        model->getLastEpisodeOnAir()->setName(episode["name"].toString());
        model->getLastEpisodeOnAir()->setOverview(episode["overview"].toString());
        model->getLastEpisodeOnAir()->setProductionCode(episode["production_code"].toString());
        model->getLastEpisodeOnAir()->setRuntime(episode["runtime"].toInt());
        model->getLastEpisodeOnAir()->setSeasonNumber(episode["season_number"].toInt());
        model->getLastEpisodeOnAir()->setShowId(episode["show_id"].toInt());
        model->getLastEpisodeOnAir()->setStillPath(episode["still_path"].toString());
        model->getLastEpisodeOnAir()->setVoteAvarage(episode["vote_average"].toDouble());
        model->getLastEpisodeOnAir()->setVoteCount(episode["vote_count"].toInt());
    }

    episode = obj["next_episode_to_air"].toObject();

    if (!episode.isEmpty()) {
        model->getNextEpisodeOnAir()->setAirDate(episode["air_date"].toString());
        model->getNextEpisodeOnAir()->setEpisodeNumber(episode["episode_number"].toInt());
        model->getNextEpisodeOnAir()->setEpisodeType(episode["episode_type"].toString());
        model->getNextEpisodeOnAir()->setId(episode["id"].toInt());
        model->getNextEpisodeOnAir()->setName(episode["name"].toString());
        model->getNextEpisodeOnAir()->setOverview(episode["overview"].toString());
        model->getNextEpisodeOnAir()->setProductionCode(episode["production_code"].toString());
        model->getNextEpisodeOnAir()->setRuntime(episode["runtime"].toInt());
        model->getNextEpisodeOnAir()->setSeasonNumber(episode["season_number"].toInt());
        model->getNextEpisodeOnAir()->setShowId(episode["show_id"].toInt());
        model->getNextEpisodeOnAir()->setStillPath(episode["still_path"].toString());
        model->getNextEpisodeOnAir()->setVoteAvarage(episode["vote_average"].toDouble());
        model->getNextEpisodeOnAir()->setVoteCount(episode["vote_count"].toInt());
    }

    if (obj["networks"].isArray()) {
        items = obj["networks"].toArray();
        QJsonArray::const_iterator it;
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            QJsonObject item = it->toObject();
            model->getNetworks()->add(NetworkListItem(
                    item["id"].toInt(),
                    item["logo_path"].toString(),
                    item["name"].toString(),
                    item["origin_country"].toString()));
        }
    }

    model->setNumberOfEpisodes(obj["number_of_episodes"].toInt());
    model->setNumberOfSeasons(obj["number_of_seasons"].toInt());

    QStringList originCountries;
    items = obj["origin_country"].toArray();

    for (it = items.constBegin(); it != items.constEnd(); it++) {
        originCountries.append(it->toString());
    }

    model->setOriginCountry(originCountries);
    model->setOriginLanguage(obj["original_language"].toString());
    model->setPopularity(obj["popularity"].toDouble());

    if (obj["production_companies"].isArray()) {
        items = obj["production_companies"].toArray();
        QJsonArray::const_iterator it;
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            QJsonObject company = it->toObject();
            model->getProductionCompanies()->add(Company(
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
            model->getProductionCountries()->add(CountryListItem(
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
            model->getSpokenLanguages()->add(LanguageListItem(item["iso_639_1"].toString(), name));
        }
    }

    if (obj["seasons"].isArray()) {
        items = obj["seasons"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            QJsonObject item = it->toObject();
            model->getSeasons()->add(SeasonListItem(
                    item["air_date"].toString(),
                    item["episode_count"].toInt(),
                    item["id"].toInt(),
                    item["name"].toString(),
                    item["overview"].toString(),
                    item["poster_path"].toString(),
                    item["season_number"].toInt(),
                    item["vote_avarage"].toInt()));
        }
    }

    model->setStatus(obj["status"].toString());
    model->setTagline(obj["tagline"].toString());
    model->setType(obj["type"].toString());

    if (obj.contains("account_states")) {
        QJsonObject accountStates = obj["account_states"].toObject();
        model->setFavorite(accountStates["favorite"].toBool());
        if (accountStates["rated"].isObject()) {
            model->setRating((int)accountStates["rated"].toObject()["value"].toDouble());
        }
        model->setWatchlist(accountStates["watchlist"].toBool());
    }
}

void TvService::favoriteDone(const QByteArray &data)
{
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    if (obj["success"].toBool()) {
        model->setFavorite(!model->getFavorite());
    }
}

void TvService::toggleWatchlistDone(const QByteArray &data)
{
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    if (obj["success"].toBool()) {
        model->setWatchlist(!model->getWatchlist());
    }
}

void TvService::addRatingDone(const QByteArray &data)
{
    qDebug() << data;
}

void TvService::removeRatingDone(const QByteArray &data)
{
    qDebug() << data;
}
