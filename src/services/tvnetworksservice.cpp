#include "tvnetworksservice.h"

TvNetworksService::TvNetworksService(Api &api, FileCache &cache, QObject *parent) :
    QObject(parent),
    api(api),
    cache(cache),
    key("tv", "networks", "1.0"),
    model(new TVNetworksList(this)),
    sortFilterModel(new QSortFilterProxyModel(this)),
    request(api.getRequestInfo(Api::LoadTvNetworks)),
    exportFileNamePrefix("tv_network_ids_"),
    exportFileNameDateFormatSeparator("_"),
    exportFileNameDateFormat("MM" + exportFileNameDateFormatSeparator + "dd" + exportFileNameDateFormatSeparator + "yyyy"),
    exportFileNameFormat("json")
{
    exportsPath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/exports";
    connect(&api, &Api::loadTvNetworksDone, this, &TvNetworksService::loadDone);
    sortFilterModel->setSourceModel(model);
}

void TvNetworksService::load()
{
    qDebug() << "TvNetworksService: load";

    if (model->rowCount() > 0) {
        return;
    }

    QDir exportsDir(exportsPath);
    QStringList exportsFilesNameFilters;
    exportsFilesNameFilters << "*.json";
    QFileInfoList exportsFilesInfo = exportsDir.entryInfoList(exportsFilesNameFilters, QDir::Files);
    QFileInfo lastExportFileInfo;

    QFileInfoList::const_iterator exportsFilesInfoIt = exportsFilesInfo.constBegin();
    QDate latestExportDate;
    QFileInfo latestExportFile;

    for (; exportsFilesInfoIt != exportsFilesInfo.constEnd(); exportsFilesInfoIt++) {
        QString name = exportsFilesInfoIt->fileName();
        if (name.startsWith(exportFileNamePrefix)) {
            QString dateInName = name.mid(exportFileNamePrefix.length(), exportFileNameDateFormat.length());
            QStringList dateParts = dateInName.split(exportFileNameDateFormatSeparator);
            if (dateParts.length() == 3) {
                QDate exportDate(dateParts.at(2).toInt(), dateParts.at(0).toInt(), dateParts.at(1).toInt());
                if (latestExportDate.isNull() || latestExportDate <= exportDate) {
                    latestExportDate = exportDate;
                    latestExportFile = *exportsFilesInfoIt;
                }
            }
        }
    }

    if (!latestExportDate.isNull()) {
        qint64 daysDiff = latestExportDate.daysTo(QDate::currentDate());
        if (daysDiff < 30) {
            qDebug() << "TvNetworksService: actual file already exists. Days diff:" << daysDiff;
            actualExportFile = latestExportFile;
            fillModel();
            return;
        }
    }

    api.loadTvNetworks();
}

RequestInfo *TvNetworksService::getRequest() const
{
    return request;
}

TVNetworksList *TvNetworksService::getModel() const
{
    return model;
}

QSortFilterProxyModel *TvNetworksService::getSortFilterModel() const
{
    return sortFilterModel;
}

QString TvNetworksService::createFileName()
{
    QDateTime date = QDateTime::currentDateTimeUtc().addDays(-1);

    return exportFileNamePrefix + date.toString(exportFileNameDateFormat) + "." + exportFileNameFormat;
}

void TvNetworksService::fillModel()
{
    qDebug() << "TvNetworksService: fill model with file" << actualExportFile.absoluteFilePath();
    QFile file(actualExportFile.absoluteFilePath());
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        if (line.length() == 0) {
            break;
        }
        QByteArray lineB;
        lineB.append(line);
        QJsonObject obj = QJsonDocument::fromJson(lineB).object();
        model->add(TVNetworkListItem(obj["id"].toInt(), obj["name"].toString()));
    }

    file.close();
    qDebug() << "TvNetworksService: model is filled";
}

void TvNetworksService::loadDone(const QByteArray &data)
{
    QDir dir(exportsPath);

    if (!dir.exists()) {
        bool mkPath = dir.mkpath(exportsPath);
        if (!mkPath) {
            qWarning() << "TvNetworksService: unable to create a exports dir" << exportsPath;
        }
    }

    QString fileName = createFileName();
    QFile file(exportsPath + "/" + fileName + ".gz");
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();

    qDebug() << "TvNetworksService: archived export file is downloaded";

    QProcess gzip;
    QStringList processArguments;
    processArguments << "-d" << file.fileName();
    gzip.start("gzip", processArguments);

    if (!gzip.waitForFinished()) {
        qWarning() << "TvNetworksService: could not unarchive exports file with exit code" << gzip.exitCode();
    }

    actualExportFile = QFileInfo(file.fileName());
    qDebug() << "TvNetworksService: actual file is updated";
    fillModel();
}
