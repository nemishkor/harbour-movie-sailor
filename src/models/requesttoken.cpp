#include "requesttoken.h"

RequestToken::RequestToken(bool success, const QString &requestToken, const QDateTime &expireAt, QObject *parent) :
    QObject(parent),
    success(success),
    requestToken(requestToken),
    expireAt(expireAt)
{

}

bool RequestToken::isValid()
{
    return !rawBody.isEmpty() && success && !requestToken.isEmpty() && expireAt.isValid() && expireAt < QDateTime::currentDateTimeUtc();
}

void RequestToken::setValid(bool newValid)
{
    Q_UNUSED(newValid);
}

bool RequestToken::getSuccess() const
{
    return success;
}

void RequestToken::setSuccess(bool newSuccess)
{
    if (success == newSuccess)
        return;
    success = newSuccess;
    emit successChanged();
    validChanged();
}

const QString &RequestToken::getRequestToken()
{
    return requestToken;
}

void RequestToken::setRequestToken(const QString &newRequestToken)
{
    if (requestToken == newRequestToken)
        return;
    requestToken = newRequestToken;
    emit requestTokenChanged();
    validChanged();
}

const QDateTime &RequestToken::getExpireAt() const
{
    return expireAt;
}

void RequestToken::setExpireAt(const QDateTime &newExpireAt)
{
    if (expireAt == newExpireAt)
        return;
    expireAt = newExpireAt;
    emit expireAtChanged();
    validChanged();
}

const QByteArray &RequestToken::getRawBody() const
{
    return rawBody;
}

void RequestToken::setRawBody(const QByteArray &newRawBody)
{
    rawBody = newRawBody;
}
