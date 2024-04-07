#include <bits/stdc++.h>
#include "src/geoHash.cpp"
#include "src/RouteOptimiser.cpp"

using namespace std;

vector<Restaurant> restaurantList;
vector<Customer> customerList;

bool checkLatLong (double lat, double lon) {
    return lat <= 90 && lat >= -90 && lon <= 180 && lon >= -180;
}

int main() {
    double delPartnerLatitude, delPartnerLongitude;
    string delPartnerId;
    cin>>delPartnerId>>delPartnerLatitude>>delPartnerLongitude;

    if(!checkLatLong(delPartnerLatitude, delPartnerLongitude)) {
        cout<<"Invalid lat-long values"<<endl;
        exit(400);
    }

    DeliveryPartner deliveryPartner(delPartnerId, delPartnerLatitude, delPartnerLongitude);

    int restaurantCount;
    cin>>restaurantCount;

    for(int i=0;i<restaurantCount;i++) {
        string id;
        double lat, lon, time;
        cin>>id>>lat>>lon>>time;
        //check lat long validity
        if(!checkLatLong(lat, lon)) {
            cout<<"Invalid lat-long values"<<endl;
            exit(400);
        }

        Restaurant restaurant(id, lat, lon, time);
        restaurantList.push_back(restaurant);
    }

    int customerCount;
    cin>>customerCount;
    for(int i=0;i<customerCount;i++) {
        string customerId, restaurantId;
        double lat, lon;
        cin>>customerId>>restaurantId;
        cin >> lat>>lon;
        if(!checkLatLong(lat, lon)) {
            cout<<"Invalid lat-long values"<<endl;
            exit(400);
        }

        Customer customer(customerId, restaurantId, lat, lon);
        customerList.push_back(customer);
    }
    GeoHash geoHash;
    geoHash.initGraphMapping(deliveryPartner, restaurantList, customerList);
    geoHash.makeGeoHash(deliveryPartner,restaurantList,customerList);

    vector<vector<pair<int, double>>> deliveryGraph = geoHash.getGeoHashGraph();
    map<int, int> orderMap = geoHash.prerequisiteMap;
    map<string, int> encodingMap = geoHash.idMapper;
    map<int, string> reverseMap = geoHash.reverseMapper;

    int nodes = 1 + restaurantCount + customerCount;

    RouteOptimise routeOptimise;
    routeOptimise.OptimalPath(nodes, deliveryGraph, orderMap, reverseMap);
}
