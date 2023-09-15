#include "logger.h"

Logger::Logger() :
    folder(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/logs"),
    sizeLimit(1024 * 100),
    numberLimit(20)
{
}

void Logger::init()
{
    if (!QDir(folder).exists()) {
        bool logFolderCreated = QDir().mkdir(folder);
        if (!logFolderCreated) {
            qWarning() << "Unable to create a log folder" << folder;
        }
    }

    deleteOldLogs();
    initLogFileName();

    QFile logFile(fileName);
    qDebug() << "Log file" << fileName;

    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qInstallMessageHandler(Logger::messageHandler);
    } else {
        qWarning() << "Unable to open log file to write" << fileName;
    }
}

Logger& Logger::get()
{
    static Logger logger;
    return logger;
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const QString &fileName = get().rotate();
    QFile logFile(fileName);
    logFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&logFile);

    ts << QString("%1T%2")
            .arg(QDate::currentDate().toString("yyyy-MM-dd"))
            .arg(QTime::currentTime().toString("hh:mm:ss"));
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    switch (type) {
    case QtDebugMsg:
        ts << " [DEBUG]";
        break;
    case QtInfoMsg:
        ts << "  [INFO]";
        break;
    case QtWarningMsg:
        ts << "  [WARN]";
        break;
    case QtCriticalMsg:
        ts << "  [CRIT]";
        break;
    case QtFatalMsg:
        ts << " [FATAL]";
        break;
    }

    ts << " " << msg << " (" << file << ":" << context.line << "," << function << ")" << endl;
}

void Logger::deleteOldLogs()
{
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time | QDir::Reversed);
    dir.setPath(folder);

    QFileInfoList list = dir.entryInfoList();
    int filesToDelete = list.size() - numberLimit;

    if (filesToDelete < 1) {
      return;
    }

    for (int i = 0; i < filesToDelete; i++) {
        QString path = list.at(i).absoluteFilePath();
        QFile file(path);
        file.remove();
    }
}

void Logger::initLogFileName()
{
    fileName = QString(folder + "/%1T%2.log")
              .arg(QDate::currentDate().toString("yyyy-MM-dd"))
            .arg(QTime::currentTime().toString("hh:mm:ss"));
}

const QString& Logger::rotate()
{
    int size = QFile(fileName).size();
    if (size > sizeLimit) {
        deleteOldLogs();
        initLogFileName();
    }

    return fileName;
}

void Logger::logSystemInfo()
{
    QFile file("/etc/hw-release");

    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open hw-release file:" << file.errorString();
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        if (line.contains("PRETTY_NAME=\"")) {
            qInfo() << "hw:" << line;
            break;
        }
    }

    file.close();

    QFile osFile("/etc/os-release");

    if(!osFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open hw-release file:" << osFile.errorString();
    }

    QTextStream osIn(&osFile);

    while(!osIn.atEnd()) {
        QString line = osIn.readLine();
        if (line.contains("PRETTY_NAME=\"")) {
            qInfo() << "os:" << line;
            break;
        }
    }

    osFile.close();
}
