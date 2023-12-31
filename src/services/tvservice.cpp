#include "tvservice.h"

TvService::TvService(Api &api, HistoryService &historyService, GenresListModel *genresListModel, QObject *parent) :
    QObject(parent),
    api(api),
    historyService(historyService),
    genresListModel(genresListModel),
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

void TvService::load(Tv *tv, int id)
{
    qDebug() << "TvService: load from API";
    model = tv;
    connect(model, &QObject::destroyed, this, &TvService::tvIsDestroyed);
    model->setId(id);
    api.loadTv(id);
}

void TvService::toggleFavorite()
{
    qDebug() << "TvService: toggle favorite";
    api.toggleFavorite(*model);
}

void TvService::toggleWatchlist()
{
    qDebug() << "TvService: toggle watchlist";
    api.toggleWatchlist(*model);
}

void TvService::addRating(int rating)
{
    qDebug() << "TvService: add rating" << rating << "for the TV show" << model->getId();
    model->setRating(rating);
    api.addRating(*model, rating);
}

void TvService::removeRating()
{
    qDebug() << "TvService: remove rating";
    model->setRating(0);
    api.removeRating(*model);
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
    qDebug() << "TvService: load from API - got data";
    QJsonObject obj = QJsonDocument::fromJson(data).object();

    model->setAdult(obj["adult"].toBool());
    model->setBackdropPath(obj["backdrop_path"].toString());

    QStringList genreNames;
    QJsonArray genreIds = obj["genres"].toArray();
    for (QJsonArray::const_iterator genresIt = genreIds.constBegin(); genresIt != genreIds.constEnd(); genresIt++) {
        genreNames.append((*genresIt).toObject()["name"].toString());
    }
    model->setGenres(genreNames);

    QJsonArray items;
    QJsonArray::const_iterator it;
    QJsonObject item;

    model->getCreatedBy()->clear();
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

    QJsonArray episodeRunTimeJson = obj["episode_run_time"].toArray();

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

    qDebug() << "TvService: load from API - set episodes";
    QJsonObject episode = obj["last_episode_to_air"].toObject();

    model->getLastEpisodeOnAir()->setId(0);
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

    model->setName(obj["name"].toString());

    episode = obj["next_episode_to_air"].toObject();

    model->getNextEpisodeOnAir()->setId(0);
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

    qDebug() << "TvService: load from API - set networks";
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
    model->setOriginName(obj["original_name"].toString());
    model->setOverview(obj["overview"].toString());
    model->setPopularity(obj["popularity"].toDouble());
    model->setPosterPath(obj["poster_path"].toString());

    qDebug() << "TvService: load from API - set production companies";
    model->getProductionCompanies()->clear();
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

    qDebug() << "TvService: load from API - set production countries";
    model->getProductionCountries()->clear();
    if (obj["production_countries"].isArray()) {
        items = obj["production_countries"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            QJsonObject item = it->toObject();
            model->getProductionCountries()->add(CountryListItem(
                    item["iso_3166_1"].toString(),
                    item["name"].toString()));
        }
    }

    qDebug() << "TvService: load from API - set seasons";
    model->getSeasons()->clear();
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

    qDebug() << "TvService: load from API - set spoken languages";
    model->getSpokenLanguages()->clear();
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

    model->setStatus(obj["status"].toString());
    model->setTagline(obj["tagline"].toString());
    model->setType(obj["type"].toString());
    model->setVoteAvarage(obj["vote_average"].toDouble());
    model->setVoteCount(obj["vote_count"].toInt());

    qDebug() << "TvService: load from API - set account states";
    if (obj.contains("account_states")) {
        QJsonObject accountStates = obj["account_states"].toObject();
        model->setFavorite(accountStates["favorite"].toBool());
        if (accountStates["rated"].isObject()) {
            model->setRating((int)accountStates["rated"].toObject()["value"].toDouble());
        }
        model->setWatchlist(accountStates["watchlist"].toBool());
    }

    qDebug() << "TvService: set credits";
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

    qDebug() << "TvService: set videos";
    if (obj.contains("videos")) {
        items = obj["videos"].toObject()["results"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            item = it->toObject();
            VideoListItem video;
            video.setKey(item["key"].toString());
            video.setName(item["name"].toString());
            video.setType(item["type"].toString());
            video.setSite(item["site"].toString());
            video.setOfficial(item["official"].toBool());
            model->getVideos()->add(video);
        }
    }

    qDebug() << "TvService: set recommendations";
    if (obj.contains("recommendations")) {
        int recommendationsIndex = 1;
        int recommendationsLimit = 3;
        items = obj["recommendations"].toObject()["results"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            if (recommendationsIndex > recommendationsLimit) {
                break;
            }
            item = it->toObject();
            model->getRecommendations()->add(genresListModel->getItems(), item, MediaListItem::MediaType::TvType);

            recommendationsIndex++;
        }
    }

    qDebug() << "TvService: set similar";
    if (obj.contains("similar")) {
        int similarIndex = 1;
        int similarLimit = 3;
        items = obj["similar"].toObject()["results"].toArray();
        for (it = items.constBegin(); it != items.constEnd(); it++) {
            if (similarIndex > similarLimit) {
                break;
            }
            item = it->toObject();
            model->getSimilar()->add(genresListModel->getItems(), item, MediaListItem::MediaType::TvType);

            similarIndex++;
        }
    }

    emit tvIsLoaded(model);
    historyService.add(MediaListItem::TvType, obj["id"].toInt(), data);

    qDebug() << "TvService: load from API - done";
}

void TvService::favoriteDone(const QByteArray &data)
{
    qDebug() << "TvService: favorite done";
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    if (obj["success"].toBool()) {
        model->setFavorite(!model->getFavorite());
    }
}

void TvService::toggleWatchlistDone(const QByteArray &data)
{
    qDebug() << "TvService: toggle watchlist done";
    QJsonObject obj = QJsonDocument::fromJson(data).object();
    if (obj["success"].toBool()) {
        model->setWatchlist(!model->getWatchlist());
    }
}

void TvService::addRatingDone(const QByteArray &data)
{
    qDebug() << "TvService: add rating done";
    qDebug() << data;
}

void TvService::removeRatingDone(const QByteArray &data)
{
    qDebug() << "TvService: remove rating done";
    qDebug() << data;
}
