#include "tst_subcipher.h"

tst_subcipher::tst_subcipher(QObject* parent)
: QObject{ parent }
{
}

void tst_subcipher::testConstructor()
{
    const QVector<QString> t{ "абвгдеёжзийклмнопрстуфхцчшщъыьэюя",
                              "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
                              "abcdefghijklmnopqrstuvwxyz",
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    s = std::make_unique<SubCipher>(t);
    QCOMPARE(s->getAlphabets(), t);
}

void tst_subcipher::testEncrypt()
{
    QCOMPARE(s->encrypt(
                 "A", [](qsizetype i, qsizetype n, qsizetype) { return n - i - 1; }, 0),
             "Z");
    QCOMPARE(s->encrypt(
                 "А", [](qsizetype i, qsizetype n, qsizetype) { return n - i - 1; }, 0),
             "Я");
    QCOMPARE(s->encrypt(
                 ".", [](qsizetype i, qsizetype n, qsizetype) { return n - i - 1; }, 0),
             ".");
}
