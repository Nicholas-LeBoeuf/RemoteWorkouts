#include <QMainWindow>
#include <iostream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edituserinfo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadData(){
    QSqlDatabase logindata = QSqlDatabase::database("qt_sql_default_connection");

    QSqlQuery name;
    name.prepare("select firstname, lastname from users where ID='" + getUser() + "';");
    name.exec();
    name.next();

    QSqlQuery userInfo;
    userInfo.prepare("select * from userinfo where UserID='" + getUser() + "';");
    userInfo.exec();
    userInfo.next();

    ui->firstname->setText(name.value(0).toString());
    ui->lastname->setText(name.value(1).toString());

    ui->UserFName->setText(name.value(0).toString());
    ui->UserLName->setText(name.value(1).toString());
    ui->UserAge->setText(userInfo.value(1).toString());
    ui->UserWeight->setText(userInfo.value(2).toString());
    ui->UserHeight->setText(userInfo.value(3).toString());
    ui->UserGender->setText(userInfo.value(4).toString());
    if (userInfo.value(5).toString() == "1")
        ui->UserGoal->setText("Lose Weight");
    else if (userInfo.value(5).toString() == "2")
        ui->UserGoal->setText("Gain Muscle");
    else if (userInfo.value(5).toString() == "3")
        ui->UserGoal->setText("Stay Fit");


}

void MainWindow::setUser(QString rec){
    received = rec;
}

QString MainWindow::getUser(){
    return received;
}

void MainWindow::on_edit_clicked()
{
    EditUserInfo EditUserInfo;
    EditUserInfo.setUser(getUser());
    EditUserInfo.exec();
    update();
}
