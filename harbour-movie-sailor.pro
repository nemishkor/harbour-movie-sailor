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
PKGCONFIG += qt5embedwidget

SOURCES += src/harbour-movie-sailor.cpp \
    src/api.cpp \
    src/apiworker.cpp \
    src/app.cpp \
    src/cachekey.cpp \
    src/filecache.cpp \
    src/listmodels/castslist.cpp \
    src/listmodels/crewlist.cpp \
    src/logger.cpp \
    src/models/account.cpp \
    src/models/accountmoviesform.cpp \
    src/models/cast.cpp \
    src/models/company.cpp \
    src/models/configurationdetails.cpp \
    src/models/configurationlistitem.cpp \
    src/models/country.cpp \
    src/models/countrylistitem.cpp \
    src/models/credits.cpp \
    src/models/crewlistitem.cpp \
    src/models/discovermovie.cpp \
    src/models/episode.cpp \
    src/models/filterbylanguagelistitem.cpp \
    src/models/form.cpp \
    src/models/genre.cpp \
    src/models/keyword.cpp \
    src/models/language.cpp \
    src/models/languagelistitem.cpp \
    src/models/loadpersonform.cpp \
    src/models/medialistitem.cpp \
    src/models/movie.cpp \
    src/models/moviecollection.cpp \
    src/models/movieprovider.cpp \
    src/models/networklistitem.cpp \
    src/models/person.cpp \
    src/models/personlistitem.cpp \
    src/models/requestinfo.cpp \
    src/models/requesttoken.cpp \
    src/models/searchform.cpp \
    src/models/searchpeopleform.cpp \
    src/models/searchpersonlistitem.cpp \
    src/models/seasonlistitem.cpp \
    src/models/tv.cpp \
    src/services/accountmedialistservice.cpp \
    src/services/accountservice.cpp \
    src/services/companiesservice.cpp \
    src/services/configurationdetailsmanager.cpp \
    src/services/countrieslistservice.cpp \
    src/services/discovermovieservice.cpp \
    src/services/genresmovieservice.cpp \
    src/services/keywordsservice.cpp \
    src/services/languageslistservice.cpp \
    src/services/movieprovidersmanager.cpp \
    src/services/movieservice.cpp \
    src/services/personservice.cpp \
    src/services/personslistservice.cpp \
    src/services/searchservice.cpp \
    src/services/tvservice.cpp \
    src/settings.cpp \
    src/system.cpp \
    src/viewmodels/companieslistmodel.cpp \
    src/viewmodels/companiessearchlistmodel.cpp \
    src/viewmodels/configurationlistmodel.cpp \
    src/viewmodels/countrieslistmodel.cpp \
    src/viewmodels/filterbycompanieslistmodel.cpp \
    src/viewmodels/filterbylanguageslistmodel.cpp \
    src/viewmodels/genreslistmodel.cpp \
    src/viewmodels/keywordslistmodel.cpp \
    src/viewmodels/keywordssearchlistmodel.cpp \
    src/viewmodels/languageslistmodel.cpp \
    src/viewmodels/medialistmodel.cpp \
    src/viewmodels/movieproviderslistmodel.cpp \
    src/viewmodels/networkslistmodel.cpp \
    src/viewmodels/personlistmodel.cpp \
    src/viewmodels/searchpeoplelistmodel.cpp \
    src/viewmodels/searchpersonlistmodel.cpp \
    src/viewmodels/seasonslistmodel.cpp

