#include "assign2.h"

//default constructor
Game::Game(){
  gamemode = "classic";
  usersBoardType = "";
  horizontalDimensions = 0;
  verticalDimensions = 0;
  generationNumber = 0;
  simulationUnstable = true;
  srand (time(NULL));
}

//constructor with users desired gamemode
Game::Game(string userGamemode){
  gamemode = userGamemode;
  usersBoardType = "";
  horizontalDimensions = 0;
  verticalDimensions = 0;
  generationNumber = 0;
  simulationUnstable = true;
  srand (time(NULL));
}

//destructor
Game::~Game(){
  //cout << "Bye-bye game" << endl;
}

//ask the user for the type of board they would like to input
string Game::getUsersBoard(){
  string usersAwnser= "";
  bool usersAwnserValid = false;

  //loop through till the user iputs a valid board type
  while (!usersAwnserValid){
    cout << "Would you like to input a game board form a file or randomize one? (file or random)" << endl;
    cin >> usersAwnser;
    if (usersAwnser == "file" || usersAwnser == "random"){
      usersAwnserValid = true;
    }
    else {
      cout << "Invalid awnser, please enter 'file' or 'random'" << endl;
    }
  }
  return usersAwnser;
}

//get the users prefered output
void Game::getUsersPreferedOutput(){
  bool usersAwnserValid = false;

  //loop through till the users inputs a valid output type
  while(!usersAwnserValid){
    cout << "How would you like to output? Either to a file, a brief pause inbetween generateions or after you hit enter. (file, pause, enter)" << endl;
    cin >> usersPreferedOutput;
    if (usersPreferedOutput == "file" || usersPreferedOutput == "pause" || usersPreferedOutput == "enter"){
      usersAwnserValid = true;
    }
    else {
      cout << "Invalid awnser, please enter 'file', 'pause', or 'enter'";
    }
  }

  //if user said file output, obtain the file
  if (usersPreferedOutput == "file"){
    string usersOutputFile;
    cout << "What file would you like to output to?" << endl;
    cin >> usersOutputFile;
    openOutputFile(usersOutputFile);
  }
}

//opens the output file
void Game::openOutputFile(string fileName){
  outputFile.open(fileName);
}

//close the opened output file
void Game::closeOpenOutputFile(){
  outputFile.close();
}

//obtains the board for the simulation
void Game::obtainBoard(){
  if (usersBoardType == "file"){
    openFile();
  }
  else if (usersBoardType == "random"){
    randomizeBoard();
  }
  else{
    cout << "ERROR: obtainBoard()" << endl;
  }
}

//opens the users file
void Game::openFile(){
  string usersFile = "";
  bool fileExists = false;
  string line = "";

  //while the file exists obtain th eboard
  while(!fileExists){
    cout << "What file would you like us pull from?" << endl;
    cin >> usersFile;
    ifstream myFile (usersFile);
    if (myFile.is_open()){
      fileExists = true;
      int numberOfLines = 0;
      int placeInString;
        while(getline(myFile,line)){
        numberOfLines += 1;
        if(numberOfLines == 1){
          verticalDimensions = stoi(line);
        }
        else if(numberOfLines == 2){
          horizontalDimensions = stoi(line);
          fillBoards();
        }
        else {
          placeInString = 0;
          while(placeInString<=line.length()-1){
            if (line.at(placeInString) == 'X')
              currentBoard[numberOfLines-3][placeInString] = "X";
            placeInString += 1;
          }
        }
      }
    }
    else{
      cout << "ERROR: File could not be found, or opened. Please try agian." << endl;
    }
  }
  myfile.close();
}


//randomizes the board for the simulation
void Game::randomizeBoard(){
  getDimensions();
  fillBoards();
  float initialPopulationDensity = getInitialPopulationDensity();
  float totalNumberOfAliveCells = (horizontalDimensions*verticalDimensions)*initialPopulationDensity;
  int numberOfAliveCells = 0;
  int randomVerticalNumber;
  int randomHorizontalNumber;
  while (numberOfAliveCells<totalNumberOfAliveCells){
    randomVerticalNumber = rand() % (verticalDimensions);
    randomHorizontalNumber = rand() % (horizontalDimensions);
    if (currentBoard[randomVerticalNumber][randomHorizontalNumber] == "X"){
      continue;
    }
    else{
      currentBoard[randomVerticalNumber][randomHorizontalNumber] = "X";
      numberOfAliveCells += 1;
    }
  }
}

//fills the board as a base board
void Game::fillBoards(){
  for (int i = 0; i < verticalDimensions; ++i){
    for (int j = 0; j < horizontalDimensions; ++j){
      currentBoard[i][j] = "-";
      updatedBoard[i][j] = "-";
    }
  }
}

//gets the initial Population Density from the user
float Game::getInitialPopulationDensity(){
  bool invalidDensity = true;
  int  numberOfChecks = 0;
  float initialPopulationDensity;
  while(invalidDensity){
    if(numberOfChecks > 0)
      cout << "invalid desity size, please ensure it is a decimal between 0 and 1" << endl;
    cout << "What is the decimal value of the initial population density" << endl;
    cin >> initialPopulationDensity;
    if (initialPopulationDensity >= 0.0 && initialPopulationDensity <= 1.0)
      invalidDensity = false;
    numberOfChecks += 1;
  }
  return initialPopulationDensity;
}


//gets the dimensions from the user
void Game::getDimensions(){
  int numberOfChecks = 0;
  while (!checkDimensions()){
    if (numberOfChecks > 0)
      cout << "Error in demenions, please try again. Please ensure they are integers and are greater then 0." << endl;
    cout << "What are the dimensions you would like to use?" << endl;
    cout << "Vertical (up to down): ";
    cin >> verticalDimensions;
    cout << "Horizontal (left to right): ";
    cin >> horizontalDimensions;
    numberOfChecks += 1;
  }
}

