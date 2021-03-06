#include <ai/Game.h>
#include <ai/AI.h>
#include <time.h>
#include <queue>

// ==================== HOW TO RUN THIS =====================
// Call:
// "AI_Template.exe -h [host] -p [port] -k [key]"
//
// If no argument given, it'll be 127.0.0.1:3011
// key is a secret string that authenticate the bot identity
// it is not required when testing
// ===========================================================

//////////////////////////////////////////////////////////////////////////////////////
//                                                                                  //
//                                    GAME RULES                                    //
//                                                                                  //
//////////////////////////////////////////////////////////////////////////////////////
// - The game is played on a map of 20x20 blocks where [x,y] is referred as the     //
// block at column x and row y.                                                     //
// - Each team has 1 main base, 2 side bases and 4 tanks.                           //
// - At the beginning of a game, each player will choose 4 tanks and place them     //
// on the map (not on any bases/obstacles/tanks).                                   //
// - The game is played in real-time mode. Each player will control 4 tanks in      //
// order to defend their bases and at the same time, try to destroy their enemyâ€™s   //
// bases.                                                                           //
// -Your tank bullets or cannon shells will pass other allied tank (not friendly    //
// fire), but will damage your own bases, so watch where you firing.                //
// -A destroyed tank will allow bullet to pass through it, but still not allow      //
// other tanks to pass through.                                                     //
// - When the game starts (and after each 30 seconds) , a random power-up will be   //
// spawn at 1 of 3 bridges (if there are still space) at location:                  //
// [10.5, 1.5], [10.5, 10.5], [10.5, 19.5].                                         //
// - Power-ups are friendly-fired and have area of effect (AOE) damage. All units   //
// near the struck location will be affected. Use them wisely.                      //
// - The game is over when:                                                         //
//   + The main base of 1 team is destroyed. The other team is the winner.          //
//   + If all tanks of a team are destroyed, the other team is the winner.          //
//   + After 120 seconds, if both main bases are not destroyed, the team with more  //
//   side bases remaining is the winner.                                            //
//   + If both team have the same bases remaining, the game will change to â€œSudden  //
//   Deathâ€ mode. In Sudden Death mode:                                             //
//     * 2 teams will play for extra 30 seconds.                                    //
//     * All destructible obstacles are removed.                                    //
//     * If 1 team can destroy any base, they are the winner.                       //
//     * After Sudden Death mode is over, the team has more tanks remaining is the  //
//     winner.                                                                      //
//   + The time is over. If itâ€™s an active game (i.e. Some tanks and/or bases are   // 
//   destroyed), the result is a DRAW. If nothing is destroyed, itâ€™s a BAD_DRAW.    //
//                                                                                  //
// Please read the detailed rule on our web site at:                                //
//   http://han-ai-contest2016.gameloft.com                                         //
//////////////////////////////////////////////////////////////////////////////////////
// This function is called automatically to set your tanks on the map
// Arrange your tanks as you wish using PlaceTank() command
// You can only place NUMBER_OF_TANK tanks in the map
// IMPORTANT: Remember to place all your tanks and the coordinates must be integers.
void AI_Placement()
{
	AI* p_AI = AI::GetInstance();
	if (p_AI->GetMyTeam() == TEAM_1) {
		Game::PlaceTank(TANK_MEDIUM, 5, 2);
		Game::PlaceTank(TANK_MEDIUM, 7, 7);
		Game::PlaceTank(TANK_MEDIUM, 7, 14);
		Game::PlaceTank(TANK_MEDIUM, 7, 20);
	}
	else if (p_AI->GetMyTeam() == TEAM_2) {
		Game::PlaceTank(TANK_MEDIUM, 14, 1);
		Game::PlaceTank(TANK_MEDIUM, 14, 7);
		Game::PlaceTank(TANK_MEDIUM, 14, 14);
		Game::PlaceTank(TANK_MEDIUM, 14, 20);
	}
}
// This function is called automatically when it's your turn.
// Remember to call AI_Move() with a valid move before the time is run out.
// See <ai/Game.h> and <ai/AI.h> for supported APIs.

  /////////////////////////////////////////////////////////////
 //						BFS									//
