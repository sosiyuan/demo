#ifndef DEMO_3_H
#define DEMO_3_H
#include <iostream>

#ifndef SELF_TEST
#define SELF_TEST 1
#endif
template <class T>
class MyArray
{
public:
    // 自定动态数组（演示用）
    MyArray(unsigned int size, T val = 0) : m_size(size), m_data(new T[size])
    {
        for (unsigned int i = 0; i < m_size; ++i)
        {
            m_data[i] = val;
        }
    }
    ~MyArray(){
        std::cout<<"die"<<std::endl;
        delete[] m_data;
    }
    T *GetData() const { return m_data; }
    unsigned int GetDataSize() const { return m_size; }
    void ShowAllData()
    {
        for (unsigned int i = 0; i < m_size; ++i)
        {
            std::cout << i << " : " << m_data[i] << std::endl;
        }
    }

private:
    T *m_data;
    unsigned int m_size;
};

#endif // DEMO_3_H