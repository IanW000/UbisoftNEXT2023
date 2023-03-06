# BOMB! BOMB! BOMB!!
![Bomb!Screenshots1](https://user-images.githubusercontent.com/90727502/223161603-9fb18300-0b2c-48af-a139-1570e7c05f88.png)
![Bomb!Screenshots2](https://user-images.githubusercontent.com/90727502/223161630-d4560590-ef3f-41eb-96da-a3530d5d7cd7.png)


## Game Description

#### "Get ready to blow up everything with Bomberman!"

BOMB! BOMB! BOMB! is a bomberman-like game made in C++ for the Ubisoft NEXT 2021 programming competition.

***[Watch the Gameplay Demo!](https://www.youtube.com/watch?v=oexk9rBuHZE&t=1s)***


## Features

- **Tilemap** - The game level is made by a tilemap which is stored as a two-dimensional array. Each tile in the map is a Tile object, which contains the tile type, and corresponding image. For simplicity, a tile can be set to 3 types: GROUND, BLOCK, and BRICK.

- **Procedurally Generated Map** - The map is randomly generated with different objects placement in every game. And the player and enemy will start off at random positions which are diagonal to each other with a certain distance 

- **Bomb** - The player needs to strategically place down bombs in order to destroy enemies and uncover doors behind destructible tiles. The bombs can explode in multiple directions after a short delay, and turn the BRICK tiles into GROUND. 

- **Powerup** - The player can pick up various power-ups, giving them benefits such as larger explosions or the ability to place more bombs down at a time. The powerups are dropped from Bricks tiles when destructed by bombs (in a certain drop rate)

- **Enemy** - The enemy has a simple AI which keep chasing at player and place bombs

- **Win/Fail Condition** - The game will end if the player or enemy are getting killed by bombs

- **UI** - ① Screens for MAIN MENU, PAUSE, WIN, FAIL, CONTROLS ② Interactive buttons with CLICK/HOVER Animations/SFX ③ In-game text and HP Bars which reflects realtime player and enemy's status 

## Installation and Usage
Run .sln file in Visual Studio 2022 and START it!


## Dependencies
API provided by Ubisoft which using OpenGL and FreeGlut only


## Assets

#### Sprites:

- https://github.com/zigurous/unity-bomberman-tutorial/tree/main/Sprites

#### Sounds:

- Click - https://freesound.org/people/herraportti/sounds/436667/

- Hover - https://freesound.org/people/Terry93D/sounds/329943/

- GameBGM -  https://freesound.org/people/BloodPixelHero/sounds/648490/

- MainMenuBGM - https://freesound.org/people/OwlStorm/sounds/404743/

- Fail - https://freesound.org/people/InspectorJ/sounds/443623/

- Take Damage - https://freesound.org/people/InspectorJ/sounds/448226/

- Pickup - https://freesound.org/people/jeremysykes/sounds/341227/
