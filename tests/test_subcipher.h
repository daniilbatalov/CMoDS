#ifndef TEST_SUBCIPHER_H
#define TEST_SUBCIPHER_H

#include <QObject>
#include <QtTest>

#include "../subcipher.h"


class test_subcipher : public QObject
{
    Q_OBJECT

public:
    test_subcipher(QObject *parent = nullptr);

private slots:
    void testConstructor();
private:
    SubCipher *s;
};

#endif // TEST_SUBCIPHER_H
