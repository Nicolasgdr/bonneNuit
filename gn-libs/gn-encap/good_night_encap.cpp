#include "good_night_encap.h"

void good_night_encap::pack_data(){
    QDataStream in(&this->data_encapsulated,QIODevice::ReadWrite);
    in<<data_;

}
void good_night_encap::unpack_data(){
    QDataStream in(&this->data_encapsulated,QIODevice::ReadWrite);
    in<<data_;

}
void good_night_encap::set_data_encap(QByteArray array){
this->data_encapsulated=std::move(array);
}
void good_night_encap::set_data(QString data){
     this->data_=std::move(data);
}


void good_night_encap::clear(){
    data_.clear();
    data_encapsulated.clear();
}
