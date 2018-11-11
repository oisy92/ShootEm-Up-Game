#include "cab202_graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <math.h>
#include <time.h>

typedef struct Game {
	sprite_id spacecraft;
	sprite_id allien[10];
	sprite_id bombs[4];
	sprite_id rocket;
	int score;
	int lives;
	int level;
	int counter;
	int counterharmonic;
	int counterdrunken;
	int counterrandom;
} Game;



void setup_game (Game * game)
{
	
	
	
//Setting up spacecraft location in the screen and drawing it.

int y = screen_height() * 0.89; 


game -> spacecraft = create_sprite ( 1, y, 1, 1, "@" );
draw_sprite (game -> spacecraft);



//Drawing Alliens
game -> allien[0] = create_sprite(screen_width()* 0.5 -3 , screen_height() * 0.1 + 6, 1, 1, "1");
game -> allien[1] = create_sprite(screen_width()* 0.5 +3 , screen_height() * 0.1 + 3, 1, 1, "2");
game -> allien[2] = create_sprite(screen_width()* 0.5 +3 , screen_height() * 0.1 + 9, 1, 1, "3");
game -> allien[3] = create_sprite(screen_width()* 0.5 +16, screen_height() * 0.1 + 6, 1, 1, "4");
game -> allien[4] = create_sprite(screen_width()* 0.5 +11, screen_height() * 0.1 + 3, 1, 1, "5");
game -> allien[5] = create_sprite(screen_width()* 0.5 +11, screen_height() * 0.1 + 9, 1, 1, "6");
game -> allien[6] = create_sprite(screen_width()* 0.5 +7 , screen_height() * 0.1 + 6, 1, 1, "7");
game -> allien[7] = create_sprite(screen_width()* 0.5 +19, screen_height() * 0.1 + 3, 1, 1, "8");
game -> allien[8] = create_sprite(screen_width()* 0.5 +19, screen_height() * 0.1 + 9, 1, 1, "9");
game -> allien[9] = create_sprite(screen_width()* 0.5 +25, screen_height() * 0.1 + 6, 1, 1, "@");



//Making all alliens visible
for (int i = 0; i < 9; i++)
{
game -> allien[i] -> is_visible = true;
}
//Creating Bombs and Assigning them to the same position as alliens
for (int i = 0; i < 4; i++)	
{
	
game -> bombs[i] = create_sprite(game -> allien[1] -> x,game -> allien[1]-> y,1,1,"@");
	
game -> bombs[i] -> is_visible = false;
	
}

//Assigning Score to 0
game -> score = 0;

//Assigning Lives to 0
game -> lives = 3;

//Assigning level to  0
game -> level = 1;

//Creating rocket and assigning it to move 1 character and making it invisible
game -> rocket = create_sprite(-20, game -> spacecraft -> y-1, 1,1, "@");
game -> rocket -> dy = 1;
game -> rocket -> is_visible = false;

//Assigning Counter to 0
game -> counter = 0;

game -> counterharmonic = 0;

game -> counterdrunken = 0;
}



