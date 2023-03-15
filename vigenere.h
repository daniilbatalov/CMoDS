#ifndef VIGENERE_H
#define VIGENERE_H

#include <QVector>
#include <QString>
#include "aux/math_aux.h"

namespace Vigenere
{

    enum class Rot
    {
        ROT_0,
        ROT_1
    };

    enum class Alphabet
    {
        INVALID = -1,
        RU_LC,
        RU_UC,
        EN_LC,
        EN_UC

    };

    enum class KeyMode
    {
        GREEDY,
        LAZY
    };


    class Vigenere
    {
    private:
        QString key;
        Rot mode = Rot::ROT_0;
        QString expand_key(int size);
        QVector<QString> alphabet;
        Alphabet currentAbc = Alphabet::INVALID;
        KeyMode key_mode = KeyMode::GREEDY;

    public:
        Vigenere();
        Vigenere(const QVector<QString> &abc_value);
        QString encrypt(const QString &message, int s_func(int, int, int));
        void setRot(Rot r);
        void setKey(const QString &k);
        void setCurrentAbc(Alphabet c);
        void setKeyMode(KeyMode k);
        Alphabet getCurrentAbc();

    };
}
#endif // VIGENERE_H
