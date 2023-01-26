#include "iGraphics.h"
#include<string>
#include<stdlib.h>

#define R 16
#define C 10

int block_x, block_y; //Coordinates of top left corner

int move_speed = 700; // Blocks move down slowly
int drop_speed = 1;   // Blocks drop fast if Arrow_Down is pressed

int boxes[R][C];      //For dropping boxes, all the values are 0, except one. which indicates a box
int permanentBoxes[R][C]; //For Blocks that are already dropped

int currenti,currentj, c1i, c1j, c2i, c2j, c3i, c3j; //Current row and column of the moving block

int shape=0; //block shape
int shapeNext; // next block
int state=0;  // State of rotation

int gameState=0; //For menu
int menuMusic=1; //Menu music on/off
int gameover=0;  //Game over tracker
int redLine=0;   // Height of red line

int score=0;     //Player score
int lvl=1;        // Player level
char scorestr[5]="00"; // For Storing score in a string
char lvlstr[5]="1";    // for Storing level in a string

//colors array of string for bmp file of different colors
char colors[7][25]= {"images\\purp_box.bmp", "images\\red_box.bmp","images\\or_box.bmp", "images\\green_box.bmp", "images\\yell_box.bmp", "images\\pink_box.bmp", "images\\cyan_box.bmp"};
char colors2[7][25]= {"images\\purp_box2.bmp", "images\\red_box2.bmp","images\\or_box2.bmp", "images\\green_box2.bmp", "images\\yell_box2.bmp", "images\\pink_box2.bmp", "images\\cyan_box2.bmp"};
char tutorial[3][25]={"images\\t1.bmp","images\\t2.bmp", "images\\t3.bmp"}; //Tutorial Pages

char rowFire3[10][25]={"images\\fr0.bmp","images\\fr1.bmp","images\\fr2.bmp","images\\fr3.bmp","images\\fr4.bmp","images\\fr5.bmp","images\\fr6.bmp","images\\fr7.bmp","images\\fr8.bmp",
                        "images\\fr9.bmp"}; // row vanish animation

                        //Bomb and blast animation images
char bomb[6][25]={"images\\bb1.bmp","images\\bb2.bmp","images\\bb3.bmp","images\\bb4.bmp","images\\bb5.bmp","images\\bb1.bmp"};
char blastbmp[9][25]={"images\\exp0.bmp","images\\exp1.bmp","images\\exp2.bmp","images\\exp3.bmp","images\\exp4.bmp","images\\exp5.bmp","images\\exp6.bmp","images\\exp7.bmp","images\\exp8.bmp"};

int tut=0; //tutorial page number

int fireI=0; // variables required for fire animation
int fireOver=0;
int fireY=0;
int cleanRow;

//Variables for bomb
int blast=0;
int blastI=0;
int blastx , blasty;
int bmbI=0;


int highscore=0; //storing highscore
char highscorestr[10]="00";


void createShapePlacer(int k) // Implementing the shape in boxes matrix
{
    boxes[currenti][currentj]=k;
    boxes[c1i][c1j]=k;
    boxes[c2i][c2j]=k;
    boxes[c3i][c3j]=k;
}

