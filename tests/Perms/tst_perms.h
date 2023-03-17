#ifndef TST_PERMS_H
#define TST_PERMS_H

#include <QObject>
#include <QTest>
#include <QString>
#include <memory>

#include "../../libs/perms.h"

class tst_perms : public QObject
{
    Q_OBJECT

public:
    tst_perms(QObject* parent = nullptr);

public slots:
    void testConstructor();
    void testEncrypt();
    void testDecrypt();
    void testRevString();
    void testGetRev();
    void testCheckPermSyntax();

private:
    std::unique_ptr<Perms::Perms> p;
};

#endif  // TST_PERMS_H
