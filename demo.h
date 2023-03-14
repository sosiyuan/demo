#pragma onece
#include "cstdio"

class CDemoBase
{
public:
    CDemoBase();
    CDemoBase(unsigned short int);
    CDemoBase(const CDemoBase &obj) : m_uint16(0) { printf("Cpoy constructor %p \n", this); }
    virtual ~CDemoBase();
    virtual void PrintValue() { printf("0x%04x\n", m_uint16); }
    void func1() { printf("1111"); }
    void func1(int i) { printf("222"); }

protected:
    unsigned short int m_uint16;
};

class CDemoBase2
{
public:
    CDemoBase2();
    virtual ~CDemoBase2();

protected:
    unsigned short int m_uint16;
};

class CDemo2Base
{
public:
    CDemo2Base() { printf("CDemo2Base()\n"); }
    CDemo2Base(unsigned short int i) { printf("CDemo2Base(unsigned short int)\n"); }
    virtual ~CDemo2Base() {}
    void func1() { printf("CDemo2Base::func1()\n"); }
    void func1(int i) { printf("CDemo2Base::func1(int i)\n"); }
    void func2Public(){func2();}
private:
    virtual void func2(){printf("virtual Base\n");}
};

class CDemo2Derive1 : public CDemo2Base
{
public:
    using CDemo2Base::CDemo2Base; // 注释此处时，CDemo2Base(unsigned short int i)会被隐藏，Drived对象无法通过此方式创建对象
    CDemo2Derive1() : CDemo2Base() { printf("CDemoDerive1()\n"); }
    virtual ~CDemo2Derive1(){}

    
    using CDemo2Base::func1; // 注释此处时，void CDemo2Base::func1(int i)会被隐藏，Drived对象无法调用此函数
    void func1() { printf("CDemoDerive1::func1()\n"); }
private:
    virtual void func2(){printf("virtual Derived\n");}
};
