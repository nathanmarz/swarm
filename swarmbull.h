#ifndef _SWARMBULL_H
#define _SWARMBULL_H



class bullet
{
public:
	bullet();
	void init(int down1, int right1, route route1, picture pic1, char damage1);
	void init(int down1, int right1, route route1, picture pic1);
	void erase(screen &display);
	void move(screen &display);
	bool getalive();
	void display(screen &display);
	void setpos(int down1, int right1); //used when deciding position relative to turret
	int getdown();
	int getright();
	void destroy();
protected:
	virtual	void collide(int hit);
	bool alive;
	int down;
	int right;
	route myroute;
	picture mypic;
private:
	char damage;
};

class expbullet:public bullet
{
public:
	expbullet();
	void settype(char exptype1); //default = 'E', others are 'H', and 'N'
private:
	void collide(int hit);
	char exptype;
};


bullet::bullet()
{
	alive = false;
}

bool bullet::getalive()
{return alive;}

void bullet::init(int down1, int right1, route route1, picture pic1)
{
	init(down1,right1,route1,pic1,'1');
}

void bullet::init(int down1, int right1, route route1, picture pic1, char damage1)
{
	damage = damage1;
	down = down1;
	right = right1;
	myroute = route1;
	mypic = pic1;
	alive = true;
}

void bullet::erase(screen &display)
{
	if(alive==false)
		return;
	display.picnot(down,right,mypic);
	position next = myroute.next();
	down = down+next.getdown();
	right = right+next.getright();
}

int bullet::getdown()
{return down;}

int bullet::getright()
{return right;}

void bullet::setpos(int down1, int right1)
{
	down = down1;
	right = right1;
}

void bullet::move(screen &display)
{
	int x,y;
	if(alive==false)
		return;
	if(down>60||down+mypic.numrows()<-10||right+mypic.numcols()<-4||right>84)
		alive = false;

		for(x=0;x<mypic.numrows();x++)
		{
			for(y=0;y<mypic.numcols();y++)
			{
				if(alive==false)
					break;
//				if(mypic.mypic[x][y]!=mypic.getmask())
//				{
					if(display.getpoint(down+x,right+y)!=' '&&display.getpoint(down+x,right+y)!=NULL)
					{
						int hit = reg.search(down+x,right+x);
						if(hit!=-1)
						{
							alive = false;
							collide(hit);
							break;
						}
					}
//				}
			}
			if(alive==false)
				break;
		}

	if(alive==true&&down<48)
		display.displaypic(down,right,mypic);
}

void bullet::collide(int hit)
{
	message themess;
	themess.setmessage(damage);
	themess = damage;
	reg.leavemessage(hit,themess);
}

void bullet::destroy()
{
	alive = false;
}


void bullet::display(screen &display)
{
	display.displaypic(down,right,mypic);
}


expbullet::expbullet()
{
	exptype = 'E';
	alive = false;
}

void expbullet::settype(char exptype1)
{
	exptype = exptype1;
}


void expbullet::collide(int hit)
{
	Explode(down+mypic.numrows()/2,right+mypic.numcols()/2,exptype);
}




#endif