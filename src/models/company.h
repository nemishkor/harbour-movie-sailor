#ifndef COMPANY_H
#define COMPANY_H

#include <QString>
#include <QJsonObject>

class Company
{
public:
    Company(int id, const QString &logo, const QString &name, const QString &country);
    Company(const QJsonObject &json);

    int getId() const;
    void setId(int newId);

    const QString &getLogo() const;
    void setLogo(const QString &newLogo);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getCountry() const;
    void setCountry(const QString &newCountry);

private:
    int id;
    QString logo;
    QString name;
    QString country;
};

#endif // COMPANY_H
