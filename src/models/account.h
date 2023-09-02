#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>

class Account : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString country READ getCountry WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool includeAdult READ getIncludeAdult WRITE setIncludeAdult NOTIFY includeAdultChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)

public:
    Account(QObject *parent);

    int getId() const;
    void setId(int newId);

    const QString &getLanguage() const;
    void setLanguage(const QString &newLanguage);

    const QString &getCountry() const;
    void setCountry(const QString &newCountry);

    const QString &getName() const;
    void setName(const QString &newName);

    bool getIncludeAdult() const;
    void setIncludeAdult(bool newIncludeAdult);

    const QString &getUsername() const;
    void setUsername(const QString &newUsername);

signals:
    void idChanged();

    void languageChanged();

    void countryChanged();

    void nameChanged();

    void includeAdultChanged();

    void usernameChanged();

private:
    int id;
    QString language;
    QString country;
    QString name;
    bool includeAdult;
    QString username;

};

#endif // ACCOUNT_H
