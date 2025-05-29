#include "gamesave.h"
#include <QSettings>

void GameSave::saveGameState(int puzzle[9][9], int solution[9][9], QLineEdit* cells[9][9], Difficulty difficulty)
{
    QSettings settings("MyCompany", "SudokuApp");
    settings.beginGroup("SavedGame");

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            settings.setValue(QString("puzzle_%1_%2").arg(i).arg(j), puzzle[i][j]);
            settings.setValue(QString("solution_%1_%2").arg(i).arg(j), solution[i][j]);
            settings.setValue(QString("user_%1_%2").arg(i).arg(j), cells[i][j]->text());
        }

    settings.setValue("difficulty", static_cast<int>(difficulty));
    settings.endGroup();
}

bool GameSave::loadGameState(int puzzle[9][9], int solution[9][9], int currentState[9][9], Difficulty& difficulty)
{
    QSettings settings("MyCompany", "SudokuApp");
    if (!settings.childGroups().contains("SavedGame"))
        return false;

    settings.beginGroup("SavedGame");

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            puzzle[i][j] = settings.value(QString("puzzle_%1_%2").arg(i).arg(j), 0).toInt();
            solution[i][j] = settings.value(QString("solution_%1_%2").arg(i).arg(j), 0).toInt();
            currentState[i][j] = settings.value(QString("user_%1_%2").arg(i).arg(j), 0).toInt();
        }
    }

    difficulty = static_cast<Difficulty>(settings.value("difficulty", 0).toInt());

    settings.endGroup();
    return true;
}

void GameSave::clearSavedGame()
{
    QSettings settings("MyCompany", "SudokuApp");
    settings.remove("SavedGame");
}

bool GameSave::hasSavedGame()
{
    QSettings settings("MyCompany", "SudokuApp");
    return settings.childGroups().contains("SavedGame");
}
