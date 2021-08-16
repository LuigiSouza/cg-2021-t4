#ifndef __DINAMIC_ARRAY_H__
#define __DINAMIC_ARRAY_H__

template <class T>
class DinamicArray
{
private:
    T *array;
    int limit;
    int size;

    void resize();

public:
    void add(T x);
    T *get(int i);
    int get_size();
    int get_limit();

    DinamicArray(int size);
    ~DinamicArray();
};

template <class T>
void DinamicArray<T>::resize(void)
{
    int new_size = (int)(size * 1.5);
    T *new_arry = new T[new_size];

    memcpy(new_arry, this->array, size * sizeof(T));

    limit = new_size;
    delete[] this->array;
    this->array = new_arry;
}

template <class T>
void DinamicArray<T>::add(T x)
{
    if (size == limit)
    {
        this->resize();
    }
    array[size++] = x;
}

template <class T>
T *DinamicArray<T>::get(int i)
{
    return &array[i];
}

template <class T>
int DinamicArray<T>::get_size(void)
{
    return size;
}

template <class T>
int DinamicArray<T>::get_limit(void)
{
    return limit;
}

template <class T>
DinamicArray<T>::DinamicArray(int size)
{
    array = new T[size];
    this->limit = size;
    this->size = 0;
}

template <class T>
DinamicArray<T>::~DinamicArray(void)
{
    delete array;
}

#endif
