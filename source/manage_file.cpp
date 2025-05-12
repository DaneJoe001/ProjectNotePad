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

bool ManageFile::open(QString path)
{
    if (path.isEmpty())
    {
        return false;
    }
    if (m_file_map.find(path) != m_file_map.end())
    {
        m_current_file_path = path;
        m_current_file_content = m_file_map[path];
        qDebug() << "文件已打开！" << path;
        //TODO：在界面中提示
        return false;
    }
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << u8"打开文件失败";
        return false;
    }
    m_current_file_content = QString(file.readAll());
    m_current_file_path = path;
    qDebug() << u8"文件名" << m_current_file_path;
    qDebug() << u8"文件内容" << m_current_file_content;

    //同步更新到map
    m_file_map[path] = m_current_file_content;
    qDebug() << m_current_file_path;
    return true;
}

bool ManageFile::close(QString path)
{
    auto it = m_file_map.find(path);
    if (it == m_file_map.end())
    {
        qDebug() << u8"关闭文件失败";
        return false;
    }
    m_file_map.erase(it);
    return true;
}

QString& ManageFile::get_file_content(QString path)
{
    if (m_file_map.find(path) != m_file_map.end())
    {
        return m_file_map[path];
    }
    //提示文件不存在
    return m_current_file_content;
}

bool ManageFile::save(const QString& path, const QString& content)
{
    if (path.isEmpty())
    {
        qDebug() << "path is empty";
        return false;
    }
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "写入文件打开失败";
        return false;
    }
    file.write(content.toUtf8());
    //更新到表结构
    m_file_map[path] = content;
    file.close();
    return true;
}

bool ManageFile::new_file(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "写入文件打开失败";
        return false;
    }
    if (m_file_map.find(m_current_file_path) != m_file_map.end())
    {
        qDebug() << "文件已存在(当前列表)";
    }
    file.close();
    //TODO 将当前文件路径及内容切换到新文件
    //TODO，提示框
    save(m_current_file_path, m_current_file_content);
    m_current_file_path = path;
    m_current_file_content.clear();
    m_file_map[m_current_file_path] = m_current_file_content;
    //保存当前文件内容
    return true;
}

QStringList ManageFile::get_file_path_list()
{
    return QStringList();
}