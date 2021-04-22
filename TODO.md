# Minigin things to do/add
## General:
- Improve InputManager
- Fix keyboard input
- Add prefab game objects
- Instead of throw std::runtime_error in code, make a static Logger class that does this
- Add rule-of-5 stuff
- Check naming
- Cleanup data folder
- Use static_cast<> instead
- Make separate game project in solution
## Audio:
- Better multi threading

- Use condition variable instead of sleep for  std::conditional variable
- non atomic operations in .store(.load - 1)
- Queueu is not really a queueu 
- BaseAudio is not an interface, also a bad name (AddSoundFile + vectors)
- Storing/retrieving requests from the queue is not correct
- Logging sound system is a wrapper of the current sound system (current sound system as member var, simple cout + currentSoundSystem.Play in Play of LoggerSoundSystem )
-conditional variables
notify 1

## PlayerObserver:
- Fix ugly UpdateHealthUI/GetScoreTextComponent if()
