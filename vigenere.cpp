#include "vigenere.h"


Vigenere::Vigenere(QVector<QString> const &abc_value)
{
    this->alphabet = abc_value;
}

QString Vigenere::expand_key(int size)
{
    QString temp_key = this->key;
    int fullstring_c = (size / key.size()) - 1;
    int remstring_c = size % key.size();
    for(int i = 0; i < fullstring_c; i++)
    {
        temp_key.append(key);
    }
    temp_key.append(key.left(remstring_c));
    return temp_key;

}

Vigenere::Vigenere()
{

}

QString Vigenere::encrypt(QString const &message, int s_func(int, int, int))
{
    QString temp_key = expand_key(message.size());
    QString result;
    Alphabet abc = this->currentAbc;
    int shift = 0;
    for(int i = 0; i < temp_key.size(); i++)
    {
        if (this->alphabet.at(abc).contains(message.at(i)))
        {
            int code1 = this->alphabet.at(abc).indexOf(message.at(i));
            int code2 = this->alphabet.at(abc).indexOf(temp_key.at(i - shift));
            int new_code = MathAux::euclidean_remainder(s_func(code1, code2, this->mode), alphabet.at(abc).size());
            result.append(alphabet.at(abc).at(new_code));
        }
        else
        {
            result.append(message.at(i));
            if (this->key_mode == LAZY)
            {
                ++shift;
            }
        }
    }
    return result;
}

void Vigenere::setRot(Rot r)
{
    this->mode = r;
}

void Vigenere::setKey(QString const &k)
{
    this->key = k;
}

void Vigenere::setCurrentAbc(Alphabet c)
{
    this->currentAbc = c;
}

void Vigenere::setKeyMode(KeyMode k)
{
    this->key_mode = k;
}

Alphabet Vigenere::getCurrentAbc()
{
    return this->currentAbc;
}