void createShape(int x) // Giving shape to a block
{
    if(shape==0)
    {
        c1i=currenti+1;
        c1j=currentj;

        c2i=currenti+1;
        c2j=currentj+1;

        c3i=currenti;
        c3j=currentj+1;

        createShapePlacer(x);

    }
    else if(shape==1)
    {
        if(state==0)
        {
             c1i=currenti;
            c1j=currentj+1;

            c2i=currenti;
            c2j=currentj+2;

            c3i=currenti;
            c3j=currentj+3;

            createShapePlacer(x);
        }
        else if(state==1)
        {
            c1i=currenti-1;
            c1j=currentj;

            c2i=currenti-2;
            c2j=currentj;

            c3i=currenti-3;
            c3j=currentj;

            createShapePlacer(x);
        }

    }
    else if(shape==2)
    {
        if(state==0)
        {
            c1i=currenti+1;
            c1j=currentj;

            c2i=currenti+2;
            c2j=currentj;

            c3i=currenti+2;
            c3j=currentj+1;

            createShapePlacer(x);
        }
        else if(state==1)
        {
            c1i=currenti;
            c1j=currentj+1;

            c2i=currenti;
            c2j=currentj+2;

            c3i=currenti-1;
            c3j=currentj+2;

            createShapePlacer(x);
        }
        else if(state==2)
        {
            c1i=currenti-1;
            c1j=currentj;

            c2i=currenti-2;
            c2j=currentj;

            c3i=currenti-2;
            c3j=currentj-1;

            createShapePlacer(x);
        }
        else if(state==3)
        {
            c1i=currenti+1;
            c1j=currentj;

            c2i=currenti;
            c2j=currentj+1;

            c3i=currenti;
            c3j=currentj+2;

            createShapePlacer(x);
        }
    }
    else if(shape==3)
    {
        if(state==0)
        {
            c1i=currenti;
            c1j=currentj+1;

            c2i=currenti;
            c2j=currentj+2;

            c3i=currenti+1;
            c3j=currentj+1;



            createShapePlacer(x);
        }
        else if(state==1)
        {
            c1i=currenti+1;
            c1j=currentj;

            c2i=currenti+2;
            c2j=currentj;

            c3i=currenti+1;
            c3j=currentj+1;

            createShapePlacer(x);
        }
        else if(state==2)
        {
              c1i=currenti;
            c1j=currentj+1;

            c2i=currenti;
            c2j=currentj+2;

            c3i=currenti-1;
            c3j=currentj+1;

            createShapePlacer(x);
        }
        else if(state==3)
        {
            c1i=currenti+1;
            c1j=currentj;

            c2i=currenti+2;
            c2j=currentj;

            c3i=currenti+1;
            c3j=currentj-1;


            createShapePlacer(x);
        }
    }
    else if(shape==4)
    {
        if(state==0)
        {
            c1i=currenti;
            c1j=currentj+1;

            c2i=currenti+1;
            c2j=currentj+1;

            c3i=currenti+1;
            c3j=currentj+2;


            createShapePlacer(x);
        }
        else if(state==1)
        {
            c1i=currenti+1;
            c1j=currentj;

            c2i=currenti+1;
            c2j=currentj-1;

            c3i=currenti+2;
            c3j=currentj-1;



            createShapePlacer(x);
        }

    }
    else if(shape==5)
    {
        if(state==0)
        {
            c1i=currenti;
            c1j=currentj-1;

            c2i=currenti+1;
            c2j=currentj-1;

            c3i=currenti+1;
            c3j=currentj-2;


            createShapePlacer(x);
        }
        else if(state==1)
        {
            c1i=currenti+1;
            c1j=currentj;

            c2i=currenti+1;
            c2j=currentj+1;

            c3i=currenti+2;
            c3j=currentj+1;



            createShapePlacer(x);
        }

    }
    else if(shape==6)
    {
        if(state==0)
        {
            c1i=currenti+1;
            c1j=currentj;

            c2i=currenti+2;
            c2j=currentj;

            c3i=currenti+2;
            c3j=currentj-1;



            createShapePlacer(x);
        }
        else if(state==1)
        {
            c1i=currenti;
            c1j=currentj+1;

            c2i=currenti;
            c2j=currentj+2;

            c3i=currenti+1;
            c3j=currentj+2;

            createShapePlacer(x);
        }
        else if(state==2)
        {
              c1i=currenti;
            c1j=currentj+1;

            c2i=currenti+1;
            c2j=currentj;

            c3i=currenti+2;
            c3j=currentj;

            createShapePlacer(x);
        }
        else if(state==3)
        {
            c1i=currenti-1;
            c1j=currentj;

            c2i=currenti;
            c2j=currentj+1;

            c3i=currenti;
            c3j=currentj+2;


            createShapePlacer(x);
        }
    }
    else if(shape==7)
    {
        c1i=currenti;
        c1j=currentj;

        c2i=currenti;
        c2j=currentj;

        c3i=currenti;
        c3j=currentj;


        createShapePlacer(x);
    }
}
void changeState() //changing rotation of blocks
{
    if(shape==0)
    {
      return;
    }
    else if(shape==1)
    {
        if(state==0)
        {
            if(permanentBoxes[currenti-1][currentj]==0 && permanentBoxes[currenti-2][currentj]==0 && permanentBoxes[currenti-3][currentj]==0
               && currenti>=3)
            {createShape(0);
                state=1;
                createShape(1);
            }
        }
        else
        {
            if(permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[currenti][currentj+2]==0 && permanentBoxes[currenti][currentj+3]==0 && currentj<7 )
            {createShape(0);
                state=0;
                createShape(1);
            }
        }
    }
    else if(shape==2)
    {
        if(state==0)
        {
            if(permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[currenti][currentj+2]==0 && permanentBoxes[currenti-1][currentj+2]==0
               && currenti>=1)
            {createShape(0);
                state=1;
                createShape(1);
            }
        }
        else if(state==1)
        {
            if(permanentBoxes[currenti-1][currentj]==0 && permanentBoxes[currenti-2][currentj]==0 && permanentBoxes[currenti-2][currentj-1]==0
               && currenti>=2 && currentj>=1)
            {createShape(0);
                state=2;
                createShape(1);
            }
        }
        else if(state==2)
        {
            if(permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[currenti][currentj+2]==0 && permanentBoxes[currenti][currentj+1]==0
               && currenti>=1)
            {createShape(0);
                state=3;
                createShape(1);
            }
        }
        else if(state==3)
        {
            if(permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[currenti+2][currentj]==0 && permanentBoxes[currenti+2][currentj+1]==0
               && currenti>=1)
            {createShape(0);
                state=0;
                createShape(1);
            }
        }
    }
    else if(shape==3)
    {
        if(state==0)
        {
            if(permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[currenti+2][currentj]==0 && permanentBoxes[currenti+1][currentj+1]==0
               && currenti>=1)
            {createShape(0);
                state=1;
                createShape(1);
            }
        }
        else if(state==1)
        {
            if(permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[currenti][currentj+2]==0 && permanentBoxes[currenti-1][currentj+1]==0
               && currenti>=1 && currentj>=1 && currentj<=9-2)
            {createShape(0);
                state=2;
                createShape(1);
            }
        }
        else if(state==2)
        {
            if(permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[currenti+2][currentj]==0 && permanentBoxes[currenti+1][currentj-1]==0
               && currenti>=1 && currentj>=1)
            {createShape(0);
                state=3;
                createShape(1);
            }
        }
        else if(state==3)
        {
            if(permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[currenti][currentj+2]==0 && permanentBoxes[currenti+1][currentj+1]==0
               && currenti>=1 && currentj<=9-2)
            {createShape(0);
                state=0;
                createShape(1);
            }
        }
    }
    else if(shape==4)
    {
        if(state==0)
        {
            if(permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[currenti+1][currentj-1]==0 && permanentBoxes[currenti+2][currentj-1]==0
               && currenti>=1 && currentj>=1 && currentj<=9-1)
            {createShape(0);
                state=1;
                createShape(1);
            }
        }
        else if(state==1)
        {
            if(permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[currenti+1][currentj+1]==0 && permanentBoxes[currenti+1][currentj+2]==0
               && currenti>=1 && currentj<=9-2)
            {createShape(0);
                state=0;
                createShape(1);
            }
        }

    }
    else if(shape==5)
    {
        if(state==0)
        {
            if(permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[currenti+1][currentj+1]==0 && permanentBoxes[currenti+2][currentj+1]==0
               && currenti>=1 &&  currentj<=9-1)
            {createShape(0);
                state=1;
                createShape(1);
            }
        }
        else if(state==1)
        {
            if(permanentBoxes[currenti][currentj-1]==0 && permanentBoxes[currenti+1][currentj-1]==0 && permanentBoxes[currenti+1][currentj-2]==0
               && currenti>=1 && currentj>=2)
            {createShape(0);
                state=0;
                createShape(1);
            }
        }

    }
    else if(shape==6) //left dev
    {
        if(state==0)
        {
            if(permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[currenti][currentj+2]==0 && permanentBoxes[currenti+1][currentj+2]==0
               && currenti>=1  && currentj<=7)
            {createShape(0);
                state=1;
                createShape(1);
            }
        }
        else if(state==1)
        {
            if(permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[currenti-2][currentj]==0
               && currenti>=1 && currentj<=9-1)
            {createShape(0);
                state=2;
                createShape(1);
            }
        }
        else if(state==2)
        {
            if(permanentBoxes[currenti-1][currentj]==0 && permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[currenti][currentj+2]==0
               && currenti>=1 && currentj<=9-2)
            {createShape(0);
                state=3;
                createShape(1);
            }
        }
        else if(state==3)
        {
            if(permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[currenti+2][currentj]==0 && permanentBoxes[currenti+2][currentj-1]==0
               && currenti>=1 && currentj>=1)
            {createShape(0);
                state=0;
                createShape(1);
            }
        }
    }
}

