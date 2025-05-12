#include <QMainWindow>
#include <QTextEdit>
#include <QObject>

#include <manage_file.hpp>
#include <dialog_append_file.hpp>
//TODO；添加键盘事件 ctrl+s 保存文件
//TODO: 添加文件是否修改检测

//TODO: 修复CMake宏
#ifndef RESOURCE_DIR
#define RESOURCE_DIR "./resource"
#endif

class WindowMain :public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief 主窗口构造函数
     * @param parent 父窗口指针
     */
    WindowMain(QWidget* parent = nullptr);
private slots:
    /**
     * @brief 打开文件
     */
    void on_open_file();
    /**
     * @brief 创建新文件
     */
    void on_new_file();
    /**
     *@brief 保存文件
     */
    void on_save_file();
    /**
     *@brief 另存为文件
     */
    void on_save_as_file();
    /**
     * @brief  追加文件(在该文件末尾添加内容)
     */
    void on_append_file();
    /**
     * @brief 切换自动换行
     * @param is_open 是否打开
     */
    void on_auto_wrap_line(bool is_open);
    /**
     * @brief 撤销
     */
    void on_undo_file();
    /**
     * @brief 保存当前文件
     */
    void save_current_file();
private:
    //记录内容是否进行了修改
    bool is_modified = false;
    //界面文本编辑框
    QTextEdit* m_text_edit = nullptr;
    //文件管理器引用
    ManageFile& m_file_manager = ManageFile::get_instance();
    //文件追加界面
    DialogAppendFile* m_dialog_append_file = nullptr;

};