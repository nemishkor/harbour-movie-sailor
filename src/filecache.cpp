#include "filecache.h"

FileCache::FileCache(QObject *parent) : QObject(parent)
{
    path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

    QDir dir(path);

    if (!dir.exists()) {
        bool mkPath = dir.mkpath(path);
        if (!mkPath) {
            qWarning() << "Unable to create a cache dir" << path;
        }
    }
}

bool FileCache::exists(const CacheKey &key, const QString &format) const
{
    QFileInfo cacheFileInfo(buildFilePath(key, format));
    return cacheFileInfo.exists() && cacheFileInfo.isFile();
}

QJsonDocument FileCache::load(const CacheKey &key) const
{
    QFile file(buildFilePath(key, "json"));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray content = file.readAll();
    file.close();

    return QJsonDocument::fromJson(content);
}

void FileCache::save(const CacheKey &key, const QJsonDocument &json) const
{
    QString filePath = buildFilePath(key, "json");
    QByteArray data = json.toJson(QJsonDocument::Compact);
    write(filePath, data);
}

const QString FileCache::buildFilePath(const CacheKey &key, const QString &format) const
{
    QString filePath = path + "/";

    if (!key.section.isEmpty()) {
        filePath.append(key.section).append("/");
    }

    QDir dir(filePath);

    if (!dir.exists()) {
        bool mkPath = dir.mkpath(filePath);
        if (!mkPath) {
            qWarning() << "Unable to create a cache dir" << filePath;
        }
    }

    filePath.append(key.name);

    if (!key.key.isEmpty()) {
        filePath.append("-").append(key.key);
    }

    if (!key.version.isEmpty()) {
        filePath.append(".").append(key.version);
    }

    filePath.append(".").append(format);

    return filePath;
}

void FileCache::write(const QString filePath, const QByteArray &data) const
{
    QFile file(filePath);
    bool open = file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    if (!open) {
        qWarning() << "Unable to open" << filePath << "file to overwrite it:" << file.errorString();
        return;
    }

    file.write(data);
    file.close();
}
