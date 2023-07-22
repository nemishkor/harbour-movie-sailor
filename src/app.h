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

#include "api.h"
#include "cache.h"
#include "viewmodels/languageslistmodel.h"
#include "viewmodels/configurationlistmodel.h"


class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);
    ~App();

    Q_INVOKABLE void initializeLanguages();
    Q_INVOKABLE void initializeCountries();

    Api &getApi();
    LanguagesListModel *getLanguagesListModel() const;
    ConfigurationListModel *getCountriesListModel() const;


private:
    Api api;
    QString systemLanguage;
    QString systemCountry;
    LanguagesListModel *languagesListModel;
    ConfigurationListModel *countriesListModel;
    Cache languagesCache;
    Cache countriesCache;

    void fillLanguages(const QByteArray &data);
    void fillCountries(const QByteArray &data);

public slots:
    void languagesLoaded(QByteArray &data);
    void countriesLoaded(QByteArray &data);

};

#endif // APP_H
