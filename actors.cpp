class DeliveryPartner {
public :
    bool isDelPartner;
    double latitude;
    double longitude;
    DeliveryPartner(double lat, double lon) : latitude(lat), longitude(lon), isDelPartner(true) {}
};

class Restaurant {
public:
    bool isRestaurant;
    int restId;
    double latitude;
    double longitude;
    double prepTime;
    Restaurant(int id, double lat, double lon, double time) : restId(id), latitude(lat), longitude(lon),
                                    prepTime(time), isRestaurant(true) {}
};

class Customer {
public:
    int custId;
    double latitude;
    double longitude;
    Customer(int id, double lat, double lon) : custId(id),
                            latitude(lat), longitude(lon) {}
};