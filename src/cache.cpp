#include "cache.h"

Cache::Cache(QString name, QObject *parent) : QObject(parent)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    filePath = path + "/" + name;

    QDir dir(path);

    if (!dir.exists()) {
        bool mkPath = dir.mkpath(path);
        if (!mkPath) {
            qWarning() << "Unable to create a cache dir" << path;
        }
    }
}

bool Cache::exists()
{
    QFileInfo cacheFileInfo(filePath);
    return cacheFileInfo.exists() && cacheFileInfo.isFile();
}

QByteArray Cache::load()
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray content = file.readAll();
    file.close();

    return content;
}

void Cache::save(const QByteArray &data)
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
