#include "swarm.h"
#include "levels.h"




int main()
{

  struct termios save_termios;
  set_cbreak (&save_termios);
//  noecho();
	reg.resize(202);
  system("clear");
	cout<<"Swarm: Mercenary Demo\n\nby Nathan Marz"<<endl<<endl<<endl;
	cout<<"Controls:\n\n"
		<<"arrow keys to change direction of ship\n"
		<<"x to stop\n"
		<<"z to fire\n"
		<<"shift-z to autofire\n"
		<<"a,s to cycle through weapons\n"
		<<"1 - 9 to switch weapons\n"
		<<"p to pause the game\n"
		<<"shift-q to quit\n"
		<<endl;
	cout<<"Object: don't let any of the enemies reach the bottom of the screen\n\n\n";
	cout<<"Weapons:\n\n"
		<<"Fast Guns - each bullet deals one damage but travels fast\n"
		<<"Spread Gun - fires 5 bullets spread out, each bullet deals one damage\n"
		<<"Grav Accelerator - each bullet deals 4 damage\n"
		<<"Devil Guns - each bullet deals 3 damage, 3 bullets fired\n"
		<<"DNA blaster - each bullet deals 5 damage, 800 ammo\n"
		<<"Missile Launcher - deals 1000 damage, very slow firing rate\n"
		<<"Shockwave Device - pushes all enemies back, 10 ammo\n"
		<<"Stasis Field - freezes all enemies for a short period of time\n"
		<<"Bomb Launcher - launches explosive bombs, limited ammo\n"
		<<"Centralizer - Pushes enemies to center of screen for limited time\n"
		<<"Vibration Field - Forces enemies to vibrate violently, taking damage over time\n"
		<<"Radiation Field - Causes enemies to slowly take damage over time\n"
		<<"Missile Support - Calls on the help of Allied Forces to launch a missile volley\n"
		<<"Inferno - Call on the fiery depths of hell to lay waste to your enemies\n"
		<<"Shield - Shield your ship making it take half damage for a limited time\n"
		<<"\n";
	cout<<"New in this version:\n\n"
		<<"Armor Class: some enemies have a chance of lowering damage when they get hit\n"
		<<"Collision Detection Improved\n"
		<<"New Weapon: Missile Support\n"
		<<"New Weapon: Radiation Field\n"
		<<"Fix: End of Level\n"
		<<"\n\n";
	cout<<"To Do:\n\n"
		<<"Hotkeys to certain weapons\n"
		;


  getchar();
	cout<<"\033[2J\033[1;1H";



	float SPEED = .04; //normal speed
	initialize();
	initlevels();
	user player;
	ship myship;
	char thechoose = NULL;


/*
	system("clear");
	cout<<"Choose a ship:\n"
		<<"1: Interceptor\n"
		<<"2: Frigate\n"
		<<"3: Battleship\n"
		<<endl;
	while(thechoose<'1'||thechoose>'3')
	{thechoose = getch();}
	if(thechoose=='1')
		myship = interceptor;
	if(thechoose=='2')
		myship = UFO;
	if(thechoose=='3')
		myship = battleship;
*/



	thechoose = NULL;
	system("clear");
	cout<<"Choose a speed:\n"
		<<"1: Normal\n"
		<<"2: Fast\n"
		<<"3: Ludicrous\n"
		<<endl;
	while(thechoose<'1'||thechoose>'3')
	{thechoose = getchar();}
	if(thechoose=='2')
	{
		env.setSPEED(.027);
		SPEED = .027;
	}
	if(thechoose=='3')
	{
		env.setSPEED(0);
		SPEED = 0;
	}


	level mylevel;

	mylevel.add(bomber,0,1400,6,1);
	mylevel.add(drop,0,400,200,1);
	mylevel.add(crazy,40,750,75,1);
	mylevel.add(armor,100,500,75,1);
	mylevel.add(drop,700,1000,250,2);
	mylevel.add(telep,1150,1650,30,1);
	mylevel.add(crazy,1250,1450,100,1);
	mylevel.add(cashbox,800,1400,10,2);
	mylevel.add(blip,1870,2350,70,1);
	mylevel.add(drop,1850,2370,50,1);
	mylevel.add(bomber,2630,3130,150,1);
	mylevel.add(beeswarm,3050,3750,150,2);
	mylevel.add(drop,3150,3650,200,1);
	mylevel.add(drop,3950,-1,0,0);


//	LEVEL ONE
/*
	mylevel.add(easy,0,200,50,1);
	mylevel.add(easy,200,800,100,2);
	mylevel.add(drop,500,650,100,1);
	mylevel.add(beeswarm,850,900,40,1);
	mylevel.add(easy,1150,-1,0,0);
*/

	spawner myspawn;



	srand((unsigned)time(NULL));

//game loop
	int c;
	int d=1;
	const char AUTOKEY = 'Z';
	while(d==1)
	{
		char g = ' ';
		float DELAYamt;
		c=1;
		mylevel = thelevels[player.getlevel()];
		myspawn.load(mylevel);
		myship = player.getcurrent();
		myship.create();
		mylevel.showinfo();
		env.reset();
		while(c==1)
		{
			float start = clock();
			float end;

	//keyboard input
			if(g!='Z')
				g = NULL;
			if(kbhit())
				g = getchar();
      cout << endl << endl << g << endl << endl;
			if(g=='Q')
				return 0;
			if(g=='X'&&env.getkeepgo()==false)
				break;
			if(g=='p')
			{
				cout<<DELAYamt<<flush;
				g = getchar();
			}

	//game cycle
			myspawn.go();
			env.erasebullets();
			myspawn.displayenemies();
			env.movebullets();
			if(g=='Z')
				myship.action('z');
			else
				myship.action(g);
			env.run();

	//delay for frame-rate
			end = clock();
			DELAYamt = SPEED-(end-start)/CLOCKS_PER_SEC; //modifies according to time spent doing calculations in this game cycle
			if(DELAYamt>0)
				Delay(DELAYamt);
		}
		myship.destroy();
		player.menu();
	}

	while(getchar()!='Q')
	{}
	return 0;
}
