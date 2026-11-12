#pragma once

#include <iostream>
#include <cstdint>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out) : out(out) {}

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args... args) {
        return process_args(args...);
    }

    Error process(bool value);
    Error process(uint64_t value);

private:
    std::ostream& out;

    Error process_args() {
        return Error::NoError;
    }

    template <class T, class... Args>
    Error process_args(T arg, Args... args) {
        Error err = process(arg);
        if (err != Error::NoError) {
            return err;
        }
        return process_args(args...);
    }
};

class Deserializer {
public:
    explicit Deserializer(std::istream& in) : in(in) {}

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args&... args) {
        return process_args(args...);
    }

    Error process(bool& value);
    Error process(uint64_t& value);

private:
    std::istream& in;

    Error process_args() {
        return Error::NoError;
    }

    template <class T, class... Args>
    Error process_args(T& arg, Args&... args) {
        Error err = process(arg);
        if (err != Error::NoError) {
            return err;
        }
        return process_args(args...);
    }
};