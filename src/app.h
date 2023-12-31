#ifndef APP_H
#define APP_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QList>
#include <QDebug>
#include <QLocale>
#include <QQmlContext>

#include <src/services/searchservice.h>

#include "src/api.h"
#include "src/filecache.h"
#include "src/settings.h"
#include "src/models/account.h"
#include "src/models/discovermovie.h"
#include "src/models/configurationdetails.h"
#include "src/models/country.h"
#include "src/models/searchpeopleform.h"
#include "src/services/accountservice.h"
#include "src/services/countrieslistservice.h"
#include "src/services/configurationdetailsmanager.h"
#include "src/services/discovermovieservice.h"
#include "src/services/discovertvservice.h"
#include "src/services/historyservice.h"
#include "src/services/genresmovieservice.h"
#include "src/services/languageslistservice.h"
#include "src/services/movieservice.h"
#include "src/services/personservice.h"
#include "src/services/tvnetworksservice.h"
#include "src/viewmodels/searchpeoplelistmodel.h"
#include "src/viewmodels/filterbylanguageslistmodel.h"
#include "src/viewmodels/configurationlistmodel.h"
#include "src/system.h"


class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int menu READ getMenu WRITE setMenu NOTIFY menuChanged)
    Q_PROPERTY(QString coverPosterImage READ getCoverPosterImage WRITE setCoverPosterImage NOTIFY coverPosterImageChanged)
    Q_PROPERTY(QString coverProfileImage READ getCoverProfileImage WRITE setCoverProfileImage NOTIFY coverProfileImageChanged)
    Q_PROPERTY(Settings* settings READ getSettings CONSTANT)
    Q_PROPERTY(ConfigurationDetailsManager* config READ getConfigurationDetailsManager CONSTANT)
    Q_PROPERTY(MovieService* movieService READ getMovieService CONSTANT)
    Q_PROPERTY(AccountService* accountService READ getAccountService CONSTANT)
    Q_PROPERTY(Account* account READ getAccount CONSTANT)
    Q_PROPERTY(SearchService* searchService READ getSearchService CONSTANT)
    Q_PROPERTY(FileCache* cache READ getCache CONSTANT)
    Q_PROPERTY(PersonService* personService READ getPersonService CONSTANT)
    Q_PROPERTY(DiscoverTvService* discoverTvService READ getDiscoverTvService CONSTANT)
    Q_PROPERTY(HistoryService* historyService READ getHistoryService CONSTANT)
    Q_PROPERTY(TvNetworksService * tvNetworksService READ getTvNetworksService CONSTANT)

public:
    App(QQmlContext *context);

    Q_INVOKABLE void initializeCountries();

    Settings *getSettings() const;

    int getMenu() const;
    void setMenu(int newMenu);

    AccountService *getAccountService() const;
    Account *getAccount() const;
    SearchService *getSearchService() const;
    FileCache *getCache() const;
    MovieService *getMovieService() const;
    PersonService *getPersonService() const;
    ConfigurationDetailsManager *getConfigurationDetailsManager() const;
    HistoryService *getHistoryService() const;

    const QString &getCoverPosterImage() const;
    void setCoverPosterImage(const QString &newCoverPosterImage);

    const QString &getCoverProfileImage() const;
    void setCoverProfileImage(const QString &newCoverProfileImage);

    DiscoverTvService *getDiscoverTvService() const;
    TvNetworksService *getTvNetworksService() const;

signals:
    void menuChanged();
    void coverPosterImageChanged();
    void coverProfileImageChanged();

private:
    int menu;
    QString coverPosterImage;
    QString coverProfileImage;
    FileCache *cache;
    System system;
    Account *account;
    Settings *settings;
    Api api;
    GenresMovieService genresService;
    ConfigurationDetailsManager *configurationDetailsManager;
    HistoryService *historyService;
    MovieService *movieService;
    TvService tvService;
    PersonService *personService;
    CountriesListService countriesListService;
    DiscoverMovieService discoverMovieService;
    DiscoverTvService *discoverTvService;
    LanguagesListService languagesListService;
    AccountService *accountService;
    SearchService *searchService;
    TvNetworksService *tvNetworksService;

private slots:
    void validateContentLanguage();
    void updateCoverImageByMovie(Movie *movie);
    void updateCoverImageByTv(Tv *model);
    void updateCoverImageByPerson(Person *person);

};

#endif // APP_H
