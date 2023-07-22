#include "app.h"

App::App(QObject *parent) :
    QObject(parent),
    languagesCache("languages.json"),
    countriesCache("countries.json")
{
    QLocale locale;
    QString localeName = locale.name();
    int separatorPosition = localeName.indexOf('_');
    if (separatorPosition != -1 && localeName.length() >= (separatorPosition + 3)) {
        systemLanguage = localeName.mid(0, separatorPosition);
        systemCountry = localeName.mid(separatorPosition + 1, separatorPosition + 3);
    }
    qDebug() << "systemCountry:" << systemCountry;
    qDebug() << "systemLanguage:" << systemLanguage;

    languagesListModel = new LanguagesListModel(this);
    countriesListModel = new ConfigurationListModel(this);

    connect(&api.getConfigurationLanguagesWorker(), &ApiWorker::done, this, &App::languagesLoaded);
    connect(&api.getConfigurationCountriesWorker(), &ApiWorker::done, this, &App::countriesLoaded);
}

App::~App()
{
}

void App::initializeLanguages()
{
    if(languagesListModel->rowCount() > 0) {
        qDebug() << "languages list are already initialized";
        return;
    }

    if (languagesCache.exists()) {
        qDebug() << "languages cache file exists. Loading from the file";
        fillLanguages(languagesCache.load());
        return;
    }

    qDebug() << "languages cache file does not exist. Loading from API";
    api.loadConfigurationLanguages();
}

void App::initializeCountries()
{
    if(countriesListModel->rowCount() > 0) {
        qDebug() << "countries list are already initialized";
        return;
    }

    if (countriesCache.exists()) {
        qDebug() << "countries cache file exists. Loading from the file";
        fillCountries(countriesCache.load());
        return;
    }

    qDebug() << "countries cache file does not exist. Loading from API";
    api.loadConfigurationCounries();
}

void App::languagesLoaded(QByteArray &data)
{
    QJsonArray jsonLanguages = QJsonDocument::fromJson(data).array();
    QList<Language> languages;

    for (QJsonArray::const_iterator it = jsonLanguages.constBegin(); it != jsonLanguages.constEnd(); it++) {
        QJsonObject json = (*it).toObject();
        languages.append(Language(json, false));
        if (languages.last().getId() == systemLanguage) {
            languages.append(Language(json, true));
        }
    }

    qDebug() << "sorting languages...";
    std::sort(languages.begin(), languages.end(), [](const Language &a, const Language &b)
    {
        return ((a.getIsPrimary() || a.getId() == "xx") ? "" : a.getEnglishName()) < ((b.getIsPrimary() || b.getId() == "xx") ? "" : b.getEnglishName());
    });
    qDebug() << "languages are sorted";

    for (int i = 0; i < languages.count(); i++) {
        const Language &language = languages.at(i);
        languagesListModel->add(language);
        jsonLanguages.replace(i, language.toJson());
    }

    languagesCache.save(QJsonDocument(jsonLanguages).toJson(QJsonDocument::Compact));
}

void App::countriesLoaded(QByteArray &data)
{
    QJsonArray json = QJsonDocument::fromJson(data).array();
    QList<Configuration> items;

    for (QJsonArray::const_iterator it = json.constBegin(); it != json.constEnd(); it++) {
        QJsonObject json = (*it).toObject();
        QString id = json["iso_3166_1"].toString();
        QString englishName = json["english_name"].toString();
        items.append(Configuration(id, englishName, false));
        if (id == systemCountry) {
            items.append(Configuration(id, englishName, true));
        }
    }

    std::sort(items.begin(), items.end(), [](const Configuration &a, const Configuration &b)
    {
        return (a.getIsPrimary() ? "" : a.getLabel()) < (b.getIsPrimary() ? "" : b.getLabel());
    });

    countriesListModel->add(Configuration("", "All countries", true));
    for (int i = 0; i < items.count(); i++) {
        const Configuration &configuration = items.at(i);
        countriesListModel->add(configuration);
        json.replace(i, configuration.toJson());
    }

    countriesCache.save(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

Api &App::getApi()
{
    return api;
}

LanguagesListModel *App::getLanguagesListModel() const
{
    return languagesListModel;
}

ConfigurationListModel *App::getCountriesListModel() const
{
    return countriesListModel;
}

void App::fillLanguages(const QByteArray &data)
{
    QJsonArray languages = QJsonDocument::fromJson(data).array();
    for(QJsonArray::const_iterator it = languages.constBegin(); it != languages.constEnd(); it++){
        languagesListModel->add(Language((*it).toObject()));
    }
}

void App::fillCountries(const QByteArray &data)
{
    countriesListModel->add(Configuration("", "All countries", true));
    QJsonArray json = QJsonDocument::fromJson(data).array();
    for(QJsonArray::const_iterator it = json.constBegin(); it != json.constEnd(); it++){
        countriesListModel->add(Configuration((*it).toObject()));
    }
}
