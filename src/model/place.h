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

#include <cstdint>
#include <string>

namespace netatmoapi {

class Place {
public:
    struct Location {
        double latitude;
        double longitude;
    };

    Place() = default;

    explicit Place(std::uint32_t altitude, std::string &&city, std::string &&country, std::string &&timezone);

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
