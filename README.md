# Uber_App

Project Capabilities:
The program acted as the backend for a ride-sharing app, managing a database of drivers and riders from text files. It could process two primary commands initiated via the command line:

1) Request a Ride:
   - A rider, identified by their phone number, could request a trip.
   - The program would search through all available drivers to find the one who was closest and had a vehicle type that matched the rider's preference.
   - Distance was calculated using the mathematical Haversine formula based on latitude and longitude.
   - Upon finding a match, the program updated the status of both the rider and driver, linking them together for the trip. It then generated new output files reflecting these changes and printed a confirmation message.
   - Upon finding a match, the program updated the status of both the rider and driver, linking them together for the trip. It then generated new output files reflecting these changes and printed a confirmation message.

2) Cancel a Ride:

    - This command could be issued by either a driver or a rider.
    - If a rider canceled, the trip was terminated. The driver became "Available" again, and the rider's status returned to "Ready to request."
    - If a driver canceled, the program not only made that driver available again but also immediately searched for a new closest driver to re-assign to the rider, ensuring the rider's trip could continue.

The program's entire state was managed by reading from input files (drivers.txt, riders.txt) at the start and writing the completely updated information to a new set of output files after every command.

Skills Gained:
This project was a practical exercise in object-oriented programming and data management in C++. The key skills you would have honed are:

1) Object-Oriented Programming (OOP): This was a core objective. You were required to design and implement at least two C++ classes (e.g., Driver and Rider). This involved:
    - Defining member variables to store data for each object (name, rating, location, current state, etc.).
    - Writing member functions to represent their behaviors (e.g., updating status, getting location).
    - Organizing the code by splitting class definitions into .h files and implementations into .cpp files.

2) STL std::vector and std::string:
    - Used std::vector as the primary container to store all of your Driver and Rider objects.
    - Used std::string extensively to handle textual data like names, phone numbers, and location details parsed from the input files.

3) File Parsing and I/O: Practiced reading and parsing structured text files line-by-line to construct your objects. I also learned to write the complete, updated state of your data back out to new files, effectively saving the program's state after each operation.
   
4) Algorithm Design: Implemented a crucial search algorithm to find the "closest available driver." This required iterating through the data, applying multiple conditions (Is the driver available? Does the car type match?), performing calculations (distance), and tracking the best match found.
   
5) Command-Line Argument Handling: The program was controlled from the command line, so I learned how to process arguments passed to main (argc, argv) to determine which files to use and which action to perform.
