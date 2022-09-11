# battleshipcpp
Introduction:
Battleship is a guessing game for two players. It is played on
ruled grids on which each player’s fleet of ships are marked.
The locations of the fleets are concealed from the other
player. Players alternate turns calling &quot;shots&quot; at the other
player&#39;s ships, and the objective of the game is to destroy the
opposing player&#39;s fleet. This is a modern version of Battleship
developed using C++ programming language

How to Play:

When the game starts the player is shown a menu screen with
5 options: 1-player, 2-player, help and exit.
1-Player/2-Player Mode:

Getting Started:
When the player selects 1-player or 2-player, a login screen is
displayed prompting the player(s) to enter an username and
password. If there exists a saved game with the same
credentials, the player is asked if he wants to continue the
saved game. If yes, the saved game is loaded and the player(s)
can continue playing. Else the saved game is deleted and a
new game is started.
Placing Ships:
When a new game is started, the player(s) need to store the
ships in a square grid. The number of ships and grid size can be
modified by the admin. Default size of the grid is 8x8 and the
number of ships is 5. The rows of the grid are represented by
alphabets and the columns are represented by numbers.

Positions on the grid are represented by row letter followed by
column number (example a1, H8). The player has to select a
base position and an appropriate orientation that is either
horizontal (represented by ‘h’ or ‘H’) or vertical (represented
by ‘v’ or ‘V’). If the entered base position or the orientation is
invalid, the player is prompted to either modify the base
position or the orientation.
Playing the Game:
Once all the ships are stored, the player and the computer (in
1-player mode) or the players (in 2-player mode) alternate
turns to guess the ships’ coordinates. If a ship is hit, that spot
on the grid turns red and the player gets to play one more
turn. If it is a miss that spot on the grid turns white. If an entire
ship is destroyed, then a message will be displayed with the
details of the destroyed ship. The high scores are displayed
once the game is finished. If the player is already on
leaderboard, his all-time best score is retained.
Pausing and Resuming the Game:
Mid-game, the player can save his progress by pressing the
‘ESC’ key. The player is asked whether he would like to save
the game in its current state or discard it. If the answer is yes
the game is saved and the player is taken to main menu. Else
the current game is discarded and the player is taken to main
menu. The saved game can be continued by logging in with the
same credentials.
High Scores:
In this page the user can view all the top scores of players who
have won the game ordered by their scores. The scores can
run to multiple pages too.

About Page:
It displays the synopsis of the game Battleship. On pressing ‘a’
key, the user gets to visit the administrator options.
Administrator Page:
In this page the admin can login with the correct credentials.
Once the administrator is logged in, the grid size and the
number of ships can be modified.
Minimum number of ships is 5 and maximum is 8.
Minimum grid size is 5X5 and maximum is 9X9.

Concepts used in the project:

 Structures
 Binary Files
1. 1PLYR.DAT- Stores the Single Player Mode saved games
2. 2PLYR.DAT- Stores the Two Player Mode saved games
3. SCORES.DAT- Stores the high scores of both game modes
Binary File Operations: Adding Records, Updating Records and
Deleting Records
 Functions(implements Modularity)
 Function Overloading(Polymorphism)
 Graphics
 Pointers &amp; Dynamic memory allocation
