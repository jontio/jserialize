#include "jserialize.h"
#include <QDebug>

bool JSerialize::fromQByteArray(const QByteArray &ba)
{
    const QMetaObject* metaObj = this->metaObject();
    QDataStream ds(ba);
#ifndef J_SERIALIZE_DROP_CLASSNAME
    QString rxclassName;
    ds>>rxclassName;
    QString className = metaObj->className();
    if(rxclassName!=className)return false;
#endif
    for (int i = 1; i < metaObj->propertyCount(); ++i)
    {
        const char* propertyName = metaObj->property(i).name();
        const QVariant::Type type = metaObj->property(i).type();
        if(type>=QVariant::UserType)
        {
            qDebug()<<"dont know how to deal with this. please help";
            return false;
        }
        QVariant value;
#ifdef J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT
        //exceptions to the QByteArray format
        if(J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT_EXCEPTIONS)
        {
            ds>>value;
        }
        else
        {
            QByteArray ba_tmp;
            ds>>ba_tmp;
            value=ba_tmp;
            value.convert(type);
        }
#else
        ds>>value;
#endif
        if(!value.isValid())
        {
            qDebug()<<"fail fromQByteArray: QVariant not valid";
            return false;
        }
        if(!this->setProperty(propertyName,value))
        {
            qDebug()<<"fail fromQByteArray: failed to set property"<<propertyName<<value;
            return false;
        }
    }
    return true;
}

bool JSerialize::toQByteArray(QByteArray &ba) const
{
    ba.clear();
    const QMetaObject* metaObj = this->metaObject();
    QDataStream ds(&ba,QIODevice::WriteOnly);
#ifndef J_SERIALIZE_DROP_CLASSNAME
    QString className = metaObj->className();
    ds<<className;
#endif
    for (int i = 1; i < metaObj->propertyCount(); ++i)
    {
        const char* propertyName = metaObj->property(i).name();
        const QVariant::Type type = metaObj->property(i).type();
        if(type>=QVariant::UserType)
        {
            qDebug()<<"dont know how to deal with this. please help";
            return false;
        }
        const QVariant value = this->property(propertyName);
        if(!value.isValid())
        {
            qDebug()<<"fail toQByteArray: QVariant not valid";
            return false;
        }
#ifdef J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT
        //exceptions to the QByteArray format
        if(J_SERIALIZE_USE_QBYTEARRAY_AS_FORMAT_EXCEPTIONS)
        {
            ds<<value;
        }
        else
        {
            ds<<value.toByteArray();
        }
#else
        ds<<value;
#endif
    }
    return true;
}

