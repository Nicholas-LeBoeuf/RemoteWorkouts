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
    void setUser(QString rec);
    QString getUser();
    ~MainWindow();
    void loadData();

private:
    Ui::MainWindow *ui;
    QString received;
};
#endif // MAINWINDOW_H
