#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <iostream>
#include <list>

using namespace std;

const int MazeHeight = 10;
const int MazeWidth = 15;

int Maze[MazeHeight][MazeWidth] = 
{
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  
    1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  
    1,  0,  0,  0,  2,  0,  1,  1,  1,  0,  0,  0,  0,  0,  1,  
    1,  0,  1,  1,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  
    1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  
    1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  
    1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  
    1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  
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
COORD zeroPoint(0, 0);
COORD endPoint(0, 0);
list<COORD> processed;

int yMove[4] = {-1, 0, 1, 0};
int xMove[4] = {0, 1, 0, -1};


void PrintMaze(int Maze[MazeHeight][MazeWidth]){
    printf(" Y\n ^\n");
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
    printf("------------------------->\n");
    printf("      0  1  2  3  4  5  6   X\n");
}

void solveMaze(list<COORD> points){
    counter++;
	cout << "WAVE " << counter-2 << ", label L=\"" << counter << "\"\n";
    int stop = points.size();
	for (int i = 0; i < stop; ++i)
    {
        COORD c = points.front();
        points.pop_front();

        cout << "    Close CLOSE=" << overallCounter << ", X=" << c.X << ", Y=" << c.Y << ".\n";

        for (int i = 0; i < 4; ++i)
        {
            cout << "        R" << i << ". X=" << c.X + xMove[i] << ", Y=" << c.Y + yMove[i] << ". ";
            if (Maze[c.X + xMove[i]][c.Y + yMove[i]] == Free) {
                overallCounter2++;
                COORD d(c.X + xMove[i], c.Y + yMove[i]);
                Maze[c.X + xMove[i]][c.Y + yMove[i]] = counter;
                if (d.X == 0 || d.Y == 0 || d.X == MazeHeight-1 || d.Y == MazeWidth-1)
                {
                    cout << "Free. NEWN=" << overallCounter2 << ". Terminal." << endl;
                    endPoint = d;
                    return;
                }
                points.push_back(d);            
                cout << "Free. NEWN=" << overallCounter2 << ".\n";

            } else if (Maze[c.X + xMove[i]][c.Y + yMove[i]] == Wall){
                cout << "Wall.\n";
            } else {
                cout << "CLOSED or OPEN.\n";
            }   
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

void printResult(COORD c){
    if (c.X == zeroPoint.X && c.Y == zeroPoint.Y) {
        cout << "  3.1. No tracable path";
        return;
    } else {
        cout << "  3.1. Path is found.\n\n";
    }
    int MazeResult[MazeHeight][MazeWidth] = {0};
    int resultCounter = Maze[c.X][c.Y];
    MazeResult[c.X][c.Y] = -2;
    string resultPath = "";
    string nodesPath = "";
    string xs = std::to_string(c.X);
    string ys = std::to_string(c.Y);
    reverse(ys.begin(), ys.end());
    reverse(xs.begin(), xs.end());
    nodesPath += " ,]" + ys + "=Y," + xs + "=X[";

    while(resultCounter > 2){
        resultCounter--;
        for (int i = 0; i < 4; ++i)
        {
            if (Maze[c.X + xMove[i]][c.Y + yMove[i]] == resultCounter) {
                MazeResult[c.X + xMove[i]][c.Y + yMove[i]] = -2;
                int j = i;
                if (i == 0) j=3;
                if (i == 1) j=4;
                if (i == 2) j=1;
                if (i == 3) j=2;
                resultPath += " ," + std::to_string(j) + "R";
                string xs = std::to_string(c.X + xMove[i]);
                string ys = std::to_string(c.Y + yMove[i]);
                reverse(ys.begin(), ys.end());
                reverse(xs.begin(), xs.end());
                nodesPath += " ,]" + ys + "=Y," + xs + "=X[";
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
    PrintMaze(MazeResult);

    reverse(resultPath.begin(), resultPath.end());
    cout << "\n  3.3. Rules: " << resultPath.substr(0, resultPath.length() - 2) << endl;
    
    reverse(nodesPath.begin(), nodesPath.end());
    cout << "\n  3.4. Nodes: " << nodesPath.substr(0, nodesPath.length() - 2) << endl;
    return;
}

int main(int argc, char* argv[])
{
    counter = 2;
    overallCounter = 0;
    cout << "Part 1. Data\n  1.1. Labyrinth\n\n";
    PrintMaze(Maze);
    cout << "   1.2. Initial position X=4, Y=3. L=2.\n";
    cout << "PART 2. Trace\n\nWAVE 0, label L=\"2\". Initial position X=4, Y=3, NEWN=0\n\n";

    processed.push_back(StartingPoint);
    solveMaze(processed);

    //PrintMaze(Maze);

    cout << "\n\nPART 3. Results\n\n";

    printResult(endPoint);

    return 0;
}