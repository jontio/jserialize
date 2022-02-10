#include "../jserialize.h"

#ifndef JSERIALIZE_TESTS_H
#define JSERIALIZE_TESTS_H

#ifndef UNIT_TESTING
#define UNIT_TESTING
#endif

#include <QSize>

class testclass : public JSerialize
{
    Q_OBJECT
public:
    J_SERIALIZE(double,_double)
    J_SERIALIZE(float,_float)
    J_SERIALIZE(QSize,_qsize)
    J_SERIALIZE(int,_int)
    J_SERIALIZE(QString,_qstring,"test")
    J_SERIALIZE(QStringList,_qstringlist)
    J_SERIALIZE(uchar,_uchar)
    J_SERIALIZE(char,_char,42)
    J_SERIALIZE(quint32, _quint32)
    J_SERIALIZE(QByteArray, _bytearray)
    J_SERIALIZE(bool, _bool)
};

class testemptyclass : public JSerialize
{
    Q_OBJECT
public:
};

#endif /* JSERIALIZE_TESTS_H */


