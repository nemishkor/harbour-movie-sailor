#ifndef COUNTRY_H
#define COUNTRY_H

#include <QObject>
#include <QString>

class Country : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

public:
    Country(QObject *parent);

    const QString &getId() const;
    void setId(const QString &newId);

    const QString &getName() const;
    void setName(const QString &newName);

private:
    QString id;
    QString name;

signals:
    void idChanged();
    void nameChanged();
};

#endif // COUNTRY_H
