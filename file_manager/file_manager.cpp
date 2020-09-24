#include "file_manager.h"
#include <time.h>

// constructor
FileManager::FileManager() {
}

// read all languages existing
QVector<StringPair> FileManager::read_all_langs() {
    QVector<StringPair> ans;
    QFile lang1(LANGS_NAMES);
    lang1.open(QIODevice::ReadWrite);
    QFile lang2(LANGS_IDS);
    lang2.open(QIODevice::ReadWrite);
    while (!lang1.atEnd()) {
        QString s = lang1.readLine();
        QString t = lang2.readLine();
        while (s.back() == '\n' || s.back() == '\r') {
            s.chop(1);
        }
        while (t.back() == '\n' || t.back() == '\r') {
            t.chop(1);
        }
        ans.push_back({s, t});
    }
    return ans;
}

// add new language
QString FileManager::add_lang(QString lang) {
    QString id = "";
    for (size_t i = 0; i < 5; i++) {
        char c = 'a' + rnd.generate() % 26;
        id += c;
    }
    QFile lang1(LANGS_NAMES);
    lang1.open(QIODevice::Append);
    QTextStream lang1_str(&lang1);
    lang1_str.setCodec("UTF-8");
    lang1_str << lang << endl;
    QFile lang2(LANGS_IDS);
    lang2.open(QIODevice::Append);
    QTextStream lang2_str(&lang2);
    lang2_str.setCodec("UTF-8");
    lang2_str << id << endl;
    return id;
}

// read all words of the language (by id)
QVector<Word> FileManager::read_all_words(QString lang) {
    QVector<Word> ans;
    QFile words(lang + "_" + WORDS_FILE);
    words.open(QIODevice::ReadWrite);
    QFile meanings(lang + "_" + MEANINGS_FILE);
    meanings.open(QIODevice::ReadWrite);
    QFile freqs(lang + "_" + FREQS_FILE);
    freqs.open(QIODevice::ReadWrite);
    size_t count = 0;
    while (!words.atEnd()) {
        QString s = words.readLine();
        s.chop(1);
        QString t = meanings.readLine();
        t.chop(1);
        int f = freqs.readLine().toInt();
        ans.push_back({ s, t, f, count });
        ++count;
    }
    return ans;
}

// write new word to language (by id)
void FileManager::write_word(QString lang, StringPair word) {
    QFile words(lang + "_" + WORDS_FILE);
    words.open(QIODevice::Append);
    QTextStream words_str(&words);
    words_str.setCodec("UTF-8");
    words_str << word.first << endl;

    QFile meanings(lang + "_" + MEANINGS_FILE);
    meanings.open(QIODevice::Append);
    QTextStream meanings_str(&meanings);
    meanings_str.setCodec("UTF-8");
    meanings_str << word.second << endl;

    QFile freqs(lang + "_" + FREQS_FILE);
    freqs.open(QIODevice::Append);
    QTextStream freqs_str(&freqs);
    freqs_str << 1 << endl;
}

// change frequency of a word (by position) of language (by id)
void FileManager::change_word(QString lang, size_t pos, int d) {
    QFile freqs(lang + "_" + FREQS_FILE);
    freqs.open(QIODevice::ReadOnly);
    QString content = "";
    size_t count = 0;
    while (!freqs.atEnd()) {
        int f = freqs.readLine().toInt();
        if (count == pos) f += d;
        content += QString::number(f);
        content += "\n";
        ++count;
    }
    freqs.close();
    freqs.open(QIODevice::WriteOnly);
    QTextStream freqs_str(&freqs);
    freqs_str << content;
}
