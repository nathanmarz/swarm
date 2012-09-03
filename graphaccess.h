#ifndef _GRAPHACCESS_H
#define _GRAPHACCESS_H

class specials
{
public:
	bool search(apstring mysearch);
	int size();
	void add(apstring myspec1);
	void remove(apstring myspecial);
	void clear();
	apstring operator [] (int mypos);
private:
	apvector <apstring> myspec;
};


class route
{
public:
	int getmaxright(); //returns amount that object will move to right in relation to Start
	int getmaxleft(); //returns amount that object will move to left in relation to Start
	const route & operator = (char mystring[]);
	const route & operator = (picture mypic);
	void reset(); //use once route is loaded in, this will find start and end
	picture mirrorhor();
	picture mirrorvert();
	position next();
private:
	void max_right();
	void max_left();
	int maxright;
	int maxleft;
	char getpoint(int rdown, int rright);
	position current;
	position last;
	position start;
	position end;
	position lastmove;
	picture theroute;
	int delay;
};




void specials::clear()
{
	myspec.resize(0);
}

void specials::remove(apstring myspecial)
{
	int ctr, ctr2;
	for(ctr=0;ctr<myspec.length();ctr++)
	{
		if(myspec[ctr]==myspecial)
		{
			for(ctr2=ctr;ctr2<myspec.length()-1;ctr2++)
			{
				myspec[ctr2] = myspec[ctr2+1];
			}
			myspec.resize(myspec.length()-1);
			break;
		}
	}
}

bool specials::search(apstring mysearch)
{
	for(int ctr=0;ctr<myspec.length();ctr++)
	{
		if(myspec[ctr]==mysearch)
			return true;
	}
	return false;
}

int specials::size()
{
	return myspec.length();
}

void specials::add(apstring myspec1)
{
	myspec.resize(myspec.length()+1);
	myspec[myspec.length()-1] = myspec1;
}

apstring specials::operator [] (int mypos)
{
	if(mypos>=0&&mypos<myspec.length())
	{
		return myspec[mypos];
	}
	cout<<endl<<"OUT OF RANGE OF SPECIALS!!!";
	apstring NULLstring;
	return NULLstring;
}








const route & route::operator =(char mystring[])
{
	theroute = mystring;
	return *this;
}

const route & route::operator =(picture mypic)
{
	theroute = mypic;
	return *this;
}

void route::reset()
{
	int x;
	int y;
	delay = 0;
	for(x=0;x<theroute.numrows();x++)
	{
		for(y=0;y<theroute.numcols();y++)
		{
			if(theroute.mypic[x][y]=='S')
				start.setpos(x,y);
			if(theroute.mypic[x][y]=='E')
				end.setpos(x,y);
		}
	}
	current = start;
	last = end;
	lastmove.setpos(0,0);
	max_right();
	max_left();
};

char route::getpoint(int rdown, int rright)
{
	if(rdown<0||rright<0||rdown>=theroute.numrows()||rright>=theroute.numcols())
		return NULL;
	return theroute.mypic[rdown][rright];
}

