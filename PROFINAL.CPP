
//Header Files

#include<fstream.h>
#include<ctype.h>
#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<process.h>
#include<math.h>

//Global Declarations

const char iswater=247;
const char ishit='X';
const char isship='S';
const char ismiss='0';

struct point
{
 int x,y;
};

struct ship
{
 int size;
 char name[10];
 point loc[5];
 int state;
};

struct player
{
 char un[9],pw[5];
 int score;
};

struct PData
{ 
 player p;
 ship s[9];
 char board[15][15];
};

struct GameData
{
 PData p1,p2;
 int shipno;
 int boardsize;
 int turn;
}D;

struct scoredata
{
 char win_un[9],loss_un[9];
 int score;
};

//User Defined Functions Prototypes:

void about();
void adboard(int &);
void admin();
void adship(int &);
int attack(PData &);
int comattack();
void comsetpos();
int corchk(int,int);
void drawplboard(PData);
void drawplboard1(int);
int gameoverchk();
void gameplay(int,int);
void highscores();
void loadgamedata();
void loading();
void login();
void login(player &,player&,int);
void menu1();
int orichk(char);
void retrieve(int);
void save();
void savescores(scoredata);
void shipsunk(PData &);
void sortscores();
void sprite_ship_hide(int,int,char,char);
void sprite_ship_show(int,int,char,char);
void spritedummy(int,int,char);
void store(PData &);
int structcmp(player,player,player,player);
void theme();

//User Defined Functions

//Function that displays basic information about the game
void about()
{
 clrscr();
 theme();
 //Text
 setcolor(WHITE);
 settextstyle(3,HORIZ_DIR,2);
 circle(30,30,15);
 outtextxy(30,15,"i");
 outtextxy(50,15,"ABOUT:");
 line(50,42,120,42);//Underline
 setcolor(GREEN);
 outtextxy(30,66,"Battleship Is A Guessing Game For 2 Players.It Is Played on ");
 outtextxy(30,86,"Ruled Grids.It Is Popularly Known As Pencil and Paper Game ");
 outtextxy(30,106,"Which Dates From World War-1.We As A Team Have Tried ");
 outtextxy(30,126,"To Recreate The Game in C++ Using Our Knowledge Of The ");
 outtextxy(30,146,"Programming Language ");
 setcolor(YELLOW);
 outtextxy(40,168,"GAME PLAY:");
 line(38,194,155,194);//Underline
 setcolor(GREEN);
 outtextxy(30,194,"The Game Involves 2 Grids And A Few Ships.Each Player Is ");
 outtextxy(30,214,"Allotted A Grid Of The Shape Of A Square.They have To ");
 outtextxy(30,234,"Place Their Ships Strategically On The Grid Which Is");
 outtextxy(30,254,"Concealed From The Opponent.Then Players Alternate Turns ");
 outtextxy(30,274,"Calling\"Shots\" At The Other Player's Ships.The Objective Of");
 outtextxy(30,294,"The Game Is To Destroy The Opposing Player's Fleet.");
 outtextxy(30,314,"Whoever Destroys The Opponent's Fleet First Is Declared ");
 outtextxy(30,334,"THE WINNER!!");
 if(getch()=='a')
  login();
 else
  menu1();
}

//Function to change the board size 
void adboard(int &n)
{
 int size;char disp[2];disp[1]='\0';
 do
 {
  cleardevice();
  theme();
  settextstyle(1,HORIZ_DIR,2);
  setcolor(GREEN);
  outtextxy(232,100,"Currrent board size : ");
  disp[0]=n+48;
  outtextxy(460,100,disp);
  setcolor(YELLOW);
  outtextxy(40,140,"Enter new board size (min-5,max-9) : ");
  size=getch();
  disp[0]=size;
  outtextxy(460,140,disp);
  size=size-48;
 }while(size<5||size>9);
 getch();
 n=size;
 admin();
}

void admin()
{
 char list[3][100]={"Change number of Ships","Change board Size","Return"};
 int mc=0,i,j=0;
 while(mc!=3)
 {
  cleardevice();
  theme();
  setlinestyle(0,0,1);
  settextstyle(0,HORIZ_DIR,5);
  setcolor(RED);
  outtextxy(100,20,"BATTLE SHIP");
  settextstyle(1,HORIZ_DIR,3);
  setcolor(GREEN);
  for(i=0;i<3;++i)
  {
   if(i==0||i==2)
    settextstyle(1,HORIZ_DIR,1);
   else
    settextstyle(1,0,0);
   outtextxy(110,120+50*(i),list[(i+mc+2)%3]);
  }
  setcolor(YELLOW);
  rectangle(100,120+(50*1),520,220);
  char c=getch();
  if(c==13)
   mc=3;
  else if(c=='P')
   (mc<2)?(mc++,++j):(mc=0,j=0);
  else if(c=='H')
   (mc>0)?(mc--,j--):(mc=2,j=2);
 }
 if(j==0)
  adship(D.shipno);
 else if (j==1)
  adboard(D.boardsize);
 else if(j==2)
  menu1();
}

//Function to change number of ships
void adship(int &n)
{
 char disp[2];disp[1]='\0';
 int size;
 do
 { 
  cleardevice();
  theme();
  setcolor(GREEN);
  settextstyle(1,HORIZ_DIR,2);
  outtextxy(255,100,"Currrent no of ships : ");
  disp[0]=n+48;
  outtextxy(480,100,disp);
  setcolor(YELLOW);
  outtextxy(45,140,"Enter new no: of ships (min-5,max-8) : ");
  size=getch();
  disp[0]=size;
  outtextxy(480,140,disp);
  size=size-48;
 }while(size<5||size>8);
 getch();
 n=size;
 admin();
}

