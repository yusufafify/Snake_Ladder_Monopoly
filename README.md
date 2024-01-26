# Snake and Ladder Monopoly Game


![Static badge/](https://badgen.net/badge/C++/OOP) ![badge 2](https://badgen.net/badge/Project/GUI)

![image](https://i.pinimg.com/750x/40/50/5e/40505e9fddcdc42224258ba24bcfda98.jpg)

## Description
This project is a fun and interactive console-based game that combines the elements of the classic games of Snake and Ladder and Monopoly. It is developed using C++ and follows the principles of Object-Oriented Programming (OOP).

![image ](https://i.pinimg.com/750x/ad/a9/f5/ada9f502bdb9fc9de6952fee3ba740a1.jpg)

## Features
- **Multiplayer:** The game supports multiple players.
- **Interactive Gameplay:** The game provides an interactive console-based interface.
- **Object-Oriented Design:** The game is designed using OOP principles, making the code modular and easy to understand.

## Special Attacks:
Every player can choose 2 unique from 4 special attacks that will help him reach the final cell first
A player can choose during his “recharge the wallet” turn to launch a special attack instead of recharging his wallet. (If he is not denied from rolling dice)
- **Fire Attack:** Choose a player to burn. Deduct 20 coins from his wallet for his next 3 turns 
- **Ice Attack:** Choose a player to prevent from rolling the next turn.
- **Lightnining Attack:** Deduct 20 coins from all other players.
- **Poison Attack:** Choose a player to poison. For 5 turns, deduct 1 number from his dice roll


## Installation
To install the game, follow these steps:
1. Clone the repository: `git clone https://github.com/Ma7moudMSA/Snake-and-Ladder-Monopoly-game.git`
2. Navigate to the project directory: `cd snake-and-ladder-monopoly`
3. Compile the code: `g++ -o game Main.cpp
4.Run the Main.cpp and the game would start 

## Usage
Run the game .\game
## Contributing
Contributions are welcome! Please read the contributing guidelines before getting started.

## Bugs
1. if you clicked on mouse while the program is waiting for keyboard input the program will store the clicked value place in the buffer and after executing the initial command it will be done 
2. there is an issue in delete function where it does delete the cell however when saved to be opened again the data would not be updated and the removed cell will remain on the screen but without any functions 



