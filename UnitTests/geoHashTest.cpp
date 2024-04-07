#include <bits/stdc++.h>
#include "../src/geoHash.cpp"

using namespace std;

class geoHashTest {
public:
    GeoHash geoHash;
    vector<Restaurant> restaurantList;
    vector<Customer> customerList;

    DeliveryPartner deliveryPartner = *new DeliveryPartner("delprt",12.934938219218925, 77.62543838205703);
    Restaurant restaurant1 = *new Restaurant("abcd", 12.935095779273444, 77.62925317745409, 20);
    Restaurant restaurant2 = *new Restaurant("efgh", 12.933961715641061, 77.61964648941698, 15);
    Customer customer1 = *new Customer("customer1", "abcd", 12.935207758527447, 77.62666306671642);
    Customer customer2 = *new Customer("customer2", "efgh", 12.928931267408323, 77.63200241273806);

    void mappingTest() {
        restaurantList.push_back(restaurant1);
        customerList.push_back(customer1);
        geoHash.initGraphMapping(deliveryPartner, restaurantList, customerList);
        geoHash.makeGeoHash(deliveryPartner,restaurantList,customerList);
        vector<vector<pair<int,int>>> graph = geoHash.getGeoHashGraph();
        for(auto v:graph) {
            for(int i=0;i<v.size();i++) {
                cout<<i<<" "<<v[i].first<<" "<<v[i].second;
            }
        }
    }
};