#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <concepts>

class FormatError : public std::runtime_error {
public:
    explicit FormatError(const std::string& msg) : std::runtime_error(msg) {}
};

template <typename T>
concept Printable = requires(std::ostream& os, const T& value) {
    os << value;
};

template <Printable T>
std::string stringify(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <Printable... Args>
std::string format(const std::string& text, const Args&... args) {
    std::vector<std::string> str_args;
    
    int dummy[] = { 0, (str_args.push_back(stringify(args)), 0)... };
    (void)dummy;

    std::string result;
    for (std::size_t i = 0; i < text.length(); ++i) {
        if (text[i] == '{') {
            std::size_t close_pos = text.find('}', i);
            if (close_pos == std::string::npos) {
                throw FormatError("Не закрыли скобку");
            }
            
            std::string index_str = text.substr(i + 1, close_pos - i - 1);
            
            if (index_str.empty() || !std::all_of(index_str.begin(), index_str.end(), ::isdigit)) {
                throw FormatError("Не правильный формат индекса");
            }
            
            std::size_t index = std::stoul(index_str);
            if (index >= str_args.size()) {
                throw FormatError("Индекс вышел за предел");
            }
            
            result += str_args[index];
            i = close_pos;
        } 
        else if (text[i] == '}') {
            throw FormatError("Неожидаемая скобка");
        } 
        else {
            result += text[i];
        }
    }
    return result;
}