#include "json_interpreter.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

int json_interpreter::unpacked_ready_play(QByteArray data){
    QJsonDocument document = QJsonDocument::fromJson(data);
    if(!document.isEmpty()){
        QJsonObject object = document.object();
        QJsonValue id = object.value("PLAYER_ID");
        return id.toInt();
    }
    return 0;
}
game_info json_interpreter::unpacked_game_info(QByteArray data){
    QJsonDocument document = QJsonDocument::fromJson(data);
    game_info info;
    std::array<square_info,45> array;
    if(!document.isEmpty()){
        QJsonObject object = document.object();
        info.cursor=object.value("CURSOR").toInt(-1);
        info.row = object.value("ROW").toInt(-1);
        info.col = object.value("COL").toInt(-1);
        info.player_c = static_cast<Color>(object.value("PLAYER_COLOR").toInt());
        info.player_i = object.value("PLAYER_DB_ID").toInt(-1);
        info.current_player_id = object.value("CURRENT_PLAYER_ID").toInt(-1);
        info.sleeping = object.value("SLEEPING").toBool();
        info.current_c = static_cast<Color>(object.value("CURRENT_PLAYER_C").toInt());
        QJsonObject board_object = object.value("BOARD").toObject();
        QJsonArray data = board_object["DATA"].toArray();
        for (int i = 0; i < data.size(); ++i) {
            square_info temp;
            QJsonObject square = data.at(i).toObject();
            temp.position = Position(square.value("x").toInt(),square.value("y").toInt());
            temp.type = static_cast<Type>(square.value("Type").toInt());
            temp.color=static_cast<Color>(square.value("Color").toInt());
            array[i]=temp;
        }
        info.data=array;

    }
    return info;
}
Action_Send json_interpreter::get_type(QByteArray data)
{
    QJsonDocument document = QJsonDocument::fromJson(data);
    if(!document.isEmpty()){
        QJsonObject object = document.object();
        QJsonValue id = object.value("TYPE_MSG");
        return static_cast<Action_Send>(id.toInt());
    }
    return NULL_ACTION;

}
placement json_interpreter::unpacked_placement(QByteArray data){
    QJsonDocument document = QJsonDocument::fromJson(data);
    placement placement;
    if(!document.isEmpty()){
        QJsonObject object = document.object();
        QJsonValue row = object.value("ROW");
        QJsonValue col = object.value("COL");
        QJsonValue id = object.value("PLAYER_ID");
        placement.player_color=static_cast<Color>(object.value("PLAYER_COLOR").toInt());
        placement.position=Position(row.toInt(),col.toInt());
    }
    return placement;
}
Position json_interpreter::unpacked_remove(QByteArray data){
    QJsonDocument document = QJsonDocument::fromJson(data);
    Position position;
    if(!document.isEmpty()){
        QJsonObject object = document.object();
        QJsonValue row = object.value("ROW");
        QJsonValue col = object.value("COL");
        position=Position(row.toInt(),col.toInt());

    }
    return position;
}
int json_interpreter::colorWinner(QByteArray data){
    QJsonDocument document = QJsonDocument::fromVariant(data);
    if(!document.isEmpty()){
        QJsonObject object = document.object();
        return object.value("COLOR").toInt(-1);

    }
    return 0;
}
