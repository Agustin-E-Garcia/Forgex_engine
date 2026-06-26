#pragma once
#include <vector>

namespace Forgex::DataStructures
{
    template <typename T>
    class RingBuffer
    {
    public:
        RingBuffer() { Reserve(10); }

        void Push(T value)
        {
            m_Data[m_WriteIndex] = value;

            if(m_Count < m_Capacity) m_Count++;
            m_WriteIndex = (m_WriteIndex + 1) % m_Capacity;
        }

        T Get(size_t index) const
        {
            if(index >= m_Count) return T();
            if(m_Count < m_Capacity) return m_Data[index];
            else return m_Data[(m_WriteIndex + index) % m_Capacity];
        }

        std::vector<T> ToVector() const { return m_Data; }

        void Reserve(size_t size)
        {
            m_Data.resize(size);
            m_Capacity = size;
        }

        size_t Size() const { return m_Count; }
        size_t Capacity() const { return m_Capacity; }

        void Clear() { m_Data.clear(); }

    private:
        std::vector<T> m_Data;
        int m_WriteIndex = 0;
        int m_Count = 0;
        int m_Capacity = 10;
    };
}
