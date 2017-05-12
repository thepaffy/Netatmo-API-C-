#ifndef RESPONSEEXCEPTION_HPP
#define RESPONSEEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

/**
 * @brief This exception is thrown, if the response of the api contains a error value.
 *
 * The error code is part of the what message.
 */
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
