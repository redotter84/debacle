#include "lang.h"

// constructor
Lang::Lang(QString _lang, QString _id, FileManager *fm):
    lang(_lang), id(_id), fmanager(fm) {
    layout = new QVBoxLayout;
    set_gui();
    load_words();
    make_connections();
}

// set up gui elements
void Lang::set_gui() {
    // back button
    back = new QPushButton("Back");
    back->setStyleSheet(
        "background: #911db7;"
        "font: 25px Arial;"
        "border: none;"
        "padding: 7px;"
        "border-radius: 10px;"
    );
    back->setDefault(true);

    // name of the language
    header = new QLabel(lang);
    header->setAlignment(Qt::AlignCenter);
    header->setStyleSheet(
        "font: 40px bold Arial;"
        "padding: 5px;"
    );

    // list of words
    table = new QTableWidget(0, 2);
    table->verticalHeader()->hide();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->hide();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setStyleSheet(
        "QTableWidget {"
            "font: 22px Arial;"
            "background: #bbb;"
            "border: none;"
            "border-radius: 10px;"
            "margin-bottom: 10px;"
        "}"
        "QTableWidget::item {"
            "padding: 5px;"
            "border: none;"
        "}"
        "QScrollBar:vertical {"
            "background: #911db7;"
            "width: 30px;"
            "height: 50px;"
            "outline: none;"
            "border: none;"
        "}"
    );

    // style sheet for line edits
    const QString line_edit_style_sheet =
        "font: 24px Arial;"
        "background: #ddd;"
        "padding: 3px;"
        "height: 35px;"
        "border-radius: 5px;";

    // "new word" input
    word = new QLineEdit;
    word->setStyleSheet(line_edit_style_sheet);

    // "new word meaning" input
    meaning = new QLineEdit;
    meaning->setStyleSheet(line_edit_style_sheet);

    // "add new word" button
    add = new QPushButton("Add");
    add->setStyleSheet(
        "background: #336dcc;"
        "font: 25px Arial;"
        "padding: 5px;"
        "width: 100px;"
        "height: 29px;"
        "border-radius: 5px;"
    );
    add->setDefault(true);

    // form with new word
    form = new QHBoxLayout;
    form->addWidget(word);
    form->addWidget(meaning);
    form->addWidget(add);

    // "run test" button
    run = new QPushButton("Run test");
    run->setStyleSheet(
        "background: #911db7;"
        "font: 25px Arial;"
        "border: none;"
        "padding: 5px;"
        "margin-top: 10px;"
        "border-radius: 10px;"
    );
    run->setDefault(true);

    // "run inverse test" button
    run_inverse = new QPushButton("Run inverse test");
    run_inverse->setStyleSheet(
        "background: #911db7;"
        "font: 25px Arial;"
        "border: none;"
        "padding: 5px;"
        "border-radius: 10px;"
    );
    run_inverse->setDefault(true);

    // add everything to layout
    layout->addWidget(back);
    layout->addWidget(header);
    layout->addWidget(table);
    layout->addLayout(form);
    layout->addWidget(run);
    layout->addWidget(run_inverse);
}

// load words from database
void Lang::load_words() {
    table->setRowCount(0);
    QVector<Word> words = fmanager->read_all_words(id);
    int count = 0;
    for (const Word& word : words) {
        table->insertRow(count);
        table->setItem(count, 0, new QTableWidgetItem(word.word));
        table->setItem(count, 1, new QTableWidgetItem(word.meaning));
        ++count;
    }
}

// connect signal to slots
void Lang::make_connections() {
    if (test) delete test;
    test = new Test(id, fmanager);
    connect(test, &Test::update_layout, this, &Lang::next_question);
    connect(test, &Test::finish_test, this, &Lang::finish_test);
    connect(run, &QPushButton::clicked, test, &Test::run_normal);
    connect(run_inverse, &QPushButton::clicked, test, &Test::run_inverse);
    connect(add, &QPushButton::clicked, this, &Lang::add_word);
    connect(back, &QPushButton::clicked, this, &Lang::close);
}

// add new word
void Lang::add_word() {
    QString w = word->text();
    QString w1 = w; w1.replace(" ", "");
    QString t = meaning->text();
    QString t1 = t; t1.replace(" ", "");
    if (w1.isEmpty() || t1.isEmpty()) return;
    fmanager->write_word(id, {w, t});
    word->setText("");
    meaning->setText("");
    load_words();
}

// next question in text
void Lang::next_question() {
    layout = test->layout;
    emit change_layout();
}

// finish test
void Lang::finish_test() {
    layout = new QVBoxLayout;
    set_gui();
    make_connections();
    load_words();
    emit change_layout();
}

// destructor
Lang::~Lang() {
    delete layout;
    delete test;
}
