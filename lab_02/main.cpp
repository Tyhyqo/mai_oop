#include <iostream>
#include "include/thirteen.h"

int main()
{
    Thirteen num1;
    std::cout << "Default constructor (num1): ";
    num1.print(std::cout);
    std::cout << std::endl;

    Thirteen num2(5, 'A');
    std::cout << "Fill constructor (num2): ";
    num2.print(std::cout);
    std::cout << std::endl;

    Thirteen num3({'1', 'A', '2'});
    std::cout << "Initializer list constructor (num3): ";
    num3.print(std::cout);
    std::cout << std::endl;

    Thirteen num4("B3");
    std::cout << "Copy string constructor (num4): ";
    num4.print(std::cout);
    std::cout << std::endl;

    Thirteen num5(num4);
    std::cout << "Copy constructor (num5): ";
    num5.print(std::cout);
    std::cout << std::endl;

    Thirteen num6(std::move(num5));
    std::cout << "Move constructor(num6): ";
    num6.print(std::cout);
    std::cout << std::endl;

    Thirteen sum = num2.add(num3);
    std::cout << "Addition (num2 + num3): ";
    sum.print(std::cout);
    std::cout << std::endl;

    Thirteen diff = num2.sub(num3);
    std::cout << "Subtraction (num2 - num3): ";
    diff.print(std::cout);
    std::cout << std::endl;

    std::cout << "Comparison (num2 == num3): " << (num2.equals(num3) ? "true" : "false") << std::endl;
    std::cout << "Comparison (num2 > num3): " << (num2.greater(num3) ? "true" : "false") << std::endl;
    std::cout << "Comparison (num2 < num3): " << (num2.less(num3) ? "true" : "false") << std::endl;

    return 0;
}