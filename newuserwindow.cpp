#include "newuserwindow.h"
#include "ui_newuserwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

newuserwindow::newuserwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newuserwindow)
{
    ui->setupUi(this);
}

void newuserwindow::on_CreateButton_clicked()
{
    QSqlDatabase loginbase;
    loginbase = QSqlDatabase::addDatabase("QMYSQL");

    loginbase.setHostName("localhost");
    loginbase.setDatabaseName("remoteworkouts");
    loginbase.setUserName("defaultuser");
    loginbase.setPassword("defaultuserpassword");
    loginbase.open();

    const QString username = ui->username->text();
    const QString fname = ui->firstname->text();
    const QString lname = ui->lastname->text();
    const QString password = ui->password->text();

    QSqlQuery unattempt, createacct;

    unattempt.prepare("select username from users where username='" + username + "';");
    if (unattempt.exec()){
        unattempt.next();
        if (username != unattempt.value(0).toString()){
            createacct.prepare("insert into users (username, firstname, lastname, password) values ('"+ username+"', '" + fname + "', '"+lname +"', '"+password+"');");
            createacct.exec();
            QMessageBox msgBox;
            msgBox.setText("account created");
            msgBox.exec();
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("failed");
        msgBox.exec();
    }
}


newuserwindow::~newuserwindow()
{
    delete ui;
}

