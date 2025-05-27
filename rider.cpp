#include "Rider.h"
#include <iostream>

Rider::Rider(std::string firstName, std::string lastName, std::string gender,
             int age, std::string phoneNumber, std::string rating, std::string pickupLocation,
             double pickupLatitude, double pickupLongitude, std::string dropoffLocation,
             double dropoffLatitude, double dropoffLongitude, std::string& vehiclePreference,
             std::string& currentState, std::string& driverFirstName,
             std::string& driverLastName, std::string& driverPhoneNumber)
    : firstName(firstName), lastName(lastName), gender(gender), age(age), phoneNumber(phoneNumber),
      rating(rating), pickupLocation(pickupLocation), pickupLatitude(pickupLatitude),
      pickupLongitude(pickupLongitude), dropoffLocation(dropoffLocation), dropoffLatitude(dropoffLatitude),
      dropoffLongitude(dropoffLongitude), vehiclePreference(vehiclePreference), currentState(currentState),
      driverFirstName(driverFirstName), driverLastName(driverLastName), driverPhoneNumber(driverPhoneNumber) {}

// setters
void Rider::set_status(std::string driver_status)
{
    currentState = driver_status;
}
void Rider::set_driverFirstName(std::string rider_firstname)
{
    driverFirstName = rider_firstname;
}
void Rider::set_driverLastName(std::string rider_lastname)
{
    driverLastName = rider_lastname;
}
void Rider::set_driverNumber(std::string rider_number)
{
    driverPhoneNumber = rider_number;   
}
