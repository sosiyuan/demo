#include "demo.h"
#include "cstdio"
CDemoBase::CDemoBase() : m_uint16(0)
{
    printf("New CDemoBase %p\n", this);
}

CDemoBase::CDemoBase(unsigned short int val) : m_uint16(val)
{
}

CDemoBase::~CDemoBase()
{
    printf("Delete CDemoBase %p\n", this);
}

CDemoBase2::CDemoBase2() : m_uint16(0)
{
    printf("New CDemoBase2 %p\n", this);
}

CDemoBase2::~CDemoBase2()
{
    printf("Delete CDemoBase2 %p\n", this);
}
