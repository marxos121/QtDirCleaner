#pragma once

#include <iostream>
#include <filesystem>

template <typename T>
class Log {
public:
	Log<T>& operator+=(const T& rhs);
	void append(T l_content);
	void appendContent(const Log<T>& rhs);
	void appendAll(const Log<T>& rhs);

	void clearContent();

	void save(const std::filesystem::path& l_path = "log.dlog", const std::locale& l_encoding = std::locale("en_US.utf8")) const;

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

#include "Log.inl"