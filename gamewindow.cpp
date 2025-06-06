#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "sudokugenerator.h"
#include <QMessageBox>
#include "gamesave.h"

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    errorsCount = 0;
    updateErrorsLabel();
    setupGrid();


}

GameWindow::~GameWindow()
{
    delete ui;
}



void GameWindow::onCellEdited(int row, int col, const QString &text)
{
    if (puzzle[row][col] != 0) return; // не трогаем предзаполненные клетки

    QLineEdit* cell = cells[row][col];

    if (text.isEmpty()) {
        cell->setStyleSheet("");
    }
    else if (text == QString::number(solution[row][col])) {
        cell->setStyleSheet("");
    }
    else {

        if (cell->styleSheet() != "background-color: pink;") {
            errorsCount++;
            updateErrorsLabel();

            if (errorsCount >= 4) {
                QMessageBox::critical(this, "УВы", "Вы не решили судоку(");
                GameSave::clearSavedGame(); // удалить сохранение
                this->reject(); // закрыть окно с кодом Rejected
                return;
            }
        }
        cell->setStyleSheet("background-color: pink;");
    }
    checkIfSolved();
}

void GameWindow::setupGrid()
{
    QFont font;
    font.setPointSize(16);

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QLineEdit* cell = new QLineEdit(this);
            cell->setMaxLength(1);
            cell->setFixedSize(40, 40);
            cell->setAlignment(Qt::AlignCenter);
            cell->setFont(font);

            // Сохраняем в массив
            cells[row][col] = cell;

            QString style = "border: 1px solid gray;";
            if (row % 3 == 0) style += " border-top: 2px solid black;";
            if (col % 3 == 0) style += " border-left: 2px solid black;";
            if (row == 8)     style += " border-bottom: 2px solid black;";
            if (col == 8)     style += " border-right: 2px solid black;";
            cell->setStyleSheet(style);

            // Добавляем в сетку
            ui->mainGridLayout->addWidget(cell, row, col);

            // Подключаем изменение текста
            connect(cell, &QLineEdit::textChanged, this, [=](const QString &text) {
                onCellEdited(row, col, text);
            });
        }
    }
}




void GameWindow::checkIfSolved()
{
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            if (cells[i][j]->text().isEmpty()) return;
            if (cells[i][j]->text().toInt() != solution[i][j]) return;
        }

    QMessageBox::information(this, "Поздравляем!", "Вы решили судоку!");
    GameSave::clearSavedGame();
    this->accept();  // Закрывает диалог с кодом Accepted
}


void GameWindow::startNewGame()
{
    GameSave::clearSavedGame();
    SudokuGenerator::generate(puzzle, solution, difficulty); // 👈 с учетом сложности
    fillGrid();
    lockPrefilledCells();

    errorsCount = 0;
    updateErrorsLabel();
}
bool GameWindow::loadSavedGame()
{
    if (!GameSave::loadGameState(puzzle, solution, currentState, difficulty))
    return false;

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            if (currentState[i][j] != 0)
                cells[i][j]->setText(QString::number(currentState[i][j]));
            else
                cells[i][j]->clear();
        }

    lockPrefilledCells();
    errorsCount = 0;
    updateErrorsLabel();
    return true;
}

void GameWindow::fillGrid()
{
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (puzzle[i][j] != 0)
                cells[i][j]->setText(QString::number(puzzle[i][j]));
            else
                cells[i][j]->clear();
}
void GameWindow::lockPrefilledCells()
{
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (puzzle[i][j] != 0)
                cells[i][j]->setReadOnly(true);
            else
                cells[i][j]->setReadOnly(false);
}

void GameWindow::setDifficulty(Difficulty diff)
{
    this->difficulty = diff;
}

void GameWindow::closeEvent(QCloseEvent *event)
{
    updateCurrentState();
    GameSave::saveGameState(puzzle, solution, cells, difficulty);
    QDialog::closeEvent(event);
}

void GameWindow::updateCurrentState()
{
    for (int i = 0; i < 9; ++i)
        for (int j = 1; j < 9; ++j) {
            QString text = cells[i][j]->text();
            if (text.isEmpty())
                currentState[i][j] = 0;
            else
                currentState[i][j] = text.toInt();
        }
}
void GameWindow::updateErrorsLabel()
{
    ui->label->setText(QString("Ошибки: %1 / 4").arg(errorsCount));
}

