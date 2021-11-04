/*	***  Graphics Mini Project  ***
	Program for Analog CLock (With Pendulum)
*/

#include <iostream>
#include <graphics.h>
#include <gl/gl.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <process.h>
#include <string.h>
#include <time.h>
#include <dos.h>
using namespace std;


//This function will determine position for min,sec hand 
void minSecPos(int xrad, int midx, int midy, int x[60], int y[60]) 
{
  int i, j=45;
  for (i=360; i>=0; i=i-6)
  {
   x[j] = midx-(xrad*cos((i*3.14)/180));
   y[j--] = midy-(xrad*sin((i*3.14)/180));
   j = (j==-1)?59:j;
  }
  return;
}


//This fuction sets clock's internal digit (their position)
void calcPoints(int radius, int midx, int midy, int x[12], int y[12])
{
  int x1, y1;
  x[0] = midx, y[0] = midy-radius;
  x[6] = midx, y[6] = midy+radius;
  x[3] = midx+radius, y[3] = midy;
  x[9] = midx-radius, y[9] = midy;

  x1 = (int) ((radius/2)*sqrt(3));
  y1 = (radius/2);
  x[2] = midx+x1, y[2] = midy-y1;
  x[4] = midx+x1, y[4] = midy+y1;
  x[8] = midx-x1, y[8] = midy+y1;
  x[10] = midx-x1, y[10] = midy-y1;

  x1 = radius/2;
  y1 = (int) ((radius/2)*sqrt(3));
  x[1] = midx+x1, y[1] = midy-y1;
  x[5] = midx+x1, y[5] = midy+y1;
  x[7] = midx-x1, y[7] = midy+y1;
  x[11] = midx-x1, y[11] = midy-y1;
  return;
}


//For making pendulum
int x_s=300+15;
int y_s=180+275;
int x_e,y_e;
void display(double i)
{
  x_e=x_s+95*cos(i);    
  y_e=y_s+95*sin(i);
  line(x_s,y_s,x_e,y_e+190);
  circle(x_e,y_e+190,20);
  for (int w=19;w>0;w--)
  {
  	circle(x_e,y_e+190,w);
  }
//delay(1);
//clearviewport();
}


//Main Function 
int main()
{	
	
 initwindow(1535,800);	
 
 int gd=DETECT, gm, err, tmp;
 initgraph(&gd, &gm, NULL);
 	
 int i, j;
 int midx, midy;
 int radius;
 int hr, min, sec;
 int x[12], y[12];
 int minx[60], miny[60];
 int hrx[12], hry[12];
 int secx[60], secy[60];
 int secx1, secy1;
 char str[256];
 time_t t1;
 struct tm*data;
 double z;


 err = graphresult();

if (err != grOk)
{
  
 printf("Graphics Error: %s",
 grapherrormsg(err));
 return 0;
 
}

 midx = getmaxx()/2;
 midy = getmaxy()/2;

//radius of clock
 radius = 200;

 calcPoints(radius-30, midx, midy, x, y);
 calcPoints(radius-90, midx, midy, hrx, hry);

//This will give position for minute,second hand
 minSecPos(radius-50, midx, midy, minx, miny);
 minSecPos(radius-70, midx, midy, secx, secy);


while (!kbhit())
{

//For line style (Here simple line)
 setlinestyle(SOLID_LINE, 1, 3);
//This will set style for text
 settextstyle(GOTHIC_FONT, 0, 3);

 circle(midx, midy, radius);

	
//Circle around clock
 setcolor(YELLOW);
 circle(315,233,220);
 circle(315,233,219);
 circle(315,233,218);
 circle(315,233,216);
 circle(315,233,215);
 circle(315,233,213);
 circle(315,233,210);



//Displaying it on right hand bottom corner
 outtextxy(847,475,"  Designed By:");
 outtextxy(847,525,"   Tanay ");
 outtextxy(847,575,"  Abhishek");
 outtextxy(847,625,"   Pradip ");
 outtextxy(847,675,"   Rupesh ");



//Print as "Analog clock" and show design around it
setcolor(10);   //Lightgreen
 line(750,30,950,30);
 line(750,200,950,200);
 line(750,30,750,200);
 line(950,30,950,200);

 setcolor(12);
 line(755,35,945,35);
 line(755,195,945,195);
 line(755,35,755,195);
 line(945,35,945,195);

 line(757,37,943,37);
 line(757,193,943,193);
 line(757,37,757,193);
 line(943,37,943,193);

 line(760,40,940,40);
 line(760,190,940,190);
 line(760,40,760,190);
 line(940,40,940,190);

 setcolor(10);  //Lightgreen
 outtextxy(840,87,"  Analog");
 outtextxy(840,155,"  Clock ");
 setcolor(YELLOW);


//
//Outline border 
setcolor(13);
for(int e=800;e>794;e--)
{
line(0,e,1535,e);
}

for(int e=1535;e>1525;e--)
{
line(e,0,e,800);
}

for(int e=0;e<10;e++)
{
line(e,0,e,800);
}
setcolor(14);
//


//Clock internal digits 
 setcolor(3);  //Cyan
 for (j=0; j<12; j++)
 {
   if (j==0)
     {
     	sprintf(str, "%d", 12);
     } 
   else 
	 {
    	sprintf(str, "%d", j);
     } 
   settextjustify(CENTER_TEXT, CENTER_TEXT);
   moveto(x[j], y[j]);
   outtext(str);
 }


//These will give current time by time function
 t1 = time(NULL);
 data = localtime(&t1);


//color of clock-hands and circle
 setcolor(15);
 
 
//Drawing line for sec,min,hr hand 
 sec = data->tm_sec % 60;
 line(midx, midy, secx[sec], secy[sec]);
 min = data->tm_min % 60;
 line(midx, midy, minx[min], miny[min]);
 hr = data->tm_hour % 12;
 line(midx, midy, hrx[hr], hry[hr]);



//Displaying name Graphics Mini Project
 setcolor(11);
 settextstyle(9,0,6);
 outtextxy(1300,90, "Computer");
 outtextxy(1300,180, "Graphics");
 outtextxy(1300,270, "Mini");
 outtextxy(1300,360, "Project");
 setcolor(11);
 settextstyle(6,0,3);
 outtextxy(1300,610, "Guide by -");
 outtextxy(1300,669, "Prof. Priti Vaidya");
 outtextxy(1300,709, "Prof. Megha Patil");


//Moving pendulum section
 setcolor(14);  //Yellow
	//for(z=2.3;z>0.7;z=z-0.01)
	for(z=2.3;z>0.7;z=z-0.03)
		{
				setcolor(14);
				display(z);
				delay(2);
				setcolor(0);
				display(z);
				//delay(2);
		}
		
		
	//for(z=0.7;z<2.3;z=z+0.01)
	for(z=0.7;z<2.3;z=z+0.03)
		{
				setcolor(14);
				display(z);
				delay(2);
				//if (z != 2.2)
			//	{
					setcolor(0);
					display(z);
				//}
		}
//

 setcolor(15); //White
 delay(1000);
 cleardevice();

}


 getch();
 closegraph();
 return 0;

}
