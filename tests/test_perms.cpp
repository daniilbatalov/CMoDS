#include "test_perms.h"

test_perms::test_perms(QObject *parent) : QObject{parent}
{

}

void test_perms::testConstructor()
{
    const Perms::ParsedPerm perm = Perms::ParsedPerm(Perms::PermType::OK, {{2, 3, 1},{1, 3, 2}});
    this->p = new Perms::Perms(perm);
    QCOMPARE(this->p->getPerm(), perm);
}

void test_perms::testEncrypt()
{

}

void test_perms::testGetRevQString()
{

}

void test_perms::testDecrypt()
{

}

void test_perms::testSwap()
{

}

void test_perms::testGetRevPerm()
{
    const Perms::ParsedPerm revperm = Perms::ParsedPerm(Perms::PermType::OK, {{3, 1, 2},{1, 3, 2}});
    QCOMPARE(this->p->getRevPerm(), revperm);
}


QTEST_GUILESS_MAIN(test_perms)
