#include "Controller.h"
#include "QHostAddress"
#include <iostream>
Controller::Controller(QObject *parent): QObject(parent)
{
    socket = new QTcpSocket();
    this->packet = good_night_encap();
    this->whp = new welcome_home_page(nullptr,this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()),Qt::DirectConnection);
}
void Controller::start(){
    this->whp->show_welcome_gui();
    socket->connectToHost("localhost",2021);
    if(socket->isOpen()) write_data(READY_TO_PLAY);

}

void Controller::user_click(Position button_position){
    this->button_click_position = button_position;
    write_data(Action_Send::CLICK);
}
void Controller::read(){
    qDebug() << "Reading Annonce.";
    buffer.clear();
    buffer=QByteArray(socket->readAll());
    qDebug() << buffer;
    this->packet.clear();
    this->packet.set_data_encap(buffer);
    QByteArray dt=QByteArray(this->packet.get_data_encapsulated());
    Action_Send type= json_interpreter::get_type(dt);
    qDebug()<<type;
    apply_server_action(dt,type);
}

void Controller::apply_server_action(QByteArray data,Action_Send action)
{
    switch (action) {
    case SEND_DATA:{
        this->game = json_interpreter::unpacked_game_info(data);
        this->current_p_id = this->game.current_player_id;
        qDebug()<<"player id "+QString::number(this->player_id);
        if(!is_launched)
        {
            this->p_c = this->game.player_c;
            this->player_id = this->game.player_i;
            this->whp->close_windows();
            this->gui = new good_night_gui(nullptr,this);
            is_launched = true;
            this->gui->init_board(this->game);
            this->gui->show();
        }
        else this->gui->update_gui(this->game);
    }
        break;
    case CONNECTION_ESTABLISHED:
        qDebug()<<"co";
        this->whp->unlock_button();
        break;
    case NULL_ACTION:
        qDebug()<<"this is null action";
        break;
    case INVALID_CLICK:
        this->gui->inform_invalid_click();
        break;
    case GAME_OVER:
    {
        int get_color = json_interpreter::colorWinner(data);
        QString name = json_interpreter::get_color(static_cast<Color>(get_color));
        this->gui->show_winner(name);
    }
        break;
    default:
        qDebug()<<"this is default";

        break;
    }
}
void Controller::player_click_start()
{
    write_data(CLICK_START);
}
void Controller::send_position(Position p,bool is_night)
{
    this->button_click_position = p;
    if(is_night)write_data(REMOVE);
    else write_data(CLICK);
}
void Controller::write_data(Action_Send action){
    this->packet.clear();
    QByteArray data_array;
    switch (action) {
    case CLICK:{
        data_array = json_generator::place_pion(this->button_click_position,static_cast<int>(p_c)); //send color instead of id

        break;
    }
    case READY_TO_PLAY:
        data_array = json_generator::ready_to_play();
        break;
    case CLICK_START:
        data_array = json_generator::click_start();
        break;
    case REMOVE:
        data_array = json_generator::remove_pion(this->button_click_position);
    default:
        break;
    }
    this->packet.set_data_encap(data_array);
    socket->write(this->packet.get_data_encapsulated());
}
