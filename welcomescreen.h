#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = nullptr);
    void setUser(QString rec);
    QString getUser();
    void loadQuote();
    ~WelcomeScreen();
    void dateNotif();

private slots:
    void on_close_clicked();

private:
    Ui::WelcomeScreen *ui;
    QString received;

};

#endif // WELCOMESCREEN_H
