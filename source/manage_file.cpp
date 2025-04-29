#include <QFileDialog>
#include <QFile>
#include <QDebug>

#include <manage_file.hpp>

ManageFile::ManageFile() {}
ManageFile& ManageFile::get_instance()
{
    static ManageFile managefile;
    return managefile;
}

QString& ManageFile::get_current_file_content()
{
    return m_current_file_content;
}

QString& ManageFile::get_current_file_path()
{
    return m_current_file_path;
}

bool ManageFile::open()
{
    m_current_file_path = QFileDialog::getOpenFileName(nullptr, u8"打开文件", "", "*");
    if (m_current_file_path.isEmpty())
    {
        return false;
    }
    QFile file(m_current_file_path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << u8"打开文件失败";
        return false;
    }
    m_current_file_content = file.readAll();
    add_new_file(m_current_file_path, m_current_file_content);
    return true;
}

void ManageFile::close(QString path)
{

}

void ManageFile::add_new_file(QString& path, QString& content)
{
    if (m_file_map.find(path) != m_file_map.end())
    {
        qDebug() << u8"文件已存在";
    }
    else
    {
        m_file_map[path] = content;
    }

}