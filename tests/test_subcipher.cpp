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

QTEST_GUILESS_MAIN(test_subcipher)

