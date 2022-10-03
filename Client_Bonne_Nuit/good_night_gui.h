#ifndef GOOD_NIGHT_GUI_H
#define GOOD_NIGHT_GUI_H

#include <QWidget>
//#include "Controller.h"
#include "button_game.h"
#include "QGridLayout"
#include "gn-encap/json_interpreter.h"
#include "QLabel"
class Controller;
namespace Ui {
class good_night_gui;
}

class good_night_gui : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief good_night_gui
     * @param parent
     */
    explicit good_night_gui(QWidget *parent = nullptr);
    /**
     * @brief good_night_gui
     * @param parent
     * @param controller
     */
    explicit good_night_gui(QWidget*parent=nullptr,Controller* controller=nullptr);
    ~good_night_gui();
    /**
     * @brief init_board
     */
    void init_board(game_info);
    /**
     * @brief get_psoition_click
     * @return
     */
    Position get_psoition_click();
    /**
     * @brief update_gui
     */
    void update_gui(game_info);
    /**
     * @brief inform_invalid_click for print wrong messages
     */
    void inform_invalid_click();
    /**
     * @brief show_winner in the view
     */
    void show_winner(QString);

private slots:
    void set_button_position(Position&);
private:
    void delete_element();
    Ui::good_night_gui *ui;
    Controller * controller;
    QGridLayout *board_layout;
    QLabel * cursor_b;
    std::vector<button_game*> buttons;
    bool is_night;



};

#endif // GOOD_NIGHT_GUI_H
