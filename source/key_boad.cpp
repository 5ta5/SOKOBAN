#include "../include/sokoban.h"

//LEVEL
void input::quit_check(level *lvl){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)){
        lvl->window->close();
    }
    sf::Event event;
    while (lvl->window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            lvl->window->close();
        }
    }
}

int input::handle_keyboard(sokoban *player){
    vector3 v=move();
    int odp=0;
    //HARD_CODE
    if (v.y>0){
        player->move(0, -1);
        odp=1;
    }
    if (v.y<0){
        player->move(0, 1);
        odp=1;
    }
    if (v.x>0){
        player->move(-1, 0);
        odp=1;
    }
    if (v.x<0){
        player->move(1, 0);
        odp=1;
    }
    if(v.z>0){
        odp=(player->jump());
    }
    if(v.z<0){
        odp=-1;
    }
    return(odp);
}


//MENU

void input::quit_check(menu *men){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)){
        men->window->close();
    }
    sf::Event event;
    while (men->window->pollEvent(event)){
        if (event.type == sf::Event::Closed){
            men->window->close();
        }
    }
}


int input::handle_keyboard(menu *men){
    int odp=0;
    vector3 v=move();
    //cout<<v<<"\n";
    //HARD_CODE
    if (v.y!=0 || v.z!=0){
        odp=1;
    }
    
    if (v.x>0){
        men->up();
    }
    if (v.x<0){
        men->down();
    }
    
    return(odp);
}
































ostream & operator <<( ostream & s, const vector3 & v )
{
    return s<<"["<< v.x <<", "<< v.y <<", "<<v.z<<"]";
}




vector3 keyboard::move(){
    int x=0;
    int y=0;
    int z=0;
    
    int odcisk_wektora=0;
    for(int i=0;i<3;i++){
        odcisk_wektora=0;
        if (sf::Keyboard::isKeyPressed(binds[i*2]))
        {
            if(wasd[i*2]==false){
                wasd[i*2]=true;
                odcisk_wektora++;
            }
        }else{
            wasd[i*2]=false;
        }
        if (sf::Keyboard::isKeyPressed(binds[(i*2)+1]))
        {
            if(wasd[(i*2)+1]==false){
                wasd[(i*2)+1]=true;
                odcisk_wektora--;
            }
        }else{
            wasd[(i*2)+1]=false;
        }
        if(i==0){
            x=odcisk_wektora;
        }
        if(i==1){
            y=odcisk_wektora;
        }
        if(i==2){
            z=odcisk_wektora;
        }
    }
    
    
    return(vector3(x, y, z));
}
