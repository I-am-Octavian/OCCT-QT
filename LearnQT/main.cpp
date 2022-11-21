#include "LearnQT.h"
#include <QtWidgets/QApplication>

/*
extern "C"
{
    _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LearnQT w;
    w.show();
    return a.exec();
}
