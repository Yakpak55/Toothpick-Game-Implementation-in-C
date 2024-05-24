//Name:Christopher Deluigi
//Dr. Steinberg
//COP3223C 
//Large Program 1

#define ROUNDS 3
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void greeting(); //display welcome message to user
int playRound(int round); //play one round
int humanPick(); //retrieve the user's guess
int computerPick(int choice, int leftover); //computer makes its pick
int leftOnTable(int toothpicks, int taken); //calculate number of toothpicks left
void winnerAnnouncment(int user); //overall winner of round announcement

int main()
{
	greeting(); // calls function and prints code that will greet the user, with rules and how to play
	
	for(int x = 0; x < ROUNDS; ++x)
	{
		int result = playRound(x + 1); //call playRound and assign result the value function returns
		
        winnerAnnouncment(result); //calls winnerAnnouncment function
	}
	
	printf("********************************************************\n");
	printf("Thank you for playing!\n");
	return 0;
}

int playRound(int round)
{
	printf("Welcome to a new round %d!\n", round);
	printf("You may go first!\n");
    printf("********************************************************\n");
	
	int toothpicks = 31; //number of toothpicks to start with
	
    int player_wins = 1; // creates variable and sets the amount to 1, this means if the ai loses the value remains at 1, so user has won

	
	//loop that keeps track of toothpicks until respective no more toothpicks left. we will learn about conditional loops soon :)
	//basically the loop continues until toothpicks is at 0
	while(toothpicks != 0)
	{
        printf("There are %d toothpick(s) left on the table.\n",toothpicks); // prints statement for how many toothpicks are left on the table after each turn
        
        int x = humanPick(); //sets variable to how many toothpicks was taken , then leftontable gets called and checks the amount of toothpicks left after the turn by subtracting toothpicks by humanpick

        if(x < 1 ||  x > 3) //checks to make sure user is only allowed to input numbers between 1-3. if user tries to input numbers different than 1-3 the following message prints and restarts allowing them to input new number
        {
            printf("********************************************************\n");
            printf("Not the correct value, try selecting 1-3 \n");
            continue;

        }
		if (x > toothpicks || x == toothpicks && x != 1) //checks to see if user tries to take more toothpicks than what is available, if they do restarts
        // checks to see if user takes the amount of toothpicks left, will restart
        {
            printf("********************************************************\n");
            printf("Can't take out more than that\n");
            continue ;
        }

        //ai choses the amount of toothpicks they want to take
        toothpicks = leftOnTable(toothpicks,x);
        int y = computerPick(x, toothpicks);
        toothpicks = leftOnTable(toothpicks,y);

        if(x == 1 && toothpicks == 0) //once no more toothpicks remain, last person's turn loses, if player_wins = 1 that means the user wins, and if player_wins = 2 that means the ai wins
        {
            player_wins = 2;
            return player_wins;
        }
	}
	
	return player_wins; 
}

void greeting() //creates function for printing guide at start of game, rules,and how to play
{
    printf("********************************************************\n");
    printf("Welcome to Toothpick Game!\n");
    printf("Here are the rules.\n");
    printf("There are currently 31 toothpicks on the table.\n");
    printf("You and I will each get a turn to pick either 1, 2, or 3 toothpicks off the table.\n");
    printf("The player that gets to pick the last toothpicks loses the game!\n");
    printf("Sounds Easy right? Well lets see if you can beat me!\n");
    printf("Ready to play?...Here we go!\n");
    printf("********************************************************\n");
}
int leftOnTable(int toothpicks, int taken) //updates the amount of toothpicks left in the pile after each turn
{
    toothpicks = toothpicks - taken;
    return toothpicks;
}

int humanPick() //asks the user how mnay toothpicks theyre going to take, as mentioned in the greeting, 1,2, or 3.
{
    int enter_choice;
    printf("How many toothpicks are you going to take off the table? ");
    scanf("%d", &enter_choice);
    return enter_choice;
}

int computerPick(int choice, int leftover) //sets variable to for ai turns. and prints how any toothpicks youve taken off the table in the last turn.
{
    int ai; 
    printf("Ok... you took %d off the table.\n", choice);
    printf("I'm making my decision now.\n");
    printf("********************************************************\n");
    printf("********************************************************\n");

    if (leftover != 0 || leftover < 0) //stops ai from taking anymore toothpicks if theres 0
    {
        if (4 < leftover) // checks to see if there are more than 4 toothpicks leftover, and if there is more than 4 toothpicks left, ten the ai will subtract 4 from users choice
        {
            ai = 4 - choice;
            printf("I am taking %d toothpick(s) off the table.\n", ai);
        }
        else if (leftover >= 2 && leftover <= 4)//checks to see if the amount of toothpicks left is between 2-4 and if so the following if statements get tested to see if theyre successfull.
        {
            if (leftover == 2) //if condition is true then the ai will remove 1, 2, or 3 depending on which condition is met below.
            {
                ai = 1;
                printf("I will be taking 1 toothpick(s) off the table.\n");
            }
           else if (leftover == 3)
            {
                ai = 2;
                printf("I will be taking 2 toothpick(s) off the table.\n");
            }
            else if (leftover == 4)
            {
                ai = 3;
                printf("I will be taking 3 toothpick(s) off the table.\n");
            }
        }
    }
        else if( leftover == 1) //checks to see if only 1 toothpick remains, and if so then ai has to take it and lose :(

            // Last situation, where the computer ends up taking the last one, making the user win in another function.
            ai = 1;
    
    else //if 0 remain game should have ended already
        ai = 0;

    printf("********************************************************\n");
    printf("********************************************************\n");

    return ai;
}

void winnerAnnouncment(int user) //checks to see what user is equal too, if 1 then we win, if 2 then ai wins.
{
    if(user == 1)
        printf("You won! I'll let you have this one.\n");
    else if(user == 2)
        printf("I won! Haha better luck next time!\n ");
}