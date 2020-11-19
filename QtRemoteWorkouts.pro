QT += widgets
QT += sql
QT += charts
requires(qtConfig(combobox))


HEADERS     = mainwindow.h loginwindow.h newuserwindow.h edituserinfo.h welcomescreen.h forgotpassword.h
SOURCES     = main.cpp mainwindow.cpp loginwindow.cpp newuserwindow.cpp edituserinfo.cpp welcomescreen.cpp forgotpassword.cpp
FORMS       = mainwindow.ui loginwindow.ui newuserwindow.ui edituserinfo.ui welcomescreen.ui forgotpassword.ui
RESOURCES   = resources.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/layouts/RemoteWorkouts
INSTALLS += target
