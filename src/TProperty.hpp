#pragma once
#include <functional>
template <class T, bool supportChangedCallback = false>
class TProperty
{
public:
    typedef TProperty<T> type;
    typedef const TProperty<T> const_type;
    typedef std::function<void(T, T)> callback_type;
    callback_type _callback;
    TProperty() {}
    TProperty(const T val, callback_type fn) : _val(val), _callback(fn) {}
    T operator=(const T val)
    {
        if (supportChangedCallback)
        {
            if (this->_val != val)
            {
                auto oldVal = this->_val;
                this->_val = val;
                this->_callback(oldVal, this->_val);
            }
            return this->_val;
        }
        else
        {
            return this->_val = val;
        }
    }
    operator T() const { return this->_val; }
    type &operator=(const_type &other)
    {
        if (supportChangedCallback)
        {
            if (this->_val != other._val)
            {
                auto oldVal = this->_val;
                this->_val = other._val;
                this->_callback(oldVal, this->_val);
            }
            return this->_val;
        }
        else
        {
            return this->_val = other._val;
        }
        return *this;
    }

private:
    T _val = T(0);
};
