#ifndef _SWARMCAMP_H
#define _SWARMCAMP_H


class user
{
public:
	user();
	void menu(); //accessed after battles, automatically gets cash earned from environment
	ship getcurrent();
	int getlevel();

private:
	void shipyard();
	void upgradeshop();
	void displayships();

	apvector <ship> myships;
	int activeship; //position in array
	int cash;
	int currlevel;
};



user::user()
{
	cash = 100;
	activeship = 0;
	myships.resize(1);
	myships[0]=battleship;
	currlevel = 5; //should start at 0
}

int user::getlevel()
{return currlevel;}

void user::shipyard()
{
	int ctr;
	system("clear");
	char input;
	int theprice;
	int num;
	for(ctr=0;ctr<SHIPS.length();ctr++)
	{
		cout<<ctr+1<<": "<<SHIPS[ctr].getname()<<" - "<<SHIPS[ctr].getprice()<<endl;
	}
	cout<<"e: "<<"Exit"<<endl<<endl<<endl;
	cout<<"Cash: "<<cash<<endl<<endl<<endl;
	do
	{
	input = getchar();
	num = int(input)-int('0')-1;
	if(num<0||num>SHIPS.length()-1)
		theprice = -1;
	else
		theprice = SHIPS[num].getprice();
	} while((theprice==-1||cash<theprice)&&input!='e');
	if(input=='e')
		return;
	if(cash>=theprice)
	{
		cash-=theprice;
		myships.resize(myships.length()+1);
		myships[myships.length()-1] = SHIPS[num];
	}

}

void user::upgradeshop() //precondition: all turrets on the ship that aren't active have a price >= 0
{
	system("clear");
	myships[activeship].displayupgrades();
	cout<<"e: Exit"<<endl<<endl;
	cout<<"Cash: "<<cash<<endl<<endl;
	char input;
	int theprice;
	do
	{
	input = getchar();
	theprice = myships[activeship].getturretprice(int(input)-int('0'));
	} while(input!='e'&&(theprice==-1||cash<theprice));
	if(input=='e')
		return;
	if(cash>=theprice)
	{
		cash-=theprice;
		myships[activeship].activate(int(input)-int('0'));
	}
}

void user::menu()
{
	cash+=env.getmoneyearned();
	currlevel++;
	int c = 1;
	char input;
	while(c==1)
	{
		system("clear");
		cout<<"Cash: "<<cash<<"\n\n\n";
		cout<<"1: Activate Ship\n"
			<<"2: Go to Shipyard\n"
			<<"3: Go to Upgrade Shop\n"
			<<"4: Go to Battle\n";
			;
		cout<<endl;
		do
		{
		input = getchar();
		} while(input<'1'||input>'4');
		if(input=='1')
			displayships();
		if(input=='2')
			shipyard();
		if(input=='3')
			upgradeshop();
		if(input=='4')
			break;
	}

}

void user::displayships()
{
	char input;
	system("clear");
	cout<<"Choose Ship:\n\n";
	int ctr;
	for(ctr=0;ctr<myships.length();ctr++)
	{
		cout<<ctr+1<<": "<<myships[ctr].getname()<<endl;
	}
	cout<<ctr+1<<": Exit\n";
	cout<<endl;
	do
	{
		input = getchar();
	} while(input<'1'||input>char(ctr+1+int('0')));
	if(input==char(ctr+1+int('0')))
		return;
	activeship = int(input)-int('0')-1;
	myships[int(input)-int('0')-1].displayturrets();
}

ship user::getcurrent()
{return myships[activeship];}





#endif
