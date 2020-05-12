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
#include <vector>
//#include <conio.h>
//#include <curses.h>
#include <stdio.h>

using namespace std;

/*
string matrix[100][100];
int matrix_x=0;
int matrix_y=0;
void show_matrix(){
    cout<<"---CURENT_STATE---\n";
    for(int i=0;i<matrix_x;i++){
        for(int j=0;j<matrix_y;j++){
            cout<<matrix[i][j];
        }
        cout<<"\n";
    }
    cout<<"------------------\n";
}*/

//class obj;
obj *kto_ma_x_y(int x, int y);


//REAL--------------------------------------------------------
class obj{
  public:
    string thype="X";
    //int x=0;
    //int y=0;
    void tp(int inp_x, int inp_y);
    virtual void move(int inp_x, int inp_y)=0;
    void display();
};



//REAL-----------------------------------------
class empty_space: public obj{
public:
    string thype=".";
    void move(int inp_x, int inp_y){};
};
empty_space emp;

class wall: public obj{
public:
    string thype="#";
    void move(int inp_x, int inp_y){};
};
vector<wall> walls;

class sokoban: public obj{
public:
    string thype="@";
    void move(int inp_x, int inp_y);
};
vector<sokoban> sokobans;

class crate: public obj{
public:
    string thype="%";
    void move(int inp_x, int inp_y){};
};
vector<crate> crates;

/*
void obj::tp(int inp_x, int inp_y){
    x=inp_x;
    y=inp_y;
}*/
/*
void obj::display(){
    matrix[x][y]=thype;
    matrix_x=max(matrix_x, x+1);
    matrix_y=max(matrix_y, y+1);
}*/
/*
class sokoban :public obj{
  public:
      void move(int inp_x, int inp_y);
};*/



void sokoban::move(int inp_x, int inp_y){
    //telepamy_tego_z_kim_sie_zamieniamy_do_nas
    //telepamy_nas_tam_gdzie_chcemy
    //cout<<"wtf?!?\n";
    obj *objekt=kto_ma_x_y(x+inp_x, y+inp_y);
    (*objekt).tp(x, y);
    tp(x+inp_x, y+inp_y);
    
    (*objekt).display();
    display();
}


/*
vector<obj> objekt;
obj *kto_ma_x_y(int x, int y){
    for(int i=0;i<objekt.size();i++){
        if(objekt[i].x==x, objekt[i].y==y){
            return(&objekt[i]);
        }
    }
}
obj *player(int num){
    for(int i=0;i<objekt.size();i++){
        if(objekt[i].thype=="@"){
            return(&objekt[i]);
        }
    }
}
*/
/*
int main() 
{
    
    cout << '\n' << "Press a key to continue...";
    
    //getch();
    getchar();
    return 0;
}*/

int main(){
    //level lvl;
    //lvl.load("lvl.txt");
    //cout<<"---\n";
    //lvl.debug();
    /*
    obj pacjent_zero;
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            pacjent_zero.x=i;
            pacjent_zero.y=j;
            pacjent_zero.thype=".";
            if(i==5 && j==5){                
                pacjent_zero.thype="@";
            }
            objekt.push_back(pacjent_zero);
            pacjent_zero.display();
        }
    }
    */
    //(*player(0)).move(0, 1);
    
    char ch;
    while(true){
        cin>>ch;
        switch(ch){
            case 'w':
                (*player(0)).move(-1, 0);
                break;
            case 'a':
                (*player(0)).move(0, -1);
                break;
            case 's':
                (*player(0)).move(1, 0);
                break;
            case 'd':
                (*player(0)).move(0, 1);
                break;                
        }
        show_matrix();
    }
    
    show_matrix();
    cout<<"Hello\n";
}










/*
 c l*ass empty_space :public obj{
 
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
                             */
