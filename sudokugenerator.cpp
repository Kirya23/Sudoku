#include "sudokugenerator.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>

static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

static bool canPlace(int board[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[startRow + i][startCol + j] == num)
                return false;

    return true;
}

/*bool fillBoard(int board[9][9], int row = 0, int col = 0) {
    if (row == 9) return true;
    if (col == 9) return fillBoard(board, row + 1, 0);
    if (board[row][col] != 0) return fillBoard(board, row, col + 1);

    std::vector<int> nums = {1,2,3,4,5,6,7,8,9};
    std::shuffle(nums.begin(), nums.end(), rng);

    for (int num : nums) {
        if (canPlace(board, row, col, num)) {
            board[row][col] = num;
            if (fillBoard(board, row, col + 1)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}*/
static bool fillBoard(int board[9][9]) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                std::vector<int> nums = {1,2,3,4,5,6,7,8,9};
                std::shuffle(nums.begin(), nums.end(), rng);

                for (int num : nums) {
                    if (canPlace(board, row, col, num)) {
                        board[row][col] = num;
                        if (fillBoard(board))
                            return true;
                        board[row][col] = 0;
                    }
                }

                return false; // не удалось поставить ни одно число
            }
        }
    }

    return true; // доска полностью заполнена
}

void SudokuGenerator::generate(int puzzle[9][9], int solution[9][9], Difficulty difficulty)
{
    // Шаг 1: очистка
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            solution[i][j] = 0;

    // Шаг 2: сгенерировать полное решение
    fillBoard(solution);

    // Шаг 3: скопировать как стартовую загадку
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            puzzle[i][j] = solution[i][j];

    // Шаг 4: убрать некоторые цифры по уровню сложности
    int removeCount = 40;

    if (difficulty == EASY) removeCount = 35;
    else if (difficulty == MEDIUM) removeCount = 45;
    else if (difficulty == HARD) removeCount = 55;

    while (removeCount > 0) {
        int r = rng() % 9;
        int c = rng() % 9;

        if (puzzle[r][c] != 0) {
            puzzle[r][c] = 0;
            --removeCount;
        }
    }
}
