#ifndef STATION_H
#define STATION_H

#include <list>
#include <string>

#include "module.h"

namespace netatmoapi {

class Station {
public:
    Station(const std::string &name, const std::string &id);

    std::string name() const { return mName; }
    void setName(const std::string &name);
    std::string id() const { return mId; }
    void setId(const std::string &id);
    std::list<Module> modules() const { return mModules; }
    void setModules(const std::list<Module> &modules);
    void addModule(const Module &module);

private:
    std::string mName;
    std::string mId;
    std::list<Module> mModules;
};

}

#endif /* STATION_H */
