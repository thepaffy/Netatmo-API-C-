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

#include <gtest/gtest.h>

using namespace netatmoapi;
using namespace netatmoapi::utils;

using namespace std;


TEST(ParseDevicesTest, parseDevices) {
    json response = json::parse("{\"body\":{\"devices\":[{\"_id\":\"70:ee:50:29:48:4e\",\"cipher_id\":\"enc:16:y+aGVZeVut\\/5aKVfwFPW5FcNsBQ4ugLGB3FjOo05QrOe\\/2ag5gMshltnTt4jBM01\",\"last_status_store\":1501708387,\"modules\":[ ],\"place\":{\"altitude\":248,\"city\":\"Waldbreitbach\",\"country\":\"DE\",\"timezone\":\"Europe\\/Berlin\",\"location\":[7.4027088,50.555413]},\"station_name\":\"wetterstation\",\"type\":\"NAMain\",\"dashboard_data\":{\"AbsolutePressure\":988.6,\"time_utc\":1501708372,\"Noise\":38,\"Temperature\":23.1,\"temp_trend\":\"stable\",\"Humidity\":69,\"Pressure\":1018.1,\"pressure_trend\":\"down\",\"CO2\":426,\"date_max_temp\":1501673300,\"date_min_temp\":1501655170,\"min_temp\":22,\"max_temp\":24.5},\"data_type\":[\"Temperature\",\"CO2\",\"Humidity\",\"Noise\",\"Pressure\"],\"co2_calibrating\":false,\"date_setup\":1495880328,\"last_setup\":1495880328,\"module_name\":\"Innenraum\",\"firmware\":132,\"last_upgrade\":1495880134,\"wifi_status\":68,\"friend_users\":[\"59297b55ea00a0920c8b4e7d\"]}],\"user\":{\"mail\":\"thepaffy@thepaffy.de\",\"administrative\":{\"lang\":\"de-DE\",\"reg_locale\":\"de-DE\",\"country\":\"DE\",\"unit\":0,\"windunit\":0,\"pressureunit\":0,\"feel_like_algo\":0}}},\"status\":\"ok\",\"time_exec\":0.021092891693115,\"time_server\":1501709269}");
    list<Station> stations = parseDevices(response);
    EXPECT_EQ(1, stations.size());
    for (const Station &station: stations) {
        EXPECT_STREQ("70:ee:50:29:48:4e", station.id().c_str());
        EXPECT_STREQ("wetterstation", station.name().c_str());
        list<Module> modules = station.modules();
        EXPECT_EQ(1, modules.size());
        for (const Module &module: modules) {
            EXPECT_STREQ("70:ee:50:29:48:4e", module.id().c_str());
            EXPECT_STREQ("Innenraum", module.name().c_str());
            EXPECT_STREQ("NAMain", module.type().c_str());
            Measures measures = module.measures();
            EXPECT_EQ(1501708372, measures.mTimeStamp);
        }
    }
}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
