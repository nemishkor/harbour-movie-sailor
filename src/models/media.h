#ifndef MEDIA_H
#define MEDIA_H

#include <QObject>

class Media : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MediaType mediaType READ getMediaType WRITE setMediaType NOTIFY mediaTypeChanged)
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString imagePath READ getImagePath WRITE setImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString historyDateTime READ getHistoryDateTime WRITE setHistoryDateTime NOTIFY historyDateTimeChanged)
public:
    enum MediaType {
        Unknown = 0,
        MovieType,
        TvType,
        PersonType
    };
    Media(QObject *parent);

    Q_ENUMS(MediaType)

    MediaType getMediaType() const;
    void setMediaType(MediaType newMediaType);

    int getId() const;
    void setId(int newId);

    const QString &getImagePath() const;
    void setImagePath(const QString &newImagePath);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getHistoryDateTime() const;
    void setHistoryDateTime(const QString &newHistoryDateTime);

signals:
    void mediaTypeChanged();
    void idChanged();
    void imagePathChanged();
    void nameChanged();
    void historyDateTimeChanged();

private:
    MediaType mediaType;
    int id;
    QString imagePath;
    QString name;
    QString historyDateTime;

};

#endif // MEDIA_H
