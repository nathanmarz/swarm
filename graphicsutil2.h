#ifndef _CONGRAPHICSUTIL_H
#define _CONGRAPHICSUTIL_H

#include "graphics.h"
#include "apvector.h"
#include "apstring.h"

class message
{
public:
	void setmessage(char mymess);
	void setID(int myID);
	void setpt1(int down, int right);
	void setpt2(int down, int right);
	char getmessage();
	int getsenderID();
	int getdown1();
	int getright1();
	int getdown2();
	int getright2();
	void operator = (char mymess);
private:
	char themess;
	int senderID;
	int down1;
	int right1;
	int down2;
	int right2;
};

void message::operator =(char mymess)
{
	themess = mymess;
}

class machine
{
public:
	void addmessage(message mymess);
	message getmessage();  //returns last message given and deletes it from the machine
	bool anymessages(); //returns true if any message is in the machine, false if their are no messages
	void clear(); //clears all messages from the machine
private:
	apvector <message> themessages;
};


class data
{
public:
	data();
	void activate();
	void unactivate();
	bool getactivate();
	void setID(int theID);
	int getID();
	int inrange(int down1, int right1); //0 if not at all, 1 if inside rectangular range, 2 if hits a non-masked point inside range
	void update(int down1, int right1, picture pic, apstring type, int dir, int speed);
	int getdown();
	int getright();
	apstring gettype();
	int getdir();
	int getspeed();

// exactly the same as directly accessing messages
	void addmessage(message mymess);
	message getmessage();
	bool anymessages();

	picture getpic();
	machine getmymessages(); //returns answering machine and clears the machine from data
private:
	bool activated;
	int ID;
	picture mypic;
	machine mymessages;
	int down;
	int right;
	apstring mytype;
	int dir; // 0 
			 //1 3
			 // 2
	int speed;
};

bool data::getactivate()
{return activated;}

data::data()
{
	activated = false;
}

void data::activate()
{
	activated = true;
}

void data::unactivate()
{
	activated = false;
}


class registry //recommended that all objects contain data object with all info inside and NO messages, use getmymessages routine and update with object's data
{
public:
	int size(); //returns size of the registry
	void resize(int mysize);
//	void clear();

	int registerme(); //puts object into the registry and returns it's specific ID which identifies it (MUST be stored within the object to access it's messages inside the registry)
	void unregister(int myID); //takes this ID out of the registry (use when this object is being removed)

//returns pos inside registry array of what exists there, -1 if it can't find anything
	int search(int down1, int right1); //starts at pos ==0
	int search(apstring type); // starts at pos==0
	int search(int down1, int right1, apstring type);
	int search(int startpos, int down1, int right1);
	int search(int startpos, apstring type);
	int search(int startpos, int down1, int right1, apstring type);
	bool searchall(int down1, int right1, apstring type); //tells if there is anthing in the registry with these characteristics
	bool searchallnot(int down1, int right1, apvector <apstring> types); //tells if there is anything at that position that is not of these types


	void leavemessage(int pos, message mess);
	void leavemessage(int down1, int right1, message mess); //leaves message to all at that specific point
	void leavemessage(apstring type, message mess); //leaves message to all with that specific type
	void leavemessage(int down1, int right1, apstring type, message mess);
	machine getmymessages(int myID); //gets messages and clears them from data inside registry

	data retrieve(int ID);

	void update(int myID, data mydata);
	void update(int myID, int down1, int right1, picture mypic, apstring type, int dir, int speed);
private:
	apvector <data> thedata;
};




// whenever an object enters a field of interaction, it should register itself into the registry.
//  i.e.
//  void object::init()
// {
// 	ID = reg.registerme();
//  //other init code
// }
// an object should constantly update the registry with it's data for use by other objects.
// an object should constantly check its messages and respond to them
//
//
//message loop (Optimal way to check messages and respond to them):
//
//		machine mymach;
//		mymach = reg.getmymessages(myID); //gets messages from registry and then clears them from there
//		while(mymess.anymessages())
//		{
//		 message mess = mymach.getmessage();
//		//stimulus to different messages goes here
//		//i.e. if(mess.getmessage()=='C') dosomething();
//		}

void message::setID(int myID)
{ senderID = myID; }

void message::setmessage(char mymess)
{ themess = mymess; }

void message::setpt1(int down, int right)
{ down1 = down; right1 = right; }

void message::setpt2(int down, int right)
{ down2 = down; right2 = right; }

int message::getdown1()
{ return down1; }

int message::getdown2()
{ return down2; }

int message::getright1()
{ return right1; }

int message::getright2()
{ return right2; }

int message::getsenderID()
{ return senderID; }

char message::getmessage()
{ return themess; }


void machine::addmessage(message mymess)
{
	themessages.resize(themessages.length()+1);
	themessages[themessages.length()-1] = mymess;
}

message machine::getmessage()
{
	if(themessages.length()>=1)
	{
	message returnmess = themessages[themessages.length()-1];
	themessages.resize(themessages.length()-1);
	return returnmess;
	}
	message NULLmess;
	NULLmess.setmessage(NULL);
	NULLmess.setID(-1);
	return NULLmess;
}

bool machine::anymessages()
{
	if(themessages.length()>0)
		return true;
	else
		return false;
}

void machine::clear()
{
	themessages.resize(0);
}



void data::addmessage(message mymess)
{
	mymessages.addmessage(mymess);
}

message data::getmessage()
{
	return mymessages.getmessage();
}

bool data::anymessages()
{
	return mymessages.anymessages();
}

int data::inrange(int down1, int right1)
{
	if(down1<down||right1<right||down1>down+mypic.numrows()-1||right1>right+mypic.numcols()-1)
		return 0;
	if(mypic.mypic[down1-down][right1-right]!=mypic.getmask())
		return 2;
	else
		return 1;
}

