#pragma once

#include "../env.h"
#include "../lang/lang.h"
#include "../file_manager/file_manager.h"
#include "../test/test.h"

// class for main window of the app
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void change_test();
    void go_home();
    void add_lang();

private:
    QWidget *current_widget = nullptr;
    QVBoxLayout *home_layout;
    FileManager *fmanager;
    Lang *language = nullptr;
    QMap<QPushButton*, StringPair> menu_langs;
    QPushButton* add;
    void build_menu();
    void go_to_lang();

};
