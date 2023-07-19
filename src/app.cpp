#include "app.h"

App::App(QObject *parent) :
    QObject(parent),
    languagesCache("languages.json")
{
    languagesListModel = new LanguagesListModel(this);
    connect(&api.getConfigurationLanguagesWorker(), &ApiWorker::done, this, &App::languagesLoaded);
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

void App::languagesLoaded(QByteArray &data)
{
    QString localeName = locale.name();
    QString systemLanguage = localeName.mid(0, localeName.indexOf('_'));
    qDebug() << "localeName:" << localeName;
    qDebug() << "systemLanguage:" << systemLanguage;
    QJsonArray jsonLanguages = QJsonDocument::fromJson(data).array();
    QList<Language> languages;

    for (QJsonArray::const_iterator it = jsonLanguages.constBegin(); it != jsonLanguages.constEnd(); it++) {
        QJsonObject json = (*it).toObject();
        languages.append(Language(json, false));
        if (languages.last().getId() == systemLanguage || languages.last().getId() == localeName) {
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

LanguagesListModel *App::getLanguagesListModel() const
{
    return languagesListModel;
}

RequestInfo *App::getLanguagesRequestInfo()
{
    return &api.getConfigurationLanguagesInfo();
}

void App::fillLanguages(const QByteArray &data)
{
    QJsonArray languages = QJsonDocument::fromJson(data).array();
    for(QJsonArray::const_iterator it = languages.constBegin(); it != languages.constEnd(); it++){
        languagesListModel->add(Language((*it).toObject()));
    }
}
