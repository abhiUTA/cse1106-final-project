#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pigpio.h>

#define PIN 17 

// Function to calculate avg
double calculateAverage(double readings[], int count) {
    if (count == 0) return 0.0;
    double total = 0;
    for (int i = 0; i < count; i++) total += readings[i];
    return total / count;
}

//check the accpetable range
int isOutOfRange(double temperature, double upper, double lower) {
    return (temperature < lower || temperature > upper) ? 1 : 0;
}

// Function to display readings and status
void displayReadings(double readings[], int count, double upper, double lower) {
    printf("\n--- Temperature Readings ---\n");
    for (int i = 0; i < count; i++) {
        printf("%.1f F - %s\n", readings[i], isOutOfRange(readings[i], upper, lower) ? "WARNING" : "NORMAL");
    }
}

int main(void) {
    int count = 0;
    double readings[10000]; 
    
    double lower = 68.0;
    double upper = 76.0;
    int choice = 0;

    if (gpioInitialise() < 0) {
        printf("pigpio initialization failed. Did you run with sudo?\n");
        return 1;
    }
    gpioSetMode(PIN, PI_OUTPUT);
    gpioWrite(PIN, 0); // Start with LED OFF

    while (1) {
        printf("\n--- Smart Classroom Comfort Monitor ---\n");
        printf("1. Enter a temperature\n");
        printf("2. Display status of readings & toggle LED\n");
        printf("3. Calculate and display average\n");
        printf("4. Save readings and statuses to file\n");
        printf("5. Change acceptable temperature range\n");
        printf("6. Exit program\n");
        printf("Please enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear buffer
            continue;
        } 

        if (choice == 1) {
            printf("Please enter a temperature (F): ");
            double temperature = 0;
            scanf("%lf", &temperature);
            readings[count] = temperature;
            count++;
            printf("Temperature recorded!\n");
        }
        else if (choice == 2) {
            displayReadings(readings, count, upper, lower);
            
            // Check the most recent reading to trigger the physical LED
            if (count > 0) {
                FILE *status_file = fopen("../status.txt", "w");
                
                if (isOutOfRange(readings[count - 1], upper, lower)) {
                    gpioWrite(PIN, 1); // Turn ON LED for Warning
                    printf(">> Current LED Status: ON (WARNING)\n");
                    if (status_file != NULL) fprintf(status_file, "# WARNING\n");
                } else {
                    gpioWrite(PIN, 0); // Turn OFF LED for Normal
                    printf(">> Current LED Status: OFF (NORMAL)\n");
                    if (status_file != NULL) fprintf(status_file, "# NORMAL\n");
                }
                
                if (status_file != NULL) fclose(status_file);
            } else {
                printf("No readings to check yet.\n");
            }
        }
        else if (choice == 3) {
            double average = calculateAverage(readings, count);
            printf("The average temperature is: %.2lf F\n", average);
        }
        else if (choice == 4) {
            // Save temperatures AND statuses to CSV
            FILE *file = fopen("../data/temperature_log.csv", "a");
            if (file != NULL) {
                fprintf(file, "Temperature(F),Status\n"); // CSV Header
                for (int i = 0; i < count; i++) {
                    fprintf(file, "%.1f,%s\n", readings[i], isOutOfRange(readings[i], upper, lower) ? "WARNING" : "NORMAL");
                }
                fclose(file);
                printf("Successfully saved to data/temperature_log.csv\n");
            } else {
                printf("Error opening file. Ensure the 'data' directory exists.\n");
            }
        }
        else if (choice == 5) {
            // Change acceptable temperature range
            printf("Current acceptable range is %.1f F to %.1f F.\n", lower, upper);
            printf("Enter new lower bound (F): ");
            scanf("%lf", &lower);
            printf("Enter new upper bound (F): ");
            scanf("%lf", &upper);
            printf("Range updated! New acceptable range is %.1f F to %.1f F.\n", lower, upper);
        }
        else if (choice == 6) {
            printf("Exiting program...\n");
            break;
        }
        else {
            printf("Please enter a valid choice between 1 and 6\n");
        }
    }

    // Safely turn off LED and terminate library
    gpioWrite(PIN, 0);
    gpioTerminate();
    
    return 0;
}
