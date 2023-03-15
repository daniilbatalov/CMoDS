#ifndef PERMS_H
#define PERMS_H

#include <QVector>
#include <QRegularExpression>

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
    ParsedPerm(PermType, const QVector<QVector<int>> &);
    ParsedPerm();
    friend bool operator==(const ParsedPerm& lhs, const ParsedPerm& rhs);
};



class Perms
{
public:
    Perms(const ParsedPerm &);
    QString encrypt(const QString &);
    QString decrypt(const QString &);
    QString revToQString();
    void swap();
    ParsedPerm getPerm();
    ParsedPerm getRevPerm();
    static ParsedPerm checkPermutationSyntax(const QString &perm, const QString &message);


private:
    ParsedPerm perm;
    ParsedPerm rev;
    ParsedPerm getReverse(const ParsedPerm&);
    QString applyOnePerm(const QString &, const QVector<int> &);




};

#endif // PERMS_H
