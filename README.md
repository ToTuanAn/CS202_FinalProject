# CS202_FinalProject
### UI (An - Hiep)
#### Start Menu
- New Game
- Load
- Settings
	- Difficulty
	- Music Volume
#### In-game Menu (Press P (or another key) to pause the game and display this Menu)
- Save
- Back to game
- Exit (to Start Menu)
#### Dead Menu
- Exit (to Start Menu)
### Save Load System (Hung)
#### Save
#### Load
#### Saveable Objects:
- Player
- GameWorld (to draw tilemap)
- ListSpawner (list of Spawners)
### Traffic (Teacher)
#### Create TrafficLight class
- Sprite (3 colors)
- Time to switch color
- Is red (use in `update()` method of Spawner)
#### In Spawner class
- Add trafficLight as a property
- Add initialSpped
    ```
    if (trafficLight.isRed())
        setEnemiesSpeed(0);
    else
        setEnemiesSpeed(initialSpped);
    ```