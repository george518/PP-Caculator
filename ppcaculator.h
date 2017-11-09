#ifndef PPCACULATOR_H
#define PPCACULATOR_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class PPCaculator;
}

enum ActionFlag{
    NoAction,
    AdditionFlag,
    SustractionFlag,
    MultiplicationFlag,
    DivisionFlag
};

class PPCaculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit PPCaculator(QWidget *parent = 0);
    ~PPCaculator();

private:
    Ui::PPCaculator *ui;

    ActionFlag currentAction;
    QString lastNumber;
    QString currentNumber;
    bool isEmpty;
    QLabel *bar1;
    QLabel *bar2;
public slots:
    void clear();
    void actionChanged();
    void inputNumber();
    void displayNumber();
    void negationClicked();
    void percentageClicked();
    void decimalPointClicked();
    void evaluationClicked();

    void aboutApp();

};

#endif // PPCACULATOR_H
