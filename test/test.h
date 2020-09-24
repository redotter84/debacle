#pragma once

#include "../env.h"
#include "../test_layout/test_layout.h"
#include "../file_manager/file_manager.h"

// class for test consisting of TEST_SIZE questions
class Test : public QWidget {
Q_OBJECT

private:
    const int TEST_SIZE = 20;
    QString id; // language
    QVector<Word> words; // words in test
    FileManager *fmanager; // file manager
    int current = -1; // number of current word
    void run();

private slots:
    void update();

public:
    Test() {}
    Test(QString lang, FileManager *fm);
    TestLayout *layout = nullptr; // test layout of the current word
    bool inverse = false;

public slots:
    void run_normal();
    void run_inverse();

signals:
    void update_layout();
    void finish_test();

};
