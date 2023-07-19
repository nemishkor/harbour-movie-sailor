#include "requestinfo.h"

RequestInfo::RequestInfo(QObject *parent) : QObject(parent)
{

}

RequestInfo::State &RequestInfo::getState()
{
    return state;
}

void RequestInfo::setState(State newState)
{
    if (newState != state) {
        state = newState;
        emit stateChanged();
    }
}

QString &RequestInfo::getError()
{
    return error;
}

void RequestInfo::setError(const QString &newError)
{
    if (newError != error) {
        error = newError;
        emit errorChanged();
    }
}

int RequestInfo::getProgress()
{
    return progress;
}

void RequestInfo::setProgress(int newProgress)
{
    if (newProgress != progress) {
        progress = newProgress;
        emit progressChanged();
    }
}