void dropColumns(int i) //for dropping columns after clearing rows
{
    for(int x=i; x>0; x--)
    {
        for(int j = 0; j<C ; j++)
        {

            permanentBoxes[x][j]=permanentBoxes[x-1][j];
            permanentBoxes[x-1][j]=0;

        }
    }

}
void checkRow() //for checking filled up rows
{
    int sum=0;

    for(int i=0; i<R ; i++)
    {
        sum=0;
        for(int j = 0; j<C ; j++)
        {
            if(permanentBoxes[i][j]>0)
            {
                sum++;
            }

        }

        if(sum==10)
        {
            fireOver=1;
            cleanRow=i;

            fireY=708-i*47;
            iResumeTimer(3);

            for(int x=0; x<C; x++)
            {
                permanentBoxes[i][x]=0;

            }
            dropColumns(cleanRow);


            PlaySound("sound\\row4.wav" , NULL ,  SND_ASYNC);
            score+=100;
            lvl=score/400+1;

            sprintf(lvlstr, "%d",lvl);

            sprintf(scorestr, "%d",score);

            redLine=lvl-1;

        }


    }
}
void changeFire() //splash animation for vanishing rows
{
    fireI++;
    if(fireI==10)
    {
        fireI=0;
        fireOver=0;

        iPauseTimer(3);
    }

}

