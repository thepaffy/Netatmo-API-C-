#ifndef NAWSAPICLIENT_H
#define NAWSAPICLIENT_H

#include "naapiclient.h"

namespace netatmoapi {

class NAWSApiClient: public NAApiClient {
public:
    NAWSApiClient(const std::string &username, const std::string &password, const std::string &clientId, const std::string &clientSecret, const std::string &accessToken = std::string(), const std::string &refreshToken = std::string());

};

}

#endif /* NAWSAPICLIENT_H */
