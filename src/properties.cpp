//src/properties.cpp
#include "bcppul/properties.h"

#include <sstream>
#include <fstream>
#include "bcppul/string_utils.h"

namespace bcppul {
	Properties::Properties(std::string path) : path(path)
	{
	}
	Properties::~Properties()
	{
	}
	void Properties::load()
	{
		map.clear();
		std::ifstream is;
		is.open(path);
		if (!is.is_open()) {
			return;
		}
		std::string line;
		while (std::getline(is, line)) {
			loadLine(line);
		}
		is.close();
	}
	void Properties::loadLine(std::string& line) {
		if (line.size() == 0 || line.empty() || line[0] == '#') {
			return;
		}
		size_t equal = line.find_first_of("=");
		if (equal == std::string::npos) {
			return;
		}
		std::string key = trim(line.substr(0, equal));
		std::string value = trim(line.substr(equal+1));

		map[key] = value;
	}
	void Properties::load(std::string& text)
	{
		map.clear();
		size_t begin = 0;
		size_t end = text.find_first_of("\n");
		for (size_t i = 0; begin < text.length(); ++i) {
			loadLine(text.substr(begin, end));
			begin = end+1;
			end = findXOf(text, '\n', i+1);
		}

	}
	std::ostream& operator<<(std::ostream& os, Properties& properties)
	{
		for (auto& pair : properties.map) {
			os << pair.first << " = " << pair.second << "\n";
		}
		return os;
	}
	std::string Properties::get(std::string key, std::string standard_value)
	{
		std::string value = map[key];
		if (value.empty()) {
			value = standard_value;
		}
		return value;
	}

	long long Properties::getLong(std::string key, long long standard_value)
	{
		std::string value = get(key);
		if (value.empty()) {
			return standard_value;
		} 
		return std::atol(value.c_str());
	}
	double Properties::getDouble(std::string key, double standard_value)
	{
		std::string value = get(key);
		if (value.empty()) {
			return standard_value;
		}
		return std::atof(value.c_str());
	}
	bool Properties::getBool(std::string key, bool standard_value)
	{
		std::string value = get(key);
		if (value.empty()) {
			return standard_value;
		}
		if (value.compare("true") == 0 || value.compare("TRUE") == 0) {
			return true;
		}
		else {
			return false;
		}

	}

	void Properties::set(std::string key, std::string value)
	{
		map[key] = value;
	}
	void Properties::set(std::string key, long long value)
	{
		map[key] = std::to_string(value);
	}
	void Properties::set(std::string key, double value)
	{
		map[key] = std::to_string(value);
	}
	void Properties::set(std::string key, bool value)
	{
		map[key] = value ? "true" : "false";
	}


	void Properties::save()
	{
		std::ofstream os;
		os.open(path);
		if (!os.is_open()) {
			return;
		}
		os << *this;

		os.close();
	}
	std::string Properties::saveInString()
	{
		std::ostringstream os;
		os << *this;
		return os.str() + "\0";
	}
	std::string& Properties::getPath()
	{
		return path;
	}
	void Properties::setPath(std::string path)
	{
		this->path = path;
	}

}