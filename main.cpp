#include "assign2.h"

using namespace std;

int main(int argc, char** argv){
  bool gamemodeValid = false;
  string userGamemode = "";

  //obtain the users gamemode and run the simulation
  while(!gamemodeValid){
    cout << "what gamemode would you like to run? (classic, doughnut, mirror)" << endl;
    cin >> userGamemode;

    //run the classic gamemode
    if (userGamemode == "classic"){
      Classic *c = new Classic();
      c->run();
      delete c;
      gamemodeValid = true;
    }

    //run the doughnut gamemode
    else if(userGamemode == "doughnut"){
      Doughnut *d = new Doughnut();
      d->run();
      delete d;
      gamemodeValid = true;
    }

    //run the mirror gamemode
    else if(userGamemode == "mirror"){
      Mirror *m = new Mirror();
      m->run();
      delete m;
      gamemodeValid = true;
    }

    //users gamemode is invalid
    else{
      cout << "Error, please input a valid gamemode (classic, doughnut, mirror)" << endl;
    }
  }
  cout << "Simulation over. Please press enter to exit the program." << endl;
  while (cin.get() != '\n'){
    //waiting for enter
  }
  cout << "Thank you." << endl;
}
