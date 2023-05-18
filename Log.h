#pragma once

#include <ostream>
#include <filesystem>

template <typename T>
class Log {
public:
	Log<T>& operator+=(const T* rhs);
	Log<T>& operator+=(const std::basic_string<T>& rhs);
	void append(const std::basic_string<T>& l_content);
	void appendContent(const Log<T>& rhs);
	void appendAll(const Log<T>& rhs);

	void clearContent();

	void save(const std::filesystem::path& l_path = "log.dlog", const std::locale& l_encoding = std::locale("en_US.utf8")) const;

private:
	std::basic_string<T> m_content;
	std::basic_string<T> m_header;
	std::basic_string<T> m_footer;

public:
	// ========== Setters and Getters ==========
	std::basic_string<T> getAll(const std::basic_string<T>& separator) const;
	const std::basic_string<T>& getContent() const;
	const std::basic_string<T>& getHeader() const;
	const std::basic_string<T>& getFooter() const;

	void setContent(const std::basic_string<T>& l_content);
	void setHeader(const std::basic_string<T>& l_header);
	void setFooter(const std::basic_string<T>& l_footer);
};

//Helper struct to implement operator<<
template <typename T>
struct NewlineString;

template <>
struct NewlineString<char>
{
	static constexpr const char* value = "\n\n";
};

template <>
struct NewlineString<wchar_t>
{
	static constexpr const wchar_t* value = L"\n\n";
};

template <>
struct NewlineString<char16_t>
{
	static constexpr const char16_t* value = u"\n\n";
};

template <>
struct NewlineString<char32_t>
{
	static constexpr const char32_t* value = U"\n\n";
};

#include "Log.inl"