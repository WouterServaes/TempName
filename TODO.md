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
- Thread should be managed by service (start it there)
- Use condition variable instead of sleep for  std::conditional variable
- non atomic operations in .store(.load - 1)
- Queueu is not really a queueu 
- BaseAudio is not an interface, also a bad name (AddSoundFile + vectors)
- Storing/retrieving requests from the queue is not correct
## PlayerObserver:
- Fix ugly UpdateHealthUI/GetScoreTextComponent if()