void update_bombs (Game * game)
{
//This function will let the bombs drop from alliens every second, with maximum of 4 bombs in screen.

//Counter will be used to drop a bomb from random allien every second
	game -> counter++;
//Generating a random number for alliens to assign who will drop the bomb randomly
	srand(time(NULL));
	int a = rand() % 9;
//If one second has passed, drop a bomb from random allien
	if (game -> counter == 30 && game -> bombs[0] -> is_visible == false)
		
			{
			draw_char(2,2,'0');
			game -> bombs[0] -> x = game -> allien[a] -> x;
			game -> bombs[0] -> y = game -> allien[a] -> y;
			game -> bombs[0] -> dy = 0.5;
			game -> bombs[0] -> y += game -> bombs[0] -> dy;
			draw_sprite(game -> bombs[0]);
			game -> bombs[0] -> is_visible = true;
			
			}

		
//If 2nd second has passed,drop a bomb from random allien	
	else if (game -> counter == 60 && game -> bombs[1] -> is_visible == false )
		
			{
			draw_char(2,2,'1');
			game -> bombs[1] -> x = game -> allien[a] -> x;
			game -> bombs[1] -> y = game -> allien[a] -> y;
			game -> bombs[1] -> dy = 0.5;
			game -> bombs[1] -> y += game -> bombs[1] -> dy;
			draw_sprite(game -> bombs[1]);
			game -> bombs[1] -> is_visible = true;
			
			}


//If 3rd second has passed,drop a bomb from random allien			
	else if (game -> counter == 90 && game -> bombs[2] -> is_visible == false )
		
			{
			draw_char(2,2,'2');
			game -> bombs[2] -> x = game -> allien[a] -> x;
			game -> bombs[2] -> y = game -> allien[a] -> y;
			game -> bombs[2] -> dy = 0.5;
			game -> bombs[2] -> y += game -> bombs[2] -> dy;
			draw_sprite(game -> bombs[2]);
			game -> bombs[2] -> is_visible = true;
			
			}
//If 4th second has passed,drop a bomb from random allien		
	else if (game -> counter == 120 && game -> bombs[3] -> is_visible == false )
	
			{
			draw_char(2,2,'2');
			game -> bombs[3] -> x = game -> allien[a] -> x;
			game -> bombs[3] -> y = game -> allien[a] -> y;
			game -> bombs[3] -> dy = 0.5;
			game -> bombs[3] -> y += game -> bombs[3] -> dy;
			draw_sprite(game -> bombs[3]);
			game -> bombs[3] -> is_visible = true;
			
			}
//Keep the bombs falling whether or not if statements were true
			game -> bombs[0] -> y += game -> bombs[0] -> dy;
			draw_sprite(game -> bombs[0]);
			
			game -> bombs[1] -> y += game -> bombs[1] -> dy;
			draw_sprite(game -> bombs[1]);
			
			game -> bombs[2] -> y += game -> bombs[2] -> dy;
			draw_sprite(game -> bombs[2]);

			game -> bombs[3] -> y += game -> bombs[3] -> dy;
			draw_sprite(game -> bombs[3]);
			
//If bombs passed certain level on the screen, make them invisible. This will allow the above if statements to be true
			for (int i=0; i < 4; i++)
			{
			if (game -> bombs[i] -> y > screen_height() * 0.89)
			{
			game -> bombs[i] -> is_visible = false;
			}
			}
//If the counter has passed 60, repeat it again, this will allow the above if statement to be true
				if (game -> counter == 120)
				{
				game -> counter = 0;
				}
			

}




void update_spacecraft(Game * game, int key)

{
/* Telling spacecraft to move 1 characater to the left or right depending 
on the user's key press, after that rounding the new location coordiantes to real integer
and finally drawing the new location of the spacecraft. */
game -> spacecraft -> dx = 1;
if (key == 'a')	
	{
	game -> spacecraft -> x -= game -> spacecraft -> dx;
	}
	
else if (key == 'd')
	{
	game -> spacecraft -> x += game -> spacecraft -> dx;
	}
	
	draw_sprite(game -> spacecraft);
	
for (int i = 0; i < 4; i++)
{
	if (game -> spacecraft -> x == game -> bombs[i] -> x && game -> spacecraft -> y == game -> bombs[i] -> y)
	{
		game -> lives--;
	}
}
//Placed here temporarly, Later, I will create a function to monitor the game stats.
if (game -> lives == 0)
{
	clear_screen();
	draw_string (screen_width() * 0.5, screen_height() * 0.5, "Game Over");
	
	

}
}


void draw_alliens(Game * game)
{
/* This function will draw alliens */
for (int i = 0; i <= 9; i++)
	{
	draw_sprite(game -> allien[i]);
	}
}



