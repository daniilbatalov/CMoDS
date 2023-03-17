#ifndef TST_MATHAUX_H
#define TST_MATHAUX_H

#include <QObject>
#include <QTest>

#include "../../libs/aux/math_aux.h"

class tst_mathaux : public QObject
{
    Q_OBJECT
public:
    explicit tst_mathaux(QObject* parent = nullptr);
public slots:
    void testInt();
    void testLongLong();
};

#endif  // TST_MATHAUX_H
