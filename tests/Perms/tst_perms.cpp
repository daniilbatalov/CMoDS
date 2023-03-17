#include "tst_perms.h"

Q_DECLARE_METATYPE(Perms::ParsedPerm)

tst_perms::tst_perms(QObject* parent)
: QObject{ parent }
{
}

void tst_perms::testConstructor()
{
    const Perms::ParsedPerm perm
        = Perms::ParsedPerm(Perms::PermType::OK, { { 2, 3, 1 }, { 1, 3, 2 } });
    p = std::make_unique<Perms::Perms>(perm);
    QCOMPARE(p->getPerm(), perm);
}

void tst_perms::testEncrypt()
{
    QCOMPARE(p->encrypt("ABC DE"), "BCA ED");
    QCOMPARE(p->encrypt("ABC DE123"), "BCA ED123");
}

void tst_perms::testDecrypt()
{
    QCOMPARE(p->decrypt("BCA ED"), "ABC DE");
    QCOMPARE(p->decrypt("BCA ED123"), "ABC DE123");
}

void tst_perms::testRevString() { QCOMPARE(p->revToQString(), "(3 1 2)(1 3 2)"); }

void tst_perms::testGetRev()
{
    const Perms::ParsedPerm revperm
        = Perms::ParsedPerm(Perms::PermType::OK, { { 3, 1, 2 }, { 1, 3, 2 } });
    QCOMPARE(p->getRevPerm(), revperm);
}

void tst_perms::testCheckPermSyntax()
{
    const Perms::ParsedPerm badperm = Perms::ParsedPerm(Perms::PermType::BadPerm, {});
    const Perms::ParsedPerm badsyntax = Perms::ParsedPerm(Perms::PermType::BadSyntax, {});
    const Perms::ParsedPerm longperm = Perms::ParsedPerm(Perms::PermType::LongPerm, {});
    const Perms::ParsedPerm okperm = Perms::ParsedPerm(Perms::PermType::OK, { { 4, 2, 3, 1 } });

    QVERIFY2(Perms::Perms::checkPermutationSyntax("(4 2 1)", "abc") == badperm,
             qPrintable(QString("BadPerm test failure")));
    QVERIFY2(Perms::Perms::checkPermutationSyntax("(1 2 a)", "abc") == badsyntax,
             qPrintable(QString("BadSyntax test failure")));
    QVERIFY2(Perms::Perms::checkPermutationSyntax("(4 2 3 1)", "abc") == longperm,
             qPrintable(QString("LongPerm test failure")));
    QVERIFY2(Perms::Perms::checkPermutationSyntax("(4 2 3 1)", "abcd") == okperm,
             qPrintable(QString("OK test failure")));
}
