#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <iostream>
#include <math.h> 

using namespace std;

const int MazeHeight = 7;
const int MazeWidth = 7;

int Maze[MazeHeight][MazeWidth] = 
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
COORD EndPoint(0,0);
COORD zeroPoint(0,0);


int yMove[4] = {-1, 0, 1, 0};
int xMove[4] = {0, 1, 0, -1};

void PrintMaze2(int Maze2[MazeHeight][MazeWidth]){
    printf(" Y\n ^\n");
    for (int Y = 0; Y < MazeHeight; Y++)
    {
        printf("%d|  ", Y);
        for (int X = 0; X < MazeWidth; X++)
            {
                //printf("%d  ", Maze2[Y][X]);
                cout << std::setfill(' ') << setw(3) << Maze2[Y][X];
            }
        printf("\n");
    }
    printf("------------------------->\n");
    printf("      0  1  2  3  4  5  6  X\n");
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

bool SolveMaze(int X, int Y)
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
    if (X == 0 || Y == 0 || X == MazeWidth-1 || Y == MazeHeight-1)
    {
        cout << "   Terminal.\n" << endl;
        EndPoint.X = X;
        EndPoint.Y = Y;
        return true;
    }

    // Recursively search for our goal.
    if (X > 0 && Maze[Y][X - 1] == Free)
    {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R1. U=" << X << ", V=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
        if (SolveMaze(X - 1, Y)) return true;
    } else {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R1. U=" << X << ", V=" << Y << ". Wall." << endl;
        overallCounter++;
    }
    if (Y < MazeHeight && Maze[Y + 1][X] == Free)
    {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R2. U=" << X << ", V=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
        if (SolveMaze(X, Y + 1)) return true;
    } else {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R2. U=" << X << ", V=" << Y << ". Wall." << endl;
        overallCounter++;
    }
    if (X < MazeWidth && Maze[Y][X + 1] == Free)
    {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R3. U=" << X << ", V=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
        if (SolveMaze(X + 1, Y)) return true;
    } else {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R3. U=" << X << ", V=" << Y << ". Wall." << endl;
        overallCounter++;
    }
    if (Y > 0 && Maze[Y - 1][X] == Free)
    {
        cout << std::setfill(' ') << setw(6) << overallCounter << ") " << returnDashes(counter-2)<< "R4. U=" << X << ", V=" << Y << ". Free. L=L+1=" << counter << ". LAB[" << X << "," << Y << "]=" << counter << "." << endl;
        if (SolveMaze(X, Y - 1)) return true;
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

void printResult(COORD c){

    if (c.X == zeroPoint.X && c.Y == zeroPoint.Y) {
        cout << "  3.1. No tracable path";
        return;
    } else {
        cout << "  3.1. Path is found.\n\n";
    }
    int MazeResult[MazeHeight][MazeWidth] = {0};
    int resultCounter = Maze[c.Y][c.X];
    MazeResult[c.Y][c.X] = -2;
    string resultPath = "";
    string xs = std::to_string(c.X);
    string ys = std::to_string(c.Y);
    reverse(ys.begin(), ys.end());
    reverse(xs.begin(), xs.end());
    string nodesPath = " ,]" + ys + "=Y," + xs + "=X[";

    while(resultCounter > 2){
        resultCounter--;
        for (int i = 0; i < 4; ++i)
        {
            if (Maze[c.Y + yMove[i]][c.X + xMove[i]] == resultCounter) {
                MazeResult[c.Y + yMove[i]][c.X + xMove[i]] = -2;
                int j = i;
                if (i == 0) j=3;
                if (i == 1) j=4;
                if (i == 2) j=1;
                if (i == 3) j=2;
                resultPath += " ," + std::to_string(j) + "R";
                if(floor((float)(c.X + xMove[i])/10)>0) {
                    string hhh = std::to_string(c.X + xMove[i]);
                    reverse(hhh.begin(), hhh.end());
                    nodesPath += " ,]" + std::to_string(c.Y + yMove[i]) + "=Y," + hhh + "=X[";
                } else {
                    nodesPath += " ,]" + std::to_string(c.Y + yMove[i]) + "=Y," + std::to_string(c.X + xMove[i]) + "=X[";
                }
                c.X = c.X + xMove[i];
                c.Y = c.Y + yMove[i];
                break;
            }
        }
    }


    for (int Y = 0; Y < MazeHeight; Y++)
    {
        for (int X = 0; X < MazeWidth; X++)
            {
                if(MazeResult[Y][X] == -2) {
                    MazeResult[Y][X] = Maze[Y][X];
                } else {
                    if (Maze[Y][X] == 1) {
                        MazeResult[Y][X] = 1;
                    } else if (Maze[Y][X] == 0){
                        MazeResult[Y][X] = 0;
                    } else {
                        MazeResult[Y][X] = -1;
                    }
                } 
            }
    }
    cout << "  3.2. Path graphically\n\n";
    PrintMaze2(MazeResult);

    reverse(resultPath.begin(), resultPath.end());
    cout << "\n  3.3. Rules: " << resultPath.substr(0, resultPath.length() - 2) << endl;
    
    reverse(nodesPath.begin(), nodesPath.end());
    cout << "\n  3.4. Nodes: " << nodesPath.substr(0, nodesPath.length() - 2) << endl;
    return;
}

int main(int argc, char* argv[])
{
    counter = 1;
    overallCounter = 0;
    PrintMaze2(Maze);
    if (SolveMaze(StartingPoint.X, StartingPoint.Y))
        {
            printResult(EndPoint);
        }
    else
        {
            printf("No successfull resolution.\n");
        }

    return 0;
}