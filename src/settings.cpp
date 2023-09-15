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
