/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr 26, 2014
 */

#include "PlayingField.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a PlayingField object using default values.
 */
PlayingField::PlayingField():
Drawable(0, 0, 10, 20),
        blockSize(10), padding(0), borderWidth(0), borderColor(Color::GRAY),
        bgRect(x+borderWidth, y+borderWidth, getWidth()-borderWidth*2, getHeight()-borderWidth*2, 
                foreground, background),
        bgRect2(x, y, getWidth(), getHeight(), borderColor, background),
        blockField(width, vector<Block*>(height, static_cast<Block*>(NULL)))
{
}

/*
 * Instantiates a PlayingField object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this PlayingField object's x with
 *   int y: The value to initialize this PlayingField object's y with
 *   int width: The value to initialize this PlayingField object's width with
 *   int height: The value to initialize this PlayingField object's height with
 *   int blockSize: The value to initialize this PlayingField object's blockSize with
 *   int padding: The value to initialize this PlayingField object's padding with
 *   unsigned int foreground: The value to initialize this PlayingField object's foreground with,
 *     defaults to Color::WHITE
 *   unsigned int background: The value to initialize this PlayingField object's background with,
 *     defaults to Color::BLACK         
 *   int borderWidth: The value to initialize this PlayingField object's borderWidth with, defaults
 *     to 0
 *   unsigned int borderColor: The value to initialize this PlayingField object's borderColor with,
 *     defaults to Color::GREY
 */
PlayingField::PlayingField(int x, int y, int width, int height, int blockSize, int padding,
  unsigned int foreground, unsigned int background, int borderWidth, unsigned int borderColor):
Drawable(x, y, width, height, foreground, background),
        blockSize(blockSize), padding(padding), borderWidth(borderWidth), borderColor(borderColor),
        bgRect(x+borderWidth, y+borderWidth, getWidth()-borderWidth*2, getHeight()-borderWidth*2, 
                foreground, background),
        bgRect2(x, y, getWidth(), getHeight(), borderColor, background),
        blockField(width, vector<Block*>(height, static_cast<Block*>(NULL)))
{
}

/*
 * Instantiates a PlayingField object that is a copy of the passed PlayingField object, except for
 *   bool isVisible, which is initialized with false.
 * 
 * Parameters:
 *   const PlayingField& other: A reference to the PlayingField object to copy from
 */
PlayingField::PlayingField(const PlayingField& other): 
Drawable(other),
        blockSize(other.blockSize), padding(other.padding), borderWidth(other.borderWidth), 
        borderColor(other.borderColor),bgRect(other.bgRect), bgRect2(other.bgRect2),
        blockField(width, vector<Block*>(height, static_cast<Block*>(NULL)))
{
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (other.blockField.at(i).at(j)) {
                blockField[i][j] = other.blockField.at(i).at(j)->makeNewClone();
            }
        }
    }
}

/*
 * Destructs this PlayingField object.
 */
PlayingField::~PlayingField() {
    erase();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            delete blockField[i][j];
        }
    }
}


/* ---------- Public ---------- */

/*
 * Assigns this PlayingField object the values of the passed PlayingField object, except for bool
 *   isVisible, which is assigned false.
 * 
 * Parameters:
 *   const PlayingField& rhs: A reference to the PlayingField object to assign from
 * 
 * Returns: A reference to this PlayingField object
 */
PlayingField& PlayingField::operator =(const PlayingField& rhs) {
    if  (this != &rhs) {
        erase();
        
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                delete blockField[i][j];
            }
            
            blockField[i].clear();
        }
        
        blockField.clear();
        
        Drawable::operator =(rhs);
        blockSize = rhs.blockSize;
        padding = rhs.padding;
        borderWidth = rhs.borderWidth;
        borderColor = rhs.borderColor;
        bgRect = rhs.bgRect;
        bgRect2 = rhs.bgRect2;
        
        blockField.assign(width, vector<Block*>(height, static_cast<Block*>(NULL)));
        
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (rhs.blockField.at(i).at(j)) {
                    blockField[i][j] = rhs.blockField.at(i).at(j)->makeNewClone();
                }
            }
        }
        
        draw();
    }
    
    return *this;
}



/*
 * Dynamically allocates a TetrominoBase from the passed TetrominoBase pointer centered at the top
 *   of the block field.
 * 
 * Parameters:
 *   TetrominoBase* initFrom: A pointer to the TetrominoBase to use a base for spawning the new
 *     tetromino
 * 
 * Returns: A pointer to the dynamically allocated TetrominoBase*, or NULL if the tetromino cannot
 *   be spawned
 */
