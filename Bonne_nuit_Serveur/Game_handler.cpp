#include "Game_handler.h"

Game_handler::Game_handler(Server*server): server_(server)
{
    this->game_running=false;
    //this->connexion=db_connexion();
}
bool Game_handler::server_is_Full(){
    return player_threads.size()==5;
}
bool Game_handler::is_running(){
    return game_running;
}
void Game_handler::creat_player_thread(qintptr &handler){
    this->player_threads.push_back(new Thread_players(handler,reinterpret_cast<QTcpServer*>(this->server_)));
    this->player_threads.back()->set_handler(this);
}
void Game_handler::start_last_thread(){
    this->player_threads.back()->run();
}
void Game_handler::create_game(){
      user_info info;
    if(game_running)
    {
        qDebug()<<"DB update...\n";
        connexion.checkUser(id_player,info);
        qDebug()<<"game running";
          id_player++;
        this->bn_game.addPlayervec(id_player);

    }else{
        qDebug()<<"not runnig";
        this->bn_game = Game();
        game_running=true;
        qDebug()<<"Game created...\n";
        if(connexion.db_is_open()){
            connexion.checkUser(id_player,info);
            id_player++;
            auto game_id= this->connexion.insert_get_game_id(); // j'ajoute un game_id
        }
        this->bn_game.addPlayervec(id_player);
        qDebug()<<"Game Player added...\n";
        int nb_connected=player_threads.size();
        this->bn_game.playBots(nb_connected);
        this->is_full=true;
        qDebug()<<"Allez bott actionnnnnnnn...\n";
    }


}
void Game_handler::notify(QByteArray& data,bool everybody,QTcpSocket*socket){
    if(everybody)
        std::for_each(player_threads.begin(),player_threads.end(),
                      [&data](Thread_players*thread){thread->notify(data);});
    else{qDebug()<<data+"\n"; qDebug()<<socket->write(data);}
}
void Game_handler::disconnecte_player(Thread_players *t){
    auto p_it= player_threads.begin();
    for(auto it=player_threads.begin();it!=player_threads.end();it++)
    {
        if(*it==t)
        {
            p_it=it;
        }
    }
    player_threads.erase(p_it);
    //bn_game.remove_player(t->get_db_id());
    if(player_threads.empty())
    {

    }
}
std::string Game_handler::get_win_from_int(int a){
    switch (a){
    case 1:{
        return "WIN";
        break;
    }
    case 2:{
        return "LOOSE";
        break;
    }
    case 4:{
        return "PLAY";
        break;
    }
    default :return "";
    }
}

Game& Game_handler::get_game()
{
    return bn_game;
}
void Game_handler::call_for_update(int id){
    connexion.updateWin(id);
}
