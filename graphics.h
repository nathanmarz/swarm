#ifndef _CONGRAPHICS_H
#define _CONGRAPHICS_H

#include <iostream>
#include <math.h>
#include <time.h>
#include "apmatrix.h"

using namespace std;

void Delay(float seconds);
/*
todo:
1. update classes with "position" object support

*/

class position
{
public:
	position();
	void setpos(int down1, int right1);
	int getdown();
	int getright();
private:
	int down;
	int right;
};

class picture
{
public:
	picture();
	void setmask(char mymask);//do this
	char getmask();
	apmatrix <char> mypic;
	void clear();
	int numrows();
	int numcols();
	const picture & operator = (char mystring[]);
private:
	char mask;
	int height;
};

class animation
{
public:
	animation();
	void add(picture mypic);
	void add(picture mypic,int num);
	picture getcurrent();
	void next();
private:
	apvector <picture> mypics;
	apvector <int> mydelays;
	int delay;
	int picnum;
};

class screen
{
public:
	screen();
	screen(int isitmanual);
	void display();
	void line(int down1,int right1,int down2, int right2);
	void line(int down1,int right1,int down2, int right2,char mydisp);
	void point(int down1, int right1);
	void point(int down1, int right1, char mydisp);
	void circle(int down1, int right1, float radius);
	void circle(int down1, int right1, float radius, char mydisp);
	void text(int down1,int right1,char mytext[]);
	void text(int down1,int right1,char mytext);
	void text(int down1,int right1,int mynum);
	void displaypic(int down, int right,picture mypic);
	void picnot(int down, int right, picture mypic);
	void clear();
	char getpoint(int down1, int right1);
private:
	int manual;
	char thescreen[51][81];
	int pten(int num);
protected:
	void trydisp();
};



position::position()
{
	down = 0;
	right = 0;
}

void position::setpos(int down1, int right1)
{
	down = down1;
	right = right1;
}

int position::getdown()
{return down;}

int position::getright()
{return right;}


picture::picture()
{
	clear();
}

int picture::numrows()
{
	return mypic.numrows();
}

int picture::numcols()
{
	return mypic.numcols();
}

const picture & picture::operator =(char mystring[])
{
	int row;
	row = height;
	height++;
	int len;
	for(len = 0;mystring[len]!=NULL;len++)
	{}
	mypic.resize(mypic.numrows()+1,len);
	for(int a = 0;a<len;a++)
	{
		mypic[row][a] = mystring[a];
	}
	return *this;
}

void picture::setmask(char mymask)
{
	mask = mymask;
}

char picture::getmask()
{
	return mask;
}

void picture::clear()
{
	height = 0;
	mypic.resize(0,0);
}



animation::animation()
{
	picnum = 0;
	delay = 0;
}

void animation::add(picture mypic)
{
	add(mypic,1);
}

void animation::add(picture mypic,int num)
{
	mypics.resize(mypics.length()+1);
	mydelays.resize(mydelays.length()+1);
	mypics[mypics.length()-1] = mypic;
	mydelays[mydelays.length()-1] = num;
	delay = mydelays[0];
}

picture animation::getcurrent()
{
	if(mypics.length()==0)
	{
		picture NULLpic;
		return NULLpic;
	}
	return mypics[picnum];
}

void animation::next()
{
	delay--;
	if(delay<=0)
	{
		picnum++;
		if(picnum>mypics.length()-1)
			picnum = 0;
		delay = mydelays[picnum];
	}
}



screen::screen()
{
	manual = 1;
	clear();
}

void screen::clear()
{
	for(int x=0;x<=50;x++)
	{
	for(int y=0;y<=79;y++)
		{
		thescreen[x][y] = ' ';
		}
	}
}

screen::screen(int isitmanual)
{
	if(isitmanual==1)
		manual = 1;
	else
		manual = 0;
for(int x=0;x<=50;x++)
	{
	for(int y=0;y<=79;y++)
		{
		thescreen[x][y] = ' ';
		}
	}
}

void screen::display()
{
system("clear");
for(int x=0;x<=49;x++)
	{
	for(int y=0;y<=79;y++)
		{
		cout<<thescreen[x][y];
		}
    cout<<endl;
	}
	for(int x=0;x<=79;x++)
	{cout<<"-";}
	cout<<endl;
}

void screen::point(int down1, int right1, char mydisp)
{
	if(down1>=0&&down1<=49&&right1<=79&&right1>=0)
		thescreen[down1][right1] = mydisp;
	trydisp();
}

void screen::point(int down1, int right1)
{
	if(down1>=0&&down1<=49&&right1<=79&&right1>=0)
		thescreen[down1][right1] = '.';
	trydisp();
}

