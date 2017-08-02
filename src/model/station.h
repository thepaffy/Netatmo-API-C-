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

#include "module.h"

#include <list>
#include <string>
#include <memory>
#include <stdexcept>

namespace netatmoapi {

struct StationPrivate;

/**
 * @brief This class represents a netatmo weather station.
 *
 * The station has a id.
 * The class holds also all modules of a station.
 */
class Station {
public:
    /**
     * Default constructor.
     */
    Station();

    /**
     * Constructor.
     * @param name The station name.
     * @param id The station id (MAC-Address).
     */
    explicit Station(std::string &&name, std::string &&id);

    /**
     * Copy constructor.
     * @param o The element to copy.
     */
    Station(const Station &o);

    /**
     * Move constructor.
     * @param o The element to move.
     */
    Station(Station &&o) noexcept;

    /**
     * Destructor.
     * Is default.
     */
    virtual ~Station() noexcept;

    /**
     * Returns the name of the station,
     * @return The name.
     */
    std::string name() const;

    /**
     * Set the name of the station.
     * @param name The name.
     */
    void setName(std::string &&name);

    /**
     * Returns the id of the station.
     * @return The id.
     */
    std::string id() const;

    /**
     *Sets the id of the station.
     * @param id The id.
     */
    void setId(std::string &&id);

    /**
     * Returns the modules of the station.
     * @return A std::list with all [Modules](@ref netatmoapi::Module) of the station.
     */
    std::list<Module> modules() const;

    /**
     * Sets the modules of the station.
     * @param modules A std::list with all [Modules](@ref netatmoapi::Module) for the Station.
     */
    void setModules(std::list<Module> &&modules);

    /**
     * Add a module to the station.
     * @param module The Module.
     */
    void addModule(Module &&module);

    /**
     * Copy assign operator.
     * @param o The Element to copy.
     * @return This element as reference.
     */
    Station &operator =(const Station &o);

    /**
     * Move assign operator.
     * @param o The Element to move.
     * @return This element as reference.
     */
    Station &operator =(Station &&o) noexcept;

private:
    std::unique_ptr<StationPrivate> d;
};

}

#endif /* STATION_H */