//Function to implement player attacks
int attack(PData &T)
{
 int t3,invalid_ip,tw,t1,t2;
 char ch,base[2],col,row;
 base[1]='\0';
 cleardevice();
 drawplboard1(D.turn);
 do
 {
  setviewport(30,350,600,450,0);
  clearviewport();
  setviewport(0,0,getmaxx(),getmaxy(),0);
  t3=0; invalid_ip=0;
  settextstyle(0,HORIZ_DIR,0);
  outtextxy(40,360,"Enter the position to attack(Eg: A2) : ");
  tw=textwidth("Enter the position to attack(Eg: A2) : ");
  ch=getch();
  if(ch==27)
  {  
   outtextxy(40,380,"Do you want to save your game? ");
   char choice=getch();
   base[0]=choice;
   outtextxy(40+textwidth("Do you want to save your game? "),380,base);
   if(choice=='Y'||choice=='y')
   { 
    outtextxy(40,400,"Game Saved! Quitting..");
	getch();
	save(); 
   }
   else
   { 
    outtextxy(40,400,"Game Not Saved! Quitting..");
	getch();
	menu1(); 
   }
  }
  else if(ch>=65 && ch<=64+D.boardsize || ch>=97 && ch<=96+D.boardsize)
  {  
   base[0]=ch;
   outtextxy(40+tw,360,base);
   col=getch();
   base[0]=col;
   outtextxy(50+tw,360,base);
   col=col-48;
   t2=toupper(ch);
   row=t2-65;
   col--;
   t1=corchk(row,col);
   if(T.board[row][col]!=iswater && T.board[row][col]!=isship)
    t3=1;
  }
  else invalid_ip=1;
 }while(t1==0||t3==1||invalid_ip==1);

 if(T.board[row][col]==isship)
 {
  if(D.turn==0 || D.turn==1)
   D.p1.p.score+=50;
  else if( strcmp(D.p2.p.un,"A.I")!=0)
   D.p2.p.score+=50;
  T.board[row][col]=ishit;
  outtextxy(40,370,"You hit!! ");
  shipsunk(T);
  getch();
  return 1;
 }
 else
 {
  if(D.turn==0 || D.turn==1)
   D.p1.p.score-=5;
  else if( strcmp(D.p2.p.un,"A.I")!=0)
   D.p2.p.score-=5;
  T.board[row][col]=ismiss;
  outtextxy(40,370,"You missed !! ");
  getch();
  return 0;
 }
}

//Function to implement computer attacks
int comattack()
{
 int t3,col1,row1;
 cleardevice();
 drawplboard1(0);
 do
 {
  t3=0;
  row1=random(D.boardsize);
  col1=random(D.boardsize);
  if(D.p1.board[row1][col1]!=iswater && D.p1.board[row1][col1]!=isship)
   t3=1;
 }while(t3==1);
 outtextxy(40,380,"Computer is thinking...");
 delay(400);
 if(D.p1.board[row1][col1]==isship)
 {
  D.p1.board[row1][col1]=ishit;
  outtextxy(40,390,"Computer hits!!");
  shipsunk(D.p1);
  getch(); return 1;
 }
 else
 {
  D.p1.board[row1][col1]=ismiss;
  outtextxy(40,390,"Computer Misses!!");
  getch();return 0;
 }
}

//Function to set computer's ships
void comsetpos()
{
 int j,row,col,t,flag,k;
 char ori;
 randomize();
 for(int i=0;i<D.shipno;i++)
 {
  do
  {
   t=random(2);
   if(t==1)
    ori='h';
   else
    ori='v';
   row=random(D.boardsize);
   col=random(D.boardsize);
   flag=0;
   for(j=0;j<D.p2.s[i].size;j++)
    if(ori=='h'&& (col+j>=D.boardsize||D.p2.board[row][col+j]==isship))
    {
     flag++;
     break;
    }
    else if(row+j>=D.boardsize||D.p2.board[row+j][col]==isship)
    {
     flag++;
     break;
    }
  }while(flag!=0);

  k=0;
  for(j=0;j<D.p2.s[i].size;j++)
   if(ori=='h')
   {
    D.p2.board[row][col+j]=isship;
    D.p2.s[i].loc[j].x=row;
    D.p2.s[i].loc[j].y=col+j;
    k++;
   }
   else
   {
    D.p2.board[row+j][col]=isship;
    D.p2.s[i].loc[j].x=row+j;
    D.p2.s[i].loc[j].y=col;
    k++;
   }
 }
}

//Function to check if co-ordinate enetered is valid 
int corchk(int a,int b)
{
 int i=0,flagr=0,flagc=0;
 for(i=0;i<D.boardsize;i++)
  if(b==i)
  {
   flagc++;
   break;
  }
 for(i=0;i<D.boardsize;i++)
  if(a==i)
  {
   flagr++;
   break; 
  }
 if(flagc==1&&flagr==1)
  return 1;
 return 0;
}

