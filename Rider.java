
public class Rider {
    private final String firstName;
    private final String lastName;
    private final String gender;
    private final int age;
    private final String phoneNumber;
    private final String rating;
    private final String pickupLocation;
    private final double pickupLatitude;
    private final double pickupLongitude;
    private final String dropoffLocation;
    private final double dropoffLatitude;
    private final double dropoffLongitude;
    private final String vehiclePreference;

    private String currentState;
    private String driverFirstName;
    private String driverLastName;
    private String driverPhoneNumber;

    public Rider(String firstName, String lastName, String gender, int age, String phoneNumber,
                 String rating, String pickupLocation, double pickupLatitude, double pickupLongitude,
                 String dropoffLocation, double dropoffLatitude, double dropoffLongitude,
                 String vehiclePreference, String currentState, String driverFirstName,
                 String driverLastName, String driverPhoneNumber) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.gender = gender;
        this.age = age;
        this.phoneNumber = phoneNumber;
        this.rating = rating;
        this.pickupLocation = pickupLocation;
        this.pickupLatitude = pickupLatitude;
        this.pickupLongitude = pickupLongitude;
        this.dropoffLocation = dropoffLocation;
        this.dropoffLatitude = dropoffLatitude;
        this.dropoffLongitude = dropoffLongitude;
        this.vehiclePreference = vehiclePreference;
        this.currentState = currentState;
        this.driverFirstName = driverFirstName;
        this.driverLastName = driverLastName;
        this.driverPhoneNumber = driverPhoneNumber;
    }

    // getters
    public String getFirstName() { return firstName; }
    public String getLastName() { return lastName; }
    public String getGender() { return gender; }
    public int getAge() { return age; }
    public String getPhoneNumber() { return phoneNumber; }
    public String getRating() { return rating; }
    public String getPickupLocation() { return pickupLocation; }
    public double getPickupLatitude() { return pickupLatitude; }
    public double getPickupLongitude() { return pickupLongitude; }
    public String getDropoffLocation() { return dropoffLocation; }
    public double getDropoffLatitude() { return dropoffLatitude; }
    public double getDropoffLongitude() { return dropoffLongitude; }
    public String getVehiclePreference() { return vehiclePreference; }
    public String getStatus() { return currentState; }
    public String getDriverFirstName() { return driverFirstName; }
    public String getDriverLastName() { return driverLastName; }
    public String getDriverPhoneNumber() { return driverPhoneNumber; }

    // setters
    public void setStatus(String status) { this.currentState = status; }
    public void setDriverFirstName(String driverFirstName) { this.driverFirstName = driverFirstName; }
    public void setDriverLastName(String driverLastName) { this.driverLastName = driverLastName; }
    public void setDriverPhoneNumber(String driverPhoneNumber) { this.driverPhoneNumber = driverPhoneNumber; }

    /** Clears the assigned driver and lets this rider request a ride again. */
    public void release() {
        currentState = NyRide.RIDER_READY;
        driverFirstName = NyRide.NONE;
        driverLastName = NyRide.NONE;
        driverPhoneNumber = NyRide.NONE;
    }

    /** One line in the same space-separated format as riders.txt. */
    public String toFileLine() {
        return String.join(" ",
                firstName,
                lastName,
                gender,
                Integer.toString(age),
                phoneNumber,
                rating,
                pickupLocation,
                Formats.coordinate(pickupLatitude),
                Formats.coordinate(pickupLongitude),
                dropoffLocation,
                Formats.coordinate(dropoffLatitude),
                Formats.coordinate(dropoffLongitude),
                vehiclePreference,
                currentState,
                driverFirstName,
                driverLastName,
                driverPhoneNumber);
    }
}
