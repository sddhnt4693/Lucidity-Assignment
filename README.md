Assumptions : 
```
#1 - only one delivery executive - but code is extensible for multiple Restaurants and customers
#2 - we'll be given latitude and longitude as location of all the nodes - distance to be calculated by Haversine formula
#3 - mapping between customers and restaurant - each customer has ordered from **at most one** restaurant, and **all restaurants have been ordered from at least once**
```

Please Follow the input format given below : 
```
delPartnerId 12.1 70.1                    // delivery partner Id, latitude and longitude taken as input first
2                                         // number of restaurants  = n (no restaurant here is not ordered from
rest1 12.2 70.2 5                         // n lines follow :
rest2 12.3 70.3 5                         // restaurantId, lat, long and average prep time (in minutes) of restaurant is plugged in 
2                                         // k = number of customres, k = 2
cust1 rest1 12.4 70.2                     // k lines follow with ith line describing
cust2 rest2 12.5 70.5                     // customerId, restaurantId of restaurant they have ordered from, latitude, longitude
```
Approach : 
please check this link for approach : https://docs.google.com/document/d/1g-ECAQyCoVBSndyiui6xqqZj2a2MpjBjs2fpCqxyk_k/edit

Output format - 
IDs of respective actors will be printed in order they need to be visited : eg - rest1 rest2 cust1 cust2

**NOTE**
Testing for this was done manually and the method is mentioned in the doc
sample test case : 
```
dp 12.1 70.1
2
rest1 12.2 70.2 5
rest2 12.3 70.3 5
2
cust1 rest1 12.4 70.2
cust2 rest2 12.5 70.5
```
output was rest1 rest2 cust1 cust2
this path takes the least time (258.15 minutes)
