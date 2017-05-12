/*
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

#include <string>
#include <cstdint>

#include "measures.h"

namespace netatmoapi {

/**
 * @brief This class represents a netatmo module.
 *
 * The module has a name, a id and type.
 * The class holds also informations about battery and wifi state.
 * Also the measures of the module are provided.
 */
class Module {
public:
    /**
     * Default constructor.
     */
    Module();

    /**
     * Constructor.
     * @param name The module name.
     * @param id The module id (MAC-Address).
     * @param type The module type.
     * @param batteryPercent The battery status of the module.
     * @param rfStatus The wifi status of the module.
     */
    explicit Module(const std::string &name, const std::string &id, const std::string &type, std::uint8_t batteryPercent, std::uint8_t rfStatus);

    /**
     * Returns the name of the module.
     * @return The name.
     */
    std::string name() const { return mName; }

    /**
     * Sets the name of the module.
     * @param name The name.
     */
    void setName(const std::string &name);

    /**
     * Returns the id of the module.
     * @return The id.
     */
    std::string id() const { return mId; }

    /**
     * Sets the id of the module.
     * @param id The id.
     */
    void setId(const std::string &id);

    /**
     * Returns the type the module.
     *
     * @see [sTypeBase](@ref netatmoapi::Module::sTypeBase), [sTypeOutdoor](@ref netatmoapi::Module::sTypeOutdoor), [sTypeWindGauge](@ref netatmoapi::Module::sTypeWindGauge), [sTypeRainGauge](@ref netatmoapi::Module::sTypeRainGauge) and [sTypeIndoor](@ref netatmoapi::Module::sTypeIndoor).
     *
     * @return The type.
     */
    std::string type() const { return mType; }

    /**
     * Sets the type the module.
     *
     * @see [sTypeBase](@ref netatmoapi::Module::sTypeBase), [sTypeOutdoor](@ref netatmoapi::Module::sTypeOutdoor), [sTypeWindGauge](@ref netatmoapi::Module::sTypeWindGauge), [sTypeRainGauge](@ref netatmoapi::Module::sTypeRainGauge) and [sTypeIndoor](@ref netatmoapi::Module::sTypeIndoor).
     *
     * @param type The type.
     */
    void setType(const std::string &type);

    /**
     * Returns the battery state of the module.
     * @return The barrery state.
     */
    std::uint8_t batteryPercent() const { return mBatteryPercent; }

    /**
     * Sets the battery state of the module.
     * @param batteryPercent The battery state.
     */
    void setBatteryPercent(std::uint8_t batteryPercent);

    /**
     * Returns the wifi state of the module.
     *
     * A small value indicates a good wifi signal.
     *
     * @return The wifi state.
     */
    std::uint8_t rfStatus() const { return mRfStatus; }

    /**
     * Sets the wifi state of the module
     *
     * A small value indicates a good wifi signal.
     *
     * @param rfStatus
     */
    void setRfStatus(std::uint8_t rfStatus);

    /**
     * Returns the measures of the module.
     * @return The measures.
     */
    Measures measures() const { return mMeasures; }

    /**
     * Sets the measures of the module.
     * @param measures
     */
    void setMeasures(const Measures &measures);

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
    std::string mName;
    std::string mId;
    std::string mType;
    std::uint8_t mBatteryPercent;
    std::uint8_t mRfStatus;
    Measures mMeasures;
};

}

#endif /* MODULE_H */
