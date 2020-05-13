#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<iomanip.h>
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ESC 27

void startgraph();
void initmouse();
void showmouse();
void hidemouse();
void getmouse();
void setmouse(int &px,int &py);
void restricmouseonx(int y1,int y2);
void restricmouseony(int y1,int y2);
class budget;
void piechart(budget &obj);
void barchart(budget &obj);
void graph();
union REGS in,out;
int px=0,py=0;
int click;

class budget
{
 public:
  double totalamt,food,clothes,electricity,other,savings,totalexp;
  double foodpercent,clothespercent,electricitypercent,otherpercent,savingspercent;
  double foodangle,clothesangle,electricityangle,otherangle,savingsangle;
  double foodbar,clothesbar,electricitybar,otherbar,savingsbar;
  char *menu[7];

 budget()
 {
  menu[0]="TotalAmmount";
  menu[1]="Food";
  menu[2]="CLothes";
  menu[3]="Electricity";
  menu[4]="OtherExp";
  menu[5]="TotalExpenses";
  menu[6]="Savings";
 }

 void setdata()
 {
  start:
  heading("  ==CHART==");
  gotoxy(5,5); cout<<menu[0];
  gotoxy(5,6); cout<<menu[1];
  gotoxy(5,7); cout<<menu[2];
  gotoxy(5,8); cout<<menu[3];
  gotoxy(5,9); cout<<menu[4];
  gotoxy(5,10); cout<<menu[5];
  gotoxy(5,11); cout<<menu[6];

  gotoxy(20,5); cin>>totalamt;
  gotoxy(20,6); cin>>food;if(checkmat()==0) goto start;
  gotoxy(20,7); cin>>clothes;if(checkmat()==0) goto start;
  gotoxy(20,8); cin>>electricity; if(checkmat()==0) goto start;
  gotoxy(20,9); cin>>other; if(checkmat()==0) goto start;
  gotoxy(20,10); cout<<gettotalexp();
  gotoxy(20,11); cout<<getsavings();
  getch();
 }

 double gettotalexp()
 {
  totalexp=food+clothes+electricity+other;
  return totalexp;
 }
 double getsavings()
 {
  gettotalexp();
  savings=totalamt-totalexp;
  return savings;
 }

 void setpercent()
 {
  foodpercent=(food*100)/totalamt;
  clothespercent=(clothes*100)/totalamt;
  electricitypercent=(electricity*100)/totalamt;
  otherpercent=(other*100)/totalamt;
  savingspercent=(savings*100)/totalamt;
 }

 void showpercent()
 {
  cout<<setprecision(2);
  gotoxy(30,5); cout<<"Food          "<<foodpercent<<"%";
  gotoxy(30,6); cout<<"Clothes       "<<clothespercent<<"%";
  gotoxy(30,7); cout<<"Electricity   "<<electricitypercent<<"%";
  gotoxy(30,8); cout<<"Other Exp     "<<otherpercent<<"%";
  gotoxy(30,9); cout<<"Savings       "<<savingspercent<<"%";
  getch();
 }

 void setanglevalue()
 {
  foodangle=(360*foodpercent)/100;
  clothesangle=foodangle+(360*clothespercent)/100;
  electricityangle=clothesangle+(360*electricitypercent)/100;
  otherangle=electricityangle+(360*otherpercent)/100;
  savingsangle=otherangle+(360*savingspercent)/100;
 }

 void setbar()
 {
  int diff=440-200;
  foodbar=440-diff*foodpercent/100;
  clothesbar=440-diff*clothespercent/100;
  electricitybar=440-diff*electricitypercent/100;
  otherbar=440-diff*otherpercent/100;
  savingsbar=440-diff*savingspercent/100;
 }

 int checkmat()
{
 int flag=1;
 if(food>totalamt)
  flag=0;
 else if((clothes+food)>totalamt)
  flag=0;
 else if((clothes+food+electricity)>totalamt)
  flag=0;
 else if((clothes+food+electricity+other)>totalamt)
  flag=0;

 if(flag==1)
 {
  return 1;
 }
 else
 {
  totalamt=food=clothes=electricity=other=0;
  gotoxy(5,12); cout<<"\nExpenses exceeding Total amt!! Renter";
  getch();
  cleardevice();
  return 0;
 }
}

};

int filtercolor(int i)
{
 int color;
 switch(i)
 {
  case 1: color=GREEN; break;
  case 2: color=LIGHTGRAY; break;
  case 3: color=RED; break;
  case 4: color=MAGENTA; break;
  case 6: color=BLUE; break;
 }
 return color;
}

void colorindex()
{
 budget obj;
 setfillstyle(0,DARKGRAY);
 setcolor(YELLOW);
 settextstyle(0,0,1);
 bar3d(430,160,600,340,3,1);
 int x=440,y=180;
 int x1=550,y1=170;

 for(int i=1;i<=6;i++)
 {
  if(i==5)continue;
  outtextxy(x,y,obj.menu[i]);
  setfillstyle(1,filtercolor(i));
  bar(x1,y1,x1+20,y1+20);
  y+=30,y1+=30;
 }
}

void heading(char label[70])
{
 setfillstyle(SOLID_FILL,WHITE);
 bar3d(220,10,220+200,10+30,5,1);
 settextstyle(1,0,3);
 setcolor(BLUE);
 outtextxy(225,10,label);
 settextstyle(0,0,1);
 setcolor(WHITE);
}