DISTFILES += qml/harbour-movie-sailor.qml \
    qml/Menu.qml \
    qml/components/Anatomy.qml \
    qml/components/AndOrListItem.qml \
    qml/components/BackdropBackgroundImage.qml \
    qml/components/BackgroundItemWithIcon.qml \
    qml/components/Badges.qml \
    qml/components/CompaniesValueButton.qml \
    qml/components/ConfigurationDialog.qml \
    qml/components/CreatedByList.qml \
    qml/components/FailedRequestInColumn.qml \
    qml/components/FilterSearchResultItem.qml \
    qml/components/FullPageRequestProgress.qml \
    qml/components/FullscreenImageModal.qml \
    qml/components/GlassSpacer.qml \
    qml/components/KeyValue.qml \
    qml/components/LabelBackgroundItem.qml \
    qml/components/LanguageDialog.qml \
    qml/components/LoginModal.qml \
    qml/components/MediaBackdropImage.qml \
    qml/components/MediaLinksModal.qml \
    qml/components/MediaProductionCompaniesList.qml \
    qml/components/MediaProductionCountries.qml \
    qml/components/MediaSpokenLanguagesList.qml \
    qml/components/Modal.qml \
    qml/components/ModalButton.qml \
    qml/components/MoviesListItem.qml \
    qml/components/OrderBy.qml \
    qml/components/OrderByDialog.qml \
    qml/components/PeopleFilterList.qml \
    qml/components/PersonListItem.qml \
    qml/components/RatingCircle.qml \
    qml/components/RatingModal.qml \
    qml/components/RemovableListItem.qml \
    qml/components/Spacer.qml \
    qml/components/Tag.qml \
    qml/components/TvEpisode.qml \
    qml/components/TwoMediaBlocks.qml \
    qml/components/VoteSlider.qml \
    qml/components/VoteSliderLabel.qml \
    qml/components/VoteSliderPoint.qml \
    qml/components/filters/CombineModeComboBox.qml \
    qml/components/filters/PeoplesValueButton.qml \
    qml/components/filters/PeoplesValueButtonTitle.qml \
    qml/components/filters/SearchResultItem.qml \
    qml/cover/CoverPage.qml \
    qml/dialogs/BaseDialog.qml \
    qml/dialogs/CompaniesDialog.qml \
    qml/dialogs/GenresDialog.qml \
    qml/dialogs/KeywordsDialog.qml \
    qml/dialogs/PeopleFilterDialog.qml \
    qml/languages.js \
    qml/pages/AboutPage.qml \
    qml/pages/AccountMediaListPage.qml \
    qml/pages/AccountPage.qml \
    qml/pages/BasePage.qml \
    qml/pages/DiscoverMoviePage.qml \
    qml/pages/DiscoverMovieResultsPage.qml \
    qml/pages/ListsPage.qml \
    qml/pages/LoginPage.qml \
    qml/pages/MovieCastPage.qml \
    qml/pages/MovieCrewPage.qml \
    qml/pages/MoviePage.qml \
    qml/pages/PersonPage.qml \
    qml/pages/SearchPage.qml \
    qml/pages/SearchResultsPage.qml \
    qml/pages/SecondPage.qml \
    qml/pages/SettingsPage.qml \
    qml/pages/TvPage.qml \
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
    src/cachekey.h \
    src/filecache.h \
    src/listmodels/castslist.h \
    src/listmodels/crewlist.h \
    src/logger.h \
    src/models/account.h \
    src/models/accountmoviesform.h \
    src/models/cast.h \
    src/models/company.h \
    src/models/configurationdetails.h \
    src/models/configurationlistitem.h \
    src/models/country.h \
    src/models/countrylistitem.h \
    src/models/credits.h \
    src/models/crewlistitem.h \
    src/models/discovermovie.h \
    src/models/episode.h \
    src/models/filterbylanguagelistitem.h \
    src/models/form.h \
    src/models/genre.h \
    src/models/keyword.h \
    src/models/language.h \
    src/models/languagelistitem.h \
    src/models/loadpersonform.h \
    src/models/medialistitem.h \
    src/models/movie.h \
    src/models/moviecollection.h \
    src/models/movieprovider.h \
    src/models/networklistitem.h \
    src/models/person.h \
    src/models/personlistitem.h \
    src/models/requestinfo.h \
    src/models/requesttoken.h \
    src/models/searchform.h \
    src/models/searchpeopleform.h \
    src/models/searchpersonlistitem.h \
    src/models/seasonlistitem.h \
    src/models/tv.h \
    src/models/workernames.h \
    src/services/accountmedialistservice.h \
    src/services/accountservice.h \
    src/services/companiesservice.h \
    src/services/configurationdetailsmanager.h \
    src/services/countrieslistservice.h \
    src/services/discovermovieservice.h \
    src/services/genresmovieservice.h \
    src/services/keywordsservice.h \
    src/services/languageslistservice.h \
    src/services/movieprovidersmanager.h \
    src/services/movieservice.h \
    src/services/personservice.h \
    src/services/personslistservice.h \
    src/services/searchservice.h \
    src/services/tvservice.h \
    src/settings.h \
    src/system.h \
    src/viewmodels/companieslistmodel.h \
    src/viewmodels/companiessearchlistmodel.h \
    src/viewmodels/configurationlistmodel.h \
    src/viewmodels/countrieslistmodel.h \
    src/viewmodels/filterbycompanieslistmodel.h \
    src/viewmodels/filterbylanguageslistmodel.h \
    src/viewmodels/genreslistmodel.h \
    src/viewmodels/keywordslistmodel.h \
    src/viewmodels/keywordssearchlistmodel.h \
    src/viewmodels/languageslistmodel.h \
    src/viewmodels/medialistmodel.h \
    src/viewmodels/movieproviderslistmodel.h \
    src/viewmodels/networkslistmodel.h \
    src/viewmodels/personlistmodel.h \
    src/viewmodels/searchpeoplelistmodel.h \
    src/viewmodels/searchpersonlistmodel.h \
    src/viewmodels/seasonslistmodel.h

RESOURCES += \
    qml.qrc
