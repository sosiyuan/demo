#include "demo.h"
#include <iostream>
#include <cstdio>
#include <iosfwd>
#include <tr1/functional>
class CDemo3 : public CDemoBase
{

public:
    CDemo3() : CDemoBase() { printf("New CDemo Dervie %p\n", this); }
    CDemo3(unsigned short int val) : CDemoBase(val) { printf("New CDemo Dervie %p. val:0x%04x\n", this, val); }
    virtual ~CDemo3() { printf("Delete CDemo Derive %p\n", this); }
    virtual void PrintValue() override{
        printf("Derived print : 0x%04x\n",m_uint16);
        printf("[Base]");
        CDemoBase::PrintValue();
        // printf("[Base Point Cast]");
        // CDemoBase* p = this;
        // p->PrintValue();
        printf("[Base Obj Cast]");
        static_cast<CDemoBase>(*this).PrintValue();  
    }
    // virtual void func() override final{}
};

class DemoBase39
{
public:
    void publicFunc() { printf("%s \n", __FUNCTION__); }

protected:
    void protectedFunc() { printf("%s \n", __FUNCTION__); }

private:
    void privateFunc() { printf("%s \n", __FUNCTION__); }
};

class Demo39Derived : private DemoBase39
{
public:
    void demoFunc()
    {
        DemoBase39::publicFunc();
        publicFunc();
        DemoBase39::protectedFunc();
        protectedFunc();
        DemoBase39::privateFunc(); // 无法访问
        privateFunc(); // 无法访问
    }
};

int main(int, char **)
{
    Demo39Derived().demoFunc();
    Demo39Derived().publicFunc(); // 无法访问
}
