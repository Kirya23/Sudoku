#include "mainwindow.h"
#include "gamewindow.h"
#include "levels.h"
#include "help.h"
#include "settings.h"
#include "./ui_mainwindow.h"
#include "gamesave.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    if (!GameSave::hasSavedGame()) {
        QMessageBox::warning(this, "Ошибка", "Нет сохранённой игры.");
        return;
    }

    GameWindow *game = new GameWindow();
    if (game->loadSavedGame()) {
        game->exec();
    } else {
        delete game;
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить игру.");
    }
}
void MainWindow::on_pushButton_3_clicked()
{
    Levels window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    qApp->quit();
}


void MainWindow::on_pushButton_5_clicked()
{
    help window;
    window.setModal(true);
    window.exec();
}


void MainWindow::on_pushButton_4_clicked()
{
    settings window;
    window.setModal(true);
    window.exec();
}

