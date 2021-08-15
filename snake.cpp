#include<iostream>
#include<conio.h>
#include<windows.h>     // For Sleep() 
using namespace std;

bool gameover;
const int width = 20;
const int height = 20;
int x,y,fruitX,fruitY,score;
int tailX[100],tailY[100];
int ntail = 0;
enum direction {STOP=0, LEFT, RIGHT, UP, DOWN};
direction dir;

void setup(){
    
    gameover = false;
    dir = STOP;
    x = width/2;
    y = height/2; 
    fruitX = rand() % width;
    fruitY = rand() % width;
    score = 0;
}

void draw(){
    system("cls");

    for(int i=0;i<width+2;i++){
        cout<<"#";
    }
    cout<<endl;

    for(int i=0;i<height;i++){

        for(int j=0;j<width;j++){
            if(j==0){
                cout<<"#";
            }

            if(j==x && i==y){
                cout<<"O";
            }
            else if(j == fruitX && i == fruitY){
                cout<<"F";
            }
            else{
                int print = false;
                for(int k=0; k<ntail; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        cout<<"o";
                        print = true;
                    }
                }
                if(!print){
                    cout<<" ";
                }
            }

            if(j==(width-1)){
                cout<<"#";
            }
        }
        cout<<endl;
    }

    for(int i=0;i<width+2;i++){
        cout<<"#";
    }
    cout<<endl;

    cout<<"SCORE:"<<score<<endl;
    
}

void input(){

    if(_kbhit()){
        
        switch(_getch()){
            
            case 'a':
                dir=LEFT;
                break;
            case 'd':
                dir=RIGHT;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'w':
                dir=UP;
                break;
            case 'x':
                gameover = true;
                break;
        }

    }
}

void logic(){
    
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X,prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    
    for(int i=1;i<ntail;i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if(x<0 || x>width || y<0 || y>height){
        gameover = true;
    }

    // if(x>=width) x=0; else if(x<0) x=width-1;    // on hitting the right wall it's gonna comeout from left wall ans vice versa
    // if(y>=height) y=0; else if(y<0) x=height-1;  //// on hitting the upper wall it's gonna comeout from lower(down) wall and vice versa

    for(int i = 0; i<ntail; i++){
        if(tailX[i] == x && tailY[i] == y){
            gameover = true;
        } 
    }
    if(x == fruitX && y== fruitY){
        
        score+=10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        ntail++;
    }
}

int main(){

    setup();
    while(!gameover){
        draw();
        input();
        logic();
       // Sleep(20);  // To slow the speed of the snake
    }

    return 0;
}