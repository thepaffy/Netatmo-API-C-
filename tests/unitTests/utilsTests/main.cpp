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

#include "core/utils.h"
#include "gtest/gtest.h"

#include <stdexcept>

using namespace netatmoapi;
using namespace netatmoapi::utils;
using namespace std;

TEST(BuildQueryUrlTest, buildUrlQuery) {
    map<string, string> params = {
        { "key1", "value1" },
        { "key2", "value2" },
        { "key3", "value3" },
    };
    EXPECT_STREQ("key1=value1&key2=value2&key3=value3",
                 buildUrlQuery(params, '&').c_str());
    EXPECT_STREQ("key1=value1+key2=value2+key3=value3",
                 buildUrlQuery(params, '+').c_str());
    EXPECT_THROW(buildUrlQuery(params, '='), invalid_argument);
    EXPECT_THROW(buildUrlQuery(params, ' '), invalid_argument);
}

TEST(EncodeUrlTest, urlEncode) {
    EXPECT_STREQ("https%3A%2F%2Fmax%3Amuster%40www.example.com%3A8080%2Findex.html%3Fp1%3DA%26p2%3DB%23ressource",
                 urlEncode("https://max:muster@www.example.com:8080/index.html?p1=A&p2=B#ressource").c_str());
    EXPECT_STREQ("thepaffy.de",
                 urlEncode("thepaffy.de").c_str());
}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
