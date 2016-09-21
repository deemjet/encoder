//encode.cpp
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


class encodeNode
{
  public:
  int weight;
  char data;
  string code;
  encodeNode* left;
  encodeNode* right;
  
};

class linkedNode
{
  public:
  int weight;
  char data;
  string code;
  linkedNode* next;
};

vector<char> fileContent;
vector<char> fileContent2;
vector<string> huffman;

int frequency(std::vector<char>& d , int n ){
  int count = 0;
  for(int j = 0; j < d.size(); j++){
    if(d[j] == n){
      count ++;
      fileContent[j] = NULL;
    }
  } 
  return count;
}

class Compare   //overloaded prototype for comparing second element in pair
{
public:
    bool operator() (encodeNode* node1, encodeNode* node2)
    {
        return node1->weight > node2->weight;
    }
};

int toBin(int dec) 
{
    int rem = 0;
    int num = 1;
    int bin = 0;
    while (dec!=0)
    {
        rem=dec%2;
        dec/=2;
        bin += rem * num;
        num*=10;
    }
    return bin;
}

  
priority_queue <char, vector<char>, greater<char>> q;

int main (int argc, const char * argv[])
{
  std::priority_queue<encodeNode*, vector<encodeNode*>, Compare> q;
  FILE * input;
  FILE * output;
  input=fopen("input.txt","r");
  vector<int> freq;
  vector<char> noDuplicates;
  huffman.clear(); // declared as global variabl
  noDuplicates.clear();
  freq.clear();
  fileContent.clear(); // declared as global variable
  int i = 0; //for a for loop
  char temp; 
  bool duplicate;
  map<char,int> myCount;
  int lengthOfCode = 0;
  std::string codeString = "";
  int currentCode = 0;
  int loopVarA = 0;
  int currentCode2 = 0;
  int newSize = 0;


  do{
    temp = getc(input);
    fileContent.push_back(temp);
    i++;
  }while(temp!=EOF);
 

    

  fileContent.pop_back();
  
  for (int loopVarC = 0; loopVarC < fileContent.size(); loopVarC++)
  {
    fileContent2.push_back(fileContent.at(loopVarC));
  }
  
  std::sort(fileContent.begin(),fileContent.begin()+fileContent.size());
  
  for(int k = 0; k < fileContent.size(); ++k){
    if(fileContent[k]!=NULL){
      noDuplicates.push_back(fileContent[k]);
      freq.push_back(frequency(fileContent,fileContent[k]));
    }
    }
    
  lengthOfCode = 1 + log2(freq.size());

  
  for (loopVarA = 0; loopVarA < freq.size(); )
  {
    
    currentCode = toBin(currentCode2);
    
    codeString = std::to_string(currentCode);
          
    while (codeString.size() < lengthOfCode)
    {
      codeString = "0" + codeString;
    }

    huffman.push_back(codeString);
    
    currentCode2++;
    loopVarA++;    
   
  }
 
    
  for (char c: noDuplicates) //construct map
  {
    myCount[c]++;
  }
  
  for(pair<char,int> ent : myCount) //construct queue
  {
 
    encodeNode* enc = new encodeNode;
    enc->data = ent.first;
    enc->weight = ent.second;
    enc->code = codeString;
    enc->left = enc->right = nullptr;
    q.push(enc);

  }
  
  newSize = q.size();
  

    
    encodeNode* combinedNode = nullptr;
    while (q.size() >= 2) //combine two lowest probability pairs into one pair whose .second is their combined frequency, and treat that as another pair for the next calculation involving two lowest
    {
      encodeNode* min1 = q.top();
      q.pop();
      
      encodeNode* min2 = q.top();
      q.pop();
      
      combinedNode = new encodeNode;
      combinedNode->data = '!';
      combinedNode->weight = min1->weight + min2->weight;
      combinedNode->left = min1;
      combinedNode->right = min2;
      
      q.push(combinedNode);
    }
    
    encodeNode* largestNode = q.top();
    encodeNode* root = new encodeNode;
    
    root->data = '!';
    root->weight = combinedNode->weight + largestNode->weight;
    root->left = combinedNode;
    root->right = largestNode;
    
 

    //  cout << "Opened file for writing. Please wait while the scheme is generated." << endl;
    
  std::ofstream out("scheme.txt"); //open output file

  std::map<char,string> secondMap;
  
  for(int p = 0; p < newSize; ++p){
    secondMap[noDuplicates[p]] = huffman.at(p);
    out << noDuplicates[p] << ":" << freq[p] << ":" << huffman.at(p) << endl;
  }
  
    out.close(); //close output file

  
    // cout << "Scheme has been generated. File closed." << endl;
  
    // cout << "Opened file for writing. Please wait while the message is generated." << endl;
    int sizeC;
  std::ofstream outMessage("message.txt"); //open output file
  
  
  for (int loopVarB = 0; loopVarB < fileContent2.size(); loopVarB++) //generate message
  {
    outMessage << secondMap[fileContent2[loopVarB]];
  }
  outMessage << endl;
  if(fileContent2.size()%6==0)
    sizeC = fileContent2.size() * 6;
  else 
    sizeC = fileContent2.size() * 5;
  
  outMessage << "Length of message: " << sizeC;
  outMessage.close();
  
  // cout << "Message has been generated. File closed." << endl;  
  
  return 0;
  
}

 
   
