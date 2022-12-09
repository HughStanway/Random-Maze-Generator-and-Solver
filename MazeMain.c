#include "graphics.h"
#include "MazeGen.h"
#include "MoveRobot.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

//Values can be changed to easily configure the size of the maze [any larger than 15 height and 35 width may not fit on the screen] and speed the the robot travels.
#define mazeWidth 25
#define mazeHeight 15
#define speed 110 //Lower number equates to a faster robot speed [Default is 100].

void drawMaze(int mazeGrid[][mazeWidth + 2])
{
    background();
    setColour(black);
    fillRect(0, 0, (40 * (mazeWidth + 2)), (40 * (mazeHeight + 2)));
    int xCoordinate = 0, yCoordinate = 0;
    for (int mazeRows = 0; mazeRows <= mazeHeight; mazeRows++)
    {
        for (int mazeColumns = 0; mazeColumns <= mazeWidth; mazeColumns++)
        {
            if (mazeGrid[mazeRows][mazeColumns] == 1)
            {
                setColour(white);
                fillRect(xCoordinate,yCoordinate,39,39);
            } else if (mazeGrid[mazeRows][mazeColumns] == 2)
            {
                setColour(gray);
                fillRect(xCoordinate,yCoordinate,39,39);
            }
            xCoordinate += 40;
        }
        yCoordinate += 40, xCoordinate = 0;
    }
}

void robot(int mazeGrid[][mazeWidth + 2], int xyCoords[], int facing, int gridXYCoords[])
{
    foreground();
    xyCoords[0] = 45, xyCoords[1] = 45, gridXYCoords[0] = 1, gridXYCoords[1] = 1, facing = EAST; //Start the robot at the begining.
    displayImage("RobotEast.png", xyCoords[0], xyCoords[1]); //Display initial robot at starting position
    while (!atMarker(mazeWidth, gridXYCoords, mazeGrid)) //keep running the algorithm until the robot reaches the finish tile.
    {
        if (canMoveLeft(mazeWidth, gridXYCoords, facing, mazeGrid)) //whenever the robot passes a left turn it turns left
        { 
            facing = left(facing);
            forward(xyCoords, gridXYCoords, facing);
        } else if (canMoveForward(mazeWidth, gridXYCoords, facing, mazeGrid)) //if the robot cannot turn left try to move forward.
        { 
            forward(xyCoords, gridXYCoords, facing);
        } else if (!canMoveForward(mazeWidth, gridXYCoords, facing, mazeGrid)) //If the robot cannot turn left or move forward look right.
        { 
            facing = right(facing);
        }
        displayRobot(xyCoords, facing);
        sleep(speed);
    }
}

int main(void)
{
    setWindowSize((40 * (mazeWidth + 2)),(40 * (mazeHeight + 2))); // multiply by 40 as each sqaure on the grid is displayed as 40x40 pixels
    //initialise the maze array [+2 is used to account for the boarder], the set of x,y cooridnates on the corresponding drawing, where the robot starts on the grid and the direction its facing 
    int mazeGrid[mazeHeight + 2][mazeWidth + 2], xyCoords[] = {45,45}, gridXYCoords[] = {1,1}, facing = EAST;  //north = 0, east = 1, south = 2, west = 3
    do
    {
        xyCoords[0] = 45, xyCoords[1] = 45, gridXYCoords[0] = 1, gridXYCoords[1] = 1, facing = EAST;
        genMaze(mazeWidth, mazeHeight, mazeGrid);
    } while (!testMaze(mazeWidth, gridXYCoords, mazeGrid, facing, xyCoords)); //Keep generating mazes until a working one is found - this sometimes means there is a few second delay unitl the maze is displayed.
    drawMaze(mazeGrid);
    robot(mazeGrid, xyCoords, facing, gridXYCoords);
}