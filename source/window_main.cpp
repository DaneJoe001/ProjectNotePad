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
    //设置窗口图标
    this->setWindowIcon(QIcon(RESOURCE_DIR"/icon/notepad.ico"));
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
    menu_file->addSeparator();
    QAction* action_append = menu_file->addAction("追加");

    //TODO:添加其他功能选项
    QMenu* menu_edit = menuBar->addMenu("编辑");
    QAction* action_settings = menu_edit->addAction("设置");
    menu_edit->addSeparator();
    QAction* action_undo = menu_edit->addAction("撤销");
    menu_edit->addSeparator();
    QAction* action_auto_wrap = menu_edit->addAction("自动换行");
    action_auto_wrap->setCheckable(true);

    on_auto_wrap_line(action_auto_wrap->isChecked());

    //连接动作和槽函数
    QObject::connect(action_open, &QAction::triggered, this, &WindowMain::on_open_file);
    QObject::connect(action_save, &QAction::triggered, this, &WindowMain::on_save_file);
    QObject::connect(action_save_as, &QAction::triggered, this, &WindowMain::on_save_as_file);
    QObject::connect(action_new, &QAction::triggered, this, &WindowMain::on_new_file);
    QObject::connect(action_append, &QAction::triggered, this, &WindowMain::on_append_file);
    QObject::connect(action_undo, &QAction::triggered, this, &WindowMain::on_undo_file);
    QObject::connect(action_auto_wrap, &QAction::triggered, this, &WindowMain::on_auto_wrap_line);
}

void WindowMain::on_open_file()
{
    if (!m_text_edit->toPlainText().isEmpty())
    {
        save_current_file();
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
        save_current_file();
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
    qDebug() << "Save file!";
    QString& current_file_path = m_file_manager.get_current_file_path();
    if (current_file_path.isEmpty())
    {
        on_save_as_file();
        return;
    }
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

void WindowMain::on_append_file()
{
    if (m_dialog_append_file == nullptr)
    {
        m_dialog_append_file = new DialogAppendFile(this);
    }
    m_dialog_append_file->show();
    QStringList file_path_list = m_dialog_append_file->get_file_path_list();
    m_dialog_append_file->hide();
}

void WindowMain::on_auto_wrap_line(bool is_open)
{
    m_text_edit->setLineWrapMode(is_open ? QTextEdit::WidgetWidth : QTextEdit::NoWrap);
}

void WindowMain::on_undo_file()
{
    qDebug() << "Undo file!";
}

void WindowMain::save_current_file()
{
    QMessageBox message_box;
    message_box.setWindowTitle(u8"提示");
    message_box.setText(u8"当前文件未保存，是否保存？");
    message_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    message_box.setDefaultButton(QMessageBox::Yes);
    int ret = message_box.exec();
    if (ret == QMessageBox::Yes)
    {
        on_save_file();
        QMessageBox::information(this, "提示", "保存成功!");
    }
    else
    {
        m_text_edit->clear();
        QMessageBox::information(this, "提示", "取消保存!");
    }
}