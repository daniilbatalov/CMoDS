#ifndef PERMS_H
#define PERMS_H

#include <QVector>
#include <QRegularExpression>

namespace Perms
{

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
        static ParsedPerm checkPermutationSyntax(const QString &perm, const QString &message);

    private:
        ParsedPerm perm;
        ParsedPerm rev;
        ParsedPerm getReverse(const ParsedPerm &);
        QString applyOnePerm(const QString &, const QVector<int> &);

    };
}
#endif // PERMS_H
