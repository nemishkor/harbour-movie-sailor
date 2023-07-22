# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-movie-sailor

CONFIG += sailfishapp

SOURCES += src/harbour-movie-sailor.cpp \
    src/api.cpp \
    src/apiworker.cpp \
    src/app.cpp \
    src/cache.cpp \
    src/models/configuration.cpp \
    src/models/country.cpp \
    src/models/language.cpp \
    src/models/requestinfo.cpp \
    src/viewmodels/configurationlistmodel.cpp \
    src/viewmodels/languageslistmodel.cpp

DISTFILES += qml/harbour-movie-sailor.qml \
    qml/components/ConfigurationDialog.qml \
    qml/components/LanguageDialog.qml \
    qml/components/Menu.qml \
    qml/components/OrderByDialog.qml \
    qml/components/VoteSlider.qml \
    qml/components/VoteSliderPoint.qml \
    qml/cover/CoverPage.qml \
    qml/pages/BasePage.qml \
    qml/pages/DiscoverPage.qml \
    qml/pages/SecondPage.qml \
    rpm/harbour-movie-sailor.changes.in \
    rpm/harbour-movie-sailor.changes.run.in \
    rpm/harbour-movie-sailor.spec \
    translations/*.ts \
    harbour-movie-sailor.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-movie-sailor-de.ts

HEADERS += \
    src/api.h \
    src/apiworker.h \
    src/app.h \
    src/cache.h \
    src/models/configuration.h \
    src/models/country.h \
    src/models/language.h \
    src/models/requestinfo.h \
    src/viewmodels/configurationlistmodel.h \
    src/viewmodels/languageslistmodel.h
