#ifndef REQUESTTOKEN_H
#define REQUESTTOKEN_H

#include <QObject>
#include <QString>
#include <QDateTime>

class RequestToken : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool success READ getSuccess WRITE setSuccess NOTIFY successChanged)
    Q_PROPERTY(QString requestToken READ getRequestToken WRITE setRequestToken NOTIFY requestTokenChanged)
    Q_PROPERTY(QDateTime expireAt READ getExpireAt WRITE setExpireAt NOTIFY expireAtChanged)
    Q_PROPERTY(bool valid READ isValid WRITE setValid NOTIFY validChanged)

public:
    RequestToken(bool success, const QString &requestToken, const QDateTime &expireAt, QObject *parent);

    bool isValid();
    void setValid(bool newValid);

    bool getSuccess() const;
    void setSuccess(bool newSuccess);

    const QString &getRequestToken();
    void setRequestToken(const QString &newRequestToken);

    const QDateTime &getExpireAt() const;
    void setExpireAt(const QDateTime &newExpireAt);

    const QByteArray &getRawBody() const;
    void setRawBody(const QByteArray &newRawBody);

signals:
    void successChanged();
    void requestTokenChanged();
    void expireAtChanged();
    void validChanged();

private:
    QByteArray rawBody;
    bool success;
    QString requestToken;
    QDateTime expireAt;

};

#endif // REQUESTTOKEN_H
