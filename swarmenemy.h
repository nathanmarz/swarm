#ifndef _SWARMENENMY_H
#define _SWARMENENMY_H

class enemy
{
public:
	enemy();
	void init(int hp1, picture mypic1, route myroute1);
	void init(int hp1, route myroute1);
	void addAnim(picture mypic1);
	void addAnim(picture mypic1,int num);
	void setworth(int money1, int losses1);
	void setspeed(int speed1);
	void setarmor(int armorreduce1, int armorchance1);
	void create(int down1, int right1);
	void move();
	void special(apstring mystring);
	bool getalive();
	int width();
	int getmaxright(); //route
	int getmaxleft();
	void display();
private:
	char exptype; //E = normal, H = High Explosive
	int money; //earned if killed
	int losses; //lost if collide
	bool alive;
	int ID;
	animation myani;
	route myroute;
	int armorreduce;
	int armorchance;
	int myhp;
	int down;
	int right;
	int myspeed; //how fast it goes through route
};

enemy::enemy()
{
	armorreduce = 0;
	armorchance = 0;
	alive = false;
	money = 0;
	losses = 0;
	myspeed = 1;
}

void enemy::setworth(int money1, int losses1)
{
	money = money1;
	losses = losses1;
}

void enemy::setspeed(int speed1)
{myspeed = speed1;}

bool enemy::getalive()
{return alive;}

void enemy::init(int hp1, picture mypic1, route myroute1)
{
	myani.add(mypic1);
	init(hp1,myroute1);
}

void enemy::init(int hp1, route myroute1)
{
	myhp = hp1;
	myroute = myroute1;
	exptype = 'E';
}

void enemy::addAnim(picture mypic1)
{
	myani.add(mypic1);
}

void enemy::addAnim(picture mypic1,int num)
{
	myani.add(mypic1,num);
}

void enemy::create(int down1, int right1)
{
	down = down1;
	right = right1;
	alive = true;
	ID = reg.registerme();
	if(ID==-1)
		alive=false;
}

void enemy::move() //use numbers so different bullets can do more or less amounts of damage
{
	picture mypic = myani.getcurrent();
	if(alive==true)
		reg.update(ID,down,right,mypic,"Enemy",-1,1);
	int ctr;
	if(alive==true)
	{
		env.picnot(down,right,mypic);
		machine mymach;
		mymach = reg.getmymessages(ID); //gets messages from registry and then clears them from there
		int dam;
		while(mymach.anymessages())
		{
			dam = 0;
			message mess = mymach.getmessage();
			if(mess.getmessage()<='9'&&mess.getmessage()>='1')
				dam = int(mess.getmessage())-int('0');
			if(mess.getmessage()=='K')
				dam = 1000;
			if(dam!=0)
			{
				if(rand()%1000<=armorchance)
				{
					dam = dam - armorreduce;
					if(dam<0)
						dam = 0;
				}
			}
			myhp = myhp - dam;
		}

		myani.next();
		mypic = myani.getcurrent();
		if(env.findeffect("Vibration"))
		{
			int randnum = rand()%4;
			if(randnum==0)
				down--;
			if(randnum==2)
				down++;
			if(randnum==1)
				right--;
			if(randnum==3)
				right++;
			randnum = rand()%20;
			if(randnum==0)
				myhp--;
		}
		if(env.findeffect("Radiation"))
		{
			int randnum = rand()%28;
			if(randnum==0)
			{
				down-=1;
				myhp-=2;
			}

		}
		if(myhp<=0||right>90||right+mypic.numcols()<-10)
		{
			alive = false;
			if(myhp<=0)
				env.killed(money);
			reg.unregister(ID);
			env.explode(down+mypic.numrows()/2,right+mypic.numcols()/2,exptype);
		}
		if(down+mypic.numrows()>=48&&alive==true)
		{
			alive = false;
			env.collide(losses);
			reg.unregister(ID);
			env.explode(down+mypic.numrows()/2,right+mypic.numcols()/2,exptype);
		}
		if(!env.findeffect("Stasis"))
		{
			position next;
			if(!env.findeffect("Shockwave"))
			{
				for(ctr=0;ctr<myspeed;ctr++)
				{
					next = myroute.next();
					down = down+next.getdown();
					right = right+next.getright();
				}
			}
		}
		if(env.findeffect("Shockwave"))
			down-=2;
		if(env.findeffect("Centralize"))
		{
			if(rand()%3!=0)
			{
				if(right+mypic.numcols()/2>40)
					right--;
				if(right+mypic.numcols()/2<40)
					right++;
			}
		}
		if(alive==true)
		{
			env.displaypic(down,right,mypic);
		}
	}
}

void enemy::setarmor(int armorreduce1, int armorchance1)
{
	armorreduce = armorreduce1;
	armorchance = armorchance1;
}

void enemy::display()
{
	if(alive==true)
		env.displaypic(down,right,myani.getcurrent());
}

int enemy::width()
{return myani.getcurrent().numcols();}

int enemy::getmaxright()
{return myroute.getmaxright();}

int enemy::getmaxleft()
{return myroute.getmaxleft();}

void enemy::special(apstring mystring)
{
	if(mystring=="High Explosive")
		exptype = 'H';
	if(mystring=="Explosive")
		exptype = 'E';
	if(mystring=="Non-Explosive")
		exptype = 'X';
}



#endif