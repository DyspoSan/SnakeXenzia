#include <iostream>
#include<stdlib.h>
#include<conio.h>//required for kbhit()
#include<windows.h>//required for sleep()
#include<graphics.h>
// #include<winbgim.h>

using namespace std;

bool gameover; 
const int width = 30 ;
const int height = 20 ;
int x,y, fruitX, fruitY,score ;
//x,y variables for head
int tailX[100], tailY[100] ;
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN } ;
eDirection dir ;
//enum datatype to keep record of the direction
void Setup()
{
    gameover = false ;
    dir = STOP ;
    x = width/2 ;
    y = height/2 ;
    fruitX = rand() % width ;
    fruitY = rand() % height ;
    score = 0 ;
}
 
 void Draw()
 {
       
    system("cls");
    // clrscr() ;
    for(int i=0 ; i<width+4 ; i++)
        cout << "=" ;
    cout << endl ;

     for(int i=0 ; i<height ; i++)
     {
        for(int j=0 ; j<width ; j++)
        {
            if( j == 0 )
                cout << "||" ;
            if(i==y && j==x)
                cout << "O" ;
                //i compared to y and j to x bcoz i runs along the height and j runs along the width
            else if(i==fruitY && j == fruitX)
                    cout << "*" ;
                else
                {
                    bool print = false ;
                    for(int k=0 ; k<nTail ; k++)
                    {
                        
                        if(tailX[k] == j && tailY[k]== i)
                        {
                            cout << "o" ;
                            print = true ;
                        }
                    }
                   if(!print)
                             cout << " " ;
                }
                    
            
         if( j == width-1 )
                cout << "||" ;
        }
        cout << endl ;
     }

    for(int i=0 ; i<width+4 ; i++)
         cout << "=" ;
    cout << endl ;
 
    cout << "Score: " << score << endl ;
    cout << "Press X to exit the game " ;
 }

 void Input()
 {
     if(_kbhit())
     {
        switch(_getch())
        {
            
            case 'a' :
            dir = LEFT ;
            break ;

            case 'd' :
            dir = RIGHT ;
            break ;

            case 'w' :
            dir = UP ;
            break ;

            case 's' :
            dir = DOWN ;
            break ;

            case 'x' :
            gameover = true ;
            break;
        }
     }
 }

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y ; 
    tailX[0] = x ;
    tailY[0] = y ;
    // i from 1 bcoz 0th index already assigned to prevX
    for(int i =1 ; i<nTail ; i++)
    {
        prev2X = tailX[i] ;
        prev2Y = tailY[i] ;
        tailX[i] = prevX ;
        tailY[i] = prevY ;

        prevX = prev2X;
        prevY = prev2Y ;
    }
    switch (dir)
    {
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
    /*if (x > width || x < 0 || y > height || y < 0)
        gameover = true ; */
    //For ending the game at the wall
    if(x >= width)
    x=0 ;
    else if (x<0)
    x = width - 1 ;

    if(y >= height)
    y=0 ;
    else if (y<0)
    y = height - 1 ;

//check if head hits tail anywhere in the game
    for(int i=0 ; i<nTail ; i++)
    {
    if(tailX[i]==x && tailY[i]==y)
    gameover = true ;
    }
    if(x == fruitX && y == fruitY)
    {
        score += 10 ;
        fruitX = rand() % width ;
        fruitY = rand() % height ;
        nTail++ ;
    }

}

int main()
{
   //int page = 0;
   // Sleep(10000000);
    Setup();
    while (!gameover)
    {
        Draw();
       // setactivepage(page);
       // setvisualpage(1-page);
        Input();
        Logic();
      // page = 1 - page ;

        Sleep(05);
    }
    system("cls");
    cout << "                                              GAMEOVER BABY!!";
    Sleep(10000) ;

    return 0;
}