#include <QtTest>
#include <memory>
#include "Subcipher/tst_subcipher.h"
#include "Perms/tst_perms.h"
#include "Gronsfeld/tst_gronsfeld.h"
#include "MathAux/tst_mathaux.h"
#include "Vigenere/tst_vigenere.h"

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
    void test_mathaux();
    void test_vigenere();

private:
    std::unique_ptr<tst_subcipher> sub_ptr;
    std::unique_ptr<tst_perms> per_ptr;
    std::unique_ptr<tst_gronsfeld> grf_ptr;
    std::unique_ptr<tst_mathaux> mth_ptr;
    std::unique_ptr<tst_vigenere> vgn_ptr;
};

tests::tests()
{
    sub_ptr = std::make_unique<tst_subcipher>(nullptr);
    per_ptr = std::make_unique<tst_perms>(nullptr);
    grf_ptr = std::make_unique<tst_gronsfeld>(nullptr);
    mth_ptr = std::make_unique<tst_mathaux>(nullptr);
    vgn_ptr = std::make_unique<tst_vigenere>(nullptr);
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

void tests::test_mathaux()
{
    mth_ptr->testInt();
    mth_ptr->testLongLong();
}

void tests::test_vigenere()
{
    vgn_ptr->testConstructor();
}

QTEST_APPLESS_MAIN(tests)

#include "tst_tests.moc"
