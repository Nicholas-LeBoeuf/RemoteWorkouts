#ifndef NEWUSERWINDOW_H
#define NEWUSERWINDOW_H

#include <QDialog>

namespace Ui {
class newuserwindow;
}

class newuserwindow : public QDialog
{
    Q_OBJECT

public:
    explicit newuserwindow(QWidget *parent = nullptr);
    ~newuserwindow();

    bool fieldValidation();
    bool passwordValidation();



private slots:
    void on_CreateButton_clicked();

    void on_close_clicked();

private:
    Ui::newuserwindow *ui;
};

#endif // NEWUSERWINDOW_H
