#include "parser.hpp"

#include <algorithm>
#include <sstream>

void Parser::forNumber(const TokenCallback& cb) {
    this->numberHandler = cb;
}

void Parser::forString(const TokenCallback& cb) {
    this->stringHandler = cb;
}

void Parser::forStart(const OnEventCallback& cb) {
    this->beginHandler = cb;
}

void Parser::forFinish(const OnEventCallback& cb) {
    this->endHandler = cb;
}

void Parser::parse(const std::string& text) const {
    if (this->beginHandler) {
        this->beginHandler();
    }

    std::istringstream stream(text);
    std::string token;
    while (stream >> token) {
        const bool isNumber = std::all_of(
            token.begin(), token.end(),
            [](char c) { return c >= '0' && c <= '9'; }
        );

        if (isNumber) {
            if (this->numberHandler) {
                this->numberHandler(token);
            }
        } else {
            if (this->stringHandler) {
                this->stringHandler(token);
            }
        }
    }

    if (this->endHandler) {
        this->endHandler();
    }
}