#include "subcipher.h"

SubCipher::SubCipher(QVector<QString> const &abc)
{
     this->alphabets = abc;
}

QString SubCipher::encrypt(QString const &message, qsizetype s_func(qsizetype, qsizetype, qsizetype), qsizetype shift)
{
    QVector<QString>::iterator it = this->alphabets.begin();

    for (; it != this->alphabets.end(); ++it)
    {
        if ((*it).contains(message, Qt::CaseSensitive))
        {
            qsizetype ind = (*it).indexOf(message);
            qsizetype n_ind = s_func(ind, (*it).length(), shift);
            return (*it)[n_ind];
        }
    }
    return message;
}

QVector<QString> SubCipher::getAlphabets()
{
    return this->alphabets;
}
