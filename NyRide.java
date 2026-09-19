
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

/**
 * Mock Uber-style ride matching.
 *
 * Usage:
 *   java nyride.NyRide drivers.txt riders.txt output0.txt output1.txt output2.txt PHONE (request|cancel)
 */
public class NyRide {

    // Placeholder used in the data files when a driver/rider has no counterpart
    static final String NONE = "null";

    // Driver statuses
    static final String DRIVER_AVAILABLE = "Available";
    static final String DRIVER_ON_THE_WAY = "On_the_way_to_pickup";

    // Rider statuses
    static final String RIDER_READY = "Ready_to_request";
    static final String RIDER_DRIVER_ON_THE_WAY = "Driver_on_the_way";
    static final String RIDER_ON_TRIP = "During_the_trip";

    private static final int DRIVER_FIELDS = 13;
    private static final int RIDER_FIELDS = 17;
    private static final int PHONE_LENGTH = 12; // xxx-xxx-xxxx

    // ---------------------------------------------------------------- parsing

    static List<Driver> parseDrivers(Path file) throws IOException {
        List<Driver> drivers = new ArrayList<>();
        for (String line : Files.readAllLines(file, StandardCharsets.UTF_8)) {
            if (line.isBlank()) {
                continue;
            }
            String[] f = line.trim().split("\\s+");
            if (f.length < DRIVER_FIELDS) {
                System.err.println("Invalid driver entry: " + line);
                continue;
            }
            try {
                drivers.add(new Driver(f[0], f[1], f[2], Integer.parseInt(f[3]), f[4], f[5],
                        Double.parseDouble(f[6]), Double.parseDouble(f[7]), f[8],
                        f[9], f[10], f[11], f[12]));
            } catch (NumberFormatException e) {
                System.err.println("Invalid driver entry: " + line);
            }
        }
        return drivers;
    }

    static List<Rider> parseRiders(Path file) throws IOException {
        List<Rider> riders = new ArrayList<>();
        for (String line : Files.readAllLines(file, StandardCharsets.UTF_8)) {
            if (line.isBlank()) {
                continue;
            }
            String[] f = line.trim().split("\\s+");
            if (f.length < RIDER_FIELDS) {
                System.err.println("Invalid rider entry: " + line);
                continue;
            }
            try {
                riders.add(new Rider(f[0], f[1], f[2], Integer.parseInt(f[3]), f[4], f[5],
                        f[6], Double.parseDouble(f[7]), Double.parseDouble(f[8]),
                        f[9], Double.parseDouble(f[10]), Double.parseDouble(f[11]),
                        f[12], f[13], f[14], f[15], f[16]));
            } catch (NumberFormatException e) {
                System.err.println("Invalid rider entry: " + line);
            }
        }
        return riders;
    }

    // ----------------------------------------------------------------- output

    private static void println(PrintWriter out, String text) {
        out.print(text + "\n"); // always '\n', regardless of platform
    }

    /** Writes the updated drivers, in the same format as drivers.txt. */
    static void updateDrivers(PrintWriter out, List<Driver> drivers) {
        for (Driver d : drivers) {
            println(out, d.toFileLine());
        }
    }

    /** Writes the updated riders, in the same format as riders.txt. */
    static void updateRiders(PrintWriter out, List<Rider> riders) {
        for (Rider r : riders) {
            println(out, r.toFileLine());
        }
    }

    // ------------------------------------------------------------- validation

    /** Phone numbers must look like xxx-xxx-xxxx. */
    static boolean validPhoneNumber(String phone, PrintWriter out) {
        boolean ok = phone.length() == PHONE_LENGTH;
        for (int i = 0; ok && i < phone.length(); i++) {
            char c = phone.charAt(i);
            ok = (i == 3 || i == 7) ? c == '-' : (c >= '0' && c <= '9');
        }
        if (!ok) {
            println(out, "Phone number is invalid.");
        }
        return ok;
    }

