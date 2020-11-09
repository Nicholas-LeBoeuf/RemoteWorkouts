#include <QMainWindow>
#include <iostream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QDebug>
#include <QDate>

#include <QChart>
#include <QChartView>
#include <QLineSeries>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edituserinfo.h"

using namespace QtCharts;

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

    loadTracking();
    loadExercises();
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

    QString weight = ui->doubleSpinBox->text();

    QSqlQuery entry;
    entry.prepare("insert into " + getUser() + "_wh(weight, date) values('" + weight + "', '" + datestr + "');");

    entry.exec();
    loadTracking();
}

void MainWindow::on_tabWidget_2_tabBarClicked()
{
    loadTracking();
}

void MainWindow::initializeTrackingModel(QSqlQueryModel *model, int type)
{
    if (type == 1) {
        model->setQuery("select weight, date from " + getUser() + "_wh;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Weight (lbs)"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    }
    else if (type == 2){
        QSqlQuery hqry;
        hqry.prepare("select HeightInches from userinfo where UserID = " +  getUser() + ";");
        hqry.exec();
        hqry.next();
        QString height = hqry.value(0).toString();

        model->setQuery("select ROUND(weight / " + height + "), date from " + getUser() + "_wh;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("BMI Measurement"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    }
}

void MainWindow::initializeExerciseModel(QSqlQueryModel *model, QString exercise)
{
    model->setQuery("select ExerciseName, ExerciseDesc from " + exercise + ";");
    qDebug() << model->query().lastQuery();
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Exercise"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
}

void MainWindow::loadTracking(){
    QSqlDatabase thedata = QSqlDatabase::database("qt_sql_default_connection");
    QLineSeries *series = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();

    QSqlQuery qry, hqry;
    qry.prepare("select ID, weight from " + getUser() + "_wh;");
    hqry.prepare("select HeightInches from userinfo where UserID = " +  getUser() + ";");
    qry.exec();

    while (qry.next()) {
        hqry.exec();
        hqry.next();
        int ID = qry.value(0).toInt();
        int weight = qry.value(1).toInt();
        int BMI = qry.value(1).toInt() / hqry.value(0).toInt();
        series->append(ID, weight);
        series2->append(ID, BMI);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Your weight progress over time");

    QChart *chart2 = new QChart();
    chart2->legend()->hide();
    chart2->addSeries(series2);
    chart2->createDefaultAxes();
    chart2->setTitle("Your BMI progress over time");

    QChartView *chartView = ui->chartViewer;
    ui->chartViewer->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QChartView *chartView2 = ui->chartViewer2;
    ui->chartViewer2->setChart(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    QSqlQueryModel *model = new QSqlQueryModel();
    initializeTrackingModel(model, 1);
    ui->weightTable->setModel(model);
    ui->weightTable->show();

    QSqlQueryModel *model2 = new QSqlQueryModel();
    initializeTrackingModel(model2, 2);
    ui->bmiTable->setModel(model2);
    ui->bmiTable->show();
}

void MainWindow::loadExercises(){
    QString execlist[4] = {"cardio", "core", "lowerbody", "upperbody"};
    for(int i = 0; i < 4; i++) {
        QSqlQueryModel *model = new QSqlQueryModel();
        initializeExerciseModel(model, execlist[i]);
        switch (i) {
            case 0:
                ui->cardioTable->setModel(model);
                break;
            case 1:
                ui->coreTable->setModel(model);
                break;
            case 2:
                ui->lowerTable->setModel(model);
                break;
            case 3:
                ui->upperTable->setModel(model);
                break;
        }
    }
}