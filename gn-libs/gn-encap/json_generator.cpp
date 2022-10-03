#include "json_generator.h"

QByteArray json_generator::ready_to_play()
{
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::READY_TO_PLAY)));
    return QJsonDocument(json_ob).toJson();
}
QByteArray json_generator::invalid_click()
{
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::INVALID_CLICK)));
    return QJsonDocument(json_ob).toJson();
}

QByteArray json_generator::user_launch_game()
{
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::CONNECTION_ESTABLISHED)));
    return QJsonDocument(json_ob).toJson();
}

QByteArray json_generator::send_game_info(Game g, Color player_color,int db_id)
{
    size_t row = g.getBoard().getRow();
    size_t column = g.getBoard().getColumn();
    Type temp;
    Color c_temp;
    QJsonObject json_object;
    json_object.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::SEND_DATA)));
    json_object.insert("ROW",QJsonValue::fromVariant(static_cast<int>(row)));
    json_object.insert("COL",QJsonValue::fromVariant(static_cast<int>(column)));
    json_object.insert("PLAYER_COLOR",QJsonValue::fromVariant(static_cast<int>(player_color)));
    json_object.insert("PLAYER_DB_ID",QJsonValue::fromVariant(db_id));
    json_object.insert("CURRENT_PLAYER_ID",QJsonValue::fromVariant(g.get_curent_player_id()));
    json_object.insert("CURRENT_PLAYER_C",QJsonValue::fromVariant(static_cast<int>(g.get_current_p_color())));
    json_object.insert("SLEEPING",QJsonValue::fromVariant(g.issleeping()));
    json_object.insert("CURSOR",QJsonValue::fromVariant(g.getCursor()));
    QJsonObject board_info;
    QJsonArray data;
    for (size_t row_=0;row_<row ;++row_ ) {
        for(size_t col=0;col<column;++col)
        {
            QJsonObject square;
            temp = g.getBoard().getSquare(Position(row_,col)).getType();
            square.insert("x",QJsonValue::fromVariant(static_cast<int>(row_)));
            square.insert("y",QJsonValue::fromVariant(static_cast<int>(col)));
            square.insert("Type",QJsonValue::fromVariant(static_cast<int>(temp)));
            c_temp =g.getBoard().getSquare(Position(row_,col)).getColor();
            square.insert("Color",QJsonValue::fromVariant(static_cast<int>(c_temp)));
            data.push_back(square);

        }
    }
    board_info.insert("DATA",data);
    json_object.insert("BOARD",board_info);


    return QJsonDocument(json_object).toJson(QJsonDocument::Indented);
}
QByteArray json_generator::click_start()
{
    QJsonObject json_ob;
    json_ob.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::CLICK_START)));
    return QJsonDocument(json_ob).toJson();
}
QByteArray json_generator::place_pion(Position square_p, int color_player)
{
    QJsonObject position_square;
    position_square.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::CLICK)));
    position_square.insert("ROW",QJsonValue::fromVariant(static_cast<int>(square_p.getRow())));
    position_square.insert("COL",QJsonValue::fromVariant(static_cast<int>(square_p.getColumn())));
    position_square.insert("PLAYER_COLOR",QJsonValue::fromVariant(color_player));
    return QJsonDocument(position_square).toJson();
}
QByteArray json_generator::remove_pion(Position square_p){
    QJsonObject position_square;
    position_square.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::REMOVE)));
    position_square.insert("ROW",QJsonValue::fromVariant(static_cast<int>(square_p.getRow())));
    position_square.insert("COL",QJsonValue::fromVariant(static_cast<int>(square_p.getColumn())));
    return QJsonDocument(position_square).toJson();
}
QByteArray json_generator::turn_off_light(){
    QJsonObject switch_light;
    switch_light.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::SWTNIGHT)));
    return QJsonDocument(switch_light).toJson();
}


QByteArray json_generator::colorWinner(int color){
    QJsonObject colorWinner;
    colorWinner.insert("TYPE_MSG",QJsonValue::fromVariant(static_cast<int>(Action_Send::GAME_OVER)));
    colorWinner.insert("COLOR",QJsonValue::fromVariant(color));
    return QJsonDocument(colorWinner).toJson();
}
