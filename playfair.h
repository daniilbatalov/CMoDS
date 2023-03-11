#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <QVector>
#include <QString>
#include <QMap>
#include "aux/math_aux.h"

enum Alphabet
{
    INVALID = -1,
    EN,
    RU
};

enum Size
{
    INVALID = -1,
    EN = 5,
    RU = 6
};

class Playfair
{
private:
    QVector<QString> tableRu;
    QVector<QString> tableEn;
    const QString alphabetEn = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    const QString alphabetRu = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ-.,";
    Size currentSize = INVALID;
    Alphabet currentAbc = INVALID;


public:
    Playfair();
    void generateTable(QString const &key);

};

#endif // PLAYFAIR_H
