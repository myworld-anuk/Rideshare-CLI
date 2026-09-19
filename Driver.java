
public class Driver {
    private final String firstName;
    private final String lastName;
    private final String gender;
    private final int age;
    private final String phoneNumber;
    private final String rating;
    private final double currentLatitude;
    private final double currentLongitude;
    private final String vehicleType;

    private String status;
    private String riderFirstName;
    private String riderLastName;
    private String riderPhoneNumber;

    public Driver(String firstName, String lastName, String gender, int age, String phoneNumber,
                  String rating, double currentLatitude, double currentLongitude, String vehicleType,
                  String status, String riderFirstName, String riderLastName, String riderPhoneNumber) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.gender = gender;
        this.age = age;
        this.phoneNumber = phoneNumber;
        this.rating = rating;
        this.currentLatitude = currentLatitude;
        this.currentLongitude = currentLongitude;
        this.vehicleType = vehicleType;
        this.status = status;
        this.riderFirstName = riderFirstName;
        this.riderLastName = riderLastName;
        this.riderPhoneNumber = riderPhoneNumber;
    }

    // getters
    public String getFirstName() { return firstName; }
    public String getLastName() { return lastName; }
    public String getGender() { return gender; }
    public int getAge() { return age; }
    public String getPhoneNumber() { return phoneNumber; }
    public String getRating() { return rating; }
    public double getCurrentLatitude() { return currentLatitude; }
    public double getCurrentLongitude() { return currentLongitude; }
    public String getVehicleType() { return vehicleType; }
    public String getStatus() { return status; }
    public String getRiderFirstName() { return riderFirstName; }
    public String getRiderLastName() { return riderLastName; }
    public String getRiderPhoneNumber() { return riderPhoneNumber; }

    // setters
    public void setStatus(String status) { this.status = status; }
    public void setRiderFirstName(String riderFirstName) { this.riderFirstName = riderFirstName; }
    public void setRiderLastName(String riderLastName) { this.riderLastName = riderLastName; }
    public void setRiderPhoneNumber(String riderPhoneNumber) { this.riderPhoneNumber = riderPhoneNumber; }

    /** Clears the assigned rider and marks this driver available again. */
    public void release() {
        status = NyRide.DRIVER_AVAILABLE;
        riderFirstName = NyRide.NONE;
        riderLastName = NyRide.NONE;
        riderPhoneNumber = NyRide.NONE;
    }

    /** One line in the same space-separated format as drivers.txt. */
    public String toFileLine() {
        return String.join(" ",
                firstName,
                lastName,
                gender,
                Integer.toString(age),
                phoneNumber,
                rating,
                Formats.coordinate(currentLatitude),
                Formats.coordinate(currentLongitude),
                vehicleType,
                status,
                riderFirstName,
                riderLastName,
                riderPhoneNumber);
    }
}
