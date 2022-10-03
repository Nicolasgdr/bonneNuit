#ifndef Square
#include<string>
#include"Type.h"
#include"Color.h"
#define LITTLEPAWN_H
class Square
{
private:
    std::string Text;
    Type type;
public:
    Square(){
        this->type=NEUTRAL;
    }
    Square(Type type)
    {
        this->type = type;
    }

    bool isPresent();
    Type getType(){
        return this->type;
    }
    void setType(Type type){
        this->type = type;
    }

    inline Color getColor(){
        return color;
    }
    void addPions(Color color);
    void RemovePions();
    void goSleep();
private :
    Color color;

};
#endif // LITTLEPAWN_H
