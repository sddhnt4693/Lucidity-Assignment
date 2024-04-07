#include <bits/stdc++.h>

#include <utility>
using namespace std;

class DeliveryPartner {
public :
    bool isDelPartner;
    string delPartnerId;
    double latitude;
    double longitude;
    DeliveryPartner(string id, double lat, double lon) : delPartnerId(std::move(id)), latitude(lat), longitude(lon), isDelPartner(true) {}
};

class Restaurant {
public:
    bool isRestaurant;
    string restId;
    double latitude;
    double longitude;
    double prepTime;
    Restaurant(string id, double lat, double lon, double time) : restId(id), latitude(lat), longitude(lon),
                                    prepTime(time), isRestaurant(true) {}
};

class Customer {
public:
    string customerId;
    string restId;
    double latitude;
    double longitude;
    Customer(string cId, string rId ,double lat, double lon) : customerId(cId),
                            restId(restId), latitude(lat), longitude(lon) {}
};