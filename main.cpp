#include "startwindow.h"
#include <QApplication>

double Sound::BGMVolume = 100;
double Sound::effectVolume = 100;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow w;
    w.show();

    return a.exec();
}
