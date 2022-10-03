#include "Server.h"

Server::Server(QObject*parent): QTcpServer(parent){}
void Server::start_server(){
    if(this->listen(QHostAddress("localhost"),PORT))
    {
        std::cout<<"Hello";
        qDebug()<< "-----------------------------------\n" <<"Server online...\n"<<"-----------------------------------\n";

    }else
    {
        qDebug()<<"Server not connectect error...\n";
    }


}
void Server::initialise_game(qintptr& handle){
    game_handlers.push_back(Game_handler(this));
    game_handlers.back().creat_player_thread(handle);
    game_handlers.back().start_last_thread();

}
void  Server::incomingConnection(qintptr handle){
    qDebug()<<"---------------------------------------\n"<< "New client coming with socket id"<<handle<<"----------------------------------------------\n";
 if(this->game_handlers.empty())
 {
     qDebug()<<"Game handler empty creating new one...\n";
     initialise_game(handle);
 }else
 {
     bool added=false;
     for(Game_handler& h : game_handlers){
         if(!h.server_is_Full())
         {
             added=true;
             h.creat_player_thread(handle);
             h.start_last_thread();
             break;
         }
     }
     if(!added)
     {
         initialise_game(handle);
     }
 }
}
