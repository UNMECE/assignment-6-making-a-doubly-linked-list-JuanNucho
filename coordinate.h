#ifndef COORDINATE_H
#define COORDINATE_H

// Struct for x,y coordinates
struct Coordinate {
    float x;
    float y;
    int coord_id;
    Coordinate *next;
    Coordinate *previous;
};

// Function prototypes
void addCoordinate(Coordinate **listEnd, float x, float y);
void forwardDisplay(Coordinate *listBeginning);
void backwardDisplay(Coordinate *listEnd);
void deleteCoordinate(Coordinate **listBeginning, int coordIDToDelete);
int listLength(Coordinate *listBeginning);
void closestTo(Coordinate *listBeginning, float x, float y);

#endif // COORDINATE_H