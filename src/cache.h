#ifndef CACHE_H
#define CACHE_H

#include <QDir>
#include <QObject>
#include <QStandardPaths>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

class Cache : public QObject
{
    Q_OBJECT
public:
    explicit Cache(QString name, QObject *parent = nullptr);
    bool exists();
    QByteArray load();
    void save(const QByteArray &data);

private:
    QString filePath;

signals:

};

#endif // CACHE_H
