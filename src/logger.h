#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QString>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QStandardPaths>

class Logger
{
public:
    Logger(Logger const&) = delete;
    void operator=(Logger const&) = delete;
    void init();
    static Logger& get();
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString& txt);
    static void logSystemInfo();

private:
    Logger();

    const QString folder;
    const int sizeLimit;
    const int numberLimit;
    QString fileName;

    void deleteOldLogs();
    void initLogFileName();
    const QString& rotate();
};

#endif // LOGGER_H
