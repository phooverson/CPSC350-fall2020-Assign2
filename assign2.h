#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdlib>

using namespace std;

class Game{
  public:
    Game();
    Game(string userGamemode);
    ~Game();

    void gamemodeType();
  private:
    string gamemode;
    string usersPreferedOutput;
    ifstream myfile;
    ofstream outputFile;

    void openFile();
    void randomizeBoard();
    bool checkDimensions();
    void getDimensions();
    float getInitialPopulationDensity();
    void fillBoards();
    void printCurrentBoardToFile();
    void printCurrentBoardToScreen();
    void printCurrentBoardBetweenEnters();
    void printCurrentBoardWithPause();
    bool boardEmpty();
    bool boardHasSwitch();
    bool checkBoards();
    void openOutputFile(string fileName);
    void copyArrayToCheck();

  protected:
    string usersBoardType;
    int horizontalDimensions;
    int verticalDimensions;
    int generationNumber;
    bool simulationUnstable;
    string currentSquare;
    int neighborsAlive;
    int vertical;
    int horizontal;
    string currentBoard[128][128];
    string updatedBoard[128][128];
    string checkBoard[128][128];

    string getUsersBoard();
    void obtainBoard();
    void printCurrentBoard();
    string whereIsTheSquare();
    void calculateNeighborsAliveInside();
    void newState();
    void copyArray();
    void checkStability();
    bool cellsEqual();
    void getUsersPreferedOutput();
    void closeOpenOutputFile();
};

class Classic : public Game{
  public:
    Classic();
    ~Classic();

    void run();

  private:
    void runSimulation();
    void updateSquare();
    void calculateNeighborsTopLeft();
    void calculateNeighborsTopRight();
    void calculateNeighborsTopEdge();
    void calculateNeighborBottomRight();
    void calculateNeighborsButtomLeft();
    void calculateNeighborsBottomEdge();
    void calculateNeighborsLeftSide();
    void calculateNeighborsRightSide();
  protected:

};

class Doughnut : public Game{
  public:
    Doughnut();
    ~Doughnut();

    void run();

  private:
    void runSimulation();
    void updateSquare();
    void calculateNeighborsTopLeft();
    void calculateNeighborsTopRight();
    void calculateNeighborsTopEdge();
    void calculateNeighborBottomRight();
    void calculateNeighborsButtomLeft();
    void calculateNeighborsBottomEdge();
    void calculateNeighborsLeftSide();
    void calculateNeighborsRightSide();

  protected:

};

class Mirror : public Game{
  public:
    Mirror();
    ~Mirror();

    void run();

  private:
    void runSimulation();
    void updateSquare();
    void calculateNeighborsTopLeft();
    void calculateNeighborsTopRight();
    void calculateNeighborsTopEdge();
    void calculateNeighborBottomRight();
    void calculateNeighborsButtomLeft();
    void calculateNeighborsBottomEdge();
    void calculateNeighborsLeftSide();
    void calculateNeighborsRightSide();

  protected:

};
