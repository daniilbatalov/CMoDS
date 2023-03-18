#include "tst_vigenere.h"

tst_vigenere::tst_vigenere(QObject *parent)
    : QObject{parent}
{

}

void tst_vigenere::testConstructor()
{
    const QVector<QString> t{ "абвгдеёжзийклмнопрстуфхцчшщъыьэюя",
                              "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
                              "abcdefghijklmnopqrstuvwxyz",
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    v = std::make_unique<Vigenere::Vigenere>(t);
    QCOMPARE(v->getAlphabets(), t);
}
