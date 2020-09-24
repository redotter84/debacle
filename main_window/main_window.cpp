#include "main_window.h"

// constructor of main window
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    fmanager = new FileManager;
    this->setStyleSheet(
        "* {"
            "background:#aaa;"
        "}"
        "QInputDialog QLineEdit {"
            "background:#ddd;"
            "font: 20px Arial;"
        "}"
    );
    go_home();
}

void MainWindow::change_test() {
    delete current_widget;
    current_widget = new QWidget;
    current_widget->setLayout(language->layout);
    this->setCentralWidget(current_widget);
}

// return from test to home
void MainWindow::go_home() {
    if (language) delete language;
    language = nullptr;
    if (current_widget) delete current_widget;
    build_menu();
    current_widget = new QWidget;
    current_widget->setLayout(home_layout);
    this->setCentralWidget(current_widget);
}

// build menu of available languages
void MainWindow::build_menu() {
    home_layout = new QVBoxLayout;
    home_layout->setContentsMargins(0, 10, 0, 10);
    QVector<StringPair> langs = fmanager->read_all_langs();
    for (StringPair lang : langs) {
        QPushButton *btn = new QPushButton(lang.first);
        btn->setStyleSheet(
            "background: #911db7;"
            "font: 25px Arial;"
            "border: none;"
            "padding: 10px;"
            "height: 30px;"
        );
        btn->setDefault(true);
        connect(btn, &QPushButton::clicked, this, &MainWindow::go_to_lang);
        menu_langs[btn] = lang;
        home_layout->addWidget(btn);
    }

    // "add language" button
    add = new QPushButton("Add Language");
    add->setStyleSheet(
        "background: #336dcc;"
        "font: 25px Arial;"
        "border: none;"
        "padding: 10px;"
        "height: 30px;"
    );
    add->setDefault(true);
    connect(add, &QPushButton::clicked, this, &MainWindow::add_lang);
    home_layout->addWidget(add);
}

// add language
void MainWindow::add_lang() {
    bool ok = false;
    QString name = QInputDialog::getText(
        this, "Language", "Language name:",
        QLineEdit::Normal, "", &ok
    );
    name.replace(" ", "");
    if (!ok || name.isEmpty()) return;

    // button with new language
    QPushButton *btn = new QPushButton(name);
    btn->setStyleSheet(
        "background: #911db7;"
        "font: 25px Arial;"
        "border: none;"
        "padding: 10px;"
        "height: 30px;"
    );
    btn->setDefault(true);
    connect(btn, &QPushButton::clicked, this, &MainWindow::go_to_lang);
    menu_langs[btn] = {name, fmanager->add_lang(name)};
    home_layout->removeWidget(add);
    home_layout->addWidget(btn);
    home_layout->addWidget(add);
}

// go to language layout
void MainWindow::go_to_lang() {
    QPushButton *obj = qobject_cast<QPushButton*>(sender());
    StringPair lang = menu_langs[obj];
    language = new Lang(lang.first, lang.second, fmanager);
    connect(language, &Lang::change_layout, this, &MainWindow::change_test);
    connect(language, &Lang::close, this, &MainWindow::go_home);
    delete current_widget;
    current_widget = new QWidget;
    current_widget->setLayout(language->layout);
    this->setCentralWidget(current_widget);
}

// destructor of main window
MainWindow::~MainWindow() {
    if (language) delete language;
    delete current_widget;
    delete fmanager;
}