//Function which displays player's grid to store ships
void drawplboard(PData T)
{
 char no[3],le[2];
 le[1]=no[2]='\0';
 int i,j;
 cleardevice();
 setcolor(WHITE);
 settextstyle(0,HORIZ_DIR,2);
 outtextxy(200,20,T.p.un);
 outtextxy(200+textwidth(T.p.un),20,"'s Board ");
 line(200,40,420,40);
 settextstyle(0,HORIZ_DIR,1);
 //Loop to print the row number
 for(i=-1;i<D.boardsize-1;++i)
 {
  if(i<8)
  {
   no[0]='0';
   no[1]=50+i;
  }
  else
  {
   no[0]='1';
   no[1]=49+i-9;
  }
  outtextxy(255+25*i,55,no);
 }
 //Loop to print the column letters
 for(i=0;i<D.boardsize;++i)
 {
  le[0]=65+i;
  outtextxy(210,75+25*i,le);
 }
 setcolor(GREEN);
 rectangle(10,10,630,470);
 //Board Boxes
 for(i=0;i<D.boardsize-1;++i)
  for(j=0;j<D.boardsize-1;++j)
   rectangle(225+25*j,65+25*i,275+25*j,115+25*i);
 //Sprite placement
 for(i=0;i<D.boardsize;++i)
  for(j=0;j<D.boardsize;++j)
   spritedummy(i,j,T.board[i][j]);
 //Rectangle for the text menu
 setfillstyle(SOLID_FILL,BLACK);
 setlinestyle(SOLID_LINE,WHITE,3);
 setcolor(WHITE);
 int p[10]={30,300,600,300,600,450,30,450,30,300};
 fillpoly(5,p);
 setlinestyle(SOLID_LINE,GREEN,1);
}

//Function to display players' grids during attacks
void drawplboard1(int mode)
{
 char no[3],le[2];
 le[1]=no[2]='\0';
 int i,j;
 cleardevice();
 setcolor(WHITE);
 setlinestyle(0,0,1);
 settextstyle(0,HORIZ_DIR,2);
 if(mode==1)
 { 
  settextstyle(0,HORIZ_DIR,2);
  outtextxy(200,30,D.p1.p.un);
  outtextxy(200+textwidth(D.p1.p.un),30,"'s Turn ");
  line(198,50,430,50);
 }
 else if(mode==2)
 { 
  settextstyle(0,HORIZ_DIR,2);
  outtextxy(200,30,D.p2.p.un);
  outtextxy(200+textwidth(D.p2.p.un),30,"'s Turn ");
  line(198,50,430,50);
 }
 outtextxy(30,70,D.p1.p.un);
 outtextxy(30+textwidth(D.p1.p.un),70,"'s Board");
 outtextxy(330,70,D.p2.p.un);
 outtextxy(330+textwidth(D.p2.p.un),70,"'s Board");
 line(30,90,250,90);
 line(330,90,565,90);
 settextstyle(0,HORIZ_DIR,1);
 //Loop to print the column letters
 for(i=0;i<D.boardsize;++i)
 {
  le[0]=65+i;
  outtextxy((25*D.boardsize+325)/2+5,135+25*i,le);
 }
 //Loop to print the row number
 //Player 1 Board
 for(i=0;i<D.boardsize;++i)
 {
  if(i<8)
  {
   no[0]='0';
   no[1]=49+i;
  }
  else
  {
   no[0]='1';
   no[1]=49+i-9;
  }
  outtextxy(30+25*i,110,no);
 }
 //Player 2 / Computer Board
 for(i=0;i<D.boardsize;++i)
 {
  if(i<8)
  {
   no[0]='0';
   no[1]=49+i;
  }
  else
  {
   no[0]='1';
   no[1]=49+i-9;
  }
  outtextxy(330+25*i,110,no);
 }
 //Game board
 setcolor(GREEN);
 rectangle(10,10,630,470);
 for(i=0;i<D.boardsize-1;++i)
  for(j=0;j<D.boardsize-1;++j)
   rectangle(25+25*j,125+25*i,75+25*j,175+25*i);
 
 for(i=0;i<D.boardsize-1;++i)
  for(j=0;j<D.boardsize-1;++j)
   rectangle(325+25*j,125+25*i,375+25*j,175+25*i);

 for(i=0;i<D.boardsize;++i)
  for(j=0;j<D.boardsize;++j)
  {
   if(strcmpi(D.p2.p.un,"A.I")==0)
    sprite_ship_show(i,j,D.p1.board[i][j],'p');
   else
    sprite_ship_hide(i,j,D.p1.board[i][j],'p');
   sprite_ship_hide(i,j,D.p2.board[i][j],'c');
  }

 //Rectangle for the text menu
 setfillstyle(SOLID_FILL,BLACK);
 setlinestyle(SOLID_LINE,WHITE,3);
 setcolor(WHITE);
 int p[10]={30,350,600,350,600,450,30,450,30,350};
 fillpoly(5,p);
}

//Function to check if game has finished
int gameoverchk()
{
 int flag=0,flag1=0;
 for(int i=0;i<D.shipno;i++)
 {
  if(D.p1.s[i].state==1)
   flag++;
  if(D.p2.s[i].state==1)
   flag1++;
 }
 if(flag1==D.shipno)
 {
  outtextxy(40,430,D.p1.p.un);
  outtextxy(40+textwidth(D.p1.p.un),430," wins ! ");
  return 1;
 }
 else if(flag==D.shipno)
 {
  outtextxy(40,430,D.p2.p.un);
  outtextxy(40+textwidth(D.p2.p.un),430," wins ! ");
  return 2;
 }
 return 0;
}

