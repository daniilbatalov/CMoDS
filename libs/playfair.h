#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <QVector>
#include <QString>
#include <QPair>
#include <QRegularExpression>

#include "aux/math_aux.h"

namespace Playfair
{

enum class Alphabet
{
    INVALID = -1,
    EN = 5,
    RU
};


class Playfair
{
private:
    QVector<QString> table;
    const QString alphabetEn = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    const QString alphabetRu = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ-.,";
    Alphabet currentAbc = Alphabet::INVALID;
    QString encryptPair(const QString& pair, qsizetype func(qsizetype));
    QPair<qsizetype, qsizetype> find(const QChar ch);
    QVector<QString> transformString(const QString& message, QVector<QString>& acc);


public:
    Playfair();
    void generateTable(const QString& key);
    void setCurrentAbc(Alphabet a);
    QString encrypt(const QString& message);
    QString decrypt(const QString& message);
};
}
#endif  // PLAYFAIR_H
