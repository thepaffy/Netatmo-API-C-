#ifndef STATION_H
#define STATION_H

#include <unordered_map>
#include <string>

#include "module.h"

namespace netatmoapi {

class Station {
public:
    Station(const std::string &id);

    std::string id() const { return mId; }
    void setId(const std::string &id);
    std::unordered_map<std::string, Module> modules() const { return mModules; }
    void setModules(const std::unordered_map<std::string, Module> &modules);
    void addModule(const std::string &moduleId, const Module &module);

private:
    std::string mId;
    std::unordered_map<std::string, Module> mModules;
};

}

#endif /* STATION_H */
