#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "app.h"
#include "src/models/requestinfo.h"

int main(int argc, char *argv[])
{
    // Set up QML engine.
    QScopedPointer<QGuiApplication> guiApp(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    guiApp->setOrganizationName("nemishkor");

    App app;
    qDebug() << "applicationName" << guiApp->applicationName();
    qDebug() << "organizationName" << guiApp->organizationName();

    QQmlContext *context = view.data()->rootContext();
    context->setContextProperty("languagesListModel", app.getLanguagesListModel());
    context->setContextProperty("languagesRequestInfo", app.getLanguagesRequestInfo());
    context->setContextProperty("app", &app);

    view->setSource(SailfishApp::pathTo("qml/harbour-movie-sailor.qml"));
    view->show();
    return guiApp->exec();
}
