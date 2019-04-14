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

#include "core/parsing.h"
#include "model/station.h"

#include <gtest/gtest.h>

using namespace netatmoapi;
using namespace std;
using json = nlohmann::json;

TEST(ParseDevicesTest, parseDevices) {
    json response = json::parse("{\"body\":{\"devices\":[{\"_id\":\"70:ee:50:29:48:4e\",\"cipher_id\":\"enc:16:y+aGVZeVut\\/5aKVfwFPW5FcNsBQ4ugLGB3FjOo05QrOe\\/2ag5gMshltnTt4jBM01\",\"last_status_store\":1509446958,\"modules\":[{\"_id\":\"02:00:00:29:2c:7a\",\"type\":\"NAModule1\",\"last_message\":1509446955,\"last_seen\":1509446923,\"dashboard_data\":{\"time_utc\":1509446923,\"Temperature\":8.2,\"temp_trend\":\"up\",\"Humidity\":84,\"date_max_temp\":1509446923,\"date_min_temp\":1509406779,\"min_temp\":3.8,\"max_temp\":8.2},\"data_type\":[\"Temperature\",\"Humidity\"],\"module_name\":\"Aussenraum\",\"last_setup\":1495880112,\"battery_vp\":5704,\"battery_percent\":88,\"rf_status\":75,\"firmware\":45},{\"_id\":\"05:00:00:04:53:b2\",\"type\":\"NAModule3\",\"last_message\":1509446936,\"last_seen\":1509446936,\"dashboard_data\":{\"time_utc\":1509446936,\"Rain\":0,\"sum_rain_24\":0,\"sum_rain_1\":0},\"data_type\":[\"Rain\"],\"module_name\":\"Niederschlagsmesser\",\"last_setup\":1504020591,\"battery_vp\":5968,\"battery_percent\":99,\"rf_status\":82,\"firmware\":8},{\"_id\":\"06:00:00:01:d9:f2\",\"type\":\"NAModule2\",\"last_message\":1509446827,\"last_seen\":1509446827,\"dashboard_data\":{\"WindAngle\":90,\"WindStrength\":2,\"GustAngle\":90,\"GustStrength\":4,\"time_utc\":1509446827,\"WindHistoric\":[{\"WindStrength\":1,\"WindAngle\":90,\"time_utc\":1509443616},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509443911},{\"WindStrength\":2,\"WindAngle\":105,\"time_utc\":1509444219},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509444526},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509444821},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509445129},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509445430},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509445737},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509446039},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509446340},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509446571},{\"WindStrength\":2,\"WindAngle\":90,\"time_utc\":1509446827}],\"date_max_wind_str\":1509436035,\"date_max_temp\":1509404683,\"date_min_temp\":1509404683,\"min_temp\":0,\"max_temp\":0,\"max_wind_angle\":128,\"max_wind_str\":10},\"data_type\":[\"Wind\"],\"module_name\":\"Windmesser\",\"last_setup\":1507197668,\"battery_vp\":6001,\"battery_percent\":100,\"rf_status\":89,\"firmware\":18}],\"place\":{\"altitude\":248,\"city\":\"Waldbreitbach\",\"country\":\"DE\",\"timezone\":\"Europe\\/Berlin\",\"location\":[7.4027088,50.555413]},\"station_name\":\"Over\",\"type\":\"NAMain\",\"dashboard_data\":{\"AbsolutePressure\":999.2,\"time_utc\":1509446950,\"Noise\":48,\"Temperature\":21.1,\"temp_trend\":\"stable\",\"Humidity\":56,\"Pressure\":1029.1,\"pressure_trend\":\"stable\",\"CO2\":1101,\"date_max_temp\":1509446041,\"date_min_temp\":1509432104,\"min_temp\":19.5,\"max_temp\":21.1},\"data_type\":[\"Temperature\",\"CO2\",\"Humidity\",\"Noise\",\"Pressure\"],\"co2_calibrating\":false,\"date_setup\":1495880328,\"last_setup\":1495880328,\"module_name\":\"Wohnzimmer\",\"firmware\":132,\"last_upgrade\":1495880134,\"wifi_status\":66,\"friend_users\":[\"59297b55ea00a0920c8b4e7d\",\"59d6247ab4809de2c18b66cc\"]}],\"user\":{\"mail\":\"thepaffy@thepaffy.de\",\"administrative\":{\"lang\":\"de-DE\",\"reg_locale\":\"de-DE\",\"country\":\"DE\",\"unit\":0,\"windunit\":0,\"pressureunit\":0,\"feel_like_algo\":0}}},\"status\":\"ok\",\"time_exec\":0.038522005081177,\"time_server\":1509447048}");
    vector<Station> stations = parseDevices(response);
    EXPECT_EQ(1, stations.size());
    for (const Station &station: stations) {
        EXPECT_STREQ("70:ee:50:29:48:4e", station.id().c_str());
        EXPECT_STREQ("Over", station.stationName().c_str());
        vector<Module> modules = station.modules();
        EXPECT_EQ(4, modules.size());

        Module module= modules.at(0);
        EXPECT_STREQ("70:ee:50:29:48:4e", module.id().c_str());
        EXPECT_STREQ("Wohnzimmer", module.moduleName().c_str());
        EXPECT_STREQ("NAMain", module.type().c_str());
        Measures measures = module.measures();
        EXPECT_EQ(1509446950, measures.timeUtc);

        module = modules.at(1);
        EXPECT_STREQ("02:00:00:29:2c:7a", module.id().c_str());
        EXPECT_STREQ("Aussenraum", module.moduleName().c_str());
        EXPECT_STREQ("NAModule1", module.type().c_str());
        measures = module.measures();
        EXPECT_EQ(1509446923, measures.timeUtc);

        module = modules.at(2);
        EXPECT_STREQ("05:00:00:04:53:b2", module.id().c_str());
        EXPECT_STREQ("Niederschlagsmesser", module.moduleName().c_str());
        EXPECT_STREQ("NAModule3", module.type().c_str());
        measures = module.measures();
        EXPECT_EQ(1509446936, measures.timeUtc);

        module = modules.at(3);
        EXPECT_STREQ("06:00:00:01:d9:f2", module.id().c_str());
        EXPECT_STREQ("Windmesser", module.moduleName().c_str());
        EXPECT_STREQ("NAModule2", module.type().c_str());
        measures = module.measures();
        EXPECT_EQ(1509446827, measures.timeUtc);
    }
}

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
