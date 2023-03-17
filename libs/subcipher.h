#ifndef SUBCIPHER_H
#define SUBCIPHER_H

#include <QString>
#include <QVector>

class SubCipher
{
private:
    QVector<QString> alphabets;

public:
    SubCipher(const QVector<QString>& abc);
    QString encrypt(QString const& message,
                    qsizetype s_func(qsizetype, qsizetype, qsizetype),
                    qsizetype shift = 0);
    QVector<QString> getAlphabets();
};

#endif  // SUBCIPHER_H
