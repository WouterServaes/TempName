
# Minigin things to do/add
## General:
- use noexcept when function can't have exception (x*y cant ever fail) (use noexcept by default)
- Add rule-of-5 stuff
- Check naming
- Cleanup data folder
- Use static_cast<> instead
- Add End() to BaseComponent, use this is destructor in components
- document that Logger is used for error handling in the engine/game
- don't crash when resource isn't found, just continue with empty resource and display message

## Audio:
- let someone double check 

## PlayerObserver:
- Fix ugly UpdateHealthUI/GetScoreTextComponent if()

## ResourceManager:
- multi thread resource loading


