#ifndef LOGINEXCEPTION_HPP
#define LOGINEXCEPTION_HPP

#include <exception>
#include <string>

namespace netatmoapi {

/**
 * @brief This exception is thrown if a login credential is not provided and the user tries to login.
 *
 * The missing credential is part of the what message.
 */
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

}

#endif /* LOGINEXCEPTION_HPP */
