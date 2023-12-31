#ifndef FILECACHE_H
#define FILECACHE_H

#include <QDir>
#include <QJsonDocument>
#include <QObject>
#include <QStandardPaths>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "src/cachekey.h"

class FileCache : public QObject
{
    Q_OBJECT
public:
    explicit FileCache(QObject *parent = nullptr);
    bool exists(const CacheKey &key, const QString &format = "json") const;
    QJsonDocument load(const CacheKey &key) const;
    void save(const CacheKey &key, const QJsonDocument &json) const;
    Q_INVOKABLE QString usedMemory();
    Q_INVOKABLE void clear();

private:
    QString path;

    const QString buildFilePath(const CacheKey &key, const QString &format) const;
    void write(const QString filePath, const QByteArray &data) const;

    qint64 dirSize(QString dirPath);
    QString formatSize(qint64 size);

signals:

};

#endif // FILECACHE_H
