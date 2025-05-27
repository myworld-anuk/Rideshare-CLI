#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip> // For std::setprecision
#include <sstream> // For std::ostringstream

#include "Driver.h"
#include "Rider.h"

std::string doubleToString(double value) 
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(4);
    stream << value;
    std::string result = stream.str();

    // Remove trailing zeros
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);

    // Removes trailing decimal point if there is
    if (result.back() == '.') {
        result.pop_back();
    }

    return result;
}

void parseDrivers(std::vector<Driver>& drivers, std::fstream& driver_file)
{
    std::string driver;
    while (getline(driver_file, driver))
    {
        std::vector<std::string> driver_attr;
        size_t start = 0;
        size_t space_index;

        // Split the driver string by spaces and save into driver_attr vector
        while ((space_index = driver.find(" ")) != std::string::npos)
        {
            driver_attr.push_back(driver.substr(start, (space_index - start)));
            driver = driver.substr((space_index - start + 1));
        }
        // Push the last part of the string
        driver_attr.push_back(driver.substr(start));

        // setting driver attributes = to indexes in vector
        if (driver_attr.size() >= 12)
        {
            std::string firstName = driver_attr[0];
            std::string lastName = driver_attr[1];
            std::string gender = driver_attr[2];
            int age = stoi(driver_attr[3]); // stoi() convert string to int
            std::string number = driver_attr[4];
            std::string rating = driver_attr[5];
            double current_latitude = stod(driver_attr[6]); // stod() convert string to float
            double current_longitude = stod(driver_attr[7]);
            std::string vehicle_type = driver_attr[8];
            std::string state = driver_attr[9];

            std::string riderFirst = driver_attr[10];
            std::string riderLast = driver_attr[11];
            std::string riderNumber = driver_attr[12];

            Driver d(firstName, lastName, gender, age, number, rating, current_latitude, current_longitude, vehicle_type, state, riderFirst, riderLast, riderNumber);
            drivers.push_back(d); // Push the Driver object into the vector
        }
        else
        {
            std::cerr << "Invalid driver entry: " << driver << std::endl;
        }
    }
}

void parseRiders(std::vector<Rider>& riders, std::fstream& rider_file)
{
    std::string rider;
    while (std::getline(rider_file, rider))
    {
        std::vector<std::string> rider_attr;
        size_t start = 0;
        size_t space_index;

        // Split the driver string by spaces and save into driver_attr vector
        while ((space_index = rider.find(" ")) != std::string::npos)
        {
            rider_attr.push_back(rider.substr(start, (space_index - start)));
            rider = rider.substr((space_index - start + 1));
        }
        // Push the last part of the string
        rider_attr.push_back(rider.substr(start));

        // setting driver attributes = to indexes in vector
        if (rider_attr.size() >= 16)
        {
            std::string firstName = rider_attr[0];
            std::string lastName = rider_attr[1];
            std::string gender = rider_attr[2];
            int age = stoi(rider_attr[3]); // stoi() convert string to int
            std::string number = rider_attr[4];
            std::string rating = rider_attr[5];
            std::string pickup_loc = rider_attr[6];
            double pickup_lat = stod(rider_attr[7]);
            double pickup_long = stod(rider_attr[8]);
            std::string dropoff_loc = rider_attr[9];
            double dropoff_lat = stod(rider_attr[10]);
            double dropoff_long = stod(rider_attr[11]);
            std::string vehicle_pref = rider_attr[12];
            std::string curr_state =  rider_attr[13];
            std::string driverFirst =  rider_attr[14];
            std::string driverLast = rider_attr[15];
            std::string driverNumber = rider_attr[16];

            Rider r(firstName, lastName, gender, age, number, rating, pickup_loc, pickup_lat, pickup_long, dropoff_loc, dropoff_lat, dropoff_long, vehicle_pref, curr_state, driverFirst, driverLast, driverNumber);
            riders.push_back(r); // Push the Driver object into the vector
        }
        else
        {
            std::cerr << "Invalid driver entry: " << rider << std::endl;
        }
    }
}
//where you print the updated drivers information, thus this file should have the same format as drivers.txt
void updateDrivers(std::ofstream& output1, std::vector<Driver>& drivers)
{
    for (size_t i = 0; i < drivers.size(); ++i)
    {
        std::string insert_line = "";
        insert_line += drivers[i].get_firstname() + " ";
        insert_line += drivers[i].get_lastname() + " ";
        insert_line +=  drivers[i].get_gender() + " ";
        insert_line += std::to_string(drivers[i].get_age()) + " ";
        insert_line += drivers[i].get_number() + " ";
        insert_line += drivers[i].get_rating() + " ";
        insert_line += doubleToString(drivers[i].get_currentLat());
        insert_line += " ";
        insert_line += doubleToString(drivers[i].get_currentLong());
        insert_line += " ";
        insert_line += drivers[i].get_vType() + " ";
        insert_line += drivers[i].get_status() + " ";
        insert_line += drivers[i].get_riderFirstName() + " ";
        insert_line += drivers[i].get_riderLastName() + " ";
        insert_line += drivers[i].get_riderPhoneNumber();

        output1 << insert_line << std::endl;
    }
}

