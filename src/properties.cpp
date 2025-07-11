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
		values.clear();
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

		values[key] = value;
	}
	void Properties::load(std::string& text)
	{
		values.clear();
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
		for (auto& pair : properties.values) {
			os << pair.first << " = " << pair.second << "\n";
		}
		return os;
	}
	std::string Properties::get(const std::string& key, const std::string& standard_value)
	{
		std::string value = values[key];
		if (value.empty()) {
			value = standard_value;
		}
		return value;
	}

	long long Properties::getLong(const std::string& key, const long long standard_value)
	{
		std::string value = get(key);
		if (value.empty()) {
			return standard_value;
		} 
		return std::atol(value.c_str());
	}
	double Properties::getDouble(const std::string& key, const double standard_value)
	{
		std::string value = get(key);
		if (value.empty()) {
			return standard_value;
		}
		return std::atof(value.c_str());
	}
	bool Properties::getBool(const std::string& key, const bool standard_value)
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

	void Properties::set(const std::string& key, const std::string& value)
	{
		values[key] = value;
	}
	void Properties::set(const std::string& key, const long long value)
	{
		values[key] = std::to_string(value);
	}
	void Properties::set(const std::string& key, const double value)
	{
		values[key] = std::to_string(value);
	}
	void Properties::set(const std::string& key, const bool value)
	{
		values[key] = value ? "true" : "false";
	}


	std::vector<std::string> Properties::getArray(const std::string& key)
	{
		std::string value = get(key);
		std::vector<std::string> out;


		std::stringstream ss(value);
		std::string segment;
		unsigned int first = segment.find_first_not_of(' ');
		while (std::getline(ss, segment, ',')) {
			unsigned int first = segment.find_first_not_of(' ');
			if (segment.empty() || first == std::string::npos) {
				out.push_back("");
			}
			else {
				out.push_back(segment.substr(first, (segment.find_last_not_of(' ') - first + 1)));
			}
		}

		return out;
	}

	std::vector<long long> Properties::getLongArray(const std::string& key)
	{
		std::vector<std::string> values = getArray(key);
		std::vector<long long> out;
		out.reserve(values.size());
		for (std::string val : values)
		{
			out.push_back(std::atol(val.c_str()));
		}
		return out;
	}
	std::vector<double> Properties::getDoubleArray(const std::string& key)
	{
		std::vector<std::string> values = getArray(key);
		std::vector<double> out;
		out.reserve(values.size());
		for (std::string val : values)
		{
			out.push_back(std::atof(val.c_str()));
		}
		return out;
	}
	std::vector<bool> Properties::getBoolArray(const std::string& key)
	{
		std::vector<std::string> values = getArray(key);
		std::vector<bool> out;
		out.reserve(values.size());
		for (std::string val : values)
		{
			if (val.compare("true") == 0 || val.compare("TRUE") == 0) {
				out.push_back(true);
			}
			else {
				out.push_back(false);
			}
		}
		return out;
	}
	void Properties::setArray(const std::string& key, const std::string* array, const unsigned int len)
	{
		std::stringstream ss;
		for (unsigned int i = 0; i < len-1; i++)
		{
			ss << array[i] << ", ";
		}
		ss << array[len-1];
		set(key, ss.str());
	}
	void Properties::setArray(const std::string& key, long long* array, const unsigned int len)
	{
		std::stringstream ss;
		for (unsigned int i = 0; i < len - 1; i++)
		{
			ss << std::to_string(array[i]) << ", ";
		}
		ss << std::to_string(array[len - 1]);
		set(key, ss.str());
	}
	void Properties::setArray(const std::string& key, double* array, const unsigned int len)
	{
		std::stringstream ss;
		for (unsigned int i = 0; i < len - 1; i++)
		{
			ss << std::to_string(array[i]) << ", ";
		}
		ss << std::to_string(array[len - 1]);
		set(key, ss.str());
	}
	void Properties::setArray(const std::string& key, bool* array, const unsigned int len)
	{
		std::stringstream ss;
		for (unsigned int i = 0; i < len - 1; i++)
		{
			if (array[i]) {
				ss << "true";
			}
			else {
				ss << "false";
			}
			ss << ", ";
		}
		if (array[len - 1]) {
			ss << "true";
		}
		else {
			ss << "false";
		}
		set(key, ss.str());
	}
	void Properties::setArray(const std::string& key, const std::vector<std::string>& array)
	{
		if (array.size() == 0) {
			set(key, "");
			return;
		}
		std::stringstream ss;
		for (unsigned int i = 0; i < array.size() - 1; i++)
		{
			ss << array[i] << ", ";
		}
		ss << array[array.size() - 1];
		set(key, ss.str());
	}
	void Properties::setArray(const std::string& key, const std::vector<long long>& array)
	{
		if (array.size() == 0) {
			set(key, "");
			return;
		}
		std::stringstream ss;
		for (unsigned int i = 0; i < array.size() - 1; i++)
		{
			ss << std::to_string(array[i]) << ", ";
		}
		ss << std::to_string(array[array.size() - 1]);
		set(key, ss.str());
	}
	void Properties::setArray(const std::string& key, const std::vector<double>& array)
	{
		if (array.size() == 0) {
			set(key, "");
			return;
		}
		std::stringstream ss;
		for (unsigned int i = 0; i < array.size() - 1; i++)
		{
			ss << std::to_string(array[i]) << ", ";
		}
		ss << std::to_string(array[array.size() - 1]);
		set(key, ss.str());
	}
	void Properties::setArray(const std::string& key, const std::vector<bool>& array)
	{
		if (array.size() == 0) {
			set(key, "");
			return;
		}
		std::stringstream ss;
		for (unsigned int i = 0; i < array.size() - 1; i++)
		{
			if (array[i]) {
				ss << "true";
			}
			else {
				ss << "false";
			}
			ss << ", ";
		}
		if (array[array.size() - 1]) {
			ss << "true";
		}
		else {
			ss << "false";
		}
		set(key, ss.str());
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