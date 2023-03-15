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
    QString encrypt(QString const &message, qsizetype s_func(qsizetype, qsizetype, qsizetype), qsizetype shift = 0);
};

#endif // SUBCIPHER_H
