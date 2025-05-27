#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>

class Driver
{
private:
    std::string firstName;
    std::string lastName;
    std::string gender;
    int age;
    std::string phoneNumber;
    std::string rating;
    double currentLatitude;
    double currentLongitude;
    std::string vehicleType;
    std::string status;
    std::string riderFirstName;
    std::string riderLastName;
    std::string riderPhoneNumber;

public:
    Driver();

    Driver(std::string firstName, std::string lastName, std::string gender,
           int age, std::string phoneNumber, std::string rating, double currentLatitude,
           double currentLongitude, std::string vehicleType, std::string &currentState,
           std::string &riderFirstName, std::string &riderLastName, std::string &riderPhoneNumber);

    // getters
    std::string get_firstname() const {return firstName;};
    std::string get_lastname() const {return lastName;};
    std::string get_gender() const {return gender;};
    int get_age() const {return age;};
    std::string get_number() const {return phoneNumber;};
    std::string get_rating() const {return rating;};
    double get_currentLat() const {return currentLatitude;};
    double get_currentLong() const {return currentLongitude;};
    std::string get_vType() const {return vehicleType;};
    std::string get_status() const {return status;};
    std::string get_riderFirstName() const {return riderFirstName;};
    std::string get_riderLastName() const {return riderLastName;};
    std::string get_riderPhoneNumber() const {return riderPhoneNumber;};

    //setters
    void set_status(std::string driver_status);
    void set_riderFirstName(std::string rider_firstname);
    void set_riderLastName(std::string rider_lastname);
    void set_riderNumber(std::string rider_number);
};

#endif