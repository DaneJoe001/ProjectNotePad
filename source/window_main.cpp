#include <QMessageBox>
#include <QDebug>
#include <QString>

#include <window_main.hpp>

WindowMain::WindowMain(QWidget* parent) :
    QMainWindow(parent)
{
    this->setWindowTitle("NotePad");
    this->setGeometry(200, 200, 800, 600);
    this->show();
}