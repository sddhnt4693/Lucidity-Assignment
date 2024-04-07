#include <bits/stdc++.h>

#include <utility>
using namespace std;

class DeliveryPartner {
public :
    string delPartnerId;
    double latitude;
    double longitude;
    DeliveryPartner(string id, double lat, double lon) : delPartnerId(std::move(id)), latitude(lat), longitude(lon){}
};

class Restaurant {
public:
    string restId;
    double latitude;
    double longitude;
    double prepTime;
    Restaurant(string id, double lat, double lon, double time) : restId(std::move(id)), latitude(lat), longitude(lon),
                                    prepTime(time) {}
};

class Customer {
public:
    string customerId;
    string restId;
    double latitude;
    double longitude;
    Customer(string cId, string rId ,double lat, double lon) : customerId(std::move(cId)),
                            restId(restId), latitude(lat), longitude(lon) {}
};