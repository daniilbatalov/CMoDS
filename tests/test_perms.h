#ifndef TEST_PERMS_H
#define TEST_PERMS_H

#include <QObject>
#include <QtTest>
#include "../perms.h"

class test_perms : public QObject
{
    Q_OBJECT
public:
    explicit test_perms(QObject *parent = nullptr);

private slots:
    void testConstructor();
    void testEncrypt();
    void testGetRevQString();
    void testDecrypt();
    void testSwap();
    void testGetRevPerm();

private:
    Perms::Perms *p;

};

#endif // TEST_PERMS_H
