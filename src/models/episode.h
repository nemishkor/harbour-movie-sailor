#ifndef EPISODE_H
#define EPISODE_H

#include <QObject>
#include <QString>

class Episode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString overview READ getOverview WRITE setOverview NOTIFY overviewChanged)
    Q_PROPERTY(double voteAvarage READ getVoteAvarage WRITE setVoteAvarage NOTIFY voteAvarageChanged)
    Q_PROPERTY(int voteCount READ getVoteCount WRITE setVoteCount NOTIFY voteCountChanged)
    Q_PROPERTY(QString airDate READ getAirDate WRITE setAirDate NOTIFY airDateChanged)
    Q_PROPERTY(int episodeNumber READ getEpisodeNumber WRITE setEpisodeNumber NOTIFY episodeNumberChanged)
    Q_PROPERTY(QString episodeType READ getEpisodeType WRITE setEpisodeType NOTIFY episodeTypeChanged)
    Q_PROPERTY(QString productionCode READ getProductionCode WRITE setProductionCode NOTIFY productionCodeChanged)
    Q_PROPERTY(int runtime READ getRuntime WRITE setRuntime NOTIFY runtimeChanged)
    Q_PROPERTY(int seasonNumber READ getSeasonNumber WRITE setSeasonNumber NOTIFY seasonNumberChanged)
    Q_PROPERTY(int showId READ getShowId WRITE setShowId NOTIFY showIdChanged)
    Q_PROPERTY(QString stillPath READ getStillPath WRITE setStillPath NOTIFY stillPathChanged)

public:
    Episode(QObject *parent);

    void clear();

    int getId() const;
    void setId(int newId);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getOverview() const;
    void setOverview(const QString &newOverview);

    double getVoteAvarage() const;
    void setVoteAvarage(double newVoteAvarage);

    int getVoteCount() const;
    void setVoteCount(int newVoteCount);

    const QString &getAirDate() const;
    void setAirDate(const QString &newAirDate);

    int getEpisodeNumber() const;
    void setEpisodeNumber(int newEpisodeNumber);

    const QString &getEpisodeType() const;
    void setEpisodeType(const QString &newEpisodeType);

    const QString &getProductionCode() const;
    void setProductionCode(const QString &newProductionCode);

    int getRuntime() const;
    void setRuntime(int newRuntime);

    int getSeasonNumber() const;
    void setSeasonNumber(int newSeasonNumber);

    int getShowId() const;
    void setShowId(int newShowId);

    const QString &getStillPath() const;
    void setStillPath(const QString &newStillPath);

signals:
    void idChanged();
    void nameChanged();
    void overviewChanged();
    void voteAvarageChanged();
    void voteCountChanged();
    void airDateChanged();
    void episodeNumberChanged();
    void episodeTypeChanged();
    void productionCodeChanged();
    void runtimeChanged();
    void seasonNumberChanged();
    void showIdChanged();
    void stillPathChanged();

private:
    int id;
    QString name;
    QString overview;
    double voteAvarage;
    int voteCount;
    QString airDate;
    int episodeNumber;
    QString episodeType;
    QString productionCode;
    int runtime;
    int seasonNumber;
    int showId;
    QString stillPath;

};

#endif // EPISODE_H
