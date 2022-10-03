#include "good_night_gui.h"
#include "ui_good_night_gui.h"
#include "Controller.h"
#include "gn-encap/json_interpreter.h"
good_night_gui::good_night_gui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::good_night_gui)
{
    ui->setupUi(this);

}
good_night_gui::good_night_gui(QWidget*parent,Controller* controller_):QWidget(parent),ui(new Ui::good_night_gui),controller(controller_)
{
    ui->setupUi(this);
    this->board_layout = new QGridLayout();
}

good_night_gui::~good_night_gui()
{
    delete ui;
}

void good_night_gui::init_board(game_info info)
{
    int row = info.row;
    int column = info.col;
    int cursor = info.cursor;
    std::array<square_info,45> data= info.data;
    int index =0;
    bool cursor_set=false;
    for (int var = 0; var < row; ++var) {
        for (int var_col = 0; var_col < column; ++var_col) {

            Position data_pos = data.at(index).position;
            Position current_pos = Position(var,var_col);
            Type type = data.at(index).type;
            Color color = data.at(index).color;
            button_game *game_button= new button_game(nullptr,current_pos);
            if(current_pos==data_pos)
            {
                if(!info.sleeping)
                {
                    if(type!=NEUTRAL)
                    {
                        switch (color) {
                        case BLACK:
                            game_button->setIcon(QIcon(":/ressources/img/star_black.png"));
                            break;
                        case BLUE:
                            game_button->setIcon(QIcon(":/ressources/img/star_blue.png"));
                            break;
                        case GREEN:
                            game_button->setIcon(QIcon(":/ressources/img/star_green.png"));
                            break;
                        case PURPLE:
                            game_button->setIcon(QIcon(":/ressources/img/star_purple.png"));
                            break;
                        case RED:
                            game_button->setIcon(QIcon(":/ressources/img/star_red.png"));
                            break;
                        default:
                            break;
                        }
                    }else
                    {

                        game_button->setIcon(QIcon(":/ressources/img/empty.png"));
                    }
                    if(var==cursor && !cursor_set && (var_col<column)){
                        cursor_b = new QLabel();
                        cursor_b->setPixmap(QPixmap(":/ressources/img/drop.png"));
                        cursor_set=true;
                        ui->gridLayout->addWidget(cursor_b,cursor,column);
                    }

                }else
                {
                    is_night=true;

                    if(type!=NEUTRAL)
                    {
                        if(type==SLEEP)
                            game_button->setIcon(QIcon(":/ressources/img/star_night.png"));

                    }else
                    {
                        game_button->setIcon(QIcon(":/ressources/img/night.png"));
                    }

                }

            }
            QObject::connect(game_button,SIGNAL(sendValue(Position&)),this,SLOT(set_button_position(Position&)));

            this->buttons.push_back(game_button);
            ui->gridLayout->addWidget(game_button,var,var_col);
            ++index;
        }
    }
    ui->player_that_play->setText(json_interpreter::get_color(info.current_c));
    ui->player_that_play_2->setText(json_interpreter::get_color(this->controller->get_c()));
    ui->gouteEau->setText(QString::number(info.cursor));


}

void good_night_gui::set_button_position(Position& position)
{
    if(this->controller->get_current_player_id()==this->controller->get_player_id())
        this->controller->send_position(position,is_night);
    else  ui->Player_Win->setText("You are not the current player stop fooling little idiot");
}

void good_night_gui::update_gui(game_info data)
{

    delete_element();
    ui->gridLayout = new QGridLayout();
    this->buttons.clear();
    init_board(data);
    ui->Board_Game->setLayout(ui->gridLayout);
    ui->Player_Win->setText("PLAYER WIN");
}

void good_night_gui::delete_element()
{
    for (auto child:ui->Board_Game->children() )
        delete child;
}

void good_night_gui::inform_invalid_click()
{
    ui->Player_Win->setText("Your choice was not correct retry");
}
void good_night_gui::show_winner(QString winner)
{
    for(button_game* b:buttons) b->setDisabled(true);
    ui->Player_Win->setText("The winner is: "+winner);
}
