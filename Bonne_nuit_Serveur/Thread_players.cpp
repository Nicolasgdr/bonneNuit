#include"Thread_players.h"
#include"Game_handler.h"
#include "gn-encap/json_interpreter.h"
#include "gn-encap/json_generator.h"
Thread_players::Thread_players(QTcpSocket* socket): player_socket_(socket){

    this->packet = good_night_encap();
}
void  Thread_players::run(){
    qDebug()<<"-----------------------------------\n"<< "Thread begin"<<"---------------------------------------\n";
    this->player_socket_= new QTcpSocket();
    if(!this->player_socket_->setSocketDescriptor(this->socket_descriptor_))
    {
        qDebug()<<"Error";
        emit error(player_socket_->error());
        return;
    }
    qDebug()<<"---------------------------\n"<<"Client connected...\n"<<"connecting slot...\n"<<"-------------------------------------\n";
    connect(player_socket_,SIGNAL(readyRead()),this,SLOT(read_in()),Qt::DirectConnection);
    connect(player_socket_,SIGNAL(disconnected()),this,SLOT(log_out()));
    connect(this,SIGNAL(send_data(QByteArray)),this,SLOT(write_data(QByteArray)),Qt::AutoConnection);
    qDebug()<<"---------------------------\n"<<"Client connected...\n"<<"Slot connected...\n"<<"-------------------------------------\n";

}

Thread_players::Thread_players(qintptr socket_descriptor,QObject*parent): QObject(parent),socket_descriptor_(socket_descriptor)
{

}

void Thread_players::read_in(){
    qDebug()<<"---------------------------\n"<<"Client connected...\n"<<"Data received...\n";
    buffer=QByteArray(player_socket_->readAll());
    qDebug()<<buffer;
    qDebug()<<"---> Data store in buffer...\n";
    this->packet.set_data_encap(buffer);
    qDebug()<<"---> Daata set into packet...\n";
    qDebug()<<this->packet.get_data_encapsulated();
    qDebug()<<"---> Data unpacked...\n";
    auto data = this->packet.get_data_encapsulated();
    qDebug()<<data;
    qDebug()<<"---> Data unpacked received...\n";
    Action_Send type =json_interpreter::get_type(data);
    qDebug()<<"---> Data action received...\n";
    handle_received(data,type);
    qDebug()<<"handle over";

}


void Thread_players::log_out(){
    this->handler->disconnecte_player(this);
    player_socket_->deleteLater();
    exit(0);
}


void Thread_players::handle_received(QByteArray data,Action_Send type){
    QByteArray data_byte;
        qDebug()<<data;
        bool everybody=false;
        switch (type) {
        case READY_TO_PLAY:{
            data_byte=json_generator::user_launch_game();
            everybody =false;
            qDebug()<<"--->  server ready...\n";
            break;
        }
        case CLICK_START:{
            qDebug()<<"click start";
            this->handler->create_game();
            player_color = this->handler->get_game().get_last_player().getColor();
            this->db_id = this->handler->get_game().get_last_player().getDbId();
            qDebug()<<this->db_id;
            qDebug()<<"--->  game created...\n";
            qDebug()<<this->handler->get_game().getCurrentPlayer();
            data_byte=  json_generator::send_game_info(handler->get_game(),this->player_color,this->db_id);
            if(this->handler->is_running())
            everybody=false;
            else everybody=true;
            break;
        }
        case CLICK:{
            qDebug()<<"click received...\n";
            if(this->handler->get_game().getpionsPlaces()==15){
                this->handler->get_game().setSleep();
                data_byte = data_byte= json_generator::send_game_info(handler->get_game(),this->player_color,this->db_id);
            }else{
                placement p = json_interpreter::unpacked_placement(data);
                bool valid=this->handler->get_game().Placement(p.position,p.player_color);
                this->handler->get_game().nextPlayer();
                qDebug()<<"Next Player: "+QString::number(this->handler->get_game().getCurrentPlayer());
                if(valid) data_byte= json_generator::send_game_info(handler->get_game(),this->player_color,this->db_id);
                else data_byte = json_generator::invalid_click();
                qDebug()<<this->handler->get_game().getpionsPlaces();

            }


            everybody=true;
            break;
        }
        case REMOVE:{
            Position place = json_interpreter::unpacked_remove(data);
            if(this->handler->get_game().checkEnd()){
                int color= this->handler->get_game().findLastStar();
                data_byte= json_generator::colorWinner(color);
                for(auto player: this->handler->get_game().getPlayers())
                {
                    if(player.getColor()== static_cast<Color>(color))
                        this->handler->call_for_update(player.getDbId());
                    break;
                }

            }else{
                this->handler->get_game().RemovePion(place);
                this->handler->get_game().nextPlayer();
                data_byte= json_generator::send_game_info(handler->get_game(),this->player_color,this->db_id);
                everybody=true;
            }

            break;
        }
        default:
            break;
        }
        qDebug()<<"I notify every body\n";
       // emit send_data(data_byte);
      this->handler->notify(data_byte,everybody,player_socket_);
        qDebug()<<"I notify every body done\n";

    }

void Thread_players::set_handler(Game_handler *h)
{
    this->handler=h;
}
