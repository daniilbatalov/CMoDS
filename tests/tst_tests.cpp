#include <QtTest>

#include "Subcipher/tst_subcipher.h"

class tests : public QObject
{
    Q_OBJECT

public:
    tests();
    ~tests();

private slots:
    void test_subcipher();

};

tests::tests()
{

}

tests::~tests()
{

}

void tests::test_subcipher()
{
    tst_subcipher t;
    t.testConstructor();
    t.testEncrypt();
}

QTEST_APPLESS_MAIN(tests)

#include "tst_tests.moc"
