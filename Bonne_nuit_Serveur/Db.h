#ifndef DB_H
#define DB_H
#define q2c(string) string.toStdString()
#include <QtSql>
struct user_info {
    int id;
    int nbWin;
};

class Db
{
    QSqlDatabase db;
    QSqlQuery query;
    bool is_open;
public:
    /**
     * @brief Default constructor of my DataBase Db
     */
    Db();

    /**
     * @brief open_db open the daba
     */
    void open_db();

    /**
     * @brief db_is_open check is the db is open
     * @return bool true if the db_is_open
     */
    bool db_is_open();
    /**
     * @brief checkUser check if the user is in the db , is the user
     * is not in the db , we create inforamtion of user in db
     */
    void checkUser(int id_player, user_info &info); //int car mon joueur a juste un numéro
    /**
     * @brief read_Db read information in the db
     */
    void read_Db(user_info&);
    /**
     * @brief clear_query clear the query
     */
    void clear_query();
    /**
    * @brief updates and retrieves the part number in the database
    * @return integer of gameID
    */
    int insert_get_game_id();
    /**
     * @brief update Win of the player
     */
    void updateWin(int id_player);

};

#endif // DB_H
