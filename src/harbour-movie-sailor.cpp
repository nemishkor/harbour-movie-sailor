#include <QtQuick>

#include <sailfishapp.h>

#include "src/app.h"
#include "src/logger.h"
#include "src/models/requestinfo.h"

int main(int argc, char *argv[])
{
    // Set up QML engine.
    QScopedPointer<QGuiApplication> guiApp(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    guiApp->setOrganizationName("nemishkor");

//    Logger::get().init();
    Logger::logSystemInfo();

    qInfo() << "applicationName" << guiApp->applicationName();
    qInfo() << "organizationName" << guiApp->organizationName();

    qmlRegisterType<Movie>("nemishkor.MovieSailor", 1, 0, "Movie");
    qmlRegisterType<Tv>("nemishkor.MovieSailor", 1, 0, "Tv");
    qmlRegisterType<Person>("nemishkor.MovieSailor", 1, 0, "Person");

    App app(view.data()->rootContext());

    view->setSource(SailfishApp::pathTo("qml/harbour-movie-sailor.qml"));
    view->show();

    return guiApp->exec();
}
