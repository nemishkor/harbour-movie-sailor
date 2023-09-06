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
#include "src/models/account.h"
#include "src/models/discovermovie.h"
#include "src/models/configurationdetails.h"
#include "src/models/country.h"
#include "src/models/searchpeopleform.h"
#include "src/models/settings.h"
#include "src/services/accountservice.h"
#include "src/services/countrieslistservice.h"
#include "src/services/configurationdetailsmanager.h"
#include "src/services/discovermovieservice.h"
#include "src/services/genresmovieservice.h"
#include "src/services/languageslistservice.h"
#include "src/services/movieservice.h"
#include "src/viewmodels/searchpeoplelistmodel.h"
#include "src/viewmodels/filterbylanguageslistmodel.h"
#include "src/viewmodels/configurationlistmodel.h"
#include "src/system.h"


class App : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Settings* settings READ getSettings CONSTANT)
    Q_PROPERTY(int menu READ getMenu WRITE setMenu NOTIFY menuChanged)
    Q_PROPERTY(MovieService* movieService READ getMovieService CONSTANT)
    Q_PROPERTY(AccountService* accountService READ getAccountService CONSTANT)
    Q_PROPERTY(Account* account READ getAccount CONSTANT)
    Q_PROPERTY(SearchService* searchService READ getSearchService CONSTANT)
    Q_PROPERTY(FileCache* cache READ getCache CONSTANT)

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

signals:
    void menuChanged();

private:
    int menu;
    FileCache *cache;
    System system;
    Account *account;
    Settings *settings;
    Api api;

    GenresMovieService genresService;
    ConfigurationDetailsManager configurationDetailsManager;
    MovieService *movieService;
    TvService tvService;
    CountriesListService countriesListService;
    DiscoverMovieService discoverMovieService;
    LanguagesListService languagesListService;
    AccountService *accountService;
    SearchService *searchService;

private slots:
    void validateContentLanguage();

};

#endif // APP_H
