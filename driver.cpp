#include "Driver.h"

#include <iostream>

Driver::Driver(std::string firstName, std::string lastName, std::string gender,
               int age, std::string phoneNumber, std::string rating, double currentLatitude,
               double currentLongitude, std::string vehicleType, std::string& currentState,
               std::string& riderFirstName, std::string& riderLastName, std::string& riderPhoneNumber)
    : firstName(firstName), lastName(lastName), gender(gender), age(age), phoneNumber(phoneNumber),
      rating(rating), currentLatitude(currentLatitude), currentLongitude(currentLongitude),
      vehicleType(vehicleType), status(currentState), riderFirstName(riderFirstName),
      riderLastName(riderLastName), riderPhoneNumber(riderPhoneNumber) {}

// setters
void Driver::set_status(std::string driver_status)
{
    status = driver_status;
}
void Driver::set_riderFirstName(std::string rider_firstname)
{
    riderFirstName = rider_firstname;
}
void Driver::set_riderLastName(std::string rider_lastname)
{
    riderLastName = rider_lastname;
}
void Driver::set_riderNumber(std::string rider_number)
{
    riderPhoneNumber = rider_number;
}