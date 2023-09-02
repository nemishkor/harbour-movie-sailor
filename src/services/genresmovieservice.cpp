#include "genresmovieservice.h"

GenresMovieService::GenresMovieService(Api &api, FileCache &cache, Settings &settings, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    settings(settings),
    key("genres", "movie", "1"),
    model(new GenresListModel(this)),
    initialized(false)
{
    connect(&settings, &Settings::languageChanged, this, &GenresMovieService::initialize);
    connect(&api, &Api::genresDone, this, &GenresMovieService::apiRequestDone);
}

void GenresMovieService::initialize()
{
    qDebug() << "initialize genres with language" << settings.getLanguage();

    if (key.key != settings.getLanguage()) {
        key.key = settings.getLanguage();
        model->clear();
        setInitialized(false);
    }

    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "load movie genres from cache";
        model->fillFromCache(cache.load(key));
        setInitialized(true);
        return;
    }

    api.loadMovieGenres();
}

GenresListModel *GenresMovieService::getModel()
{
    return model;
}

void GenresMovieService::setInitialized(bool newInitialized)
{
    if (initialized == newInitialized)
        return;
    initialized = newInitialized;
    emit initializedChanged();
}

bool GenresMovieService::isInitialized()
{
    return initialized;
}

void GenresMovieService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "genres api request is done";
    QJsonDocument newJson = model->fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    setInitialized(true);
}
