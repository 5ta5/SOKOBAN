#include "../include/sokoban.h"




void obj::draw(level *lvl, int x, int y, string tp, float alpha, float angle){
    sf::Sprite sprite;
    sf::Texture texture;
    //int scale=100;
    int scale=lvl->nice_scale;
    sprite.setScale(sf::Vector2f(0.01f*scale, 0.01f*scale));
    sprite.setColor(sf::Color(255, 255, 255, 255*alpha));
    
    sf::Transform transform;
    sf::Vector2f minusoffsettt(((lvl->minusoffset.y)*scale/2), ((lvl->minusoffset.x)*scale/2));
    transform.rotate(angle*90, sf::Vector2f(scale*y+(scale/2), scale*x+(scale/2))+lvl->plusoffset-minusoffsettt-sf::Vector2f(scale*(0.5), scale*(0.5)));
    
    sprite.setPosition(sf::Vector2f(scale*y, scale*x)+lvl->plusoffset-minusoffsettt-sf::Vector2f(scale*(0.5), scale*(0.5)));
    //sprite.setTexture(matrix[i][j]->get_texture());
    if (!texture.loadFromFile(tp))
    {
        // error...
        cout<<"ERROR\n";
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    lvl->window->draw(sprite, transform);
};

void sokoban::move(int inp_x, int inp_y){
    direction=(inp_x)+((inp_y-1)*(inp_y*inp_y));
    //cout<<"x: "<<(inp_x);
    //cout<<"direction: "<<direction<<"\n";//DEBUG
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

int sokoban::jump(){
    int odp=0;
    int inp_x=0;
    int inp_y=0;
    if(direction==1 || direction==-1){
        inp_x=direction;
    }else{
        inp_y=direction+1;
    }
    
    //obj *objekt;
    obj *objekt=(*lvl).kto_ma_x_y(x+inp_x, y+inp_y);
    while(objekt->thype()=="."){
        (*lvl).matrix[x][y]=(objekt);
        (*lvl).matrix[x+inp_x][y+inp_y]=(this);
        x=x+inp_x;
        y=y+inp_y;
        
        odp++;
        objekt=(*lvl).kto_ma_x_y(x+inp_x, y+inp_y);
    };
    return(odp);
}

sound_box sb;//mhm moze to lvl powinien miec swoj dzwienk?

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
        
        switch((lvl->overmatrix[x][y])-happy){
            case 1:
                sb.ps("score");
                //cout<<"score\n";//DEBUG
                break;
            case 0:
                sb.ps("crate_push");
                //cout<<"crate_push\n";//DEBUG
                break;
            case -1:
                sb.ps("un-score");
                //cout<<"un-score\n";//DEBUG
                break;
        }
        
        
        lvl->solve+=(lvl->overmatrix[x][y])-happy;
        happy=lvl->overmatrix[x][y];
    }
    
}




void empty_space::self_draw(level *lvl, int x, int y){draw(lvl, x, y, texture_path());};
void empty_flor::self_draw(level *lvl, int x, int y){
    draw(lvl, x, y, texture_path());
    if(lvl->overmatrix[x][y]==true){
        draw(lvl, x, y, tex_p+"point_field.png", 0.5);
    }
};
void wall::self_draw(level *lvl, int x, int y){draw(lvl, x, y, texture_path());};
void sokoban::self_draw(level *lvl, int x, int y){
    empty_flor ef;
    ef.self_draw(lvl, x, y);
    draw(lvl, x, y, texture_path(), 1, direction);
};
void crate::self_draw(level *lvl, int x, int y){
    empty_flor ef;
    ef.self_draw(lvl, x, y);
    draw(lvl, x, y, texture_path());
    if(happy==true){
        draw(lvl, x, y, tex_p+"okejka.png");
    }
};
