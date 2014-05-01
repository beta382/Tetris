#Tetris

Group project for CSI 1440 - Freshman Spring Semester

For complete documentation, check out the source code.

## Project structure

***Bold Italics*** indicates an abstract object

- Objects
  - ***Drawable***
    - ***Screen***
      - MenuScreen
      - InstructionScreen
      - GameScreen
      - PauseScreen
      - ConfirmScreen
      - GameOverScreen
    - PlayingField
    - Shape
      - ***TetrominoBase***
        - Tetromino\<BlockType\>
      - BlockString
      - Logo
    - Block
      - GhostBlock
      - ExplodingBlock
      - GravityBlock
      - LeftMagnetBlock
      - RightMagnetBlock
      - LaserBlock
    - Rect
  - Tetris (Provided by instructor, no docs)
  - GLUT_Plotter (Provided by instructor, no docs)
- Enumerations
  - TetrominoShape
- Namespaces
  - Color
  - Key
  - util
  - leakcheck

##How to use leakcheck

It's super simple. First, either tell your compiler to define DO_LEAKCHECK (for g++, just add the `-DDO_LEAKCHECK` flag
to your compile options; your IDE should allow you to define build configurations for Release and Debug separately, add
this flag to the Debug build configuration), or define DO_LEAKCHECK manually at the top of "util.h" (Note that if you
don't define DO_LEAKCHECK, or build from a configuration that doesn't define DO_LEAKCHECK, you can add the code detailed
below, and it will safely have no effect). Then in the header(s) of the object(s) you want to track, include "util.h"
and add the following code inside your object declaration:

```cpp
_registerForLeakcheckWithID(ID)
```

where `ID` is the name of your object. You can put whatever you want; allocations will get logged using a string
representation of what you put as the ID. Note that you do not include string-literal quotes around ID. For example:

```cpp
class Foo {
_registerForLeakcheckWithID(Bar)

// Rest of declaration goes here
}
```

will log heap memory allocations for Foo objects using the ID "Bar". It is recommended you use the object name as the 
ID, this example just shows that you aren't forced to use the same name.

To output a report of the tracked objects currently on the heap to the console, insert:

```cpp
leakcheck::report(cout);
```

somewhere in your code.

To show a summary when your program dies, add the same code before an exit point (either the end of main or a call to
`exit(int)`). For best results, make sure that all dynamically allocated data is deleted prior to sumarizing and
exiting. This includes forcing objects you know are dynamically allocated to commit suicide (`delete this;`) if control
will reach a call to `exit(int)` from within the object.

Example code:

```cpp
switch (foo) {
    case 0: // ShouldDoCode
        // Code goes here
        break;
    case 1: // ShouldPrint
        leakcheck::report(cout);
        break;
    case 2: // ShouldExit
        delete someObjectThatIsDynamicallyAllocated;
        delete anotherDynamicallyAllocatedObject;
        leakcheck::report(cout);
        exit(0);
        break;
}
```

Hopefully, your final summary will look like this:

```
-------------------------------------------------------------------------------

No tracked objects on heap.

Currently have 0 objects allocated consuming 0 bytes.

-------------------------------------------------------------------------------
```

If you are leaking objects that you are tracking, your final summary will look something like this:

```
-------------------------------------------------------------------------------

Tracked objects on heap:
// ... Lots of output here
0x6099790   Shape               52
0x60997d0   Shape               52
0x6099810   Shape               52
0x609d8b8   GhostBlock          40
0x609d8e8   Block               40
0x609d918   Block               40
0x609d948   Block               40
// ... Lots more output here
0x60a1788   GhostBlock          40
0x60a17b8   GhostBlock          40
0x60a17e8   GhostBlock          40
0x60a1818   GhostBlock          40

Currently have 3222 objects allocated consuming 136584 bytes.

-------------------------------------------------------------------------------
```

The object ID's should give you an idea of WHAT you are leaking, and from there, it should be relatively straightfoward
to find WHERE you are allocating an object of that type and failing to delete it.
