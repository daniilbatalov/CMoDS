#include <QtTest>
#include <memory>
#include "Subcipher/tst_subcipher.h"
#include "Perms/tst_perms.h"
#include "Gronsfeld/tst_gronsfeld.h"

class tests : public QObject
{
    Q_OBJECT

public:
    tests();
    ~tests();

private slots:
    void test_subcipher();
    void test_perms();
    void test_gronsfeld();

private:
    std::unique_ptr<tst_subcipher> sub_ptr;
    std::unique_ptr<tst_perms> per_ptr;
    std::unique_ptr<tst_gronsfeld> grf_ptr;
};

tests::tests()
{
    sub_ptr = std::make_unique<tst_subcipher>(nullptr);
    per_ptr = std::make_unique<tst_perms>(nullptr);
    grf_ptr = std::make_unique<tst_gronsfeld>(nullptr);
}

tests::~tests() {}

void tests::test_subcipher()
{
    sub_ptr->testConstructor();
    sub_ptr->testEncrypt();
}

void tests::test_perms()
{
    per_ptr->testConstructor();
    per_ptr->testEncrypt();
    per_ptr->testDecrypt();
    per_ptr->testRevString();
    per_ptr->testGetRev();
    per_ptr->testCheckPermSyntax();
}

void tests::test_gronsfeld()
{
    grf_ptr->testConstructor();
    grf_ptr->testKey();
    grf_ptr->testEncrypt();
    grf_ptr->testDecrypt();
}

QTEST_APPLESS_MAIN(tests)

#include "tst_tests.moc"
