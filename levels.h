#ifndef LEVELS_H
#define LEVELS_H

#include <QDialog>
#include "sudokugenerator.h"
namespace Ui {
class Levels;
}

class Levels : public QDialog
{
    Q_OBJECT

public:
    explicit Levels(QWidget *parent = nullptr);
    ~Levels();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Levels *ui;
};

#endif // LEVELS_H
