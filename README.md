# Minigin

## Table of conten
- [In short](#inShort)
- [A Minigin Game](#game)
    - [Scene Manager](#sceneManager)
    - [Scenes](#scenes)
    - [Game Objects](#gameObjects)
    - [Subjects and Observers](#subjectsObservers)
    - [User input and commands](#inputCommands)
    - [Audio Service Locator](#audio)
- [Rendering](#rendering)
- [References](#ref)

## In short <a name ="inShort"></a>
Minigin is a simple 2D game engine. At its core it uses the basic Game Loop pattern we all know.
A Minigin game is made up of multiple Scenes consisting of Game Objects. I use the Entity Component System for the Game Objects.
Game Objects can be Subjects to use Observers. 
For the game sound I use the Service Locator pattern, multiple sound systems can be made and used without changing the engine itself.
I made a logging system to easily show info and warnings in the console. The logging system can also be used to throw an error box with multiple options. 
All input is handled by the InputManager. 

## A Minigin Game <a name ="game"></a>
A Minigin game is made by making derived class from Minigin, calling Run in the main function and deleting it after the Run() call.
The Minigin class has a pure virtual LoadGame() function, this is used to add scenes to the game using the SceneManager

### Scene Manager <a name ="sceneManager"></a>
The scene manager is a Singleton that holds the container containing all the scenes. Scenes can easily be added, loaded and restarted.

### Scenes <a name ="scenes"></a>
A scene is an object derived from Scene. It has the pure virtual function InitializeScene(), used to add every game object to the scene. The virtual Restart function should be used to define how a restart should happen. Instead of making a new scene and really restarting it I provide this Restart function. This is better and faster for the small scope of this project (both for me and the program itself). Every scene has a name, this can be used to load a different scene. 

### Game Objects <a name ="gameObjects"></a>
I use the Entity Component System (ECS) for the game objects. It's well worth the extra effort as only a handfull of components can make a bunch of differently acting objects depending on the components on the game objects. 

### Subjects and Observers <a name ="subjectsObservers"></a>
The observer pattern can be used on Game Objects by marking a Game Object as Subject. An event can be fired to the Subject and will be picked up by every observer handling this event. It was hard to determine when to use the pattern and when not to, but I've learned a lot.

### User input and commands <a name ="inputCommands"></a>
The input manager stores a std::map of InputActions and Commands. An input action holds the SDL_KeyCode and triggerState of a key and the Controller button and number of a controller. When an input action is triggered, the command gets executed.

### Audio Service Locator <a name ="audio"></a>
I use the Service Locator pattern for the audio to easily use custom audio services. The AudioInterface can be used to make custom sound services, for the project I use [Simple SDL2 Audio](https://github.com/jakebesworth/Simple-SDL2-Audio). 


## Rendering <a name ="rendering"></a>


## References <a name ="ref"></a>
Entity Component System. https://gameprogrammingpatterns.com/component.html
Game loop https://gameprogrammingpatterns.com/game-loop.html
Observer https://gameprogrammingpatterns.com/observer.html
Service Locator https://gameprogrammingpatterns.com/service-locator.html
Commands https://gameprogrammingpatterns.com/command.html