void main()
{
 startgraph();
 setbkcolor(CYAN);
 setcolor(BLUE);
 initmouse();
// graph();
// showmouse();
 heading("   ==CHART==");
 budget obj;
 obj.setdata();
 obj.getsavings();
 obj.setpercent();
 obj.showpercent();
 colorindex();
 obj.setanglevalue();
 obj.setbar();

 settextstyle(2,0,6);
 setcolor(WHITE);
 outtextxy(160,180,"Press.........");
 outtextxy(160,196,"1.> BarChart");
 outtextxy(160,210,"2.> Piechart");
 outtextxy(160,234,"Enter Your Choice: ");
 int choice;
 gotoxy(44,16); cin>>choice;

 switch(choice)
 {
  start:
  case 1:
   barchart(obj);
   break;
  case 2:
   piechart(obj);
   break;
  default:
  {
  // outtextxy(160,240,"Invalid Choice!");
   goto start;
  }
 }
// piechart(obj);
// getch();
// barchart(obj);


 getch();
// restorecetmode();
 closegraph(); //shuts down graphics system...
}

void piechart(budget &obj)
{
 int x=240,y=340,radius=80;
 setfillstyle(1,filtercolor(1));
 pieslice(x,y,0,obj.foodangle,radius);
 delay(500);
 setfillstyle(1,filtercolor(2));
 pieslice(x,y,obj.foodangle,obj.clothesangle,radius);
 delay(500);
 setfillstyle(1,filtercolor(3));
 pieslice(x,y,obj.clothesangle,obj.electricityangle,radius);
 delay(500);
 setfillstyle(1,filtercolor(4));
 pieslice(x,y,obj.electricityangle,obj.otherangle,radius);
 delay(500);
 setfillstyle(1,filtercolor(6));
 pieslice(x,y,obj.otherangle,obj.savingsangle,radius);

}


 void barchart(budget &obj)
 {
  char *msg;
  sprintf(msg,"%s %.lf",obj.menu[0],obj.totalamt);
  setfillstyle(1,DARKGRAY);
  bar3d(20,440,340,450,20,1);
  delay(500);
  setfillstyle(1,YELLOW);
  bar3d(40,200,50,440,0,0);
  settextstyle(0,VERT_DIR,1);
  setcolor(DARKGRAY);
  outtextxy(36,260,msg);
  delay(500);
  settextstyle(0,HORIZ_DIR,1);
  sprintf(msg,"%.lf%c",obj.foodpercent,'%');
  outtextxy(80+3,obj.foodbar-20,msg);
  setfillstyle(1,filtercolor(1));
  bar3d(80,obj.foodbar,100,440,3,1);
  delay(500);
  sprintf(msg,"%.lf%c",obj.clothespercent,'%');
  outtextxy(120+3,obj.clothesbar-20,msg);
  setfillstyle(1,filtercolor(2));
  bar3d(120,obj.clothesbar,140,440,3,1);
  delay(500);
  sprintf(msg,"%.lf%c",obj.electricitypercent,'%');
  outtextxy(160+3,obj.electricitybar-20,msg);
  setfillstyle(1,filtercolor(3));
  bar3d(160,obj.electricitybar,180,440,3,1);
  delay(500);
  sprintf(msg,"%.lf%c",obj.otherpercent,'%');
  outtextxy(200+3,obj.otherbar-20,msg);
  setfillstyle(1,filtercolor(4));
  bar3d(200,obj.otherbar,220,440,3,1);
  delay(500);
  sprintf(msg,"%.lf%c",obj.savingspercent,'%');
  outtextxy(240+3,obj.savingsbar-20,msg);
  setfillstyle(1,filtercolor(6));
  bar3d(240,obj.savingsbar,260,440,3,1);

 }

void startgraph()
{
  //request for autodectection
 int gd=DETECT,gm,errcode;

 //initialize the graphics system
 initgraph(&gd,&gm,"c:\\turboc3\\bgi");

 //read result of initialization
 errcode=graphresult();

 //grOK means driver loaded prperly... no issus
 if(errcode!=grOk)//some error
 {
  cout<<"Graphics err msg: "<<grapherrormsg(errcode)<<endl;
  getch();
  exit(1);
 }
}

void initmouse()
{
 in.x.ax=0;
 int86(51,&in,&out);
}

void showmouse()
{
 in.x.ax=1;
 int86(51,&in,&out);
}

void hidemouse()
{
 in.x.ax=2;
 int86(51,&in,&out);
}

void getmouse()
{
 in.x.ax=3;
 int86(51,&in,&out);
 click=out.x.bx;
 px=out.x.cx;
 py=out.x.dx;
}

void setmouse(int &px,int &py)
{
 in.x.ax=4;
 in.x.cx=px;
 in.x.dx=py;
 int86(51,&in,&out);
}

void restricmouseonx(int x1,int x2)
{
 in.x.ax=7;
 in.x.cx=x1;
 in.x.dx=x2;
 int86(51,&in,&out);
}

void restricmouseony(int y1,int y2)
{
 in.x.ax=8;
 in.x.cx=y1;
 in.x.dx=y2;
 int86(51,&in,&out);
}

void graph()
{
 int x;
 int y;
 int i;
 char xsg[10];
 char ysg[10];

 setbkcolor(DARKGRAY);
 settextstyle(2,0,2);

 for(x=0,y=0;x<=639;x=x+20,y=y+20)
 {
  setcolor(WHITE);
  line(x,0,x,479);
  sprintf(xsg,"%d",x);
  outtextxy(x+2,0,xsg);

  setcolor(WHITE);
  line(0,y,639,y);
  sprintf(ysg,"%d",y);
  outtextxy(0+2,y+1,ysg);

  setcolor(RED);
  line(x+10,0+10,x+10,479);
  line(0+10,y+10,639,y+10);
 }
}