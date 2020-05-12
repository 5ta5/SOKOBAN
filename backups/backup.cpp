/*
. -pusty
# -sciana
@ -sokoban
$ -pole_fajne
% -skrzynka
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <boost/any.hpp>

using namespace std;

class obj{
  public:
    string thype="";
    //boost::any object;
    //bool staticc=true;
    //bool block=true;
};

class wall : obj{
    
};

class rigid  : obj{
    int x;
    int y;
};

class level{
  private:
    boost::any o[10][10];
    int x=0;
    int y=0;
  public:
    void load(string filename);
    void debug();
};

void level::load(string filename){
    ifstream myfile;
    myfile.open(filename);
    string content="";
    int a, b, tmp;
    while(myfile >> content)
    {
        tmp=content.size();
        y=max(y, tmp);
        for(int i=0;i<content.size();i++){
            o[x][i].thype=content[i];
            if(content[i])
            /*
            if(content[i]=='%' || content[i]=='@'){
                o[x][i].staticc=false;
            }
            if(content[i]=='#'){
                o[x][i].block=true;
            }
            */
            //ob=new wall;
        }
        x++;
    }
    myfile.close();
};

void level::debug(){
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            cout<<o[i][j].thype;
        }
        cout<<"\n";
    }
    
}

int main(){
    level lvl;
    lvl.load("lvl.txt");
    //cout<<"---\n";
    lvl.debug();
    
    
    cout<<"Hello\n";
}
