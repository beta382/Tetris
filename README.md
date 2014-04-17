#Tetris

Group project for CSI 1440 - Freshman Spring Semester

For complete documentation, check out the source code.

## Public method overview: 

### `Drawable` (abstract)

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
    
### `Screen` (abstract, extends `Drawable`)

```c++
/* --- Pure virtual --- */
virtual Screen* respondToKey(int);
vitrual Screen* respondToClick(Click);
virtual void doBackground();
```

### `Game` (extends `Screen`)

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

### `PlayingField` (extends `Drawable`)

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

### `Shape` (extends `Drawable`)

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

### `TetrominoBase` (abstract, extends `Shape`)

```c++
void rotateCW();
void rotateCCW();
int getOffsetX();
int getOffsetY();
```

### `Tetromino<BlockType>` (template, extends `TetrominoBase`)

```c++
Tetromino();
Tetromino(int x, int y, int blockSize, int padding, TetrominoShape shape,
                unsigned int background = Color::BLACK);
Tetromino(const Tetromino<BlockType>&);
Tetromino<BlockType>& operator =(const Tetromino<BlockType>&);
```


### `Block` (extends `Drawable`)

```c++
Block();
Block(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
        		unsigned int background = Color::BLACK);
Block(const Block&);
Block& operator =(const Block&);

int getSize();
int getPadding();
int getTotalSize();
unsigned int getUniqueID();
void setUniqueID(unsigned int);
virtual void doEffect(vector<vector<Block*> >&, int x, int y);
virtual Block* makeNewClone();

/* --- Implemented from Drawable --- */
void draw();
void erase();
```

### `GhostBlock` (extends `Block`)

```c++
GhostBlock();
GhostBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);
GhostBlock(const GhostBlock&);
GhostBlock& operator =(const GhostBlock&);

/* --- Overriding from Block --- */
void doEffect(vector<vector<Block*> >&, int x, int y);
GhostBlock* makeNewClone();
void draw();
void erase();
```

### Namespace `util`

```c++
void wait(clock_t);
```

