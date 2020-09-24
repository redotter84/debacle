#include "test.h"

// constructor
Test::Test(QString _id, FileManager *fm):
    id(_id), fmanager(fm) {
}

// run either normal or inverse version
void Test::run_normal() {
    this->inverse = false;
    run();
}
void Test::run_inverse() {
    this->inverse = true;
    run();
}

// create questions
void Test::run() {
    words.clear();
    QVector<Word> all_words = fmanager->read_all_words(id);
    std::random_shuffle(all_words.begin(), all_words.end());
    std::sort(all_words.begin(), all_words.end());
    for (int i = 0; i < min(TEST_SIZE, all_words.size()); i++) {
        words.push_back(all_words[i]);
    }
    update();
}

// test process
void Test::update() {
    if (current != -1) {
        fmanager->change_word(id, words[current].ind, layout->status);
        delete layout;
    }
    ++current;
    if (current == words.size()) {
        current = -1;
        emit finish_test();
        return;
    }
    layout = new TestLayout(words[current], this->inverse);
    connect(layout->next, &QPushButton::clicked, this, &Test::update);
    connect(layout->wrong, &QPushButton::clicked, this, &Test::update);
    emit update_layout();
}
