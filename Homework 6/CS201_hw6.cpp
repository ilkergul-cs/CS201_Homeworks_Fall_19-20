#include <string>
#include "strutils.h"
#include "randgen.h"
#include "miniFW_Modified.h"
#include "Robots_Modified.h"


using namespace std;

void manuel_actions(Robot & player1) // I modified the code for manuel entry from the user
{
	if (IsPressed(keyDownArrow))		// When user entries down arrow button robot will move downwards
	{				
		player1.TurnFace(south);
		player1.Move();
		player1.PickAllThings();
	}
	else if (IsPressed(keyUpArrow))		// When user entries up arrow button robot will move upwards
	{
		player1.TurnFace(north);
		player1.Move();	
		player1.PickAllThings();
	}
	else if (IsPressed(keyLeftArrow))		// When user left arrow button robot will move to left
	{
		player1.TurnFace(west);	
		player1.Move();	
		player1.PickAllThings();
	}
	else if (IsPressed(keyRightArrow))		// When user right arrow button robot will move to right
	{
		player1.TurnFace(east);
		player1.Move();	
		player1.PickAllThings();
	}


}

void automatic_actions(Robot & monster_given)			// This one is for monsters(robots)
{
	RandGen random; 
	int move_number = random.RandInt(0,3);
	int turner = random.RandInt(0,3);
	if (turner == 0)
	{
		monster_given.TurnFace(east);
	}
	else if(turner == 1)
	{
		monster_given.TurnFace(north);
	}
	else if(turner == 2)
	{
		monster_given.TurnFace(south);
	}
	else if(turner == 3)
	{
		monster_given.TurnFace(west);
	}
	while(move_number > 0 && !monster_given.FacingWall() && monster_given.IsAlive())
	{
		monster_given.Move();
		move_number--;
		monster_given.PickAllThings();
	}
	monster_given.Resurrect();
}

void life_checker(Robot & player1, int & count)			//I am going to check the count of life
{
	if(player1.IsAlive() == false)
	{
		count--;
		if(count > 0)
		{
			ShowMessage("You have " + to_string(count) + " lives left");
			player1.Resurrect();
		}

	}
}

void random_putting_things_machine()			// I am putting the things randomly with this function
{
	int k , j, num, count = 0, checker;
	RandGen complex;
	checker = complex.RandInt(20, 40);
	while (count <= checker)
	{
		RandGen random;
		k = random.RandInt(0,7);
		j = random.RandInt(0,7);
		num = random.RandInt(0, 10);
		if (num > 0 && GetCellCount(k,j) == 0)
		{
			PutThings(k, j, num);
			count++;
		}					
	}
}

int award_goes_to(const int & playeruno, const int & dos, const int & tres, const int & cuatro) // Checking how many things in the back
{
	if(playeruno > dos && playeruno > tres && playeruno > cuatro)
	{
		return 1;
	}
	else 		
	{
		if(dos >= tres && dos >= cuatro)				// Checking the necessary conditions for ranking
		{
			return 2;
		}
		else if(tres >= dos && tres >= cuatro)
		{
			return 3;
		}
		else if(cuatro >= dos && cuatro >= tres)
		{
			return 4;
		}
	}
}



int main()
{	
	string player1_name, monster1_name, monster2_name, monster3_name;
	RandGen order; int num;

	GetInput("Please enter the name of the player robot ",player1_name);				//I am getting the inputs
	GetInput("Please enter the name of the monster robot 1 ", monster1_name);
	GetInput("Please enter the name of the monster robot 2 ", monster2_name);
	GetInput("Please enter the name of the monster robot 3 ", monster3_name);

	Robot player1(5,2); Robot monster1(0,0); Robot monster2(0,7); Robot monster3(7,7);
	player1.SetColor(blue); monster1.SetColor(red); monster2.SetColor(red); monster3.SetColor(red);	

	player1.SetName(player1_name); monster1.SetName(monster1_name);
	monster2.SetName(monster2_name); monster3.SetName(monster3_name);
	int lives_of_player1 = 3;

	random_putting_things_machine();

	while(GetThingCount(0,0,7,7) != 0 && lives_of_player1 > 0)
	{
		num = order.RandInt(6);											// I am making the order differently with randomization with 6 combination
		if(num == 0)
		{
			automatic_actions(monster2); automatic_actions(monster3); automatic_actions(monster1);
		}
		else if(num == 1)
		{
			automatic_actions(monster1); automatic_actions(monster3); automatic_actions(monster2);
		}
		else if(num == 2)
		{
			automatic_actions(monster3); automatic_actions(monster2); automatic_actions(monster1);
		}
		else if(num == 3)
		{
			automatic_actions(monster1); automatic_actions(monster2); automatic_actions(monster3);
		}
		else if(num == 4)
		{
			automatic_actions(monster2); automatic_actions(monster1); automatic_actions(monster3);
		}
		else if(num == 5)
		{
			automatic_actions(monster3); automatic_actions(monster1); automatic_actions(monster2);
		}

		manuel_actions(player1); 
		life_checker(player1, lives_of_player1);

	}

	if(GetThingCount(0,0,7,7) == 0)							// I am announcing the winner
	{
		if (award_goes_to(player1.GetBagCount(), monster1.GetBagCount(), monster2.GetBagCount(), monster3.GetBagCount()) == 1)
		{
			ShowMessage("Congratulations. " + player1.GetName() + " has won the game.");
		}
		else if (award_goes_to(player1.GetBagCount(), monster1.GetBagCount(), monster2.GetBagCount(), monster3.GetBagCount()) == 2)
		{
			ShowMessage("You lost. " + monster1.GetName()+ " won the game.");
		}
		else if (award_goes_to(player1.GetBagCount(), monster1.GetBagCount(), monster2.GetBagCount(), monster3.GetBagCount()) == 3)
		{
			ShowMessage("You lost. " + monster2.GetName()+ " won the game.");
		}
		else if (award_goes_to(player1.GetBagCount(), monster1.GetBagCount(), monster2.GetBagCount(), monster3.GetBagCount()) == 4)
		{
			ShowMessage("You lost. " + monster3.GetName()+ " won the game.");
		}

	}
	else if (lives_of_player1 == 0)
	{
		ShowMessage(player1.GetName() + " out of lives, you just lost the game.");		//User lost the game
	}

	return 0;
}

//End of Homework 6
//Yours sincerely
//ilker gul
