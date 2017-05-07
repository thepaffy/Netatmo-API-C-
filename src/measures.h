#ifndef MEASURES_H
#define MEASURES_H

#include <cstdint>

namespace netatmoapi {

struct Measures {
    Measures();

    std::uint64_t   timeStamp;
    double          temperature;
    std::int32_t    co2;
    std::int32_t    humidity;
    std::int32_t    pressure;
    std::int32_t    noise;
    double          rain;
    double          windStrength;
    std::int32_t    windAngle;
    double          gustStrength;
    std::int32_t    gustAngle;
    double          minTemperature;
    double          maxTemperature;
    std::int32_t    minHumidity;
    std::int32_t    maxHumidity;
    std::int32_t    minPressure;
    std::int32_t    maxPressure;
    std::int32_t    minNoise;
    std::int32_t    maxNoise;
    double          sumRain;
    double          dateMaxGust;
    std::int32_t    dateMaxHumidity;
    std::int32_t    dateMinPressure;
    std::int32_t    dateMaxPressure;
    std::int32_t    dateMinNoise;
    std::int32_t    dateMaxNoise;
    std::int32_t    dateMinCo2;
    std::int32_t    dateMaxCo2;
};

}

#endif /* MEASURES_H */
