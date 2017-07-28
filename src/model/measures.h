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
#ifndef MEASURES_H
#define MEASURES_H

#include <cstdint>
#include <string>

namespace netatmoapi {

/**
 * @brief Container for measures.
 */
class Measures {
public:
    /**
     * @brief Enum for pressure trend.
     */
    enum PressureTrend {
        //! No pressure trend data provided or state is unknown.
        noData,
        //! Pressure trend is up-wards.
        up,
        //! Pressure trend is down-wards.
        down,
        //! Pressure trend is stable.
        stable
    };

    /**
     * Constructor.
     */
    Measures();

    /**
     * Returns the timestamp of the meausres.
     * @return The timestamp of the measures.
     */
    std::uint64_t timeStamp() const { return mTimeStamp; }

    /**
     * Sets the timestamp of the measures.
     * @param timeStamp The timestamp.
     */
    void setTimeStamp(std::uint64_t timeStamp);

    /**
     * Returns the timestamp of the min temperature.
     * @return The timestamp of the min temperature.
     */
    std::uint64_t timeStampMinTemp() const { return mTimeStampMinTemp; }

    /**
     * Sets the timestamp of the min temperature.
     * @param timeStampMinTemp The timestamp.
     */
    void setTimeStampMinTemp(std::uint64_t timeStampMinTemp);

    /**
     * Returns the timestamp of the max temperature.
     * @return The timestamp of the max temperature.
     */
    std::uint64_t timeStampMaxTemp() const { return mTimeStampMaxTemp; }

    /**
     * Sets the timestamp of the max temperature.
     * @param timeStampMaxTemp The timestamp.
     */
    void setTimeStampMaxTemp(std::uint64_t timeStampMaxTemp);

    /**
     * Returns the temperature.
     * @return The temperature.
     */
    double temperature() const { return mTemperature; }

    /**
     * Sets the temperature.
     * @param temperature The temperature.
     */
    void setTemperature(double temperature);

    /**
     * Returns the Co2 value.
     * @return The Co2 value.
     */
    double co2() const { return mCo2; }

    /**
     * Sets the Co2 value.
     * @param co2 The Co2 value.
     */
    void setCo2(double co2);

    /**
     * Returns the humidity.
     * @return The humidity.
     */
    double humidity() const { return mHumidity; }

    /**
     * Sets the humidity.
     * @param humidity The humidity.
     */
    void setHumidity(double humidity);

    /**
     * Returns the pressure.
     * @return The pressure.
     */
    double pressure() const { return mPressure; }

    /**
     * Sets the pressure.
     * @param pressure The pressure.
     */
    void setPressure(double pressure);

    /**
     * Returns the rain value.
     * @return The rain value.
     */
    double rain() const { return mRain; }

    /**
     * Sets the rain value.
     * @param rain The rain value.
     */
    void setRain(double rain);

    /**
     * Returns the wind strength.
     * @return The wind strength.
     */
    double windStrength() const { return mWindStrength; }

    /**
     * Sets the wind strength.
     * @param windStrength The wind stength.
     */
    void setWindStrength(double windStrength);

    /**
     * Returns the wind angle.
     * @return The wind angle.
     */
    double windAngle() const { return mWindAngle; }

    /**
     * Sets the wind angle.
     * @param windAngle The wind angle.
     */
    void setWindAngle(double windAngle);

    /**
     * Returns the gust strength.
     * @return The gust strength.
     */
    double gustStrength() const { return mGustStrength; }

    /**
     * Sets the gust strength.
     * @param gustStrength The gust stength.
     */
    void setGustStrength(double gustStrength);

    /**
     * Returns the gust angle.
     * @return The gust angle.
     */
    double gustAngle() const { return mGustAngle; }

    /**
     * Sets the gust angle.
     * @param gustAngle The gust angle.
     */
    void setGustAngle(double gustAngle);

    /**
     * Returns the minimum temperature.
     * @return The minimum temperature.
     */
    double minTemperature() const { return mMinTemperature; }

    /**
     * Sets the minimum temperature.
     * @param minTemperature The minimum temperature.
     */
    void setMinTemperature(double minTemperature);

    /**
     * Returns the maximum temperature.
     * @return The maximum temperature.
     */
    double maxTemperature() const { return mMaxTemperature; }

    /**
     * Sets the maximum temperature.
     * @param maxTemperature The maximum temperature.
     */
    void setMaxTemperature(double maxTemperature);

    /**
     * Returns the pressure trend for the last 12 hours.
     * @return The pressure trend.
     */
    PressureTrend pressureTrend12() const { return mPressureTrend12; }

    /**
     * Sets the pressure trend for the last 12 hours.
     * @param pressureTrend12 The pressure trend.
     */
    void setPressureTrend12(PressureTrend pressureTrend12);

    /**
     * Returns the sum of the rain for the last hour.
     * @return The sum of the rain.
     */
    double sumRain1() const { return mSumRain1; }

    /**
     * Sets the sum of the rain for the last hour.
     * @param sumRain1 The sum of the rain.
     */
    void setSumRain1(double sumRain1);

    /**
     * Returns the sum of the rain for the last 24 hours.
     * @return The sum of the rain.
     */
    double sumRain24() const { return mSumRain24; }

    /**
     * Sets the sum of the rain for the last 24 hours.
     * @param sumRain24 The sum of the rain.
     */
    void setSumRain24(double sumRain24);

    /**
     * Converts the pressure trend from string to PressureTrend enum.
     * @param pressureTrend The pressure trend string.
     * @return The pressure trend enum value.
     */
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
