#include <iostream>


/*
    The order of constructor calling in inheritance
*/

// class A {
// public:
//     A() { std::cout << "Constructor A" << std::endl; }
//     ~A() { std::cout << "Destructor B" << std::endl; }
// };

// class B {
// public:
//     B() { std::cout << "Constructor B" << std::endl; }
//     ~B() { std::cout << "Destructor B" << std::endl; }
// };

// class C : public B, public A {
// public:
//     C() { std::cout << "Constructor C" << std::endl; }
//     ~C() { std::cout << "Destructor C" << std::endl; }
// };

/*
 * The non-static member will be initialized first even though the order of the initialization list  
*/

// class B 
// {
// public:
//     B() { std::cout << "Constructor B" << std::endl; }
//     ~B() { std::cout << "Destructor B" << std::endl; }
//     void test() {
//         std::cout << a << std::endl;
//     }
//     int a;
// };

// class A 
// {
// public:
//     A(B* b){
//         std::cout << "Contructor A" << std::endl;
//         b->test();
//     }
// };

// class C {
// public:
//     C() : a(new A(b)), b(new B()) { std::cout << "Contructor C" << std::endl; }
//     A* a = nullptr;
//     B* b = nullptr;
// };

class A {
public:
    A() = delete;
    A(int a) {
        std::cout << "Param Constructor A" << std::endl;
    }
    
}

int main() 
{
    C c;
}