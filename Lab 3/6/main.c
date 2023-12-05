#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Макрос для разбора строки времени
#define PARSE_TIME(str, time) do { \
    struct tm tm = {0}; \
    sscanf(str, "%d.%d.%d %d:%d:%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year, &tm.tm_hour, &tm.tm_min, &tm.tm_sec); \
    tm.tm_year -= 1900; \
    tm.tm_mon -= 1; \
    time = mktime(&tm); \
} while (0)

struct Stop {
    char transportNumber[50];
    time_t arrivalTime;
    time_t departureTime;
    char marker[20];
    double latitude;
    double longitude;
    struct Stop* next;
};


struct Route {
    char location[100];
    struct Stop* stops;
    struct Route* nextRoute;
};

struct TransportStats {
    char transportNumber[50];
    int numOfRoutes;
    double totalDistance;
    double maxDistance;
    double minDistance;
    time_t maxDuration;
    time_t minDuration;
};

void insertStop(struct Route* route, char transportNumber[], char arrivalTimeStr[], char departureTimeStr[], char marker[], double latitude, double longitude) {
    // ... То, что было ранее ...
    struct Stop* newStop = (struct Stop*)malloc(sizeof(struct Stop));

    time_t arrivalTime, departureTime;

    strcpy(newStop->transportNumber, transportNumber);
    PARSE_TIME(arrivalTimeStr, arrivalTime);
    PARSE_TIME(departureTimeStr, departureTime);
    newStop->arrivalTime = arrivalTime;
    newStop->departureTime = departureTime;
    strcpy(newStop->marker, marker);

    newStop->next = NULL;



    if (route->stops == NULL) {
        route->stops = newStop;
    } else {
        struct Stop* temp = route->stops;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStop;
    }
}

// Function to calculate time difference in seconds
time_t timeDifference(struct tm start, struct tm end) {
    time_t startTime = mktime(&start);
    time_t endTime = mktime(&end);
    time_t difference = difftime(endTime, startTime);
    return difference;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s file1 file2 ... fileN\n", argv[0]);
        return 1;
    }

    // Initialize transport statistics
    struct TransportStats transportStatistics[100];
    int numOfTransport = 0;

    struct Route* routes = NULL;

    for (int i = 1; i < argc; ++i) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("Error opening file: %s\n", argv[i]);
            continue;
        }

        char location[100];
        fscanf(file, "%s", location);

        struct Route* newRoute = (struct Route*)malloc(sizeof(struct Route));
        strcpy(newRoute->location, location);
        newRoute->stops = NULL;
        newRoute->nextRoute = NULL;

        char transportNumber[50];
        char arrivalTime[20];
        char departureTime[20];
        char marker[20];
        double latitude, longitude;

        while (fscanf(file, "%s %s %s %s %lf %lf", transportNumber, arrivalTime, departureTime, marker, &latitude, &longitude) == 6) {
            insertStop(newRoute, transportNumber, arrivalTime, departureTime, marker, latitude, longitude);

            // Update transport statistics
            int foundTransport = 0;
            for (int j = 0; j < numOfTransport; ++j) {
                if (strcmp(transportStatistics[j].transportNumber, transportNumber) == 0) {
                    foundTransport = 1;
                    transportStatistics[j].numOfRoutes++;
                    // Update total distance, max distance, min distance, max and min duration (if applicable)
                    // ...
                    break;
                }
            }
            if (!foundTransport) {
                strcpy(transportStatistics[numOfTransport].transportNumber, transportNumber);
                transportStatistics[numOfTransport].numOfRoutes = 1;
                // Calculate distance and duration for this route
                // ...
                numOfTransport++;
            }
        }
        fclose(file);

        if (routes == NULL) {
            routes = newRoute;
        } else {
            struct Route* temp = routes;
            while (temp->nextRoute != NULL) {
                temp = temp->nextRoute;
            }
            temp->nextRoute = newRoute;
        }
    }

    // Perform interactive dialog for searching transport statistics
    // ...

    // Free allocated memory
    // ...

    return 0;
}