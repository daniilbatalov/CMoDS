#ifndef SUBCIPHER_H
#define SUBCIPHER_H

#include <QString>
#include <QVector>

class SubCipher
{
private:
    QVector<QString> alphabets;
public:
    SubCipher(QVector<QString> const &abc);
    QString encrypt(QString const &message, int s_func(int, int, int), int shift = 0);
};

#endif // SUBCIPHER_H
