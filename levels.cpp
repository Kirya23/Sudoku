#include "levels.h"
#include "gamewindow.h"
#include "sudokugenerator.h"
#include "ui_levels.h"

Levels::Levels(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Levels)
{
    ui->setupUi(this);
}

Levels::~Levels()
{
    delete ui;
}

void Levels::on_pushButton_clicked()
{


    GameWindow* game = new GameWindow(this);
    game->setDifficulty(EASY);
    game->startNewGame();
    game->exec();
}


void Levels::on_pushButton_2_clicked()
{

    GameWindow* game = new GameWindow(this);
    game->setDifficulty(MEDIUM);
    game->startNewGame();
    game->exec();
}


void Levels::on_pushButton_3_clicked()
{

    GameWindow* game = new GameWindow(this);
    game->setDifficulty(HARD);
    game->startNewGame();
    game->exec();
}

