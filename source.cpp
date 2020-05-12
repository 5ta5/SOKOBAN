#include "include/sokoban.h"

int main(){
    
    
    sf::Keyboard::Key wasd[6];
    wasd[0]=sf::Keyboard::Key::W;
    wasd[1]=sf::Keyboard::Key::S;
    wasd[2]=sf::Keyboard::Key::A;
    wasd[3]=sf::Keyboard::Key::D;
    wasd[4]=sf::Keyboard::Space;
    wasd[5]=sf::Keyboard::Key::Z;
    
    
    
    keyboard inp(wasd);
    
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow window(desktop, "SOKOBAN", sf::Style::Fullscreen);//sf::VideoMode(1000, 1000)
    //window->setFramerateLimit(60);
    //window->setVerticalSyncEnabled(true);
    
    
    
    menu men(&window);
    
    while(men.window->isOpen()){
        while(men.window->isOpen() && men.action(&inp)){
           inp.quit_check(&men);
            men.draw();
        }
    
    
        level lvl(&window);//nom
        stack<level> backups;
    
        lvl.load(men.options[men.selected]);
    
        sokoban *player;
        player=lvl.spawn();
    
    
        backups.push(lvl);
    
        char ch;
        int killer=0;
        while(lvl.window->isOpen() && killer<2){
            inp.quit_check(&lvl);
        
            int state=inp.handle_keyboard(player);
            if(state>0){
                //cout<<"NEW_STATE\n";//DEBUG
                lvl.moves+=state;
                backups.push(lvl);
                if(lvl.solve==lvl.crates_counter){//temporary
                    killer++; 
                }
            }
            if(state==-1 && backups.size()>1){
                //cout<<"BACK_STATE\n";//DEBUG
                backups.pop();
                lvl=backups.top();
            }
        
            //lvl.render();//cool
            lvl.draw();
        }
    }
    
}


//sfml simple fast multimedia library
/*
 . -pusty
 # -sciana
 @ -sokoban
 $ -pole_fajne
 % -skrzynka
 */
