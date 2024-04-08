#include <bits/stdc++.h>
#include "actors.cpp"

using namespace std;

const int SPEED = 20;

typedef pair<int, double> pid;

class GeoHash {
public :
    vector<vector<pid>> geoHashGraph;
    map<string, int> idMapper;
    map<int, int> prerequisiteMap;
    map<int, string> reverseMapper;

    void initGraphMapping(const DeliveryPartner &deliveryPartner,
                          const vector<Restaurant> &restaurantList,
                          const vector<Customer> &customerList) {
        initialiseMapping(deliveryPartner, restaurantList, customerList);
    }

    vector<vector<pid>> getGeoHashGraph() {
        return geoHashGraph;
    }

    void makeGeoHash(const DeliveryPartner &deliveryPartner,
                     const vector<Restaurant> &restaurantList,
                     const vector<Customer> &customerList) {
        int nodes = 1 + restaurantList.size() + customerList.size();
        vector<pair<int, double>> temp;
        geoHashGraph.assign(nodes, temp);
        populateGeoHash(deliveryPartner, restaurantList, customerList);
    }

private :
    void initialiseMapping(const DeliveryPartner &deliveryPartner,
                           const vector<Restaurant> &restaurantList,
                           const vector<Customer> &customerList) {
        int start = 0;
        idMapper[deliveryPartner.delPartnerId] = start;
        reverseMapper[start] = deliveryPartner.delPartnerId;
        start++;

        for (const auto &restaurant: restaurantList) {
            idMapper[restaurant.restId] = start;
            reverseMapper[start] = restaurant.restId;
            start++;
        }

        for (const auto &customer: customerList) {
            idMapper[customer.customerId] = start;
            reverseMapper[start] = customer.customerId;
            start++;
        }

        for (const auto &customer: customerList) {
            prerequisiteMap[idMapper[customer.customerId]] = idMapper[customer.restId];
        }
    }

    void populateGeoHash(const DeliveryPartner &delPartner,
                         const vector<Restaurant> &restaurantList,
                         const vector<Customer> &customerList) {
        for (const auto restaurant: restaurantList) {
            double distance = calculateHaversineDist({delPartner.latitude, delPartner.longitude},
                                                     {restaurant.latitude, restaurant.longitude});
            double timeRequired = distance / SPEED * 60;
            timeRequired += restaurant.prepTime;

            geoHashGraph[idMapper[delPartner.delPartnerId]].emplace_back(idMapper[restaurant.restId], timeRequired);
            geoHashGraph[idMapper[restaurant.restId]].emplace_back(idMapper[delPartner.delPartnerId], timeRequired);
        }

        for (auto restaurant: restaurantList) {
            for (auto customer: customerList) {
                double distance = calculateHaversineDist({customer.latitude, customer.longitude},
                                                         {restaurant.latitude, restaurant.longitude});
                double timeRequired = distance / SPEED * 60;
                geoHashGraph[idMapper[customer.customerId]].emplace_back(idMapper[restaurant.restId], timeRequired);
                geoHashGraph[idMapper[restaurant.restId]].emplace_back(idMapper[customer.customerId], timeRequired);
            }
        }
        for (auto customer: customerList) {
            double distance = calculateHaversineDist({delPartner.latitude, delPartner.longitude},
                                                     {customer.latitude, customer.longitude});
            double timeRequired = distance / SPEED * 60;

            geoHashGraph[idMapper[delPartner.delPartnerId]].emplace_back(idMapper[customer.customerId], timeRequired);
            geoHashGraph[idMapper[customer.customerId]].emplace_back(idMapper[delPartner.delPartnerId], timeRequired);
        }

        for (int i = 0; i < customerList.size() - 1; i++) {
            for (int j = i + 1; j < customerList.size(); j++) {
                double distance = calculateHaversineDist({customerList[i].latitude, customerList[i].longitude},
                                                         {customerList[j].latitude, customerList[j].longitude});
                double timeRequired = distance / SPEED * 60;
                geoHashGraph[idMapper[customerList[i].customerId]].emplace_back(idMapper[customerList[j].customerId],
                                                                                timeRequired);
                geoHashGraph[idMapper[customerList[j].customerId]].emplace_back(idMapper[customerList[i].customerId],
                                                                                timeRequired);
            }
        }

        for (int i = 0; i < restaurantList.size() - 1; i++) {
            for (int j = i + 1; j < restaurantList.size(); j++) {
                double distance = calculateHaversineDist({restaurantList[i].latitude, restaurantList[i].longitude},
                                                         {restaurantList[j].latitude, restaurantList[j].longitude});
                double timeRequired = distance / SPEED * 60;

                geoHashGraph[idMapper[restaurantList[i].restId]].emplace_back(idMapper[restaurantList[j].restId],
                                                                              timeRequired);
                geoHashGraph[idMapper[restaurantList[j].restId]].emplace_back(idMapper[restaurantList[i].restId],
                                                                              timeRequired);
            }
        }
    }

    static double calculateHaversineDist(pair<double, double> source,
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