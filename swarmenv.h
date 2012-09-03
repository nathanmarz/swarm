#ifndef _SWARMENV_H
#define _SWARMENV_H

bullet helpMissL;
bullet helpMissR;

class environment //have different arrays for nukes and bombs
{
public:
	environment();
	bool scan(int down1, int right1, int down2, int right2);
	void displaypic(int down1, int right1, picture pic1);
	void picnot(int down1, int right1, picture pic1);
	void explode(int down1, int right1);
	void explode(int down1, int right1, char exptype);
	void createbullet(bullet mybull);
	void createbullet(expbullet mybull);
	void erasebullets();
	void movebullets(); //bullet movement (first expbull, then reg)
	bool run(); //screen display
	void setSPEED(float newspeed); //changes framerate
	void stop(); //used when level has finished
	void reset();
	void circle(int down1, int right1, float rad, char disp);
	void collide(int damage1);
	void killed(int money1);
	void sdamage(int damage1); //used for on-screen stats (how much damage ship has taken)
	void smaxHP(int maxHP1); //used when ship is created for level (shown on on screen stats next to damage taken)
	void sammo(int myammo);
	int getmoneyearned();
	bool getkeepgo();
	void effect(apstring myeffect, int time);
	bool findeffect(apstring myeffect);
	void myweapon(apstring activeweapon1);

private:
	void updateEff();
	specials envFactors;
	apvector <int> envFtime;
	int bullPOS;
	int expbullPOS;
	bool keepgo;
	float SPEED;
	int SIZE;
	int expSIZE;
	bullet bullets[650];
	expbullet expbullets[100];
	screen display;

// stats and info purposes for screen
	apstring activeweapon;
	int numkilled;
	int numcollide;
	int moneyearned;
	int shipdamage;
	int shipmax;
	int shipammo;
};


environment::environment()
{
	expbullPOS = 0;
	bullPOS = 0;
	SPEED = .04;
	SIZE = 650;
	expSIZE = 100;
}

void environment::sammo(int myammo)
{
	shipammo = myammo;
}

void environment::stop()
{
	keepgo = false;
}

void environment::reset()
{
//	reg.clear();
	envFactors.clear();
	envFtime.resize(0);
	numcollide = 0;
	numkilled = 0;
	moneyearned = 0;
	display.clear();
	bullPOS = 0;
	expbullPOS = 0;
	keepgo = true;
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		bullets[ctr].destroy();
	}
	for(ctr=0;ctr<expSIZE;ctr++)
	{
		expbullets[ctr].destroy();
	}
}

void environment::collide(int damage1)
{
	numcollide++;
	moneyearned-=damage1;
}

void environment::killed(int money1)
{
	numkilled++;
	moneyearned+=money1;
}

void environment::sdamage(int damage1)
{shipdamage = damage1;}

void environment::smaxHP(int maxHP)
{shipmax = maxHP;}

void environment::setSPEED(float newspeed)
{SPEED = newspeed;}

void environment::displaypic(int down1, int right1, picture pic1)
{
	display.displaypic(down1,right1,pic1);
}

void environment::picnot(int down1, int right1, picture pic1)
{
	display.picnot(down1,right1,pic1);
}


void environment::explode(int down1, int right1)
{
	explode(down1,right1,'E');
}

void environment::explode(int down1, int right1, char exptype)
{
	bullet mybull;
	expbullet myexp;
	picture thepic;
	thepic.setmask('Q');

	if(exptype=='E')
	{
		thepic.clear();
		thepic = "*";
		mybull.init(down1,right1,northWR,thepic);
		createbullet(mybull);
		mybull.init(down1,right1,upR,thepic);
		createbullet(mybull);
		mybull.init(down1,right1,northER,thepic);
		createbullet(mybull);
		mybull.init(down1,right1,leftR,thepic);
		createbullet(mybull);
		mybull.init(down1,right1,rightR,thepic);
		createbullet(mybull);
		mybull.init(down1,right1,southWR,thepic);
		createbullet(mybull);
		mybull.init(down1,right1,downR,thepic);
		createbullet(mybull);
		mybull.init(down1,right1,southER,thepic);
		createbullet(mybull);
	}
	if(exptype=='N')
	{
		thepic.clear();
		thepic = "o";
		myexp.settype('E');
		myexp.init(down1,right1,northWR,thepic);
		createbullet(myexp);
		myexp.init(down1,right1,upR,thepic);
		createbullet(myexp);
		myexp.init(down1,right1,northER,thepic);
		createbullet(myexp);
		myexp.init(down1,right1,leftR,thepic);
		createbullet(myexp);
		myexp.init(down1,right1,rightR,thepic);
		createbullet(myexp);
		myexp.init(down1,right1,southWR,thepic);
		createbullet(myexp);
		myexp.init(down1,right1,downR,thepic);
		createbullet(myexp);
		myexp.init(down1,right1,southER,thepic);
		createbullet(myexp);
	}

	if(exptype=='H')
	{
		thepic.clear();
		thepic = "***";
		thepic = "***";
		thepic = "***";
		mybull.init(down1-1,right1-1,northWR,thepic,'4');
		createbullet(mybull);
		mybull.init(down1-1,right1-1,upR,thepic,'4');
		createbullet(mybull);
		mybull.init(down1-1,right1-1,northER,thepic,'4');
		createbullet(mybull);
		mybull.init(down1-1,right1-1,leftR,thepic,'4');
		createbullet(mybull);
		mybull.init(down1-1,right1-1,rightR,thepic,'4');
		createbullet(mybull);
		mybull.init(down1-1,right1-1,southWR,thepic,'4');
		createbullet(mybull);
		mybull.init(down1-1,right1-1,downR,thepic,'4');
		createbullet(mybull);
		mybull.init(down1-1,right1-1,southER,thepic,'4');
		createbullet(mybull);
	}
}