//where you print the updated riders information, thus this file should have the same format as riders.txt
void updateRiders(std::ofstream& output2, std::vector<Rider>& riders)
{
    for (size_t i = 0; i < riders.size(); ++i)
    {
        std::string insert_line = "";
        insert_line += riders[i].get_firstname() + " ";
        insert_line += riders[i].get_lastname() + " ";
        insert_line += riders[i].get_gender() + " ";
        insert_line += std::to_string(riders[i].get_age()) + " ";
        insert_line += riders[i].get_number() + " ";
        insert_line += riders[i].get_rating() + " ";
        insert_line += riders[i].get_pickLoc() + " ";
        insert_line += doubleToString(riders[i].get_pickupLat());
        insert_line += " ";
        insert_line += doubleToString(riders[i].get_pickupLong());
        insert_line += " ";
        insert_line += riders[i].get_dropLoc() + " ";
        insert_line += doubleToString(riders[i].get_dropLat());
        insert_line += " ";
        insert_line += doubleToString(riders[i].get_dropLong());
        insert_line += " ";
        insert_line += riders[i].get_vPref() + " ";
        insert_line += riders[i].get_status() + " ";
        insert_line += riders[i].get_driverFirst() + " ";
        insert_line += riders[i].get_driverLast() + " ";
        insert_line += riders[i].get_driverPhoneNumber();

        output2 << insert_line << std::endl;
    }
}

bool validPhoneNumber(const std::string phoneNumber, std::ofstream& output0) 
{
    if (phoneNumber.length() != 12) 
    {
        output0 << "Phone number is invalid." << std::endl;
        return false;
    }
    // Check the format: xxx-xxx-xxxx
    for (size_t i = 0; i < phoneNumber.length(); ++i) 
    {
        if ((i == 3 || i == 7)) 
        {
            // Check if the 4th and 8th characters are hyphens
            if (phoneNumber[i] != '-') 
            {
                output0 << "Phone number is invalid." << std::endl;
                return false;
            }
        }
        else 
        {
            // All other characters should be digits
            if (!std::isdigit(phoneNumber[i])) 
            {
                output0 << "Phone number is invalid." << std::endl;
                return false;
            }
        }
    }
    return true;
}

int validRider(const std::string phoneNumber, std::vector<Rider>& riders, std::ofstream& output0)
{
    int index = 0;
    for (size_t i = 0; i < riders.size(); ++i)
    {
        if(riders[i].get_number() == phoneNumber) //phone number matches with a rider
        {
            if(riders[i].get_status() == "Driver_on_the_way") // rider does not have valid status
            {
                output0 << "You have already requested a ride and your driver is on the way to the pickup location." << std::endl;
                index = -1;
                return index;
            }
            else if(riders[i].get_status() == "During_the_trip")// rider does not have valid status
            {
                output0 << "You can not request a ride at this moment as you are already on a trip." << std::endl;
                index = -1;
                return index;
            }
            else if(riders[i].get_status() == "Ready_to_request")// rider has valid status
            {
                return i;
            }
            else
            {
                std::cout << "something went wrong with rider status" << i << riders[i].get_firstname() << std::endl;
            }
        }
    }
    if(index == 0) //phone number does not match with any riders
    { 
        output0 << "Account does not exist." << std::endl;
        return -1;
    }

    return -1;
}

