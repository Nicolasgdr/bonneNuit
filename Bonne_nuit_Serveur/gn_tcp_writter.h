#ifndef GN_TCP_WRITTER_H
#define GN_TCP_WRITTER_H

#include <QObject>

class gn_tcp_writter : public QObject
{
    Q_OBJECT
public:
    gn_tcp_writter(QObject*parent=0):QObject(parent)
    {

    }
signals:
    void write(QByteArray);
};

#endif // GN_TCP_WRITTER_H
