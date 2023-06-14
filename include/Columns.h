#pragma once

enum CleanModelColumns
{
	Type = 0,
	Extensions,
	TargetDirs,
	Exempt,
	Destination
};

constexpr const char* columnHeaders(CleanModelColumns column) {
	switch (column)
	{
	case CleanModelColumns::Type: return "Type";
	case CleanModelColumns::Extensions: return "Extensions";
	case CleanModelColumns::TargetDirs: return "Target Directories";
	case CleanModelColumns::Exempt: return "Exceptions";
	case CleanModelColumns::Destination: return "Output Directory";
	default: return "";
	}
}