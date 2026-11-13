# Test Plan: Smart Classroom Comfort Monitor

**Test Case 1: Normal Temperature (Inside Range)**
* Action: Select Choice 1 and enter 72. Select Choice 2.
* Expected Result:** Status displays as "NORMAL". The physical LED remains OFF.
* Pass/Fail: Passed

**Test Case 2: Warning Temperature (Above Range)**
* Action: Select Choice 1 and enter 80 Select Choice 2.
* Expected Result: Status displays as "WARNING". The physical LED turns ON.
* Pass/Fail: Pass

**Test Case 3: Warning Temperature (Below Range)**
* Action: Select Choice 1 and enter 65. Select Choice 2.
* Expected Result: Status displays as "WARNING". The physical LED turns ON.
* Pass/Fail: Pass

**Test Case 4: Changing Acceptable Range**
* Action: Select Choice 5. Change the range to 70 (lower) and 75 (upper). Select Choice 1 and enter 69. Select Choice 2.
* Expected Result: Status displays as "WARNING" and LED turns ON (since 69 is now outside the new 70-75 range).
* Pass/Fail: Pass

**Test Case 5: Save Data to File**
* Action: Select Choice 4. Open data/temperature_log.csv.
* Expected Result: The CSV file contains the header "Temperature(F),Status" followed by the temperatures entered in the previous tests and their corresponding statuses.
* Pass/Fail: Pass
