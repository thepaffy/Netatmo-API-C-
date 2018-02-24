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
#ifndef MODULE_H
#define MODULE_H

#include "netatmoapi++_export.h"
#include "measures.h"

#include <memory>
#include <string>
#include <cstdint>
#include <nlohmann/json.hpp>

namespace netatmoapi {

/**
 * @brief This class represents a netatmo module.
 *
 * The module has a name, a id and type.
 * The class holds also informations about battery and wifi state.
 * Also the measures of the module are provided.
 */
class NETATMOAPI___EXPORT Module {
public:
    /**
     * Constructor.
     * @param name The module name.
     * @param id The module id (MAC-Address).
     * @param type The module type.
     * @param batteryPercent The battery status of the module.
     * @param rfStatus The wifi status of the module.
     */
    explicit Module(const std::string &id, const std::string &moduleName, const std::string &type, std::uint16_t batteryVp, std::uint16_t batteryPercent, std::uint16_t rfStatus, std::uint32_t firmware);

    explicit Module(const nlohmann::json &module);

    /**
     * Returns the name of the module.
     * @return The name.
     */
    const std::string &moduleName() const {
        return mModuleName;
    }

    /**
     * Returns the id of the module.
     * @return The id.
     */
    const std::string &id() const {
        return mId;
    }

    /**
     * Returns the type the module.
     *
     * @see [sTypeBase](@ref netatmoapi::Module::sTypeBase), [sTypeOutdoor](@ref netatmoapi::Module::sTypeOutdoor), [sTypeWindGauge](@ref netatmoapi::Module::sTypeWindGauge), [sTypeRainGauge](@ref netatmoapi::Module::sTypeRainGauge) and [sTypeIndoor](@ref netatmoapi::Module::sTypeIndoor).
     *
     * @return The type.
     */
    const std::string &type() const {
        return mType;
    }

    std::uint16_t batteryVp() const {
        return mBatteryVp;
    }

    /**
     * Returns the battery state of the module.
     * @return The barrery state.
     */
    std::uint16_t batteryPercent() const {
        return mBatteryPercent;
    }

    /**
     * Returns the rf state of the module.
     *
     * A small value indicates a good rf signal.
     *
     * @return The rf state.
     */
    std::uint16_t rfStatus() const {
        return mRfStatus;
    }

    std::uint32_t firmware() const {
        return mFirmware;
    }

    /**
     * Returns the measures of the module.
     * @return The measures.
     */
    const Measures &measures() const {
        return mMeasures;
    }

    /**
     * Sets the measures of the module.
     * @param measures
     */
    void setMeasures(Measures &&measures);

    /**
     * Base module.
     *
     * Value: "NAMain"
     */
    static const std::string sTypeBase;

    /**
     * Outdoor module.
     *
     * Value: "NAModule1"
     */
    static const std::string sTypeOutdoor;

    /**
     * Wind gauge module.
     *
     * Value: "NAModule2"
     */
    static const std::string sTypeWindGauge;

    /**
     * Rain gauge module.
     *
     * Value: "NAModule3"
     */
    static const std::string sTypeRainGauge;

    /**
     * Additional indoor module.
     *
     * Value: "NAModule4"
     */
    static const std::string sTypeIndoor;

private:
    std::string mId;
    std::string mModuleName;
    std::string mType;
    std::uint16_t mBatteryVp;
    std::uint16_t mBatteryPercent;
    std::uint16_t mRfStatus;
    std::uint32_t mFirmware;
    Measures mMeasures;
};

}

#endif /* MODULE_H */
