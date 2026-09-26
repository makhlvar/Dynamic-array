#include <iostream>
#include "classDynamic.h"

int main() {
    //    демонстрация конструктора и show()
    DynamicArray a(5);                    // массив из 5 нулей
    std::cout << "a: "; a.show();

    //    демонстрация set()
    a.set(0, 10);                         // ок
    a.set(1, -50);                        // ок
    a.set(2, 200);                        // ошибка диапазона
    a.set(99, 5);                         // ошибка индекса
    std::cout << "a после set: "; a.show();

    //   демонстрация get()
    std::cout << "get(0) = " << a.get(0) << "\n";    // 10
    std::cout << "get(99) = " << a.get(99) << " (ошибка)\n";

    //   демонстрация конструктора копирования
    DynamicArray b = a;                   // глубокая копия
    //т.е. создаётся новая независимая память куда
    //копируются все данный
    b.set(0, 99);                         // меняем b
    std::cout << "a: "; a.show();         // a не изменился
    std::cout << "b: "; b.show();         // b изменился

    //   демонстрация push_back
    a.push_back(7);                       // размер стал 6
    a.push_back(500);                     // ошибка диапазона
    std::cout << "a после push_back(7): "; a.show();

    //   демонстрация add
    DynamicArray x(3);
    x.set(0, 1); x.set(1, 2); x.set(2, 3);
    DynamicArray y(5);
    y.set(0, 10); y.set(1, 20); y.set(2, 30); y.set(3, 40); y.set(4, 50);

    DynamicArray s = x;                   // копия x
    s.add(y);                             // x + y (недостающие элементы y считаются 0)
    std::cout << "x + y: "; s.show();

    //   демонстрация substract
    DynamicArray d = y;                   // копия y
    d.substract(x);                       // y - x
    std::cout << "y - x: "; d.show();

    return 0;                             // при выходе вызовутся деструкторы, память освободится
}