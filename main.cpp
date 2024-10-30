#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "coordinate.h"

int currentCoordID = 1; // Global Variable for tracking coordinate IDs

// Add new coordinate at the end of the list
void addCoordinate(Coordinate **listEnd, float x, float y) {
    Coordinate *newCoord = new Coordinate(); // Create a new coordinate
    newCoord->x = x;
    newCoord->y = y;
    newCoord->coord_id = currentCoordID++;
    newCoord->next = nullptr;
    newCoord->previous = *listEnd;

    if (*listEnd != nullptr) { // Link the new coordinate to the end of the list
        (*listEnd)->next = newCoord;
    }
    *listEnd = newCoord; // Update the end of the list
}

// Show list from beginning -> end
void forwardDisplay(Coordinate *listBeginning) {
    Coordinate *temp = listBeginning;
    while (temp != nullptr) {
        std::cout << "ID: " << temp->coord_id << " (x: " << temp->x << ", y: " << temp->y << ")\n";
        temp = temp->next;
    }
}

// Show the list from end -> beginning
void backwardDisplay(Coordinate *listEnd) {
    Coordinate *temp = listEnd;
    while (temp != nullptr) {
        std::cout << "ID: " << temp->coord_id << " (x: " << temp->x << ", y: " << temp->y << ")\n";
        temp = temp->previous;
    }
}

// Delete a coordinate by the ID
void deleteCoordinate(Coordinate **listBeginning, int coordIDToDelete) {
    Coordinate *temp = *listBeginning;

    // Find coordinate to delete
    while (temp != nullptr && temp->coord_id != coordIDToDelete) {
        temp = temp->next;
    }

    if (temp != nullptr) { // If found, delete it
        if (temp->previous != nullptr) {
            temp->previous->next = temp->next;
        } else {
            *listBeginning = temp->next; // Update list beginning if first node
        }

        if (temp->next != nullptr) {
            temp->next->previous = temp->previous;
        }

        delete temp;
        std::cout << "Deleted coordinate with ID: " << coordIDToDelete << "\n";
    } else {
        std::cout << "Coordinate with ID " << coordIDToDelete << " not found.\n";
    }
}

// Find the closest coordinate to a given x-y point
void closestTo(Coordinate *listBeginning, float x, float y) {
    Coordinate *temp = listBeginning;
    Coordinate *closest = nullptr;
    float minDistance = 9999.0f; // Set a large initial value

    // Loop through list to find the closest coordinate
    while (temp != nullptr) {
        float distance = std::sqrt((temp->x - x) * (temp->x - x) + (temp->y - y) * (temp->y - y));

        if (distance < minDistance) {
            minDistance = distance;
            closest = temp;
        }

        temp = temp->next;
    }

    // Display the closest coordinate and its distance
    if (closest != nullptr) {
        std::cout << "Closest coordinate: (" << x << ", " << y << ") is ID: " << closest->coord_id
                  << " (x: " << closest->x << ", y: " << closest->y << ") Distance: " << minDistance << "\n";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <number_of_coordinates>\n";
        return 1;
    }

    int numCoordinates = std::atoi(argv[1]);
    if (numCoordinates <= 0) {
        std::cout << "Please enter a positive number of coordinates.\n";
        return 1;
    }

    std::srand(static_cast<unsigned int>(std::time(0))); // Initialize random number generator

    Coordinate *listBeginning = nullptr; // Pointers (beginning/end of the list)
    Coordinate *listEnd = nullptr;

    // Add random coordinates to the list
    for (int i = 0; i < numCoordinates; i++) {
        float x = static_cast<float>(std::rand() % 100); // https://stackoverflow.com/questions/686353/random-float-number-generation
        float y = static_cast<float>(std::rand() % 100);
        addCoordinate(&listEnd, x, y);
        if (listBeginning == nullptr) {
            listBeginning = listEnd;
        }
    }

    std::cout << "\nCoordinates, beginning to end:\n"; // Display coordinates forward
    forwardDisplay(listBeginning);

    std::cout << "\nCoordinates, end to beginning:\n"; // Display coordinates backward
    backwardDisplay(listEnd);

    deleteCoordinate(&listBeginning, 2); // Delete a coordinate by ID

    closestTo(listBeginning, 50.0f, 50.0f); // Find closest coordinate to (50, 50)

    return 0;
}
