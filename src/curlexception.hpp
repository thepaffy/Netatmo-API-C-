#ifndef CURLEXCEPTION_HPP
#define CURLEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

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
