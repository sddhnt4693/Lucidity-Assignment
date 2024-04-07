#include <bits/stdc++.h>
#include "actors.cpp"
#include "geoHash.cpp"

using namespace std;

vector<Restaurant> restaurantList;
vector<Customer> customerList;

bool checkLatLong (double lat, double lon) {
    return lat <= 90 && lat >= -90 && lon <= 180 && lon >= -180;
}

map<string,int>mapping;
int lastUsed = 0;

int main() {
    double delPartnerLatitude, delPartnerLongitude;
    string delPartnerId;
    cout<<"Insert delivery partner id, latitude and longitude"<<endl;
    cin>>delPartnerId>>delPartnerLatitude>>delPartnerLongitude;

    if(!checkLatLong(delPartnerLatitude, delPartnerLongitude)) {
        cout<<"Invalid lat-long values"<<endl;
        exit(400);
    }

    DeliveryPartner deliveryPartner(delPartnerId, delPartnerLatitude, delPartnerLongitude);

    int restaurantCount;
    cout<<"Insert number of restaurants"<<endl;
    cin>>restaurantCount;

    cout<<"Insert the ids, latitudes, longitudes and average prep time of these restaurants"<<endl;
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
    cout<<"Insert number of customers"<<endl;
    cin>>customerCount;

    cout<<"Insert the customerIds, restaurantId from which customer has ordered, latitudes and longitudes in order"<<endl;
    for(int i=0;i<customerCount;i++) {
        string customerId, restaurantId;
        double lat, lon;
        cin>>customerId>>restaurantId>>lat>>lon;

        if(!checkLatLong(lat, lon)) {
            cout<<"Invalid lat-long values"<<endl;
            exit(400);
        }

        Customer customer(customerId, restaurantId, lat, lon);
        customerList.push_back(customer);
    }
    GeoHash geoHash;
    geoHash.initGraphMapping(deliveryPartner, restaurantList, customerList);

    vector<vector<pair<int, int>>> deliveryGraph = geoHash.getGeoHash(deliveryPartner, restaurantList, customerList);
}
