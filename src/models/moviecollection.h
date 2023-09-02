#ifndef MOVIECOLLECTION_H
#define MOVIECOLLECTION_H

#include <QObject>

class MovieCollection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString posterPath READ getPosterPath WRITE setPosterPath NOTIFY posterPathChanged)
    Q_PROPERTY(QString backdropPath READ getBackdropPath WRITE setBackdropPath NOTIFY backdropPathChanged)

public:
    MovieCollection(QObject *parent);

    int getId() const;
    void setId(int newId);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getPosterPath() const;
    void setPosterPath(const QString &newPosterPath);

    const QString &getBackdropPath() const;
    void setBackdropPath(const QString &newBackdropPath);

signals:
    void idChanged();
    void nameChanged();
    void posterPathChanged();
    void backdropPathChanged();

private:
    int id;
    QString name;
    QString posterPath;
    QString backdropPath;
};

#endif // MOVIECOLLECTION_H
