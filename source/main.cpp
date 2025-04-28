#include <iostream>
#include <QApplication>
#include <QDebug>

#include <window_main.hpp>

int main(int argc, const char* argv[])
{
    qDebug() << "Hello World!";
    QApplication app(argc, const_cast<char**>(argv));
    WindowMain window;
    return app.exec();
}