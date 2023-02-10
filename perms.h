#ifndef PERMS_H
#define PERMS_H

#include <QVector>

enum PermType
{
    BadPerm,
    BadSyntax,
    LongPerm,
    OK

};

struct ParsedPerm
{
    PermType result;
    QVector<QVector<int>> parsed;
    ParsedPerm(PermType, QVector<QVector<int>>);
    ParsedPerm();
};



class Perms
{
public:
    Perms(ParsedPerm);
    QString encrypt(QString);
    QString decrypt(QString);
    QString revToQString();
    void swap();


private:
    ParsedPerm perm;
    ParsedPerm rev;
    ParsedPerm getReverse(ParsedPerm);
    QString applyOnePerm(QString, QVector<int>);




};

#endif // PERMS_H
