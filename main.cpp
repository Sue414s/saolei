#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include "myCanvas.h"
#include "controller.h"


int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    MyCanvas window;
    window.setAttribute(Qt::WA_DeleteOnClose); 
    Controller controller(&window);
    window.show();
    return app.exec();
}