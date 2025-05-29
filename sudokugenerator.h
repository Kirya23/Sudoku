#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H
enum Difficulty { EASY , MEDIUM, HARD };
class SudokuGenerator
{
public:

    static void generate(int puzzle[9][9], int solution[9][9], Difficulty difficulty);

};

#endif // SUDOKUGENERATOR_H
