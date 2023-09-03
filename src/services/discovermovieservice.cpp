#include "discovermovieservice.h"

DiscoverMovieService::DiscoverMovieService(Api &api,
                                           FileCache &cache,
                                           Settings &settings,
                                           MovieService &movieService,
                                           GenresListModel *genres,
                                           QObject *parent) :
    QObject(parent),
    api(api),
    movieService(movieService),
    form(new DiscoverMovie(genres, this)),
    movieProviders(new MovieProvidersManager(api, cache, settings, form->getProviders(), this)),
    personsListService(new PersonsListService(api, cache, settings, form->getAnyRoleList(), form->getCastRoleList(), form->getCrewRoleList(), this)),
    companiesService(new CompaniesService(api, cache, form->getCompanies(), this)),
    keywordsService(new KeywordsService(api, cache, form->getKeywords(), this)),
    model(new MediaListModel(this))
{
    connect(&api, &Api::discoverMoviesDone, this, &DiscoverMovieService::apiRequestDone);
    connect(form, &DiscoverMovie::watchRegionChanged, this, &DiscoverMovieService::initializeMovieProviders);
}

void DiscoverMovieService::search()
{
    setInitialized(false);
    api.discoverMovies(*form);
}

void DiscoverMovieService::select(int id)
{
    QList<MediaListItem>::const_iterator it;
    for (it = model->getItems().constBegin(); it != model->getItems().constEnd(); it++) {
        if (it->getId() == id) {
            movieService.fillWithListItemAndLoad(*it);
            return;
        }
    }
}

void DiscoverMovieService::addCompanyFromSearch(int id)
{
    Company item = companiesService->getList()->findById(id);
    qDebug() << "found item" << item.getId();
    if (item.getId() != -1) {
        form->getCompanies()->add(item);
        companiesService->getList()->removeOneById(item.getId());
    }
}

void DiscoverMovieService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "discover movie api request done. Filling the model...";
    model->fillFromAPI(QJsonDocument::fromJson(data), form->getGenres()->getItems());
    setInitialized(true);
}

void DiscoverMovieService::initializeMovieProviders()
{
    if (form->getWatchRegion().isEmpty())
        return;
    qDebug() << "initializeMovieProviders(" << form->getWatchRegion() << ")";
    movieProviders->initialize(form->getWatchRegion());
}

KeywordsService *DiscoverMovieService::getKeywordsService() const
{
    return keywordsService;
}

CompaniesService *DiscoverMovieService::getCompaniesService() const
{
    return companiesService;
}

PersonsListService *DiscoverMovieService::getPersonsListService() const
{
    return personsListService;
}

MovieProvidersManager *DiscoverMovieService::getMovieProviders() const
{
    return movieProviders;
}

DiscoverMovie *DiscoverMovieService::getForm() const
{
    return form;
}

MediaListModel *DiscoverMovieService::getModel() const
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
