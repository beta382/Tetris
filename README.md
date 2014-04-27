#Tetris

Group project for CSI 1440 - Freshman Spring Semester

For complete documentation, check out the source code.

## Outline

***Bold Italics*** indicates an abstract object

- [Public API overview](https://github.com/beta382/Tetris#public-api-overview)
  - [Objects](https://github.com/beta382/Tetris#objects)
    - [***Drawable***](https://github.com/beta382/Tetris#drawable)
      - [***Screen***](https://github.com/beta382/Tetris#screen)
        - [Game](https://github.com/beta382/Tetris#game)
        - [PauseScreen](https://github/beta382/Tetris#pausescreen)
      - [PlayingField](https://github.com/beta382/Tetris#playingfield)
      - [Shape](https://github.com/beta382/Tetris#shape)
        - [***TetrominoBase***](https://github.com/beta382/Tetris#tetrominobase)
          - [Tetromino\<BlockType\>](https://github.com/beta382/Tetris#tetrominoblocktype)
      - [Block](https://github.com/beta382/Tetris#block)
        - [GhostBlock](https://github.com/beta382/Tetris#ghostblock)
        - [ExplodingBlock](https://github.com/beta382/Tetris#explodingblock)
        - [GravityBlock](https://github.com/beta382/Tetris#gravityblock)
    - Tetris (Provided by instructor, no docs)
    - GLUT_Plotter (Provided by instructor, no docs)
  - [Enumerations](https://github.com/beta382/Tetris#enumerations)
    - [TetrominoShape](https://github.com/beta382/Tetris#tetrominoshape)
  - [Namespaces](https://github.com/beta382/Tetris#namespaces)
    - [Color](https://github.com/beta382/Tetris#color)
    - [Key](https://github.com/beta382/Tetris#key)
    - [util](https://github.com/beta382/Tetris#util)
    - [leakcheck](https://github.com/beta382/Tetris#leakcheck)
- [How to use leakcheck](https://github.com/beta382/Tetris#how-to-use-leakcheck)

## Public API overview: 

### Objects

#### ***Drawable***

```cpp
virtual void setWidth(int);
virtual int getWidth() const;
virtual void setHeight(int);
virtual int getHeight() const;
virtual void setLocation(int, int);
virtual int getLocationX() const;
virtual int getLocationY() const;
virtual void setForeground(unsigned int);
virtual unsigned int getForeground() const;
virtual void setBackground(unsigned int);
virtual unsigned int getBackground() const;
virtual void blink(int, clock_t);

static void setG(GLUT_Plotter*);

/* --- Pure virtual --- */
virtual void draw();
virtual void erase();
```
    
#### ***Screen***

```cpp
bool shouldRetain();

/* --- Pure virtual --- */
virtual Screen* respondToKey(int);
vitrual Screen* respondToClick(Click);
virtual void doBackground();
```

#### Game

```cpp
Game(unsigned int color = Color::BLACK);

/* --- Implemented from Screen --- */
Screen* respondToKey(int);
Screen* respondToClick(Click);
void doBackground();

/* --- Implemented from Drawable --- */
void draw();
void erase();
```

#### PauseScreen

```cpp
PauseScreen(Screen*);

/* --- Implemented from Screen --- */
Screen* respondToKey(int);
Screen* respondToClick(Click);
void doBackground();

/* --- Implemented from Drawable --- */
void draw();
void erase();
```

#### PlayingField

```cpp
PlayingField();
PlayingField(int x, int y, int width, int height, int blockSize, int padding,
    unsigned int foreground = Color::WHITE, unsigned int background = Color::BLACK, 
    int borderWidth = 0, unsigned int borderColor = Color::GRAY);
PlayingField(const PlayingField&);
PlayingField& operator =(const PlayingField&);

template <typename BlockType>
Tetromino<BlockType>* spawnNewTetromino(TetrominoShape) const;

int mergeAndDelete(Shape*);

int getBlockSize() const;
int getPadding() const;
int getTotalBlockSize() const;

bool canShiftUp(const Shape*) const;
bool canShiftDown(const Shape*) const;
bool canShiftLeft(const Shape*) const;
bool canShiftRight(const Shape*) const;
bool canRotateCW(const TetrominoBase*) const;
bool canRotateCCW(const TetrominoBase*) const;

/* --- Overriding from Drawable --- */
int getWidth() const;
int getHeight() const;
void setLocation(int, int);

/* --- Implemented from Drawable --- */
void draw();
void erase();
```

#### Shape

```cpp
Shape();
Shape(int x, int y, int blockSize, int padding, unsigned int background = Color::BLACK);
Shape(const Shape&);
Shape& operator =(const Shape&);

Block* getBlock(int) const;
Shape& addBlock(Block*);

int numBlocks() const;
int getBlockSize() const;
int getPadding() const;
int getTotalBlockSize() const;

void shiftUp();
void shiftDown();
void shiftLeft();
void shiftRight();

Block*& operator [](int);

/* --- Overriding from Drawable --- */
int getWidth() const;
int getHeight() const;
void setLocation(int, int);
void setForeground (unsigned int);
void setBackground (unsigned int);

/* --- Implemented from Drawable --- */
void draw();
void erase();

```

#### ***TetrominoBase***

```cpp
void rotateCW();
void rotateCCW();

/* --- Pure virtual --- */
virtual TetrominoBase* makeNewClone() const;
```

#### Tetromino\<BlockType\>

```cpp
Tetromino();
Tetromino(int x, int y, int blockSize, int padding, TetrominoShape shape,
                unsigned int background = Color::BLACK);
Tetromino(const Tetromino<BlockType>&);
Tetromino<BlockType>& operator =(const Tetromino<BlockType>&);

/* --- Implimented from TetrominoBase --- */
Tetromino<BlockType>* makeNewClone() const;
```


#### Block

```cpp
Block();
Block(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
Block(const Block&);
Block& operator =(const Block&);

int getSize() const;
int getPadding() const;
int getTotalSize() const;
unsigned int getUniqueID() const;
void setUniqueID(unsigned int);
virtual int doEffect(vector<vector<Block*> >&, int x, int y);
virtual Block* makeNewClone() const;

/* --- Implemented from Drawable --- */
void draw();
void erase();
```

#### GhostBlock

```cpp
GhostBlock();
GhostBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);
GhostBlock(const GhostBlock&);
GhostBlock& operator =(const GhostBlock&);

/* --- Overriding from Block --- */
int doEffect(vector<vector<Block*> >&, int x, int y);
GhostBlock* makeNewClone() const;
void draw();
```

#### ExplodingBlock

```cpp
ExplodingBlock();
ExplodingBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);
ExplodingBlock(const ExplodingBlock&);
ExplodingBlock& operator =(const ExplodingBlock&);

/* --- Overriding from Block --- */
int doEffect(vector<vector<Block*> >&, int x, int y);
ExplodingBlock* makeNewClone() const;
void draw();
```

#### GravityBlock

```cpp
GravityBlock();
GravityBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);
GravityBlock(const GravityBlock&);
GravityBlock& operator =(const GravityBlock&);

/* --- Overriding from Block --- */
int doEffect(vector<vector<Block*> >&, int x, int y);
GravityBlock* makeNewClone() const;
void draw();
```

### Enumerations

#### TetrominoShape

```cpp
enum TetrominoShape {I, O, T, J, L, S, Z};
```

### Namespaces

#### Color

```cpp
const unsigned int WHITE;
const unsigned int BLACK;
const unsigned int BLUE;
const unsigned int BROWN;
const unsigned int GREEN;
const unsigned int GRAY;
const unsigned int LIGHT_GRAY;
const unsigned int RED;
const unsigned int TAN;
const unsigned int LIGHT_TAN;
const unsigned int DARK_TAN;
const unsigned int DARK_GREEN;
const unsigned int CYAN;
```

#### Key

```cpp
const int UP;
const int DOWN;
const int LEFT;
const int RIGHT;
const int ESC;
```

#### util

```cpp
void wait(clock_t);
```

#### leakcheck

```cpp
map<void*, pair<string, size_t> > allocated;

void report(ostream& out);
size_t bytes();
```

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
