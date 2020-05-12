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
    
    
    
    sf::Keyboard::Key wasd2[6];
    wasd2[0]=sf::Keyboard::Up;
    wasd2[1]=sf::Keyboard::Down;
    wasd2[2]=sf::Keyboard::Left;
    wasd2[3]=sf::Keyboard::Right;
    
    //wasd2[0]=sf::Keyboard::Key::W;
    //wasd2[1]=sf::Keyboard::Key::S;
    //wasd2[2]=sf::Keyboard::Key::A;
    //wasd2[3]=sf::Keyboard::Key::D;
    wasd2[4]=sf::Keyboard::Enter;
    wasd2[5]=sf::Keyboard::Key::M;
    keyboard inp2(wasd2);
    
    
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow window(desktop, "SOKOBAN", sf::Style::Fullscreen);//sf::VideoMode(1000, 1000)
    //window->setFramerateLimit(60);
    //window->setVerticalSyncEnabled(true);
    
    menu men(&window);
    while(men.window->isOpen() && men.action(&inp) && men.action(&inp2)){
        inp.quit_check(&men);
        men.draw();
    }
    
    
    level lvl(&window);//nom
    stack<level> backups;
    
    lvl.load(men.options[men.selected]);
    
    sokoban *player;
    player=lvl.spawn();

    sokoban *player2;
    player2=lvl.spawn();
    
    backups.push(lvl);
    
    char ch;
    int killer=0;
    while(lvl.window->isOpen() && killer<2){
        inp.quit_check(&lvl);
        
        
        int state2=inp2.handle_keyboard(player2);
        //int state=inp.handle_keyboard(player);
        
        int state=inp.handle_keyboard(player);
        if(state>0 || state2>0){
            //cout<<"NEW_STATE\n";//DEBUG
            lvl.moves+=state+state2;
            backups.push(lvl);
            if(lvl.solve==lvl.crates_counter){//temporary
                killer++; 
            }
            //cout<<"new state[ "<<lvl.crates_counter<<" ---> "<<lvl.solve<<" ]\n";
        }
        if((state==-1 || state2==-1) && backups.size()>1){
            //cout<<"BACK_STATE\n";//DEBUG
            backups.pop();
            lvl=backups.top();
        }
        
        //lvl.render();//cool
        lvl.draw();
    }
    
    
}


//sfml simple fast multimedia library
/*
 * . -pusty
 * # -sciana
 * @ -sokoban
 * $ -pole_fajne
 * % -skrzynka
 */