bool environment::run()
{
	bullPOS = 0;
	expbullPOS = 0;
	if(keepgo==false)
	{
		display.text(15,33,"Enemies killed: ");
		display.text(15,49,numkilled);
		display.text(17,28,"Enemies that reached bottom: ");
		display.text(17,57,numcollide);
		display.text(19,33,"Damage to ship: ");
		display.text(19,49,(shipdamage-shipmax)*(shipdamage>shipmax));
		display.text(21,33,"Money earned: ");
		display.text(21,47,moneyearned-5*(shipdamage-shipmax)*(shipdamage>shipmax));
		display.text(23,33,"Shift-X to Continue");
	}
	display.line(48,0,48,79,'_');
	display.line(49,0,49,79,' ');
	display.text(49,0,shipmax);
	display.text(49,5,"/");
	display.text(49,7,shipdamage);
	display.text(49,15,"Kills: ");
	display.text(49,22,numkilled);
	display.text(49,31,"Kamikazied: ");
	display.text(49,43,numcollide);
	char thewep[21];
	int ctr;
	for(ctr=0;ctr<activeweapon.length()&&ctr<21;ctr++)
	{
		thewep[ctr] = activeweapon[ctr];
	}
	thewep[ctr] = NULL;

	display.text(49,48,thewep);
	display.text(49,70,"Ammo: ");
	if(shipammo==-1)
		display.text(49,76,"oo");
	else
		display.text(49,76,shipammo);
	if(shipdamage>shipmax*2)
		display.text(15,33,"You have exploded!!!");
	display.display();
	updateEff();
	return keepgo;
}

void environment::createbullet(bullet mybull)
{
	int ctr;
	for(ctr=bullPOS;ctr<SIZE;ctr++)
	{
		if(bullets[ctr].getalive()==false)
		{
			bullets[ctr] = mybull;
			bullets[ctr].display(display);
			break;
		}
	}
	bullPOS = ctr;
}

void environment::createbullet(expbullet mybull)
{
	int ctr;
	for(ctr=expbullPOS;ctr<SIZE;ctr++)
	{
		if(expbullets[ctr].getalive()==false)
		{
			expbullets[ctr] = mybull;
			expbullets[ctr].display(display);
			break;
		}
	}
	expbullPOS = ctr;
}

void environment::erasebullets()
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		bullets[ctr].erase(display);
	}
	for(ctr=0;ctr<expSIZE;ctr++)
	{
		expbullets[ctr].erase(display);
	}

}

void environment::movebullets()
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		bullets[ctr].move(display);
	}
	for(ctr=0;ctr<expSIZE;ctr++)
	{
		expbullets[ctr].move(display);
	}
	if(findeffect("Missiles"))
	{
		if(rand()%3==0)
		{
			int y = rand()%30+1;
			bullet maker;
			int randnum = rand()%2;
			if(randnum==0)
			{
				maker = helpMissL;
				maker.setpos(y,-5);
			}
			else
			{
				maker = helpMissR;
				maker.setpos(y,85);
			}
			createbullet(maker);
		}
	}
	if(findeffect("Inferno"))
	{
		if(rand()%3==0)
		{
			explode(rand()%40+2,rand()%76+2,'H');
		}
	}
}

bool environment::scan(int down1, int right1, int down2, int right2)
{
	int a;
	if(down1>down2)
	{
		a = down2;
		down2 = down1;
		down1 = a;
	}
	if(right1>right2)
	{
		a = right2;
		right2 = right1;
		right1 = a;	
	}

	for(a = down1;a<=down2;a++)
	{
		for(int b = right1;b<=right2;b++)
		{
			if(display.getpoint(a,b)!=' ')
				return true;
		}
	}
	return false;
}

void environment::circle(int down1, int right1, float rad, char disp)
{
	display.circle(down1,right1,rad,disp);
}

void environment::myweapon(apstring activeweapon1)
{
	activeweapon = activeweapon1;
}

bool environment::findeffect(apstring myeffect)
{
	return envFactors.search(myeffect);
}

void environment::effect(apstring myeffect,int time)
{
	envFactors.add(myeffect);
	envFtime.resize(envFtime.length()+1);
	envFtime[envFtime.length()-1] = time;
}

void environment::updateEff()
{
	int ctr, ctr2;
	for(ctr=0;ctr<envFtime.length();ctr++)
	{
		if(envFtime[ctr]!=-1)
		{
			envFtime[ctr] = envFtime[ctr] - 1;
			if(envFtime[ctr]<=0)
			{
				if(envFactors[ctr]=="Half")
				{
					message mess;
					mess.setmessage('S');
					reg.leavemessage(reg.search("User"),mess);
				}
				envFactors.remove(envFactors[ctr]);
				for(ctr2=ctr;ctr2<envFtime.length()-1;ctr2++)
				{
					envFtime[ctr2] = envFtime[ctr2+1];
				}
			envFtime.resize(envFtime.length()-1);
			ctr--;
			}
		}
	}
}

bool environment::getkeepgo()
{return keepgo;}


int environment::getmoneyearned()
{return moneyearned;}















#endif