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
 *
 * The station has a id.
 * The class holds also all modules of a station.
 */
class NETATMOAPI___EXPORT Station {
public:
    /**
     * Constructor.
     * @param name The station name.
     * @param id The station id (MAC-Address).
     */
    explicit Station(const std::string &id, const std::string &stationName, const std::string &moduleName, bool co2Calibrating, std::uint32_t firmware, std::uint64_t lastUpgrade, std::uint16_t wifiStatus);

    explicit Station(const nlohmann::json &station);

    /**
     * Returns the name of the station,
     * @return The name.
     */
    const std::string &stationName() const {
        return mStationName;
    }

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

    bool co2Calibrating() const {
        return mCo2Calibrating;
    }

    std::uint32_t firmware() const {
        return mFirmware;
    }

    std::uint64_t lastUpgrade() const {
        return mLastUpgrade;
    }

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
     * @param modules A std::list with all [Modules](@ref netatmoapi::Module) for the Station.
     */
    void setModules(std::vector<Module> &&modules);

    /**
     * Add a module to the station.
     * @param module The Module.
     */
    void addModule(Module &&module);

    const Measures &measures() const {
        return mMeasures;
    }

    void setMeasures(Measures &&measures);

    const Place &place() const {
        return mPlace;
    }

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
