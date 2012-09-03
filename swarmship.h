#ifndef _SWARMSHIP_H
#define _SWARMSHIP_H


class engine
{
public:
	engine();
	void init(int down1,int right1,picture pic1);
	void erase(int shipdown, int shipright);
	void use(int shipdown, int shipright);
	void on();
	void off();
	bool getactive();
private:
	bool ison;
	bool active;
	int down;
	int right;
	picture mypic;
};

class turret //change addbullet so you can create the bullet inside the function, instead of first making it outside
{
public:
	turret(); //set active to false, real to false
	void setpos(int down1, int right1);
	void init(int myresponse, int rate1, int cool1, int MAXammo1, apstring name1); //sets real to true
	void init(int rate1, int cool1, int MAXammo1, apstring name1); //sets real to true
	void setresponse(int resp1);
	void setname(apstring name1, int price1);
	void setprice(int price1);

	void addbullet(int down1, int right1, bullet mybull);
	void addbullet(int down1, int right1, expbullet mybull);
	void addbullet(int down1, int right1, route route1, picture pic1, char damage1);
	void addbullet(int down1, int right1, route route1, picture pic1);
//	void addexpbullet(expbullet myexpbull);
	void fire(int weaponset, int shipdown, int shipright); //gives number which weapons are set to
	void reset(); //fills with ammo, resets delay, this function is used by ship when ship is created
	void activate(int response1); //sets active to true (for upgrades and such)
	void tick(); //should be done every cycle of game, ticks down delay by 1
	int getresponse();
	bool getactive();
	bool getreal();
	int getammo();
	apstring getname();
	int getprice();
	void special(apstring myspec); //shockwave
private:
	specials myS;
	apstring name;
	int price;
	int rate; //min delay needed to fire (delay constantly ticks down to 0)
	int cool; //amount it affects the delay (i.e. adds 20)
	int delay;
	int down;
	int right;
	bool real;
	bool active;
	int ammo;
	int MAXammo; //-1 = infinite ammo
	int response; //keyboard number that this responds to (i.e. hit 2 to switch to duel guns, z to fire, 5 to switch to nukes, z to fire)
	apvector <bullet> bullets; //the bullets the turret makes in relation to position of turret on ship
	apvector <expbullet> expbullets; //the expbullets the turret makes
};

class ship //unregister after every level
{
public:
	ship(); //sets size of arrays
	void action(char input); //causes ship to do something (i.e. fire, change direction)
	void move(); //moves ship on its current route, checks to make sure it doesn't go out of bounds
	void loadpic(picture mypic1);
	void addturret(int down1, int right1, turret myturret1); //put response number here
	void addturret(int down1, int right1, turret myturret1, int responsenum);
	void nameturrets(int response1, apstring name1, int price1);
	void setHP(int myHP1);
	void setspeed(int speed1);
	void create(); //resets all turrets, HP, position, sets route to stopped, registers
	void activate(int response1); //activates all turrets with this response # (for upgrades)
	void addengine(int down1, int right1, picture myengine1);
	void init(apstring myname, int myprice);
	void displayturrets();
	void displayupgrades();
	int getturretprice(int response1);
	int getprice();
	void destroy(); //unregisters ship at end of level
	apstring getname();

private:
	void changedir(int newdir);//  0             // changes the route
							   //1 -1 3
							   //  2
	apstring name;
	int price;
	void fire();
	route myroute;
	turret myturrets[40];
	engine myengines[10];
	int weapontype; //number to search in turrets for firing
	int down;
	int right;
	picture mypic;
	int ID;
	int speed;
	int HP;
	int maxHP;
	int SIZE;
	int engSIZE;
};

engine::engine()
{
	active = false;
}

bool engine::getactive()
{return active;}

void engine::init(int down1, int right1, picture pic1)
{
	down = down1;
	right = right1;
	mypic = pic1;
	ison = false;
	active = true;
}


void engine::on()
{
	ison=true;
}

void engine::off()
{
	ison = false;
}

void engine::erase(int shipdown, int shipright)
{
	if(active==true&&ison==true)
		env.picnot(shipdown+down,shipright+right,mypic);
}

void engine::use(int shipdown, int shipright)
{
	if(ison==true&&active==true)
		env.displaypic(shipdown+down,shipright+right,mypic);
}



turret::turret()
{
	response = -1;
	active = false;
	real = false;
	price = -1;
}

