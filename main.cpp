#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

//lvaule rvaule ссылки и универсальные ссылки
//copi-swap принцип


/*class A {

public:
    void foo() const {
        std::cout << "A::foo() const\n";
    }
    void foo() {
        std::cout << "A::foo()\n";
    }
};

A aFunc() { 
    return A(); 
}
const A c_aFunc() { 
    return A(); 
}

int main() {

    aFunc().foo();
    c_aFunc().foo();
}*/


/*int foo() {
    return 2;
}

int globalvaulue = 20;
int& bar() {//lvaule
    return globalvaulue;
}

int main()
{
    int x = 5;
   // foo() = 2; // ошибка
    bar() = 10;
    //lvaule - объект который занимает идентифицированное место в памяти, например имеет адрес
    //rvaule - объект который не занимает идентифицированное место в памяти, например имеет адрес
    std::map<int, float> mymap;
    mymap[10] = 5.6f;

    const int a = 10;
    //a = 11; // не работает

    int t = 1;
    int tt = 2;
    int res = t + tt;  //не явное преобразование lvaule в rvaule. обратного преобразования быть не может (явно можно)

    int arr[] = { 1,2 };
    int *p = &arr[0];
    *(p + 1) = 10; // rvaule явное преобразование (р+1) в lvaule с помощью *(p + 1) - lvaule

    //lvaule в rvaule с помощью &
    int var = 10;
   // int*dab_addr = &(var+1);  // ошибка - для унарного оператора & требуется lvaule
    int* addr = &var; //ok
   // &var = 40; // ошибка с левой стороны требуется lvaule


    // lvaule на тип Т, не являющемся функциональным или массивом, может быть преобразован в rvaule. Если Т не класс, типом rvaule
    //  является сv-неспецифированная версия типа Т. Иначе, типом rvaule является Т

    // cv: c - const, v -volatile
    // T lvaule -> T rvaule
    // const volatile T lvaule -> T rvaule
    // Если Т это класс, то rvaule может сохранить cv-специфированность

    std::cout << "Hello World!\n";
}*/


class Intvec {
public:
    explicit Intvec(size_t num = 0) : m_size(num), m_data(new int[m_size]) {
        log("constructor");
    }
    ~Intvec() {
        log("destructor");
        if (m_data) {
            delete[] m_data;
            m_data = nullptr;
        }
    }
    Intvec(const Intvec& other) : m_size(other.m_size),
        m_data(new int[m_size]) {
        log("copy constructor");
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }

    Intvec& operator=(Intvec&& other) noexcept { // &&- ссылка на rvalue или универсальная ссылка
        //оператор присваивания перемещением
        log("move assignment operator");
        std::swap(m_size, other.m_size);
        std::swap(m_data, other.m_data);
        return *this;
    }

    Intvec& operator=(const Intvec& other) {
        //оператор присваивания копированием
        log("copy assignment operator");
        Intvec tmp(other);
        std::swap(m_size, tmp.m_size); //меняет местами m c tmp т.е. копирует tmp в m
        std::swap(m_data, tmp.m_data);
        return *this;
    }
private:
    void log(const char* msg) {
        std::cout << "[" << this << "]" << msg << "\n";
    }
    size_t m_size;
    int* m_data;
};

int main() {
    Intvec v1(20);
    Intvec v2;
    Intvec v3;

    std::cout << "assigning lvalue...\n";
    v2 = v1;
    std::cout << "ended assigning lvalue...\n";
    std::cout << "==============================\n";
    std::cout << "assigning rvalue...\n";
    v3 = Intvec(33);
    v3 = std::move(v1); //std::move lvalue в rvalue, v3.operator=(std::move(v1))
    std::cout << "ended assigning lvalue...\n";
}