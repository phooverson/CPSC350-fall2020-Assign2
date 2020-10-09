#include "assign2.h"

//default constructor
Mirror::Mirror(){
  Game(Mirror);
}

//default destructor
Mirror::~Mirror(){

}

//run method to run the simulation
void Mirror::run(){
  usersBoardType = getUsersBoard();
  obtainBoard();
  getUsersPreferedOutput();
  printCurrentBoard();
  runSimulation();
}

//run the mirror gamemode
void Mirror::runSimulation(){
  printCurrentBoard();
  while(simulationUnstable){
    for (vertical = 0; vertical < verticalDimensions; ++vertical){
      for (horizontal = 0; horizontal < horizontalDimensions; ++horizontal){
        updateSquare();
      }
    }
    checkStability();
    if(!simulationUnstable){
      closeOpenOutputFile();
      break;
    }
    else{
      copyArray();
      printCurrentBoard();
    }
  }
}

//update the squares based off of where they are
void Mirror::updateSquare(){
  currentSquare = whereIsTheSquare();
  neighborsAlive = 0;
  if(currentSquare == "inside"){
    calculateNeighborsAliveInside();
    newState();
  }
  else if (currentSquare == "top left"){
    calculateNeighborsTopLeft();
    newState();
  }
  else if (currentSquare == "top right"){
    calculateNeighborsTopRight();
    newState();
  }
  else if(currentSquare == "top edge"){
    calculateNeighborsTopEdge();
    newState();
  }
  else if(currentSquare == "botton right"){
    calculateNeighborBottomRight();
    newState();
  }
  else if(currentSquare == "bottom left"){
    calculateNeighborsButtomLeft();
    newState();
  }
  else if(currentSquare == "bottom edge"){
    calculateNeighborsBottomEdge();
    newState();
  }
  else if(currentSquare == "left side"){
    calculateNeighborsLeftSide();
    newState();
  }
  else if(currentSquare == "right side"){
    calculateNeighborsRightSide();
    newState();
  }
  else{
    cout << "Error: updateSquare()" << endl;
  }
}

//calculate neighors alive for the top left
void Mirror::calculateNeighborsTopLeft(){
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical+1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical][horizontal] == "X")
    neighborsAlive += 3;
}

//calculate neighors alive for the top edge
void Mirror::calculateNeighborsTopEdge(){
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical+1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical][horizontal] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the top right
void Mirror::calculateNeighborsTopRight(){
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical+1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical][horizontal] == "X")
    neighborsAlive += 3;
}

//calculate neighors alive for the left side
void Mirror::calculateNeighborsLeftSide(){
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical-1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical][horizontal] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the right side
void Mirror::calculateNeighborsRightSide(){
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical-1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical][horizontal] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the botton left
void Mirror::calculateNeighborsButtomLeft(){
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical-1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical][horizontal] == "X")
    neighborsAlive += 3;
}

//calculate neighors alive for the bottom edge
void Mirror::calculateNeighborsBottomEdge(){
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical-1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical][horizontal] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the bottom right
void Mirror::calculateNeighborBottomRight(){
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical-1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 2;
  if (currentBoard[vertical][horizontal] == "X")
    neighborsAlive += 3;
}
