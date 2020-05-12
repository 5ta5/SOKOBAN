#include "../include/sokoban.h"

void level::render(){
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

void level::draw(){
    window->clear();
    for(int i=0;i<sizeee;i++){
        for(int j=0;j<sizeee;j++){
            //cout<<matrix[i][j]<<"\n";//DEBUG
            matrix[i][j]->self_draw(this, i, j);
            //sokobans[0].self_draw(this, i, j);
        }
    }
    if(solve==crates_counter){
        win();
    }
    
    print_lvl_info();
    
    window->display();
}

void level::print_lvl_info(){
    game_agent::write("name: "+game_agent::cut(loaded_file_name), 40, 0, 0, sf::Color::White, true);
    
    deltatime=high_resolution_clock::now();
    duration<double, std::milli> time_span = deltatime - start_time;
    int a=floor(time_span.count()/1000);
    int b=a+1;
    float power=(time_span.count()/1000)-a;
    sf::Color ac=sf::Color(255, 255, 255, (1-power)*255);
    sf::Color bc=sf::Color(255, 255, 255, power*255);
    game_agent::write("time: "+std::to_string(a), 40, 0, 40, ac);
    game_agent::write("time: "+std::to_string(b), 40, 0, 40, bc);
    game_agent::write("moves: "+std::to_string(moves), 40, 0, 80, sf::Color::White);    
}


void level::load(string filename){
    ifstream myfile;
    myfile.open(filename);
    string content="";
    
    loaded_file_name=filename;
    
    int maxi=0;
    int maxj=0;
    bool first_wall;
    for(int i=0;std::getline(myfile, content);i++){//myfile>>content
        first_wall=false;
        for(int j=0;j<content.size();j++){
            if(content[j]=='#'){//... hardcode
                first_wall=true;
            }
            add_obj(content[j], i, j, first_wall);
            maxj=max(j, maxj);
        }
        //cout<<"\n";//DEBUG
        maxi=max(i, maxi);
    }
    nice_scale=2000/(max(maxi*2, maxj)+2);
    
    minusoffset=sf::Vector2f(maxi, maxj);
    
    myfile.close();
    
    start_time=high_resolution_clock::now();
    
};

void level::add_obj(string name, int x, int y, bool first_wall){
    if(name==" " || name=="."){
        if(first_wall==true){
            matrix[x][y]=&(flo);
        }
    }
    
    if(name=="." || name=="+" || name=="*"){
        overmatrix[x][y]=true;
    }
    if(name=="#"){
        //fix-me
        /*
        wall wall_tmp;
        walls.push_back(wall_tmp);
        cout<<walls.size()<<"\n";
        matrix[x][y]=&(walls[(walls.size()-1)]);
        */
        
        matrix[x][y]=&(walls[walls_counter]);
        walls_counter++;
        
    }
    if(name=="@" || name=="+"){
        /*
        matrix[x][y]=&(sokobans[sokobans_counter]);
        sokobans[sokobans_counter].lvl=this;//fix-me
        sokobans[sokobans_counter].x=x;
        sokobans[sokobans_counter].y=y;
        sokobans_counter++;
        */
        matrix[x][y]=&(flo);
        spawn_point_x=x;
        spawn_point_y=y;
    }
    if(name=="$" || name=="*"){
        matrix[x][y]=&(crates[crates_counter]);
        crates[crates_counter].lvl=this;
        crates[crates_counter].x=x;
        crates[crates_counter].y=y;
        if(name=="*"){
            solve++;
            crates[crates_counter].happy=true;
        }
        crates_counter++;
        /*
        cout<<"SPAWNING CRATE["<<crates_counter<<"]\n";
        crate tmp;
        tmp.lvl=this;
        tmp.x=x;
        tmp.y=y;
        crates.push_back(tmp);
        matrix[x][y]=&(crates[(crates.size()-1)]);
        crates_counter++;
        */
    }
    
    
}
void level::add_obj(char name, int x, int y, bool first_wall){
    string tmp="";
    tmp+=name;
    add_obj(tmp, x, y, first_wall);
}



void level::win(){
    srand (time(NULL));
    sf::Sprite sprite;
    sf::Texture texture;
    //x=1000;
    //y=1000;
    sprite.setScale(sf::Vector2f(2, 2));
    sprite.setColor(sf::Color(rand() % 256, rand() % 256, rand() % 256, 255));
    
    sprite.setPosition(plusoffset-sf::Vector2f(420, 300));
    if (!texture.loadFromFile(tex_p+"win.png"))
    {
        cout<<"ERROR\n";
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    window->draw(sprite);
    
    //cout<<"!!!YOU WIN!!!\n";
}


sokoban *level::spawn(){
    /*
     *   sokoban player;
     *   player.x=spawn_point_x;
     *   player.y=spawn_point_y;
     *   player.lvl=this;
     *   sokobans.push_back(player);
     *   matrix[spawn_point_x][spawn_point_y]=&(sokobans[sokobans.size()-1]);
     *   return(&(sokobans[sokobans.size()-1]));
     */
    sokoban player;
    player.x=spawn_point_x;
    player.y=spawn_point_y;
    player.lvl=this;
    player.num_color=sokobans_counter;
    sokobans[sokobans_counter]=player;
    
    sokobans_counter++;
    matrix[spawn_point_x][spawn_point_y]=&(sokobans[sokobans_counter-1]);
    
    //MOVE_spawn_point
    for(int i=1;i<4;i++){
        int off_x=(i%2)*(i%4-2);
        int off_y=((i+1)%2*((i-1)-2));
        if(matrix[spawn_point_x+off_x][spawn_point_y+off_y]==&(flo)){
            i+=100;
            spawn_point_x+=off_x;
            spawn_point_y+=off_y;
        }
    }
    
    return(&(sokobans[sokobans_counter-1]));
}
