#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onEvent(const std::string& message) = 0;
};

#endif // OBSERVER_HPP