void update_alliens(Game * game)
{
//Moving alliens from left to right ----->.
	int i;
for (i =0; i<=9; i++)
	{
	game -> allien[i] -> dx=1;
	
	game -> allien[i] -> x += game -> allien[i] -> dx;
	
	game -> allien[i] -> x = round(game -> allien[i] -> x);
	
	
	
//If allien went off screen, redraw it again at the left edge of the screen.
if (game -> allien[i] -> x >= screen_width())
			{
			game -> allien[i] -> x = 0;
			game -> allien[i] -> x += game -> allien[i] -> dx;
			}


//If rocket hit allien, make the allien disapear and increase the score by 30.	
			int yallien = round(game -> allien[i] -> y);
			int xallien = round(game -> allien[i] -> x);
			int xrocket = round(game -> rocket -> x);
			int yrocket = round(game -> rocket -> y);
	
if (xallien == xrocket && yallien == yrocket && game -> allien[i] -> is_visible == true)
			{
			
			game -> allien[i] -> is_visible = false;
			game -> rocket -> is_visible = false;
			game -> score = game -> score + 30;
			}
//Placed here temporatly, will add it to the game stats function later
if (game -> score == 300)
			{
			game -> score = game -> score + 500;
			game -> allien[i] -> is_visible = true;
			}

}


}


void update_rocket(Game * game, int key)
{
//This function draws the rocket that is shot from spacecraft, and will consider the rocket to be invisible if it hit an allien or went off screen.
	if (key == 's' && game -> rocket -> is_visible == false)
	{
	draw_char(1,2,'F');
	game -> rocket -> x = game -> spacecraft -> x;
	game -> rocket -> y = game -> spacecraft -> y-1;
	game -> rocket -> y = round(game -> rocket -> y);
	draw_sprite(game -> rocket);
	game -> rocket -> is_visible = true;

	}
	game -> rocket -> y -= game -> rocket -> dy;
	draw_sprite(game -> rocket);
	
	if (game -> rocket -> y < 0)
	{
		game -> rocket -> is_visible = false;
	}
}


void draw_menu(Game * game)
{
//Game's Menu
draw_formatted(screen_width() * 0.1, screen_height() * 0.92, "SCORE: %d\n", game -> score);
draw_formatted(screen_width() * 0.1, screen_height() * 0.94, "LIVES: %d\n", game -> lives);
draw_formatted(screen_width() * 0.1, screen_height() * 0.96, "LEVEL: %d\n", game -> level);
draw_formatted(screen_width() * 0.2, screen_height() * 0.92, "TIMER: %d\n", game -> counter);
draw_string(screen_width() - 30, screen_height() * 0.92, "Creator Name: Osama Yahya");
}

void draw_bottom_string(void)
{
	draw_line(0, screen_height() * 0.9, screen_width(), screen_height() * 0.9, '-');
}



