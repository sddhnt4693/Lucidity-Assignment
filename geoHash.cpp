#include <bits/stdc++.h>
#include "actors.cpp"

using namespace std;

const int SPEED = 20;

typedef pair<int, int> pii;
class GeoHash {
    public :
    static vector<vector<pii>> geoHashGraph;

    map<string, int> idMapper;
    map<string, string> orderMap;

    void initGraphMapping(const DeliveryPartner& deliveryPartner,
                          const vector<Restaurant>& restaurantList,
                          const vector<Customer>& customerList) {
        initialiseMapping(deliveryPartner, restaurantList, customerList);
    }
    vector<vector<pii>> getGeoHash(const DeliveryPartner& deliveryPartner,
                                   const vector<Restaurant>& restaurantList,
                                   const vector<Customer>& customerList) {
        populateGeoHash(deliveryPartner, restaurantList, customerList);
        return geoHashGraph;
    }

    private :
    void initialiseMapping(const DeliveryPartner& deliveryPartner,
                           const vector<Restaurant>& restaurantList,
                           const vector<Customer>& customerList) {
        int start = 0;
        idMapper[deliveryPartner.delPartnerId] = start;
        start++;

        for(const auto& restaurant : restaurantList) {
            idMapper[restaurant.restId] = start;
            start++;
        }

        for(const auto& customer : customerList) {
            orderMap[customer.customerId] = customer.restId;
            idMapper[customer.customerId] = start;
            start++;
        }
    }
    void populateGeoHash(const DeliveryPartner& delPartner,
                         const vector<Restaurant>& restaurantList,
                         const vector<Customer>& customerList) {

        for(const auto& restaurant : restaurantList) {
            double distance = calculateHaversineDist({delPartner.latitude, delPartner.longitude},
                                                     {restaurant.latitude, restaurant.longitude});
            double timeRequired = distance/SPEED * 60;
            timeRequired += restaurant.prepTime;
            geoHashGraph[idMapper[delPartner.delPartnerId]].push_back({idMapper[restaurant.restId], timeRequired});
        }

        for(const auto& restaurant : restaurantList) {
            for(const auto& customer : customerList) {
                double distance = calculateHaversineDist({customer.latitude, customer.longitude},
                                                         {restaurant.latitude, restaurant.longitude});
                double timeRequired = distance/SPEED * 60;

                geoHashGraph[idMapper[customer.customerId]].push_back({idMapper[restaurant.restId], timeRequired});
            }
        }

        for(const auto& customer : customerList) {
            double distance = calculateHaversineDist({delPartner.latitude, delPartner.longitude},
                                                     {customer.latitude, customer.longitude});
            double timeRequired = distance/SPEED * 60;
            geoHashGraph[idMapper[delPartner.delPartnerId]].push_back({idMapper[customer.restId], timeRequired});
        }
    }

    static double calculateHaversineDist (pair<double, double> source,
                                        pair<double, double> dest) {
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