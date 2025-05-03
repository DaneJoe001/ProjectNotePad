#pragma once

#include <QString>
#include <QMap>

//TODO:考虑使用一种更合理的方式管理文件列表

class ManageFile
{
public:
    /**
     * @brief 获取文件管理器实例
     */
    static ManageFile& get_instance();
    /**
     * @brief 打开文件
     * @return true 打开成功 false 打开失败
     */
    bool open(QString path);
    /**
     * @brief 新建文件
     * @return QString
     */
    bool new_file(QString path);
    /**
     * @brief 保存文件
     * @param path 文件路径名
     * @param content 文件内容
     * @return true 保存成功
     * @return false 保存失败
     */
    bool save(const QString& path, const QString& content);
    /**
     * @brief 在m_file_map中删除文件
     * @param path 文件路径
     */
    bool close(QString path);
    /**
     * @brief 获取当前文件内容
     * @return 当前文件内容引用
     */
    QString& get_current_file_content();
    /**
     * @brief 获取当前文件路径
     * @return 当前文件路径引用
     */
    QString& get_current_file_path();
    /**
     * @brief 获取文件内容
     * @note 当文件不在列表中中则打开当前文件内容
     */
    QString& get_file_content(QString path);
private:
    ManageFile();
    ~ManageFile() = default;
    ManageFile(const ManageFile&) = delete;
    ManageFile(const ManageFile&&) = delete;
    ManageFile& operator=(ManageFile&) = delete;
    ManageFile&& operator=(ManageFile&&) = delete;


private:
    //当前文件内容
    QString m_current_file_content = nullptr;
    //当前文件路径
    QString m_current_file_path = nullptr;
    //存储文件路径+内容
    QMap<QString, QString> m_file_map;
};