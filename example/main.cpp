#include <QCoreApplication>
#include <QDebug>
#include "testclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testclass tc;
    tc.stringProperty="yup";
//    tc.val=34234; //default is 42
    tc.val2=112;
    tc.num="numnumnum";
    QByteArray ba=tc;

    //say transmit ba over the net
    //then we can create something
    //that looks like tc on the
    //remote computer

    testclass tc2;
    tc2<<ba;
    qDebug()<<tc2.stringProperty;
    qDebug()<<tc2.val;
    qDebug()<<tc2.val2;
    qDebug()<<tc2.num;

    return a.exec();
}
