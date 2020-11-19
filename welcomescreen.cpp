#include <iostream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <ctime>
#include <string>


#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include "mainwindow.h"

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

void WelcomeScreen::setUser(QString rec){
    received = rec;
}

QString WelcomeScreen::getUser(){
    return received;
}

void WelcomeScreen::loadQuote() {
    QSqlDatabase logindata = QSqlDatabase::database("qt_sql_default_connection");

    QSqlQuery quoteSql;

    quoteSql.prepare("select quote from quotes order by rand() limit 1;");
    quoteSql.exec();
    quoteSql.next();

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    ui->quote->setText(quoteSql.value(0).toString());
    ui->date->setText(date.toString("dddd, MMMM d, yyyy"));
    ui->time->setText(time.toString("h:mm AP"));
}

void WelcomeScreen::on_close_clicked()
{
    MainWindow *newMain = new MainWindow();
    newMain->setUser(getUser());
    newMain->loadData();
    newMain->show();
    this->hide();
}
