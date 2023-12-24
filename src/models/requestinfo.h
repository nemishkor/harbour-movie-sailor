#ifndef REQUESTINFO_H
#define REQUESTINFO_H

#include <QObject>
#include <QString>

class RequestInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int state READ getState NOTIFY stateChanged)
    Q_PROPERTY(QString error READ getError NOTIFY errorChanged)
    Q_PROPERTY(int progress READ getProgress NOTIFY progressChanged)

public:
    enum State {
        StandBy = 0,
        Running = 1,
        Success = 2,
        Failed = 3
    };

    RequestInfo(QObject *parent);

    void start();

    State &getState();
    void setState(State newState);
    QString &getError();
    void setError(const QString &newError);
    int getProgress();
    void setProgress(int progress);

private:
    State state = State::StandBy;
    QString error = "";
    int progress = 0;

signals:
    void stateChanged();
    void errorChanged();
    void progressChanged();

};

#endif // REQUESTINFO_H
