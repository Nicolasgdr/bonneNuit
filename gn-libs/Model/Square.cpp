#include"Square.h"
/**
 * @brief Check if the square is busy or not
 * @brief Square::isPresent
 * @return
 */
bool Square::isPresent() {
    return this->type == Type::BUSY;
}
/**
 * @brief ADD pions on the vector of the player
 * @brief Square::addPions
 * @param pions
 */
void Square::addPions(Color color){
    this->color = color;
    this->type = Type::BUSY;
}
/**
 * @brief Remove the pions
 * @brief Square::RemovePions
 */
void Square::RemovePions(){ // plus besoin de passer le pion en paramètre puisque on va crée avec un par default et sa pali au problème du nullptr
    this->type= NEUTRAL;
}
void Square::goSleep(){
    if(type==BUSY){
        type=SLEEP;
    }
}

