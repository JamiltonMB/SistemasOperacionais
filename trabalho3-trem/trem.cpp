#include "trem.h"
#include <QtCore>

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}


Trem::Trem(int ID, int x, int y, int velocidade) {
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = velocidade;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x <290)
                x+=10;
            else if (x == 290 && y < 150)
                y+=10;
            else if (x > 20 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x <560)
                x+=10;
            else if (x == 560 && y < 150)
                y+=10;
            else if (x > 290 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (y == 30 && x <830)
                x+=10;
            else if (x == 830 && y < 150)
                y+=10;
            else if (x > 560 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x <430)
                x+=10;
            else if (x == 430 && y < 270)
                y+=10;
            else if (x > 160 && y == 270)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x <700)
                x+=10;
            else if (x == 700 && y < 270)
                y+=10;
            else if (x > 430 && y == 270)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}

void Trem::setVelocidade(int velocidade){
    this->velocidade = (100-velocidade);
}




