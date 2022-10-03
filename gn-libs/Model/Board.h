#ifndef BOARD_H
#define BOARD_H
#include<vector>
#include"Square.h"
#include"Position.hpp"
class Board
{
public :

    /**
     * @brief Board --> initialize the board
     */
    Board()
    {
       grille = std::vector<std::vector<Square>>(9, std::vector<Square>(5));
    }
    /**
     * @brief getRow
     * @return row
     */
    inline size_t getRow(){
       return this->grille.size();
    }
    /**
     * @brief getColumn
     * @return column
     */
    inline size_t getColumn(){
        return this->grille.at(0).size();
    }
    /**
     * @brief isInside --> check if the square are in the grille
     * @param position
     * @return
     */
    bool isInside(Position position){
        return grille.at(position.getRow()).at(position.getColumn()).isPresent();
    }
    /**
     * @brief getGrille --> getter for the grille
     * @return
     */
    std::vector<std::vector<Square>> &getGrille(){
        return grille;
    }
    /**
     * @brief getSquare --> getter for the square
     * @param position
     * @return
     */
    Square & getSquare(Position position){
        return grille.at(position.getRow()).at(position.getColumn());
    }
private:
   std::vector<std::vector<Square>> grille;

};
#endif // BOARD_H
