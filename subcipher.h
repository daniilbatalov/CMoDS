#ifndef SUBCIPHER_H
#define SUBCIPHER_H

#include <QString>
#include <QVector>

class SubCipher
{
private:
    QVector<QString> alphabets;
public:
    SubCipher(const QVector<QString> &abc);
    QString encrypt(const QString &message, int s_func(int, int, int), int shift = 0);
    QVector<QString> getAlphabets();
};

#endif // SUBCIPHER_H
