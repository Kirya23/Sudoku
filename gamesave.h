#ifndef GAMESAVE_H
#define GAMESAVE_H
#include <QString>
#include <QLineEdit>
#include "sudokugenerator.h"

enum Difficulty;

class GameSave
{
public:
    static void saveGameState(int puzzle[9][9], int solution[9][9], QLineEdit* cells[9][9],Difficulty difficulty);
    static bool loadGameState(int puzzle[9][9], int solution[9][9], int currentState[9][9], Difficulty& difficulty);
    static void clearSavedGame();
    static bool hasSavedGame();
};

#endif // GAMESAVE_H
