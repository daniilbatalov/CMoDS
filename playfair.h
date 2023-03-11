#ifndef PLAYFAIR_H
#define PLAYFAIR_H

#include <QVector>
#include <QString>
#include "aux/math_aux.h"

enum Alphabet
{
    INVALID = -1,
    EN,
    RU
};

class Playfair
{
private:
    QVector<QString> tableRu;
    QVector<QString> tableEn;
    const QString alphabetEn = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    const QString alphabetRu = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ-.,";
    const int EN_SIZE = 5;
    const int RU_SIZE = 6;
    Alphabet currentAbc = INVALID;


public:
    Playfair();
    void generateTable(QString const &message);

};

#endif // PLAYFAIR_H
