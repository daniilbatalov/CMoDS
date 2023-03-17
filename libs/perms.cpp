#include "perms.h"

namespace Perms
{

    ParsedPerm::ParsedPerm(PermType r,  const QVector<QVector<int>> &p)
    {
        this->result = r;
        this->parsed = p;
    }

    ParsedPerm::ParsedPerm()
    {

    }

    bool operator==(const ParsedPerm &lhs, const ParsedPerm &rhs)
    {
        return ((lhs.result == rhs.result) && (lhs.parsed == rhs.parsed));
    }

    Perms::Perms(ParsedPerm const &p)
    {
        this->perm = p;
        this->rev = getReverse(p);
    }

    QString Perms::encrypt(QString const &message)
    {
        QVector<QVector<int>>::iterator it = this->perm.parsed.begin();
        int pos = 0;
        QString res = "";
        for (; it != this->perm.parsed.end(); it++)
        {
            res += this->applyOnePerm(message.mid(pos, (*it).length()), *it);
            pos += (*it).length();
        }
        res += message.mid(pos);
        return res;
    }

    QString Perms::decrypt(QString const &message)
    {
        QVector<QVector<int>>::iterator it = this->rev.parsed.begin();
        int pos = 0;
        QString res = "";
        for (; it != this->rev.parsed.end(); it++)
        {
            res += this->applyOnePerm(message.mid(pos, (*it).length()), *it);
            pos += (*it).length();
        }
        res += message.mid(pos);
        return res;
    }

    ParsedPerm Perms::getReverse(ParsedPerm const &p)
    {
        QVector<QVector<int>> res;
        QVector<QVector<int>>::const_iterator it = p.parsed.begin();
        for (; it != p.parsed.end(); it++)
        {
            QVector<int> subres = QVector<int>((*it).length());
            for (int i = 0; i < (*it).length(); i++)
            {
                int ind = (*it).at(i) - 1;
                subres[ind] = i + 1;
            }
            res.append(subres);
        }
        return ParsedPerm(p.result, res);
    }

    QString Perms::applyOnePerm(QString const &message, QVector<int> const &perm)
    {
        QString res = "";
        QVector<int>::const_iterator it = perm.begin();
        for (; it != perm.end(); it++)
        {
            res += message.at((*it) - 1);
        }
        return res;
    }

    QString Perms::revToQString()
    {
        QString res = "(";
        QVector<QVector<int>>::iterator it = this->rev.parsed.begin();
        for (; it != this->rev.parsed.end(); it++)
        {
            QVector<int>::iterator sub_it = (*it).begin();
            for (; sub_it != (*it).end(); sub_it++)
            {
                res += QString::number(*sub_it);
                res += " ";
            }
            res = res.first(res.length() - 1);
            res += ")(";
        }
        res = res.first(res.length() - 1);
        return res;
    }

    void Perms::swap()
    {
        ParsedPerm temp = this->perm;
        this->perm = this->rev;
        this->rev = temp;
    }

    ParsedPerm Perms::getPerm()
    {
        return this->perm;
    }

    ParsedPerm Perms::getRevPerm()
    {
        return this->rev;
    }

    ParsedPerm Perms::checkPermutationSyntax(QString const &perm, QString const &message)
    {
        static QRegularExpression re(R"((\((\d+\s)*\d+\))+)");
        if (re.match(perm).capturedLength() != perm.length())
        {
            return ParsedPerm(BadSyntax, QVector<QVector<int>>());
        }
        else
        {
            QVector<QVector<int>> res;
            QVector<QString> tokenized = perm.mid(1, perm.length() - 2).split(")(");
            QVector<QString>::iterator it = tokenized.begin();
            int count = 0;
            for(; it != tokenized.end(); it++)
            {
                QVector<int> result;
                QVector<QString> r = (*it).split(" ");
                QVector<bool> visited = QVector<bool>(r.length());
                for(QVector<QString>::iterator i = r.begin(); i != r.end(); ++i)
                {
                    if ((*i).toInt() > r.length() || (*i).toInt() < 1)
                    {
                        return ParsedPerm(BadPerm, QVector<QVector<int>>());
                    }
                    else
                    {
                        result.append((*i).toInt());
                        visited[(*i).toInt() - 1] = true;
                        count++;
                    }
                }
                if (visited.contains(false))
                    return ParsedPerm(BadPerm, QVector<QVector<int>>());
                else
                    res.append(result);

            }
            if (count > message.length())
                return ParsedPerm(LongPerm, QVector<QVector<int>>());
            else
                return ParsedPerm(OK, res);
        }
    }
}
