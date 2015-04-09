#include "gcom.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lamp::GCOM w;
    w.show();
    return a.exec();
}
