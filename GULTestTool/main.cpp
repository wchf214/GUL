#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowFlags(w.windowFlags()
                    & ~Qt::WindowMinMaxButtonsHint
                    | Qt::WindowMinimizeButtonHint);
    const int fixedWidth = 513;
    const int fixedHeight = 493;
    w.setFixedSize(fixedWidth, fixedHeight);
    w.show();
    return a.exec();
}
