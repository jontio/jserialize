#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "../jserialize.h"

//some class derived from JSerialize
class testclass : public JSerialize
{
    Q_OBJECT
public:
//    J_SERIALIZE(double,dub)
    double dub;
    J_SERIALIZE(int,val2)
    J_SERIALIZE(QString,num,"test")
    J_SERIALIZE(QString,stringProperty)
    J_SERIALIZE(int,val,42)
};

#endif // TESTCLASS_H
