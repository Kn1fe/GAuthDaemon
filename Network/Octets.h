#ifndef OCTETS_H
#define OCTETS_H

#include <QObject>

struct Octets
{
    Octets() {}
    Octets(QByteArray data) : text(data) { lenght = text.length(); }
    uint lenght;
    QByteArray text;
};

#endif // OCTETS_H
