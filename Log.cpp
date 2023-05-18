#include "Log.h"

template <typename T>
std::basic_ostream<typename Log<T>::T::value_type>&
operator<< (std::basic_ostream<typename Log<T>::T::value_type>& os, const Log<T>& l_log)
{
    os << l_log.getAll();
    return os;
}
