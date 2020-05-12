#include "../include/sokoban.h"


void sound_box::ps(string name){
    //if (!buffer.loadFromFile("../sound/score.wav")){
    if (buffer.loadFromFile("../sound/"+name+".wav")){
        //cout<<"SOUND?!?\n";
        sound.setBuffer(buffer);
        sound.setVolume(100.f);
        sound.play();
        
    }else{
        cout<<"MHM.... ERROR...\n";
    }
}
