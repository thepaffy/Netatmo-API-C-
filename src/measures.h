#ifndef MEASURES_H
#define MEASURES_H

#include <cstdint>
#include <string>

namespace netatmoapi {

class Measures {
public:
    enum PressureTrend {
        noData,
        up,
        down,
        stable
    };

    Measures();

    std::uint64_t timeStamp() const { return mTimeStamp; }
    void setTimeStamp(std::uint64_t timeStamp);

    std::uint64_t timeStampMinTemp() const { return mTimeStampMinTemp; }
    void setTimeStampMinTemp(std::uint64_t timeStampMinTemp);

    std::uint64_t timeStampMaxTemp() const { return mTimeStampMaxTemp; }
    void setTimeStampMaxTemp(std::uint64_t timeStampMaxTemp);

    double temperature() const { return mTemperature; }
    void setTemperature(double temperature);

    double co2() const { return mCo2; }
    void setCo2(double co2);

    double humidity() const { return mHumidity; }
    void setHumidity(double humidity);

    double pressure() const { return mPressure; }
    void setPressure(double pressure);

    double rain() const { return mRain; }
    void setRain(double rain);

    double windStrength() const { return mWindStrength; }
    void setWindStrength(double windStrength);

    double windAngle() const { return mWindAngle; }
    void setWindAngle(double windAngle);

    double gustStrength() const { return mGustStrength; }
    void setGustStrength(double gustStrength);

    double gustAngle() const { return mGustAngle; }
    void setGustAngle(double gustAngle);

    double minTemperature() const { return mMinTemperature; }
    void setMinTemperature(double minTemperature);

    double maxTemperature() const { return mMaxTemperature; }
    void setMaxTemperature(double maxTemperature);

    PressureTrend pressureTrend12() const { return mPressureTrend12; }
    void setPressureTrend12(PressureTrend pressureTrend12);

    double sumRain1() const { return mSumRain1; }
    void setSumRain1(double sumRain1);

    double sumRain24() const { return mSumRain24; }
    void setSumRain24(double sumRain24);

    static PressureTrend convertPressureTrendFromString(const std::string &pressureTrend);

private:
    std::uint64_t   mTimeStamp;
    std::uint64_t   mTimeStampMinTemp;
    std::uint64_t   mTimeStampMaxTemp;
    double          mTemperature;
    double          mCo2;
    double          mHumidity;
    double          mPressure;
    double          mRain;
    double          mWindStrength;
    double          mWindAngle;
    double          mGustStrength;
    double          mGustAngle;
    double          mMinTemperature;
    double          mMaxTemperature;
    PressureTrend   mPressureTrend12;
    double          mSumRain1;
    double          mSumRain24;
};

}

#endif /* MEASURES_H */
