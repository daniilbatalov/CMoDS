#include "playfair.h"

Playfair::Playfair()
{

}

void Playfair::generateTable(const QString &key)
{
    QString noDup = "";
    QString::const_iterator it = key.begin();
    for (; it != key.end(); ++it)
    {
        if (!noDup.contains(*it))
        {
            noDup.append(*it);
        }
    }

    for (int i = 0; i < this->)
}

