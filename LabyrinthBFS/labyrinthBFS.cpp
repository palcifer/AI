#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <iostream>
#include <list>

using namespace std;

const int MazeHeight = 7;
const int MazeWidth = 7;

int Maze[7][7] = 
{
    1, 1, 1, 1, 1, 0, 1, 
    0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 1, 0, 1, 1, 
    1, 0, 0, 0, 2, 1, 1, 
    1, 0, 1, 0, 0, 0, 1, 
    1, 0, 0, 0, 1, 0, 1, 
    1, 1, 1, 1, 1, 1, 1,  
};

const int Wall = 1;
const int Free = 0;
int counter;
int overallCounter;
int overallCounter2;

class COORD
{
public:
    int X;
    int Y;
    COORD(int x = 0, int y = 0) { X = x, Y = y; }
    COORD(const COORD &coord) { X = coord.X; Y = coord.Y; }
};

COORD StartingPoint(3, 4);
list<COORD> processed;


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

void solveMaze(list<COORD> points){
    counter++;
	cout << "WAVE " << counter-2 << ", label L=\"" << counter << "\"\n";
	for (int i = 0; i < points.size(); ++i)
    {
        COORD c = points.front();
        points.pop_front();

        if (c.X == 0 || c.Y == 0 || c.X == MazeWidth || c.Y == MazeHeight)
        {
            cout << "Terminal." << endl;
            return;
        }

        cout << "    Close CLOSE=" << overallCounter << ", X=" << c.X << ", Y=" << c.Y << ".\n";

        cout << "        R1. X=" << c.X-1 << ", Y=" << c.Y << ". ";
        if (Maze[c.X-1][c.Y] == Free) {
            overallCounter2++;
            COORD d(c.X-1,c.Y);
            points.push_back(d);
            Maze[c.X-1][c.Y] = counter;
            cout << "Free. NEWN=" << overallCounter2 << ".\n";

        } else if (Maze[c.X-1][c.Y] == Wall){
            cout << "Wall.\n";
        } else {
            cout << "CLOSED or OPEN.\n";
        }

        cout << "        R2. X=" << c.X << ", Y=" << c.Y-1 << ". ";
        if (Maze[c.X][c.Y-1] == Free) {
            overallCounter2++;
            COORD d(c.X,c.Y-1);
            points.push_back(d);
            Maze[c.X][c.Y-1] = counter;
            cout << "Free. NEWN=" << overallCounter2 << ".\n";

        } else if (Maze[c.X][c.Y-1] == Wall){
            cout << "Wall.\n";
        } else {
            cout << "CLOSED or OPEN.\n";
        }


        cout << "        R3. X=" << c.X+1 << ", Y=" << c.Y << ". ";
        if (Maze[c.X+1][c.Y] == Free) {
            overallCounter2++;
            COORD d(c.X+1,c.Y);
            points.push_back(d);
            Maze[c.X+1][c.Y] = counter;
            cout << "Free. NEWN=" << overallCounter2 << ".\n";

        } else if (Maze[c.X+1][c.Y] == Wall){
            cout << "Wall.\n";
        } else {
            cout << "CLOSED or OPEN.\n";
        }


        cout << "        R4. X=" << c.X << ", Y=" << c.Y+1 << ". ";
        if (Maze[c.X][c.Y+1] == Free) {
            overallCounter2++;
            COORD d(c.X,c.Y+1);
            points.push_back(d);
            Maze[c.X][c.Y+1] = counter;
            cout << "Free. NEWN=" << overallCounter2 << ".\n";

        } else if (Maze[c.X][c.Y+1] == Wall){
            cout << "Wall.\n";
        } else {
            cout << "CLOSED or OPEN.\n";
        }

        overallCounter++;
    }
    if(points.empty()) {
        cout << "No resolution found.\n";
        return;
    } else {
        solveMaze(points);
    }
    return;
}

int main(int argc, char* argv[])
{
    counter = 2;
    overallCounter = 0;
    cout << "Part 1. Data\n  1.1. Labyrinth\n\n";
    PrintMaze();
    cout << "   1.2. Initial position X=4, Y=3. L=2.\n";
    cout << "PART 2. Trace\n\nWAVE 0, label L=\"2\". Initial position X=4, Y=3, NEWN=1\n\n";

    processed.push_back(StartingPoint);
    solveMaze(processed);

    PrintMaze();

    return 0;
}