/////////////////////////////////////////////////////////////
struct tdo
{
	int x, y, z;
	tdo(int x1, int y1, int z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
};
int a[101][101], b[101][101], bgx, bgy, endx, endy;
int _x[] = { -1, 0, 1, 0 };
int _y[] = { 0, 1, 0, -1 };
bool ktra(int x, int y)
{
	return x > 0 && x <= 100 && y > 0 && y <= 100;
}
void BFS()
{
	queue <tdo> Q;
	Q.push(tdo(endx, endy, 0));
	while (!Q.empty())
	{
		tdo temp = Q.front();
		Q.pop();
		if (b[temp.x][temp.y] == 0)
		{
			b[temp.x][temp.y] = 1;
			a[temp.x][temp.y] = temp.z;
			for (int j = 0; j < 4; j++)
			{
				tdo diem = tdo(temp.x + _x[j], temp.y + _y[j], temp.z + 1);
				if (ktra(diem.x, diem.y) && b[diem.x][diem.y] == 0)
					Q.push(diem);
			}
		}
	}
}
void clear()
{
	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			a[i][j] = 0;
			b[i][j] = 0;
		}
	}
}
void AI_Update()
{
	AI* p_AI = AI::GetInstance();
	// =========================================================================================================
	// Check if there will be any airstrike or EMP
	// The GetIncomingStrike() function will return an array of strike object. Both called by your team
	// or enemy team.
	// =========================================================================================================
	std::vector<Strike*> strike = p_AI->GetIncomingStrike();
	for (int i = 0; i < strike.size(); i++)
	{
		float x = strike[i]->GetX();
		float y = strike[i]->GetY();
		int count = strike[i]->GetCountDown(); // Delay (in server loop) before the strike reach the battlefield.
		int type = strike[i]->GetType();

		if (type == POWERUP_AIRSTRIKE)
		{
			// You may want to do something here, like moving your tank away if the strike is on top of your tank.
		}
		else if (type == POWERUP_EMP)
		{
			// Run... RUN!!!!
		}
	}
	// =========================================================================================================
	// Get power up list on the map. You may want to move your tank there and secure it before your enemy
	// does it. You can get coordination, and type from this object
	// =========================================================================================================
	std::vector<PowerUp*>  powerUp = p_AI->GetPowerUpList();
	for (int i = 0; i < powerUp.size(); i++) {
		float x = powerUp[i]->GetX();
		float y = powerUp[i]->GetY();
		int type = powerUp[i]->GetType();
		if (type == POWERUP_AIRSTRIKE)
		{
			// You may want to move your tank to this position to secure this power up.
		}
		else if (type == POWERUP_EMP)
		{
			// Do something else
		}
	}
	// =========================================================================================================
	// This is an example on how you command your tanks.
	// In this example, I go through all of my "still intact" tanks, and give them random commands.
	// =========================================================================================================
	// Loop through all tank (if not dead yet)
	/*for (int i = 0; i < 4; i++)
	{
	int td1 = p_AI->GetEnemyTank(i)->GetY();
	int td2= p_AI->GetEnemyTank(i)->GetX();
	for(int k=td1*5-4;k<=td1*5;k++)
	for(int l=td2*5-4;l<=td2*5;l++)
	b[k][l] = 1;
	}*/
	for (int i = 0; i < NUMBER_OF_TANK; i++)
	{
		for (int i1 = 1; i1 <= 20; i1++)
		{
			for (int j = 1; j <= 20; j++)
			{
				if (p_AI->GetBlock(j, i1) != BLOCK_GROUND)
				{
					for (int k = i1 * 5 - 4; k <= i1 * 5; k++)
						for (int l = j * 5 - 4; l <= j * 5; l++)
							b[k][l] = 1;
				}
				for (int k = i1 * 5 - 4; k <= i1 * 5; k++)
					for (int l = j * 5 - 4; l <= j * 5; l++)
						if (k != i1 * 5 - 2 && l != j * 5 - 2)
							b[k][l] = 1;
			}
		}
		Tank* tempTank = p_AI->GetMyTank(i);
		//don't waste effort if tank's death
		if ((tempTank == NULL) || (tempTank->GetHP() == 0))
			continue;
		// Run randomly and fire as soon as cooldown finish.
		// You may want a more ... intelligent algorithm here.
		///////////////////////////////////////////////////////////////
		//						TEAM_1								  //
		///////////////////////////////////////////////////////////////
		if (p_AI->GetMyTeam() == TEAM_1)
		{
			bgx = tempTank->GetY() * 5 - 2;
			bgy = tempTank->GetX() * 5 - 2;
			if (i == 0)
			{
				for (int j = 0; j < 4; j++)
				{
					if (p_AI->GetEnemyTank(j)->GetHP() != 0) {
						endx = (int)p_AI->GetEnemyTank(j)->GetY() * 5 + -2;
						endy = (int)p_AI->GetEnemyTank(j)->GetX() * 5 + -2;
					}
				}
				BFS();
				for (int j = 0; j < 4; j++)
				{
					if (ktra(bgx + _x[j], bgy + _y[j]) && a[bgx + _x[j]][bgy + _y[j]] == a[bgx][bgy] - 1)
					{
						Game::CommandTank(i, j + 1, true, true);
						break;
					}
				}
				clear();
			}
			if (i == 1)
			{
				for (int j = 0; j < 4; j++)
				{
					if (p_AI->GetEnemyTank(j)->GetHP() != 0) {
						endx = (int)p_AI->GetEnemyTank(j)->GetY() * 5 + -2;
						endy = (int)p_AI->GetEnemyTank(j)->GetX() * 5 + -2;
					}
				}
				BFS();
				for (int j = 0; j < 4; j++)
				{
					if (ktra(bgx + _x[j], bgy + _y[j]) && a[bgx + _x[j]][bgy + _y[j]] == a[bgx][bgy] - 1)
					{
						Game::CommandTank(i, j + 1, true, true);
						break;
					}
				}
				clear();
			}
			if (i == 2)
			{
				for (int j = 3; j >= 0; j--)
				{
					if (p_AI->GetEnemyTank(j)->GetHP() != 0) {
						endx = (int)p_AI->GetEnemyTank(j)->GetY() * 5 + -2;
						endy = (int)p_AI->GetEnemyTank(j)->GetX() * 5 + -2;
					}
				}
				BFS();
				for (int j = 0; j < 4; j++)
				{
					if (ktra(bgx + _x[j], bgy + _y[j]) && a[bgx + _x[j]][bgy + _y[j]] == a[bgx][bgy] - 1)
					{
						Game::CommandTank(i, j + 1, true, true);
						break;
					}
				}
				clear();
			}
			if (i == 3)
			{
				for (int j = 3; j >= 0; j--)
				{
					if (p_AI->GetEnemyTank(j)->GetHP() != 0) {
						endx = (int)p_AI->GetEnemyTank(j)->GetY() * 5 + -2;
						endy = (int)p_AI->GetEnemyTank(j)->GetX() * 5 + -2;
					}
				}
				BFS();
				for (int j = 0; j < 4; j++)
				{
					if (ktra(bgx + _x[j], bgy + _y[j]) && a[bgx + _x[j]][bgy + _y[j]] == a[bgx][bgy] - 1)
					{
						Game::CommandTank(i, j + 1, true, true);
						break;
					}
				}
				clear();
			}
		}
		/////////////////////////////////////
		//				TEAM 2			   //
		/////////////////////////////////////
		else
		{
			bgx = tempTank->GetY() * 5 - 2;
			bgy = tempTank->GetX() * 5 - 2;
			if (i == 0)
			{
				for (int j = 0; j < 4; j++)
				{
					if (p_AI->GetEnemyTank(j)->GetHP() != 0) {
						endx = (int)p_AI->GetEnemyTank(j)->GetY() * 5 + -2;
						endy = (int)p_AI->GetEnemyTank(j)->GetX() * 5 + -2;
						break;
					}
				}
				BFS();
				for (int j = 0; j < 4; j++)
				{
					if (ktra(bgx + _x[j], bgy + _y[j]) && a[bgx + _x[j]][bgy + _y[j]] == a[bgx][bgy] - 1)
					{
						Game::CommandTank(i, j + 1, true, true);
						break;
					}
				}
				clear();
			}
			if (i == 1)
			{
				for (int j = 0; j < 4; j++)
				{
					if (p_AI->GetEnemyTank(j)->GetHP() != 0) {
						endx = (int)p_AI->GetEnemyTank(j)->GetY() * 5 + -2;
						endy = (int)p_AI->GetEnemyTank(j)->GetX() * 5 + -2;
						break;
					}
				}
				BFS();
				for (int j = 0; j < 4; j++)
				{
					if (ktra(bgx + _x[j], bgy + _y[j]) && a[bgx + _x[j]][bgy + _y[j]] == a[bgx][bgy] - 1)
					{
						Game::CommandTank(i, j + 1, true, true);
						break;
					}
				}
				clear();
			}
			if (i == 2)
			{
				for (int j = 3; j >= 0; j--)
				{
					if (p_AI->GetEnemyTank(j)->GetHP() != 0) {
						endx = (int)p_AI->GetEnemyTank(j)->GetY() * 5 + -2;
						endy = (int)p_AI->GetEnemyTank(j)->GetX() * 5 + -2;
						break;
					}
				}
				BFS();
				for (int j = 0; j < 4; j++)
				{
					if (ktra(bgx + _x[j], bgy + _y[j]) && a[bgx + _x[j]][bgy + _y[j]] == a[bgx][bgy] - 1)
					{
						Game::CommandTank(i, j + 1, true, true);
						break;
					}
				}
				clear();
			}
			if (i == 3)
			{
				for (int j = 3; j >= 0; j--)
				{
					if (p_AI->GetEnemyTank(j)->GetHP() != 0) {
						endx = (int)p_AI->GetEnemyTank(j)->GetY() * 5 + -2;
						endy = (int)p_AI->GetEnemyTank(j)->GetX() * 5 + -2;
						break;
					}
				}
				BFS();
				for (int j = 0; j < 4; j++)
				{
					if (ktra(bgx + _x[j], bgy + _y[j]) && a[bgx + _x[j]][bgy + _y[j]] == a[bgx][bgy] - 1)
					{
						Game::CommandTank(i, j + 1, true, true);
						break;
					}
				}
				clear();
			}
		}
	}
	// =========================================================================================================
	// This is an example on how you use your power up if you acquire one.
	// If you have airstrike or EMP, you may use them anytime.
	// I just give a primitive example here: I strike on the first enemy tank, as soon as I acquire power up
	// =========================================================================================================
	if (p_AI->HasAirstrike())
	{
		int HP1 = 1000, min1;
		for (int i = 0; i < NUMBER_OF_TANK; i++)
		{
			Tank* tempTank = p_AI->GetEnemyTank(i);
			if (tempTank->GetHP() > 0 && HP1 > tempTank->GetHP()) {
				min1 = i;
				HP1 = tempTank->GetHP();
			}
		}
		Tank* tempTank = p_AI->GetEnemyTank(min1);
		p_AI->UseAirstrike(tempTank->GetX(), tempTank->GetY());
	}
	else if (p_AI->HasEMP())
	{
		int HP2 = 0, max1;
		for (int i = 0; i < NUMBER_OF_TANK; i++)
		{
			Tank* tempTank = p_AI->GetEnemyTank(i);
			if (tempTank->GetHP() > 0 && HP2 < tempTank->GetHP())
			{
				max1 = i;
				HP2 = tempTank->GetHP();
			}
		}
		Tank* tempTank = p_AI->GetEnemyTank(max1);
		p_AI->UseEMP(tempTank->GetX(), tempTank->GetY());
	}

	// Leave this here, don't remove it.
	// This command will send all of your tank command to server
	Game::GetInstance()->SendCommand();
}

////////////////////////////////////////////////////////////
//                DON'T TOUCH THIS PART                   //
////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	srand(clock());

#ifdef _WIN32
	INT rc;
	WSADATA wsaData;

	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc) {
		printf("WSAStartup Failed.\n");
		return 1;
	}
#endif

	Game::CreateInstance();
	Game* p_Game = Game::GetInstance();

	// Create connection
	if (p_Game->Connect(argc, argv) == -1)
	{
		LOG("Failed to connect to server!\n");
		return -1;
	}

	// Set up function pointers
	AI::GetInstance()->PlaceTank = &AI_Placement;
	AI::GetInstance()->Update = &AI_Update;

	// Polling every 100ms until the connection is dead
	p_Game->PollingFromServer();

	Game::DestroyInstance();

#ifdef _WIN32
	WSACleanup();
#endif
	return 0;
}