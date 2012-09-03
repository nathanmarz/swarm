#ifndef _SWARMSPAWN_H
#define _SWARMSPAWN_H

class ldata
{
public:
	void load(enemy myenemy1, int timeS1, int timeE1, int rate1, int spawnamt1);
	enemy getenemy();
	int gettimeStart();
	int gettimeEnd();
	int getrate();
	int getspawnamt();
private:
	enemy myenemy;
	int timeStart;//time to switch to this spawn rate (0 at start)
	int timeEnd;//times to stop this spawn
	int rate;//number to spawn if rand number comes up <=rate
	int spawnamt;//number to spawn if rand number comes up <=rate
};


class level
{
public:
	level(); //resets pos to 0
	void add(enemy myenemy1, int timeS1, int timeE1, int rate1, int spawnamt1);
	ldata get(int time); //gets 1st occurence of spawn attempt in data, sets pos so no repeat   returns a NULL ldata (timeS==-1) if none left, automatically resets pos at this point
	void loadinfo(apstring myinfo);
	void showinfo();
private:
	apstring info;
	int pos;
	apvector<ldata> thelevel;
};

class spawner
{
public:
	spawner();
	void go();
	void displayenemies();
	void load(level thelevel1);
private:
	bool anyenemies();
	level thelevel;
	void moveall(); //moves all enemies
	void createenemy(enemy thenemy);
	int SIZE;
	int time;
	int enemyPOS;
	enemy enemies[200];
};




void ldata::load(enemy myenemy1, int timeS1, int timeE1, int rate1, int spawnamt1)
{
	myenemy = myenemy1;
	timeStart = timeS1;
	timeEnd = timeE1;
	rate = rate1;
	spawnamt = spawnamt1;
}

enemy ldata::getenemy()
{return myenemy;}

int ldata::gettimeStart()
{return timeStart;}

int ldata::gettimeEnd()
{return timeEnd;}

int ldata::getrate()
{return rate;}

int ldata::getspawnamt()
{return spawnamt;}




level::level()
{
	pos = 0;
}

void level::add(enemy myenemy1, int timeS1, int timeE1, int rate1, int spawnamt1)
{
	thelevel.resize(thelevel.length()+1);
	thelevel[thelevel.length()-1].load(myenemy1,timeS1,timeE1,rate1,spawnamt1);
}

ldata level::get(int time)
{
	for(pos;pos<thelevel.length();pos++)
	{
		if(time>=thelevel[pos].gettimeStart()&&(time<=thelevel[pos].gettimeEnd()||thelevel[pos].gettimeEnd()==-1))
		{
			pos++;
			return thelevel[pos-1];
		}
	}
	ldata NULLldata;
	enemy NULLenemy;
	NULLldata.load(NULLenemy,-1,-1,-1,-1);
	pos = 0;
	return NULLldata;
}

void level::loadinfo(apstring myinfo)
{
	info = myinfo;
}

void level::showinfo()
{
	if(info.length()==0)
		return;
	system("clear");
	cout<<info<<endl;
	getchar();
}



spawner::spawner()
{
	enemyPOS = 0;
	SIZE = 200;
}

void spawner::load(level thelevel1)
{
	thelevel = thelevel1;
	time = 0;
}

void spawner::go()
{
	if(!env.findeffect("Stasis")&&!env.findeffect("Shockwave"))
	{
		time++;
		int num;
		int ctr;
		ldata myspawn;
		myspawn = thelevel.get(time);
		while(myspawn.gettimeStart()!=-1)
		{
			if(myspawn.gettimeEnd()==-1)
			{
				if(!anyenemies())
					env.stop();
				else
					time--;
				break;
			}
			num = rand()%1000;
			if(num<=myspawn.getrate())
			{
				for(ctr=0;ctr<myspawn.getspawnamt();ctr++)
				{
					createenemy(myspawn.getenemy());
				}
			}
			myspawn = thelevel.get(time);
			}
		}
		moveall();
		enemyPOS = 0;
}

void spawner::createenemy(enemy theenemy)
{
	int ctr;
	int maxright = 79-theenemy.width()-theenemy.getmaxright();
	int maxleft = 1 + theenemy.getmaxleft();
	int num = rand()%(maxright-maxleft);
	theenemy.create(-5,maxleft+num);
	for(ctr=enemyPOS;ctr<SIZE;ctr++)
	{
		if(enemies[ctr].getalive()==false)
		{
			enemies[ctr] = theenemy;
			break;
		}
	}
	enemyPOS = ctr;
}

void spawner::moveall()
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		enemies[ctr].move();
	}
}

void spawner::displayenemies()
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		enemies[ctr].display();
	}
}

bool spawner::anyenemies()
{
	int ctr;
	for(ctr=0;ctr<SIZE;ctr++)
	{
		if(enemies[ctr].getalive()==true)
			return true;
	}
	return false;
}



#endif