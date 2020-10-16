#include "mainwindow.h"
#include "loginwindow.h"
#include <QtWidgets>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginWindow login;
    login.show();



    return a.exec();
}