void bombAnim() //Animating the burning bomb
{
    bmbI++;
    if(bmbI==5)
    {
        bmbI=0;
    }
}
void blastAnim()
{
    blastI++;

        if(blastI==8)
        {
            blastI=0;
            blast=0;
            iPauseTimer(5);
        }

}
void bombExplode() //animating explosion
{
    blast=1;
    PlaySound("sound\\blast2.wav",NULL,SND_ASYNC);
    iResumeTimer(5);

    if(currenti!=15)
    {   blastx=block_x-30;
        blasty=block_y-30;
        permanentBoxes[currenti+1][currentj]=0;

        if(currentj!=9)
        {
            permanentBoxes[currenti+1][currentj+1]=0;

        }
        if(currentj!=0)
        {
            permanentBoxes[currenti+1][currentj-1]=0;


        }

    }
    else
    {
        blastx=block_x-30;
        blasty=block_y;
    }
    if(currentj!=0)
    {
        permanentBoxes[currenti][currentj-1]=0;

    }
    if(currentj!=9)
    {
        permanentBoxes[currenti][currentj+1]=0;
    }
    if(currenti!=15)
    {
        if(currentj!=9)
        {

            for(int i=currenti+1; i>=2; i--)
            {
                permanentBoxes[i][currentj+1]=permanentBoxes[i-2][currentj+1];
            }
        }
        if(currentj!=0)
        {
            for(int i=currenti+1; i>=2; i--)
            {
                permanentBoxes[i][currentj-1]=permanentBoxes[i-2][currentj-1];
            }

        }
        for(int i=currenti+1; i>=2; i--)
        {
            permanentBoxes[i][currentj]=permanentBoxes[i-2][currentj];
        }
    }
    else
    {
        if(currentj!=9)
        {

            for(int i=currenti; i>=1; i--)
            {
                permanentBoxes[i][currentj+1]=permanentBoxes[i-1][currentj+1];
            }
        }
        if(currentj!=0)
        {
            for(int i=currenti; i>=1; i--)
            {
                permanentBoxes[i][currentj-1]=permanentBoxes[i-1][currentj-1];
            }

        }
        for(int i=currenti; i>=1; i--)
        {
            permanentBoxes[i][currentj]=permanentBoxes[i-1][currentj];
        }

    }
}
void place_Box(void) //searches The matrix boxes[r][c] and permanentBoxes for '1' value, places a block there
{

    for(int i=0; i<R ; i++)
    {
        for(int j = 0; j<C ; j++)
        {

            if(permanentBoxes[i][j]>0)
            {

                if(i<13)
                {
                    iShowBMP(43+j*46, 720-i*48, colors2[permanentBoxes[i][j]-1]);

                }

                else
                {
                    iShowBMP(43+j*46, 708-i*47, colors2[permanentBoxes[i][j]-1]);

                }
            }

            if (boxes[i][j]==1)
            {
                if(shape==7)
                {
                    if(currenti<13)
                    {
                        block_x = 43+j*46, block_y=720-i*48;
                        iShowBMP2(block_x, block_y, bomb[bmbI],0);

                    }
                    else
                    {
                        block_x = 43+j*46, block_y=708-i*47;
                        iShowBMP2(block_x, block_y, bomb[bmbI],0);
                    }

                }
                else
                {
                    if(currenti<13)
                    {
                        block_x = 43+j*46, block_y=720-i*48;
                        iShowBMP(block_x, block_y, colors[shape]);

                    }

                    else
                    {   block_x = 43+j*46, block_y=708-i*47;
                        iShowBMP(block_x, block_y, colors[shape]);

                    }
                }


            }

        }

    }

}