TetrominoBase* PlayingField::spawnNewTetromino (TetrominoBase* initFrom) const {
    
    TetrominoBase* tetromino = initFrom;
    
    tetromino->setLocation(
            getLocationX()+getPadding()+borderWidth+getTotalBlockSize()*(width/2),
            getLocationY()+getPadding()+borderWidth+getTotalBlockSize()*height
    );
    
    tetromino->setBackground(getForeground());
    
    // Move us to the top of the screen and center since we spawned at a general location above it
    // and to the right
    tetromino->setLocation(
        tetromino->getLocationX()-(((tetromino->getWidth()+tetromino->getPadding())/
                tetromino->getTotalBlockSize()+1)/2)*tetromino->getTotalBlockSize(),
        tetromino->getLocationY()-tetromino->getHeight()-tetromino->getPadding()
    );
    
    // Check to see if this is a valid location
    bool canSpawn = true;
    for (int i = 0; i < tetromino->numBlocks() && canSpawn; i++) {
        if(!couldAdd(tetromino->getBlock(i))) {
            canSpawn = false;
            tetromino->setLocation(getLocationX()+borderWidth+getPadding(),
                    tetromino->getLocationY()); // Move us all the way to the left
        }
    }
    
    // Try new locations until we find one that works, or can't find one, in which case we return
    // NULL
    while(!canSpawn) {
        canSpawn = true;
        for (int i = 0; tetromino && i < tetromino->numBlocks() && canSpawn; i++) {
            if(xIndexFromLocation(tetromino->getBlock(i)) > width) {
                delete tetromino;
                tetromino = NULL;
            } else if(!couldAdd(tetromino->getBlock(i))) {
                canSpawn = false;
                tetromino->setLocation(tetromino->getLocationX()+getTotalBlockSize(), 
                        tetromino->getLocationY());
            }
        }
    }
    
    return tetromino;
}

/*
 * Merges a clone of the Shape pointed to by the passed pointer into the blockField, de-allocates
 *   the Shape, and then checks to see if lines need to be cleared, doing so if need be.
 *   
 * Parameters:
 *   Shape* shape: A pointer to the Shape object to merge and delete
 *   
 * Returns: The number of points the merge accumulated
 */
int PlayingField::mergeAndDelete (Shape* shape) {
    int points = 0;
    
    mergeCopy(shape);
    
    delete shape;
    
    draw();
    
    vector<int> clearableLines = getClearableLines();

    if (clearableLines.size() > 0) {
        points += doLineClear(clearableLines);
    }
    
    return points;
}


/*
 * Getter for blockSize.
 * 
 * Returns: The value of this PlayingField object's blockSize
 */
int PlayingField::getBlockSize() const {
    return blockSize;
}

/*
 * Getter for padding.
 * 
 * Returns: The value of this PlayingField object's padding
 */
int PlayingField::getPadding() const {
    return padding;
}

/*
 * Getter for the sum of blockSize and padding.
 * 
 * Returns: The value of this PlayingField object's blockSize+padding
 */
int PlayingField::getTotalBlockSize() const {
    return getBlockSize()+getPadding();
}


/*
 * Determines whether or not the Shape object pointed to by the passed pointer can be shifted up
 *   within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Shape object to test
 *   
 * Returns: True if the Shape can shift up within the blockField, false otherwise
 */
bool PlayingField::canShiftUp(const Shape* shape) const {
    bool can = true;
    
    Shape* tmp = new Shape(*shape);
    
    tmp->shiftUp();
    
    for (int i = 0; i < tmp->numBlocks() && can; i++) {
         
        if (!couldAdd((*tmp)[i])) {
            can = false;
        }
    }
    
    delete tmp;
    
    return can;
}

/*
 * Determines whether or not the Shape object pointed to by the passed pointer can be shifted down
 *   within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Shape object to test
 *   
 * Returns: True if the Shape can shift down within the blockField, false otherwise
 */
bool PlayingField::canShiftDown(const Shape* shape) const {
    bool can = true;
    
    Shape* tmp = new Shape(*shape);
    
    tmp->shiftDown();
    
    for (int i = 0; i < tmp->numBlocks() && can; i++) {
         
        if (!couldAdd((*tmp)[i])) {
            can = false;
        }
    }
    
    delete tmp;
    
    return can;
}

