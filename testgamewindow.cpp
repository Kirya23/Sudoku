#include <QtTest>
#include <QSignalSpy>
#include "gamewindow.h"
#include "gamesave.h"

class TestGameWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        // Очищаем возможные предыдущие сохранения
        GameSave::clearSavedGame();
    }

    void testCellEditing()
    {
        GameWindow game;
        game.show();

        // Симулируем новую игру
        game.setDifficulty(Difficulty::EASY);
        game.startNewGame();

        // Находим первую редактируемую ячейку
        bool foundEditable = false;
        QLineEdit* editableCell = nullptr;

        for (int i = 0; i < 9 && !foundEditable; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (!game.cells[i][j]->isReadOnly()) {
                    editableCell = game.cells[i][j];
                    foundEditable = true;
                    break;
                }
            }
        }

        QVERIFY2(editableCell != nullptr, "Не найдена редактируемая ячейка");

        // Тест 1: Проверка правильного ввода
        int solutionValue = game.solution[editableCell->property("row").toInt()]
                                         [editableCell->property("col").toInt()];
        editableCell->setText(QString::number(solutionValue));
        QCOMPARE(editableCell->styleSheet(), QString("background-color: pink;"));

        // Тест 2: Проверка неправильного ввода
        int wrongValue = (solutionValue % 9) + 1; // Гарантированно другое число
        editableCell->setText(QString::number(wrongValue));
        QCOMPARE(editableCell->styleSheet(), QString("background-color: pink;"));
    }

    void testPrefilledCellsLocking()
    {
        GameWindow game;
        game.setDifficulty(Difficulty::MEDIUM);
        game.startNewGame();

        int lockedCount = 0;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (game.cells[i][j]->isReadOnly()) {
                    lockedCount++;
                    // Проверяем, что текст соответствует puzzle
                    QCOMPARE(game.cells[i][j]->text().toInt(), game.puzzle[i][j]);
                }
            }
        }

        // Для MEDIUM сложности должно быть примерно 40-50 заполненных клеток
        QVERIFY2(lockedCount > 30 && lockedCount < 60,
                 "Некорректное количество заблокированных ячеек");
    }

    void testGameSolutionCheck()
    {
        GameWindow game;
        game.setDifficulty(Difficulty::HARD);
        game.startNewGame();

        // Заполняем правильное решение
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (!game.cells[i][j]->isReadOnly()) {
                    game.cells[i][j]->setText(QString::number(game.solution[i][j]));
                }
            }
        }

        // Должно появиться сообщение о победе
        QSignalSpy spy(&game, &GameWindow::accepted);
        game.checkIfSolved();
        QCOMPARE(spy.count(), 1);
    }


    void cleanupTestCase()
    {
        // Очищаем сохранения после тестов
        GameSave::clearSavedGame();
    }
};

QTEST_MAIN(TestGameWindow)
#include "testgamewindow.moc"
