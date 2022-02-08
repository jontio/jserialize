# JSerialize: Simple serialization

Simple serialization of simple type in classes. Useful for saving things to disk and transmitting stuff from one place to another.

# Example

First something to serialize...

```C++
//some class derived from JSerialize
class testclass : public JSerialize
{
    Q_OBJECT
public:
    J_SERIALIZE(int,val2)
    J_SERIALIZE(QString,num,"test")
    J_SERIALIZE(QString,stringProperty)
    J_SERIALIZE(int,val,42)
};
```

Then code to serialize...

```C++
    testclass tc;
    tc.stringProperty="yup";
    tc.val2=112;
    tc.num="numnumnum";
    QByteArray ba=tc;

    //say transmit ba over the net
    //then we can create something
    //that looks like tc on the
    //remote computer. ba is just a
    //a container for bytes.
    qDebug()<<"serialization size is"<<ba.size()<<"bytes\n";

    testclass tc2;
    tc2<<ba;
    qDebug()<<tc2.stringProperty;
    qDebug()<<tc2.val;
    qDebug()<<tc2.val2;
    qDebug()<<tc2.num;
```

output...

```bash
serialization size is 33 bytes

"yup"
42
112
"numnumnum"
```

Jonti 2022
