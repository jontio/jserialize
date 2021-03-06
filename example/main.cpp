#include <QCoreApplication>
#include <QDebug>
#include "testclass.h"

void show_data(const testclass &c)
{
    qDebug()<<c.stringProperty;
    qDebug()<<c.val;
    qDebug()<<c.val2;
    qDebug()<<c.num;
    qDebug()<<qSetRealNumberPrecision(16)<<c.dub;
}

int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)

    //load testclass with some data
    testclass tc;
    tc.stringProperty="yup";
    //tc.val is 42 by default if you look in testclass.h
    tc.val2=112;
    tc.num="numnumnum";
    tc.dub=3.14;

    //show user what's going to be serialized
    qDebug()<<"Data to send:";
    show_data(tc);

    //serialize
    QByteArray ba=tc;

    //say transmit ba over the net
    //then we can create something
    //that looks like tc on the
    //remote computer
    qDebug()<<"\nsending"<<ba.size()<<"bytes of data\n";

    //deserialize
    testclass tc2;
    tc2<<ba;

    //show user what's been deserialized
    qDebug()<<"Received data:";
    show_data(tc2);
    qDebug()<<"\n";

    return 0;
}