// calculate the distance between two coordinates using Haversine formula
double calculateDistance(double lat1, double lon1, double lat2, double lon2) 
{
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}

//finds closest driver to specified rider
void findDriver(std::vector<Driver>& drivers, std::string const vehiclePref, std::vector<Rider>& riders, const int r_index, std::ofstream& output0)
{
    double min = 0.0;
    int d_index = 0;

    for (size_t i = 0; i < drivers.size(); ++i)
    {
        double distance = calculateDistance(riders[r_index].get_pickupLat(), riders[r_index].get_pickupLong(), drivers[i].get_currentLat(), drivers[i].get_currentLong());

        if(i == 0)
        {
            min = distance;
            d_index = i;
        }
        //matching conditions for driver status and rider vehicle type
        if(drivers[i].get_status() == "Available" && drivers[i].get_vType() == vehiclePref)
        {
            if(distance < min)
            {
                min = distance;
                d_index = i;
            }
        }
    }

    if(d_index != 0)
    {
        min = floor(min * 10) / 10.0;

        //update last three values for driver
        drivers[d_index].set_status("On_the_way_to_pickup");
        drivers[d_index].set_riderFirstName(riders[r_index].get_firstname());
        drivers[d_index].set_riderLastName(riders[r_index].get_lastname());
        drivers[d_index].set_riderNumber(riders[r_index].get_number());
        
        //update last three values for rider
        riders[r_index].set_status("Driver_on_the_way");
        riders[r_index].set_driverFirstName(drivers[d_index].get_firstname());
        riders[r_index].set_driverLastName(drivers[d_index].get_lastname());
        riders[r_index].set_driverNumber(drivers[d_index].get_number());

        std::string firstChar = (riders[r_index].get_vPref()).substr(0, 1);

        if(firstChar == "E")
        {
            output0 << "Ride requested for rider " << riders[r_index].get_firstname() << ", looking for an " << riders[r_index].get_vPref() << " vehicle." << std::endl;
        }
        else
        {
            output0 << "Ride requested for rider " << riders[r_index].get_firstname() << ", looking for a " << riders[r_index].get_vPref() << " vehicle." << std::endl;
        }
        output0 << "Pick Up Location: " << riders[r_index].get_pickLoc() << ", Drop Off Location: " << riders[r_index].get_dropLoc() << "." << std::endl;
        output0 << "We have found the closest driver " << riders[r_index].get_driverFirst() << "(" << drivers[d_index].get_rating() << ")" << " for you." << std::endl;
        output0 << riders[r_index].get_driverFirst() << " is now " << min << " miles away from you." << std::endl;
    }
    else
    {
        std::string firstChar = (riders[r_index].get_vPref()).substr(0, 1);

        if(firstChar == "E")
        {
            output0 << "Ride requested for rider " << riders[r_index].get_firstname() << ", looking for an " << riders[r_index].get_vPref() << " vehicle." << std::endl;
        }
        else
        {
            output0 << "Ride requested for rider " << riders[r_index].get_firstname() << ", looking for a " << riders[r_index].get_vPref() << " vehicle." << std::endl;
        }
        output0 << "Pick Up Location: " << riders[r_index].get_pickLoc() << ", Drop Off Location: " << riders[r_index].get_dropLoc() << "." << std::endl;
        output0 << "Sorry we can not find a driver for you at this moment." << std::endl;
    }
}

void ride_request(const std::string phoneNumber, std::vector<Rider>& riders, std::vector<Driver>& drivers, std::ofstream& output0)
{
    if(validPhoneNumber(phoneNumber, output0)) //checks if phone number format is correct
    {
        int r_index = validRider(phoneNumber, riders, output0); //checks if phone number belongs to a rider

        if(r_index != -1)
        {
            std::string v_pref = riders[r_index].get_vPref();
            findDriver(drivers, v_pref, riders, r_index, output0); //finds a driver for rider
        }
    }
}

