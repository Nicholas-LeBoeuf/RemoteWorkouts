#include <QMainWindow>
#include <iostream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDebug>
#include <QDate>
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
    name.prepare("select username, firstname, lastname from users where ID='" + getUser() + "';");
    name.exec();
    name.next();

    QSqlQuery userInfo;
    userInfo.prepare("select * from userinfo where UserID='" + getUser() + "';");
    userInfo.exec();
    userInfo.next();
    qDebug() << userInfo.lastQuery();

    ui->displayname->setText("Hello, " + name.value(0).toString());

    ui->UserFName->setText(name.value(1).toString());
    ui->UserLName->setText(name.value(2).toString());
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
    EditUserInfo EditUserInfo(this);
    EditUserInfo.setUser(getUser());
    EditUserInfo.exec();
    if(EditUserInfo.close()){
        loadData();
    }
    //update();
}

void MainWindow::on_addWeight_clicked(){
    QDate date = QDate::currentDate();
    QString datestr = date.toString();
    qDebug() << datestr;

    QString weight = ui->doubleSpinBox->text();

    QSqlQuery entry;
    entry.prepare("insert into " + getUser() + "_wh values('" + weight + "', '" + datestr + "');");
    qDebug() << entry.lastQuery();
    entry.exec();
}

void MainWindow::on_tabWidget_2_tabBarClicked()
{
    QSqlDatabase thedata = QSqlDatabase::database("qt_sql_default_connection");
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(thedata);
    qry->prepare("select * from " + getUser() + "_wh;");
    qry->exec();
    initializeModel(model);
    ui->weightTable->setModel(model);
    ui->weightTable->show();
}

void MainWindow::initializeModel(QSqlQueryModel *model)
{
    model->setQuery("select * from " + getUser() + "_wh;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Weight (lbs)"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
}
