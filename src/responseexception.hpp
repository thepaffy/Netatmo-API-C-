#ifndef RESPONSEEXCEPTION_HPP
#define RESPONSEEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

class ResponseException: public std::exception {
public:
    ResponseException(const std::string &what) {
        mWhat = what;
    }
    ResponseException(const char *what) {
        mWhat = what;
    }

    const char *what() const noexcept override {
        return mWhat.c_str();
    }

private:
    std::string mWhat;
};

}

#endif /* RESPONSEEXCEPTION_HPP */
