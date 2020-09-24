#include "test_layout.h"

// constructor
TestLayout::TestLayout(Word _word, bool rev):
    QVBoxLayout(), word(_word), reverse(rev) {
    set_gui();
}

void TestLayout::set_gui() {
    // name of the current screen
    header = new QLabel("Do you know this word?");
    header->setStyleSheet(
        "font:italic 30px Arial;"
        "padding:5px;"
    );
    header->setAlignment(Qt::AlignTop);
    header->setFixedHeight(100);

    // current word
    if (!reverse) {
        question = new QLabel(word.word);
    } else {
        question = new QLabel(word.meaning);
    }
    question->setStyleSheet(
        "margin:30px;"
        "font:bold 40px Arial;"
    );
    question->setAlignment(Qt::AlignTop);

    // meaning of the current word
    if (!reverse) {
        answer = new QLabel(word.meaning);
    } else {
        answer = new QLabel(word.word);
    }
    answer->setStyleSheet(
        "margin: 30px;"
        "font: bold 40px Arial;"
    );
    answer->setAlignment(Qt::AlignTop);
    QSizePolicy sp = answer->sizePolicy();
    sp.setRetainSizeWhenHidden(true);
    answer->setSizePolicy(sp);
    answer->hide();

    const QString button_style_sheet =
        "font: 30px Arial;"
        "border: none;"
        "outline: none;"
        "padding: 5px;"
        "margin-bottom: 10px;"
        "border-radius: 5px;";

    // "yes" button
    yes = new QPushButton("Yes");
    yes->setStyleSheet(
        "background: #058c0e;" +
        button_style_sheet
    );

    // "no" button
    no = new QPushButton("No");
    no->setStyleSheet(
        "background: #ba0909;" +
        button_style_sheet
    );

    choice = new QHBoxLayout();
    choice->addWidget(yes); choice->addWidget(no);

    // "i was wrong" button
    wrong = new QPushButton("I was wrong");
    wrong->setStyleSheet(
        "background:#ba0909;" +
        button_style_sheet
    );
    wrong->hide();

    // "next" button
    next = new QPushButton("Next");
    next->setStyleSheet(
        "background: #911db7;" +
        button_style_sheet
    );
    next->hide();

    this->addWidget(header);
    this->addWidget(question);
    this->addWidget(answer);
    this->addLayout(choice);
    this->addWidget(wrong);
    this->addWidget(next);

    // connect signals to slots
    connect(yes, &QPushButton::clicked, this, &TestLayout::ifYes);
    connect(no, &QPushButton::clicked, this, &TestLayout::ifNo);
    connect(wrong, &QPushButton::clicked, this, &TestLayout::i_was_wrong);
}

// action we do depending on the answer
void TestLayout::ifYes() {
    ++status;
    next_step(true);
}
void TestLayout::ifNo() {
    --status;
    next_step();
}

// show link to next question
void TestLayout::next_step(bool from_yes) {
    yes->hide();
    no->hide();
    if (from_yes) wrong->show();
    answer->show();
    next->show();
}

// wrong answer
void TestLayout::i_was_wrong() {
    status -= 2;
}

// destructor
TestLayout::~TestLayout() {
    delete header;
    delete question;
    delete choice;
    delete answer;
    delete wrong;
    delete next;
}
