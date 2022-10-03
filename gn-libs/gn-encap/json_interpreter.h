#ifndef JSON_INTERPRETER_H
#define JSON_INTERPRETER_H

#include "Model/Color.h"
#include "Model/Position.hpp"
#include "Model/Type.h"
#include <array>
#include "QString"
#include "Model/Game.h"
struct square_info{
    Position position;
    Type type;
    Color color;
};
struct game_info{
    int row;
    int col;
    Color player_c;
    int player_i;
    bool sleeping;
    std::array<square_info,45> data;
    int current_player_id;
    int cursor;
    bool place;
    Color current_c;
};
struct placement{
    Position position;
    Color player_color;
};

class json_interpreter
{

public:

    json_interpreter() = default;
    static int unpacked_ready_play(QByteArray data);
    static game_info unpacked_game_info(QByteArray data);
    static placement unpacked_placement(QByteArray data);
    static Position unpacked_remove(QByteArray data);
    static Action_Send get_type(QByteArray);
    static int colorWinner(QByteArray);
    static QString get_color(Color player)
    {
        switch (player) {
        case RED : return "RED";
        case BLUE: return "BLUE";
        case GREEN: return "GREEN";
        case BLACK: return "BLACK";
        case PURPLE: return "PURPLE";
        default:
            break;
        }
    }




};

#endif // JSON_INTERPRETER_H
