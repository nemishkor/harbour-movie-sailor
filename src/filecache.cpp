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

QString FileCache::usedMemory()
{
    return formatSize(dirSize(path));
}

void FileCache::clear()
{
    QDir dir(path);

    dir.setFilter( QDir::NoDotAndDotDot | QDir::Files );
    foreach (QString dirItem, dir.entryList())
        dir.remove( dirItem );

    dir.setFilter( QDir::NoDotAndDotDot | QDir::Dirs );
    foreach (QString dirItem, dir.entryList()) {
        if (dirItem == ".QtWebKit" || dirItem == ".mozilla")
            continue;
        QDir subDir(dir.absoluteFilePath(dirItem));
        subDir.removeRecursively();
    }
}

qint64 FileCache::dirSize(QString dirPath) {
    qint64 size = 0;
    QDir dir(dirPath);
    //calculate total size of current directories' files
    QDir::Filters fileFilters = QDir::Files|QDir::System|QDir::Hidden;
    for(QString filePath : dir.entryList(fileFilters)) {
        QFileInfo fi(dir, filePath);
        size+= fi.size();
    }
    //add size of child directories recursively
    QDir::Filters dirFilters = QDir::Dirs|QDir::NoDotAndDotDot|QDir::System|QDir::Hidden;
    for(QString childDirPath : dir.entryList(dirFilters))
        size+= dirSize(dirPath + QDir::separator() + childDirPath);
    return size;
}

QString FileCache::formatSize(qint64 size) {
    QStringList units = {"Bytes", "KB", "MB", "GB", "TB", "PB"};
    int i;
    double outputSize = size;
    for(i=0; i<units.size()-1; i++) {
        if(outputSize<1024) break;
        outputSize= outputSize/1024;
    }
    return QString("%0 %1").arg(outputSize, 0, 'f', 2).arg(units[i]);
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
