#include "bonne_nuit.h"
#include "Controller.h"
Bonne_Nuit::Bonne_Nuit(Controller *controller, QWidget *parent): QWidget(parent)
{

}
Bonne_Nuit::~Bonne_Nuit()
{
   // delete ui;
}

void Bonne_Nuit::set_controller(Controller* controller){
    this->controller= controller;
}
void Bonne_Nuit::on_Btn_clicked(){
    controller->button(); //les boutons sont tous les mêmes ( les cases du jeu)
}
