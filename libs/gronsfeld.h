#ifndef GRONSFELD_H
#define GRONSFELD_H

#include <QVector>
#include <QString>

#include "aux/math_aux.h"

namespace Gronsfeld
{

enum class KeyMode
{
    GREEDY,
    LAZY
};

class Gronsfeld
{
public:
    Gronsfeld(const QVector<QString>& abc);
    QString encrypt(const QString& message, qsizetype func(qsizetype, qsizetype));
    void setKey(const QString& k);
    void setKeyMode(const KeyMode k);

private:
    QVector<QString> alphabet;
    QChar shift(const QChar c, const qsizetype sh, qsizetype func(qsizetype, qsizetype));
    QString expand_key(const qsizetype size);
    QString key;
    KeyMode key_mode = KeyMode::GREEDY;
};
}
#endif  // GRONSFELD_H
