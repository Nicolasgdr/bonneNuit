#include"Game.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include"Color.h"
#include "random.hpp"

/**
 * Return random number for the de
 * @brief Game::De
 * @return random value between 1 and 3
 */
int Game::De(){
    int dice = he2b::nvs::random_value(1, 3);
    cursor += dice;
    if (cursor> 8)
        cursor -= 9;
    return cursor;
}
/**
 * @brief Game::AddPlayervec
 * @param player
 */
void Game::addPlayervec(int id){
    std::array<Color,5> colors = {RED,BLUE,GREEN,PURPLE,BLACK};
    bool found=false;
    if(vectplayer.empty())
    {
        Player player(id,colors[0]);
        vectplayer.push_back(player);

    }else{
        for (int var = 0; var < static_cast<int>(vectplayer.size())&&!found; ++var) {
            if(vectplayer.at(var).getColor()==colors.at(var))
            {
                found = true;
                Player player(id,colors.at(++var));
                vectplayer.push_back(player);

            }

        }
    }

    nbplayers++;
}



/**
 * Method to get the place of a square
 * @brief Game::Placement
 * @param positon
 * @param pions
 */
bool Game::Placement(Position position,Color color){
    if(static_cast<int>(position.getRow())==getCursor()){
        if(board.getSquare(position).getType()==NEUTRAL){
            this->board.getGrille().at(position.getRow()).at(position.getColumn()).addPions(color);
            pionsPlaces++;

        }

        De();
        return true;
    }

        return false;
}
/**
 * Remove pion of player
 * @brief Game::RemovePion
 * @param position
 */
void Game::RemovePion(Position position){ //supression d'un pion a un endroit précis

    if(board.getSquare(position).getType()==SLEEP){ // ajout check lumière
        this->board.getGrille().at(position.getRow()).at(position.getColumn()).RemovePions();
        pionselimines--;
    }
}

/**
 * Chek who win the game
 * @brief Game::checkWin
 * @return
 */
bool Game::checkEnd(){
    return (pionsPlaces==15 && pionselimines==1);


}
/**
 * Find the last star up
 * @brief Game::findLastStar
 */
int Game::findLastStar(){
    for( size_t i =0; i<board.getRow(); i++){
        for (size_t y=0; y<board.getColumn(); y++){
            if(board.getSquare(Position(i,y)).getType()==SLEEP){
                return board.getGrille().at(i).at(y).getColor();
            }
        }
    }

    return -1;
}
/**
 * Switch the player
 * @brief Game::switchPlayers
 */
void Game::nextPlayer(){
    currentplayer++;
    currentplayer = currentplayer%nbplayers;
}
/**
 * Move the pions of the player in the grill
 * @brief Game::movePions
 * @param deValue
 */
void Game::movePions(int position){
    Placement(Position(cursor,position),vectplayer.at(currentplayer).getColor());
}

/**
 * getter of board
 * @brief Game::getBoard
 * @return
 */
Board Game::getBoard(){
    return this->board;
}
/**
 * set the square at sleep
 * @brief Game::setSleep
 */
bool Game::setSleep(){
    if(pionsPlaces==15){
        for(size_t i = 0; i<board.getRow();i++){
            for(size_t u =0; u<board.getColumn();u++){
                Position position = Position(i,u);
                board.getSquare(position).goSleep();
            }
        }
        gameState =2;
        sleep = true;
        return true;
    }
    return false;
}

/**
 * set the action for the button
 * @brief Game::setAction
 * @param position
 */
void Game::setAction(Position& position)
{
    if(board.getSquare(position).getType()==SLEEP){ // ajout check lumière
        this->board.getGrille().at(position.getRow()).at(position.getColumn()).setType(BUSY);
        this->board.getGrille().at(position.getRow()).at(position.getColumn()).RemovePions();

    }
}
void Game::playBots(int nb_connected){
    he2b::nvs::randomize();
    if(nb_connected<5){
        size_t bot = 5-nb_connected; // le type pas sur
        for(size_t y=0;y<3;y++){
            for(size_t u=1; u<=bot;u++){
                size_t random = 0;
                do{
                    random=he2b::nvs::random_value(0,4);
                }
                while (board.getSquare(Position(cursor,random)).getType()!=NEUTRAL);
                Placement(Position(cursor,random),(Color)(5-u));
            }
        }
    }
}

Color Game::colorOfPlayer(int id){
    for (size_t var = 0; var < vectplayer.size(); ++var) {
        if(id == vectplayer[var].getDbId()){
            return vectplayer[var].getColor();
        }
    }
    return Color();
}

