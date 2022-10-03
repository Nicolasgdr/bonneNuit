#ifndef GAME_H
#include"Board.h"
#include"Player.hpp"
#include "QtDebug"
#define GAME_H
enum GameState{NOTSTARTED=0,DAY=1,NIGHT=2,FINISHED=3};
enum Action_Send{READY_TO_PLAY=0,CONNECTION_ESTABLISHED,SEND_DATA,CLICK,REMOVE,SWTNIGHT,NULL_ACTION,CLICK_START,INVALID_CLICK,GAME_OVER};

class Game
{

public:
    Game()=default;

public:

    int De();
    bool Placement(Position position, Color color);
    void RemovePion(Position position);

    bool checkEnd();
    int findLastStar();
    void nextPlayer();
    void movePions(int position);
    inline Player get_last_player(){return vectplayer.back();}
    Board getBoard();
    int getGameState(){
        return this->gameState;
    }

    bool setSleep();

    void setAction(Position&);
    void addPlayervec(int id);
    int getCurrentPlayer(){
        return this->currentplayer;
    }
    void playBots(int);
    std::vector<Player> getPlayers(){
        return vectplayer;
    }
    Color colorOfPlayer(int id);
    int getpionsPlaces(){
        return pionsPlaces;
    }
    bool issleeping() {
        return sleep;
    }
    int getCursor(){
        return cursor;
    }
    inline int get_curent_player_id(){return vectplayer.at(currentplayer).getDbId();}
    inline Color get_current_p_color(){return vectplayer.at(currentplayer).getColor();}
private:
    bool sleep;
    Board board;
    int gameState;
    std::vector<Player> vectplayer;
    int currentplayer=0;
    int cursor = 0;
    int nbplayers =0;
    int pionsPlaces =0;
    int pionselimines=15;
    std::vector<Player> vectbot;
};
#endif // GAME_H
