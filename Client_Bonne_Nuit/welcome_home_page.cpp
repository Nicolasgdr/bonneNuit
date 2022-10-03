#include "welcome_home_page.h"
#include "ui_welcome_home_page.h"
#include "Controller.h"
welcome_home_page::welcome_home_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcome_home_page)
{
    ui->setupUi(this);
}
welcome_home_page::welcome_home_page(QWidget *parent,Controller*controller_) :
    QWidget(parent),
    ui(new Ui::welcome_home_page),controller(controller_)
{
    ui->setupUi(this);
}

welcome_home_page::~welcome_home_page()
{
    delete ui;
}

void welcome_home_page::show_welcome_gui()
{
    this->ui->_sendBt->setDisabled(true);
    this->show();
}

void welcome_home_page::unlock_button()
{
    ui->welcom_msg->setText("Server is online you can start the game...");

    ui->_sendBt->setDisabled(false);
}

void welcome_home_page::close_windows()
{
    this->close();
}

void welcome_home_page::on__sendBt_clicked()
{
    this->controller->player_click_start();
}

