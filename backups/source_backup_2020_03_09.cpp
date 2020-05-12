//sfml simple fast multimedia library
/*
. -pusty
# -sciana
@ -sokoban
$ -pole_fajne
% -skrzynka
*/
#include <SFML/Graphics.hpp>
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

class obj;
class level;


//REAL--------------------------------------------------------
class obj{
  public:
    void tp(int inp_x, int inp_y);
    sf::Texture texture;
    virtual void move(int inp_x, int inp_y)=0;
    virtual string thype()=0;
    void display();
};

class rigid:public obj{
public:
    level *lvl;
    int x=0;
    int y=0;
};



//REAL-----------------------------------------
class empty_space: public obj{
public:
    string thype(){return(" ");};
    void move(int inp_x, int inp_y){};
};

class empty_flor: public obj{
public:
    string thype(){return(".");};
    void move(int inp_x, int inp_y){};
};

class wall: public obj{
public:
    string thype(){return("#");};
    void move(int inp_x, int inp_y){};
};

class sokoban: public rigid{
public:
    string thype(){return("@");};
    void move(int inp_x, int inp_y);
};

class crate: public rigid{
public:
    bool happy=false;
    string thype(){return("%");};
    void move(int inp_x, int inp_y);
};




class level{
private:
    int sizeee=20;
public:
    empty_space emp;
    empty_flor flo;
    //vector<wall> walls;
    //wall wall_tmp;
    //vector<sokoban> sokobans;
    //vector<crate> crates;
    
    wall walls[400];
    int walls_counter=0;
    sokoban sokobans[400];
    int sokobans_counter=0;
    crate crates[400];
    int crates_counter=0;
    
    int solve=0;
    
    //int sizeee=10;
    obj *matrix[20][20];
    bool overmatrix[20][20];
    level(){
        for(int i=0;i<sizeee;i++){
            for(int j=0;j<sizeee;j++){
                overmatrix[i][j]=false;
                matrix[i][j]=&emp;
            }
        }
    }
    void render(){
        cout<<"STAN---------\n";
        for(int i=0;i<sizeee;i++){
            for(int j=0;j<sizeee;j++){
                if(overmatrix[i][j]==true && matrix[i][j]->thype()=="."){
                    cout<<"$";
                }else{
                    cout<<matrix[i][j]->thype();
                }
            }
            cout<<"\n";
        }
        if(solve<crates_counter){
            cout<<solve<<"\n";
        }else{
            cout<<"!!!YOU WIN!!!\n";
        }
        
        cout<<"-------------\n";
    }
    void add_obj(string name, int x, int y){
        if(name=="." || name=="$"){
            matrix[x][y]=&(flo);
        }
        
        if(name=="$"){
            overmatrix[x][y]=true;
        }
        if(name=="#"){
            //fix-me
            //walls.push_back(wall_tmp);
            //matrix[x][y]=&(walls[(walls.size()-1)]);
            matrix[x][y]=&(walls[walls_counter]);
            walls_counter++;
        }
        if(name=="@"){
            matrix[x][y]=&(sokobans[sokobans_counter]);
            sokobans[sokobans_counter].lvl=this;//fix-me
            sokobans[sokobans_counter].x=x;
            sokobans[sokobans_counter].y=y;
            sokobans_counter++;
        }
        if(name=="%"){
            matrix[x][y]=&(crates[crates_counter]);
            crates[crates_counter].lvl=this;
            crates[crates_counter].x=x;
            crates[crates_counter].y=y;
            crates_counter++;
        }
    }
    
    void add_obj(char name, int x, int y){
        string tmp="";
        tmp+=name;
        add_obj(tmp, x, y);
    }
    
    obj *kto_ma_x_y(int x, int y){
        return(matrix[x][y]);
    }
    
    void load(string filename);
    
    sokoban *get_player(){
        return(&sokobans[0]);
    }
};


void level::load(string filename){
    ifstream myfile;
    myfile.open(filename);
    string content="";
    
    for(int i=0;myfile>>content;i++){
        for(int j=0;j<content.size();j++){
            add_obj(content[j], i, j);
        }
    }
    myfile.close();
};

void sokoban::move(int inp_x, int inp_y){
    //telepamy_tego_z_kim_sie_zamieniamy_do_nas
    //telepamy_nas_tam_gdzie_chcemy
    //cout<<"kto_ma_x_y("<<x+inp_x<<", "<<y+inp_y<<")\n";
    obj *objekt=(*lvl).kto_ma_x_y(x+inp_x, y+inp_y);
    
    if(objekt->thype()=="%"){
        //cout<<"matrix[0][0]"<<(*lvl).matrix[0][0]<<"\n";
        objekt->move(inp_x, inp_y);
    }
    
    objekt=(*lvl).kto_ma_x_y(x+inp_x, y+inp_y);
    
    if(objekt->thype()=="."){
        //cout<<"matrix[0][0]"<<(*lvl).matrix[0][0]<<"\n";
        (*lvl).matrix[x][y]=(objekt);
        (*lvl).matrix[x+inp_x][y+inp_y]=(this);
        x=x+inp_x;
        y=y+inp_y;
    }
    
}
void crate::move(int inp_x, int inp_y){
    //telepamy_tego_z_kim_sie_zamieniamy_do_nas
    //telepamy_nas_tam_gdzie_chcemy
    //cout<<"kto_ma_x_y("<<x+inp_x<<", "<<y+inp_y<<")\n";
    obj *objekt=(*lvl).kto_ma_x_y(x+inp_x, y+inp_y);
    
    if(objekt->thype()=="."){
        (*lvl).matrix[x][y]=(objekt);
        (*lvl).matrix[x+inp_x][y+inp_y]=(this);
        x=x+inp_x;
        y=y+inp_y;
        
        lvl->solve+=(lvl->overmatrix[x][y])-happy;
        happy=lvl->overmatrix[x][y];
        /*
        if((*lvl).overmatrix[x][y]==true){
            lvl->solve++;
        }*/
        
    }
    
}


int main(){
    level lvl;
    sokoban *player;
    
    lvl.load("lvl.txt");
    //lvl.load("simple.txt");
    player=(lvl.get_player());
    lvl.render();
    
    //obj *objekt=(lvl).kto_ma_x_y(4, 8);
    //cout<<objekt->thype()<<"\n";
    
    //cout<<"-----\n";
    char ch;
    while(true){
        cin>>ch;
        //player->move(0, -1);
        
        switch(ch){
            case 'w':
                player->move(-1, 0);
                break;
            case 'a':
                player->move(0, -1);
                break;
            case 's':
                player->move(1, 0);
                break;
            case 'd':
                player->move(0, 1);
                break; 
        }
        lvl.render();
    }
    
    /*
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
    */
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
