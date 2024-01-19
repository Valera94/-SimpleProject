# -SimpleProject for HeadHunter
С++ SimpleProject => Press to download [SimpleProject-TestMovement](https://drive.google.com/file/d/1BtmU8JW-ttMAw_RstFgv0tuY9B9Yg6Xr/view?usp=sharing)

> [!WARNING]
> When the project creation stage reaches the level of deep knowledge and tricks, the project will be closed for download and review, at the moment you see a simple form of code that I don't mind giving away.

# Road Map:

+ Step 1 (Complete) - Create a small game prototype.
   - Architectural map of the game
   - Base UI/UX
     - Game UI/UX
   - Base Controller
     - Standard controller RTS camera
     - Standard key press
   - Base Game Mechanic
     - Create Wall
     - Create Build
     - Create new unit (skip)


  
+ Step 2 (Current)- Add need game core.
   - Building Instance manager.
   - DataTable : Building/Resources/Units
   - Global camera switching.



+ Step 3 - The project will be closed, but a demo version of the game with possible results will be available.
 -Adding global logic and configuring ChunkManager and Chunk.
   - Adding logic for working with LightWeightInstanceStaticMeshMesh.
   - Create a path calculation algorithm using VectorFieldMovement
   - Working with squads.
      -Creation of a system (Variations).
      - Moving using ChunkManager.
   - Start working on the ECS architecture.

  
# UI/UX

> [!NOTE]
> "Game UI/UX" - When using one type of mod, we disable the other mod, and everything connected to it.

![image](https://github.com/Valera94/-SimpleProject/assets/91465697/3166136d-3de6-4fbf-9577-aedb308873bc)

# Architectural map of the game

> [!NOTE]
> An approximate tree-like logical relationship.
>
> 
![image](https://github.com/Valera94/-SimpleProject/assets/91465697/cf6f5203-3445-4a22-8205-55ef97d6215c)
![image](https://github.com/Valera94/-SimpleProject/assets/91465697/fb0cad9a-902a-453b-95f7-50d124d56be3)


# Data
>[!NOTE]
> Game data- Prepared data structures. Initially, we are ready for the implementation of leveling levels,
> a variety of races, as well as the possibility of combining resources with each other in order to obtain a valuable resource at the exit.
>
![image](https://github.com/Valera94/-SimpleProject/assets/91465697/3d0a4b72-e100-4736-8d65-aa6429714bc6)
![image](https://github.com/Valera94/-SimpleProject/assets/91465697/f15f5355-9cbf-4179-8828-d0f318e15590)
