#include <QDebug>
#include <QMessageBox>

#include <dialog_append_file.hpp>

DialogAppendFile::DialogAppendFile(QWidget* parent) : QDialog(parent)
{
    this->setWindowTitle("追加文件");
    this->setGeometry(200, 200, 400, 300);
    this->setWindowIcon(QIcon(RESOURCE_DIR"/icon/notepad.ico"));
}

QStringList DialogAppendFile::get_file_path_list()
{
    qDebug() << "DialogAppendFile::get_file_path_list()";
    QMessageBox::information(this, "提示", "请选择要追加的文件");
    return QStringList();
}