/*
 * Determines whether or not the Shape object pointed to by the passed pointer can be shifted left
 *   within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Shape object to test
 *   
 * Returns: True if the Shape can shift left within the blockField, false otherwise
 */
bool PlayingField::canShiftLeft(const Shape* shape) const {
    bool can = true;
    
    Shape* tmp = new Shape(*shape);
    
    tmp->shiftLeft();
    
    for (int i = 0; i < tmp->numBlocks() && can; i++) {
         
        if (!couldAdd((*tmp)[i])) {
            can = false;
        }
    }
    
    delete tmp;
    
    return can;
}

/*
 * Determines whether or not the Shape object pointed to by the passed pointer can be shifted right
 *   within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Shape object to test
 *   
 * Returns: True if the Shape can shift right within the blockField, false otherwise
 */
bool PlayingField::canShiftRight(const Shape* shape) const {
    bool can = true;
    
    Shape* tmp = new Shape(*shape);
    
    tmp->shiftRight();
    
    for (int i = 0; i < tmp->numBlocks() && can; i++) {
         
        if (!couldAdd((*tmp)[i])) {
            can = false;
        }
    }
    
    delete tmp;
    
    return can;
}

/*
 * Determines whether or not the TetrominoBase object pointed to by the passed pointer can be
 *   rotated clockwise within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the TetrominoBase object to test
 *   
 * Returns: True if the TetrominoBase object can rotate clockwise within the blockField, false
 *   otherwise
 */
bool PlayingField::canRotateCW(const TetrominoBase* t) const {
    bool can = true;
    
    TetrominoBase* tmp = t->makeNewClone();
    
    tmp->rotateCW();
    
    for (int i = 0; i < tmp->numBlocks() && can; i++) {
         
        if (!couldAdd((*tmp)[i])) {
            can = false;
        }
    }
    
    delete tmp;
    
    return can;
}

/*
 * Determines whether or not the TetrominoBase object pointed to by the passed pointer can be
 *   rotated counter-clockwise within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the TetrominoBase object to test
 *   
 * Returns: True if the TetrominoBase object can rotate counter-clockwise within the blockField,
 *   false otherwise
 */
bool PlayingField::canRotateCCW(const TetrominoBase* t) const {
    bool can = true;
    
    TetrominoBase* tmp = t->makeNewClone();
    
    tmp->rotateCCW();
    
    for (int i = 0; i < tmp->numBlocks() && can; i++) {
         
        if (!couldAdd((*tmp)[i])) {
            can = false;
        }
    }
    
    delete tmp;
    
    return can;
}


/* ---------- Private ---------- */

/*
 * Determines whether or not the Block object pointed to by the passed pointer can be added to the
 *   blockField without conflict.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Block object to test
 *   
 * Returns: True if the Block object can be added to the blockField without conflict, false
 *   otherwise
 */
bool PlayingField::couldAdd(const Block* block) const {
    bool can = true;
    
    int xIndex = xIndexFromLocation(block);
    int yIndex = yIndexFromLocation(block);
    
    // Check that it isn't out-of-bounds or intersecting an existing Block
    if (xIndex < 0 || xIndex >= width || yIndex < 0 || yIndex >= height ||
            blockField.at(xIndex).at(yIndex))
    {
        can = false;
    }
    
    return can;
}

/*
 * Checks if there are lines to be cleared, and clears them if there are.
 * 
 * Is mutually recursive with doFall(vector<Shape*>&).
 * 
 * Parameters:
 *   vector<int> clearableLines: The lines to clear
 *   
 * Returns: The number of points the line clear accumulated
 */
int PlayingField::doLineClear(vector<int> clearableLines) {
    // Static because this recurses with doFall, maintains the remaining shapes across calls, is
    // always cleared/reset before exiting the top-level of a single call.
    static vector<Shape*> fallingShapes;
    
    int points = clearableLines.size()*50;
    
    vector<Shape*> newFallingShapes;

    // Extract all the clearable lines into a single Shape
    Shape clearedBlocks;
    for (unsigned int i = 0; i < clearableLines.size(); i++) {
        for (int j = 0; j < width; j++) {
            clearedBlocks.addBlock(blockField[j][clearableLines[i]]->makeNewClone());
            delete blockField[j][clearableLines[i]];
            blockField[j][clearableLines[i]] = NULL;
        }
    }

    clearedBlocks.blink(3, 150);

    normalizeBlocks(clearedBlocks);

    points += doClearedBlockEffects(clearedBlocks, fallingShapes);

    // See if we have any new shapes to form, and add them to fallingShapes
    newFallingShapes = formNewContiguousShapes(blockField);

    for (unsigned int i = 0; i < newFallingShapes.size(); i++) {
        fallingShapes.push_back(newFallingShapes[i]);
    }

    // Maintains proper order since we might add new shapes out-of-order
    sort(fallingShapes.begin(), fallingShapes.end(), compareShapePointerByLocation);

    points += doFall(fallingShapes);
    
    // Clear fallingShapes when this finally exits, should be totally NULL at this point
    fallingShapes.clear();
    
    // SFX
    PlaySound("sounds/line_clear.wav", NULL, SND_ASYNC);
    
    return points;
}