void turret::setprice(int price1)
{price = price1;}

int turret::getprice()
{return price;}

void turret::setname(apstring name1, int price1)
{
	name = name1;
	price = price1;
}

int turret::getammo()
{return ammo*(bullets.length()+expbullets.length()+myS.size());}

void turret::special(apstring myspec)
{
	myS.add(myspec);
}

void turret::activate(int response1)
{
	if(response==response1)
		active = true;
}

bool turret::getreal()
{return real;}

bool turret::getactive()
{return active;}

int turret::getresponse()
{return response;}

apstring turret::getname()
{return name;}

void turret::reset()
{
	ammo = MAXammo;
	delay = 0;
}

void turret::tick()
{
	delay--;
	if(delay<0)
		delay = 0;
}

void turret::fire(int weaponset, int shipdown, int shipright)
{
	int ctr;
	bullet shell;
	expbullet expshell;
	if(active==true&&weaponset==response&&delay<=rate&&(ammo>0||ammo==-1))
	{
		if(ammo!=-1)
			ammo--;
		delay+=cool;
		for(ctr=0;ctr<bullets.length();ctr++)
		{
			shell = bullets[ctr];
			shell.setpos(shipdown+down+bullets[ctr].getdown(),shipright+right+bullets[ctr].getright());
			env.createbullet(shell);
		}
		for(ctr=0;ctr<expbullets.length();ctr++)
		{
			expshell = expbullets[ctr];
			expshell.setpos(shipdown+down+expbullets[ctr].getdown(),shipright+right+expbullets[ctr].getright());
			env.createbullet(expshell);
		}
		if(myS.search("Shockwave"))
		{
			env.effect("Shockwave",5);
		}
		if(myS.search("Super Shock"))
		{
			env.effect("Shockwave",14);
		}
		if(myS.search("Stasis"))
		{
			env.effect("Stasis",150);
		}
		if(myS.search("Vibration"))
		{
			env.effect("Vibration",200);
			env.effect("Stasis",200);
		}
		if(myS.search("Radiation"))
		{
			env.effect("Radiation",1000);
		}
		if(myS.search("Centralize"))
		{
			env.effect("Centralize",250);
		}
		if(myS.search("Missiles"))
		{
			env.effect("Missiles",320);
		}
		if(myS.search("Inferno"))
		{
			env.effect("Inferno",250);
		}
		if(myS.search("Half"))
		{
			env.effect("Half",500);
		}
	}
}

void turret::setpos(int down1, int right1)
{
	down = down1;
	right = right1;
}

void turret::addbullet(int down1, int right1, bullet mybull)
{
	mybull.setpos(down1,right1);
	bullets.resize(bullets.length()+1);
	bullets[bullets.length()-1] = mybull;
}

void turret::addbullet(int down1, int right1, expbullet mybull)
{
	mybull.setpos(down1,right1);
	expbullets.resize(expbullets.length()+1);
	expbullets[expbullets.length()-1] = mybull;
}

void turret::addbullet(int down1, int right1, route route1, picture pic1, char damage1)
{
	bullet mybull;
	mybull.init(down1,right1,route1,pic1,damage1);
	addbullet(down1,right1,mybull);
}

void turret::addbullet(int down1, int right1, route route1, picture pic1)
{
	addbullet(down1,right1,route1,pic1,'1');
}

void turret::init(int myresponse, int rate1, int cool1, int MAXammo1, apstring name1)
{
	response = myresponse;
	rate = rate1;
	cool = cool1;
	real = true;
	MAXammo = MAXammo1;
	name = name1;
}

void turret::init(int rate1, int cool1, int MAXammo1, apstring name1)
{
	init(-1,rate1,cool1,MAXammo1,name1);
}

void turret::setresponse(int resp1)
{
	response = resp1;
}




ship::ship()
{
	SIZE = 40;
	engSIZE = 10;
	speed = 1;
}

void ship::setspeed(int speed1)
{
	speed = speed1;
}

void ship::addturret(int down1, int right1, turret myturret1)
{
	addturret(down1,right1,myturret1,myturret1.getresponse());
}

void ship::addturret(int down1, int right1, turret myturret1, int responsenum)
{
	int ctr;
	for(ctr=0;myturrets[ctr].getreal()==true&&ctr<SIZE;ctr++)
	{}
	if(ctr<SIZE)
	{
		myturrets[ctr] = myturret1;
		myturrets[ctr].setresponse(responsenum);
		myturrets[ctr].setpos(down1,right1);
	}
}

