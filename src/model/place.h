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
#ifndef PLACE_H
#define PLACE_H

#include "netatmoapi++_export.h"

#include <cstdint>
#include <string>
#include <nlohmann/json.hpp>

namespace netatmoapi {

/**
 * @brief This class represents a netatmo place.
 */
class NETATMOAPI___EXPORT Place {
public:
    struct Location {
        Location();
        Location(const nlohmann::json &location);
        double latitude;
        double longitude;
    };

    Place();

    explicit Place(std::uint32_t altitude, const std::string &city, const std::string &country, const std::string &timezone);

    explicit Place(const nlohmann::json &place);

    std::uint32_t altitude() const {
        return mAltitude;
    }

    const std::string &city() const {
        return mCity;
    }

    const std::string &country() const {
        return mCountry;
    }

    const std::string &timezone() const {
        return mTimezone;
    }

    const Location &location() const {
        return mLocation;
    }

    void setLocation(Location &&location);

private:
    std::uint32_t mAltitude;
    std::string mCity;
    std::string mCountry;
    std::string mTimezone;
    Location mLocation;
};

}

#endif /* PLACE_H */
