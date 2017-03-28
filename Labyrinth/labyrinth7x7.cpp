#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <iostream>

using namespace std;

const int MazeHeight = 7;
const int MazeWidth = 7;

int Maze2[10][15] = 
{
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  
    1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  
    1,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  1,  
    1,  0,  1,  1,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  
    1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  
    1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  
    1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  
    1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  
};

int Maze[7][7] = 
{
    1, 1, 1, 1, 1, 0, 1, 
    0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 0, 1, 1, 
    1, 0, 0, 0, 0, 1, 1, 
    1, 0, 1, 0, 1, 1, 1, 
    1, 0, 0, 0, 1, 1, 1, 
    1, 1, 1, 1, 1, 1, 1,  
};

const int Wall = 1;
const int Free = 0;
int counter;
int overallCounter;

class COORD
{
public:
    int X;
    int Y;
    COORD(int x = 0, int y = 0) { X = x, Y = y; }
    COORD(const COORD &coord) { X = coord.X; Y = coord.Y; }
};

COORD StartingPoint(4, 3);

void PrintMaze2(){
    printf(" ^\n");
    for (int Y = 0; Y < MazeHeight; Y++)
    {
        printf("%d|  ", Y);
        for (int X = 0; X < MazeWidth; X++)
            {
                //printf("%d  ", Maze2[Y][X]);
                cout << std::setfill(' ') << setw(3) << Maze[Y][X];
            }
        printf("\n");
    }
    printf("------------------------------------------------->\n");
    printf("      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14\n");
}

void PrintMaze(){
    printf(" ^\n");
    for (int Y = 0; Y < 7; Y++)
    {
        printf("%d|  ", Y);
        for (int X = 0; X < 7; X++)
            {
                //printf("%d  ", Maze2[Y][X]);
                cout << std::setfill(' ') << setw(3) << Maze[Y][X];
            }
        printf("\n");
    }
    printf("------------------------->\n");
    printf("      0  1  2  3  4  5  6\n");
}

string returnDashes(int n){
    string s = "";
    for (int i = 0; i < n; ++i)
    {
        s += '-';
    }
    return s;
}

bool SolveMaze2(int X, int Y)
{
    // Make the move (if it's wrong, we will backtrack later.
    counter++;
    overallCounter++;
    //char c = '0' + counter;
    //Maze[Y][X] = SomeDude;
    Maze[Y][X] = counter;

    // If you want progressive update, uncomment these lines...
    //PrintDaMaze();
    //sleep(1);

    // Check if we have reached our goal.
    if (X == 0 || Y == 0 || X == MazeWidth || Y == MazeHeight)
    {
        cout << "Terminal" << endl;
        return true;
    }

    // Recursively search for our goal.
    if (X > 0 && Maze[Y][X - 1] == Free)
    {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R1. U=" << X << ", V=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
        if (SolveMaze2(X - 1, Y)) return true;
    } else {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R1. U=" << X << ", V=" << Y << ". Wall." << endl;
        overallCounter++;
    }
    if (Y < MazeHeight && Maze[Y + 1][X] == Free)
    {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R2. U=" << X << ", V=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
        if (SolveMaze2(X, Y + 1)) return true;
    } else {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R2. U=" << X << ", V=" << Y << ". Wall." << endl;
        overallCounter++;
    }
    if (X < MazeWidth && Maze[Y][X + 1] == Free)
    {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R3. U=" << X << ", V=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
        if (SolveMaze2(X + 1, Y)) return true;
    } else {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R3. U=" << X << ", V=" << Y << ". Wall." << endl;
        overallCounter++;
    }
    if (Y > 0 && Maze[Y - 1][X] == Free)
    {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R4. U=" << X << ", V=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
        if (SolveMaze2(X, Y - 1)) return true;
    } else {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R4. U=" << X << ", V=" << Y << ". Wall." << endl;
        overallCounter++;
    }

    cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2) << "Backtrack from X=" << X << ", Y=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
    // Otherwise we need to backtrack and find another solution.
    counter--;
    //Maze2[Y][X] = Free;

    // If you want progressive update, uncomment these lines...
    //PrintDaMaze();
    //Sleep(50);
    return false;
}

bool SolveMaze(int X, int Y)
{
    // Make the move (if it's wrong, we will backtrack later.
    counter++;
    //char c = '0' + counter;
    //Maze[Y][X] = SomeDude;
    Maze[Y][X] = counter;

    // If you want progressive update, uncomment these lines...
    //PrintDaMaze();
    //sleep(1);

    // Check if we have reached our goal.
    if (X == 0 || Y == 0 || X == 6 || Y == 6)
    {
        return true;
    }

    // Recursively search for our goal.
    if (X > 0 && Maze[Y][X - 1] == Free && SolveMaze(X - 1, Y))
    {
        return true;
    }
    if (Y < MazeHeight && Maze[Y + 1][X] == Free && SolveMaze(X, Y + 1))
    {
        return true;
    }
    if (X < MazeWidth && Maze[Y][X + 1] == Free && SolveMaze(X + 1, Y))
    {
        return true;
    }
    if (Y > 0 && Maze[Y - 1][X] == Free && SolveMaze(X, Y - 1))
    {
        return true;
    }

    // Otherwise we need to backtrack and find another solution.
    counter--;
    //Maze[Y][X] = Free;

    // If you want progressive update, uncomment these lines...
    //PrintDaMaze();
    //Sleep(50);
    return false;
}

int main(int argc, char* argv[])
{
    counter = 1;
    overallCounter = 0;
    PrintMaze2();
    bool maze7x7 = false;
    if(maze7x7){
        if (SolveMaze(StartingPoint.X, StartingPoint.Y))
        {
            PrintMaze();
        }
        else
        {
            printf("No successfull resolution.\n");
        }
    } else {
        if (SolveMaze2(StartingPoint.X, StartingPoint.Y))
        {
            PrintMaze2();
        }
        else
        {
            printf("No successfull resolution.\n");
        }
    }

    return 0;
}