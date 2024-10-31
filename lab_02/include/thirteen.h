#pragma once

#include <string>
#include <iostream>
#include <map>

class Thirteen
{
public:
    Thirteen();
    Thirteen(const size_t &n, unsigned char t = 0);
    Thirteen(const std::initializer_list<unsigned char> &t);
    Thirteen(const std::string &t);
    Thirteen(const Thirteen &other);
    Thirteen(Thirteen &&other) noexcept;

    Thirteen add(const Thirteen &other);
    Thirteen sub(const Thirteen &other);

    bool equals(const Thirteen &other) const;
    bool greater(const Thirteen &other) const;
    bool less(const Thirteen &other) const;

    std::ostream &print(std::ostream &os);

    virtual ~Thirteen() noexcept;

private:
    unsigned char charToValue(unsigned char ch);
    unsigned char valueToChar(unsigned char value);

    size_t _size;
    unsigned char *_array;
};