    /** Returns the index of the rider who may request a ride, or -1 (after explaining why). */
    static int validRider(String phone, List<Rider> riders, PrintWriter out) {
        for (int i = 0; i < riders.size(); i++) {
            Rider r = riders.get(i);
            if (!r.getPhoneNumber().equals(phone)) {
                continue;
            }
            switch (r.getStatus()) {
                case RIDER_DRIVER_ON_THE_WAY:
                    println(out, "You have already requested a ride and your driver is on the way to the pickup location.");
                    return -1;
                case RIDER_ON_TRIP:
                    println(out, "You can not request a ride at this moment as you are already on a trip.");
                    return -1;
                case RIDER_READY:
                    return i;
                default:
                    System.err.println("something went wrong with rider status " + i + " " + r.getFirstName());
            }
        }
        println(out, "Account does not exist.");
        return -1;
    }

    // --------------------------------------------------------------- distance

    /** Haversine distance between two coordinates, in miles. */
    static double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
        final double radiusOfEarthKm = 6371.0;
        final double degToRad = Math.PI / 180.0;

        lat1 *= degToRad;
        lon1 *= degToRad;
        lat2 *= degToRad;
        lon2 *= degToRad;

        double dLat = lat2 - lat1;
        double dLon = lon2 - lon1;
        double a = Math.sin(dLat / 2.0) * Math.sin(dLat / 2.0)
                + Math.cos(lat1) * Math.cos(lat2) * Math.sin(dLon / 2.0) * Math.sin(dLon / 2.0);
        double c = 2.0 * Math.atan2(Math.sqrt(a), Math.sqrt(1.0 - a));
        double distanceKm = radiusOfEarthKm * c;
        return distanceKm * 0.621371;
    }

    // --------------------------------------------------------------- requests

    /** Matches the rider at riderIndex with the closest available driver of the preferred vehicle type. */
    static void findDriver(List<Driver> drivers, List<Rider> riders, int riderIndex, PrintWriter out) {
        Rider rider = riders.get(riderIndex);
        String pref = rider.getVehiclePreference();

        int best = -1;
        double min = Double.MAX_VALUE;
        for (int i = 0; i < drivers.size(); i++) {
            Driver d = drivers.get(i);
            if (!DRIVER_AVAILABLE.equals(d.getStatus()) || !pref.equals(d.getVehicleType())) {
                continue;
            }
            double distance = calculateDistance(rider.getPickupLatitude(), rider.getPickupLongitude(),
                    d.getCurrentLatitude(), d.getCurrentLongitude());
            if (distance < min) {
                min = distance;
                best = i;
            }
        }

        String article = pref.startsWith("E") ? "an" : "a";
        println(out, "Ride requested for rider " + rider.getFirstName() + ", looking for " + article + " " + pref + " vehicle.");
        println(out, "Pick Up Location: " + rider.getPickupLocation() + ", Drop Off Location: " + rider.getDropoffLocation() + ".");

        if (best == -1) {
            println(out, "Sorry we can not find a driver for you at this moment.");
            return;
        }

        Driver driver = drivers.get(best);
        double roundedDown = Math.floor(min * 10) / 10.0;

        driver.setStatus(DRIVER_ON_THE_WAY);
        driver.setRiderFirstName(rider.getFirstName());
        driver.setRiderLastName(rider.getLastName());
        driver.setRiderPhoneNumber(rider.getPhoneNumber());

        rider.setStatus(RIDER_DRIVER_ON_THE_WAY);
        rider.setDriverFirstName(driver.getFirstName());
        rider.setDriverLastName(driver.getLastName());
        rider.setDriverPhoneNumber(driver.getPhoneNumber());

        println(out, "We have found the closest driver " + rider.getDriverFirstName() + "(" + driver.getRating() + ") for you.");
        println(out, rider.getDriverFirstName() + " is now " + Formats.miles(roundedDown) + " miles away from you.");
    }

    static void rideRequest(String phone, List<Rider> riders, List<Driver> drivers, PrintWriter out) {
        if (!validPhoneNumber(phone, out)) {
            return;
        }
        int riderIndex = validRider(phone, riders, out);
        if (riderIndex != -1) {
            findDriver(drivers, riders, riderIndex, out);
        }
    }

    // ---------------------------------------------------------------- cancels

    /** Cancels on behalf of a rider whose driver is on the way. Returns true if something was canceled. */
    static boolean cancelAsRider(Rider rider, List<Driver> drivers, PrintWriter out) {
        if (!RIDER_DRIVER_ON_THE_WAY.equals(rider.getStatus())) {
            println(out, "You can only cancel a ride request if your driver is currently on the way to the pickup location.");
            return false;
        }
        println(out, "Ride request for rider " + rider.getFirstName() + " is now canceled by the rider.");

        String driverPhone = rider.getDriverPhoneNumber();
        rider.release();
        for (Driver d : drivers) {
            if (d.getPhoneNumber().equals(driverPhone)) {
                d.release();
            }
        }
        return true;
    }

    /** Cancels on behalf of a driver heading to a pickup, then looks for a new driver for that rider. */
    static boolean cancelAsDriver(Driver driver, List<Rider> riders, List<Driver> drivers, PrintWriter out) {
        if (!DRIVER_ON_THE_WAY.equals(driver.getStatus())) {
            println(out, "You can only cancel a ride request if you are currently on the way to the pickup location.");
            return false;
        }
        println(out, "Your driver " + driver.getFirstName() + " has canceled the ride request. We will now find a new driver for you.");

        String riderPhone = driver.getRiderPhoneNumber();
        for (Rider r : riders) {
            if (r.getPhoneNumber().equals(riderPhone)) {
                r.release();
            }
        }

        // The canceling driver is still "on the way" here, so they cannot be matched again.
        rideRequest(riderPhone, riders, drivers, out);

        driver.release();
        return true;
    }

    static void rideCancel(PrintWriter out0, PrintWriter out1, PrintWriter out2,
                           List<Rider> riders, List<Driver> drivers, String phone) {
        Rider rider = null;
        for (Rider r : riders) {
            if (r.getPhoneNumber().equals(phone)) {
                rider = r; // last match wins, as in the C++ version
            }
        }
        Driver driver = null;
        for (Driver d : drivers) {
            if (d.getPhoneNumber().equals(phone)) {
                driver = d;
            }
        }

        boolean canceled;
        if (rider != null) {
            canceled = cancelAsRider(rider, drivers, out0);
        } else if (driver != null) {
            canceled = cancelAsDriver(driver, riders, drivers, out0);
        } else {
            println(out0, "Account does not exist.");
            return;
        }

        if (canceled) {
            updateDrivers(out1, drivers);
            updateRiders(out2, riders);
        }
    }

    // ------------------------------------------------------------------- main

    public static void main(String[] args) {
        if (args.length < 7) {
            System.err.println("Not enough arguments given");
            System.err.println("Usage: java nyride.NyRide <drivers> <riders> <output0> <output1> <output2> <phone> <request|cancel>");
            System.exit(1);
        }

        Path driverFile = Paths.get(args[0]);
        Path riderFile = Paths.get(args[1]);
        String phone = args[5];
        String command = args[6];

        if (!command.equals("request") && !command.equals("cancel")) {
            System.err.println("Unknown command: " + command + " (expected 'request' or 'cancel')");
            System.exit(1);
        }

        try (PrintWriter out0 = openWriter(args[2]);
             PrintWriter out1 = openWriter(args[3]);
             PrintWriter out2 = openWriter(args[4])) {

            List<Driver> drivers = parseDrivers(driverFile);
            List<Rider> riders = parseRiders(riderFile);

            if (command.equals("request")) {
                rideRequest(phone, riders, drivers, out0);
                updateDrivers(out1, drivers);
                updateRiders(out2, riders);
            } else {
                rideCancel(out0, out1, out2, riders, drivers, phone);
            }
        } catch (IOException e) {
            System.err.println("Failed to open one or more files: " + e.getMessage());
            System.exit(1);
        }
    }

    private static PrintWriter openWriter(String filename) throws IOException {
        return new PrintWriter(Files.newBufferedWriter(Paths.get(filename), StandardCharsets.UTF_8));
    }
}
