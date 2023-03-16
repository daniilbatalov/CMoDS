#include "test_subcipher.h"

test_subcipher::test_subcipher(QObject *parent) : QObject(parent)
{
}

void test_subcipher::testConstructor()
{
    const QVector<QString> t{"абвгдеёжзийклмнопрстуфхцчшщъыьэюя", "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ", "abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    s = new SubCipher(t);
    QCOMPARE(s->getAlphabets(), t);
}

void test_subcipher::testEncrypt()
{
    QCOMPARE(s->encrypt("A", [](qsizetype i, qsizetype n, qsizetype) {return n - i - 1;}, 0), "Z");
    QCOMPARE(s->encrypt("А", [](qsizetype i, qsizetype n, qsizetype) {return n - i - 1;}, 0), "Я");
    QCOMPARE(s->encrypt(".", [](qsizetype i, qsizetype n, qsizetype) {return n - i - 1;}, 0), ".");
}


QTEST_GUILESS_MAIN(test_subcipher)

