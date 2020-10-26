#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setuser(QString rec);
    QString getUser();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString received;
};
#endif // MAINWINDOW_H
