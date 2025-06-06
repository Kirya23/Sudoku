#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include "sudokugenerator.h"
#include <QCloseEvent>

namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void startNewGame();
    void setDifficulty(Difficulty diff);//сложность
    void updateCurrentState();
    void loadGame();
    void saveGame();
    void checkSolution();
    bool loadSavedGame();

private slots:
    void onCellEdited(int row, int col, const QString &text);

private:
    Ui::GameWindow *ui;

    Difficulty difficulty;

    int errorsCount = 0;
    void updateErrorsLabel();

    QLineEdit* cells[9][9]= {{nullptr}};
    int solution[9][9]; // правильное решение
    int puzzle[9][9];   // игровое поле
    int currentState[9][9];

    void setupGrid();
    void checkIfSolved();
    void fillGrid();
    void lockPrefilledCells();

protected:
    void closeEvent(QCloseEvent *event) override;


    // Для unit-тестов
    friend class TestGameWindow;
};

#endif // GAMEWINDOW_H
