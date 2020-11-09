#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QDialog>

namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = nullptr);
    void loadQuote();
    ~WelcomeScreen();

private slots:
    void on_close_clicked();

private:
    Ui::WelcomeScreen *ui;
};

#endif // WELCOMESCREEN_H
