#pragma once
#include <iostream>

template <class T>
class CachedValue
{
private:
    bool valid;
    T value;

public:
    CachedValue(T value)
    {
        this->value = value;
        valid = true;
    }

    CachedValue()
    {
        this->value = T();
        valid = false;
    }

    T getValue()
    {
        return value;
    }

    void setValue(T value)
    {
        this->value = value;
        this->valid = true;
    }

    void invalidate()
    {
        value = T();
        valid = false;
    }

    bool isValid()
    {
        return valid;
    }
};