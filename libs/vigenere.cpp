#include "vigenere.h"

namespace Vigenere
{

Vigenere::Vigenere(const QVector<QString>& abc_value) { this->alphabet = abc_value; }

QString Vigenere::expandKey(const qsizetype size)
{
    QString temp_key = this->key;
    qsizetype fullstring_c = (size / key.size()) - 1;
    qsizetype remstring_c = size % key.size();
    for (qsizetype i = 0; i < fullstring_c; ++i)
    {
        temp_key.append(key);
    }
    temp_key.append(key.left(remstring_c));
    return temp_key;
}

Vigenere::Vigenere() {}

QString Vigenere::encrypt(const QString& message, qsizetype s_func(qsizetype, qsizetype, qsizetype))
{
    QString temp_key = expandKey(message.size());
    QString result;
    Alphabet abc = this->current_abc;
    qsizetype shift = 0;
    for (qsizetype i = 0; i < temp_key.size(); ++i)
    {
        if (this->alphabet.at(static_cast<qsizetype>(abc)).contains(message.at(i)))
        {
            qsizetype code1 = this->alphabet.at(static_cast<qsizetype>(abc)).indexOf(message.at(i));
            qsizetype code2
                = this->alphabet.at(static_cast<qsizetype>(abc)).indexOf(temp_key.at(i - shift));
            qsizetype new_code = MathAux::euclidean_remainder<qsizetype>(
                s_func(code1, code2, static_cast<qsizetype>(this->mode)),
                alphabet.at(static_cast<qsizetype>(abc)).size());
            result.append(alphabet.at(static_cast<qsizetype>(abc)).at(new_code));
        }
        else
        {
            result.append(message.at(i));
            if (this->key_mode == KeyMode::LAZY)
            {
                ++shift;
            }
        }
    }
    return result;
}

void Vigenere::setRot(const Rot r) { this->mode = r; }

void Vigenere::setKey(const QString& k) { this->key = k; }

void Vigenere::setCurrentAbc(const Alphabet c) { this->current_abc = c; }

void Vigenere::setKeyMode(const KeyMode k) { this->key_mode = k; }

Alphabet Vigenere::getCurrentAbc() { return this->current_abc; }

QVector<QString> Vigenere::getAlphabets() { return this->alphabet; }
}
