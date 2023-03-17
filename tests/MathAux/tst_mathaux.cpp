#include "tst_mathaux.h"

tst_mathaux::tst_mathaux(QObject* parent)
: QObject{ parent }
{
}

void tst_mathaux::testInt()
{
    QCOMPARE(MathAux::euclidean_remainder<int>(5, 3), 2);
    QCOMPARE(MathAux::euclidean_remainder<int>(-5, 3), 1);
    QCOMPARE(MathAux::euclidean_remainder<int>(-5, -3), 1);
    QCOMPARE(MathAux::euclidean_remainder<int>(5, -3), 2);
}

void tst_mathaux::testLongLong()
{
    QCOMPARE(MathAux::euclidean_remainder<long long>(9223372036854775803LL, 4523333036854775806LL),
            176705963145224191LL);
    QCOMPARE(MathAux::euclidean_remainder<long long>(-9223372036854775803LL, 4523333036854775806LL),
            4346627073709551615LL);
    QCOMPARE(MathAux::euclidean_remainder<long long>(-9223372036854775803LL, -4523333036854775806LL),
            4346627073709551615LL);
    QCOMPARE(MathAux::euclidean_remainder<long long>(9223372036854775803LL, -4523333036854775806LL),
            176705963145224191LL);
}
