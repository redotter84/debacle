#pragma once

#include <QtWidgets>
#include <QFile>
#include <QApplication>

typedef QPair<QString, QString> StringPair;

struct Word {
    QString word, meaning;
    int freq;
    size_t ind;
    bool operator < (const Word& w) const {
        return freq < w.freq;
    }
};