void harmonicmotion (Game * game)
{

game -> counterharmonic++;

if (game -> counterharmonic <= 30)

{
	game -> allien[0] -> dy = 0.5;
	game -> allien[0] -> y += game -> allien[0] -> dy;
	game -> allien[1] -> dy = 0.5;
	game -> allien[1] -> y += game -> allien[1] -> dy;
	game -> allien[2] -> dy = 0.5;
	game -> allien[2] -> y += game -> allien[2] -> dy;
	game -> allien[3] -> dy = 0.5;
	game -> allien[3] -> y += game -> allien[3] -> dy;
	game -> allien[4] -> dy = 0.5;
	game -> allien[4] -> y += game -> allien[4] -> dy;
	game -> allien[5] -> dy = 0.5;
	game -> allien[5] -> y += game -> allien[5] -> dy;
	game -> allien[6] -> dy = 0.5;
	game -> allien[6] -> y += game -> allien[6] -> dy;
	game -> allien[7] -> dy = 0.5;
	game -> allien[7] -> y += game -> allien[7] -> dy;
	game -> allien[8] -> dy = 0.5;
	game -> allien[8] -> y += game -> allien[8] -> dy;
	game -> allien[9] -> dy = 0.5;
	game -> allien[9] -> y += game -> allien[9] -> dy;
	
}

if (game -> counterharmonic > 30 && game -> counterharmonic < 60)
	
	{
	game -> allien[0] -> dy = 0.5;
	game -> allien[0] -> y -= game -> allien[0] -> dy;
	game -> allien[1] -> dy = 0.5;
	game -> allien[1] -> y -= game -> allien[1] -> dy;
	game -> allien[2] -> dy = 0.5;
	game -> allien[2] -> y -= game -> allien[2] -> dy;
	game -> allien[3] -> dy = 0.5;
	game -> allien[3] -> y -= game -> allien[3] -> dy;
	game -> allien[4] -> dy = 0.5;
	game -> allien[4] -> y -= game -> allien[4] -> dy;
	game -> allien[5] -> dy = 0.5;
	game -> allien[5] -> y -= game -> allien[5] -> dy;
	game -> allien[6] -> dy = 0.5;
	game -> allien[6] -> y -= game -> allien[6] -> dy;
	game -> allien[7] -> dy = 0.5;
	game -> allien[7] -> y -= game -> allien[7] -> dy;
	game -> allien[8] -> dy = 0.5;
	game -> allien[8] -> y -= game -> allien[8] -> dy;
	game -> allien[9] -> dy = 0.5;
	game -> allien[9] -> y -= game -> allien[9] -> dy;
	}
	
	if (game -> counterharmonic == 60)
	{
		game -> counterharmonic = 0;
	}

}

void fallingmotion(Game * game)
{

	
	
			game -> allien[0] -> dy = 0.5;
			game -> allien[0] -> y += game -> allien[0] -> dy;
			game -> allien[1] -> dy = 0.5;
			game -> allien[1] -> y += game -> allien[1] -> dy;
			game -> allien[2] -> dy = 0.5;
			game -> allien[2] -> y += game -> allien[2] -> dy;
			game -> allien[3] -> dy = 0.5;
			game -> allien[3] -> y += game -> allien[3] -> dy;
			game -> allien[4] -> dy = 0.5;
			game -> allien[4] -> y += game -> allien[4] -> dy;
			game -> allien[5] -> dy = 0.5;
			game -> allien[5] -> y += game -> allien[5] -> dy;
			game -> allien[6] -> dy = 0.5;
			game -> allien[6] -> y += game -> allien[6] -> dy;
			game -> allien[7] -> dy = 0.5;
			game -> allien[7] -> y += game -> allien[7] -> dy;
			game -> allien[8] -> dy = 0.5;
			game -> allien[8] -> y += game -> allien[8] -> dy;
			game -> allien[9] -> dy = 0.5;
			game -> allien[9] -> y += game -> allien[9] -> dy;
	
	

	
		for (int i = 0; i <= 9; i++)
		{
			
		if (game -> allien[i] -> y >= screen_height())
			{
			game -> allien[i] -> y = 0;
			game -> allien[i] -> y += game -> allien[i] -> dy;
			
			}
		if (game -> allien[i] -> x >= screen_width())
			{
			game -> allien[i] -> x = 0;
			game -> allien[i] -> x += game -> allien[i] -> dx;
			}

		int yallien = round(game -> allien[i] -> y);
		int xallien = round(game -> allien[i] -> x);
		int yspacecraft = round(game -> spacecraft -> y);
		int xspacecraft = round(game -> spacecraft -> x);
		
		
		if (yallien == yspacecraft && xallien == xspacecraft)
		{
			game -> allien[i] -> is_visible = false;
			game -> lives--;
		}
	
		}

}

