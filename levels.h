#include "swarm.h"

apvector <level> thelevels;

void initlevels()
{
	int a;

//Level 1
	thelevels.resize(thelevels.length()+1);
	a = thelevels.length()-1;
	thelevels[a].add(easy,0,200,50,1);
	thelevels[a].add(easy,200,800,100,2);
	thelevels[a].add(drop,500,650,100,1);
	thelevels[a].add(beeswarm,850,900,40,1);
	thelevels[a].add(easy,1150,-1,0,0);
	thelevels[a].loadinfo(""
				  "Welcome to the roughneck, Rookie. I hear you were a pretty good pilot back in \n"
				  "the war. Let me tell you something: that don't mean shit. Over here, we don't \n"
				  "work for no army. We're mercenaries. You take your ship, you get a spot on \n"
				  "this station to defend, and you blow the shit out of those mofos. When one\n"
				  "hits our station, we take it out of your paycheck. But every one you shoot\n"
				  "down, we give you a bonus. Got that, rookie? Now show us what you've got.");
				  

//Level 2
	thelevels.resize(thelevels.length()+1);
	a = thelevels.length()-1;
	thelevels[a].add(drop,0,500,150,1);
	thelevels[a].add(armor,100,600,8,1);
	thelevels[a].add(crazy,550,650,50,1);
	thelevels[a].add(drop,1000,-1,0,0);
	thelevels[a].loadinfo(""
				  "Not bad for your first time out rookie. But your ship is outdated and \n"
				  "ridiculous. Let's see how you handle this next challenge.");

//Level 3
	thelevels.resize(thelevels.length()+1);
	a = thelevels.length()-1;
	thelevels[a].add(armor,0,1000,10,1);
	thelevels[a].add(drop,30,1100,80,1);
	thelevels[a].add(drop,1320,-1,0,0);
	thelevels[a].loadinfo(""
				  "You think you're some sort of hot shot now? Well no matter how many you kill,\n"
				  "they'll just keep coming and coming. And it looks like they're coming right\n"
				  "now, full force. Get your sorry ass back out there.");

//Level 4
	thelevels.resize(thelevels.length()+1);
	a = thelevels.length()-1;
	thelevels[a].add(cashbox,0,800,8,1);
	thelevels[a].add(armor,0,500,8,1);
	thelevels[a].add(easy,860,-1,0,0);
	thelevels[a].loadinfo(""
				  "You got lucky, rookie. Our advance fighters knocked out one of their supply\n"
				  "ships. The enemy launched the little they had left at us. Some of what they\n"
				  "launched happens to have a nice bounty price for you. So what the hell are you\n"
				  "doing here talking to me?");

//Level 5
	thelevels.resize(thelevels.length()+1);
	a = thelevels.length()-1;
	thelevels[a].add(cashbox,0,600,4,1);
	thelevels[a].add(bomber,0,800,5,1);
	thelevels[a].add(crazy,0,400,110,1);
	thelevels[a].add(armor,50,500,15,2);
	thelevels[a].add(telep,400,700,4,1);
	thelevels[a].add(drop,1100,-1,0,0);
	thelevels[a].loadinfo(""
				  "I'll admit it, you sorry little punk. You're good. You've got skills I've only\n"
				  "seen in one other person, me. But you still got a long way to go. When I was\n"
				  "your age, I was shooting down Battlecruisers in the famous battle at Tulan \n"
				  "Port. But that doesn't matter for you. You'll probably get toasted long before\n"
				  "you ever get to see your first Battlecruiser.");

	level mylevel;//

	mylevel.add(bomber,0,1400,6,1);//
	mylevel.add(drop,0,400,200,1);//
	mylevel.add(crazy,40,750,75,1);//
	mylevel.add(armor,100,500,75,1);//
	mylevel.add(drop,700,1000,250,2);//
	mylevel.add(telep,1150,1650,30,1);//
	mylevel.add(crazy,1250,1450,100,1);//
	mylevel.add(cashbox,800,1400,10,2);//
	mylevel.add(blip,1870,2350,70,1);//
	mylevel.add(drop,1850,2370,50,1);//
	mylevel.add(bomber,2630,3130,150,1);//
	mylevel.add(beeswarm,3050,3750,150,2);//
	mylevel.add(drop,3150,3650,200,1);//
	mylevel.add(drop,3950,-1,0,0);//


//Level 6
	thelevels.resize(thelevels.length()+1);
	a = thelevels.length()-1;
	thelevels[a].add(bomber,0,2000,6,1);
	thelevels[a].add(easy,0,200,50,1);
	thelevels[a].add(drop,20,400,300,1);
	thelevels[a].add(crazy,380,1000,300,1);
	thelevels[a].add(telep,1100,1400,20,1);
	thelevels[a].add(armor,1600,2000,120,1);
	thelevels[a].add(drop,2450,-1,0,0);

	thelevels[a] = mylevel; //

	thelevels[a].loadinfo(""
				  "Oh, you think cause you held off a light attack you're some sort of ace pilot\n"
				  "now? Well, I got news for you rookie. We picked up some transmissions. They're\n"
				  "coming in, and they're coming in strong. Get a move on, mercenary!");

}