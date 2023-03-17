#ifndef TST_SUBCIPHER_H
#define TST_SUBCIPHER_H

#include <QObject>
#include <QTest>
#include "../../libs/subcipher.h"

class tst_subcipher : public QObject
{
    Q_OBJECT

public:
    tst_subcipher(QObject* parent = nullptr);

public slots:
    void testConstructor();
    void testEncrypt();

private:
    std::unique_ptr<SubCipher> s;
};

#endif  // TST_SUBCIPHER_H
