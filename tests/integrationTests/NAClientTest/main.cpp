/*
 * Copyright (C) 2017 Christian Paffhausen, <https://github.com/thepaffy/>
 *
 * This file is part of Netatmo-API-CPP.
 *
 * Netatmo-API-CPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Netatmo-API-CPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Netatmo-API-CPP.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "core/naclient.h"

#include <gtest/gtest.h>
#include <cstdlib>
#include <nlohmann/json.hpp>

using namespace std;
using namespace netatmoapi;

TEST(NAClientTest, loginTestFails) {
    {
        NAClient client{"", "", "", ""};
        EXPECT_DEATH(client.login(), "");
        EXPECT_FALSE(client.loggedIn());
    }
    {
        NAClient client{"username", "password", "clientId", "clientSecret"};
        client.login();
        EXPECT_FALSE(client.loggedIn());
    }
}

TEST(NAClientTest, loginTestSuccessful) {
    NAClient client{getenv("TEST_USERNAME"), getenv("TEST_PASSWORD"), getenv("TEST_CLIENTID"), getenv("TEST_CLIENTSECRET")};
    client.login();
    EXPECT_TRUE(client.loggedIn());
}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
