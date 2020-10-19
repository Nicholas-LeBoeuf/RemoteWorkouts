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

private slots:
    void on_pushButton_2_clicked();

    void on_CreateButton_clicked();

private:
    Ui::newuserwindow *ui;
};

#endif // NEWUSERWINDOW_H
