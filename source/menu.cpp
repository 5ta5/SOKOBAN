#include "../include/sokoban.h"

void menu::up(){
    if(selected>0){
        selected--;
    }
}
void menu::down(){
    if(selected<options.size()-1){
        selected++;
    }
}
/*
void menu::write(string txt, int size, int x, int y, sf::Color col, bool bold){
    sf::Font font;
    font.loadFromFile("../fonts/NovaSquare-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    //text.setString("Hello world["+to_string(selected)+"]");
    text.setString(txt);
    text.setCharacterSize(size);
    text.setFillColor(col);
    if(bold==true){
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    }
    text.setPosition(sf::Vector2f(x, y));
    window->draw(text);
    
}
*/

int menu::min(int a, int b){
    if(a<b){
        return(a);
    }
    return(b);
}

void menu::draw(){
    window->clear();
    
    //write("SOKOBAN");
    game_agent::write("SOKOBAN", 140, 0, 0, sf::Color::Red, true);
    game_agent::write("(5ta5)", 80, 700, 20, sf::Color::Red, true);
    
    if(options.size()>0){
        game_agent::write(game_agent::cut(options[selected]), 60, 20, 200, sf::Color::White, true);
    }
    int gray=255;
    for(int i=selected+1;i<min(options.size(), selected+20);i++){
        gray-=min(gray, 20);
        game_agent::write(game_agent::cut(options[i]), 60, 20, 200+((i-selected)*60), sf::Color(gray, gray, gray), false);
    }
    
    
    sf::Sprite sprite;
    sf::Texture texture;
    sprite.setScale(sf::Vector2f(0.8, 0.8));
    sprite.setPosition(600, 100);
    
    if (!texture.loadFromFile("../textures/big_sokoban.png"))
    {
        // error...
        cout<<"ERROR\n";
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    window->draw(sprite);
    
    window->display();
}

bool menu::action(input *inp){
    if(inp->input::handle_keyboard(this)==1){
        return(false);
    }
    return(true);
}
