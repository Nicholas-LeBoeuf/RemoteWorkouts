#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>

namespace Ui {
class ForgotPassword;
}

class ForgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ForgotPassword(QWidget *parent = nullptr);
    void setUser(QString rec);
    QString getUser();
    void loadSecurityQ();
    bool fieldValidation();
    bool passwordValidation();
    bool securityValidation();
    ~ForgotPassword();

private slots:
    void on_close_clicked();

    void on_resetPassword_clicked();

private:
    QString received;
    Ui::ForgotPassword *ui;
};

#endif // FORGOTPASSWORD_H
