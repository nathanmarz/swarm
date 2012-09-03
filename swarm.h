#ifndef _SWARM_H
#define _SWARM_H

#include "graphics.h"
#include "graphicsutil2.h"
#include <time.h>
#include <stdlib.h>
#include "getche.h"
#include <curses.h>
#include "cbreak.h"

/*
todo:

1. more routes
2. multiple buyable ships with engines and turrets
3. a high score table ranked according to how far each player got into the game
4. you lose the game if you go bankrupt since eventually the game will get so difficult with the swarms 
   that you'll be netting negative money every swarm wave (b/w waves you buy stuff, and eventually all your money 
   will go to below 0
5. Nukes (create high explosive bombs)  hardcode the bullets a nuke makes
6. have certain enemies explode differently when they kamikaze than when shot down!
7. Enemies that fire back
8. Implement "Special" coding into enemies and routines through it to implement special enemies (like health packs)

*/

registry reg;
void initialize();
void initweapons();
void initships();
void Explode(int down, int right, char exptype);

#include "graphaccess.h"

route downVS, downS, downR, downF, downVF, leftF, rightF;
route upR, upF, rightR, leftR, northER, northWR, southWR, southER, upVF;
route diag, spiral, backNforth, backNforthDel, stop;
route northENR, northWNR;
route backarchR, backarchL, frontarchR, frontarchL;
route helixR, helixL;
route teleR;
route beesR;

#include "swarmbull.h"

#include "swarmenv.h"


environment env;

#include "swarmenemy.h"

#include "swarmspawn.h"

#include "swarmship.h"

apvector <ship> SHIPS;
ship interceptor, UFO, battleship;
ship fieldship;

#include "swarmcamp.h"






bullet fastB, northWRB, upRB, northERB, northENRB, northWNRB;
bullet archRB, archLB;

enemy easy;
enemy drop, armor, crazy, telep, bomber, cashbox, blip, beeswarm;

turret fastT, spreadT, backarchTL, backarchTR, devilT, DNAT, missileT, shockwaveT;
turret supershockT;
turret stasisT;
turret bombT;
turret vibrT;
turret centrT;
turret radiatT;
turret misshelpT;
turret infernoT;
turret halfshieldT;


void Explode(int down, int right, char exptype)
{
		env.explode(down,right,exptype);
}



