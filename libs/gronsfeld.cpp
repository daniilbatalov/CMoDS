#include "gronsfeld.h"

namespace Gronsfeld
{

Gronsfeld::Gronsfeld(const QVector<QString>& abc) { this->alphabet = abc; }

void Gronsfeld::setKey(const QString& k) { this->key = k; }

QString Gronsfeld::expandKey(const qsizetype size)
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

QString Gronsfeld::encrypt(const QString& message, qsizetype func(qsizetype, qsizetype))
{
    QString tmp_key = this->expandKey(message.length());
    QString res = "";
    qsizetype shift_k = 0;
    for (QString::const_iterator it = message.cbegin(); it != message.cend(); ++it)
    {
        qsizetype curr_key
            = static_cast<qsizetype>(tmp_key.mid(it - message.cbegin() - shift_k, 1).toInt());
        QPair<QChar, bool> new_char = this->shift((*it), curr_key, func);
        if ((!new_char.second) && (this->key_mode == KeyMode::LAZY))
        {
            ++shift_k;
        }
        res.append(new_char.first);
    }
    return res;
}

QPair<QChar, bool> Gronsfeld::shift(const QChar c,
                                    const qsizetype sh,
                                    qsizetype func(qsizetype, qsizetype))
{
    for (QVector<QString>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it)
    {
        if ((*it).contains(c))
        {
            qsizetype new_index = MathAux::euclidean_remainder<qsizetype>(
                func((*it).indexOf(c), sh), (*it).length());
            return QPair<QChar, bool>((*it).at(new_index), true);
        }
    }
    return QPair<QChar, bool>(c, false);
}

void Gronsfeld::setKeyMode(const KeyMode k) { this->key_mode = k; }

QString Gronsfeld::getKey() { return this->key; }

KeyMode Gronsfeld::getKeyMode() { return this->key_mode; }

QVector<QString> Gronsfeld::getAlphabets() { return this->alphabet; }

}
