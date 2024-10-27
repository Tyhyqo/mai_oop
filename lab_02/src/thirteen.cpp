#include "thirteen.h"
#include <vector>

// Default constructor
Thirteen::Thirteen() : _size(0), _array{nullptr} {}

// Fill constructor
Thirteen::Thirteen(const size_t &n, unsigned char t)
{
    if (!(t >= '0' && t <= '9') && !(t >= 'A' && t <= 'C'))
    {
        throw std::invalid_argument("Invalid character for base 13");
    }

    _array = new unsigned char[n];
    for (size_t i = 0; i < n; ++i)
        _array[i] = t;
    _size = n;
}

// Initializer list constructor
Thirteen::Thirteen(const std::initializer_list<unsigned char> &t)
{
    if (*t.begin() == '0')
    {
        throw std::invalid_argument("The number cannot start with '0'");
    }
    _array = new unsigned char[t.size()];
    size_t i{0};
    for (auto &c : t)
    {
        if (!(c >= '0' && c <= '9') && !(c >= 'A' && c <= 'C'))
        {
            throw std::invalid_argument("Invalid character for base 13");
        }
        _array[i++] = c;
    }
    _size = t.size();
}

// Copy string constructor
Thirteen::Thirteen(const std::string &t)
{
    if (t[0] == '0')
    {
        throw std::invalid_argument("The number cannot start with '0'");
    }
    _array = new unsigned char[t.size()];
    _size = t.size();

    for (size_t i{0}; i < _size; ++i)
    {
        if (!(t[i] >= '0' && t[i] <= '9') && !(t[i] >= 'A' && t[i] <= 'C'))
        {
            throw std::invalid_argument("Invalid character for base 13");
        }
        _array[i] = t[i];
    }
}

// Copy constructor
Thirteen::Thirteen(const Thirteen &other)
{
    _size = other._size;
    _array = new unsigned char[_size];

    for (size_t i{0}; i < _size; ++i)
        _array[i] = other._array[i];
}

// Move constructor
Thirteen::Thirteen(Thirteen &&other) noexcept
{
    _size = other._size;
    _array = other._array;

    other._size = 0;
    other._array = nullptr;
}

// Add two Thirteen numbers
Thirteen Thirteen::add(const Thirteen &other)
{
    size_t maxSize = std::max(this->_size, other._size);
    std::vector<unsigned char> resultArray(maxSize + 1, 0);

    int carry = 0;
    for (int i = 0; i < maxSize; ++i)
    {
        int digit1 = (this->_size - i - 1 >= 0) ? charToValue(this->_array[this->_size - i - 1]) : 0;
        int digit2 = (other._size - i - 1 >= 0) ? charToValue(other._array[other._size - i - 1]) : 0;

        int sum = digit1 + digit2 + carry;
        resultArray[maxSize - i] = valueToChar(sum % 13);
        carry = sum / 13;
    }

    int is_carry = 1;
    if (carry > 0)
    {
        resultArray[0] = valueToChar(carry);
        ++maxSize;
        is_carry = 0;
    }

    Thirteen result;
    result._size = maxSize;
    result._array = new unsigned char[maxSize];
    std::copy(resultArray.begin() + is_carry, resultArray.begin() + is_carry + maxSize, result._array);

    return result;
}

// Subtract two Thirteen numbers
Thirteen Thirteen::sub(const Thirteen &other)
{
    size_t maxSize = std::max(this->_size, other._size);
    std::vector<unsigned char> resultArray(maxSize, 0);

    if (this->less(other))
    {
        throw std::logic_error("Thirteen can't be negative");
    }

    int borrow = 0;
    for (int i = 0; i < maxSize; ++i)
    {
        int digit1 = (this->_size - i - 1 >= 0) ? charToValue(this->_array[this->_size - i - 1]) : 0;
        int digit2 = (other._size - i - 1 >= 0) ? charToValue(other._array[other._size - i - 1]) : 0;

        int sub = digit1 - digit2 - borrow;
        if (sub < 0)
        {
            sub += 13;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        resultArray[maxSize - i - 1] = valueToChar(sub);
    }

    int begin = 0;
    while (resultArray[begin] == '0' && begin < maxSize - 1)
    {
        ++begin;
    }

    Thirteen result;
    result._size = resultArray.size();
    result._array = new unsigned char[result._size];
    std::copy(resultArray.begin() + begin, resultArray.end(), result._array);

    return result;
}

// Convert char to value
unsigned char Thirteen::charToValue(unsigned char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    else if (ch >= 'A' && ch <= 'C')
        return ch - 'A' + 10;
}

// Convert value to char
unsigned char Thirteen::valueToChar(unsigned char value)
{
    if (value <= 9)
        return value + '0';
    else if (value >= 10 && value <= 12)
        return value - 10 + 'A';
}

// Is this number equal to another
bool Thirteen::equals(const Thirteen &other) const
{
    if (this->_size != other._size)
        return false;

    for (size_t i = 0; i < this->_size; ++i)
        if (this->_array[i] != other._array[i])
            return false;

    return true;
}

// Is this number greater than another
bool Thirteen::greater(const Thirteen &other) const
{
    if (this->_size > other._size)
        return true;
    else if (this->_size < other._size)
        return false;

    for (size_t i = 0; i < this->_size; ++i)
        if (this->_array[i] > other._array[i])
            return true;
        else if (this->_array[i] < other._array[i])
            return false;

    return false;
}

// Is this number less than another
bool Thirteen::less(const Thirteen &other) const
{
    if (this->_size < other._size)
        return true;
    else if (this->_size > other._size)
        return false;

    for (size_t i = 0; i < this->_size; ++i)
        if (this->_array[i] < other._array[i])
            return true;
        else if (this->_array[i] > other._array[i])
            return false;

    return false;
}

// Print number
std::ostream &Thirteen::print(std::ostream &os)
{
    for (size_t i = 0; i < _size; ++i)
        os << _array[i];
    return os;
}

// Destructor
Thirteen::~Thirteen() noexcept
{
    if (_size > 0)
    {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}