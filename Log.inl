#include "Log.h"





template<typename T>
inline void Log<T>::append(T l_content)
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
inline void Log<T>::save(const std::filesystem::path& l_path, const std::locale& l_encoding)
{
    std::wofstream os(l_path);
    os.imbue(l_encoding);
    os << getAll();
    os.close();
}




// Setter methods implementation
template<typename T>
void Log<T>::setContent(const T& l_content) {
    m_content = l_content;
}

template<typename T>
void Log<T>::setHeader(const T& l_header) {
    m_header = l_header;
}

template<typename T>
void Log<T>::setFooter(const T& l_footer) {
    m_footer = l_footer;
}

// Getter methods implementation
template<typename T>
const T& Log<T>::getAll() const {
    static T result;
    result = m_header + "\n\n" + m_content + "\n\n" + m_footer;
    return result;
}

template<typename T>
const T& Log<T>::getContent() const {
    return m_content;
}

template<typename T>
const T& Log<T>::getHeader() const {
    return m_header;
}

template<typename T>
const T& Log<T>::getFooter() const {
    return m_footer;
}