void gameOver() // pauses all timers, saves high score
{
    PlaySound("sound\\gOver.wav" , NULL ,  SND_ASYNC);

    iPauseTimer(0);
    iPauseTimer(1);
    iPauseTimer(2);



    if(highscore<score)
    {
        FILE* f=fopen("score.txt", "w");
        fprintf(f,"%d",score);
        fclose(f);
    }
    gameover=1;
}

void pause_Box() //makes a block permanent because it has reached bottom
{
    if(shape==7)
    {
        bombExplode();
    }
    else
    {
    permanentBoxes[currenti][currentj]=shape+1;
    permanentBoxes[c1i][c1j]=shape+1;
    permanentBoxes[c2i][c2j]=shape+1;
    permanentBoxes[c3i][c3j]=shape+1;

    PlaySound("sound\\drop.wav" , NULL ,  SND_ASYNC);

    if(currenti==redLine || c1i==redLine || c2i==redLine || c3i==redLine)
    {

        gameOver();
        return;
    }
    }


    int temp=shapeNext;

    shapeNext=rand() % 8;
    createShape(0);

    currenti=0;
    currentj=4;

    shape=temp;

    state=0;
    createShape(1);

    if(gameover!=1)
    iResumeTimer(0);

}

void upNext() //shows next block
{
    if(shapeNext==0)
    {
        iShowBMP(760 ,576, colors[shapeNext]);
        iShowBMP(760+46,576, colors[shapeNext]);
        iShowBMP(760 ,576+46, colors[shapeNext]);
        iShowBMP(760+46,576+46, colors[shapeNext]);

    }
    if(shapeNext==1)
    {
        iShowBMP(760 ,585, colors[shapeNext]);
        iShowBMP(760+46,585, colors[shapeNext]);
        iShowBMP(760 +46*2,585, colors[shapeNext]);
        iShowBMP(760+46*3,585, colors[shapeNext]);

    }
    if(shapeNext==2)
    {
        iShowBMP(760 ,576, colors[shapeNext]);
        iShowBMP(760+46,576, colors[shapeNext]);
        iShowBMP(760 +46*2,576, colors[shapeNext]);
        iShowBMP(760+46*2,576+46, colors[shapeNext]);

    }
    if(shapeNext==3)
    {
        iShowBMP(760 ,576, colors[shapeNext]);
        iShowBMP(760+46,576, colors[shapeNext]);
        iShowBMP(760 +46*2,576, colors[shapeNext]);
        iShowBMP(760+46,576+46, colors[shapeNext]);

    }
    if(shapeNext==4)
    {
        iShowBMP(760 ,558, colors[shapeNext]);
        iShowBMP(760,558+46, colors[shapeNext]);
        iShowBMP(760 +46,558+46, colors[shapeNext]);
        iShowBMP(760+46,558+46*2, colors[shapeNext]);

    }
    if(shapeNext==5)
    {
        iShowBMP(769 ,558,colors[shapeNext]);
        iShowBMP(769,558+46,colors[shapeNext]);
        iShowBMP(769 -46,558+46,colors[shapeNext]);
        iShowBMP(769-46,558+2*46, colors[shapeNext]);

    }
    if(shapeNext==6)
    {
        iShowBMP(760+46 ,556, colors[shapeNext]);
        iShowBMP(760+46,556+46, colors[shapeNext]);
        iShowBMP(760+46,556+46*2, colors[shapeNext]);
        iShowBMP(760,556, colors[shapeNext]);

    }
    if(shapeNext==7)
    {
        iShowBMP2(770 ,586, bomb[bmbI],0);

    }

}

int checkBottom() //Checking every condition if the block has reached final position
{
    if(currenti<15 && c1i<15 && c2i<15 && c3i<15 && permanentBoxes[currenti+1][currentj]==0 && permanentBoxes[c1i+1][c1j]==0 && permanentBoxes[c2i+1][c2j]==0
       && permanentBoxes[c3i+1][c3j]==0)
        return 1;
    else
        return 0;
}

