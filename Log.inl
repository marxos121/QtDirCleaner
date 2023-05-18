#include "Log.h"

template <typename T>
std::basic_ostream<T>&
operator<<(std::basic_ostream<T>& os, const Log<T>& l_log)
{
    os << l_log.getAll(std::basic_string<T>(NewlineString<T>::value));
    return os;
}

template <typename T>
Log<T> operator+(const Log<T>& log, const std::basic_string<T>& str)
{
    Log<T> temp(log);
    temp += str;
    return temp;
}

template <typename T>
Log<T> operator+(const Log<T>& log, const T* str)
{
    Log<T> temp(log);
    temp += str;
    return temp;
}

template<typename T>
inline Log<T>& Log<T>::operator+=(const T* rhs)
{
    m_content.append(rhs);
    return *this;
}

template<typename T>
inline Log<T>& Log<T>::operator+=(const std::basic_string<T>& rhs)
{
    m_content.append(rhs);
    return *this;
}

template<typename T>
inline void Log<T>::append(const std::basic_string<T>& l_content)
{
    l_content.append(l_content);
}

template<typename T>
inline void Log<T>::appendContent(const Log<T>& rhs)
{
    m_content.append(rhs.getContent());
}

template<typename T>
inline void Log<T>::appendAll(const Log<T>& rhs)
{
    m_content.append(rhs.getAll());
}

template<typename T>
inline void Log<T>::clearContent()
{
    m_content.clear();
}

template<typename T>
inline void Log<T>::save(const std::filesystem::path& l_path, const std::locale& l_encoding) const
{
    std::basic_ofstream<T> os(l_path);
    os.imbue(l_encoding);
    os << *this;
    os.close();
}




// Setter methods implementation
template<typename T>
void Log<T>::setContent(const std::basic_string<T>& l_content) {
    m_content = l_content;
}

template<typename T>
void Log<T>::setHeader(const std::basic_string<T>& l_header) {
    m_header = l_header;
}

template<typename T>
void Log<T>::setFooter(const std::basic_string<T>& l_footer) {
    m_footer = l_footer;
}

// Getter methods implementation
template<typename T>
std::basic_string<T> Log<T>::getAll(const std::basic_string<T>& separator) const {
    return (m_header.empty() ? m_header : m_header + separator) 
        + m_content + 
        (m_footer.empty() ? m_footer : separator + m_footer);
}

template<typename T>
const std::basic_string<T>& Log<T>::getContent() const {
    return m_content;
}

template<typename T>
const std::basic_string<T>& Log<T>::getHeader() const {
    return m_header;
}

template<typename T>
const std::basic_string<T>& Log<T>::getFooter() const {
    return m_footer;
}