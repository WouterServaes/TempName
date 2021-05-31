
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
- change wchar_t to char + cleanup  Subject* GameObject::GetSubject() const  

## PlayerObserver:
- Fix ugly UpdateHealthUI/GetScoreTextComponent if()

## ResourceManager:
- multi thread resource loading

## Events:
- revisit event and handling of events. remove enum class, change to array of strings/idx ?
- events shouldnt be defined in the engine project  

## Minigin.cpp
- Ability to set audio system