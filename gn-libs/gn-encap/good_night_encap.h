#ifndef GOOD_NIGHT_ENCAP_H
#define GOOD_NIGHT_ENCAP_H
#include "QString"
#include "QByteArray"
#include "QDataStream"
#include "QIODevice"

class good_night_encap
{   
    QString data_;
    QByteArray data_encapsulated;


public:
    good_night_encap()=default;
    void pack_data();
    void unpack_data();
    void set_data_encap(QByteArray);
    void set_data(QString data);
   inline QByteArray get_data_encapsulated(){return data_encapsulated;}
   inline QString get_data(){return data_;}
    void clear();
};

#endif // GOOD_NIGHT_ENCAP_H
