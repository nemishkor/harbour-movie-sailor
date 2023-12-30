#ifndef TVNETWORK_H
#define TVNETWORK_H

#include <QObject>

class TvNetwork : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)

public:
    TvNetwork(QObject *parent);

    int getId() const;
    void setId(int newId);

    const QString &getName() const;
    void setName(const QString &newName);

private:
    int id;
    QString name;

signals:
    void idChanged();
    void nameChanged();
};

#endif // TVNETWORK_H
