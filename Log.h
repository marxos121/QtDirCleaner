#pragma once

#include <iostream>
#include <filesystem>

template <typename T>
class Log {
	friend std::basic_ostream<T::value_type>& operator<<(std::basic_ostream<T::value_type>& os, const Log<T>& l_log);
	friend std::basic_istream<T::value_type>& operator>>(std::basic_istream<T::value_type>& is, Log<T>& l_log);

	friend Log<T> operator+(const Log<T>& rhs);
	friend Log<T> operator+(const T& rhs);

public:
	Log<T>& operator+=(const Log<T>& rhs);
	Log<T>& operator+=(const T& rhs);
	void append(T l_content);
	void appendContent(const Log<T>& rhs);
	void appendAll(const Log<T>& rhs);

	void addHeader();
	void addFooter();

	void clearContent();

	void save(const std::filesystem::path& l_path = "log.dlog");

private:
	T m_content;
	T m_header;
	T m_footer;

public:
	// ========== Setters and Getters ==========
	const T& getAll() const;
	const T& getContent() const;
	const T& getHeader() const;
	const T& getFooter() const;

	void setContent(const T& l_content);
	void setHeader(const T& l_header);
	void setFooter(const T& l_footer);
};
