#pragma once

#include "../env.h"
#include "../file_manager/file_manager.h"
#include "../test/test.h"

// class for one particular language
class Lang: public QObject {
Q_OBJECT

private:
    QString lang, id; // language and its id
    FileManager *fmanager; // file manager
    QPushButton *back; // back to the start screen
    QLabel *header; // name of the language
    QTableWidget *table; // table with words
    QHBoxLayout *form; // form consisting of a word and its meaning
    QLineEdit *word, *meaning; // word and its meaning
    QPushButton *add; // "add word" button
    QPushButton *run, *run_inverse; // "run test" buttons
    Test *test = nullptr; // test itself

    void set_gui();
    void make_connections();
    void load_words();

private slots:
    void next_question();
    void finish_test();
    void add_word();

signals:
    void change_layout();
    void close();

public:
    QVBoxLayout *layout;
    Lang(QString _lang, QString _id, FileManager *fmanager);
    ~Lang();

};
