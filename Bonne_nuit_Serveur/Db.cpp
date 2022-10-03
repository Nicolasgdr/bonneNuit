#include "Db.h"

Db::Db(){
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(db.open())
    {
        is_open = true;
        this->query=QSqlQuery(db);
        this->query.exec("create table game "
                         "(gameID INTEGER NOT NULL,"
                         "PRIMARY KEY(gameID AUTOINCREMENT)) ");
        this->query.exec("create table player "
                         "(playerID INTEGER NOT NULL,"
                         "nb_win INTEGER,"
                         "PRIMARY KEY(ID AUTOINCREMENT)) ");
        this->query.exec("create table game_info"
                         "(id_game INTEGER NOT NULL, id_player INTEGER NOT NULL, nb_win INTEGER,"
                         "status TEXT,"
                         "FOREIGN KEY(id_player) REFERENCES player,"
                         "FOREIGN KEY(id_game) REFERENCES game(gameID),"
                         "PRIMARY KEY(id_game,id_player))");

    }
}

bool Db::db_is_open()
{
    return is_open;
}
void Db::checkUser(int id_player, user_info &info){
this->query=QSqlQuery(db);
    if(query.exec("SELECT * FROM player WHERE id_player ='"+QString::number(id_player)+"'")){
        qDebug()<<"Query exec...\n";
        if (query.next()){
            int id = query.value(0).toInt();
            int nbWin = query.value(1).toInt();
            info.id=id;
            info.nbWin=nbWin;
        }else{
            query.exec("INSERT INTO player (id) VALUES ('"+ QString::number(id_player) +"'");
            query.next();
            int id = query.value(0).toInt();
               int nbWin = query.value(1).toInt();
               info.id=id;
               info.nbWin=nbWin;
            db.commit();
            qDebug()<<"player add";
        }
    }
}
void Db::read_Db(user_info& info){
    if(query.next()){
        int id = query.value("id").toInt();
        int nbWin = query.value("nb_win").toInt();
        info.id=id;
        info.nbWin=nbWin;

    }else{
         qDebug()<<"no next\n";
    }
}

void Db::clear_query(){
    query.clear();
    qDebug()<<query.isActive()<<"\n";
}
int Db::insert_get_game_id(){
    this->query.exec("INSERT INTO game (gameID) VALUES(NULL);SELECT max(gameID) FROM game;");
    query.next();
    int gameid = query.value(0).toInt();
    return gameid;
}
void Db::updateWin(int id_player){
    this->query.exec("UPDATE player SET nb_win = nb_win +1 WHERE id_player =  "+ QString::number(id_player) +""); //pas sur sur du nb_win +1

}
