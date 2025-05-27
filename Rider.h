#ifndef RIDER_H
#define RIDER_H

#include <string>
#include <vector>

class Rider
{
private:
    std::string firstName;
    std::string lastName;
    std::string gender;
    int age;
    std::string phoneNumber;
    std::string rating;
    std::string pickupLocation;
    double pickupLatitude;
    double pickupLongitude;
    std::string dropoffLocation;
    double dropoffLatitude;
    double dropoffLongitude;
    std::string vehiclePreference;
    std::string currentState;

    std::string driverFirstName;
    std::string driverLastName;
    std::string driverPhoneNumber;

public:
    //default constructor
    Rider();
    
    // constructor with all attribute values given
    Rider(std::string firstName,  std::string lastName, std::string gender,
          int age, std::string phoneNumber, std::string rating, std::string pickupLocation,
          double pickupLatitude, double pickupLongitude, std::string dropoffLocation,
          double dropoffLatitude, double dropoffLongitude, std::string& vehiclePreference,
          std::string& currentState, std::string& driverFirstName,
          std::string& driverLastName, std::string& driverPhoneNumber);

    // getter functions so that other files have access to private attributes
    std::string get_firstname() const {return firstName;};
    std::string get_lastname() const {return lastName;};
    std::string get_gender() const {return gender;};
    int get_age() const {return age;};
    std::string get_number() const {return phoneNumber;};
    std::string get_rating() const {return rating;};
    std::string get_pickLoc() const {return pickupLocation;};
    double get_pickupLat() const {return pickupLatitude;};
    double get_pickupLong() const {return pickupLongitude;};
    std::string get_dropLoc() const {return dropoffLocation;};
    double get_dropLat() const {return dropoffLatitude;};
    double get_dropLong() const {return dropoffLongitude;};
    std::string get_vPref() const {return vehiclePreference;};
    std::string get_status() const {return currentState;};
    std::string get_driverFirst() const {return driverFirstName;};
    std::string get_driverLast() const {return driverLastName;};
    std::string get_driverPhoneNumber() const {return driverPhoneNumber;};

    //setter functions
    void set_status(std::string driver_status);
    void set_driverFirstName(std::string rider_firstname);
    void set_driverLastName(std::string rider_lastname);
    void set_driverNumber(std::string rider_number);
};

#endif
