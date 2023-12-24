#ifndef DISCOVERMOVIESERVICE_H
#define DISCOVERMOVIESERVICE_H

#include <QDebug>
#include <QObject>

#include "src/api.h"
#include "src/filecache.h"
#include "src/settings.h"
#include "src/system.h"
#include "src/models/discovermovie.h"
#include "src/services/companiesservice.h"
#include "src/services/keywordsservice.h"
#include "src/services/movieprovidersmanager.h"
#include "src/services/movieservice.h"
#include "src/services/personslistservice.h"
#include "src/viewmodels/medialistmodel.h"
#include "src/viewmodels/genreslistmodel.h"

class DiscoverMovieService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DiscoverMovie* form READ getForm CONSTANT)
    Q_PROPERTY(MediaListModel* model READ getModel CONSTANT)
    Q_PROPERTY(MovieProvidersManager* movieProviders READ getMovieProviders CONSTANT)
    Q_PROPERTY(PersonsListService* personsListService READ getPersonsListService CONSTANT)
    Q_PROPERTY(CompaniesService* companiesService READ getCompaniesService CONSTANT)
    Q_PROPERTY(KeywordsService* keywordsService READ getKeywordsService CONSTANT)
    Q_PROPERTY(bool initialized READ getInitialized WRITE setInitialized NOTIFY initializedChanged)

public:
    DiscoverMovieService(Api &api,
                      FileCache &cache,
                      Settings &settings,
                      GenresListModel *genres,
                      QObject *parent);
    Q_INVOKABLE void search();
    Q_INVOKABLE void addCompanyFromSearch(int id);

    bool getInitialized() const;
    void setInitialized(bool newInitialized);

    MediaListModel *getModel() const;
    DiscoverMovie *getForm() const;
    MovieProvidersManager *getMovieProviders() const;
    PersonsListService *getPersonsListService() const;
    CompaniesService *getCompaniesService() const;
    KeywordsService *getKeywordsService() const;

public slots:
    void apiRequestDone(const QByteArray &data);
    void initializeMovieProviders();

private:
    Api &api;
    GenresListModel &genres;
    DiscoverMovie* form;
    MovieProvidersManager* movieProviders;
    PersonsListService* personsListService;
    CompaniesService* companiesService;
    KeywordsService* keywordsService;
    MediaListModel* model;
    bool initialized;

signals:
    void initializedChanged();

};

#endif // DISCOVERMOVIESERVICE_H
