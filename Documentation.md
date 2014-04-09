#Documentation

##Drawable

Drawable is intended to be the abstract base class of all objects that are to be drawn to the screen. You MAY NOT
  independantly instantiate a Drawable object, this is enforced by making the constructors protected.
  
####Constructors
  - `Drawable()`: Initializes `int x`, `int y`, `int width`, and `int height` to 0, `unsigned int foreground` to
    `Color::WHITE`, `unsigned int background` to `Color::BLACK`, and `bool isVisible` to false.
  - `Drawable(int x, int y)`: Initializes `int x` and `int y` to the passed values, `int width`, and `int height` to
    0, `unsigned int foreground` to `Color::WHITE`, `unsigned int background` to `Color::BLACK`, and
    `bool isVisible` to false.
  - `Drawable(int x, int y, int width, int height, unsigned int foreground, unsigned int background)`: Initializes
    `int x`, `int y`, `int width`, `int height`, `unsigned int foreground`, and `unsigned int background` to the
    passed values, and `bool isVisible` to false.

####Protected member data
  - `int x`/`int y`: Are intended to define the pixel-location of the bottom-left corner of the Drawable's bounding
    rectangle. Descendants of Drawable MAY define and interpret these values however best suits its purpose.
  - `int width`/`int height`: Are intended to define the number of pixels wide/tall the Drawable's bounding rectangle
    is. Descendants of Drawable MAY define and interpret these values however best suits its purpose.
  - `unsigned int foreground`/`unsigned int background`: Are intended to define the foreground color and background
    color of the Drawable. Descendants of Drawable MAY define and interpret these values however best suits its
    purpose.
  - `bool isVisible`: Is intended to define whether or not the Drawable is visible on the screen. It is STRONGLY
    ENCOURAGED that you use this as a check when implementing `void erase()`, and that you set it accordingly
    at the end of your `void draw()` and `void erase()` implementations. It is STRONGLY ENCOURAGED that you NOT use
    this in a different manner than described.
    
####Protected static data
  - `GLUT_Plotter *g`: A shared GLUT_Plotter for all instances of objects that descend from Drawable.
 
####Public functions
  - `void setWidth(int)`/`int getWidth()`/`void setHeight(int)`/`int getHeight()`: Simple getters and setters for
    `int width` and `int height`.
  - `void setLocation(int, int)`/`int getLocationX()`/`int getLocationY()`: Simple getters and setters for `int x`
    and `int y`.
  - `void setForeground(unsigned int)`/`unsigned int getForeground()`/`void setBackground(unsigned int)`/`unsigned
    int getBackground()`: Simple getters and setters for `unsigned int foreground` and `unsigned int background`.
  - `void draw()`/`void erase()`: Pure virtual functions that MUST be implemented by descendants of Drawable to draw
    and erase the Drawable on the screen.

####All objects that directly inherit from Drawable MUST
  - Implement `void draw()`
  - Implement `void erase()`

####All objects that directly or indirectly inherit from Drawable MAY
  - Override `void setForeground(unsigned int)`
  - Override `void setBackground(unsigned int)`
  - Override `void setLocation(int, int)`

####All objects that directly or indirectly inherit from Drawable are STRONGLY ENGOURAGED to
  - Define a proper copy constructor that calls `Drawable(const Drawable&)`, even if there is no memory management
  - Define a proper assignment operator that calls `Drawable::operator =(const Drawable&)`, even if there is not
    memory management
  - (This is because each new Drawable, even if it is a copy, should have `bool isVisible` set to false regardless of its
    origin)
    
    
##Game

Inherits from Drawable.

Game is intended to represent the game screen, and be a wrapper for everything that the game screen contains. Game IS
  NOT intended to be inherited from.

####Constructors
  - `Game()`: Calls `Drawable()`, then calls `void init()`.

####Private member data
  - `PlayingField *field`: Pointer to a PlayingField object representing the main gameplay area.
  - `TetrominoBase *currentTetromino`: Pointer to a TetrominoBase object (which can be any Tetromino<BlockType>)
    representing the currently falling tetromino.

####Public functions
  - `void respondToKey(int)`: Performs a gameplay action based on the pressed key.

####Private functions
  - `void init()`: Initializes member data and the RNG, draws the initial state to the screen.

####Functions implemented from Drawable
  - `void draw()`
  - `void erase()`
    

##PlayingField

Inherits from Drawable.

PlayingField is intended to represent the field of blocks in play, and provide methods for general core gameplay,
  including generating and merging tetrominos and checking whether or not a shape can move or rotate within the block
  field. PlayingField IS NOT intended to be inherited from.
  
PlayingField defines and interprets `int width` and `int height` as the number of Blocks wide and tall the block
  field is.

