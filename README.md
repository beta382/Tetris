#Tetris

Group project for CSI 1440 - Freshman Spring Semester

For complete documentation, check out the source code.

## Outline

***Bold Italics*** indicates an abstract object

- [Public API overview](https://github.com/beta382/Tetris/edit/Austin/README.md#public-api-overview)
  - [Objects](https://github.com/beta382/Tetris/edit/Austin/README.md#objects)
    - [***Drawable***](https://github.com/beta382/Tetris/edit/Austin/README.md#drawable)
      - [***Screen***](https://github.com/beta382/Tetris/edit/Austin/README.md#screen)
        - [Game](https://github.com/beta382/Tetris/edit/Austin/README.md#game)
      - [PlayingField](https://github.com/beta382/Tetris/edit/Austin/README.md#playingfield)
      - [Shape](https://github.com/beta382/Tetris/edit/Austin/README.md#shape)
        - [***TetrominoBase***](https://github.com/beta382/Tetris/edit/Austin/README.md#tetrominobase)
          - [Tetromino\<BlockType\>](https://github.com/beta382/Tetris/edit/Austin/README.md#tetrominoblocktype)
      - [Block](https://github.com/beta382/Tetris/edit/Austin/README.md#block)
        - [GhostBlock](https://github.com/beta382/Tetris/edit/Austin/README.md#ghostblock)
        - [ExplodingBlock](https://github.com/beta382/Tetris/edit/Austin/README.md#explodingblock)
        - [GravityBlock](https://github.com/beta382/Tetris/edit/Austin/README.md#gravityblock)
    - Tetris (Provided by instructor, no docs)
    - GLUT_Plotter (Provided by instructor, no docs)
  - [Enumerations](https://github.com/beta382/Tetris/edit/Austin/README.md#enumerations)
    - [TetrominoShape](https://github.com/beta382/Tetris/edit/Austin/README.md#tetrominoshape)
  - [Namespaces](https://github.com/beta382/Tetris/edit/Austin/README.md#namespaces)
    - [Color](https://github.com/beta382/Tetris/edit/Austin/README.md#color)
    - [Key](https://github.com/beta382/Tetris/edit/Austin/README.md#key)
    - [util](https://github.com/beta382/Tetris/edit/Austin/README.md#util)
    - [leakcheck](https://github.com/beta382/Tetris/edit/Austin/README.md#leakcheck)
- [How to use leakcheck](https://github.com/beta382/Tetris/edit/Austin/README.md#how-to-use-leakcheck)

## Public API overview: 

### Objects

#### ***Drawable***

```c++ 
void setWidth(int);
int getWidth();
void setHeight(int);
int getHeight();
virtual void setLocation(int, int);
int getLocationX();
int getLocationY();
virtual void setForeground(unsigned int);
unsigned int getForeground();
virtual void setBackground(unsigned int);
unsigned int getBackground();
void blink(int, clock_t);

static void setG(GLUT_Plotter*);

/* --- Pure virtual --- */
virtual void draw();
virtual void erase();
```
    
#### ***Screen***

```c++
/* --- Pure virtual --- */
virtual Screen* respondToKey(int);
vitrual Screen* respondToClick(Click);
virtual void doBackground();
```

#### Game

```c++
Game(unsigned int color = Color::BLACK);

/* --- Implemented from Screen --- */
Screen* respondToKey(int);
Screen* respondToClick(Click);
void doBackground();

/* --- Implemented from Drawable --- */
void draw();
void erase();

```

#### PlayingField

```c++
PlayingField();
PlayingField(int x, int y, int width, int height, int blockSize, int padding,
                unsigned int foreground = Color::WHITE, unsigned int background = Color::BLACK);
PlayingField(const PlayingField&);
PlayingField& operator =(const PlayingField&);

template <typename BlockType>
Tetromino<BlockType>* spawnNewTetromino(TetrominoShape);

void mergeAndDelete(Shape*);
bool canShiftUp(const Shape*);
bool canShiftDown(const Shape*);
bool canShiftLeft(const Shape*);
bool canShiftRight(const Shape*);
bool canRotateCW(const TetrominoBase*);
bool canRotateCCW(const TetrominoBase*);

/* --- Overriding from Drawable --- */
void setLocation(int, int);

/* --- Implemented from Drawable --- */
void draw();
void erase();
```

#### Shape

```c++
Shape();
Shape(int x, int y, int blockSize, int padding, unsigned int background = Color::BLACK);
Shape(const Shape&);
Shape& operator =(const Shape&);

Block* getBlock(int);
Shape& addBlock(Block*);
int numBlocks();
int getBlockSize();
int getPadding();
int getTotalBlockSize();
void shiftUp();
void shiftDown();
void shiftLeft();
void shiftRight();
Block*& operator [](int);

/* --- Overriding from Drawable --- */
void setLocation(int, int);
void setForeground (unsigned int);
void setBackground (unsigned int);

/* --- Implemented from Drawable --- */
void draw();
void erase();

```

#### ***TetrominoBase***

```c++
void rotateCW();
void rotateCCW();
int getOffsetX();
int getOffsetY();
```

#### Tetromino\<BlockType\>

```c++
Tetromino();
Tetromino(int x, int y, int blockSize, int padding, TetrominoShape shape,
                unsigned int background = Color::BLACK);
Tetromino(const Tetromino<BlockType>&);
Tetromino<BlockType>& operator =(const Tetromino<BlockType>&);
```


#### Block

```c++
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
virtual Block* makeNewClone();

/* --- Implemented from Drawable --- */
void draw();
void erase();
```

#### GhostBlock

```c++
GhostBlock();
GhostBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);
GhostBlock(const GhostBlock&);
GhostBlock& operator =(const GhostBlock&);

/* --- Overriding from Block --- */
int doEffect(vector<vector<Block*> >&, int x, int y);
GhostBlock* makeNewClone();
void draw();
```

#### ExplodingBlock

```c++
ExplodingBlock();
ExplodingBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);
ExplodingBlock(const ExplodingBlock&);
ExplodingBlock& operator =(const ExplodingBlock&);

/* --- Overriding from Block --- */
int doEffect(vector<vector<Block*> >&, int x, int y);
ExplodingBlock* makeNewClone();
void draw();
```

#### GravityBlock

```c++
GravityBlock();
GravityBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);
GravityBlock(const GravityBlock&);
GravityBlock& operator =(const GravityBlock&);

/* --- Overriding from Block --- */
int doEffect(vector<vector<Block*> >&, int x, int y);
GravityBlock* makeNewClone();
void draw();
```

#### Namespace `util`

```c++
void wait(clock_t);
```

##How to use leakcheck

It's super simple. In the header(s) of the object(s) you want to monitor, include `"util.cpp"` add the following code under `public`:

```c++
void* operator new(size_t bytes) {
    return leakcheck::alloc(bytes, "NAME_OF_YOUR_OBJECT");
}

void operator delete(void* mem) {
    leakcheck::dealloc(mem);
}
```

`NAME_OF_YOUR_OBJECT` is a string representation of what you call your object, although you can make it whatever you want.
The allocations will get logged with the name that you provide.

To output the tracked objects currently on the heap to the console, insert:

```c++
leakcheck::print(cout);
```

somewhere in your code.

To show a summary when your program dies, add the following code before an exit point (either the end of main or a call to `exit(int)`):

```c++
cout << "n_new:    " << leakcheck::n_new << endl;
cout << "n_delete: " << leakcheck::n_delete << endl;
cout << endl;
cout << "leaking " << leakcheck::bytes() << " bytes from " << leakcheck::allocated.size() << " objects" << endl;
cout << endl;
leakcheck::print(cout);
```

For best results, make sure that all dynamically allocated data is deleted prior to sumarizing and exiting. This
includes forcing objects you know are dynamically allocated to commit suicide (`delete this;`) if control will reach a
call to `exit(int)` from within the object.