void ship::addengine(int down1, int right1, picture myengine1)
{
	int ctr;
	for(ctr=0;myengines[ctr].getactive()==true&&ctr<SIZE;ctr++)
	{}
	if(ctr<SIZE)
	{
		myengines[ctr].init(down1,right1,myengine1);
	}
}

void ship::activate(int response1)
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		myturrets[ctr].activate(response1);
	}
}

void ship::create()
{
	int ctr;
	HP = maxHP;
	env.smaxHP(maxHP);
	ID = reg.registerme();
	for(ctr=0;ctr<SIZE;ctr++)
	{
		myturrets[ctr].reset();
	}
	for(ctr=0;ctr<engSIZE;ctr++)
	{
		myengines[ctr].off();
	}
	down = 39;
	right = 38;
	myroute = stop;
	weapontype = 1;
}

void ship::loadpic(picture mypic1)
{mypic = mypic1;}

void ship::setHP(int myHP1)
{maxHP = myHP1;}

void ship::action(char input)
{
	int ctr;
	int dam;
	int myrad = mypic.numrows()/2+2;
	if(mypic.numcols()/2+2>myrad)
		myrad = mypic.numcols()/2+2;
	env.picnot(down,right,mypic);
	if(env.findeffect("Half"))
	{
		env.circle(down+mypic.numrows()/2,right+mypic.numcols()/2,myrad,' ');
	}
	for(ctr=0;ctr<engSIZE;ctr++)
	{
		myengines[ctr].erase(down,right);
	}
	bool flag;
	machine mymach;
	mymach = reg.getmymessages(ID); //gets messages from registry and then clears them from there
	while(mymach.anymessages())
	{
		message mess = mymach.getmessage();
		dam = 0;
		if(mess.getmessage()<='9'&&mess.getmessage()>='1')
		{
			dam = (int(mess.getmessage())-int('0'));
		}
		if(mess.getmessage()=='K')
		{
			dam = 1000;
		}
		HP = HP - dam;
		if(env.findeffect("Half"))
		{
			HP = HP + dam/2;
			if(int(dam/2)==0)
				HP+=1;
		}
		if(mess.getmessage()=='S')
			env.circle(down+mypic.numrows()/2,right+mypic.numcols()/2,myrad,' ');
	}
	move();
	for(ctr=0;ctr<SIZE;ctr++)
	{
		myturrets[ctr].tick();
	}
			//  H
			// KPM
	if(HP>=-maxHP)
	{
		if(input=='A')
			changedir(0);
		if(input=='D')
			changedir(1);
		if(input=='B')
			changedir(2);
		if(input=='C')
			changedir(3);
		if(input=='x')
			changedir(-1);
		if(input=='z')
			fire();
		if(input>='0'&&input<='9')
		{
			int possweapontype=int(input)-'0';
			for(ctr = 0;ctr<SIZE;ctr++) //checks to see if there are any turrets with that response number
			{
				if(myturrets[ctr].getactive()==true&&myturrets[ctr].getresponse()==possweapontype)
					weapontype = possweapontype;
			}
		}
		if(input=='s')
		{
			flag = false;
			do
			{
				weapontype++;
				if(weapontype>9)
					weapontype = 0;
				for(ctr = 0;ctr<SIZE;ctr++)
				{
					if(myturrets[ctr].getactive()==true&&myturrets[ctr].getresponse()==weapontype)
						flag = true;
				}
			} while(flag==false);
		}
		if(input=='a')
		{
			flag = false;
			do
			{
				weapontype--;
				if(weapontype<0)
					weapontype = 9;
				for(ctr = 0;ctr<SIZE;ctr++)
				{
					if(myturrets[ctr].getactive()==true&&myturrets[ctr].getresponse()==weapontype)
						flag = true;
				}
			} while(flag==false);
		}
	}

	int retammo = 0;
	apstring retname;
	int thisammo;
	bool inf = false;
		for(ctr = 0;ctr<SIZE;ctr++)
		{
			if(myturrets[ctr].getactive()==true&&myturrets[ctr].getresponse()==weapontype)
			{
				thisammo = myturrets[ctr].getammo();
				retname = myturrets[ctr].getname();
				if(thisammo<0)
					inf = true;
				else
					retammo+=thisammo;
			}
		}
	if(retammo==0&&inf==true)
		env.sammo(-1);
	else
		env.sammo(retammo);
	env.myweapon(retname);
	env.sdamage(maxHP-HP);
	if(HP>=-maxHP)
	{
		if(env.findeffect("Half"))
		{
			env.circle(down+mypic.numrows()/2,right+mypic.numcols()/2,myrad,'*');
		}
		env.displaypic(down,right,mypic);
	}
	reg.update(ID,down,right,mypic,"User",-1,-1);
}