void initialize()
{
//routes
	
	downVS = "S";
	downVS = "7";
	downVS = "E";
	downVS.reset();

	downS = "S";
	downS = "2";
	downS = "E";
	downS.reset();

	downR = "S";
	downR = ".";
	downR = "E";
	downR.reset();

	downF = "S";
	downF = "*";
	downF = ".";
	downF = "E";
	downF.reset();

	downVF = "S";
	downVF = "*";
	downVF = "*";
	downVF = ".";
	downVF = "E";
	downVF.reset();

	upR = "E";
	upR = ".";
	upR = "S";
	upR.reset();

	upF = "E";
	upF = ".";
	upF = "*";
	upF = "S";
	upF.reset();

	upVF = "E";
	upVF = ".";
	upVF = "*";
	upVF = "*";
	upVF = "S";
	upVF.reset();

	rightR = "S.E";
	rightR.reset();

	leftF = "E.*S";
	leftF.reset();

	rightF = "S*.E";
	rightF.reset();

	leftR = "E.S";
	leftR.reset();

	stop = "   ";
	stop = " S ";
	stop = "   ";
	stop.reset();

	northER = "  E";
	northER = " . ";
	northER = "S  ";
	northER.reset();

	northWR = "E  ";
	northWR = " . ";
	northWR = "  S";
	northWR.reset();

	southER = "S  ";
	southER = " . ";
	southER = "  E";
	southER.reset();

	southWR = "  S";
	southWR = " . ";
	southWR = "E  ";
	southWR.reset();

	northENR = "  E";
	northENR = " . ";
	northENR = " . ";
	northENR = "S  ";
	northENR.reset();

	northWNR = "E  ";
	northWNR = " . ";
	northWNR = " . ";
	northWNR = "  S";
	northWNR.reset();

	backarchR = "        C";
	backarchR = "        .";
	backarchR = "S       *";
	backarchR = ".      . ";
	backarchR = ".      * ";
	backarchR = " .   *.  ";
	backarchR = "  *..    ";
	backarchR.reset();
 
	backarchL = "C        ";
	backarchL = ".        ";
	backarchL = "*       S";
	backarchL = " .      .";
	backarchL = " *      .";
	backarchL = "  .*   . ";
	backarchL = "    ..*  ";
	backarchL.reset();

	frontarchR = "      C";
	frontarchR = "      .";
	frontarchR = "     * ";
	frontarchR = "     * ";
	frontarchR = "     . ";
	frontarchR = "     * ";
	frontarchR = "    .  ";
	frontarchR = "  *.   ";
	frontarchR = "S.     ";
	frontarchR.reset();

	frontarchL = "C      ";
	frontarchL = ".      ";
	frontarchL = " *     ";
	frontarchL = " *     ";
	frontarchL = " .     ";
	frontarchL = " *     ";
	frontarchL = "  .    ";
	frontarchL = "   .*  ";
	frontarchL = "     .S";
	frontarchL.reset();


	diag = "S        ";
	diag = " 11      ";
	diag = "   11    ";
	diag = "     11  ";
	diag = "       2 ";
	diag = "     11  ";
	diag = "   11    ";
	diag = " 11      ";
	diag = "1        ";
	diag = " E       ";
	diag.reset();

	spiral = "    .......    ";
	spiral = "   .       .   ";
	spiral = "  .  .....  .  ";
	spiral = " .  .     .  . ";
	spiral = " . .  ...  . . ";
	spiral = " . . .   . . . ";
	spiral = " . . . S.  . . ";
	spiral = " . . .    .  . ";
	spiral = " . .  ....  .  ";
	spiral = " .  .      .   ";
	spiral = "  .  ......    ";
	spiral = "   .           ";
	spiral = "    ....E      ";
	spiral.reset();

	helixR = "      **.E          ";
	helixR = "    *.              ";
	helixR = "  *.                ";
	helixR = " .                  ";
	helixR = " .                  ";
	helixR = " .                  ";
	helixR = "  .*                ";
	helixR = "    .*              ";
	helixR = "      .**           ";
	helixR = "         .*.**      ";
	helixR = "              .*    ";
	helixR = "                .*  ";
	helixR = "                  . ";
	helixR = "                  . ";
	helixR = "                  . ";
	helixR = "                *.  ";
	helixR = "              *.    ";
	helixR = "           **.      ";
	helixR = "         S.         ";
	helixR.reset();

	helixL = "          E.**      ";
	helixL = "              .*    ";
	helixL = "                .*  ";
	helixL = "                  . ";
	helixL = "                  . ";
	helixL = "                  . ";
	helixL = "                *.  ";
	helixL = "              *.    ";
	helixL = "           **.      ";
	helixL = "      **.*.         ";
	helixL = "    *.              ";
	helixL = "  *.                ";
	helixL = " .                  ";
	helixL = " .                  ";
	helixL = " .                  ";
	helixL = "  .*                ";
	helixL = "    .*              ";
	helixL = "      .**           ";
	helixL = "         .S         ";
	helixL.reset();

	teleR = "                         ";
	teleR = "                  9      ";
	teleR = "                 **      ";
	teleR = "    S           * *      ";
	teleR = "     *         *  *      ";
	teleR = "   ************   *      ";
	teleR = "    9  *          *      ";
	teleR = "     *  *          *     ";
	teleR = "     *   9*******   *    ";
	teleR = "     ***        *    *   ";
	teleR = "       *         ****9   ";
	teleR = "9**************          ";
	teleR = " *     *       *         ";
	teleR = "  *  E9******   *        ";
	teleR = "   *   *     *   ******  ";
	teleR = "   *   *      9        * ";
	teleR = "    * *        *********9";
	teleR = "     9                   ";
	teleR.reset();

	beesR = "                ";
	beesR = "  S..    ...1   ";
	beesR = "     1  1    1  ";
	beesR = " 1.E . 1     .  ";
	beesR = ".     1      1  ";
	beesR = ".    1 1    1   ";
	beesR = "1   1   1..1    ";
	beesR = " ..1            ";
	beesR = "                ";
	beesR.reset();

	backNforthDel = "S.........*.*.*.............M.............*.*.*.........5 ";
	backNforthDel = "                                                         1";
	backNforthDel = " 5.........*.*.*.............M.............*.*.*........1 ";
	backNforthDel = "1                                                         ";
	backNforthDel = "1E                                                        ";
	backNforthDel.reset();

	backNforth = "S........................................................... "; // 60 spaces back n forth
	backNforth = "                                                            1";
	backNforth = " ..........................................................1 ";
	backNforth = "1                                                            ";
	backNforth = "1E                                                           ";
	backNforth.reset();

//enemies

	picture pic;
	pic.setmask('Q');

	pic.clear();
	pic = "--";
	pic = "\\/";
	drop.init(2,diag);
	drop.setspeed(2);
	drop.addAnim(pic,7);
	pic.clear();
	pic = "/|";
	pic = "\\|";
	drop.addAnim(pic,7);
	pic.clear();
	pic = "/\\";
	pic = "--";
	drop.addAnim(pic,7);
	pic.clear();
	pic = "|\\";
	pic = "|/";
	drop.addAnim(pic,7);
	drop.setworth(5,20);

	pic.clear();
	pic = "QQQQQQQ";
	pic = "QQQQQQQ";
	pic = "QQQQQQQ";
	pic = "QQQ.QQQ";
	pic = "QQQQQQQ";
	pic = "QQQQQQQ";
	pic = "QQQQQQQ";
	blip.init(20,downS);
	blip.addAnim(pic,8);
	pic.clear();
	pic = "QQQQQQQ";
	pic = "QQQQQQQ";
	pic = "QQQ.QQQ";
	pic = "QQ. .QQ";
	pic = "QQQ.QQQ";
	pic = "QQQQQQQ";
	pic = "QQQQQQQ";
	blip.addAnim(pic,5);
	pic.clear();
	pic = "QQQQQQQ";
	pic = "QQQ.QQQ";
	pic = "QQ. .QQ";
	pic = "Q.   .Q";
	pic = "QQ. .QQ";
	pic = "QQQ.QQQ";
	pic = "QQQQQQQ";
	blip.addAnim(pic,5);

	pic.clear();
	pic = "QQ...QQ";
	pic = "Q.   .Q";
	pic = ".     .";
	pic = ".     .";
	pic = ".     .";
	pic = "Q.   .Q";
	pic = "QQ...QQ";
	blip.addAnim(pic,10);
	blip.setworth(20,50);




	pic.clear();
	pic = "Q()Q";
	pic = "(())";
	pic = "Q()Q";
	telep.init(40,pic,teleR);
	telep.setworth(40,110);
	telep.setarmor(1,500);

	pic.clear();
	pic = "____";
	pic = "\\  /";
	pic = "Q^^Q";
	easy.init(3,downS);
	easy.addAnim(pic,14);
	easy.setworth(3,15);
	pic.clear();
	pic = "____";
	pic = "\\**/";
	pic = "Q^^Q";
	easy.addAnim(pic,14);

	pic.clear();
	pic = "Q_Q";
	pic = "| |";
	pic = "\\_/";
	bomber.init(500,pic,downS);
	bomber.setworth(5,8);
	bomber.special("High Explosive");

	pic.clear();
	pic = "$-$";
	pic = "|$|";
	pic = "$-$";
	cashbox.init(15,pic,downS);
	cashbox.setworth(100,0);

	pic.clear();
	pic = "Q(_)Q";
	pic = ">-+-<";
	pic = "Q/-\\Q";
	crazy.init(8,pic,spiral);
	crazy.setworth(5,50);
	crazy.setspeed(2);

	beeswarm.init(16,diag);
	beeswarm.setworth(10,50);
	beeswarm.setspeed(1);
	beeswarm.special("Non-Explosive");
	pic.clear();
	pic = " .  .";
	pic = "     ";
	pic = ".    ";
	pic = "   . ";
	pic = " .   ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "  .  ";
	pic = " . . ";
	pic = "     ";
	pic = " ..  ";
	pic = "     ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "     ";
	pic = "  .. ";
	pic = "...  ";
	pic = "     ";
	pic = "     ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = " .   ";
	pic = " .  .";
	pic = "  .. ";
	pic = "     ";
	pic = "     ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "     ";
	pic = ".  . ";
	pic = "  . .";
	pic = "   . ";
	pic = "     ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "  .  ";
	pic = "  .  ";
	pic = ".    ";
	pic = "    .";
	pic = "  .  ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "     ";
	pic = " ..  ";
	pic = "     ";
	pic = ".    ";
	pic = " . . ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "  .  ";
	pic = "     ";
	pic = "  .  ";
	pic = " ..  ";
	pic = ".    ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "     ";
	pic = "   . ";
	pic = "  .  ";
	pic = ".. . ";
	pic = "     ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "     ";
	pic = "  .  ";
	pic = ". .. ";
	pic = "     ";
	pic = "   . ";
	beeswarm.addAnim(pic,2);
	pic.clear();
	pic = "     ";
	pic = ".   .";
	pic = "     ";
	pic = ". .  ";
	pic = "  .  ";
	beeswarm.addAnim(pic,2);






	pic.clear();
	pic = "Q/________\\Q";
	pic = "/----------\\";
	armor.init(35,pic,downVS);
	armor.setworth(5,20);
	armor.setarmor(1,500);


//bullets ; fastB, northWRB, upRB, northERB, northENRB, northWNRB;


	pic.clear();
//	pic = "Q";
	pic = "\"";
	pic = "\"";
	fastB.init(0,0,upF,pic);

	pic.clear();
	pic = "Q\\QQ";
	pic = "*---";
	pic = "Q/QQ";
	helpMissL.init(0,0,rightF,pic,'K');

	pic.clear();
	pic = "QQ/Q";
	pic = "---*";
	pic = "QQ\\Q";
	helpMissR.init(0,0,leftF,pic,'K');

	pic.clear();
	pic = "Q";
	pic = ".";

	upRB.init(0,0,upR,pic);

	northERB.init(0,0,northER,pic);

	northWRB.init(0,0,northWR,pic);

	northENRB.init(0,0,northENR,pic);

	northWNRB.init(0,0,northWNR,pic);


	pic.clear();
	pic = "^";
	pic = "Q";
	pic = "Q";

	archRB.init(0,0,backarchR,pic,'4');

	archLB.init(0,0,backarchL,pic,'4');




//turrets
//idea: mines!!!
	
	fastT.init(1,6,2,-1, "Fast Gun");
	fastT.addbullet(-2,0,fastB);

	expbullet bomb;
	pic.clear();
	pic = "o";
	bomb.init(0,0,upR,pic);
	bomb.settype('N');
	bombT.init(9,0,8,100, "Bomb Launcher");
	bombT.addbullet(-1,0,bomb);

	spreadT.init(2,10,3,-1, "Spread Gun");
	spreadT.addbullet(-2,0,upRB);
	spreadT.addbullet(-2,-1,northWNRB);
	spreadT.addbullet(-2,1,northENRB);
	spreadT.addbullet(-2,-2,northWRB);
	spreadT.addbullet(-2,2,northERB);

	backarchTL.init(3,5,2,-1,"Grav Accelerator");
	backarchTL.addbullet(1,0,archLB);

	backarchTR.init(3,5,2,-1,"Grav Accelerator");
	backarchTR.addbullet(1,0,archRB);

	pic.clear();
	pic = "Q";
	pic = "Q";
	pic = "!";
	devilT.init(4,5,4,-1,"Devil's Gun");
	devilT.addbullet(-3,0,upF,pic,'3');
	devilT.addbullet(-3,0,frontarchR,pic,'3');
	devilT.addbullet(-3,0,frontarchL,pic,'3');

	pic.clear();
	pic = "QQQ";
	pic = "( )";
	DNAT.init(5,4,3,400,"DNA Blaster");
	DNAT.addbullet(-2,-1,helixR,pic,'5');
	DNAT.addbullet(-2,-1,helixL,pic,'5');

	pic.clear();
	pic = "Q|Q";
	pic = "<|>";
	pic = "Q*Q";
	missileT.init(6,0,60,-1,"Missile Launcher");
	missileT.addbullet(-3,-1,upF,pic,'K'); //K = 1000

	shockwaveT.init(7,0,50,10,"Shockwave Device");
	shockwaveT.special("Shockwave");

	supershockT.init(7,0,50,8,"Super Shockwave");
	supershockT.special("Super Shock");

	stasisT.init(0,300,7,"Stasis Field Generator");
	stasisT.special("Stasis");

	vibrT.init(0,250,5,"Vibration Field");
	vibrT.special("Vibration");

	centrT.init(0,400,10,"Centralizer");
	centrT.special("Centralize");

	radiatT.init(0,1000,3,"Radiation Field");
	radiatT.special("Radiation");

	misshelpT.init(0,600,3,"Missile Support");
	misshelpT.special("Missiles");

	infernoT.init(0,450,5,"Inferno");
	infernoT.special("Inferno");

	halfshieldT.init(0,750,6,"Shield");
	halfshieldT.special("Half");


//ships

/*
	pic = "  !  ";
	pic = ":/!\:";
*/

	pic.clear();
	pic = "QQ!QQ";
	pic = ":/!\\:";
	interceptor.init("Interceptor",1000);
	interceptor.loadpic(pic);
	interceptor.setHP(75);
	interceptor.setspeed(2);
	interceptor.addturret(1,0,fastT);
	interceptor.addturret(1,4,fastT);
	interceptor.addturret(0,2,spreadT);
	interceptor.addturret(1,4,backarchTR);
	interceptor.addturret(1,0,backarchTL);
	interceptor.addturret(0,2,devilT);
	interceptor.addturret(0,2,DNAT);
	interceptor.addturret(0,2,missileT);
	interceptor.addturret(0,1,shockwaveT);
	interceptor.addturret(1,0,bombT,8);
	interceptor.addturret(1,4,bombT,8);
	interceptor.nameturrets(2,"Spread Gun",100);
	interceptor.nameturrets(3,"Grav Accelerator",475);
	interceptor.nameturrets(4,"Devil Guns",350);
	interceptor.nameturrets(5,"DNA Blaster",800);
	interceptor.nameturrets(6,"Missile Launcher",250);
	interceptor.nameturrets(7,"Weak Shockwave",500);
	interceptor.nameturrets(8,"Bomb Launcher",900);
	interceptor.activate(1);
//	interceptor.activate(2);
//	interceptor.activate(5);
//	interceptor.activate(8);
//	interceptor.activate(7);
//	interceptor.activate(9);
//	interceptor.activate(0);
	pic.clear();
	pic = "***";
	interceptor.addengine(2,1,pic);

/*
	pic = "|/====: :====\|";
	pic = "|  _   "   _  |";
	pic = " \/ \=====/ \/ ";
*/

	UFO.init("Frigate",3000);
	pic.clear();
	pic = "|/====:Q:====\\|";
	pic = "|  _   \"   _  |";
	pic = "Q\\/Q\\=====/Q\\/Q";
	UFO.loadpic(pic);
	UFO.setHP(350);
	UFO.addturret(0,6,fastT);
	UFO.addturret(0,8,fastT);
	UFO.addturret(0,0,fastT);
	UFO.addturret(0,14,fastT);
	UFO.addturret(0,7,spreadT);
	UFO.addturret(1,0,backarchTL);
	UFO.addturret(1,14,backarchTR);
	UFO.addturret(0,0,devilT);
	UFO.addturret(0,14,devilT);
	UFO.addturret(0,0,DNAT);
	UFO.addturret(0,14,DNAT);
	UFO.addturret(0,0,missileT);
	UFO.addturret(0,14,missileT);
	UFO.addturret(0,7,shockwaveT);
	UFO.activate(1);
	UFO.activate(2);
	UFO.activate(3);
	UFO.activate(4);
	UFO.activate(5);
	UFO.activate(6);
	UFO.activate(7);
	pic.clear();
	pic = "Q*Q";
	pic = "~~~";
	UFO.addengine(2,2,pic);
	UFO.addengine(2,10,pic);

/*
	pic = "          /- -\          ";
	pic = "          / " \          ";
	pic = " /_\     |     |     /_\ ";
	pic = "/   \=^=/  ___  \=^=/   \";
	pic = "|         /   \         |";
	pic = "\/\/\/\/\/     \/\/\/\/\/";
*/

	battleship.init("Battleship",20000);
	pic.clear();
	pic = "QQQQQQQQQQ/-Q-\\QQQQQQQQQQ";
	pic = "QQQQQQQQQQ/ \" \\QQQQQQQQQQ";
	pic = "Q/_\\QQQQQ|     |QQQQQ/_\\Q";
	pic = "/   \\=^=/  ___  \\=^=/   \\";
	pic = "|         /QQQ\\         |";
	pic = "\\/\\/\\/\\/\\/QQQQQ\\/\\/\\/\\/\\/";
	battleship.loadpic(pic);
	pic.clear();
	pic = "QQ***QQ";
	pic = "Q*****Q";
	pic = "*******";
	battleship.addengine(4,9,pic);
	battleship.setHP(800);
	battleship.addturret(2,1,fastT);
	battleship.addturret(2,3,fastT);
	battleship.addturret(2,21,fastT);
	battleship.addturret(2,23,fastT);
	battleship.addturret(3,6,fastT);
	battleship.addturret(3,18,fastT);
	battleship.addturret(0,10,fastT);
	battleship.addturret(1,12,fastT);
	battleship.addturret(0,14,fastT);
	battleship.addturret(0,12,spreadT);
	battleship.addturret(2,2,spreadT);
	battleship.addturret(2,22,spreadT);
	battleship.addturret(3,-1,backarchTL);
	battleship.addturret(5,0,backarchTL);
	battleship.addturret(3,25,backarchTR);
	battleship.addturret(5,24,backarchTR);
	battleship.addturret(2,2,devilT);
	battleship.addturret(0,10,devilT);
	battleship.addturret(0,12,devilT);
	battleship.addturret(0,14,devilT);
	battleship.addturret(2,22,devilT);
	battleship.addturret(2,2,DNAT);
	battleship.addturret(0,12,DNAT);
	battleship.addturret(2,22,DNAT);
	battleship.addturret(5,-1,missileT);
	battleship.addturret(5,25,missileT);
	battleship.addturret(2,2,missileT);
	battleship.addturret(2,22,missileT);
	battleship.addturret(3,6,missileT);
	battleship.addturret(3,18,missileT);
	battleship.addturret(0,12,missileT);
	battleship.addturret(0,12,supershockT);
	battleship.addturret(0,0,halfshieldT,9);

	battleship.activate(1);
	battleship.activate(2);
	battleship.activate(3);
	battleship.activate(4);
	battleship.activate(5);
	battleship.activate(6);
	battleship.activate(7);
	battleship.activate(9);

/*
	":/"\||/"\:";
	"(  |/\|  )";
	" \      / ";
	"  \/--\/  ";
*/

	fieldship.init("Field Ship",4000);
	pic.clear();
	pic = ":/\"\\||/\"\\:";
	pic = "(  |/\\|  )";
	pic = "Q\\      /Q";
	pic = "QQ\\/--\\/QQ";
	fieldship.loadpic(pic);

	pic.clear();
	pic = "~~";
	fieldship.addengine(4,4,pic);
	fieldship.setHP(350);
	fieldship.addturret(0,0,fastT,1);
	fieldship.addturret(0,2,fastT,1);
	fieldship.addturret(0,7,fastT,1);
	fieldship.addturret(0,9,fastT,1);
	fieldship.addturret(0,0,supershockT,2);
	fieldship.addturret(0,0,centrT,3);
	fieldship.addturret(0,0,stasisT,4);
	fieldship.addturret(0,0,vibrT,5);
	fieldship.addturret(0,0,radiatT,6);
	fieldship.addturret(0,0,misshelpT,7);
	fieldship.addturret(0,0,infernoT,8);
	fieldship.addturret(0,0,halfshieldT,9);
	fieldship.activate(1);
	fieldship.activate(2);
	fieldship.activate(3);
	fieldship.activate(4);
	fieldship.activate(5);
	fieldship.activate(6);
	fieldship.activate(7);
	fieldship.activate(8);
	fieldship.activate(9);








	SHIPS.resize(SHIPS.length()+1);
	SHIPS[SHIPS.length()-1] = interceptor;
	SHIPS.resize(SHIPS.length()+1);
	SHIPS[SHIPS.length()-1] = UFO;
	SHIPS.resize(SHIPS.length()+1);
	SHIPS[SHIPS.length()-1] = fieldship;
	SHIPS.resize(SHIPS.length()+1);
	SHIPS[SHIPS.length()-1] = battleship;

}



#endif