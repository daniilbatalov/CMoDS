#ifndef VIGENERE_H
#define VIGENERE_H

#include <QVector>
#include <QString>
#include "aux/math_aux.h"

enum Rot
{
    ROT_0,
    ROT_1
};

enum Alphabet
{
    INVALID = -1,
    RU_LC,
    RU_UC,
    EN_LC,
    EN_UC

};

enum KeyMode
{
    GREEDY,
    LAZY
};


class Vigenere
{
private:
    QString key;
    Rot mode = ROT_0;
    QString expand_key(int size);
    QVector<QString> alphabet;
    Alphabet currentAbc = INVALID;
    KeyMode key_mode = GREEDY;

public:
    Vigenere();
    Vigenere(QVector<QString> const &abc_value);
    QString encrypt(QString const &message, int s_func(int, int, int));
    void setRot(Rot r);
    void setKey(QString const &k);
    void setCurrentAbc(Alphabet c);
    void setKeyMode(KeyMode k);
    Alphabet getCurrentAbc();

};

#endif // VIGENERE_H
