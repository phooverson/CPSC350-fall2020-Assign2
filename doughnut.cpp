#include "assign2.h"

//default constructor
Doughnut::Doughnut(){
  Game(Doughnut);
}

//default destructor
Doughnut::~Doughnut(){

}

//run method to run the simulation
void Doughnut::run(){
  usersBoardType = getUsersBoard();
  obtainBoard();
  getUsersPreferedOutput();
  printCurrentBoard();
  runSimulation();
}

//run the doughnut gamemode
void Doughnut::runSimulation(){
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
void Doughnut::updateSquare(){
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
void Doughnut::calculateNeighborsTopLeft(){
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the top edge
void Doughnut::calculateNeighborsTopEdge(){
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontal-1] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the top right
void Doughnut::calculateNeighborsTopRight(){
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][0] == "X")
    neighborsAlive += 1;
  if (currentBoard[1][0] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][0] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontalDimensions-2] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the left side
void Doughnut::calculateNeighborsLeftSide(){
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the right side
void Doughnut::calculateNeighborsRightSide(){
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][0] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][0] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical+1][0] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the botton left
void Doughnut::calculateNeighborsButtomLeft(){
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][0] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][1] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-2][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the bottom edge
void Doughnut::calculateNeighborsBottomEdge(){
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal+1] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][horizontal+1] == "X")
    neighborsAlive += 1;
}

//calculate neighors alive for the bottom right
void Doughnut::calculateNeighborBottomRight(){
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical-1][horizontal] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][0] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][horizontalDimensions-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[0][horizontalDimensions-2] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-1][0] == "X")
    neighborsAlive += 1;
  if (currentBoard[verticalDimensions-2][0] == "X")
    neighborsAlive += 1;
}
