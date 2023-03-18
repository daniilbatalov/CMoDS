#ifndef TST_VIGENERE_H
#define TST_VIGENERE_H

#include <QObject>
#include <QTest>
#include <memory>

#include "../libs/vigenere.h"

class tst_vigenere : public QObject
{
    Q_OBJECT
public:
    explicit tst_vigenere(QObject *parent = nullptr);

public slots:
    void testConstructor();

private:
    std::unique_ptr<Vigenere::Vigenere> v;
};

#endif // TST_VIGENERE_H
