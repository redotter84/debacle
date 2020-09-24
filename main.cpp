#include "main_window/main_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Debacle");
    w.resize(540, 870);
    w.show();
    return a.exec();
}
