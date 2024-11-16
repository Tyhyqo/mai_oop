#include "array.hpp"
#include "rectangle.hpp"
#include "rhomb.hpp"
#include "trapezoid.hpp"

#include <iostream>
#include <array>
#include <memory>

int main()
{
    Array<std::shared_ptr<Figure<float>>> figures;

    std::string command;

    while (true)
    {
        std::cout << "Select command: " << std::endl;
        std::cout << "1) Add figure" << std::endl;
        std::cout << "2) Print all figures info" << std::endl;
        std::cout << "3) Print total figures area" << std::endl;
        std::cout << "4) Print <index> figure area" << std::endl;
        std::cout << "5) Print <index> figure points" << std::endl;
        std::cout << "6) Print <index> figure geometric center:" << std::endl;
        std::cout << "7) Delete <index> figure" << std::endl;
        std::cout << "8) Exit" << std::endl;

        std::cin >> command;
        std::cout << "------------------------------------------------" << std::endl;
        if (command == "1")
        {
            std::cout << "Select firgure: " << std::endl;
            std::cout << "1) Rhomb" << std::endl;
            std::cout << "2) Rectangle" << std::endl;
            std::cout << "3) Trapezoid" << std::endl;

            std::string figure;
            std::cin >> figure;
            std::cout << "------------------------------------------------" << std::endl;
            if (figure == "1")
            {
                try
                {
                    auto rhomb = std::make_shared<Rhomb<float>>();
                    std::cin >> *rhomb;
                    figures.push_back(rhomb);
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
            else if (figure == "2")
            {
                try
                {
                    auto rectangle = std::make_shared<Rectangle<float>>();
                    std::cin >> *rectangle;
                    figures.push_back(rectangle);
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
            else if (figure == "3")
            {
                try
                {
                    auto trapezoid = std::make_shared<Trapezoid<float>>();
                    std::cin >> *trapezoid;
                    figures.push_back(trapezoid);
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid input" << std::endl;
            }
        }
        else if (command == "2")
        {
            std::cout << figures;
        }
        else if (command == "3")
        {
            std::cout << "Total figures area: " << static_cast<double>(figures) << std::endl;
        }
        else if (command == "4")
        {
            std::cout << "Enter index: " << std::endl;

            std::size_t index;
            std::cin >> index;
            std::cout << "------------------------------------------------" << std::endl;
            try
            {
                std::cout << "Figure area: " << static_cast<double>(*figures[index]) << std::endl;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else if (command == "5")
        {
            std::cout << "Enter index: " << std::endl;

            std::size_t index;
            std::cin >> index;
            std::cout << "------------------------------------------------" << std::endl;
            try
            {
                std::cout << *figures[index];
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else if (command == "6")
        {
            std::cout << "Enter index: " << std::endl;

            std::size_t index;
            std::cin >> index;
            std::cout << "------------------------------------------------" << std::endl;
            try
            {
                auto center = figures[index]->center();
                std::cout << "Geometric center: " << center << std::endl;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else if (command == "7")
        {
            std::cout << "Enter index: " << std::endl;

            std::size_t index;
            std::cin >> index;
            std::cout << "------------------------------------------------" << std::endl;
            try
            {
                figures.erase(index);
                std::cout << "Figure deleted" << std::endl;
            }
            catch (const std::out_of_range &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else if (command == "8")
        {
            break;
        }
        else
        {
            std::cout << "Invalid command" << std::endl;
        }
        std::cout << "------------------------------------------------" << std::endl;
    }

    return 0;
}