#include "ppcaculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PPCaculator w;
    w.show();

    return a.exec();
}
