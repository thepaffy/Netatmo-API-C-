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
#ifndef STATION_H
#define STATION_H

#include "netatmoapi++_export.h"
#include "module.h"
#include "place.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <nlohmann/json.hpp>

namespace netatmoapi {

/**
 * @brief This class represents a netatmo weather station.
 */
class NETATMOAPI___EXPORT Station {
public:
    /**
     * Constructs a station instance by all station parameters.
     * @param id The station id (MAC-Address).
     * @param stationName The station name.
     * @param moduleName The module name of the main module.
     * @param co2Calibrating The CO2 calibrating state.
     * @param firmware The firmware version.
     * @param lastUpgrade The last upgrade date.
     * @param wifiStatus The wifi status of the station.
     */
    explicit Station(const std::string &id, const std::string &stationName, const std::string &moduleName, bool co2Calibrating, std::uint32_t firmware, std::uint64_t lastUpgrade, std::uint16_t wifiStatus);

    /**
     * Constructs a station instance by a json node.
     * The constructor pareses the json node and initialize the station with all sub classes.
     * @param station The json node for the station.
     */
    explicit Station(const nlohmann::json &station);

    /**
     * Returns the name of the station.
     * @return The station name.
     */
    const std::string &stationName() const {
        return mStationName;
    }

    /**
     * Returns the name of the module.
     * @return The module name.
     */
    const std::string &moduleName() const {
        return mModuleName;
    }

    /**
     * Returns the id of the station.
     * @return The id.
     */
    const std::string &id() const {
        return mId;
    }

    /**
     * Returns the stations CO2 calibrating state.
     * @return The CO2 calibrating state.
     */
    bool co2Calibrating() const {
        return mCo2Calibrating;
    }

    /**
     * Returns the stations firmware version of the station.
     * @return The firmware version.
     */
    std::uint32_t firmware() const {
        return mFirmware;
    }

    /**
     * Returns the last firmware upgrade timestamp of the station.
     * @return The last firmware upgradetimestamp.
     */
    std::uint64_t lastUpgrade() const {
        return mLastUpgrade;
    }

    /**
     * Returns the wifi status of the station.
     * @return The wifi status.
     */
    std::uint16_t wifiStatus() const {
        return mWifiStatus;
    }

    /**
     * Returns the modules of the station.
     * @return A std::list with all [Modules](@ref netatmoapi::Module) of the station.
     */
    const std::vector<Module> &modules() const {
        return mModules;
    }

    /**
     * Sets the modules of the station.
     * @param modules A std::vector with all [Modules](@ref netatmoapi::Module) for the Station. The parameter will be moved.
     */
    void setModules(std::vector<Module> &&modules);

    /**
     * Add a module to the station.
     * @param module A [Module](@ref netatmoapi::Module) for the station. The parameter will be moved.
     */
    void addModule(Module &&module);

    /**
     * Returns the stations main module measures.
     * @return The [Measures](@ref netatmoapi::Measures) of the stations main module.
     */
    const Measures &measures() const {
        return mMeasures;
    }

    /**
     * Sets the stations main module measures.
     * @param measures The [Measures](@ref netatmoapi::Measures) of the stations main module. The parameter will be moved.
     */
    void setMeasures(Measures &&measures);

    /**
     * Returns the stations place.
     * @return The [Place](@ref netatmoapi::Place) of the station.
     */
    const Place &place() const {
        return mPlace;
    }

    /**
     * Sets the stations place.
     * @param place The [Place](@ref netatmoapi::Place) of the station. The parameter will be moved.
     */
    void setPlace(Place &&place);

private:
    std::string mId;
    std::string mStationName;
    std::string mModuleName;
    std::vector<Module> mModules;
    Measures mMeasures;
    bool mCo2Calibrating;
    std::uint32_t mFirmware;
    std::uint64_t mLastUpgrade;
    std::uint16_t mWifiStatus;
    Place mPlace;
};

}

#endif /* STATION_H */
