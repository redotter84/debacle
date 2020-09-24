#pragma once

#include "env.h"

// class for test screen for one particular word
class TestLayout : public QVBoxLayout {

private:
    friend class Test;
    Word word;
    QLabel *header, *question, *answer;
    QPushButton *yes, *no, *next, *wrong;
    QHBoxLayout *choice;
    int status = 0; // change to frequency after test
    void set_gui();
    void next_step(bool from_yes = false);
    bool reverse = false;

private slots:
    void ifYes(), ifNo();
    void i_was_wrong();

public:
    TestLayout(Word _word, bool rev = false);
    ~TestLayout();

};
