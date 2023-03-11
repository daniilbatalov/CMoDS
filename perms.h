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
    ParsedPerm(PermType, QVector<QVector<int>> const&);
    ParsedPerm();
};



class Perms
{
public:
    Perms(ParsedPerm const&);
    QString encrypt(QString const&);
    QString decrypt(QString const&);
    QString revToQString();
    void swap();


private:
    ParsedPerm perm;
    ParsedPerm rev;
    ParsedPerm getReverse(ParsedPerm const&);
    QString applyOnePerm(QString const&, QVector<int> const&);




};

#endif // PERMS_H
