#include "measures.h"
#include <limits>

using namespace std;

namespace netatmoapi {

Measures::Measures() :
    timeStamp(0),
    temperature(numeric_limits<double>::min()),
    co2(numeric_limits<int32_t>::min()),
    humidity(numeric_limits<int32_t>::min()),
    pressure(numeric_limits<int32_t>::min()),
    noise(numeric_limits<int32_t>::min()),
    rain(numeric_limits<double>::min()),
    windStrength(numeric_limits<double>::min()),
    windAngle(numeric_limits<int32_t>::min()),
    gustStrength(numeric_limits<double>::min()),
    gustAngle(numeric_limits<int32_t>::min()),
    minTemperature(numeric_limits<double>::min()),
    maxTemperature(numeric_limits<double>::min()),
    minHumidity(numeric_limits<int32_t>::min()),
    maxHumidity(numeric_limits<int32_t>::min()),
    minPressure(numeric_limits<int32_t>::min()),
    maxPressure(numeric_limits<int32_t>::min()),
    minNoise(numeric_limits<int32_t>::min()),
    maxNoise(numeric_limits<int32_t>::min()),
    sumRain(numeric_limits<double>::min()),
    dateMaxGust(numeric_limits<double>::min()),
    dateMaxHumidity(numeric_limits<int32_t>::min()),
    dateMinPressure(numeric_limits<int32_t>::min()),
    dateMaxPressure(numeric_limits<int32_t>::min()),
    dateMinNoise(numeric_limits<int32_t>::min()),
    dateMaxNoise(numeric_limits<int32_t>::min()),
    dateMinCo2(numeric_limits<int32_t>::min()),
    dateMaxCo2(numeric_limits<int32_t>::min())
{

}

}
