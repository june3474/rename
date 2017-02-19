#include "rename.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rename w;
    w.show();

    return a.exec();
}
