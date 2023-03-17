#include "playfair.h"

namespace Playfair
{


QString Playfair::encryptPair(const QString& pair, qsizetype func(qsizetype))
{
    QString res = "";
    QPair<qsizetype, qsizetype> first = this->find(pair.at(0));
    QPair<qsizetype, qsizetype> second = this->find(pair.at(1));

    if (first.first == second.first)
    {
        qsizetype new_first_x = MathAux::euclidean_remainder<qsizetype>(
            func(first.second), static_cast<qsizetype>(this->currentAbc));
        qsizetype new_second_x = MathAux::euclidean_remainder<qsizetype>(
            func(second.second), static_cast<qsizetype>(this->currentAbc));
        res.append(this->table.at(first.first).at(new_first_x));
        res.append(this->table.at(second.first).at(new_second_x));
        return res;
    }
    else if (first.second == second.second)
    {
        qsizetype new_first_y = MathAux::euclidean_remainder<qsizetype>(
            func(first.first), static_cast<qsizetype>(this->currentAbc));
        qsizetype new_second_y = MathAux::euclidean_remainder<qsizetype>(
            func(second.first), static_cast<qsizetype>(this->currentAbc));
        res.append(this->table.at(new_first_y).at(first.second));
        res.append(this->table.at(new_second_y).at(second.second));
        return res;
    }
    else
    {
        res.append(this->table.at(first.first).at(second.second));
        res.append(this->table.at(second.first).at(first.second));
        return res;
    }
}

QPair<qsizetype, qsizetype> Playfair::find(const QChar ch)
{
    for (qsizetype i = 0; i < this->table.length(); ++i)
    {
        for (qsizetype j = 0; j < this->table.at(i).length(); ++j)
        {
            if (table.at(i).at(j) == ch)
                return QPair<qsizetype, qsizetype>{ i, j };
        }
    }
    return QPair<qsizetype, qsizetype>();
}

QVector<QString> Playfair::transformString(const QString& message, QVector<QString>& acc)
{
    QString res = message;
    const QChar x
        = (this->currentAbc == Alphabet::EN) ? this->alphabetEn.at(22) : this->alphabetRu.at(32);
    const QChar q
        = (this->currentAbc == Alphabet::EN) ? this->alphabetEn.at(15) : this->alphabetRu.at(27);
    if (res.length() == 0)
    {
        return acc;
    }
    else if (res.length() == 1)
    {
        if (res.at(0) == x)
        {
            res.append(q);
        }
        else
        {
            res.append(x);
        }
        this->transformString(res, acc);
    }
    else
    {
        if (res.at(0) == res.at(1))
        {
            if (res.at(0) == x)
            {
                res.insert(1, q);
            }
            else
            {
                res.insert(1, x);
            }
        }
        acc.append(res.first(2));
        this->transformString(res.sliced(2), acc);
    }
    return acc;
}

Playfair::Playfair() {}

void Playfair::generateTable(const QString& key)
{
    this->table = {};
    QString noDup = "";
    const QString keyAbc
        = key + (this->currentAbc == Alphabet::EN ? this->alphabetEn : this->alphabetRu);
    for (QString::const_iterator it = keyAbc.begin(); it != keyAbc.end(); ++it)
    {
        if (!noDup.contains(*it))
        {
            noDup.append(*it);
        }
    }

    for (int i = 0; i < static_cast<int>(this->currentAbc); ++i)
    {
        QString tmp = "";
        for (int j = 0; j < static_cast<int>(this->currentAbc); ++j)
        {
            tmp.append(noDup.at(static_cast<int>(this->currentAbc) * i + j));
        }
        this->table.append(tmp);
    }
}

void Playfair::setCurrentAbc(Alphabet a) { this->currentAbc = a; }

QString Playfair::encrypt(const QString& message)
{
    auto n = QVector<QString>();
    QVector<QString> tmp = this->transformString(message, n);
    QString res = "";

    for (QVector<QString>::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
        res.append(this->encryptPair((*it), [](qsizetype x) { return x + 1; }));
    }
    return res;
}
QString Playfair::decrypt(const QString& message)
{
    auto n = QVector<QString>();
    QVector<QString> tmp = this->transformString(message, n);
    QString res = "";

    for (QVector<QString>::iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
        res.append(this->encryptPair((*it), [](qsizetype x) { return x - 1; }));
    }
    return res;
}
}