position route::next()
{
	delay--;
	int ctr;
	if(delay>=0)
	{
		position NULLpos;
		return NULLpos;
	}
	delay = 0;
	int x, y;
	position thestart = current;
	position thestartlast = last;
	position lastmoveC;
	lastmoveC.setpos(current.getdown()-last.getdown(),current.getright()-last.getright());
	if(getpoint(current.getdown(),current.getright())=='S'||getpoint(current.getdown(),current.getright())=='s')
		lastmoveC.setpos(0,0);
	position thelist[8];


	thelist[7].setpos(0,0);
	if(lastmoveC.getdown()==-1 && lastmoveC.getright()==0)
	{
		thelist[0].setpos(-1,0);
		thelist[1].setpos(0,-1);
		thelist[2].setpos(0,1);
		thelist[3].setpos(-1,-1);
		thelist[4].setpos(-1,1);
		thelist[5].setpos(1,-1);
		thelist[6].setpos(1,1);
	}

	if(lastmoveC.getdown()==1 && lastmoveC.getright()==0)
	{
		thelist[0].setpos(1,0);
		thelist[1].setpos(0,-1);
		thelist[2].setpos(0,1);
		thelist[3].setpos(1,1);
		thelist[4].setpos(1,-1);
		thelist[5].setpos(-1,1);
		thelist[6].setpos(-1,-1);
	}

	if(lastmoveC.getdown()==0 && lastmoveC.getright()==1)
	{
		thelist[0].setpos(0,1);
		thelist[1].setpos(-1,0);
		thelist[2].setpos(1,0);
		thelist[3].setpos(-1,-1);
		thelist[4].setpos(-1,1);
		thelist[5].setpos(1,-1);
		thelist[6].setpos(1,1);
	}

	if(lastmoveC.getdown()==0 && lastmoveC.getright()==-1)
	{
		thelist[0].setpos(0,-1);
		thelist[1].setpos(1,0);
		thelist[2].setpos(-1,0);
		thelist[3].setpos(-1,-1);
		thelist[4].setpos(-1,1);
		thelist[5].setpos(1,-1);
		thelist[6].setpos(1,1);
	}

	if(lastmoveC.getdown()==-1 && lastmoveC.getright()==-1)
	{
		thelist[0].setpos(-1,-1);
		thelist[1].setpos(-1,1);
		thelist[2].setpos(1,-1);
		thelist[3].setpos(0,1);
		thelist[4].setpos(0,-1);
		thelist[5].setpos(1,0);
		thelist[6].setpos(-1,0);
	}

	if(lastmoveC.getdown()==1 && lastmoveC.getright()==1)
	{
		thelist[0].setpos(1,1);
		thelist[1].setpos(1,-1);
		thelist[2].setpos(-1,1);
		thelist[3].setpos(0,1);
		thelist[4].setpos(0,-1);
		thelist[5].setpos(1,0);
		thelist[6].setpos(-1,0);
	}

	if(lastmoveC.getdown()==-1 && lastmoveC.getright()==1)
	{
		thelist[0].setpos(-1,1);
		thelist[1].setpos(-1,-1);
		thelist[2].setpos(1,1);
		thelist[3].setpos(0,1);
		thelist[4].setpos(0,-1);
		thelist[5].setpos(1,0);
		thelist[6].setpos(-1,0);
	}

	if(lastmoveC.getdown()==1 && lastmoveC.getright()==-1)
	{
		thelist[0].setpos(1,-1);
		thelist[1].setpos(1,1);
		thelist[2].setpos(-1,-1);
		thelist[3].setpos(0,1);
		thelist[4].setpos(0,-1);
		thelist[5].setpos(1,0);
		thelist[6].setpos(-1,0);
	}
	if(lastmoveC.getdown()==0 && lastmoveC.getright()==0)
	{
		thelist[0].setpos(-1,-1);
		thelist[1].setpos(-1,0);
		thelist[2].setpos(-1,1);
		thelist[3].setpos(0,-1);
		thelist[4].setpos(0,1);
		thelist[5].setpos(1,-1);
		thelist[6].setpos(1,0);
		thelist[7].setpos(1,1);
	}








	char theaction;

	for(ctr=0;ctr<8;ctr++)
	{
		x = current.getdown()+thelist[ctr].getdown();
		y = current.getright()+thelist[ctr].getright();

		theaction=getpoint(x,y);
		if(theaction!=NULL&&theaction!=' ')
		{
			last = current;
			current.setpos(x,y);
			break;
		}
					
	}



	position theret;
	if(theaction=='.'||theaction=='S')
	{
		theret.setpos(current.getdown()-thestart.getdown(),current.getright()-thestart.getright());
	}
	if(theaction=='*'||theaction=='s')
	{
		
		next();
		theret.setpos(current.getdown()-thestart.getdown(),current.getright()-thestart.getright());
	}
	if(theaction=='E')
	{
		current = start;
		last = end;
		theret = next();
	}
	if(theaction=='R')
	{
		position spec = last;
		last = current;
		current = spec;
	}
	if(theaction=='C')
	{
		last = thestartlast;
		current = thestart;
		theret = lastmove;
	}
	if(theaction>='1'&&theaction<='9')
	{
		delay = int(theaction) - int('0');
		theret.setpos(current.getdown()-thestart.getdown(),current.getright()-thestart.getright());
	}
	if(theaction=='M')
	{
		delay = 20;
		theret.setpos(current.getdown()-thestart.getdown(),current.getright()-thestart.getright());
	}
	if(theaction=='L')
	{
		delay = 60;
		theret.setpos(current.getdown()-thestart.getdown(),current.getright()-thestart.getright());
	}
	lastmove = theret;
	return theret;
}


picture route::mirrorhor()
{
	picture newroute;
	newroute.mypic.resize(theroute.numrows(),theroute.numcols());
	int x,y;
	for(x=0;x<theroute.numrows();x++)
	{
		for(y=0;y<theroute.numcols();y++)
		{
			newroute.mypic[x][theroute.numcols()-y-1]=theroute.mypic[x][y];
		}
	}
	return newroute;
}

picture route::mirrorvert()
{
	picture newroute;
	newroute.mypic.resize(theroute.numrows(),theroute.numcols());
	int x,y;
	for(x=0;x<theroute.numrows();x++)
	{
		for(y=0;y<theroute.numcols();y++)
		{
			newroute.mypic[theroute.numrows()-x-1][y]=theroute.mypic[x][y];
		}
	}
	return newroute;
}

int route::getmaxright()
{return maxright;}

int route::getmaxleft()
{return maxleft;}

void route::max_right()
{
	int right = 0;
	int x,y;
	char test;
	for(x=0;x<theroute.numrows();x++)
	{
		for(y=0;y<theroute.numcols();y++)
		{
			test = theroute.mypic[x][y];
			if(test!=' '&&test!='*'&&test!='E'&&test!='R'&&test!='C'&&y>right)
				right = y;
		}
	}
	maxright = right;
}

void route::max_left()
{
	int left = theroute.numcols()-1;
	int x,y;
	char test;
	for(x=0;x<theroute.numrows();x++)
	{
		for(y=0;y<theroute.numcols();y++)
		{
			test = theroute.mypic[x][y];
			if(test!=' '&&test!='*'&&test!='E'&&test!='R'&&test!='C'&&y<left)
				left = y;
		}
	}
	maxleft = left;
}



#endif