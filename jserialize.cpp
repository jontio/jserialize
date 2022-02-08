#include "jserialize.h"
#include <QDebug>

bool JSerialize::fromQByteArray(const QByteArray &ba)
{
    const QMetaObject* metaObj = this->metaObject();
    QString rxclassName;
    QDataStream ds(ba);
    ds>>rxclassName;
    QString className = metaObj->className();
    if(rxclassName!=className)return false;
    for (int i = 1; i < metaObj->propertyCount(); ++i)
    {
        const char* propertyName = metaObj->property(i).name();
        const QVariant::Type type = metaObj->property(i).type();
        if(type>=QVariant::UserType)
        {
            qFatal("dont know how to deal with this. please help");
            continue;
        }
        QVariant value;
        ds>>value;
        if(!value.isValid())
        {
            qDebug()<<"fail fromQByteArray: QVariant not valid";
            return false;
        }
        if(!this->setProperty(propertyName,value))
        {
            qDebug()<<"fail fromQByteArray: failed to set property";
            return false;
        }
    }
    return true;
}

bool JSerialize::toQByteArray(QByteArray &ba) const
{
    ba.clear();
    const QMetaObject* metaObj = this->metaObject();
    QString className = metaObj->className();
    QDataStream ds(&ba,QIODevice::WriteOnly);
    ds<<className;
    for (int i = 1; i < metaObj->propertyCount(); ++i)
    {
        const char* propertyName = metaObj->property(i).name();
        const QVariant::Type type = metaObj->property(i).type();
        if(type>=QVariant::UserType)
        {
            qFatal("dont know how to deal with this. please help");
            continue;
        }
        const QVariant value = this->property(propertyName);
        if(!value.isValid())
        {
            qDebug()<<"fail toQByteArray: QVariant not valid";
            return false;
        }
        ds<<value;
    }
    return true;
}

