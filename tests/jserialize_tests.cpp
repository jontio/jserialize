#include "../jserialize.h"
#include "jserialize_tests.h"

#include <stdio.h>
#include <QDebug>

#define RAND_SMALL_INT (qrand()-(RAND_MAX>>1))

//important for Qt include cpputest last as it mucks up new and causes compiling to fail
#include "CppUTest/TestHarness.h"

TEST_GROUP(Test_JSerialize)
{

    //the strange error that cpputest throws of a memory leak when using QFile only happens so far on linux
    void setup()
    {
#ifdef __linux__
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
#endif
    }

    void teardown()
    {
#ifdef __linux__
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
#endif
    }
};

TEST(Test_JSerialize, check_types)
{
    testclass tc,tc2;
    QByteArray ba,ba2;

    for(int k=0;k<10000;k++)
    {

        tc._double=1.123+RAND_SMALL_INT;
        tc._float=-1956546.2668+RAND_SMALL_INT;
        tc._qsize=QSize(RAND_SMALL_INT,RAND_SMALL_INT);
        tc._int=RAND_SMALL_INT;
        tc._qstring="trt";
        tc._qstringlist=QStringList()<<"asdf"<<"asdf"<<"r232";
        tc._uchar=RAND_SMALL_INT;
        tc._char=RAND_SMALL_INT;
        tc._quint32=((quint32)RAND_SMALL_INT)*10000+RAND_SMALL_INT;
        tc._bytearray="jvns9u4ng";
        tc._bool=(RAND_SMALL_INT>0?true:false);

        ba=tc;
        tc2.fromQByteArray(ba);
        ba2=tc2;

        CHECK_TEXT(!tc.hasSerializeError(),"tc has error");
        CHECK_TEXT(!tc2.hasSerializeError(),"tc2 has error");
        bool should_fail=false;
        if(ba!=ba2)
        {
            printf("serialization compare not equal this should fail\n");
            should_fail=true;
        }

        CHECK_TEXT(tc._double==tc2._double,"double");
        CHECK_TEXT(tc._float==tc2._float,"float");
        CHECK_TEXT((tc._qsize.width()==tc2._qsize.width())&&(tc._qsize.height()==tc2._qsize.height()),"qsize");
        CHECK_TEXT(tc._int==tc2._int,"int");
        CHECK_TEXT(tc._uchar==tc2._uchar,"ucar");
        CHECK_TEXT(tc._char==tc2._char,"char");
        CHECK_TEXT(tc._qstring==tc2._qstring,"qstring");
        CHECK_TEXT(tc._qstringlist==tc2._qstringlist,"qstringlist");
        CHECK_TEXT(tc._quint32==tc2._quint32,"quint32");
        CHECK_TEXT(tc._bytearray==tc2._bytearray,"bytearray");

        CHECK_TEXT(!should_fail,"didn't fail as expected so failing now");

    }

//    printf("ba size=%d\n",ba.size());

}

TEST(Test_JSerialize, empty_class)
{
    testemptyclass tc,tc2;
    QByteArray ba,ba2;

    ba=tc.toQByteArray();
    tc2.fromQByteArray(ba);
    ba2=tc2;

    CHECK_TEXT(!tc.hasSerializeError(),"tc has error");
    CHECK_TEXT(!tc2.hasSerializeError(),"tc2 has error");
    CHECK_TEXT(ba==ba2,"serialization compare not equal");
}

TEST(Test_JSerialize, base_class)
{
    JSerialize tc,tc2;
    QByteArray ba,ba2;

    ba=tc.toQByteArray();
    tc2.fromQByteArray(ba);
    ba2=tc2;

    CHECK_TEXT(!tc.hasSerializeError(),"tc has error");
    CHECK_TEXT(!tc2.hasSerializeError(),"tc2 has error");
    CHECK_TEXT(ba==ba2,"serialization compare not equal");
}