void screen::line(int down1,int right1,int down2, int right2)
{
	float right = right2 - right1;
	float down = down2 - down1;
	int variable = right*(right2>right1) + down*(down2>down1) - right*(right2<right1) - down*(down2<down1);
	right = 1.0*right/variable;
	down = 1.0*down/variable;
	for(int t=0;t<=variable;t++)
	{
	thescreen[int(down1+down*t)][int(right1+right*t)]='.';		
	}
	trydisp();
}

void screen::line(int down1,int right1,int down2, int right2,char mydisp)
{
	float right = right2 - right1;
	float down = down2 - down1;
	int variable = right*(right2>right1) + down*(down2>down1) - right*(right2<right1) - down*(down2<down1);
	right = 1.0*right/variable;
	down = 1.0*down/variable;
	for(int t=0;t<=variable;t++)
	{
	thescreen[int(down1+down*t)][int(right1+right*t)]=mydisp;		
	}
	trydisp();
}

void screen::circle(int down1, int right1, float radius)
{
	for(float angle=0;angle<=7;angle+=.05)
	{
		if(int(down1+radius*cos(angle))==int(down1+radius)&&int(right1+radius*sin(angle))==right1)
		{}
		else
			thescreen[int(down1+radius*cos(angle))][int(right1+radius*sin(angle))] = '.';
	}
	trydisp();
}

void screen::circle(int down1, int right1, float radius, char mydisp)
{
	for(float angle=0;angle<=7;angle+=.05)
	{
		if(int(down1+radius*cos(angle))==int(down1+radius)&&int(right1+radius*sin(angle))==right1)
		{}
		else
			point(int(down1+radius*cos(angle)),int(right1+radius*sin(angle)),mydisp);

	}
	trydisp();
}

void screen::text(int down1,int right1,char mytext[])
{
	int length;
	for(length=0;mytext[length]!='\0';length++)
	{}
	for(int x = 0;right1+x<=right1+length;x++)
	{
	if(right1+x<=79)
		thescreen[down1][right1+x] = mytext[x];
	}
}

void screen::text(int down1,int right1,int mynum)
{
	if(mynum<0)
	{
		mynum=-mynum;
		text(down1,right1,'-');
		right1++;
	}
	char mytext[81];
	int length;
	int mynum2;
	for(length = 1;1.0*mynum/pten(length)>=1;length++)
	{}
	int amt = 0;
	for(int ctr=length-1;ctr>=0;ctr--)
	{
		mynum2 = mynum - amt;
		for(mynum2;mynum2%pten(ctr)!=0;mynum2--)
		{}
		amt = amt+mynum2;
		mynum2 = mynum2/pten(ctr);
		mytext[length-ctr-1] = char(mynum2+48);
	}
	mytext[length] = NULL;

	text(down1,right1,mytext);
}

void screen::displaypic(int down, int right, picture mypic)
{
	for(int ctr1 = 0;ctr1<mypic.numrows();ctr1++)
	{
		for(int ctr2 = 0;ctr2<mypic.numcols();ctr2++)
		{
			if(mypic.getmask()!=mypic.mypic[ctr1][ctr2]&&down+ctr1>=0&&down+ctr1<=49&&right+ctr2>=0&&right+ctr2<=79)
				point(down+ctr1,right+ctr2,mypic.mypic[ctr1][ctr2]);

		}
	}

}

void screen::picnot(int down, int right, picture mypic)
{
	for(int ctr1 = 0;ctr1<mypic.numrows();ctr1++)
	{
		for(int ctr2 = 0;ctr2<mypic.numcols();ctr2++)
		{
			if(mypic.getmask()!=mypic.mypic[ctr1][ctr2]&&down+ctr1>=0&&down+ctr1<=49&&right+ctr2>=0&&right+ctr2<=79)
				point(down+ctr1,right+ctr2,' ');

		}
	}
}


int screen::pten(int num)
{
	int value = 1;
	for(int ctr = 0;ctr<num;ctr++)
	{
		value*=10;
	}
return value;
}

void screen::text(int down1,int right1,char mytext)
{
		thescreen[down1][right1] = mytext;
}

char screen::getpoint(int down1, int right1)
{
	if(down1>=0&&down1<=49&&right1>=0&&right1<=79)
		return thescreen[down1][right1];
	else
		return ' ';
}

void screen::trydisp()
{
	if(manual!=1)
		display();
}


void Delay(float seconds) {	// creates a delay of specified seconds
								// example: Delay(0.2); // o.2 seconds
	// translate seconds into clock ticks
	clock_t ticks = seconds * CLOCKS_PER_SEC;	

	// Get the current tick value of the clock
	clock_t start = clock();

	// Wait until current tick of clock exceeds the delay time
	while (clock() - start < ticks)
	{}
}// end of Delay

#endif