#include "graphics.h"
#include <stdlib.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

void forward(int xyCoords[], int gridXYCoords[], int facing)
{
    switch(facing)
    {
        case NORTH:
            xyCoords[1] -= 40;
            gridXYCoords[1] -= 1;
            break;
        case EAST:
            xyCoords[0] += 40;
            gridXYCoords[0] += 1;
            break;
        case SOUTH:
            xyCoords[1] += 40;
            gridXYCoords[1] += 1;
            break;
        case WEST:
            xyCoords[0] -= 40;
            gridXYCoords[0] -= 1;
    }
}

int left(int facing)
{
    facing = (facing + (4 - 1)) % 4;
    return facing;
}

int right(int facing)
{
    facing = (facing + 1) % 4;
    return facing;
}

int atMarker(int mazeWidth, int gridXYCoords[], int mazeGrid[][mazeWidth + 2])
{
    if (mazeGrid[gridXYCoords[1]][gridXYCoords[0]] == 2)
        return 1;
    return 0;
}

int canMoveLeft(int mazeWidth, int gridXYCoords[], int facing, int mazeGrid[][mazeWidth + 2])
{
    if (facing == NORTH && (mazeGrid[gridXYCoords[1]][gridXYCoords[0] - 1] == 1 || mazeGrid[gridXYCoords[1]][gridXYCoords[0] - 1] == 2))
    {
        return 1;
    }  else if (facing == EAST && (mazeGrid[gridXYCoords[1] - 1][gridXYCoords[0]] == 1 || mazeGrid[gridXYCoords[1] - 1][gridXYCoords[0]] == 2)) 
    {
        return 1;
    } else if (facing == SOUTH && (mazeGrid[gridXYCoords[1]][gridXYCoords[0] + 1] == 1 || mazeGrid[gridXYCoords[1]][gridXYCoords[0] + 1] == 2)) 
    {
        return 1;
    } else if (facing == WEST && (mazeGrid[gridXYCoords[1] + 1][gridXYCoords[0]] == 1 || mazeGrid[gridXYCoords[1] + 1][gridXYCoords[0]] == 2)) 
    {
        return 1;
    }
    return 0;
}

int canMoveForward(int mazeWidth, int gridXYCoords[], int facing, int mazeGrid[][mazeWidth + 2])
{
    if (facing == NORTH && (mazeGrid[gridXYCoords[1] - 1][gridXYCoords[0]] == 1 || mazeGrid[gridXYCoords[1] - 1][gridXYCoords[0]] == 2)) 
    {
        return 1;
    }  else if (facing == EAST && (mazeGrid[gridXYCoords[1]][gridXYCoords[0] + 1] == 1 || mazeGrid[gridXYCoords[1]][gridXYCoords[0] + 1] == 2)) 
    {
        return 1;
    } else if (facing == SOUTH && (mazeGrid[gridXYCoords[1] + 1][gridXYCoords[0]] == 1 || mazeGrid[gridXYCoords[1] + 1][gridXYCoords[0]] == 2)) 
    {
        return 1;
    } else if (facing == WEST && (mazeGrid[gridXYCoords[1]][gridXYCoords[0] - 1] == 1 || mazeGrid[gridXYCoords[1]][gridXYCoords[0] - 1] == 2)) 
    {
        return 1;
    }
    return 0;
}

void displayRobot(int xyCoords[], int facing)
{
    clear();
    switch (facing) 
    {
        case NORTH:
            displayImage("RobotNorth.png", xyCoords[0], xyCoords[1]);
            break;
        case EAST:
            displayImage("RobotEast.png", xyCoords[0], xyCoords[1]);
            break;
        case SOUTH:
            displayImage("RobotSouth.png", xyCoords[0], xyCoords[1]);
            break;
        case WEST:
            displayImage("RobotWest.png", xyCoords[0], xyCoords[1]);
            break;
    } 
}


