```
         _          _            _      
        /\ \       /\ \         /\ \    
       /  \ \     /  \ \____   /  \ \   
      / /\ \ \   / /\ \_____\ / /\ \ \  
     / / /\ \_\ / / /\/___  // / /\ \_\ 
    / /_/_ \/_// / /   / / // /_/_ \/_/ 
   / /____/\  / / /   / / // /____/\    
  / /\____\/ / / /   / / // /\____\/    
 / / /       \ \ \__/ / // / /          
/ / /         \ \___\/ // / /           
\/_/           \/_____/ \/_/            
                                                                                      
```
<h1 align="center">Fil de Fer // 3D Wireframes</h1>

<p align="center">
  <img src="https://github.com/user-attachments/assets/e68f358d-8041-4cf8-be2f-500cb5eedb43" alt="fdf demo"/>
</p>

This project consists on rendering 3D wireframes, it was made with C and the MLX graphics library developed by 42. Example files that can be passed as input can be found at `./maps`. You may realize that some directories can be passed as an input to the program, those are the animated maps, and each file inside them corresponds to a frame (example above).

## Requirements

MLX42 is dependent of X11, so you will need to be using it as your window system.

- A C compiler
- Make
- X11 ([but not for long!](https://github.com/FelBenini/SampaLX))

## Compiling, Installing and Running

First, clone the repository

```bash
git clone https://github.com/FelBenini/FDF.git
cd FDF
```

After cloning, run the following command inside the project's directory:

```bash
make bonus
```

If you simply run 'make', it will compile a more basic with less features version of the program.

Finally, you will be able to run the program passing a file as an argument.

```bash
./fdf ./path/to/the/file/map
```

## Generating any map with an image

For this step you might want to take a look at my other repository: [img_to_fdf](https://github.com/FelBenini/img_to_fdf)!

## Showcase

<img width="1918" height="1012" alt="image" src="https://github.com/user-attachments/assets/be50f58c-e4d6-4adc-a16c-63d5da21bd69" />

<img width="1918" height="1012" alt="image" src="https://github.com/user-attachments/assets/85a1a454-bb07-46ca-b849-4f2b491d46dc" />

<img width="1918" height="1012" alt="image" src="https://github.com/user-attachments/assets/8bd229ed-837a-42e4-bf8a-a0baac96d7a1" />

<img width="1918" height="1012" alt="image" src="https://github.com/user-attachments/assets/72870269-2d8e-4a3d-98b5-d41e90564013" />
