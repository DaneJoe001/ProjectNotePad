#include <QApplication>
#include <QDebug>

#include <window_main.hpp>

int main(int argc, const char* argv[])
{
    QApplication app(argc, const_cast<char**>(argv));
    WindowMain window;
    window.show();
    return app.exec();
}