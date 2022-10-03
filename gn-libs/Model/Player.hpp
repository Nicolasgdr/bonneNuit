#ifndef PLAYER_HPP
#include"Color.h"
#include<vector>
#define PLAYER_HPP
class Player {
public:


    Player(int dbID,Color color){
        this->dbId=dbID;
        this->color=color;
    }

    int getdbId(){
        return  this->dbId;
    }
    int getDbId(){
        return  this->dbId;
    }
    void setdbId(int number){
        this->dbId=number;
    }
    Color getColor(){
        return this->color;
    }
private:
    Color color;
    int dbId;
};

#endif // PLAYER_HPP
