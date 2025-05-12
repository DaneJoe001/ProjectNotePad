#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QStringList>

#ifndef RESOURCE_DIR
#define RESOURCE_DIR "./resource"
#endif

class DialogAppendFile : public QDialog
{
    Q_OBJECT
public:
    explicit DialogAppendFile(QWidget* parent = nullptr);
    QStringList get_file_path_list();

private:
    QLineEdit* m_line_filter_0;
    QLineEdit* m_line_filter_1;
    QLineEdit* m_line_filter_2;
};