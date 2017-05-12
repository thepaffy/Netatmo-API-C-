#ifndef STATION_H
#define STATION_H

#include <unordered_map>
#include <string>

#include "module.h"

namespace netatmoapi {

/**
 * @brief This class represents a netatmo weather station.
 *
 * The station has a id.
 * The class holds also all modules of a station.
 */
class Station {
public:
    /**
     * Constructor.
     * @param id The station id (MAC-Address).
     */
    explicit Station(const std::string &id);

    /**
     * Returns the id of the station.
     * @return The id.
     */
    std::string id() const { return mId; }

    /**
     *Sets the id of the station.
     * @param id The id.
     */
    void setId(const std::string &id);

    /**
     * Returns the modules of the station.
     * @return A std::unorderd_map with the [id](@ref netatmoapi::Module::id) (MAC-Address) as key and the Module as value.
     */
    std::unordered_map<std::string, Module> modules() const { return mModules; }

    /**
     * Sets the modules of the station.
     * @param modules A std::unorderd_map with the [id](@ref netatmoapi::Module::id) (MAC-Address) as key and the Module as value.
     */
    void setModules(const std::unordered_map<std::string, Module> &modules);

    /**
     * Add a module to the station.
     * @param moduleId The [id](@ref netatmoapi::Module::id) (MAC-Address) of the module.
     * @param module The Module.
     */
    void addModule(const std::string &moduleId, const Module &module);

    //! \todo Add function that return module by id. Add function to return the ids of all modules.

private:
    std::string mId;
    std::unordered_map<std::string, Module> mModules;
};

}

#endif /* STATION_H */
