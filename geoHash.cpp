#include <bits/stdc++.h>
#include "actors.cpp"

using namespace std;

typedef pair<int, int> pii;
class GeoHash {
    public :
    vector<vector<pii>> geoHashGraph;

    void getGeoHash() {

    }

    private :
    void populateGeoHash(vector<DeliveryPartner> delPartnerList,
                         vector<Restaurant> restaurantList,
                         vector<Customer> customerList) {

    }

    double calculateHaversineDist (pair<double, double>& source,
                                        pair<double, double>& dest) {
        double lat1 = source.first, lon1 = source.second;
        double lat2 = dest.first, lon2 = dest.second;

        double dLat = (lat2 - lat1) *
                      M_PI / 180.0;
        double dLon = (lon2 - lon1) *
                      M_PI / 180.0;

        lat1 = (lat1) * M_PI / 180.0;
        lat2 = (lat2) * M_PI / 180.0;

        double a = pow(sin(dLat / 2), 2) +
                   pow(sin(dLon / 2), 2) *
                   cos(lat1) * cos(lat2);
        double rad = 6371;
        double c = 2 * asin(sqrt(a));
        return rad * c;
    }
};