####Constructors
  - `PlayingField()`: Calls `Drawable(0, 0, 10, 20)`, initializes `int blockSize` to 10 and `int padding` to 0, then
    calls `void init()`.
  - `PlayingField(int x, int y, int width, int height, int blockSize, int padding, unsigned int foreground,
    unsigned int background)`: Calls `Drawable(x, y, width, height, foreground, background)`, initializes
    `int blockSize` and `int padding` to the passed values, then calls `void init()`.

####Private member data
  - `vector<vector<Block *> > blocks`: A two-dimensional array of pointers to dynamically allocated Blocks,
     representing the Blocks currently on the field. The index of the Block DOES directly correlate to its on-screen
     location. Entries that don't contain a Block address will contain NULL.
  - `MyRectangle *bgRect`: A rectangle fill representing the background of the playing field.
  - `int blockSize`/`int padding`: The size of the Blocks and padding between Blocks.

####Public functions
  - `Tetromino<BlockType> *spawnNewTetromino(TetrominoShape)`: Allocates a new Tetromino<BlockType> with the
    specified shape and BlockType within the block field, and returns the address of the allocated
    Tetromino<BlockType>.
  - `void mergeAndDelete(Shape *)`: Merges a copy of the Shape into the block field, and then de-allocates the Shape.
  - `bool canShiftUp(Shape *)`/`bool canShiftDown(Shape *)`/`bool canShiftLeft(Shape *)`/`bool
    canShiftRight(Shape *)`: Determines whether or not the specified Shape can shift in the respective direction
    within the block field, without actually shifting the Shape.
  - `bool canRotateCW(TetrominoBase *)`/`bool canRotateCCW(TetrominoBase *)`: Determines whether or not the specified
    TetrominoBase can rotate in the respective direction within the block field, without actually rotating the
    TetrominoBase.

####Private functions
  - `void init()`: Initializes member data, draws the initial state to the screen.
  - `bool couldAdd(Block *)`: Determines whether or not the specified Block could be added to the block field without
    conflict.
  - `void doLineClear()`: Determines whether or not there needs to occur a line clear, and if so, performs the line
    clear.
  - `vector<Shape *> formShapes()`: Disassembles the block field and groups contiguous groups of Blocks into distinct
    Shapes, returning those Shapes. After running this, `vector<vector<Block *> > blocks` will be entirely NULL.
  - `void makeShapeRecursively(Shape *, int, int)`: Starting at the specified location in the block field, adds
    adjacent blocks to the Shape until all contiguous Blocks are added to the Shape.

####Functions implemented from Drawable
  - `void draw()`
  - `void erase()`

####Functions overridden from Drawable
  - `void SetLocation(int, int)`


##Shape

Inherits from Drawable.

Shape is intended to represent and be a wrapper for a collection of Blocks, and provide methods for interfacing with
  and manipulating the Blocks. Shape IS intended to be inherited from.
  
Shape DOES NOT use `int width`, `int height`, or `unsigned int foreground`. However subclasses of Shape MAY use these
  member data.

####Constructors
  - `Shape()`: Calls `Drawable()` and initializes `int blockSize` to 10 and `int padding` to 0.
  - `Shape(int x, int y, int blockSize, int padding, unsigned int background)`: Calls
    `Drawable(x, y, 0, 0, Color::WHITE, background)` and initializes `int blockSize` and `int padding` to the
    passed values.

####Protected member data
  - `vector<Block *> blocks`: An array of pointers to dynamically allocated Blocks, representing the Blocks contained
    within the Shape. The index of the Block DOES NOT correlate to its on-screen location.
  - `int blockSize`/`int padding`: The size of the Blocks and padding between Blocks.

####Public functions
  - `Block *getBlock(int)`: Gets the Block pointer at the specified index.
  - `int numBlocks()`: Returns the number of Blocks the Shape contains.
  - `int getBlockSize()`/`int getPadding()`/`int getTotalBlockSize()`: Getters for `int blockSize`, `int padding`,
    and the sum of both.
  - `void shiftUp()`/`void shiftDown()`/`void shiftLeft()`/`void shiftRight()`: Shifts the Shape one block in the
    respective direction, without performing checks. Within the context of a PlayingField, should be surrounded
    with a conditional.
  - `Shape& addBlock(Block *)`: Adds the Block pointer to the Shape, and returns the Shape by reference for chaining.

####Functions implemented from Drawable
  - `void draw()`
  - `void erase()`

####Functions overridden from Drawable
  - `void setLocation(int, int)`
  - `void setBackground(unsigned int)`
  - `void setForeground(unsigned int)`
    
    

##TetrominoShape

