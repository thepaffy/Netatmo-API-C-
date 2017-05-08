#include "nawsapiclient.h"

namespace netatmoapi {

NAWSApiClient::NAWSApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken, const std::string &refreshToken) :
    NAApiClient(username, password, clientId, clientSecret, accessToken, refreshToken) {

}

}
