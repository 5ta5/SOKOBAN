//#pragma once
#include "libs.h"

class obj;
class level;
class menu;

//VIRTUAL--------------------------------------------------------
class obj{
public:
    //sf::Texture texture;
    virtual void move(int inp_x, int inp_y)=0;
    virtual string thype()=0;
    virtual void self_draw(level *lvl, int x, int y)=0;
    //void display();
    virtual string texture_path()=0;
    //sf::Texture get_texture();
    
    
    void draw(level *lvl, int x, int y, string tp, float alpha=1, float angle=0);
};

class rigid:public obj{
public:
    level *lvl;
    int x=0;
    int y=0;
};


static inline const string tex_p="../textures/";
//REAL-----------------------------------------
class empty_space: public obj{
public:
    string thype(){return(" ");};
    string texture_path(){return(tex_p+"black.png");};
    void move(int inp_x, int inp_y){};
    void self_draw(level *lvl, int x, int y);
};

class empty_flor: public obj{
public:
    string thype(){return(".");};
    string texture_path(){return(tex_p+"floor.png");};
    void move(int inp_x, int inp_y){};
    void self_draw(level *lvl, int x, int y);
};

class wall: public obj{
public:
    string thype(){return("#");};
    string texture_path(){return(tex_p+"wall.png");};
    void move(int inp_x, int inp_y){};
    void self_draw(level *lvl, int x, int y);
};

class sokoban: public rigid{
public:
    int direction=0;
    int num_color=0;
    string thype(){return("@");};
    string texture_path(){
        char tmp='0'+num_color;
        return(tex_p+"sokoban["+(tmp)+"].png");
    };
    void move(int inp_x, int inp_y);
    void self_draw(level *lvl, int x, int y);
    int jump();
};

class crate: public rigid{
public:
    bool happy=false;
    string thype(){return("%");};
    string texture_path(){return(tex_p+"crate.png");};
    void move(int inp_x, int inp_y);
    void self_draw(level *lvl, int x, int y);
};


class game_agent{
public:
    std::string path = "../levels/ALL";
    //std::string path = "../levels/TEST";
    string cut(string in);
    void write(string txt="", int size=40, int x=0, int y=0, sf::Color col=sf::Color::White, bool bold=false);
    
    sf::RenderWindow *window;
    
};


class level: public ::game_agent{
private:
    int sizeee=20;
    
    int spawn_point_x=0;
    int spawn_point_y=0;
    
    string loaded_file_name;
    
    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point deltatime;
    
public:
    int moves=0;
    
    int nice_scale;
    
    sf::Vector2f plusoffset;//screan_size
    sf::Vector2f minusoffset;//lvl_size
    
    empty_space emp;
    empty_flor flo;
    
    wall walls[400];
    int walls_counter=0;
    //vector<wall> walls;
    sokoban sokobans[40];
    int sokobans_counter=0;
    //vector<sokoban> sokobans;
    //vector<crate> crates;
    crate crates[400];
    int crates_counter=0;
    
    int solve=0;
    
    obj *matrix[20][20];
    bool overmatrix[20][20];
    
    level(sf::RenderWindow *wind){
        window=wind;
        plusoffset=sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2);
        
        
        for(int i=0;i<sizeee;i++){
            for(int j=0;j<sizeee;j++){
                overmatrix[i][j]=false;
                matrix[i][j]=&emp;
            }
        }
    }
    void render();
    void draw();
    void win();
    
    void add_obj(string name, int x, int y, bool first_wall);
    void add_obj(char name, int x, int y, bool first_wall);
    
    void print_lvl_info();
    
    obj *kto_ma_x_y(int x, int y){
        return(matrix[x][y]);
    }
    
    void load(string filename);
    
    sokoban *spawn();
};


class vector3{
public:
    int x;
    int y;
    int z;
    vector3(int ix=0, int iy=0, int iz=0){
        x=ix;
        y=iy;
        z=iz;
    }
    
};
ostream & operator <<( ostream &, const vector3 &);


//int handle_keyboard(sokoban *player);
class input{
  public:
    
    bool wasd[5];//...global
    sf::Keyboard::Key binds[6];
    /*
    input(sf::Keyboard::Key bind[]){
        for(int i=0;i<6;i++){
            binds[i]=bind[i];
        }
    }*/
    
    virtual vector3 move()=0;
    
    void quit_check(level *lvl);
    void quit_check(menu *men);
    int handle_keyboard(sokoban *player);
    int handle_keyboard(menu *men);
    
};

class keyboard: public input{
public:
    vector3 move();
    
    keyboard(sf::Keyboard::Key bind[]){
        for(int i=0;i<6;i++){
            binds[i]=bind[i];
        }
    }
    
};


class menu: public ::game_agent{
public:
    //sf::RenderWindow *window;
    sf::Vector2f plusoffset;
    
    int selected=0;
    
    vector<string> options;
    
    menu(sf::RenderWindow *wind){
        window=wind;
        //plusoffset=sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/2);
        for (const auto & entry : fs::directory_iterator(path)){
            //std::cout << entry.path() << std::endl;
            options.push_back(entry.path());
        }
        
    }
    
    void up();
    void down();
    
    //void write(string txt="", int size=40, int x=0, int y=0, sf::Color col=sf::Color::White, bool bold=false);
    string cut(string in);
    int min(int a, int b);
    void draw();
    
    bool action(input *inp);    
};


class sound_box{
private:
    sf::SoundBuffer buffer;//WTF
    sf::Sound sound;
public:
    void ps(string name);//play_sound
    
};
