#include "genresmovieservice.h"

GenresMovieService::GenresMovieService(Api &api, FileCache &cache, System &system, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("genres", "movie", "1"),
    model(this),
    initialized(false)
{
    language = system.getLanguage();
    key.key = language;
    connect(&api, &Api::genresDone, this, &GenresMovieService::apiRequestDone);
}

void GenresMovieService::initialize()
{
    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "load movie genres from cache";
        model.fillFromCache(cache.load(key));
        initialized = true;
        emit initializedChanged();
        return;
    }

    api.loadMovieGenres(language);
}

GenresListModel *GenresMovieService::getModel()
{
    return &model;
}

bool GenresMovieService::isInitialized()
{
    return initialized;
}

void GenresMovieService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "genres api request is done";
    QJsonDocument newJson = model.fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    initialized = true;
    emit initializedChanged();
}
