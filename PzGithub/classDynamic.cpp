#include "classDynamic.h"        // подключаем объявление класса (компилятор должен знать поля и методы)
#include <iostream>             

//            КОНСТРУКТОР
DynamicArray::DynamicArray(std::size_t size)   // определяем конструктор, принимающий размер
    //инициализация в списке присваивания
    : data_(nullptr), data_size_(size)         // поля инициализируются до тела
    //т.е выполняется до тела
    //задаем значение сразу,не инициализируя пустотой
    //в теле конструктора только логика
    //выделение памяти и вычисления
{
    if (size > 0) {                            // если размер больше нуля — нужно выделить память
        data_ = new int[data_size_]();         // new[] выделяет в куче массив; () — зануление всех элементов
    }                                          // если size == 0, data_ остаётся nullptr — пустой массив
}

//          КОНСТРУКТОР КОПИРОВАНИЯ 
DynamicArray::DynamicArray(const DynamicArray& other)   // other — объект, с которого копируем
    : data_(nullptr), data_size_(other.data_size_)      // свой размер берём из other; data_ пока nullptr
{
    if (data_size_ > 0) {                     // если у other есть элементы — копируем
        data_ = new int[data_size_];          // выделяем СВОЮ память (важно: не делим одну с other)
        for (std::size_t i = 0; i < data_size_; ++i) {  // идём по всем элементам
            data_[i] = other.data_[i];        // копируем значение из other по тому же индексу
        }                                     // после цикла у нас независимая копия
    }
}

//               ДЕСТРУКТОР 
DynamicArray::~DynamicArray() {               // вызывается автоматически при уничтожении объекта
    delete[] data_;                           // освобождаем память, выделенную через new[]
}                                             // (delete[] для массивов, а не delete)

//                ВЫВОД 
void DynamicArray::show() const {             // const — метод не меняет поля
    std::cout << "[";                         // открывающая скобка формата
    for (std::size_t i = 0; i < data_size_; ++i) {  // идём по всем элементам
        if (i > 0) std::cout << ", ";         // запятую ставим перед всеми, кроме первого
        std::cout << data_[i];                // выводим значение по индексу i
    }
    std::cout << "]\n";                       // закрывающая скобка и перевод строки
}

//                СЕТТЕР
void DynamicArray::set(std::size_t index, int value) {   // записать value по индексу
    if (index >= data_size_) {                // проверка: индекс внутри [0, data_size_ - 1]
        std::cerr << "set: индекс " << index
                  << " вне границ массива (размер " << data_size_ << ")\n";
        return;                               // выходим, ничего не меняя
    }
    if (value < -100 || value > 100) {        // проверка: значение в диапазоне [-100, 100]
        std::cerr << "set: значение " << value
                  << " вне диапазона [-100, 100]\n";
        return;                               // выходим, ничего не меняя
    }
    data_[index] = value;                     // обе проверки прошли — пишем в приватное поле
}                                             // data_[index] — это *(data_ + index)

//              ГЕТТЕР 
int DynamicArray::get(std::size_t index) const {   // const — только чтение
    if (index >= data_size_) {                // проверка выхода за границы
        std::cerr << "get: индекс " << index
                  << " вне границ массива (размер " << data_size_ << ")\n";
        return 0;                             // возвращаем 0 как безопасное значение
    }
    return data_[index];                      // возвращаем значение по индексу
}

//             PUSH_BACK 
void DynamicArray::push_back(int value) {     // добавить в конец и увеличить размер на 1
    if (value < -100 || value > 100) {        // проверяем диапазон
        std::cerr << "push_back: значение " << value
                  << " вне диапазона [-100, 100]\n";
        return;                               // при ошибке ничего не меняем
    }

    int* new_data = new int[data_size_ + 1];  // выделяем новый массив на 1 больше, не трогая старый
    for (std::size_t i = 0; i < data_size_; ++i) {  // копируем старые элементы
        new_data[i] = data_[i];               // поэлементно
    }
    new_data[data_size_] = value;             // кладём новый элемент в конец (по индексу size)

    delete[] data_;                           // старую память освобождаем
    data_      = new_data;                    // теперь data_ указывает на новый массив
    data_size_ = data_size_ + 1;              // и размер увеличился на 1
}

//                    ADD 
void DynamicArray::add(const DynamicArray& other) {   // *this = *this + other поэлементно
    for (std::size_t i = 0; i < data_size_; ++i) {    // идём ТОЛЬКО по своим элементам (размер *this не меняется)
        int other_value = (i < other.data_size_)      // если у other есть элемент с таким индексом
                            ? other.data_[i]          // берём его
                            : 0;                      // иначе считаем его равным нулю (по ТЗ)
        data_[i] += other_value;                      // прибавляем к своему элементу
    }
}

//                  SUBSTRACT 
void DynamicArray::substract(const DynamicArray& other) {   // *this = *this - other поэлементно
    for (std::size_t i = 0; i < data_size_; ++i) {          // тот же принцип
        int other_value = (i < other.data_size_)            // не хватает элемента у other?
                            ? other.data_[i]                // есть — берём его
                            : 0;                            // нет — считаем нулём
        data_[i] -= other_value;                            // вычитаем из своего элемента
    }
}
