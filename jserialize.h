#ifndef JSERIALIZE_H
#define JSERIALIZE_H

/*
 * for easy convertion of variables of classes derived from QObject to QByteArray and back.
 *
 * useful for saving and loading class variables or for transmitting over the net.
 *
 * Example usage:
 *
 * Declare say in testclass.h ...
 *
 * #ifndef TESTCLASS_H
 * #define TESTCLASS_H
 *
 * #include "jserialize.h"
 *
 * class testclass : public JSerialize
 * {
 *     Q_OBJECT
 * public:
 *     J_DECLARE_SERIALIZE
 *     J_SERIALIZE(int,val2)
 *     J_SERIALIZE(QString,num,"test")
 *     J_SERIALIZE(QString,stringProperty)
 *     J_SERIALIZE(int,val,42)
 * };
 *
 * #endif // TESTCLASS_H
 *
 * Then use in somewhere else...
 *
 * #include <QDebug>
 * #include "testclass.h"
 *
 * void test()
 * {
 *     testclass tc;
 *     tc.stringProperty="yup";
 *     QByteArray ba=tc;
 *
 *     //say transmit ba over the net
 *     //then we can create something
 *     //that looks like tc on the
 *     //remote computer
 *
 *     testclass tc2;
 *     tc2<<ba;
 *     qDebug()<<tc2.stringProperty;
 * }
 *
 */

//these defined effect serialization output size
//use J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT with
//cation as it might have issues with some types
//I'll leave it as the default so ppl can
//let me know what ones fail
//NOPE J_SERIALIZE_USE_QBYTEARRAY_AS_FORMA
// really has issues. don't use
//J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT yet. Wait
//#define J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT
#define J_SERIALIZE_DROP_CLASSNAME

//not all types can be converted to QByteArray.
//not sure what ones can but add any that don't
//to this list if you are using the
//J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT define.
//somethings like bool are shorter as a QVariant
//than a QByteArray so might as well add anything
//than makes the size shorter too as that's
//the only reasion for using the
//J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT define
#define J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT_EXCEPTIONS (\
    (type==QVariant::StringList)    ||\
    (type==QVariant::Map)           ||\
    (type==QVariant::Hash)          ||\
    (type==QVariant::Bool)\
    )\

#include <QObject>
#include <QDataStream>
#include <QMetaProperty>
#include <QByteArray>

#define GET_SERIALIZE_MACRO(_1,_2,_3,NAME,...) NAME
#define J_SERIALIZE(...) GET_SERIALIZE_MACRO(__VA_ARGS__, J_SERIALIZE_3, J_SERIALIZE_2)(__VA_ARGS__)

#define J_SERIALIZE_3(type, val, init_val)\
    Q_PROPERTY(type val MEMBER val)\
    type val=init_val;\

#define J_SERIALIZE_2(type, val)\
    Q_PROPERTY(type val MEMBER val)\
    type val;\

class JSerialize : public QObject
{
    Q_OBJECT
public:
    explicit JSerialize(QObject *parent=nullptr) : QObject(parent){}
    JSerialize(const JSerialize &other) : QObject()
    {
        if(this == &other) return;
        other.toQByteArray(ba);
        this->fromQByteArray(ba);
    }
    virtual ~JSerialize(){}

    Q_INVOKABLE bool fromQByteArray(const QByteArray &ba);
    Q_INVOKABLE bool toQByteArray(QByteArray &ba) const;

    //convinience
    const QByteArray& toQByteArray()
    {
        toQByteArray(ba);
        return ba;
    }
    operator const QByteArray & ()
    {
        return toQByteArray();
    }
    JSerialize& operator =(const JSerialize& other)
    {
        if(this == &other) return *this;
        other.toQByteArray(ba);
        fromQByteArray(ba);
        return *this;
    }

    //QDataStream serialization
    friend QDataStream &operator<<(QDataStream &s, const JSerialize &val)
    {
        QByteArray ba;
        val.toQByteArray(ba);
        s<<ba;
        return s;
    }
    friend QDataStream &operator>>(QDataStream &s, JSerialize &val)
    {
        QByteArray ba;
        s>>ba;
        val.fromQByteArray(ba);
        return s;
    }

    //QByteArray serialization
    friend JSerialize &operator<<(JSerialize &s, const QByteArray &val)
    {
        s.fromQByteArray(val);
        return s;
    }
    friend JSerialize &operator>>(JSerialize &s, QByteArray &val)
    {
        s.toQByteArray(val);
        return s;
    }


private:
    QByteArray ba;
};

Q_DECLARE_METATYPE(JSerialize)



#endif // JSERIALIZE_H
