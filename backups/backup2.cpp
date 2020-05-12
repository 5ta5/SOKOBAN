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
    string thype="$";
    void scream(char inp){
        thype=inp;
        cout<<"WTF!?!\n";
        cout<<thype;
        cout<<"FTW?!?\n";
    }
    string get_thype(){
        cout<<thype<<"\n";
        return(thype);
    }
    //bool staticc=true;
    //bool block=true;
};

class empty_space :public obj{
    
};

class wall :public obj{
    
};

class rigid :public obj{
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
            if(content[i]=='.' or true){
                empty_space emp;
                o[x][i]=emp;
                //boost::any_cast<empty_space>(o[x][i]).thype=content[i];
                boost::any_cast<empty_space>(o[x][i]).scream(content[i]);
                cout<<boost::any_cast<empty_space>(o[x][i]).get_thype()<<"\n";
                //cout<<boost::any_cast<empty_space>(o[x][i]).thype;
            }
            if(content[i]=='#' and false){
                wall wal;
                o[x][i]=wal;
                boost::any_cast<wall>(o[x][i]).thype=content[i];
            }
            
            //cout<<boost::any_cast<empty_space>(o[x][i]).thype;
        }
        x++;
    }
    myfile.close();
};

void level::debug(){
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            cout<<boost::any_cast<empty_space>(o[i][j]).thype;
        }
        cout<<"\n";
    }
    
}

int main(){
    level lvl;
    lvl.load("lvl.txt");
    cout<<"---\n";
    lvl.debug();
    
    
    cout<<"Hello\n";
}
