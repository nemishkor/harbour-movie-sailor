#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>
#include <QStandardPaths>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString sessionId READ getSessionId WRITE setSessionId NOTIFY sessionIdChanged)
    Q_PROPERTY(bool doNotShowRatingReminder READ getDoNotShowRatingReminder WRITE setDoNotShowRatingReminder NOTIFY doNotShowRatingReminderChanged)

public:
    Settings(QObject *parent);

    const QString &getLanguage() const;
    void setLanguage(const QString &newLanguage);

    const QString &getSessionId() const;
    void setSessionId(const QString &newSessionId);

    bool getDoNotShowRatingReminder() const;
    void setDoNotShowRatingReminder(bool newDoNotShowRatingReminder);

private:
    QSettings *settings;
    QString language;
    QString sessionId;
    bool doNotShowRatingReminder;

signals:
    void languageChanged();

    void sessionIdChanged();
    void doNotShowRatingReminderChanged();
};

#endif // SETTINGS_H
