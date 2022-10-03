#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H
//#include "Db.h"
#include"QTcpServer"
#include "Model/Game.h"
#include "Thread_players.h"
#include "Db.h"
class Thread_players;
class Server; //je comprend pas le fait de mettre 2 class
class Game_handler

{
    Server * server_;
    std::vector<Thread_players*> player_threads;
    Game bn_game;
    bool is_full;
    Db connexion;


  //  Db connexion;
public:
    /**
     * @brief Constructor of game_handler
     */
    Game_handler(Server*);
    /**
     * @brief Verfies how many players there are on the thread.
     * @return true if 7 or more, false otherwise.
     */
    bool server_is_Full();
    /**
     * @brief Verifies if the game is running.
     * @return true if so, false otherwise.
     */
    bool is_running();
    /**
     * @brief Creates a new thread for a player
     * @param handler
     */
    void creat_player_thread(qintptr &handler);
    /**
     * @brief Starts the last thread that was registered in the list?
     */
    void start_last_thread();
    /**
     * @brief Creates a game to manage with the data of the first person to connect.
     * @param name of the user.
     */
    void create_game();
    /**
     * @brief Getter for game object.
     * @return a game.
     */
    Game& get_game();
    /**
     * @brief Informs all the other player threads that there were changes to take note of.
     */
    void notify(QByteArray&,bool,QTcpSocket* socket=nullptr);
    /**
     * @brief Disconnects a player and removes the thread.
     */
    void disconnecte_player(Thread_players*);
    /**
    * @brief Returns the status to register in db related to win status.
    * @param a status in form of int(game_status).
    * @return what to register in db.
    */
   std::string get_win_from_int(int a);
   /**
    * @brief call_for_update the db
    */
   void call_for_update(int);

private:
    bool game_running;
    int id_player =0;

};

#endif // GAME_HANDLER_H
