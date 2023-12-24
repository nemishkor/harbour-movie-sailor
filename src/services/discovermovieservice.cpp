#include "discovermovieservice.h"

DiscoverMovieService::DiscoverMovieService(Api &api,
                                           FileCache &cache,
                                           Settings &settings,
                                           GenresListModel *genres,
                                           QObject *parent) :
    QObject(parent),
    api(api),
    genres(*genres),
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
    qDebug() << "DiscoverMovieService: search";
    setInitialized(false);
    api.discoverMovies(*form);
}

void DiscoverMovieService::addCompanyFromSearch(int id)
{
    qDebug() << "DiscoverMovieService: add company from search";
    Company item = companiesService->getList()->findById(id);
    qDebug() << "DiscoverMovieService: found company" << item.getId();
    if (item.getId() != -1) {
        form->getCompanies()->add(item);
        companiesService->getList()->removeOneById(item.getId());
    }
}

void DiscoverMovieService::apiRequestDone(const QByteArray &data)
{
    qDebug() << "DiscoverMovieService: search - got data";
    model->fillFromAPI(genres.getItems(), QJsonDocument::fromJson(data));
    setInitialized(true);
    qDebug() << "DiscoverMovieService: search - done";
}

void DiscoverMovieService::initializeMovieProviders()
{
    qDebug() << "DiscoverMovieService: initialize movie providers";
    if (form->getWatchRegion().isEmpty())
        return;
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
