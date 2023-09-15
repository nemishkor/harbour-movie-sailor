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
    qDebug() << "GenresMovieService: initialize with language" << settings.getLanguage();

    if (key.key != settings.getLanguage()) {
        key.key = settings.getLanguage();
        model->clear();
        setInitialized(false);
    }

    if (initialized) {
        return;
    }

    if (cache.exists(key)) {
        qDebug() << "GenresMovieService: initialize using cache";
        model->fillFromCache(cache.load(key));
        setInitialized(true);
        return;
    }

    qDebug() << "GenresMovieService: initialize using API - start";
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
    qDebug() << "GenresMovieService: initialize using API - got data";
    QJsonDocument newJson = model->fillFromAPI(QJsonDocument::fromJson(data));
    cache.save(key, newJson);
    setInitialized(true);
    qDebug() << "GenresMovieService: initialize using API - done";
}
