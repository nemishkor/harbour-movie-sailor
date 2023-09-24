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
#include "src/services/countrieslistservice.h"
#include "src/services/configurationdetailsmanager.h"
#include "src/services/languageslistservice.h"
#include "src/services/movieprovidersmanager.h"
#include "src/viewmodels/languageslistmodel.h"
#include "src/viewmodels/configurationlistmodel.h"
#include "src/system.h"


class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QQmlContext *context, QObject *parent = nullptr);

    Q_INVOKABLE void initializeConfigurationDetails();
    Q_INVOKABLE void initializeMovieProviders(const QString &region);
    Q_INVOKABLE void initializeLanguages();
    Q_INVOKABLE void initializeCountries();

private:
    System system;
    Api api;
    FileCache cache;

    ConfigurationDetailsManager configurationDetailsManager;
    MovieProvidersManager movieProvidersManager;
    LanguagesListService languagesListService;
    CountriesListService countriesListService;


};

#endif // APP_H