void drunkenmotion(Game * game)
{
	


game -> counterdrunken++;





if (game -> counterdrunken == 30)
{

srand(time(NULL));

int dxallien0 = 5 + rand() % 10;
int dxallien1 = 5 + rand() % 10;
int dxallien2 = 5 + rand() % 10;
int dxallien3 = 1 + rand() % 4;
int dxallien4 = 1 + rand() % 4; 
int dxallien5 = 1 + rand() % 4; 
int dxallien6 = 1 + rand() % 4;
int dxallien7 = 5 + rand() % 10;
int dxallien8 = 5 + rand() % 10;
int dxallien9 = 5 + rand() % 10;


game -> allien[8] -> x += dxallien8;
game -> allien[7] -> x += dxallien7;
game -> allien[9] -> x += dxallien9;
game -> allien[3] -> x += dxallien3;
game -> allien[4] -> x += dxallien4;

game -> allien[0] -> x -= dxallien0;
game -> allien[1] -> x -= dxallien1;
game -> allien[2] -> x -= dxallien2;
game -> allien[6] -> x -= dxallien6;
game -> allien[5] -> x -= dxallien5;

}


if (game -> counterdrunken == 60)
{

srand(time(NULL));

int dxallien0 = 5 + rand() % 10;
int dxallien1 = 5 + rand() % 10;
int dxallien2 = 5 + rand() % 10;
int dxallien3 = 1 + rand() % 4;
int dxallien4 = 1 + rand() % 4; 
int dxallien5 = 1 + rand() % 4; 
int dxallien6 = 1 + rand() % 4;
int dxallien7 = 5 + rand() % 10;
int dxallien8 = 5 + rand() % 10;
int dxallien9 = 5 + rand() % 10;
	
	
game -> allien[8] -> x -= dxallien8;
game -> allien[7] -> x -= dxallien7;
game -> allien[9] -> x -= dxallien9;
game -> allien[3] -> x -= dxallien3;
game -> allien[4] -> x -= dxallien4;

game -> allien[0] -> x += dxallien0;
game -> allien[1] -> x += dxallien1;
game -> allien[2] -> x += dxallien2;
game -> allien[6] -> x += dxallien6;
game -> allien[5] -> x += dxallien5;
}


if (game -> counterdrunken == 60)
{
	game -> counterdrunken = 0;
}
}


int main( void ) {
	int key = get_char();
	int level = 1;
	Game game;
	setup_screen();
	setup_game (&game);
	while (key != 'q' ||  key != 'r')
	{
	
	if (key == 'l')
	{
		level ++;
	}

		clear_screen();
		key = get_char();
		draw_menu(&game);
		draw_bottom_string();
		update_spacecraft(&game,key);
		draw_alliens(&game);
		update_bombs (&game);
		update_rocket(&game,key);
		update_alliens(&game);
		show_screen ();
		timer_pause( 50 );
		if (level == 2)
		{
		break;
		}
	}

	while (key != 'q' ||  key != 'r')
	{
	if (key == 'l')
	{
		level ++;
	}
		clear_screen();
		key = get_char();
		draw_menu(&game);
		draw_bottom_string();
		update_spacecraft(&game,key);
		draw_alliens(&game);
		update_alliens(&game);
		harmonicmotion(&game);
		update_bombs (&game);
		update_rocket(&game,key);
		show_screen ();
		timer_pause( 50 );
		if (level == 3)
		{
			break;
		}
			
	}
	
	while (key != 'q' ||  key != 'r')
	{
	if (key == 'l')
	{
		level ++;
	}

		clear_screen();
		key = get_char();
		draw_menu(&game);
		draw_bottom_string();
		update_spacecraft(&game,key);
		draw_alliens(&game);
		update_alliens(&game);
		fallingmotion(&game);
		update_bombs (&game);
		update_rocket(&game,key);
		show_screen ();
		timer_pause( 50 );
		if (level == 4)
		{
			break;
		}
	}
	
		while (key != 'q' ||  key != 'r')
	{
	if (key == 'l')
	{
		level ++;
	}

		clear_screen();
		key = get_char();
		draw_menu(&game);
		draw_bottom_string();
		update_spacecraft(&game,key);
		draw_alliens(&game);
		update_alliens(&game);
		fallingmotion(&game);
		drunkenmotion(&game);
		update_bombs (&game);
		update_rocket(&game,key);
		show_screen ();
		timer_pause( 50 );
	
	}
	
	cleanup_screen ();
	return 0;
}