void drop_box() // For dropping boxes 1 row at a time
{


    if(checkBottom()==1)
    {
        createShape(0);
        currenti+=1;
        createShape(1);
        if(shape==7 && currenti>=2)
        {
            PlaySound("sound\\bmbfuse2.wav", NULL, SND_ASYNC);

        }


    }
    else
    {
        iPauseTimer(0);
        iPauseTimer(1);


        pause_Box();

    }

}
void Move_LeftRight(int x) //for moving block left or right
{
    if(x==0)//left
    {
        if(currentj>0 && c1j>0 && c2j>0 && c3j>0 && permanentBoxes[currenti][currentj-1]==0 && permanentBoxes[c1i][c1j-1]==0 && permanentBoxes[c2i][c2j-1]==0 &&permanentBoxes[c3i][c3j-1]==0)
        {
            createShape(0);
            currentj--;
            createShape(1);
        }
    }
    if(x==1) //right
    {
        if(currentj<9 && c1j<9 && c2j<9 && c3j<9 && permanentBoxes[currenti][currentj+1]==0 && permanentBoxes[c1i][c1j+1]==0 && permanentBoxes[c2i][c2j+1]==0 &&permanentBoxes[c3i][c3j+1]==0)
        {
            createShape(0);
            currentj++;

            createShape(1);
        }
    }
}


void gameSart() // Starts the game
{
    PlaySound(0, NULL , 0);

    FILE* fp= fopen("score.txt","r");
    fscanf(fp , "%d" , &highscore); //Read highscore
    fclose(fp);

    sprintf(highscorestr, "%d", highscore);


    shape=rand() % 7;
    state=0;

    shapeNext=rand() %8;


    for(int i=0; i<R ; i++)
    {
        for(int j = 0; j<C ; j++)
        {
            boxes[i][j]=0;
            permanentBoxes[i][j]=0; //Set all values of matrices to 0
        }

    }
    score=0;

    sprintf(scorestr, "%d", score);

    currenti=0;
    currentj=4;

    createShape(1);
    gameover=0;
    lvl=0;
    redLine=0;

    iResumeTimer(0);


}

void iDraw()
{

    iClear();

    if(gameState==1) // game Playing
    {
        iShowBMP(0, 0, "images\\bg.bmp");
        if(redLine<10)
        iShowBMP(43, 760-redLine*47, "images\\redLine.bmp");
        else
        iShowBMP(43, 740-redLine*47, "images\\redLine.bmp");


        place_Box(); //placing the box in the screen, from the 2d arrays


        upNext(); // next shape

        iSetColor(0,0,0);
        iText(600,403, lvlstr, GLUT_BITMAP_TIMES_ROMAN_24); //LEVEL

        iText(767 ,378, scorestr, GLUT_BITMAP_TIMES_ROMAN_24); //SCORES
        iText(767, 229 , highscorestr,GLUT_BITMAP_TIMES_ROMAN_24);

        if(fireOver==1) //clearing row animation
        {
            iShowBMP2(43, fireY,rowFire3[fireI],0);
        }
        if(blast==1) //explode animation
        {
            iShowBMP2(blastx,blasty ,blastbmp[blastI],0);
        }


        if(gameover==1) // game over
        {
            iShowBMP(243, 432, "images\\bgOver.bmp");
            iText(565 ,455, scorestr, GLUT_BITMAP_TIMES_ROMAN_24); //SCORES
            iShowBMP(380, 332, "images\\returnMenu.bmp");

        }

    }
    else if(gameState==0) //Main Menu
    {
        iShowBMP(0, 0, "images\\menu.bmp");

        if(menuMusic==1)
            iShowBMP(693,15, "images\\soundOn.bmp");
        else
            iShowBMP(693,15, "images\\soundOff.bmp");
        iShowBMP2(900, 68, bomb[bmbI],0);


    }
    else if(gameState==2) //Tutorial
    {
        iShowBMP(0, 0, tutorial[tut]);
    }
    else if(gameState==3) // Credits
    {
        iShowBMP(0, 0, "images\\creds.bmp");
    }

}