void gameplay(int gamemode ,int savestate)
{
 if(D.boardsize==5 && D.shipno==8)
  D.boardsize=6;
 int event,event1;
 if(savestate==0)
 {  
  loadgamedata(); 
  D.p1.p.score=D.p2.p.score=0; 
 }
 if(gamemode==1)
 {
  if(savestate==0)
  { 
   store(D.p1);
   comsetpos(); 
  }
  do
  {
   do
   {
    event=attack(D.p2);
   }while(event==1 && gameoverchk()==0);
   if(gameoverchk()!=0)
	break;
   do
   {
    event1=comattack();
   }while(event1==1 && gameoverchk()==0);
  }while(gameoverchk()==0);
 }
 else
 {
  if(savestate==0)
  { 
   store(D.p1);
   store(D.p2); 
  }
  do
  {
   if(D.turn==1)
   { 
    do
	{
     event=attack(D.p2);
    }while(event==1 && gameoverchk()==0);
    if(gameoverchk()!=0)
	 break;
    D.turn=2;   
   }
   if(D.turn==2)
   { 
    do
	{
     event1=attack(D.p1);
    }while(event1==1 && gameoverchk()==0);
    if(gameoverchk()!=0)
	 break;
	D.turn=1; 
   }
  }while(gameoverchk()==0);
 }
 getch();
 scoredata s;
 if(gameoverchk()==1)
 {
  strcpy(s.win_un,D.p1.p.un);
  strcpy(s.loss_un,D.p2.p.un);
  s.score=D.p1.p.score;
 }
 else if(strcmp(D.p2.p.un,"A.I")!=0)
 {
  strcpy(s.win_un,D.p2.p.un);
  strcpy(s.loss_un,D.p1.p.un);
  s.score=D.p2.p.score;
 }
 savescores(s);
 highscores();
}

//Function to display highscores
void highscores()
{
 scoredata t;
 cleardevice();
 theme();int i=0,totpage,curpage=1;
 char page[10];
 char score[10];
 setcolor(WHITE);
 settextstyle(0,HORIZ_DIR,4);
 outtextxy(150,50,"HIGH SCORES");
 outtextxy(150,80,"-----------");
 settextstyle(0,HORIZ_DIR,2);
 setcolor(GREEN);
 outtextxy(100,150,"NAME");
 outtextxy(250,150,"OPPONENT");
 outtextxy(440,150,"SCORE");
 outtextxy(100,170,"----");
 outtextxy(250,170,"--------");
 outtextxy(440,170,"-----");
 settextstyle(1,HORIZ_DIR,2);
 ifstream fin("scores.dat",ios::binary);
 fin.seekg(0,ios::end);
 totpage=fin.tellg()/sizeof(scoredata);
 totpage=ceil(totpage/9.0);
 fin.seekg(0,ios::beg);
 while(fin.read((char*)&t,sizeof(t)))
 {
  settextstyle(0,HORIZ_DIR,1);
  outtextxy(530,445,"Page ");
  itoa(curpage,page,10);
  outtextxy(566,445,page);
  outtextxy(570,445," Of ");
  itoa(totpage,page,10);
  outtextxy(600,445,page);
  settextstyle(1,HORIZ_DIR,2);
  if(i==0 && curpage==1)
   setcolor(YELLOW);
  else if(i==1 && curpage==1)
   setcolor(LIGHTGRAY);
  else if(i==2 && curpage==1)
   setcolor(BROWN);
  else
   setcolor(WHITE);
  itoa(t.score,score,10);
  outtextxy(100,200+30*i,t.win_un);
  outtextxy(270,200+30*i,t.loss_un);
  outtextxy(460,200+30*i,score);
  i++;
  if(i%9==0 && totpage!=1)
  { 
   getch();
   setviewport(150,200,605,460,0);
   clearviewport();
   setviewport(0,0,0,0,0);
   i=0;curpage++;
  }
 }
 getch();
 i=0;
 menu1();
}
//Function which loads ship data and resets all board & ship data
void loadgamedata()
{
 strcpy(D.p1.s[0].name,"Cruiser");   D.p1.s[0].size= 2;
 strcpy(D.p1.s[1].name,"Submarine"); D.p1.s[1].size = 2;
 strcpy(D.p1.s[2].name,"Frigate");   D.p1.s[2].size = 3;
 strcpy(D.p1.s[3].name,"Escort");    D.p1.s[3].size = 4;
 strcpy(D.p1.s[4].name,"Destroyer"); D.p1.s[4].size = 5;
 strcpy(D.p1.s[5].name,"Anhilator"); D.p1.s[5].size=3;
 strcpy(D.p1.s[6].name,"Booster");   D.p1.s[6].size=2;
 strcpy(D.p1.s[7].name,"Necromancer");D.p1.s[7].size=4;

 strcpy(D.p2.s[0].name,"Cruiser");   D.p2.s[0].size= 2;
 strcpy(D.p2.s[1].name,"Submarine"); D.p2.s[1].size = 2;
 strcpy(D.p2.s[2].name,"Frigate");   D.p2.s[2].size = 3;
 strcpy(D.p2.s[3].name,"Escort");    D.p2.s[3].size = 4;
 strcpy(D.p2.s[4].name,"Destroyer"); D.p2.s[4].size = 5;
 strcpy(D.p2.s[5].name,"Anhilator"); D.p2.s[5].size=3;
 strcpy(D.p2.s[6].name,"Booster");   D.p2.s[6].size=2;
 strcpy(D.p2.s[7].name,"Necromancer");D.p2.s[7].size=4;

 for(int i=0;i<D.boardsize;i++)
  for(int j=0;j<D.boardsize;j++)
   D.p1.board[i][j]=iswater;

 for(i=0;i<D.boardsize;i++)
  for(j=0;j<D.boardsize;j++)
   D.p2.board[i][j]=iswater;

 for(i=0;i<D.shipno;i++)
 {
  D.p1.s[i].state=0;
  D.p2.s[i].state=0;
 }
}

