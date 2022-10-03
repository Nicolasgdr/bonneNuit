#ifndef BUTTON_GAME_H
#define BUTTON_GAME_H

#include "QPushButton"
#include "Model/Position.hpp"
#include "QMouseEvent"
class button_game : public QPushButton
{
    Q_OBJECT
    Position button_position;
protected:
    /**
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent*event)override;
signals:
    /**
     * @brief sendValue
     */
    void sendValue(Position&);
public:
    /**
     * @brief button_game
     * @param parent
     * @param button_position_
     */
    explicit button_game(QWidget *parent=nullptr,const Position& button_position_=Position());
    /**
     * @brief get_button_position
     * @return
     */
    const Position&get_button_position()const;
};

#endif // BUTTON_GAME_H
