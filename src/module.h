#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <unordered_map>
#include <cstdint>

#include "measures.h"

namespace netatmoapi {

class Module {
public:
    Module(const std::string &name, const std::string &id, const std::string &type);

    std::string name() const { return mName; }
    void setName(const std::string &name);
    std::string id() const { return mId; }
    void setId(const std::string &id);
    std::string type() const { return mType; }
    void setType(const std::string &type);
    std::unordered_map<std::uint64_t, Measures> measures() const { return mMeasures; }
    void setMeasures(const std::unordered_map<std::uint64_t, Measures> &measures);

    static const std::string sTypeOutdoor;
    static const std::string sTypeWindGauge;
    static const std::string sTypeRainGauge;
    static const std::string sTypeIndoor;

private:
    std::string mName;
    std::string mId;
    std::string mType;
    std::unordered_map<std::uint64_t, Measures> mMeasures;
};

}

#endif /* MODULE_H */
