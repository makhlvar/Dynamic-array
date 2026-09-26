#pragma once
#include <cstddef>

class DynamicArray{
    private:
        int* data_;
        std::size_t data_size_;
    public:

    void show()const;
    DynamicArray(std::size_t size);
    ~DynamicArray();//деструктор
    DynamicArray(const DynamicArray& other);//конструктор копирования 
    void set(std::size_t index, int value);//сеттер
    //
    void push_back(int value);
    int get(std::size_t index) const; //геттер
    //
    void add(const DynamicArray& other);
    void substract(const DynamicArray& other);
};