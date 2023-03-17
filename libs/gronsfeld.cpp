#include "gronsfeld.h"

namespace Gronsfeld
{

Gronsfeld::Gronsfeld(const QVector<QString>& abc) { this->alphabet = abc; }

void Gronsfeld::setKey(const QString& k) { this->key = k; }

QString Gronsfeld::expand_key(const qsizetype size)
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
    QString tmp_key = this->expand_key(message.length());
    QString res = "";
    qsizetype shift = 0;
    for (QString::const_iterator it = message.cbegin(); it != message.cend(); ++it)
    {
        qsizetype curr_key
            = static_cast<qsizetype>(tmp_key.mid(it - message.cbegin() - shift, 1).toInt());
        QChar new_char = this->shift((*it), curr_key, func);
        if (((*it) == new_char) && (this->key_mode == KeyMode::LAZY))
        {
            ++shift;
        }
        res.append(new_char);
    }
    return res;
}

QChar Gronsfeld::shift(const QChar c, const qsizetype sh, qsizetype func(qsizetype, qsizetype))
{
    for (QVector<QString>::iterator it = this->alphabet.begin(); it != this->alphabet.end(); ++it)
    {
        if ((*it).contains(c))
        {
            qsizetype new_index = MathAux::euclidean_remainder<qsizetype>(
                func((*it).indexOf(c), sh), (*it).length());
            return (*it).at(new_index);
        }
    }
    return c;
}

void Gronsfeld::setKeyMode(const KeyMode k) { this->key_mode = k; }

}