//checks that the dimensions are greater the 0
bool Game::checkDimensions(){
  if (verticalDimensions > 0 && horizontalDimensions > 0)
    return true;
  else
    return false;
}


//update the cell to its new state
void Game::newState(){
  if (neighborsAlive <= 1 || neighborsAlive >= 4)
    updatedBoard[vertical][horizontal] = "-";
  else if (neighborsAlive == 2)
    updatedBoard[vertical][horizontal] = currentBoard[vertical][horizontal];
  else if(neighborsAlive == 3)
    updatedBoard[vertical][horizontal] = "X";
  else
    cout << "ERROR: newState()" << endl;
}


//calculate how many neighors are alive for an inside cell
void Game::calculateNeighborsAliveInside(){
  neighborsAlive = 0;
  if (currentBoard[vertical-1][horizontal-1] == "X")
    neighborsAlive += 1;
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
  if (currentBoard[vertical+1][horizontal-1] == "X")
    neighborsAlive += 1;
  if (currentBoard[vertical][horizontal-1] == "X")
    neighborsAlive += 1;
}

//calculate where the square is and return its location
string Game::whereIsTheSquare(){
  if (vertical == 0){
    if (horizontal == 0){
      return "top left";
    }
    else if (horizontal == horizontalDimensions-1){
      return "top right";
    }
    else{
      return "top edge";
    }
  }
  else if (vertical == verticalDimensions-1){
    if (horizontal == horizontalDimensions-1){
      return "botton right";
    }
    else if (horizontal == 0){
      return "bottom left";
    }
    else{
      return "bottom edge";
    }
  }
  else{
    if (horizontal == 0){
      return "left side";
    }
    else if (horizontal == horizontalDimensions-1){
      return "right side";
    }
    else{
      return "inside";
    }
  }
}

//print the board pased of the output type
void Game::printCurrentBoard(){
  if(usersPreferedOutput == "pause")
    printCurrentBoardWithPause();
  else if(usersPreferedOutput == "file")
    printCurrentBoardToFile();
  else if(usersPreferedOutput == "enter")
    printCurrentBoardBetweenEnters();
}

//print board with a 1 second pause
void Game::printCurrentBoardWithPause(){
  printCurrentBoardToScreen();
  sleep(1);
}

//prints the current game board to the screen
void Game::printCurrentBoardToScreen(){
  if (generationNumber == 0)
    cout << 0 << endl;
  else
    cout << "Generation " << generationNumber << endl;

  for (int i = 0; i < verticalDimensions; ++i){
    for (int j = 0; j < horizontalDimensions; ++j){
      cout << currentBoard[i][j];
    }
    cout << endl;
  }
  generationNumber += 1;
}

//print game board to a file
void Game::printCurrentBoardToFile(){
  if (generationNumber == 0)
    outputFile << 0 << endl;
  else
    outputFile << "Generation " << generationNumber << endl;

  for (int i = 0; i < verticalDimensions; ++i){
    for (int j = 0; j < horizontalDimensions; ++j){
      outputFile << currentBoard[i][j];
    }
    outputFile << endl;
  }
  generationNumber += 1;
}

//print gameboard inbetween enters
void Game::printCurrentBoardBetweenEnters(){
  while (cin.get() != '\n'){
    //waiting for enter
  }
  printCurrentBoardToScreen();
}

//copy the gameboard to the updated
void Game::copyArray(){
  for (int i = 0; i < verticalDimensions; ++i){
    for (int j = 0; j < horizontalDimensions; ++j){
      currentBoard[i][j] = updatedBoard[i][j];
    }
  }
  //check every 3rd generation
  if(generationNumber % 3 == 0)
    copyArrayToCheck();
}

//copy current board to a check board
void Game::copyArrayToCheck(){
  for (int i = 0; i < verticalDimensions; ++i){
    for (int j = 0; j < horizontalDimensions; ++j){
      checkBoard[i][j] = currentBoard[i][j];
    }
  }
}

//check for stability
void Game::checkStability(){
  if (!cellsEqual()){
    simulationUnstable = false;
  }
  else if (boardEmpty()){
    simulationUnstable = false;
  }
  else if (boardHasSwitch()){
    simulationUnstable = false;
  }
  else if (generationNumber == 5000){
    simulationUnstable = false;
  }
}

//if the board as no alive cells
bool Game::boardEmpty(){
  for (int i = 0; i < verticalDimensions; ++i){
    for (int j = 0; j < horizontalDimensions; ++j){
      if (updatedBoard[i][j] == "X")
        return false;
    }
  }
  return true;
}

//if the board has a switch that alternates every generation
bool Game::boardHasSwitch(){
  int count = 0;
  int totalCells = verticalDimensions*horizontalDimensions;
  if(generationNumber < 4)
    return false;
  for (int i = 0; i < verticalDimensions; ++i){
    for (int j = 0; j < horizontalDimensions; ++j){
      if (checkBoard[i][j] == updatedBoard[i][j])
        count += 1;
    }
  }
  if (count == totalCells)
    return true;
  return false;
}

//if the board is stabalized and doesnt alternate on generations
bool Game::cellsEqual(){
  for (int i = 0; i < verticalDimensions; ++i){
    for (int j = 0; j < horizontalDimensions; ++j){
      if (currentBoard[i][j] != updatedBoard[i][j]){
        return true;
      }
    }
  }
}
