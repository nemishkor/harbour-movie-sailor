#include "settings.h"

Settings::Settings(System &system, QObject *parent) :
    QObject(parent)
{
    const QString settingsPath =
        QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)
        + "/" + QCoreApplication::applicationName() + ".conf";
    settings = new QSettings(settingsPath, QSettings::NativeFormat);
    language = settings->value("language", system.getLanguage()).toString();
    qInfo() << "Settings: language" << language;
    sessionId = settings->value("sessionId", "").toString();
    qInfo() << "Settings: sessionId is empty:" << (sessionId.isEmpty() ? "yes" : "no");
    doNotShowRatingReminder = settings->value("doNotShowRatingReminder", false).toBool();
    viewedMediaHistoryEnabled = settings->value("viewedMediaHistoryEnabled", true).toBool();
    viewedMediaHistoryDaysLimit = settings->value("viewedMediaHistoryDaysLimit", 14).toUInt();
    mediaSearchHistoryEnabled = settings->value("mediaSearchHistoryEnabled", true).toBool();
}

const QString &Settings::getLanguage() const
{
    return language;
}

void Settings::setLanguage(const QString &newLanguage)
{
    qInfo() << "Settings: set language" << newLanguage;
    if (language == newLanguage)
        return;
    language = newLanguage;
    settings->setValue("language", language);
    emit languageChanged();
}

const QString &Settings::getSessionId() const
{
    return sessionId;
}

void Settings::setSessionId(const QString &newSessionId)
{
    qInfo() << "Settings: set new sessionId";
    if (sessionId == newSessionId)
        return;
    sessionId = newSessionId;
    settings->setValue("sessionId", sessionId);
    emit sessionIdChanged();
}

bool Settings::getDoNotShowRatingReminder() const
{
    return doNotShowRatingReminder;
}

void Settings::setDoNotShowRatingReminder(bool newDoNotShowRatingReminder)
{
    if (doNotShowRatingReminder == newDoNotShowRatingReminder)
        return;
    doNotShowRatingReminder = newDoNotShowRatingReminder;
    settings->setValue("doNotShowRatingReminder", doNotShowRatingReminder);
    emit doNotShowRatingReminderChanged();
}

bool Settings::getViewedMediaHistoryEnabled() const
{
    return viewedMediaHistoryEnabled;
}

void Settings::setViewedMediaHistoryEnabled(bool newVisitedPagesHistoryEnabled)
{
    if (viewedMediaHistoryEnabled == newVisitedPagesHistoryEnabled)
        return;
    viewedMediaHistoryEnabled = newVisitedPagesHistoryEnabled;
    settings->setValue("viewedMediaHistoryEnabled", viewedMediaHistoryEnabled);
    emit viewedMediaHistoryEnabledChanged();
}

quint8 Settings::getViewedMediaHistoryDaysLimit() const
{
    return viewedMediaHistoryDaysLimit;
}

void Settings::setViewedMediaHistoryDaysLimit(quint8 newVisitedPagesHistoryDaysLimit)
{
    if (viewedMediaHistoryDaysLimit == newVisitedPagesHistoryDaysLimit)
        return;
    viewedMediaHistoryDaysLimit = newVisitedPagesHistoryDaysLimit;
    settings->setValue("viewedMediaHistoryDaysLimit", viewedMediaHistoryDaysLimit);
    emit viewedMediaHistoryDaysLimitChanged();
}

bool Settings::getMediaSearchHistoryEnabled() const
{
    return mediaSearchHistoryEnabled;
}

void Settings::setMediaSearchHistoryEnabled(bool newMediaSearchHistoryEnabled)
{
    if (mediaSearchHistoryEnabled == newMediaSearchHistoryEnabled)
        return;
    mediaSearchHistoryEnabled = newMediaSearchHistoryEnabled;
    settings->setValue("mediaSearchHistoryEnabled", viewedMediaHistoryDaysLimit);
    emit mediaSearchHistoryEnabledChanged();
}

