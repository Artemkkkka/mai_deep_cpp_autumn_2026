#include <functional>
#include <string>

class Parser {
public:
    using TokenCallback = std::function<void(const std::string&)>;
    using OnEventCallback = std::function<void()>;

    void forNumber(const TokenCallback& cb);
    void forString(const TokenCallback& cb);
    void forStart(const OnEventCallback& cb);
    void forFinish(const OnEventCallback& cb);

    void parse(const std::string& text) const;

private:
    TokenCallback numberHandler;
    TokenCallback stringHandler;
    OnEventCallback beginHandler;
    OnEventCallback endHandler;
};