/*
 * Checks the blockField for lines that are able to be cleared.
 * 
 * Returns: A vector<int> of the indices of the clearable lines
 */
vector<int> PlayingField::getClearableLines() {
    vector<int> clearableLines;
    
    for (int i = 0; i < height; i++) {
        bool isClearable = true;
        for (int j = 0; j < width && isClearable; j++) {
            if (!blockField[j][i]) {
                isClearable = false;
            }
        }
        
        if (isClearable) {
            clearableLines.push_back(i);
        }
    }
    
    return clearableLines;
}

/*
 * Runs through the passed Shape and finds all Blocks either in the blockField or the passed Shape
 *   that have the same uniqueID, replacing them with identical base Blocks.
 *   
 * Parameters:
 *   Shape& shape: A reference to the Shape to use as a base when searching for Blocks with the
 *     same uniqueID
 */
void PlayingField::normalizeBlocks(Shape& shape) {
    for (int i = 0; i < shape.numBlocks(); i++) {
        
        // If the block we are on has a "no-ID", we don't need to check
        if (shape[i] && shape[i]->getUniqueID() != 0) {
            
            // blockField
            for (int j = 0; j < width; j++) {
                for (int k = 0; k < height; k++) {
                    if (blockField[j][k] &&
                            blockField[j][k]->getUniqueID() == shape[i]->getUniqueID())
                    {
                        Block* tmp = blockField[j][k];
                        
                        // Not making a clone, this will give us a base Block
                        blockField[j][k] = new Block(*tmp);
                        delete tmp;
                        blockField[j][k]->draw();
                    }
                }
            }
            
            // Passed Shape
            for (int j = i+1; j < shape.numBlocks(); j++) {
                if (shape[i]->getUniqueID() == shape[j]->getUniqueID()) {
                    Block* tmp = shape[j];
                    
                    // Not making a clone, this will give us a base Block
                    shape[j] = new Block(*tmp); 
                    delete tmp; // Don't redraw, these blocks aren't supposed to be visible
                }
            }
        }
    }
}

/*
 * For each Block in the passed Shape, performs its special effect on the blockField and the passed
 *   vector<Shape*> of fallingShapes.
 * 
 * Parameters:
 *   Shape& clearedBlocks: A reference to the Shape object who's Block's special effects should be
 *     performed.
 *   vector<Shape*>& fallingShapes: A reference to the vector<Shape*> containing pointers to the 
 *     Shape objects currently falling; since these are separate from the blockField, they must
 *     be passed separately
 *     
 * Returns: The number of points the special effects accumulated
 */
int PlayingField::doClearedBlockEffects(Shape& clearedBlocks, vector<Shape*>& fallingShapes) {
    vector<vector<Block*> > remainingBlockField(width,
            vector<Block*>(height, static_cast<Block*>(NULL)));
    
    int points = 0;
    
    // Before we perform any special effects, temporarily directly merge any fallingShapes
    for (unsigned int i = 0; i < fallingShapes.size(); i++) {
        for (int j = 0; fallingShapes[i] && j < fallingShapes[i]->numBlocks(); j++) {
            
            Block* curBlock = (*fallingShapes[i])[j];
            int indexX = xIndexFromLocation(curBlock);
            int indexY = yIndexFromLocation(curBlock);
            
            // Delete anything that may already be here
            delete blockField[indexX][indexY];
            
            blockField[indexX][indexY] = curBlock;
            
            curBlock->draw();
        }
    }
    
    // For each cleared block, perform the block's special effect, and then delete the block
    for (int i = 0; i < clearedBlocks.numBlocks(); i++) {
        points += clearedBlocks[i]->doEffect(blockField, 
                xIndexFromLocation(clearedBlocks[i]), yIndexFromLocation(clearedBlocks[i]));
    }
    
    // Extract the merged fallingShapes and make them into a separate blockField
    for (unsigned int i = 0; i < fallingShapes.size(); i++) {
        for (int j = 0; fallingShapes[i] && j < fallingShapes[i]->numBlocks(); j++) {
            Block* curBlock = (*fallingShapes[i])[j];
            int indexX = xIndexFromLocation(curBlock);
            int indexY = yIndexFromLocation(curBlock);
            
            blockField[indexX][indexY] = NULL;
            remainingBlockField[indexX][indexY] = curBlock;
            
            // NULL the leftover Block pointer copy in fallingShapes
            (*fallingShapes[i])[j] = NULL;
        }
        
        // Deletes dynamically allocated Shape, doesn't delete Blocks because they were NULLed
        delete fallingShapes[i];
    }
    
    // Takes a blockField made from the potentially modified original fallingShapes and forms new
    // shapes out of them. Effectively refreshes fallingShapes post-special effects
    fallingShapes = formNewContiguousShapes(remainingBlockField);
    
    return points;
}

