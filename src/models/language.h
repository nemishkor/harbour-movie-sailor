#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QObject>
#include <QString>

class Language : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
public:
    explicit Language(QObject *parent);

    const QString &getId() const;
    void setId(const QString &newId);

    const QString &getName() const;
    void setName(const QString &newName);

signals:
    void idChanged();
    void nameChanged();

private:
    QString id;
    QString name;
};

#endif // LANGUAGE_H
