#include <bits/stdc++.h>
#include "actors.cpp"
#include "geoHash.cpp"

using namespace std;

vector<Restaurant> restaurantList;
vector<Customer> customerList;

bool checkLatLong (double lat, double lon) {
    return lat <= 90 && lat >= -90 && lon <= 180 && lon >= -180;
}

int main() {
    double delPartnerLatitude, delPartnerLongitude;
    cout<<"Insert delivery partner latitude and longitude"<<endl;
    cin>>delPartnerLatitude>>delPartnerLongitude;

    if(!checkLatLong(delPartnerLatitude, delPartnerLongitude)) {
        cout<<"Invalid lat-long values"<<endl;
        exit(400);
    }

    DeliveryPartner deliveryPartner(delPartnerLatitude, delPartnerLongitude);

    int restaurantCount;
    cout<<"Insert number of restaurants"<<endl;
    cin>>restaurantCount;

    cout<<"Insert the ids, latitudes, longitudes and average prep time of these restaurants"<<endl;
    for(int i=0;i<restaurantCount;i++) {
        int id;
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

    cout<<"Insert the customerIds, latitudes and longitudes in order - id of the customer will be same as Id of the restaruant they have ordered from "<<endl;
    for(int i=0;i<customerCount;i++) {
        int id, lat, lon;
        cin>>id>>lat>>lon;

        if(!checkLatLong(lat, lon)) {
            cout<<"Invalid lat-long values"<<endl;
            exit(400);
        }

        Customer customer(id, lat, lon);
        customerList.push_back(customer);
    }
    GeoHash geoHash;
    vector<vector<pair<int, int>>> deliveryGraph = geoHash.getGeoHash(deliveryPartner, restaurantList, customerList);
}
