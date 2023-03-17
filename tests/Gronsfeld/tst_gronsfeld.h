#ifndef TST_GRONSFELD_H
#define TST_GRONSFELD_H

#include <QObject>
#include <QTest>
#include <QString>
#include <memory>

#include "../../libs/gronsfeld.h"

class tst_gronsfeld : public QObject
{
    Q_OBJECT

public:
    tst_gronsfeld(QObject* parent = nullptr);

public slots:
    void testConstructor();
    void testKey();
    void testEncrypt();
    void testDecrypt();

private:
    std::unique_ptr<Gronsfeld::Gronsfeld> g;
};

#endif  // TST_GRONSFELD_H