//Function for Loading Screen 
void loading()
{
 D.boardsize=8;D.shipno=5;
 theme();
 //Ship
 int poly[12]={106,256,200,256,226,189,154,145,85,183,106,256},
 top1[12]={205,175,193,127,117,127,101,174,154,145,205,175},
 top2[10]={183,127,176,100,132,100,125,127,183,127},
 can1[10]={114,137,73,122,65,140,107,157,114,137},
 can2[10]={196,139,234,125,241,141,202,160,196,139};
 setcolor(15);
 setlinestyle(SOLID_LINE,0,3);
 setfillstyle(SOLID_FILL,DARKGRAY);
 fillpoly(6,poly);
 setfillstyle(SOLID_FILL,LIGHTGRAY);
 fillpoly(6,top1);
 setfillstyle(SOLID_FILL,DARKGRAY);
 fillpoly(5,top2);
 fillpoly(5,can1);
 setfillstyle(SOLID_FILL,DARKGRAY);
 fillpoly(5,can2);
 setfillstyle(SOLID_FILL,LIGHTGRAY);
 bar(139,99,144,66);
 bar(154,68,150,99);
 setcolor(BLUE);
 settextstyle(0,HORIZ_DIR,4);
 outtextxy(80,260,"~~~~~");
 //rocket and fire
 int body[10]={484,86,523,144,497,159,460,105,484,86},
 head[8]={484,86,454,67,461,104,484,86},
 fire[16]={500,159,500,183,514,164,541,173,530,156,558,156,525,145,500,159},
 bomb[24]={320,235,267,128,321,183,287,101,347,177,347,91,370,165,399,100,393,180,428,130,406,235,320,235};
 setcolor(RED);
 setfillstyle(SOLID_FILL,RED);
 fillpoly(4,head);
 setcolor(DARKGRAY);
 setfillstyle(SOLID_FILL,LIGHTGRAY);
 fillpoly(5,body);
 setcolor(RED);
 setfillstyle(1,YELLOW);
 fillpoly(8,fire);
 fillpoly(12,bomb);
 settextstyle(0,HORIZ_DIR,4);
 setcolor(BLUE);
 outtextxy(275,240,"~~~~~~");
 //loading bar
 setcolor(RED);
 settextstyle(7,HORIZ_DIR,3);
 outtextxy(350,340,"Loading . . .");
 setcolor(WHITE);
 rectangle(99,379,541,401);
 setfillstyle(1,RED);
 for(int i=0;i<=88;++i)
 {
  delay(50);
  bar(100,380,100+i*5,400);
 }
 menu1();
}

//Admin Login Function
void login()
{
 int i,p,b[10]={190,180,480,180,480,260,190,260,190,180};
 char un[8],pw[5],t[2];
 do
 {
  p=0;
  cleardevice();
  theme();
  setcolor(BLUE);
  t[1]='\0';
  settextstyle(1,HORIZ_DIR,5);
  setcolor(RED);
  outtextxy(190,100,"ADMIN LOGIN");
  setcolor(BLUE);
  settextstyle(11,HORIZ_DIR,2);
  setfillstyle(1,LIGHTGRAY);
  fillpoly(5,b);
  rectangle(357,190,450,205);
  outtextxy(200,195,"User Name (8 chars):");
  outtextxy(200,240,"Password(5 chars)  :");
  rectangle(357,235,450,250);
  for(i=0;i<8;++i)
  {
   un[i]=getch();
   t[0]=un[i];
   if(un[i]!=13)
    outtextxy(360+i*10,195,t);
   else
    break;
  }
  un[i]='\0';
  setcolor(GREEN);
  outtextxy(200,195,"User Name (8 chars):");
  setcolor(BLUE);
  for(i=0;i<5;++i)
  {
   pw[i]=getch();
   if(pw[i]!=13)
    outtextxy(380+i*10,240,"*");
   else
    break;
  }
  pw[i]='\0';
  setcolor(GREEN);
  outtextxy(200,240,"Password(5 chars)  :");
  settextstyle(0,HORIZ_DIR,3);
  if(strcmp("admin",pw)==0 && strcmp("bttlship",un)==0)
  {
   setcolor(GREEN);
   outtextxy(130,340," WELCOME ADMIN ! ");
   p=1;
   getch();
   admin();
  }
  else
  {
   setcolor(RED);
   outtextxy(170,340," INTRUDER ! ");
   getch();
   menu1();
  }
 }while(p==0);
}

