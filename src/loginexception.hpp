#ifndef LOGINEXCEPTION_HPP
#define LOGINEXCEPTION_HPP

#include <exception>
#include <string>

class LoginException: public std::exception {
public:
    LoginException(const std::string &what) :
        mWhat(what) {
    }
    LoginException(const char *what) :
        mWhat(what) {
    }

    const char *what() const noexcept override {
        return mWhat.c_str();
    }

private:
    std::string mWhat;
};

#endif /* LOGINEXCEPTION_HPP */
