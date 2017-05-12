#ifndef CURLEXCEPTION_HPP
#define CURLEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

/**
 * @brief This exception is thrown if the curl perform method returns a error code.
 *
 * The error code is part of the what message.
 */
class CurlException: public std::exception {
public:
    CurlException(const std::string &what) {
        mWhat = what;
    }
    CurlException(const char *what) {
        mWhat = what;
    }

    const char *what() const noexcept override {
        return mWhat.c_str();
    }

private:
    std::string mWhat;
};

}

#endif /* CURLEXCEPTION_HPP */
