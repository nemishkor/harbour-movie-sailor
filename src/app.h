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

#include "src/api.h"
#include "src/filecache.h"
#include "src/models/configurationdetails.h"
#include "src/models/searchpeopleform.h"
#include "src/services/countrieslistservice.h"
#include "src/services/configurationdetailsmanager.h"
#include "src/services/companiesservice.h"
#include "src/services/genresmovieservice.h"
#include "src/services/languageslistservice.h"
#include "src/services/movieprovidersmanager.h"
#include "src/services/personslistservice.h"
#include "src/viewmodels/peoplelistmodel.h"
#include "src/viewmodels/languageslistmodel.h"
#include "src/viewmodels/configurationlistmodel.h"
#include "src/system.h"


class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QQmlContext *context);

    Q_INVOKABLE void initializeConfigurationDetails();
    Q_INVOKABLE void initializeMovieProviders(const QString &region);
    Q_INVOKABLE void initializeLanguages();
    Q_INVOKABLE void initializeCountries();
    Q_INVOKABLE void initializePersons();

private:
    System system;
    Api api;
    FileCache cache;

    ConfigurationDetailsManager configurationDetailsManager;
    CompaniesService companiesService;
    CountriesListService countriesListService;
    GenresMovieService genresMovieService;
    MovieProvidersManager movieProvidersManager;
    LanguagesListService languagesListService;
    PersonsListService personsListService;
    SearchPeopleForm searchPeopleForm;

};

#endif // APP_H
