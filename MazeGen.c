#include <stdlib.h>
#include <time.h>
#include "MoveRobot.h"

void genGrid(int mazeWidth, int mazeHeight, int mazeGrid[][mazeWidth + 2])
{
    //Function fills empty array with a boarder of 3's filled with 0's - The + 1 is so the boarder is placed around the Maze Height and Width
    for (int n = 0; n <= (mazeHeight + 1); n++)
    {
        for (int i = 0; i <= (mazeWidth + 1); i++)
        {
            if (n == 0 || n == (mazeHeight + 1))
            {
                mazeGrid[n][i] = 3;
            } else if (i == 0 || i == (mazeWidth + 1))
            {
                mazeGrid[n][i] = 3;
            } else {
                mazeGrid[n][i] = 0;
            }
        }
    }
}

int genEnding(int mazeHeight)
{
    int randInt = (rand() % mazeHeight);
    if (randInt == 0)
        randInt++; //This is so the ending point cannot generate on the boarder of the maze (index = 0 is the boarder).
    return randInt;
}

void genPath(int mazeHeight, int mazeWidth, int mazeGrid[][mazeWidth + 2])
{
    //Use nested for loops to look over every cell of the maze within the boarder. For every cell, then a white tile will generate either south or east of it.
    for (int n = 1; n <= mazeHeight; n++)
    {
        for (int i = 1; i <= mazeWidth; i++)
        {
            if (mazeGrid[n][i] != 2){
                int randInt = (rand() % 2);
                if (randInt == 0 && mazeGrid[n + 1][i] != 3 && mazeGrid[n + 1][i] != 2 && mazeGrid[n + 1][i] != 1) // GENERATE SOUTH
                { 
                    mazeGrid[n + 1][i] = 1;
                } else if (randInt == 1 && mazeGrid[n][i + 1] != 3 && mazeGrid[n][i + 1] != 2 && mazeGrid[n + 1][i] != 1) // Generate EAST
                { 
                    mazeGrid[n][i + 1] = 1;
                }
            }
        }
    }
}

void cleanGrid(int mazeHeight, int mazeWidth, int mazeGrid[][mazeWidth + 2])
{
    //To clean up the maze search every cell for 2x2 spaces of white maze path, if so set the current cell to be zero [Maze wall].
    for (int n = 1; n <= mazeHeight; n++)
    {
        for (int i = 1; i <= mazeWidth; i++)
        {
            if (mazeGrid[n][i] != 2)
            {
                if (mazeGrid[n - 1][i] == 1 && mazeGrid[n][i - 1] == 1 && mazeGrid[n - 1][i - 1] == 1 && mazeGrid[n][i] == 1)
                    mazeGrid[n][i] = 0;
            }
        }
    }
}

void genMaze(int mazeWidth, int mazeHeight, int mazeGrid[][mazeWidth + 2])
{
    srand(time(NULL));
    genGrid(mazeWidth, mazeHeight, mazeGrid);
    mazeGrid[genEnding(mazeHeight)][mazeWidth] = 2; //Generate the ending sqaure of the maze at a random point down the right most column.
    mazeGrid[1][1] = 1; //Set the start point of the maze as the top-left - however when taking into account the boarder this is (1,1) in the grid
    genPath(mazeHeight, mazeWidth, mazeGrid);
    cleanGrid(mazeHeight, mazeWidth, mazeGrid);
}

int testMaze(int mazeWidth, int gridXYCoords[], int mazeGrid[][mazeWidth + 2], int facing, int XYCoords[])
{
    do
    {
        if (canMoveLeft(mazeWidth, gridXYCoords, facing, mazeGrid))
        {
            facing = left(facing);
            forward(XYCoords, gridXYCoords, facing);
        } else if (canMoveForward(mazeWidth, gridXYCoords, facing, mazeGrid))
        {
            forward(XYCoords, gridXYCoords, facing);
        } else if (!canMoveForward(mazeWidth, gridXYCoords, facing, mazeGrid))
        {
            facing = right(facing);
        }

        if (gridXYCoords[0] == 1 && gridXYCoords[1] == 1) //check if the robot has returned to the start.
        {
            return 0;
        }
    } while (!atMarker(mazeWidth, gridXYCoords, mazeGrid));
    return 1;
}
