#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDebug>
#include <QObject>
#include <QSettings>
#include <QCoreApplication>
#include <QStandardPaths>

#include "src/system.h"

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString sessionId READ getSessionId WRITE setSessionId NOTIFY sessionIdChanged)
    Q_PROPERTY(bool doNotShowRatingReminder READ getDoNotShowRatingReminder WRITE setDoNotShowRatingReminder NOTIFY doNotShowRatingReminderChanged)
    Q_PROPERTY(bool viewedMediaHistoryEnabled READ getViewedMediaHistoryEnabled WRITE setViewedMediaHistoryEnabled NOTIFY viewedMediaHistoryEnabledChanged)
    Q_PROPERTY(quint8 viewedMediaHistoryDaysLimit READ getViewedMediaHistoryDaysLimit WRITE setViewedMediaHistoryDaysLimit NOTIFY viewedMediaHistoryDaysLimitChanged)

public:
    Settings(System &system, QObject *parent);

    const QString &getLanguage() const;
    void setLanguage(const QString &newLanguage);

    const QString &getSessionId() const;
    void setSessionId(const QString &newSessionId);

    bool getDoNotShowRatingReminder() const;
    void setDoNotShowRatingReminder(bool newDoNotShowRatingReminder);

    bool getVisitedPagesHistory() const;
    void setVisitedPagesHistory(bool newVisitedPagesHistory);

    bool getViewedMediaHistoryEnabled() const;
    void setViewedMediaHistoryEnabled(bool newVisitedPagesHistoryEnabled);

    quint8 getViewedMediaHistoryDaysLimit() const;
    void setViewedMediaHistoryDaysLimit(quint8 newVisitedPagesHistoryDaysLimit);

private:
    QSettings *settings;
    QString language;
    QString sessionId;
    bool doNotShowRatingReminder;
    bool viewedMediaHistoryEnabled;
    quint8 viewedMediaHistoryDaysLimit;

signals:
    void languageChanged();
    void sessionIdChanged();
    void doNotShowRatingReminderChanged();
    void viewedMediaHistoryEnabledChanged();
    void viewedMediaHistoryDaysLimitChanged();
};

#endif // SETTINGS_H
