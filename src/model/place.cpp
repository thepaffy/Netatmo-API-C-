#include "place.h"

using namespace std;

namespace netatmoapi {

Place::Place(uint32_t altitude, string &&city, string &&country, string &&timezone) :
    mAltitude(move(altitude)),
    mCity(move(city)),
    mCountry(move(country)),
    mTimezone(move(timezone)) {
}

void Place::setLocation(Location &&location) {
    mLocation = move(location);
}

}
