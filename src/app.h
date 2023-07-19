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

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);
    ~App();

    Q_INVOKABLE void initializeLanguages();

    LanguagesListModel *getLanguagesListModel() const;

    RequestInfo *getLanguagesRequestInfo();

private:
    Api api;
    QLocale locale;
    LanguagesListModel *languagesListModel;
    Cache languagesCache;

    void fillLanguages(const QByteArray &data);

public slots:
    void languagesLoaded(QByteArray &data);

};

#endif // APP_H
