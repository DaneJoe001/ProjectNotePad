#include <QMainWindow>
#include <QTextEdit>
#include <QObject>

#include <manage_file.hpp>
//TODO；添加键盘事件 ctrl+s 保存文件
//TODO: 添加文件是否修改检测

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
private:
    //记录内容是否进行了修改
    bool is_modified = false;
    //界面文本编辑框
    QTextEdit* m_text_edit = nullptr;
    //文件管理器引用
    ManageFile& m_file_manager = ManageFile::get_instance();

};