/*
 * Performs a falling animation for each of the Shapes pointed to by the pointers in the passed
 *   vector<Shape*> and merges Shapes that have finished falling.
 * 
 * Is mutually recursive with doLineClear(vector<int> clearableLines)
 * 
 * Parameters:
 *   vector<Shape*>& fallingShapes: A vector of pointers to Shape objects that need to have a
 *     falling animation performed on them, may contain NULL pointers
 *     
 * Returns: The number of points the fall accumulated
 */
int PlayingField::doFall(vector<Shape*>& fallingShapes) {
    int points = 0;
    
    bool didFall = true;
    // While we are still shifting down...
    while(didFall) {
        didFall = false;

        vector<int> mergeIndex;
        vector<int> shiftIndex;
        for (unsigned int i = 0; i < fallingShapes.size(); i++) {
            // Shift down once if we can
            if (fallingShapes[i]) {
                if (canShiftDown(fallingShapes[i])) {
                    shiftIndex.push_back(i);
                } else {
                    mergeIndex.push_back(i);
                }
            }
        }

        // Merge all the mergeable shapes
        if (mergeIndex.size() > 0) {
            for (unsigned int i = 0; i < mergeIndex.size(); i++) {
                mergeCopy(fallingShapes[mergeIndex[i]]);

                delete fallingShapes[mergeIndex[i]];

                fallingShapes[mergeIndex[i]] = NULL;
            }

            draw();

            for (unsigned int i = 0; i < fallingShapes.size(); i++) {
                if (fallingShapes[i]) {
                    fallingShapes[i]->draw();
                }
            }

            g->Draw(); // Force redraw

            // Since we merged, see if we need to clear new lines
            vector<int> clearableLines = getClearableLines();

            if (clearableLines.size() > 0) {
                points += doLineClear(clearableLines)*2; // Double points for each cascading clear
            }

            didFall = false;
        }

        // Shift all the shiftable shapes
        if (shiftIndex.size() > 0) {
            for (unsigned int i = 0; i < shiftIndex.size(); i++) {
                // These can be NULL since from previous calls, since all calls pass the same data
                if (fallingShapes.size() > 0 && fallingShapes[shiftIndex[i]]) {
                    fallingShapes[shiftIndex[i]]->erase();
                    fallingShapes[shiftIndex[i]]->shiftDown();
                    fallingShapes[shiftIndex[i]]->draw();
                    
                    didFall = true;
                }
            }
        }

        if (didFall) {
            util::wait(100, g);
        }
    }
    
    return points;
}

/*
 * Allocates contiguous Shapes objects from the Blocks in the passed blockField.
 * 
 * Parameters:
 *   vector<vector<Block*> >& blockField: The blockField to from contiguous shapes from
 *   
 * Returns: A vector of pointers to the formed Shape objects
 */
vector<Shape*> PlayingField::formNewContiguousShapes(vector<vector<Block*> >& blockField) {
    vector<Shape*> shapes;
    
    for (unsigned int i = 0; blockField.size() > 0 && i < blockField[0].size(); i++) {
        for (unsigned int j = 0; j < blockField.size(); j++) {
            if (blockField[j][i]) {
                Shape* curShape = new Shape(blockField[j][i]->getLocationX(),
                        blockField[j][i]->getLocationY(), blockField[j][i]->getSize(),
                        blockField[j][i]->getPadding());

                r_makeContiguousShape(curShape, j, i, blockField);
                
                curShape->draw();
                
                shapes.push_back(curShape);
            }
        }
    }
    
    return shapes;
}

