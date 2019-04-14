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

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <iostream>

using json = nlohmann::json;
using namespace std;

size_t writeCallback(char *buffer, size_t size, size_t nmemb, void *userp) {
    if (userp) {
        ostream *os = static_cast<ostream *>(userp);
        size_t len = size * nmemb;
        if (os->write(buffer, streamsize (len))) {
            return len;
        }
    }

    return 0;
}

TEST(CurlTest, getTest) {
    CURL *curl;
    CURLcode res;

    string url = "http://httpbin.org/get?param1=key1&param2=key2";
    stringstream rawResponse;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FILE, &rawResponse);
        res = curl_easy_perform(curl);
        ASSERT_EQ(CURLE_OK, res);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    json response;
    rawResponse >> response;
    json args = response["args"];

    EXPECT_NE(args.find("param1"), args.end());
    string param1 = args["param1"];
    EXPECT_STREQ(param1.c_str(), "key1");

    EXPECT_NE(args.find("param2"), args.end());
    string param2 = args["param2"];
    EXPECT_STREQ(param2.c_str(), "key2");
}

TEST(CurlTest, postTest) {
    CURL *curl;
    CURLcode res;

    string url = "http://httpbin.org/post";
    string postField = "param1=key1&param2=key2";
    stringstream rawResponse;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_FILE, &rawResponse);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postField.c_str());
        res = curl_easy_perform(curl);
        ASSERT_EQ(CURLE_OK, res);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    json response;
    rawResponse >> response;
    json form = response["form"];

    EXPECT_NE(form.find("param1"), form.end());
    string param1 = form["param1"];
    EXPECT_STREQ(param1.c_str(), "key1");

    EXPECT_NE(form.find("param2"), form.end());
    string param2 = form["param2"];
    EXPECT_STREQ(param2.c_str(), "key2");
}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