void ship::fire()
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		myturrets[ctr].fire(weapontype,down,right);
	}
}

void ship::changedir(int newdir)
{
	if(newdir==-1)
		myroute=stop;
	if(speed==1)
	{
		if(newdir==0)
			myroute=upR;
		if(newdir==2)
			myroute=downR;
		if(newdir==1)
			myroute=leftR;
		if(newdir==3)
			myroute=rightR;
	}
	if(speed==2)
	{
		if(newdir==0)
			myroute=upF;
		if(newdir==2)
			myroute=downF;
		if(newdir==1)
			myroute=leftF;
		if(newdir==3)
			myroute=rightF;
	}
}

void ship::move()
{
	int ctr;
	position next;
	int olddown, oldright;
	olddown = down;
	oldright = right;
	if(env.findeffect("Shockwave"))
	{
		down+=3;
		changedir(-1);
	}
	else
	{
		next = myroute.next();
		down = down+next.getdown();
		right = right+next.getright();
	}
	if(env.findeffect("Vibration"))
	{
		changedir(-1);
		int randnum = rand()%10;
		if(randnum==0)
			down--;
		if(randnum==1)
			down++;
		if(randnum==2)
			right--;
		if(randnum==3)
			right++;

	}
	if(down+mypic.numrows()>47)
	{
		changedir(-1);
		down = 47-mypic.numrows();
	}
	if(down<35)
	{
		changedir(-1);
		down = 35;
	}
	if(right<1)
	{
		changedir(-1);
		right=1;
	}
	if(right+mypic.numcols()>79)
	{
		changedir(-1);
		right = 79-mypic.numcols();
	}
	if(right!=oldright||down!=olddown)
	{
		for(ctr=0;ctr<engSIZE;ctr++)
		{
			myengines[ctr].on();
			myengines[ctr].use(down,right);
		}	
	}
	else
	{
		for(ctr=0;ctr<engSIZE;ctr++)
		{
			myengines[ctr].off();
		}
	}
}

void ship::destroy()
{
	reg.unregister(ID);
}

void ship::displayupgrades()
{
	int ctr, ctr2;
	cout<<name<<" Upgrades:\n\n";
	for(ctr=0;ctr<=9;ctr++)
	{
		for(ctr2=0;ctr2<SIZE;ctr2++)
		{
			if(myturrets[ctr2].getreal()==true&&myturrets[ctr2].getactive()==false&&myturrets[ctr2].getresponse()==ctr)
			{
				cout<<ctr<<": "<<myturrets[ctr2].getname()<<" - "<<getturretprice(ctr)<<endl;
				break;
			}
		}
	}

}

int ship::getturretprice(int response1)
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		if(myturrets[ctr].getresponse()==response1)
		{
			if(myturrets[ctr].getactive()==true)
				return -1;
			else
				return myturrets[ctr].getprice();
		}
	}
	return -1;
}

void ship::nameturrets(int response1, apstring name1, int price1)
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		if(myturrets[ctr].getreal()==true&&myturrets[ctr].getresponse()==response1)
		{
			myturrets[ctr].setname(name1, price1);
		}
	}
}

void ship::displayturrets()
{
	int ctr, ctr2;
	system("clear");
	cout<<name<<":\n\n";
	for(ctr=0;ctr<=9;ctr++)
	{
		for(ctr2=0;ctr2<SIZE;ctr2++)
		{
			if(myturrets[ctr2].getactive()==true&&myturrets[ctr2].getresponse()==ctr)
			{
				cout<<ctr<<": "<<myturrets[ctr2].getname()<<endl;
				break;
			}
		}
	}

	cout<<endl;
	getchar();
}

void ship::init(apstring myname, int myprice)
{
	name = myname;
	price = myprice;
}

int ship::getprice()
{return price;}

apstring ship::getname()
{return name;}









#endif