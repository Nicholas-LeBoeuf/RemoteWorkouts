#include "edituserinfo.h"
#include "ui_edituserinfo.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

EditUserInfo::EditUserInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserInfo)
{
    ui->setupUi(this);
}

EditUserInfo::~EditUserInfo()
{
    delete ui;
}

void EditUserInfo::on_editButton_clicked()
{
    const QString age = ui->userAge->text();
    const QString height = ui->userHeight->text();
    const QString weight = ui->userWeight->text();
    const QString gender = ui->userGender->text();
    const QString goal = ui->userGoal->text();

    QSqlQuery updatedata;

    updatedata.prepare(
            "UPDATE userinfo SET Age='" + age + "', Weight='" + weight + "', HeightInches='" + height + "', Gender='" + gender + "', Goal='" + goal + "' WHERE userID='" + getUser() + "'"
            );
    updatedata.exec();
    close();
}

void EditUserInfo::setUser(QString rec) {
    received = rec;
}

QString EditUserInfo::getUser() {
    return received;
}