//Player Login Function
void login(player &pl,player &p2,int mode)
{
 if(mode==1)
 {
  strcpy(D.p2.p.un,"A.I");
  strcpy(D.p2.p.pw,"\0");
  D.turn=0;
 }
 if(mode==2)
  D.turn=1;
 int i,p,b[10]={190,180,480,180,480,320,190,320,190,180};
 char t[2],c[9];
 do
 {
  p=0;
  cleardevice();
  theme();
  setcolor(BLUE);
  t[1]='\0';
  settextstyle(1,HORIZ_DIR,5);
  setcolor(RED);
  if(mode==1)
   outtextxy(190,100,"PLAYER LOGIN");
  else
   outtextxy(190,100,"PLAYER 1 LOGIN");
  setcolor(BLUE);
  settextstyle(11,HORIZ_DIR,2);
  setfillstyle(1,LIGHTGRAY);
  fillpoly(5,b);
  rectangle(357,190,450,205);
  outtextxy(200,195,"User Name (8 chars):");
  outtextxy(200,240,"Password(5 chars)  :");
  rectangle(357,235,450,250);
  outtextxy(200,295,"Confirm Password   :");
  rectangle(357,290,450,305);
  for(i=0;i<8;++i)
  {
   pl.un[i]=getch();
   t[0]=pl.un[i];
   if(pl.un[i]!=13)
    outtextxy(360+i*10,195,t);
   else
    break;
  }
  pl.un[i]='\0';
  setcolor(GREEN);
  outtextxy(200,195,"User Name (8 chars):");
  setcolor(BLUE);
  for(i=0;i<5;++i)
  {
   pl.pw[i]=getch();
   if(pl.pw[i]!=13)
    outtextxy(380+i*10,240,"*");
   else
    break;
  }
  pl.pw[i]='\0';
  setcolor(GREEN);
  outtextxy(200,240,"Password(5 chars)  :");
  setcolor(BLUE);
  for(i=0;i<5;++i)
  {
   c[i]=getch();
   if(c[i]!=13)
    outtextxy(380+i*10,295,"*");
   else
    break;
  }
  c[i]='\0';
  setcolor(GREEN);
  outtextxy(200,295,"Confirm Password   :");
  settextstyle(0,HORIZ_DIR,3);
  if(strcmp(c,pl.pw)==0)
  {
   setcolor(GREEN);
   outtextxy(240,340,"SUCCESS");
   p=1;
   getch();
  }
  else
  {
   setcolor(RED);
   outtextxy(75,340,"PASSWORD NOT MATCHING");
   getch();
  }
 }while(p==0);
 if(mode==2)
  do
  {
   p=0;
   cleardevice();
   theme();
   setcolor(BLUE);
   t[1]='\0';
   settextstyle(1,HORIZ_DIR,5);
   setcolor(RED);
   outtextxy(190,100,"PLAYER 2 LOGIN");
   setcolor(BLUE);
   settextstyle(11,HORIZ_DIR,2);
   setfillstyle(1,LIGHTGRAY);
   fillpoly(5,b);
   rectangle(357,190,450,205);
   outtextxy(200,195,"User Name (8 chars):");
   outtextxy(200,240,"Password(5 chars)  :");
   rectangle(357,235,450,250);
   outtextxy(200,295,"Confirm Password   :");
   rectangle(357,290,450,305);
   for(i=0;i<8;++i)
   {
	p2.un[i]=getch();
    t[0]=p2.un[i];
    if(p2.un[i]!=13)
     outtextxy(360+i*10,195,t);
    else
     break;
   }
   p2.un[i]='\0';
   setcolor(GREEN);
   outtextxy(200,195,"User Name (8 chars):");
   setcolor(BLUE);
   for(i=0;i<5;++i)
   {
	p2.pw[i]=getch();
    if(p2.pw[i]!=13)
     outtextxy(380+i*10,240,"*");
    else
     break;
   }
   p2.pw[i]='\0';
   setcolor(GREEN);
   outtextxy(200,240,"Password(5 chars)  :");
   setcolor(BLUE);
   for(i=0;i<5;++i)
   {
	c[i]=getch();
    if(c[i]!=13)
     outtextxy(380+i*10,295,"*");
    else
     break;
   }
   c[i]='\0';
   setcolor(GREEN);
   outtextxy(200,295,"Confirm Password   :");
   settextstyle(0,HORIZ_DIR,3);
   if(strcmp(c,p2.pw)==0)
   {
    setcolor(GREEN);
    outtextxy(240,340,"SUCCESS");
    p=1;
    getch();
   }
   else
   {      
    setcolor(RED);
    outtextxy(75,400,"PASSWORD NOT MATCHING");
    getch();
   }
  }while(p==0);
 retrieve(mode);
}

//MENU Function 
void menu1()
{
 char list[5][20]={"1-Player","2-Player","High Scores","About","Exit"};
 int mc=0,i,j=0;
 while(mc!=5)
 {
  cleardevice();
  theme();
  setlinestyle(0,0,1);
  settextstyle(0,HORIZ_DIR,5);
  setcolor(RED);
  outtextxy(100,20,"BATTLE SHIP");
  settextstyle(1,HORIZ_DIR,3);
  setcolor(GREEN);
  for(i=1;i<=5;++i)
  {
   settextstyle(1,HORIZ_DIR,fmod(i,3));
   outtextxy(205,120+50*(i-1),list[(i+mc+2)%5]);
  }
  setcolor(WHITE);
  rectangle(200,220,405,260);
  char c=getch();
  if(c==13)
   mc=5;
  else if(c=='P')
  (mc<4)?(mc++,++j):(mc=0,j=0);
  else if(c=='H')
  (mc>0)?(mc--,j--):(mc=4,j=4);
 }
 if(j==0)
  login(D.p1.p,D.p2.p,1);
 else if(j==1)
  login(D.p1.p,D.p2.p,2);
 else if(j==2)
  highscores();
 else if(j==3)
  about();
 else if(j==4)
  exit(0);
}

//Function to Check for valid orientation
int orichk(char c)
{
 if(c=='h'||c=='H'||c=='v'||c=='V')
  return 1;
 return 0;
}

//Function to retrieve the saved game
void retrieve(int mode)
{
 ifstream fin;
 ofstream fout("temp.dat",ios::binary);
 GameData T;
 char c='*',base[2];
 base[1]='\0';
 if(mode==1)
  fin.open("1plyr.dat",ios::binary);
 else if(mode==2)
  fin.open("2plyr.dat",ios::binary);
 settextstyle(0,HORIZ_DIR,0);
 setcolor(15);
 while(fin.read((char *)&T,sizeof(T)))
 {  
  if(structcmp(D.p1.p,T.p1.p,D.p2.p,T.p2.p)==1)
  {  
   outtextxy(40,400,"Do you want to continue your saved game? ");
   c=getch();base[0]=c;
   outtextxy(390,400,base);
   if(c=='y'||c=='Y')
   {  
    D=T;
	outtextxy(40,420,"Loading Saved Game.. ");
   }
   else
	outtextxy(40,420,"Loading New Game.. ");
   getch();
  }
  else
   fout.write((char *)&T,sizeof(T));
 }
 fin.close();
 fout.close();
 if(mode==1)
 { 
  remove("1plyr.dat");
  rename("temp.dat","1plyr.dat");
 }
 else
 { 
  remove("2plyr.dat");
  rename("temp.dat","2plyr.dat");
 }
 if(c=='y'||c=='Y')//checking if user wishes to continue
  gameplay(mode,1);
 else
  gameplay(mode,0);
}

