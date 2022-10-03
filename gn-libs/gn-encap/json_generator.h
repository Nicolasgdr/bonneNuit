#ifndef JSON_GENERATOR_H
#define JSON_GENERATOR_H
#include "QJsonDocument"
#include "QJsonArray"
#include "QJsonObject"
#include "Model/Game.h"


class json_generator
{
public:
    json_generator()=default;

    static QByteArray ready_to_play();
    static QByteArray user_launch_game();
    static QByteArray send_game_info(Game,Color,int);
    static QByteArray place_pion(Position,int);
    static QByteArray remove_pion(Position);
    static QByteArray turn_off_light();
    static QByteArray click_start();
    static QByteArray invalid_click();
    static QByteArray colorWinner(int color);

};

#endif // JSON_GENERATOR_H
