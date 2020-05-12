#include "../include/sokoban.h"


string game_agent::cut(string in){
    return(in.substr(path.size()+1+3, in.size()));
}

void game_agent::write(string txt, int size, int x, int y, sf::Color col, bool bold){
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