//checks the status of drive ror rider trying to cancel and outputs accordingly
bool checkStatus(bool isRider, int index, std::vector<Rider>& riders, std::vector<Driver>& drivers, std::ofstream& output0)
{
    if(isRider)
    {
        if(riders[index].get_status() == "Driver_on_the_way")
        {
            output0 << "Ride request for rider " << riders[index].get_firstname() << " is now canceled by the rider." << std::endl;
            
            std::string d_number = riders[index].get_driverPhoneNumber();
            
            //update rider values
            riders[index].set_status("Ready_to_request");
            riders[index].set_driverFirstName("null");
            riders[index].set_driverLastName("null");
            riders[index].set_driverNumber("null");

            //update driver values
            for (size_t i = 0; i < drivers.size(); ++i)
            {
                if (drivers[i].get_number() == d_number)
                {
                    drivers[i].set_status("Available");
                    drivers[i].set_riderFirstName("null");
                    drivers[i].set_riderLastName("null");
                    drivers[i].set_riderNumber("null");
                }
            }

            return true;
        }
        else
        {
            output0 << "You can only cancel a ride request if your driver is currently on the way to the pickup location." << std::endl;
            return false;
        }
    }
    else
    {
        if(drivers[index].get_status() == "On_the_way_to_pickup")
        {
            output0 << "Your driver " << drivers[index].get_firstname() << " has canceled the ride request. We will now find a new driver for you." <<std::endl;
            
            std::string phoneNumber = drivers[index].get_riderPhoneNumber();
            for (size_t i = 0; i < riders.size(); ++i)
            {
                //updates rider attributes
                if (riders[i].get_number() == phoneNumber)
                {
                    riders[i].set_status("Ready_to_request");
                    riders[i].set_driverFirstName("null");
                    riders[i].set_driverLastName("null");
                    riders[i].set_driverNumber("null");
                }
            }

            ride_request(phoneNumber, riders, drivers, output0); //requests a ride for rider

            //updated driver attributes
            drivers[index].set_status("Available");
            drivers[index].set_riderFirstName("null");
            drivers[index].set_riderLastName("null");
            drivers[index].set_riderNumber("null");

            return true;
        }
        else
        {
            output0 << "You can only cancel a ride request if you are currently on the way to the pickup location." << std::endl;
            return false;
        }
    }
}

void ride_cancel(std::ofstream& output0, std::ofstream& output1, std::ofstream& output2, std::vector<Rider>& riders, std::vector<Driver>& drivers, const std::string phoneNumber)
{
    int index = -1;
    bool isRider = false;

    for (size_t i = 0; i < drivers.size(); ++i)
    {
        if(drivers[i].get_number() == phoneNumber)
        {
            index = i;
        }
    }
    for (size_t i = 0; i < riders.size(); ++i)
    {
        if(riders[i].get_number() == phoneNumber)
        {
            index = i;
            isRider = true;
        }
    }

    if(index == -1)
    {
        output0 << "Account does not exist." << std::endl;
    }
    else
    {
        if(checkStatus(isRider, index, riders, drivers, output0))
        {
            //print an updated version of drivers.txt into output1.txt:
            updateDrivers(output1, drivers);
            //print an updated version of riders.txt into output2.txt
            updateRiders(output2, riders);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        std::cerr << "Not enough arguments given" << std::endl;
        return 1;
    }

    // take first argument as driver file and open
    std::string d_filename = argv[1];
    std::fstream driver_file(d_filename);

    // take second argument as rider file and open
    std::string r_filename = argv[2];
    std::fstream rider_file(r_filename);

    std::string o0_filename = argv[3];
    std::ofstream output0(o0_filename);

    std::string o1_filename = argv[4];
    std::ofstream output1(o1_filename);

    std::string o2_filename = argv[5];
    std::ofstream output2(o2_filename);

    std::string phoneNumber = argv[6];

    std::string command = argv[7];

    if (!driver_file.is_open() || !rider_file.is_open() || !output0.is_open() || !output1.is_open() || !output2.is_open())
    {
        std::cerr << "Failed to open one or more files" << std::endl;
        return 1;
    }

    // vector for each object of drivers and riders
    std::vector<Driver> drivers;
    std::vector<Rider> riders;

    //call parse functions
    parseDrivers(drivers, driver_file);
    parseRiders(riders, rider_file);

    //call request function
    if (command == "request")
    {
        ride_request(phoneNumber, riders, drivers, output0);

        updateDrivers(output1, drivers);
        updateRiders(output2, riders);
    }
    //call cancel function
    if(command == "cancel")
    {
        ride_cancel(output0, output1, output2, riders, drivers, phoneNumber);
    }

    output0.close();
    output1.close();
    output2.close();

    return 0;
}