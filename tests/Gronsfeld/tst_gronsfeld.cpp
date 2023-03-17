#include "tst_gronsfeld.h"


tst_gronsfeld::tst_gronsfeld(QObject* parent)
: QObject{ parent }
{
}

void tst_gronsfeld::testConstructor()
{
    const QVector<QString> t{ "абвгдеёжзийклмнопрстуфхцчшщъыьэюя",
                              "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
                              "abcdefghijklmnopqrstuvwxyz",
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    g = std::make_unique<Gronsfeld::Gronsfeld>(t);
    QCOMPARE(g->getAlphabets(), t);
}

void tst_gronsfeld::testKey()
{
    g->setKey("2023");
    QCOMPARE(g->getKey(), "2023");
    g->setKeyMode(Gronsfeld::KeyMode::GREEDY);
    QCOMPARE(g->getKeyMode(), Gronsfeld::KeyMode::GREEDY);
}

void tst_gronsfeld::testEncrypt()
{
    g->setKeyMode(Gronsfeld::KeyMode::GREEDY);
    QCOMPARE(g->encrypt("ABC DE", [](qsizetype i, qsizetype s) { return i + s; }), "CBE FE");
    QCOMPARE(g->encrypt("ABCDE", [](qsizetype i, qsizetype s) { return i + s; }), "CBEGG");
    g->setKeyMode(Gronsfeld::KeyMode::LAZY);
    QCOMPARE(g->encrypt("ABC DE", [](qsizetype i, qsizetype s) { return i + s; }), "CBE GG");
}

void tst_gronsfeld::testDecrypt()
{
    g->setKeyMode(Gronsfeld::KeyMode::GREEDY);
    QCOMPARE(g->encrypt("CBE FE", [](qsizetype i, qsizetype s) { return i - s; }), "ABC DE");
    QCOMPARE(g->encrypt("CBEGG", [](qsizetype i, qsizetype s) { return i - s; }), "ABCDE");
    g->setKeyMode(Gronsfeld::KeyMode::LAZY);
    QCOMPARE(g->encrypt("CBE GG", [](qsizetype i, qsizetype s) { return i - s; }), "ABC DE");
}
