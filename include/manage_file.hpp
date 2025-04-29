#pragma once

#include <QString>
#include <QMap>

//TODO:考虑使用一种更合理的方式管理文件列表

class ManageFile
{
public:
    /**
     * @brief Get the instance object
     * @return ManageFile&
     */
    static ManageFile& get_instance();
    /**
     * @brief open file
     * @return true
     * @return false
     */
    bool open();
    /**
     * @brief close file
     * @param path
     */
    void close(QString path);
    /**
     * @brief get current file content
     * @return QString&
     */
    QString& get_current_file_content();
    /**
     * @brief Get the current file path object
     * @return QString&
     */
    QString& get_current_file_path();
private:
    ManageFile();
    ~ManageFile() = default;
    ManageFile(const ManageFile&) = delete;
    ManageFile(const ManageFile&&) = delete;
    ManageFile& operator=(ManageFile&) = delete;
    ManageFile&& operator=(ManageFile&&) = delete;
    /**
     * @brief 向文件列表中添加文件信息
     * @param path 文件路径
     * @param content 文件内容
     */
    void add_new_file(QString& path, QString& content);


private:
    //path+content
    QString m_current_file_content;
    QString m_current_file_path;
    //考虑是否换种数据结构存储？
    QMap<QString, QString> m_file_map;
};