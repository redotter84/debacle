#pragma once

#include "../env.h"

using namespace std;

// class for manipulation with files
class FileManager {

private:
    const QString LANGS_NAMES = "lang_names.txt";
    const QString LANGS_IDS = "lang_ids.txt";
    const QString WORDS_FILE = "words.txt";
    const QString MEANINGS_FILE = "meanings.txt";
    const QString FREQS_FILE = "freqs.txt";
    QRandomGenerator rnd; // randomizer

public:
    FileManager();
    QVector<StringPair> read_all_langs();
    QString add_lang(QString);
    QVector<Word> read_all_words(QString lang);
    void write_word(QString lang, StringPair word);
    void change_word(QString lang, size_t pos, int d);

};