/*
 * Recursively makes a Shape from contiguous Blocks in the passed blockField, starting at the
 *   passed coordinates.
 *   
 * Is recursive.
 *   
 * Parameters:
 *   Shape* shape: A pointer to the Shape object to add contiguous blocks to
 *   int x: The x-coordinate of the block to attempt to add
 *   int y: The y-coordinate of the block to attempt to add
 *   vector<vector<Block*> >& blockField: The blockField to pull Blocks from when making the Shape
 */
void PlayingField::r_makeContiguousShape(Shape* shape, int x, int y, 
        vector<vector<Block*> >& blockField)
{
    if (x < 0 || x >= static_cast<int>(blockField.size()) || y < 0 ||
            y >= static_cast<int>(blockField[x].size()) || !blockField[x][y]) {
        return;
    }
    
    shape->addBlock(blockField[x][y]);
    
    blockField[x][y] = NULL;
    
    r_makeContiguousShape(shape, x+1, y, blockField);
    r_makeContiguousShape(shape, x, y+1, blockField);
    r_makeContiguousShape(shape, x-1, y, blockField);
    r_makeContiguousShape(shape, x, y-1, blockField);
}

/*
 * Merges a clone of the Shape pointed to by the passed pointer into the blockField.
 *   
 * Parameters:
 *   Shape* shape: A pointer to the Shape object to merge
 */
void PlayingField::mergeCopy(const Shape* shape) {
    for (int i = 0; i < shape->numBlocks(); i++) {
        Block* curBlock = shape->getBlock(i)->makeNewClone();
        int indexX = xIndexFromLocation(curBlock);
        int indexY = yIndexFromLocation(curBlock);
        
        // Delete anything that may already be here
        delete blockField[indexX][indexY];
        
        blockField[indexX][indexY] = curBlock;
        
        curBlock->draw();
    }
}

/*
 * Determines the x-index the Block pointed to by the passed pointer would have if it were a part
 *   of the blockField, derived from it's x-coordinate.
 *   
 * Parameters:
 *   const Block* block: A pointer to the Block to determine the x-index of
 *   
 * Return: The x-index of the Block pointed to by the passed pointer
 */
int PlayingField::xIndexFromLocation(const Block* block) const {
    return (block->getLocationX()-getLocationX()-getPadding()-borderWidth)/block->getTotalSize();
}

/*
 * Determines the y-index the Block pointed to by the passed pointer would have if it were a part
 *   of the blockField, derived from it's y-coordinate.
 *   
 * Parameters:
 *   const Block* block: A pointer to the Block to determine the y-index of
 *   
 * Return: The y-index of the Block pointed to by the passed pointer
 */
int PlayingField::yIndexFromLocation(const Block* block) const {
    return (block->getLocationY()-getLocationY()-getPadding()-borderWidth)/block->getTotalSize();
}


/* ---------- Overriding from Drawable ---------- */


/*
 * Getter for width.
 * 
 * Returns: The value of this PlayingField object's width
 */
int PlayingField::getWidth() const {
    return width*(blockSize+padding) + padding + borderWidth*2;
}

/*
 * Getter for height.
 * 
 * Returns: The value of this PlayingField object's height
 */
int PlayingField::getHeight() const {
    return height*(blockSize+padding) + padding + borderWidth*2;
}

/*
 * Assigns x and y the values of the passed parameters, and properly offsets all Drawable member
 *   data to reflect the shift
 * 
 * Parameters:
 *   int x: The value to assign to this PlayingField object's x
 *   int y: The value to assign to this PlayingField object's y
 */
void PlayingField::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    
    erase();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (blockField[i][j]) {
                blockField[i][j]->setLocation(blockField[i][j]->getLocationX()+dX,
                        blockField[i][j]->getLocationY()+dY);
            }
        }
    }
    
    bgRect.setLocation(bgRect.getLocationX()+dX, bgRect.getLocationY()+dY);
    bgRect2.setLocation(bgRect2.getLocationX()+dX, bgRect2.getLocationY()+dY);
    
    draw();
    
    this->x = x;
    this->y = y;
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void PlayingField::draw() {
    bgRect2.draw();
    bgRect.draw();

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (blockField[i][j]) {
                blockField[i][j]->draw();
            }
        }
    }

    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void PlayingField::erase() {
    if (isVisible) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (blockField[i][j]) {
                    blockField[i][j]->erase();
                }
            }
        }
        
        bgRect.erase();
        bgRect2.erase();
        
        isVisible = false;
    }
}
