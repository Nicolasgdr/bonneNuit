#ifndef THREAD_PLAYERS_H
#define THREAD_PLAYERS_H
#include"QThread"
#include"QTcpSocket"
#include "Model/Game.h"
#include"gn-encap/good_night_encap.h"
class Game_handler;
class Thread_players :  public QObject
{
    Q_OBJECT
    QTcpSocket *player_socket_;
    qintptr socket_descriptor_;
    Game_handler* handler;
    good_night_encap packet;
    QByteArray buffer;
   Color player_color;
   int db_id;
    /**
 * @brief handle_received processes the messages
 * @param type
 */
    void handle_received(QByteArray,Action_Send type);
public:
    /**
     * @brief Thread_players::set_handler setter of game handler
     */
    void set_handler(Game_handler*);
    /**
    * @brief player_thread generate information in json
    * @param socket
    */
    explicit Thread_players(QTcpSocket* socket);
    inline void notify(QByteArray data){emit send_data(data);}
    /**
    * @brief player_thread  generate information in json
    * @param socket_descriptor
    * @param parent
    */
    explicit Thread_players(qintptr socket_descriptor, QObject* parent=0);
    /**
     * @brief operator ==
     * @param rhs
     * @return
     */
    inline bool operator==(Thread_players&rhs){return rhs.socket_descriptor_==this->socket_descriptor_;}
    void  run();
private slots:
    inline void write_data(QByteArray data){this->player_socket_->write(data);}
    void read_in();
    /**
  * @brief log_out clear socket
  */
    void log_out();
signals:
    void error(QTcpSocket::SocketError error);
    void send_data(QByteArray);

};

#endif // THREAD_PLAYERS_H
