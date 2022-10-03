#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTcpSocket>
#include <QObject>

#include "Model/Game.h" //librairie
#include "gn-encap/json_interpreter.h"
#include "gn-encap/good_night_encap.h"
#include "gn-encap/json_generator.h"
#include "good_night_gui.h"
#include "welcome_home_page.h"
class good_night_gui;
class Controller: public QObject
{
    Q_OBJECT
public:
    inline int get_player_id(){return this->player_id;}
    inline Color get_c(){return this->p_c;}
    /**
     * constructor of the controller
     * @brief Controller
     * @param parent
     */
    Controller(QObject *parent = nullptr);
    void player_click_start();
    /**
     * launch the connexion between the serveur and the client
     * @brief conection_serv
     * @param name
     */
    void conection_serv(); //la j'ai pas besoin d'avoir un nom
    /**
     * launch the view of the connection for the player
     * @brief start
     */
    void start();
    /**
     * write the type of message CLICK in the json
     * @brief button
     */
    void user_click(Position=Position());
    /**
     * @brief send_position
     */
    void send_position(Position,bool);

public slots:
    /**
     * read the incomming information from the serveur
     * @brief read
     */
    void read();
    /**
     * write the information/type in the json for the serveur
     * @brief write_data
     * @param action
     */
    void write_data(Action_Send action);
    /**
     * @brief get_current_player_id
     * @return
     */
    inline int get_current_player_id(){return current_p_id;}

private:


    QTcpSocket *socket;
    game_info game;
    QByteArray buffer;
    good_night_encap packet;
    size_t game_user_id;
    welcome_home_page *whp;
    good_night_gui * gui;
    Position button_click_position;
    int player_id = 0;
    Color p_c;
    bool is_launched = false;
    int current_p_id;
    void apply_server_action(QByteArray,Action_Send);
};

#endif // CONTROLLER_H
