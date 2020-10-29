#include <QMainWindow>
#include <iostream>
#include <QMessageBox>
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <string.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QSqlDatabase logindata;
    logindata = QSqlDatabase::addDatabase("QMYSQL");

    logindata.setHostName("localhost");
    logindata.setDatabaseName("remoteworkouts");
    logindata.setUserName("defaultuser");
    logindata.setPassword("defaultuserpassword");
    logindata.open();

    QSqlQuery name;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setuser(QString rec){
    received = rec;
}

QString MainWindow::getUser(){
    return received;
}
