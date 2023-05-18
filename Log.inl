#include "Log.h"

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