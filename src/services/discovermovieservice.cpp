#include "discovermovieservice.h"

DiscoverMovieService::DiscoverMovieService(Api &api, GenresMovieService &genresService, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    form(new DiscoverMovie(this)),
    genresService(genresService),
    model(new DiscoverMovieResultListModel(this))
{
    connect(&api, &Api::discoverMoviesDone, this, &DiscoverMovieService::apiRequestDone);
}

void DiscoverMovieService::search()
{
    setInitialized(false);
    api.discoverMovies(*form);
}

void DiscoverMovieService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "discover movie api request done. Filling the model...";
    model->fillFromAPI(QJsonDocument::fromJson(data), genresService.getModel()->getItems());
    setInitialized(true);
}

DiscoverMovie *DiscoverMovieService::getForm() const
{
    return form;
}

DiscoverMovieResultListModel *DiscoverMovieService::getModel() const
{
    return model;
}

bool DiscoverMovieService::getInitialized() const
{
    return initialized;
}

void DiscoverMovieService::setInitialized(bool newInitialized)
{
    if (initialized == newInitialized)
        return;
    initialized = newInitialized;
    emit initializedChanged();
}