Enumeration of all possible shapes a TetrominoBase may take.
 

##TetrominoBase

Inherits from Shape.

TetrominoBase is intended to be the abstract base class for all possible Tetromino<BlockType> classes. You MAY NOT
  independantly instantiate a TetrominoBase object, this is enforced by making the constructors protected.

####Constructors
  - `TetrominoBase()`: Calls `Shape()` and initializes `int offsetX` and `int offsetY` to 0.
  - `TetrominoBase(int x, int y, int blockSize, int padding, unsigned int background)`: Calls
    `Shape(x, y, blockSize, padding, background)` and initializes `int offsetX` and `int offsetY` to the passed
    values.

####Protected member data
  - `int offsetX`/`int offsetY`: Used to alter rotation behavior of a TetrominoBase. Specifically, describes how to
    shift the bounding rectangle prior to rotating the TetrominoBase.

####Public functions
  - `void rotateCW()`/`void rotateCCW()`: Rotates the TetrominoBase one quarter rotation in the respective direction,
    without performing checks. Within the context of a PlayingField, should be surrounded with a conditional.
  - `int getOffsetX()`/`int getOffsetY()`: Getters for `int offsetX` and `int offsetY`.

####Protected functions
  - `void initTetromino(TetrominoShape)`: Pure virtual function that MUST be implemented by descendants of
    TetrominoBase to initialize the tetromino with the specified shape.

####All objects that directly inherit from TetrominoBase MUST
  - Implement `void initTetromino(TetrominoShape)`

    

##Tetromino<BlockType>

Inherits from TetrominoBase.

Tetromino<BlockType> is intended to represent a specialized Shape that contains four Blocks of the specified
  BlockType. Tetromino<BlockType> IS NOT intended to be inherited from.
  
Tetromino<BlockType> DOES use `int width`, `int height`, and `unsigned int foreground`. Tetromino<BlockType> defines
  and interprets `int width` and `int height` as the size of the bounding rectangle of the tetromino in Blocks, with
  some tetromino shapes having modified bounding rectangles to accommodate special rotations.

####Constructors
  - `Tetromino()`: Calls `TetrominoBase()`, and then calls `void initTetromino(TetrominoShape)` with TetrominoShape
    `S`.
  - `Tetromino(int x, int y, int blockSize, int padding, TetrominoShape shape, unsigned int background)`: Calls
    `TetrominoBase(x, y, blockSize, padding, background)`, and then calls `void initTetromino(TetrominoShape)` with
    the passed `TetrominoShape shape`.

####Functions implemented from TetrominoBase
  - `void initTetromino(TetrominoShape)`

    

##Block

Inherits from Drawable.

Block is intended to represent a single block, and define behaviors specific to that block. Block IS intended to be
  inherited from.

####Constructors
  - `Block()`: Calls `Drawable(0, 0, 10, 10)` and initializes `int padding` to 0.
  - `Block(int x, int y, int size, int padding, unsigned int foreground, unsigned int background)`: Calls
    `Drawable(x, y, size, size, foreground, background)` and initializes `int padding` to the passed value.

####Protected member data
  - `int padding`: The padding the Block should have in addition to it's visible representation. Specifically, defines
    the number of pixels above and to the right the Block technically occupies, but not visibly.

####Public functions
  - `int getSize()`/`int getPadding()`/`int getTotalSize()`: Getters for `int width`, `int padding`, and the sum
    of both.
  - `void doOnClear(vector<vector<Bock *> >&, int, int)`: Defines what special effect should happen to the given
    block field at the given index when the Block is cleared.
  - `void Block *makeNewClone()`: Allows for proper copying of a Block or one of its descendants into a polymorphic
    Block pointer without knowing whether the object being copied is a Block or one of its descendants. This MUST
    be properly overridden by all descendants of Block.

####Functions implemented from Drawable
  - `void draw()`
  - `void erase()`

####All objects that directly or indirectly inherit from Block MAY
  - Override `void doOnClear(vector<vector<Bock *> >&, int, int)`

####All objects that directly or indirectly inherit from Block MUST
  - Override `Block *makeNewClone();`

    

##GhostBlock

Inherits from Block.

GhostBlock is intended to represent a single block outline, to be used to show where a Block may end up. GhostBlock
  IS NOT intended to be inherited from.

####Constructors
  - `GhostBlock()`: Calls `Block()`.
  - `GhostBlock(int x, int y, int size, int padding, unsigned int foreground, unsigned int background)`: Calls
    `Block (x, y, size, padding, foreground, background)`.

####Functions overridden from Block
  - `void draw()`
  - `void erase()`
  - `GhostBlock *makeNewClone()`
  
  
  
  
  
  
  
  
  
  
  
  
  
  