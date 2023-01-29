#include <iostream>

template <typename T> class Vector{
    public:
        Vector(const int newSize); // throws std::out_of_range("Vector")
        ~Vector();
        int size() const { return actualSize; };
        void resize(const int newSize); // throws std::out_of_range("Vector")
        T& at(const int index); // throws std::out_of_range("Vector")
    private:
        T* data;
        int actualSize;
        int capacity;
};

template <typename T>
Vector<T>::Vector(const int newSize)
{
    // prohibit negative sizes
    if (newSize < 0) throw std::out_of_range("Vector");

    data = new T[newSize];

    actualSize = newSize;
    capacity = newSize;
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] data;
}

template <typename T>
void Vector<T>::resize(const int newSize)
{
    if (newSize < 0) throw std::out_of_range("Vector");

    // if the new vector is smaller than the allocated memory, no extra allocation is necessary
    if (newSize < actualSize || (newSize > actualSize && newSize < capacity))
    {
        actualSize = newSize;
        return;
    }

    T *temp = new T[newSize];

    // copy data over
    for (int i = 0; i < actualSize; i++)
        temp[i] = data[i];
    
    // replace old data with new data
    delete[] data;
    data = temp;

    actualSize = newSize;
    capacity = newSize;
}

template <typename T>
T &Vector<T>::at(const int index)
{
    if (index < 0 || index >= actualSize) throw std::out_of_range("Vector");

    return data[index];
}