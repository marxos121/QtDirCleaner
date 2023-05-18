#include "Log.h"

template <typename T>
std::basic_ostream<typename Log<T>::T::value_type>&
operator<< (std::basic_ostream<typename Log<T>::T::value_type>& os, const Log<T>& l_log)
{
    os << l_log.getAll();
    return os;
}

template <typename T>
Log<T> operator+(const Log<T>& log, const typename Log<T>::T& str)
{
    Log<T> temp(log);
    temp += str;
    return temp;
}