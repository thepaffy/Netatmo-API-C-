#include "place.h"

using namespace std;
using json = nlohmann::json;

namespace netatmoapi {

Place::Location::Location() :
    latitude(0),
    longitude(0)
{
}

Place::Location::Location(const json &location) :
    latitude(location[1]),
    longitude(location[0]) {
}

Place::Place() :
    mAltitude(0)
{
}

Place::Place(uint32_t altitude, const string &city, const string &country, const string &timezone) :
    mAltitude(altitude),
    mCity(city),
    mCountry(country),
    mTimezone(timezone) {
}

Place::Place(const json &place) :
    mAltitude(place["altitude"]),
    mCity(place["city"].get<json::string_t>()),
    mCountry(place["country"].get<json::string_t>()),
    mTimezone(place["timezone"].get<json::string_t>()),
    mLocation(place["location"])
{
}

void Place::setLocation(Location &&location) {
    mLocation = move(location);
}

}