//Function to save game 
void save()
{  
 ofstream fout;
 if(D.turn==0)
 { 
  fout.open("1plyr.dat",ios::binary|ios::app);
  fout.write((char *)&D,sizeof(D));
 }
 else
 { 
  fout.open("2plyr.dat",ios::binary|ios::app);
  fout.write((char *)&D,sizeof(D));
 }
 fout.close();
 menu1();
}

//Function to save scores of winners
void savescores(scoredata p)
{
 ifstream fin("scores.dat",ios::binary);
 ofstream fout("temp2.dat",ios::binary);
 scoredata t;
 int flag=0;
 while(fin.read((char*)&t,sizeof(t)))
 {
  if(strcmp(t.win_un,p.win_un)==0)
  {   
   flag++;
   if(t.score<p.score)
	fout.write((char*)&p,sizeof(p));
   else
	fout.write((char*)&t,sizeof(t));
  }
  else
   fout.write((char*)&t,sizeof(t));
 }
 if(flag==0)
  fout.write((char*)&p,sizeof(p));
 fin.close();  
 fout.close();
 remove("scores.dat");
 rename("temp2.dat","scores.dat");
 sortscores();
}

//Function to display message when a ship is sunk
void shipsunk(PData &T)
{
 int x,y,flag;
 for(int i=0;i<D.shipno;i++)
 {
  flag=0;
  for(int j=0;j<T.s[i].size;j++)
  {
   x=T.s[i].loc[j].x;
   y=T.s[i].loc[j].y;
   if(T.board[x][y]==ishit)
    flag++;
  }
  if(flag==T.s[i].size && T.s[i].state!=1)
  {
   T.s[i].state=1;
   outtextxy(40,400,T.p.un);
   outtextxy(40+textwidth(T.p.un),400,"'s ");
   outtextxy(40+textwidth(T.p.un)+textwidth("'s "),400,T.s[i].name);
   outtextxy(40+textwidth(T.p.un)+textwidth("'s ")+textwidth(T.s[i].name),400," Has been sunk");
  }
 }
}

//Function to sort high scores in descending order
void sortscores()
{
 int size,i=0;
 ifstream fin("scores.dat",ios::binary);
 ofstream fout("temp1.dat",ios::binary);
 fin.seekg(0,ios::end);
 size=fin.tellg()/sizeof(scoredata);
 scoredata *p=new scoredata[size];
 fin.seekg(0);
 scoredata t;
 while(fin.read((char*)(p+i),sizeof(scoredata)))
 {
  i++;
 }
 for(i=0;i<size-1;i++)
  for(int j=0;j<size-i-1;j++)
  {
   if( (p+j)->score < (p+j+1)->score )
   {
    t=*(p+j);
    *(p+j)=*(p+j+1);
    *(p+j+1)=t;
   }
  }
 delete p;
 for(i=0;i<size;i++)
 fout.write((char*)(p+i),sizeof(scoredata));
 fout.close();
 fin.close();
 remove("scores.dat");
 rename("temp1.dat","scores.dat");
}

void sprite_ship_hide(int i,int j,char c,char m)
{
 switch(c)
 { 
  case '÷':setcolor(BLUE);
	   setfillstyle(SOLID_FILL,BLUE);
	   break;
  case 'X':setcolor(YELLOW);
	   setfillstyle(SOLID_FILL,RED);
	   break;
  case '0':setcolor(BLUE);
	   setfillstyle(SOLID_FILL,LIGHTGRAY);
	   break;
  case 'S':setcolor(BLUE);
	   setfillstyle(SOLID_FILL,BLUE);
	   break;
 }
 if(m=='p')
  pieslice(37+25*j,137+25*i,0,360,8);
 else if(m=='c')
  pieslice(337+25*j,137+25*i,0,360,8);
 setcolor(WHITE);
 setfillstyle(SOLID_FILL,0);
}

void sprite_ship_show(int i,int j,char c,char m)
{
 switch(c)
 {
  case '÷':setcolor(BLUE);
	   setfillstyle(SOLID_FILL,BLUE);
	   break;
  case 'X':setcolor(YELLOW);
	   setfillstyle(SOLID_FILL,RED);
	   break;
  case '0':setcolor(BLUE);
	   setfillstyle(SOLID_FILL,LIGHTGRAY);
	   break;
  case 'S':setcolor(GREEN);
	   setfillstyle(SOLID_FILL,DARKGRAY);
	   break;
 }
 if(m=='p')
  pieslice(37+25*j,137+25*i,0,360,8);
 else if(m=='c')
  pieslice(337+25*j,137+25*i,0,360,8);
 setcolor(WHITE);
 setfillstyle(SOLID_FILL,0);
}

void spritedummy(int i,int j,char c)
{
 switch(c)
 {
  case '÷':setcolor(BLUE);
	   setfillstyle(SOLID_FILL,BLUE);
	   break;
  case 'X':setcolor(YELLOW);
	   setfillstyle(SOLID_FILL,RED);
	   break;
  case '0':setcolor(BLUE);
	   setfillstyle(SOLID_FILL,LIGHTGRAY);
	   break;
  case 'S':setcolor(GREEN);
	   setfillstyle(SOLID_FILL,DARKGRAY);
	   break;
 }
 pieslice(237+25*j,77+25*i,0,360,8);
 setcolor(WHITE);
 setfillstyle(SOLID_FILL,0);
}

