#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "src/app.h"
#include "src/models/requestinfo.h"

int main(int argc, char *argv[])
{
    // Set up QML engine.
    QScopedPointer<QGuiApplication> guiApp(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    guiApp->setOrganizationName("nemishkor");

    App app(view.data()->rootContext());
    qDebug() << "applicationName" << guiApp->applicationName();
    qDebug() << "organizationName" << guiApp->organizationName();

    view->setSource(SailfishApp::pathTo("qml/harbour-movie-sailor.qml"));
    view->show();
    return guiApp->exec();
}
