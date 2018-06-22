#include "program.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Program prog;
    prog.show();

    return a.exec();
}
