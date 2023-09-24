#ifndef MOVIEPROVIDER_H
#define MOVIEPROVIDER_H

#include <QString>

class MovieProvider
{
public:
    MovieProvider();

    const QString &getLogo() const;
    void setLogo(const QString &newLogo);


    const QString &getName() const;
    void setName(const QString &newName);

    int getId() const;
    void setId(int newId);

    int getPriority() const;
    void setPriority(int newPriority);

    bool getChecked() const;
    void setChecked(bool newChecked);

private:
    QString logo;
    QString name;
    int id;
    int priority;
    bool checked;
};

#endif // MOVIEPROVIDER_H