//Function to store players' ships 
void store(PData &T)
{
 int i,j,flag,col,t1,row,tw,th;
 char ch,ch2,t2,ori,base[2];
 base[1]='\0';
 for(i=0;i<D.shipno;i++)
 {
  cleardevice();
  drawplboard(T);
  outtextxy(280,320,"STORE YOUR SHIPS!") ;
  if(i==0)
   outtextxy(40,330,"CRUISER(2 spots)");
  else if(i==1)
   outtextxy(40,330,"SUBMARINE(2 spots)");
  else if(i==2)
   outtextxy(40,330,"FRIGATE(3 spots)");
  else if(i==3)
   outtextxy(40,330,"ESCORT(4 spots)");
  else if(i==4)
   outtextxy(40,330,"DESTROYER(5 spots)");
  else if(i==5)
   outtextxy(40,330,"ANHILATOR(3 spots)");
  else if(i==6)
   outtextxy(40,330,"BOOSTER(2 spots)");
  else
   outtextxy(40,330,"NECROMANCER(4 spots)");
  do
  {
   do
   { 
    th=340;
    outtextxy(40,340,"Enter the base position(Eg: A2) : ");
    tw=textwidth("Enter the base position(Eg: A2) : ");
    do
    {
	 flag=0;
	 ch=getch();
	 base[0]=ch;
	 outtextxy(40+tw,th,base);
	 col=getch();
	 base[0]=col;
	 outtextxy(50+tw,th,base);
	 col=col-48;
	 t2=toupper(ch);
	 row=t2-65;
	 col--;
	 t1=corchk(row,col);
	 if(t1==0)
	 {
	  setviewport(30,300,600,450,0);
	  clearviewport();
	  setviewport(0,0,getmaxx(),getmaxy(),0);
	  outtextxy(40,320,"Enter a valid position : ");
	  tw=textwidth("Enter a valid position : ");
	  th=320;
	 }
    }while(t1==0);
    flag=0;
    do
    { 
	 th=350;
	 outtextxy(40,350,"Enter the orientation(Horizontal - h/H or Vertical - v/V) : ");
	 tw=textwidth("Enter the orientation(Horizontal - h/H or Vertical - v/V) : ");
	 do
	 {
	  flag=0;
	  ori=getch();
	  base[0]=ori;
	  outtextxy(40+tw,th,base);
	  t1=orichk(ori);
	  if(t1==0)
	  {
	   setviewport(30,300,600,450,0);
	   clearviewport();
	   setviewport(0,0,getmaxx(),getmaxy(),0);
	   outtextxy(40,320,"Enter a valid orientation : ");
	   tw=textwidth("Enter a valid orientation : ");
	   th=320;
	  }
	 }while(t1==0);
     flag=0;
	 if(ori=='h'||ori=='H')
	 {
	  for(j=0;j<T.s[i].size;j++)
	   if(col+j>=D.boardsize)
	   {
	    flag++;
	    break;
	   }
	 }
     else
	 {
	  for(j=0;j<T.s[i].size;j++)
	   if(row+j>=D.boardsize)
	   {
	    flag++;
	    break;
	   }
	 }
     if(flag!=0)
	 {
	  setviewport(30,300,600,450,0);
	  clearviewport();
	  setviewport(0,0,getmaxx(),getmaxy(),0);
	  outtextxy(40,320,"The base position entered does not support the orientation! ");
	  outtextxy(40,330,"Do you want to enter different orientation(o) or base position(b) :");
	  tw=textwidth("Do you want to enter different orientation(o) or base position(b) :");
	  th=330;
	  do
	  {
	   ch2=getch();
	   base[0]=ch2;
	   outtextxy(40+tw,th,base);
	   if(ch2!='o'&&ch2!='b')
	   { outtextxy(40,340,"Enter valid choice : "); 
         th=340; 
	   }
      }while(ch2!='o'&&ch2!='b');
      flag=0;
	  if(ch2=='o'||ch2=='O')
	   flag++;
	 }
    }while(flag!=0);
    flag=0;
    if(ch2=='b'||ch2=='B')
	 flag++;
    ch2='a';
   }while(flag!=0);
   flag=0;
   if(ori=='h'||ori=='H')
   {
    for(j=col;j<col+T.s[i].size;j++)
	 if(T.board[row][j]==isship)
	 {
	  flag++;
	  break;
	 }
   }
   else
   {
    for(j=row;j<row+T.s[i].size;j++)
	 if(T.board[j][col]==isship)
	 {
	  flag++;
	  break;
	 }
   }
   if(flag!=0)
   { 
    outtextxy(40,360,"Position already occupied");
	setviewport(30,300,600,450,0);
	clearviewport();
	setviewport(0,0,getmaxx(),getmaxy(),0);
   }
  }while(flag!=0);
  int m=0;
  if(ori=='h')
   for(int n=col;n<col+T.s[i].size;n++)
   {
    T.board[row][n]=isship;
    T.s[i].loc[m].x=row;
    T.s[i].loc[m].y=n;
    m++;
   }
  if(ori=='v')
   for(int n=row;n<row+T.s[i].size;n++)
   {
    T.board[n][col]=isship;
    T.s[i].loc[m].x=n;
    T.s[i].loc[m].y=col;
    m++;
   }
  getch();
 }
}

//Fn to compare struct objects
int structcmp(player A,player B,player C,player D)
{   
 if(strcmp(A.un,B.un)==0&&strcmp(A.pw,B.pw)==0&&strcmp(C.un,D.un)==0&&strcmp(C.pw,D.pw)==0)
  return(1);
 else
  return(0);
}

void theme()
{
 int p[10]={10,10,630,10,630,470,10,470,10,10};
 cleardevice();
 setcolor(BLUE);
 setlinestyle(SOLID_LINE,BLUE,2);
 drawpoly(5,p);
 setfillstyle(1,GREEN);
}

void main()
{
 clrscr();
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"..\\bgi");
 loading();
 closegraph();
}