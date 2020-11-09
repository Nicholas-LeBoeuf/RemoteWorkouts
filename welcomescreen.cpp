#include <iostream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDebug>
#include <QDate>
#include <ctime>
#include <string>

#include "welcomescreen.h"
#include "ui_welcomescreen.h"

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

void WelcomeScreen::loadQuote() {
    QSqlDatabase logindata = QSqlDatabase::database("qt_sql_default_connection");

    QSqlQuery quoteSql;



    quoteSql.prepare("select quote from quotes order by rand() limit 1;");
    quoteSql.exec();
    quoteSql.next();

    ui->quote->setText(quoteSql.value(0).toString());
}
