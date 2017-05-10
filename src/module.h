#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <cstdint>

#include "measures.h"

namespace netatmoapi {

class Module {
public:
    Module();
    explicit Module(const std::string &name, const std::string &id, const std::string &type, std::uint8_t batteryPercent, std::uint8_t rfStatus);

    std::string name() const { return mName; }
    void setName(const std::string &name);
    std::string id() const { return mId; }
    void setId(const std::string &id);
    std::string type() const { return mType; }
    void setType(const std::string &type);
    std::uint8_t batteryPercent() const { return mBatteryPercent; }
    void setBatteryPercent(std::uint8_t batteryPercent);
    std::uint8_t rfStatus() const { return mRfStatus; }
    void setRfStatus(std::uint8_t rfStatus);
    Measures measures() const { return mMeasures; }
    void setMeasures(const Measures &measures);

    static const std::string sTypeBase;
    static const std::string sTypeOutdoor;
    static const std::string sTypeWindGauge;
    static const std::string sTypeRainGauge;
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
