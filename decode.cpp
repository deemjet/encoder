//decode.cpp
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <queue>
#include <map>
#include <math.h> 

using namespace std;

int main(){
  ifstream scheme("scheme.txt");
  ifstream message("message.txt");
  vector<string> schemeContents;
  string messageContents;
  schemeContents.clear();
  messageContents = "";
  string temp;
  string temp1;
  string size;
  int s;
  //Pass scheme into vector
  if(scheme){
  while(getline(scheme,temp)){
    schemeContents.push_back(temp);
    }
  }
  //Pass message into string
  if(message){
    getline(message,messageContents);
    getline(message,size);
  }
 
  s = stoi(size.substr(19));
  vector<char> characters;//to store characters **Corresponds to codes vector
  vector<string> codes;//to store corresponding codes for characters
  vector<string> messageCodes;//to parse message

  //to parse schemeContents
  for(int i = 0; i < schemeContents.size(); ++i){
    characters.push_back(schemeContents[i].at(0));
    if(schemeContents[i].at(3) == ':')
      codes.push_back(schemeContents[i].substr(4));
    else
      codes.push_back(schemeContents[i].substr(5));
  }

  //parse messageContents
  while(messageContents!=""){
    if(s%5==0){
    messageCodes.push_back(messageContents.substr(0,5));
    messageContents.erase(0,5);
    }
    else {
      messageCodes.push_back(messageContents.substr(0,7));
      messageContents.erase(0,7);
    }  
  }
  
  ofstream output("output.txt");

  //decode
  for(int j = 0; j < messageCodes.size(); ++j){//cycle through parsed message
    for(int k = 0; k < codes.size(); ++k){//compare to codes
	  if(messageCodes[j]==codes[k]){
	    output << characters[k];
	  }

	}
      }
  
  output.close();
}
