#include "charactersheet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CharacterSheet w;
    w.show();
    return a.exec();
}
