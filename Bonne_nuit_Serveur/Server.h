#ifndef SERVER_H
#define SERVER_H
#include "QTcpServer"
#include"Game_handler.h"
#include"QDebug"
#include "iostream"
#define PORT 2021
class Server : public QTcpServer
{
    Q_OBJECT
     std::vector<Game_handler> game_handlers;
public:
    /**
       * @brief server
       * @param parent
       */
    explicit  Server(QObject*parent=0);
    /**
   * @brief start_server launch the server
   *  the server need a port and QhostAdress
   *  if the server start we have a message server connected
   */
    void start_server();
private:
    /**
   * @brief initialise_game intialise the game , create a thred for player.
   */
    void initialise_game(qintptr& handle);
protected:
    /**
   * @brief incomingConnection
   * @param handle
   */
    void  incomingConnection(qintptr handle) override;


};
#endif // SERVER_H
