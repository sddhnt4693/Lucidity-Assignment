class DeliveryPartner {
public :
    bool isDelPartner;
    int delPartnerId;
    int latitude;
    int longitude;
    DeliveryPartner(int id, int lat, int lon) : delPartnerId(id), latitude(lat), longitude(lon), isDelPartner(true) {}
};

class Restaurant {
public:
    bool isRestaurant;
    int restId;
    int latitude;
    int longitude;
    int prepTime;
    Restaurant(int id, int lat, int lon, int time) : restId(id), latitude(lat), longitude(lon),
                                    prepTime(time), isRestaurant(true) {}
};

class Customer {
public:
    int custId;
    int restId;
    int latitude;
    int longitude;
    Customer(int id, int rId, int lat, int lon) : custId(id), restId(rId),
                            latitude(lat), longitude(lon) {}
};