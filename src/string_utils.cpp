//src/string_utils.cpp
#include "bcppul/string_utils.h"

namespace bcppul {
	std::string parseEscapeSequences(const std::string& input_str) {
		std::ostringstream oss;
		int i = 0;
		while (i < input_str.length()) {
			char current_char = input_str[i];

			if (current_char == '\\') {
				i++;
				if (i >= input_str.length()) {
					throw std::runtime_error("Incorrect escape-sequence: string ends on '\\'");
				}

				char escape_char = input_str[i];

				auto it = simple_escapes.find(escape_char);
				if (it != simple_escapes.end()) {
					oss << it->second;
					i++;
					continue;
				}

				if (escape_char == 'x') {
					i++;
					if (i >= input_str.length() || !isxdigit(static_cast<unsigned char>(input_str[i]))) {
						throw std::runtime_error("Incorrect hex escape-sequence: \\x without numbers");
					}
					char value = 0;
					int digits_read = 0;
					while (i < input_str.length() && isxdigit(static_cast<unsigned char>(input_str[i]))) {
						value = (value << 4) | (isdigit(static_cast<unsigned char>(input_str[i])) ? (input_str[i] - '0') :
							(tolower(static_cast<unsigned char>(input_str[i])) - 'a' + 10));
						i++;
						digits_read++;
						if (digits_read > 2) {
							value &= 0xFF;
						}
					}
					oss << static_cast<char>(value);
					continue;
				}


				if (escape_char == 'u' || escape_char == 'U') {
					int num_digits = (escape_char == 'u' ? 4 : 8);
					std::string hex_digits;
					int start_pos = i;
					for (int k = 0; k < num_digits; ++k) {
						if (i < input_str.length() && isxdigit(static_cast<unsigned char>(input_str[i]))) {
							hex_digits += input_str[i];
							i++;
						}
						else {
							throw std::runtime_error("Incomplete Unicode escape-sequence: \\" + std::string(1, escape_char));
						}
					}
					if (hex_digits.length() != num_digits) {
						throw std::runtime_error("Incorrect Unicode escape-sequence: \\" + std::string(1, escape_char) + hex_digits);
					}
					unsigned long codepoint = std::stoul(hex_digits, nullptr, 16);

					if (codepoint >= 0x00 && codepoint <= 0x7F) {
						oss << static_cast<char>(codepoint);
					}
					else if (codepoint >= 0x80 && codepoint <= 0x7FF) {
						oss << static_cast<char>(0xC0 | (codepoint >> 6));
						oss << static_cast<char>(0x80 | (codepoint & 0x3F));
					}
					else if (codepoint >= 0x800 && codepoint <= 0xFFFF) {
						oss << static_cast<char>(0xE0 | (codepoint >> 12));
						oss << static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
						oss << static_cast<char>(0x80 | (codepoint & 0x3F));
					}
					else if (codepoint >= 0x10000 && codepoint <= 0x10FFFF) {
						oss << static_cast<char>(0xF0 | (codepoint >> 18));
						oss << static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F));
						oss << static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F));
						oss << static_cast<char>(0x80 | (codepoint & 0x3F));
					}
					else {
						throw std::runtime_error("Unicode codepoint " + std::to_string(codepoint) + " out of representable range for char/basic UTF-8 encoding in this example.");
					}
					continue;
				}

				if (isdigit(static_cast<unsigned char>(escape_char)) && escape_char >= '0' && escape_char <= '7') {
					char value = escape_char - '0';
					int digits_read = 1;
					while (digits_read < 3 && i + 1 < input_str.length() &&
						isdigit(static_cast<unsigned char>(input_str[i + 1])) && input_str[i + 1] >= '0' && input_str[i + 1] <= '7') {
						i++;
						value = (value << 3) | (input_str[i] - '0');
						digits_read++;
					}
					oss << static_cast<char>(value);
					i++;
					continue;
				}

				throw std::runtime_error(std::string("Unknown escape-sequence: \\") + escape_char);

			}
			else {
				oss << current_char;
				i++;
			}
		}
		return oss.str();
	}

	std::string replaceEscapesWithRaw(const std::string& input_str) {
		std::ostringstream oss;

		for (char c : input_str) {
			switch (c) {
			case '\n': oss << "\\n"; break;
			case '\t': oss << "\\t"; break;
			case '\r': oss << "\\r"; break;
			case '\a': oss << "\\a"; break;
			case '\b': oss << "\\b"; break;
			case '\f': oss << "\\f"; break;
			case '\v': oss << "\\v"; break;
			case '\\': oss << "\\\\"; break;
			case '\'': oss << "\\'"; break;
			case '\"': oss << "\\\""; break;
			case '\?': oss << "\\?"; break;
			default:
				if (static_cast<unsigned char>(c) < 32 || static_cast<unsigned char>(c) > 126) {
					oss << "\\x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
				}
				else {
					oss << c;
				}
				break;
			}
		}
		return oss.str();
	}
	std::string& ltrim(std::string& s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));
		return s;
	}
	std::string& rtrim(std::string& s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
		return s;
	}
	std::string& trim(std::string& s)
	{
		ltrim(s);
		rtrim(s);
		return s;
	}
	size_t findXOf(std::string& str, char c, size_t x) {
		size_t j = 0;
		for (size_t i = 0; i < str.length(); ++i)
		{
			if (str[i] == c) {
				if (j == x) {
					return i;
				}
				++j;
			}
		}
	}
}