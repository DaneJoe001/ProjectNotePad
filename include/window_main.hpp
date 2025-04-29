#include <QMainWindow>
#include <QTextEdit>
#include <QObject>

class WindowMain :public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Window Main object
     * @param parent 父窗口指针
     */
    WindowMain(QWidget* parent = nullptr);
private slots:
    /**
     * @brief 打开文件
     */
    void on_open_file();
    /**
     *@brief 保存文件
     */
    void on_save_file();
    /**
     *@brief 另存为文件
     */
    void on_save_as_file();
private:
    QTextEdit* m_text_edit = nullptr;

};