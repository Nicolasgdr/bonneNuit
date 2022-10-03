#include "button_game.h"

button_game::button_game(QWidget*parent,const Position&button_position_)
    :QPushButton(parent),button_position(button_position_){}

[[maybe_unused]]const Position& button_game::get_button_position()const
{
    return button_position;
}

void button_game::mousePressEvent(QMouseEvent*event)
{

    event->accept();
    emit sendValue(button_position);
}
