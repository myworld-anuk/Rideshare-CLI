# Uber_App (Java)

Mock Uber App with basic capabilities: request a ride (matches the closest available driver with the
rider's preferred vehicle type) or cancel one (as either the rider or the driver).

## Layout

```
src/nyride/Driver.java    driver data + status changes
src/nyride/Rider.java     rider data + status changes
src/nyride/Formats.java   number formatting that matches the original C++ output
src/nyride/NyRide.java    parsing, request/cancel logic, main()
data/drivers.txt          sample input
data/riders.txt           sample input
```

## Build

```
mkdir -p out
javac -d out src/nyride/*.java
```

## Run

Same arguments as the C++ program:

```
java -cp out nyride.NyRide data/drivers.txt data/riders.txt output0.txt output1.txt output2.txt <phone> <request|cancel>
```

- `output0.txt` - messages for the rider/driver
- `output1.txt` - updated drivers (same format as `drivers.txt`)
- `output2.txt` - updated riders (same format as `riders.txt`)

Example:

```
java -cp out nyride.NyRide data/drivers.txt data/riders.txt output0.txt output1.txt output2.txt 301-144-6533 request
```

## Differences from the C++ version

These are bug fixes; output on the sample data is identical to the C++ program.

- Parsers require 13 (driver) / 17 (rider) fields; C++ checked for 12 / 16 but read one field further.
- Argument check requires all 7 arguments; C++ only checked for 6 and then read `argv[6]` and `argv[7]`.
- Driver matching only considers drivers who are `Available` and have the requested vehicle type. C++ seeded
  the "closest" distance from driver #0 regardless of status, and treated "driver #0 was chosen" as
  "no driver found".
- Unknown commands and unreadable input files print an error and exit with status 1.
