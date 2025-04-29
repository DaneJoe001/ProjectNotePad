#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>
#include <QWidget>


#include <window_main.hpp>
#include <manage_file.hpp>

WindowMain::WindowMain(QWidget* parent) :
    QMainWindow(parent)
{
    //设置主窗口标题
    this->setWindowTitle("NotePad");
    //设置窗口位置及大小
    this->setGeometry(200, 200, 800, 600);
    //TODO:设置窗口图标
    //TODO:修改窗口样式以及布局

    //创建文本编辑框
    m_text_edit = new QTextEdit(this);
    this->setCentralWidget(m_text_edit);

    //创建菜单栏
    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* menu_file = menuBar->addMenu("File");
    QAction* action_open = menu_file->addAction("Open");
    menu_file->addSeparator();
    QAction* action_save = menu_file->addAction("Save");
    menu_file->addSeparator();
    QAction* action_save_as = menu_file->addAction("Save as");
    QMenu* menu_edit = menuBar->addMenu("Edit");

    //连接动作和槽函数
    QObject::connect(action_open, &QAction::triggered, this, &WindowMain::on_open_file);
    QObject::connect(action_save, &QAction::triggered, this, &WindowMain::on_save_file);
    QObject::connect(action_save_as, &QAction::triggered, this, &WindowMain::on_save_as_file);
}

void WindowMain::on_open_file()
{
    if (!m_text_edit->toPlainText().isEmpty())
    {
        //TODO:save or discard
    }
    ManageFile& manage_file = ManageFile::get_instance();
    manage_file.open();
    QString& current_file_path = manage_file.get_current_file_path();
    QString& current_file_content = manage_file.get_current_file_content();
    if (current_file_content != nullptr)
    {
        m_text_edit->setText(current_file_content);
    }

    qDebug() << "Open file!";
}

void WindowMain::on_save_file()
{
    qDebug() << "Save file!";
}

void WindowMain::on_save_as_file()
{
    qDebug() << "Save as file!";
}