#include "ppcaculator.h"
#include "ui_ppcaculator.h"
#include <QAction>
#include <QMenuBar>
#include <QTimer>
#include <QDialog>
#include <QMessageBox>

PPCaculator::PPCaculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PPCaculator),
    currentAction(NoAction),
    isEmpty(true)
{
    ui->setupUi(this);

    setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint);
    connect(ui->btnClear,SIGNAL(clicked(bool)),this,SLOT(clear()));
    connect(ui->btnNegativity,SIGNAL(clicked(bool)),this,SLOT(negationClicked()));
    connect(ui->btnPercentage,SIGNAL(clicked(bool)),this,SLOT(percentageClicked()));
    connect(ui->btnPoint,SIGNAL(clicked(bool)),this,SLOT(decimalPointClicked()));
    connect(ui->btnEqual,SIGNAL(clicked(bool)),this,SLOT(evaluationClicked()));

    connect(ui->btnAddition,SIGNAL(clicked(bool)),this,SLOT(actionChanged()));
    connect(ui->btnSubtraction,SIGNAL(clicked(bool)),this,SLOT(actionChanged()));
    connect(ui->btnMultiplication,SIGNAL(clicked(bool)),this,SLOT(actionChanged()));
    connect(ui->btnDivision,SIGNAL(clicked(bool)),this,SLOT(actionChanged()));

    connect(ui->btnNum0,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum1,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum2,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum3,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum4,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum5,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum6,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum7,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum8,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));
    connect(ui->btnNum9,SIGNAL(clicked(bool)),this,SLOT(inputNumber()));

    connect(ui->actionAbout_Qt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(aboutApp()));
}

PPCaculator::~PPCaculator()
{
    delete ui;
}

void PPCaculator::clear()
{
    if(ui->btnClear->text()=="AC")
    {
        currentAction = NoAction;
        currentNumber = "0";
        lastNumber = "0";
        isEmpty = true;
    }else if(ui->btnClear->text()=="C"){
        currentNumber = "0";
        isEmpty = true;
        ui->btnClear->setText("AC");
    }

     displayNumber();
}

void PPCaculator::actionChanged()
{
       QPushButton *currentButton = qobject_cast<QPushButton *>(this->sender());
       if(currentButton)
       {
           isEmpty = false;
           if(currentButton==ui->btnAddition)
           {
               currentAction = AdditionFlag;
               statusBar()->showMessage("输入了加号",3000);
           }else if(currentButton==ui->btnSubtraction)
           {
               currentAction = SustractionFlag;
               statusBar()->showMessage("输入了减号",3000);
           }else if(currentButton==ui->btnMultiplication)
           {
               currentAction = MultiplicationFlag;
               statusBar()->showMessage("输入了乘号",3000);
           }else if(currentButton==ui->btnDivision)
           {
               currentAction = DivisionFlag;
               statusBar()->showMessage("输入了除号",3000);
           }else{
               currentAction = NoAction;
           }
       }

}

void PPCaculator::inputNumber()
{
    QPushButton *button = qobject_cast<QPushButton *>(this->sender());

    if(button)
    {
        ui->btnClear->setText("C");
        if(!isEmpty)
        {
            lastNumber = currentNumber;
            currentNumber.clear();
            isEmpty = true;
        }
        if(currentNumber=="0")
        {
            currentNumber.clear();
        }

        if(button == ui->btnNum0)
        {
            currentNumber.append("0");
            statusBar()->showMessage("输入了0",3000);
        }
        if(button == ui->btnNum1)
        {
            currentNumber.append("1");
            statusBar()->showMessage("输入了1",3000);
        }
        if(button == ui->btnNum2)
        {
            currentNumber.append("2");
            statusBar()->showMessage("输入了2",3000);
        }
        if(button == ui->btnNum3)
        {
            currentNumber.append("3");
            statusBar()->showMessage("输入了3",3000);
        }
        if(button == ui->btnNum4)
        {
            currentNumber.append("4");
            statusBar()->showMessage("输入了4",3000);
        }
        if(button == ui->btnNum5)
        {
            currentNumber.append("5");
            statusBar()->showMessage("输入了5",3000);
        }if(button == ui->btnNum6)
        {
            currentNumber.append("6");
            statusBar()->showMessage("输入了6",3000);
        }if(button == ui->btnNum7)
        {
            currentNumber.append("7");
            statusBar()->showMessage("输入了7",3000);
        }if(button == ui->btnNum8)
        {
            currentNumber.append("8");
            statusBar()->showMessage("输入了8",3000);
        }if(button == ui->btnNum9)
        {
            currentNumber.append("9");
            statusBar()->showMessage("输入了9",3000);
        }

    }
    displayNumber();
}

void PPCaculator::displayNumber()
{
    ui->labShow->setText(currentNumber);
}

void PPCaculator::negationClicked()
{
    if(!isEmpty || (currentNumber.size() == 0))
    {
        isEmpty = true;
        currentNumber = "0";
    }
    else {
        if(currentNumber.at(0) == '-')
        {
            currentNumber.remove(0,1);
        }
        else {
            currentNumber.push_front("-");
        }
    }
    statusBar()->showMessage("符号变更",3000);
    displayNumber();
}

void PPCaculator::percentageClicked()
{
    if(!isEmpty)
    {
        isEmpty = true;
        currentNumber = "0";
    }
    else
    {
        double number = currentNumber.toDouble() / 100.0;
        currentNumber = QString::number(number);
    }
    statusBar()->showMessage("百分比",3000);
    displayNumber();
}
void PPCaculator::decimalPointClicked()
{
    if(!isEmpty)
    {
        currentNumber = "0.";
        isEmpty = true;
    }
    else if(currentNumber.indexOf(".") == -1)
    {
        currentNumber.push_back(".");
    }

    statusBar()->showMessage("输入了小数点",3000);
    displayNumber();
}

void PPCaculator::evaluationClicked()
{
    if(currentAction == NoAction)
    {
        statusBar()->showMessage("请选择一个运算",3000);
        return;
    }
    switch (currentAction) {
    case AdditionFlag:
    {
        currentNumber = QString::number(lastNumber.toDouble() + currentNumber.toDouble());
        break;
    }
    case SustractionFlag:
    {
        currentNumber = QString::number(lastNumber.toDouble() - currentNumber.toDouble());
        break;
    }
    case MultiplicationFlag:
    {
        currentNumber = QString::number(lastNumber.toDouble() * currentNumber.toDouble());
        break;
    }
    case DivisionFlag:
    {
        currentNumber = QString::number(lastNumber.toDouble() / currentNumber.toDouble());
        break;
    }
    default:
        break;
    }
    statusBar()->showMessage("计算完成",3000);
    currentAction = NoAction;
    displayNumber();
}

void PPCaculator::aboutApp()
{
    QMessageBox::about(this,"关于皮皮计算器","皮皮一直爱计算器，2017年11月9日");
}


