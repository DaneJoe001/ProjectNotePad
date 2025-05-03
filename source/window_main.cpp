#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QMenuBar>
#include <QFile>
#include <QFileDialog>
#include <QWidget>


#include <window_main.hpp>

WindowMain::WindowMain(QWidget* parent) :
    QMainWindow(parent)
{
    //设置主窗口标题
    this->setWindowTitle("文本编辑器");
    //设置窗口位置及大小
    this->setGeometry(200, 200, 800, 600);
    //TODO:设置窗口图标
    //TODO:修改窗口样式以及布局

    //创建文本编辑框
    m_text_edit = new QTextEdit(this);
    this->setCentralWidget(m_text_edit);

    //创建菜单栏
    QMenuBar* menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    QMenu* menu_file = menuBar->addMenu("文件");
    QAction* action_open = menu_file->addAction("打开");
    menu_file->addSeparator();
    QAction* action_new = menu_file->addAction("新建");
    menu_file->addSeparator();
    QAction* action_save = menu_file->addAction("保存");
    menu_file->addSeparator();
    QAction* action_save_as = menu_file->addAction("另存为");

    //TODO:添加其他功能选项
    QMenu* menu_edit = menuBar->addMenu("编辑");
    QAction* action_settings = menu_edit->addAction("设置");
    menu_edit->addSeparator();
    QAction* action_undo = menu_edit->addAction("撤销");

    //连接动作和槽函数
    QObject::connect(action_open, &QAction::triggered, this, &WindowMain::on_open_file);
    QObject::connect(action_save, &QAction::triggered, this, &WindowMain::on_save_file);
    QObject::connect(action_save_as, &QAction::triggered, this, &WindowMain::on_save_as_file);
    QObject::connect(action_new, &QAction::triggered, this, &WindowMain::on_new_file);
}

void WindowMain::on_open_file()
{
    if (!m_text_edit->toPlainText().isEmpty())
    {
        //TODO:save or discard
    }
    QString path = QFileDialog::getOpenFileName(nullptr, u8"打开文件", "", "*");
    m_file_manager.open(path);
    QString& current_file_path = m_file_manager.get_current_file_path();
    QString& current_file_content = m_file_manager.get_current_file_content();
    m_text_edit->setText(current_file_content);
}

void WindowMain::on_new_file()
{
    if (!m_text_edit->toPlainText().isEmpty())
    {
        //TODO:提示保存或关闭
    }
    QString path = QFileDialog::getSaveFileName(nullptr, "新建文件", "", "*.txt");
    qDebug() << u8"新建文件！";
    if (path.isEmpty())
    {
        QMessageBox::information(this, "错误", "文件名为空！");
    }
    bool check_new_file = m_file_manager.new_file(path);
    if (check_new_file)
    {
        QMessageBox::information(this, "提示", "新建文件成功!");
    }
    else
    {
        QMessageBox::information(this, "提示", "新建文件失败!");
    }
}

void WindowMain::on_save_file()
{
    //TODO:当前文件路径为空时调用save_as_file()
    qDebug() << "Save file!";
    QString& current_file_path = m_file_manager.get_current_file_path();
    QString& current_file_content = m_file_manager.get_current_file_content();
    //写入当前TextEdit中的内容
    current_file_content = m_text_edit->toPlainText();
    bool check_save = m_file_manager.save(current_file_path, current_file_content);
    if (check_save)
    {
        QMessageBox::information(this, u8"提示", u8"保存文件成功!");
    }
    else
    {
        QMessageBox::information(this, u8"提示", u8"保存文件失败!");
    }

}

void WindowMain::on_save_as_file()
{
    QString path = QFileDialog::getSaveFileName(nullptr, "另存为文件", "", "*.txt");
    if (path.isEmpty())
    {
        QMessageBox::information(this, u8"保存失败", "文件名为空!");
    }
    bool check_new_file = m_file_manager.new_file(path);
    m_file_manager.save(path, m_text_edit->toPlainText());
    if (check_new_file)
    {
        QMessageBox::information(nullptr, "提示", "文件另存为成功!");
    }
    else
    {
        QMessageBox::information(nullptr, "提示", "文件另存为失败!");
    }
}