void data::setID(int theID)
{
	ID = theID;
}

void data::update(int down1, int right1, picture pic, apstring type, int thedir, int thespeed)
{
	down = down1;
	right = right1;
	mypic = pic;
	mytype = type;
	dir = thedir;
	speed = thespeed;
}

machine data::getmymessages()
{
	machine returnmess = mymessages;
	mymessages.clear();
	return returnmess;
}

int data::getdir()
{	return dir; }

int data::getdown()
{	return down; }

int data::getright()
{	return right; }

int data::getID()
{	return ID; }

picture data::getpic()
{	return mypic; }

int data::getspeed()
{	return speed; }

apstring data::gettype()
{	return mytype; }


int registry::size()
{
	return thedata.length();
}

void registry::resize(int mysize)
{
	thedata.resize(mysize);
	for(int ctr=0;ctr<thedata.length();ctr++)
	{
		thedata[ctr].unactivate();
	}
}

int registry::registerme()
{
	data newinput;
	int IDtogive;
	for(IDtogive=0;IDtogive<thedata.length();IDtogive++)
	{
		if(thedata[IDtogive].getactivate()==false)
		{
			newinput.setID(IDtogive);
			newinput.activate();
			thedata[IDtogive] = newinput;
			return IDtogive;
		}
	}
	return -1;
}

void registry::unregister(int myID)
{
	if(myID>=0&&myID<thedata.length())
	{
		data NULLdata;
		thedata[myID] = NULLdata;
		thedata[myID].unactivate();
	}
}

//	int search(int down1, int right1);
//	int search(apstring type);
//	int search(int startpos, int down1, int right1);
//	int search(int startpos, apstring type);

int registry::search(int startpos, int down1, int right1)
{
	int ctr;
	for(ctr = startpos;ctr<thedata.length();ctr++)
	{
		int num = thedata[ctr].inrange(down1,right1);
		if(num==2)
			return ctr;
	}
	return -1;
}

int registry::search(int startpos, int down1, int right1, apstring type)
{
	int ctr;
	for(ctr = startpos;ctr<thedata.length();ctr++)
	{
		int num = thedata[ctr].inrange(down1,right1);
		if(num==2&&thedata[ctr].gettype()==type)
			return ctr;
	}
	return -1;
}

int registry::search(int down1, int right1, apstring type)
{
	int num = search(0,down1,right1,type);
	return num;
}

int registry::search(int down1, int right1)
{
	int num = search(0,down1,right1);
	return num;
}

int registry::search(int startpos, apstring type)
{
	int ctr;
	for(ctr = startpos;ctr<thedata.length();ctr++)
	{
		if(thedata[ctr].gettype()==type)
			return ctr;
	}
	return -1;
}

int registry::search(apstring type)
{
	int num = search(0,type);
	return num;
}


bool registry::searchall(int down1, int right1, apstring type)
{
	int ctr;
	for(ctr=0;ctr<thedata.length();ctr++)
	{
		if(thedata[ctr].gettype()==type&&thedata[ctr].inrange(down1,right1)==2)
			return true;
	}
	return false;
}

bool registry::searchallnot(int down1, int right1, apvector <apstring> types)
{
	int ctr;
	int flag;
	for(ctr=0;ctr<thedata.length();ctr++)
	{
		if(thedata[ctr].inrange(down1,right1)==2)
		{
			flag = 1;
			for(int ctr2=0;ctr2<types.length();ctr2++)
			{
				if(thedata[ctr].gettype()==types[ctr2])
					flag = 0;
			}
			if(flag==1)
				return true;
		}
	}
	return false;
}

//	void leavemessage(int pos, char mess);
//	machine getmymessages(int myID);

void registry::leavemessage(int pos, message mess)
{
	if(pos>=0&&pos<thedata.length())
	{
		thedata[pos].addmessage(mess);
	}
}

void registry::leavemessage(int down1, int right1, message mess)
{
int thepos = -1;
do
{
	thepos = search(thepos+1,down1,right1);
	if(thepos!=-1)
		leavemessage(thepos,mess);
} while(thepos!=-1);
}

void registry::leavemessage(apstring type, message mess)
{
int thepos = -1;
do
{
	thepos = search(thepos+1,type);
	if(thepos!=-1)
		leavemessage(thepos,mess);
} while(thepos!=-1);
}

void registry::leavemessage(int down1, int right1, apstring type, message mess)
{
int thepos = -1;
do
{
	thepos = search(thepos+1,down1,right1,type);
	if(thepos!=-1)
		leavemessage(thepos,mess);
} while(thepos!=-1);
}


machine registry::getmymessages(int myID)
{
	if(myID>=0&&myID<thedata.length())
		return thedata[myID].getmymessages();
	machine NULLmach;
	return NULLmach;
	
}

//	data retrieve(int pos);
//	data myretrieve(int myID);

data registry::retrieve(int pos)
{
	if(pos>=0&&pos<thedata.length())
	{
		return thedata[pos];
	}
	data NULLdata;
	return NULLdata;
}


//	void update(int myID, data mydata);
//	void update(int myID, int down1, int right1, picture mypic, apstring type, int dir, int speed);

void registry::update(int myID, data mydata)
{
	if(myID>=0&&myID<thedata.length())
		thedata[myID] = mydata;	
}

void registry::update(int myID, int down1, int right1, picture mypic, apstring type, int dir, int speed)
{
	if(myID>=0&&myID<thedata.length())	
		thedata[myID].update(down1,right1,mypic,type,dir,speed);
}
/*
void registry::clear()
{
	int SIZE = thedata.length();
	thedata.resize(0);
	resize(SIZE);
}
*/
#endif