void iMouse(int button, int state, int mx, int my) // For implementing mouse button clicks
{

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //Left button of  mouse clicked
    {
       //printf("%d %d\n", mx, my);

        if(gameState==0) //in the main menu
        {
            if(mx>=347 && my>=377 && mx <= 678 && my<= 475) //play button pressed
            {

                gameSart();
                gameState=1;
            }

            else if(mx>=347 && my>=254 && mx <= 678 && my<= 346)//Tutorial button
            {
                gameState=2;

            }
            else if(mx>=347 && my>=126 && mx <= 678 && my<= 220)//Credits button
            {
                gameState=3;

            }
            else if(mx>=805 && my>=14 && mx <= 1004 && my<= 63) //Exit button
            {
                exit(0);
            }
            else if(mx>=693 && my>=15 && mx <= 758 && my<= 60)//Music on/off
            {
                if(menuMusic==1)
                {
                    menuMusic=0;
                    PlaySound(0, NULL , 0);
                }
                else
                {
                    menuMusic=1;
                    PlaySound("sound\\menu.wav" , NULL , SND_LOOP | SND_ASYNC);
                }
            }
        }
        else if(gameState==1)//Inside the game
        {
            if(mx>=823 && my>=717 && mx <= 1004 && my<= 763)// Main menu pressed in the top right corner
            {

                gameOver();
                if(menuMusic==1)
                {
                    PlaySound("sound\\menu.wav" , NULL , SND_LOOP | SND_ASYNC);
                }
                gameState=0;
            }
            if(gameover==1)
            {
                if(mx>=380 && my>=332 && mx <= 680 && my<= 432) //Main menu pressed after game over
                {

                    if(menuMusic==1)
                    {
                        PlaySound("sound\\menu.wav" , NULL , SND_LOOP | SND_ASYNC);
                    }

                    gameover=0;
                    gameState=0;
                }
            }
        }
        else if(gameState==3) // in credits
        {
            if(mx>=258 && my>=24 && mx <= 617 && my<= 112) //back button pressed
            {
                gameState=0;
            }
        }
        else if(gameState==2)// tutorial
        {

            if(mx>=823 && my>=717 && mx <= 1004 && my<= 763)// Next button pressed
            {
                if(tut==2) //after last page, go back to main menu
                {
                    tut=0;
                    gameState=0;
                }
                else
                {
                    tut++;
                }

            }
        }

    }

}
void iMouseMove(int mx, int my)
{

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(key == 'q') //exit game
    {
        exit(0);
    }
    else if(key == ' ') // exit tutorial
    {
        if(gameState==2)
        {
            tut=0;
            gameState=0;
        }
    }

}




void iSpecialKeyboard(unsigned char key) //for moving blocks using arrow keys
{

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if(key == GLUT_KEY_DOWN && gameState==1) //drop box fast
    {

        iPauseTimer(0);

        if(gameover==0)
        {
            iResumeTimer(1);
            iResumeTimer(2);


        }

    }
    if(key == GLUT_KEY_UP && gameState==1) // Rotate block
    {
        changeState();

    }
    if(key == GLUT_KEY_LEFT ) //move left
    {
        if(gameState==1)
        {
             Move_LeftRight(0);
        }


        else if(gameState==2) // or go to p page of tutorial
        {
            if(tut==0)
            {

                gameState=0;
            }
            else
            {
                tut--;
            }

        }

    }
    if(key == GLUT_KEY_RIGHT ) // move right
    {
        if(gameState==1)
               Move_LeftRight(1);

        else if(gameState==2) // or go to next page of tutorial
        {
            if(tut==2)
            {
                tut=0;
                gameState=0;
            }
            else
            {
                tut++;
            }

        }
        else if(gameState==0) //start the game
        {
            gameSart();
                gameState=1;
        }

    }
}


int main()
{

    if(menuMusic==1)
    {
        PlaySound("sound\\menu.wav" , NULL , SND_LOOP | SND_ASYNC); //menu music

    }

    iSetTimer(move_speed, drop_box); //timer for dropping slowly
    iPauseTimer(0);
    iSetTimer(drop_speed, drop_box); //timer for dropping fast
    iPauseTimer(1);
    iSetTimer(1000, checkRow); //for checking filled up rows
    iPauseTimer(2);
    iSetTimer(30, changeFire); //for animating row clearing
    iPauseTimer(3);
    iSetTimer(100 , bombAnim); //for changing bomb animation
    iSetTimer(100, blastAnim); //blast animation
    iPauseTimer(5);

    iInitialize(1024,768, "BlockBuster!");

    return 0;
}
