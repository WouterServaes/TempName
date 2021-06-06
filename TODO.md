
# Minigin things to do/add
## General:
- use noexcept when function can't have exception (x*y cant ever fail) (use noexcept by default)
- Check naming
- Cleanup data folder
- Use static_cast<> instead
- document that Logger is used for error handling in the engine/game

## ResourceManager:
- multi thread resource loading

## IMPORTANT
- Versus - One player plays as Q*bert, another player can play as a Coily. The Coily player bounces to the bottom and then gets control.

- Load game level from file
-> json or xml: array of gameObjects with array of Components and object name and object position + scale and if object is active
        array of components:
            use class names of components,
            dont include transform component
            per component, define important component attributes

            <SomeComp>
                <Attr1> lkrgjklg </Attr1>
                <Attr2> lkrgjklg </Attr2>
            </SomeComp>

change to binary if time.

- Update sprite sheets to nicer ones.
- Add main menu background + title + make buttons nicer

- fix purple's movement

     