#ifndef WELCOME_HOME_PAGE_H
#define WELCOME_HOME_PAGE_H

#include <QWidget>
class Controller;

namespace Ui {
class welcome_home_page;
}

class welcome_home_page : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief welcome_home_page
     * @param parent
     */
    explicit welcome_home_page(QWidget *parent = nullptr);
    /**
     * @brief welcome_home_page
     * @param parent
     * @param controller
     */
    explicit welcome_home_page(QWidget*parent=nullptr,Controller* controller=nullptr);
    ~welcome_home_page();
    /**
     * @brief show_welcome_gui
     */
    void show_welcome_gui();
    /**
     * @brief unlock_button for the right player
     */
    void unlock_button();
    /**
     * @brief close_windows
     */
    void close_windows();
private slots:
    /**
     * @brief on__sendBt_clicked
     */
    void on__sendBt_clicked();

private:
    Ui::welcome_home_page *ui;
    Controller * controller;
};

#endif // WELCOME_HOME_PAGE_H
