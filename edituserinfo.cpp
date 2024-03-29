#include "edituserinfo.h"
#include <iostream>
#include "ui_edituserinfo.h"
#include "mainwindow.h"
#include "forgotpassword.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>

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

void EditUserInfo::loadData()
{
    QSqlQuery info;
    info.prepare("select age, heightinches, weight, gender, goal from userinfo where UserID='" + getUser() + "';");
    info.exec();
    info.next();

    ui->userAge->setText(info.value(0).toString());
    ui->userHeight->setText(info.value(1).toString());
    ui->userWeight->setText(info.value(2).toString());
    ui->userGender->setText(info.value(3).toString());

    const QString goal = info.value(4).toString();

    if(goal == "1")
        ui->goalCombo->setCurrentText("Losing weight");
    else if (goal == "2")
        ui->goalCombo->setCurrentText("Gaining muscle");
    else if(goal == "3")
        ui->goalCombo->setCurrentText("Staying fit");
}

void EditUserInfo::on_editButton_clicked()
{
    const QString username = ui->userUsername->text();
    const QString age = ui->userAge->text();
    const QString height = ui->userHeight->text();
    const QString weight = ui->userWeight->text();
    const QString gender = ui->userGender->text();
    const QString goal = ui->goalCombo->currentText();

    QSqlQuery updatedata;
    QSqlQuery updateusername;
    QString goalID;

    if(ui->goalCombo->currentText() == "Losing weight"){
        goalID = "1";
    }
    else if(ui->goalCombo->currentText() == "Gaining muscle"){
        goalID = "2";
    }
    else if(ui->goalCombo->currentText() == "Staying fit"){
        goalID = "3";
    }

    if (fieldValidation()) {
        if (username != NULL)
        {
            updateusername.prepare(
                    "UPDATE users SET username='" + username + "' WHERE ID='" + getUser() + "'"
                    );
        }
        updatedata.prepare(
                "UPDATE userinfo SET Age='" + age + "', Weight='" + weight + "', HeightInches='" + height +
                "', Gender='" + gender + "', Goal='" + goalID + "' WHERE userID='" + getUser() + "'"
        );
        updatedata.exec();
        updateusername.exec();

        QDate date = QDate::currentDate();
        QString datestr = date.toString();
        QSqlQuery checkDate;

        checkDate.prepare("select date from " + getUser() + "_wh where date = '" + datestr + "';");
        qDebug() << checkDate.lastQuery();
        checkDate.exec();
        checkDate.next();
        qDebug() << checkDate.result();
        QString dateChecked = checkDate.value(0).toString();
        qDebug() << dateChecked;
        qDebug() << datestr;

        QSqlQuery entry;

        if (dateChecked != datestr) {
            entry.prepare("insert into " + getUser() + "_wh(weight, date) values('" + weight + "', '" + datestr + "');");
            qDebug() << entry.lastQuery();
        }
        else {
            entry.prepare("update " + getUser() + "_wh set weight = " + weight + " where date ='" + datestr + "';");
            qDebug() << entry.lastQuery();
        }

        entry.exec();
        close();
    }
}

void EditUserInfo::setUser(QString rec) {
    received = rec;
}

QString EditUserInfo::getUser() {
    return received;
}

bool EditUserInfo::fieldValidation() {
    const QString username = ui->userUsername->text();
    const QString age = ui->userAge->text();
    const QString height = ui->userHeight->text();
    const QString weight = ui->userWeight->text();
    const QString gender = ui->userGender->text();
    const QString goal = ui->goalCombo->currentText();

    std::string usernameStr = username.toStdString();
    std::string ageStr = age.toStdString();
    std::string heightStr = height.toStdString();
    std::string weightStr = weight.toStdString();
    std::string genderStr = gender.toStdString();
    std::string goalStr = goal.toStdString();

    QSqlQuery unattempt;

    if (ageStr != "" && heightStr != "" && weightStr != "" && genderStr != "" && goalStr != "Make a selection...") {
        if (checkDigits(ageStr)) {
            if (checkDigits(heightStr)) {
                if (checkDigits(weightStr)) {
                    if (username != NULL) {
                        unattempt.prepare("select username from users where username='" + username + "';");

                        if (unattempt.exec()) {
                            unattempt.next();

                            if (username == unattempt.value(0).toString()) {
                                QMessageBox msgBox;
                                msgBox.setText("Username already being used");
                                msgBox.exec();
                                return false;
                            }
                            else if (username != unattempt.value(0).toString()) {
                                return true;
                            }
                        }
                    }
                    else {
                        return true;
                    }
                }
                else {
                    QMessageBox msgBox;
                    msgBox.setText("Weight must be in digit form");
                    msgBox.exec();
                }
            }
            else {
                QMessageBox msgBox;
                msgBox.setText("Height must be in digit form");
                msgBox.exec();
            }
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("Age must be in digit form");
            msgBox.exec();
        }
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("Not all fields are filled in!");
        msgBox.exec();
    }
}

bool EditUserInfo::checkDigits(const std::string &str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}
void EditUserInfo::on_close_clicked()
{
    close();
}
