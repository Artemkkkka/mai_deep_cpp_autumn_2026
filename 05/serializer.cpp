#include "serializer.hpp"
#include <cctype>

Error Serializer::process(bool value) {
    this->out << (value ? "true" : "false") << Serializer::Separator;
    return Error::NoError;
}

Error Serializer::process(uint64_t value) {
    this->out << value << Serializer::Separator;
    return Error::NoError;
}

Error Deserializer::process(bool& value) {
    std::string text;
    if (!(this->in >> text)) {
        return Error::CorruptedArchive;
    }

    if (text == "true") {
        value = true;
    } else if (text == "false") {
        value = false;
    } else {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}

Error Deserializer::process(uint64_t& value) {
    std::string text;
    if (!(this->in >> text)) {
        return Error::CorruptedArchive;
    }

    for (char c : text) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return Error::CorruptedArchive;
        }
    }

    try {
        value = std::stoull(text);
    } catch (...) {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}