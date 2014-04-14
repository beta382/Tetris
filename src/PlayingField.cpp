/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr 12, 2014
 */

#include "PlayingField.h"

/*
 * Instantiates a PlayingField object using default values
 * 
 * Calls Drawable(0, 0, 10, 20)
 * Initializes blockSize with 10
 * Initializes padding with 0
 * Initializes bgRect with MyRectangle(x, y, (blockSize+padding)*width-padding,
 *   (blockSize+padding)*height-padding, foreground, background)
 * Initializes blocks with vector(width, vector<Block *>(height, static_cast<Block *>(NULL)))
 */
PlayingField::PlayingField():
Drawable(0, 0, 10, 20),
        blockSize(10), padding(0),
        bgRect(x, y, (blockSize+padding)*width-padding, (blockSize+padding)*height-padding, foreground, background),
        blockField(width, vector<Block *>(height, static_cast<Block *>(NULL)))
{
}

/*
 * Instantiates a PlayingField object using the passed values
 * 
 * Calls Drawable(x, y, width, height, foreground, background)
 * Initializes blockSize and padding with the passed values
 * Initializes bgRect with MyRectangle(x, y, (blockSize+padding)*width-padding,
 *   (blockSize+padding)*height-padding, foreground, background)
 * Initializes blocks with vector(width, vector<Block *>(height, static_cast<Block *>(NULL)))
 */
PlayingField::PlayingField(int x, int y, int width, int height, int blockSize, int padding, unsigned int foreground,
        unsigned int background):
Drawable(x, y, width, height, foreground, background),
        blockSize(blockSize), padding(padding), 
        bgRect(x, y, (blockSize+padding)*width-padding, (blockSize+padding)*height-padding, foreground, background),
        blockField(width, vector<Block *>(height, static_cast<Block *>(NULL)))
{
}

/*
 * Instantiates a PlayingField object that is a copy of the passed PlayingField object
 * 
 * Calls Drawable(other)
 * Initializes blockSize, padding, and bgRect with the respective values from the passed
 *   PlayingField object
 * Initializes blocks with vector(width, vector<Block *>(height, static_cast<Block *>(NULL)))
 * Assigns blocks pointers to newly allocated clones of the respective Blocks from the passed
 *   PlayingField object 
 *   
 * Guaranteed that the passed PlayingField object will not be modified
 */
PlayingField::PlayingField(const PlayingField& other): 
Drawable(other),
        blockSize(other.blockSize), padding(other.padding), bgRect(other.bgRect),
        blockField(width, vector<Block *>(height, static_cast<Block *>(NULL)))
{
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (other.blockField.at(i).at(j)) {
                blockField[i][j] = other.blockField.at(i).at(j)->makeNewClone();
            }
        }
    }
}

/*
 * Assigns this PlayingField object the values of the passed PlayingField object
 * 
 * Calls erase()
 * Deletes any dynamically allocated Blocks contained in blocks and clears blocks
 * 
 * Calls Drawable::operator =(rhs)
 * Assigns blockSize, padding, and bgRect the respective values from the passed PlayingField object
 * Assigns blocks a 2D vector of NULL pointers
 * Assigns blocks pointers to newly allocated clones of the respective Blocks from the passed
 *   PlayingField object 
 *   
 * Guaranteed that the passed PlayingField object will not be modified
 * 
 * Returns a reference to this PlayingField object
 */
PlayingField& PlayingField::operator =(const PlayingField& rhs) {
    if  (this != &rhs) {
        erase();
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                delete blockField[i][j];
            }
            
            blockField[i].clear();
        }
        
        blockField.clear();
        
        Drawable::operator =(rhs);
        blockSize = rhs.blockSize;
        padding = rhs.padding;
        bgRect = rhs.bgRect;
        
        blockField.assign(width, vector<Block *>(height, static_cast<Block *>(NULL)));
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
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
 * Properly destructs a PlayingField object
 * 
 * Calls erase()
 * Deletes any dynamically allocated Blocks pointed to in blocks
 */
PlayingField::~PlayingField() {
    erase();
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            delete blockField[i][j];
        }
    }
}

/*
 * Merges a clone of the passed Shape into the playingField, and then de-allocates the Shape
 * 
 * Is mutually recursive with doLineClear()
 * 
 * Calls merge(shape)
 * De-allocates shape
 * Calls draw()
 * Calls doLineClear()
 */
void PlayingField::mergeAndDelete (Shape *shape) {
    merge(shape);
    
    delete shape;
    
    draw();
    
    vector<int> clearableLines = getClearableLines();

    if (clearableLines.size() > 0) {
    	doLineClear(clearableLines);
    }
}

/*
 * Returns true if the passed Shape can shift up within the block field, false otherwise
 * 
 * Guaranteed that the Shape pointed to by shape will not be modified
 * Guaranteed that this PlayingField object will not be modified
 */
bool PlayingField::canShiftUp(const Shape *shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block *tmp = shape->getBlock(i)->makeNewClone();
        
        // Apply transformation to our tmp Block
        tmp->setLocation(tmp->getLocationX(), tmp->getLocationY()+tmp->getTotalSize());
                
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Returns true if the passed Shape can shift down within the block field, false otherwise
 * 
 * Guaranteed that the Shape pointed to by shape will not be modified
 * Guaranteed that this PlayingField object will not be modified
 */
bool PlayingField::canShiftDown(const Shape *shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block *tmp = shape->getBlock(i)->makeNewClone();
        
        // Apply transformation to our tmp Block
        tmp->setLocation(tmp->getLocationX(), tmp->getLocationY()-tmp->getTotalSize());
                
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Returns true if the passed Shape can shift left within the block field, false otherwise
 * 
 * Guaranteed that the Shape pointed to by shape will not be modified
 * Guaranteed that this PlayingField object will not be modified
 */
bool PlayingField::canShiftLeft(const Shape *shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block *tmp = shape->getBlock(i)->makeNewClone();
        
        // Apply transformation to our tmp Block
        tmp->setLocation(tmp->getLocationX()-tmp->getTotalSize(), tmp->getLocationY());
                
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Returns true if the passed Shape can shift left within the block field, false otherwise
 * 
 * Guaranteed that the Shape pointed to by shape will not be modified
 * Guaranteed that this PlayingField object will not be modified
 */
bool PlayingField::canShiftRight(const Shape *shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block *tmp = shape->getBlock(i)->makeNewClone();
        
        // Apply transformation to our tmp Block
        tmp->setLocation(tmp->getLocationX()+tmp->getTotalSize(), tmp->getLocationY());
                
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Returns true if the passed TetrominoBase can rotate clockwise within the block field, false
 *   otherwise
 * 
 * Guaranteed that the TetrominoBase pointed to by t will not be modified
 * Guaranteed that this PlayingField object will not be modified
 */
bool PlayingField::canRotateCW(const TetrominoBase *t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block *tmp = t->getBlock(i)->makeNewClone();
        
        // Apply rotation transformation to our tmp Block
        tmp->setLocation(((tmp->getLocationY()-t->getLocationY())/tmp->getTotalSize()-t->getOffsetY()-t->getOffsetX())*
                  tmp->getTotalSize()+t->getLocationX(),
                (t->getWidth()-((tmp->getLocationX()-t->getLocationX())/tmp->getTotalSize()+t->getOffsetX())-1+
                  t->getOffsetY())*tmp->getTotalSize()+t->getLocationY());
        
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Returns true if the passed TetrominoBase can rotate counter-clockwise within the block field,
 *   false otherwise
 * 
 * Guaranteed that the TetrominoBase pointed to by t will not be modified
 * Guaranteed that this PlayingField object will not be modified
 */
bool PlayingField::canRotateCCW(const TetrominoBase *t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block *tmp = t->getBlock(i)->makeNewClone();
        
        // Apply rotation transformation to our tmp Block
        tmp->setLocation((t->getHeight()-((tmp->getLocationY()-t->getLocationY())/tmp->getTotalSize()-t->getOffsetY())-
                  1-t->getOffsetX())*tmp->getTotalSize()+t->getLocationX(),
                ((tmp->getLocationX()-t->getLocationX())/tmp->getTotalSize()+t->getOffsetX()+t->getOffsetY())*
                  tmp->getTotalSize()+t->getLocationY());
         
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}


/* ---------- Private ---------- */

/*
 * Returns true if the passed Block could successfully be merged with the block field without
 *   conflict, false otherwise
 *   
 * Guaranteed that the Block pointed to by block will not be modified
 * Guaranteed that this PlayingField object will not be modified
 */
bool PlayingField::couldAdd(const Block *block) const {
    bool can = true;
    
    int xIndex = xIndexFromLocation(block);
    int yIndex = yIndexFromLocation(block);
    
    // Check that it isn't out-of-bounds or intersecting an existing Block
    if (xIndex < 0 || xIndex >= getWidth() || yIndex < 0 || yIndex >= getHeight() ||
            blockField.at(xIndex).at(yIndex))
    {
        can = false;
    }
    
    return can;
}

/*
 * Checks if there are lines to be cleared, and clears them if there are
 * 
 * Is mutually recursive with mergeAndDelete(Shape *)
 * 
 * 
 */
void PlayingField::doLineClear(vector<int> clearableLines) {
	static vector<Shape *> remainingShapes(0);
    
    // If there are lines to clear
    if (clearableLines.size() > 0) {

    	// Extract all the clearable lines into a single Shape
        Shape clearedBlocks;
        for (unsigned int i = 0; i < clearableLines.size(); i++) {
            for (int j = 0; j < getWidth(); j++) {
                clearedBlocks.addBlock(blockField[j][clearableLines[i]]->makeNewClone());
                delete blockField[j][clearableLines[i]];
                blockField[j][clearableLines[i]] = NULL;
            }
        }
        
        clearedBlocks.blink(3, 150);
        
        normalizeBlocks(clearedBlocks);
        
        doClearedBlockEffects(clearedBlocks, remainingShapes);
        
        vector<Shape *> newRemainingShapes = formShapes(blockField);
        
        for (unsigned int i = 0; i < newRemainingShapes.size(); i++) {
            remainingShapes.push_back(newRemainingShapes[i]);
        }
        
        sort(remainingShapes.begin(), remainingShapes.end(), compareShapeByLocation);
    }
    
    // Take each of those shapes and push them all the way down. This should be hierarchically safe because 
    // formShapes() starts it's search at (0,0) and works it's way up, so the first shapes should always be entirely
    // lower than the next shape
    bool didFall = true;
    // While we are still shifting down...
    while(didFall) {
        didFall = false;
        // For each shape...
        vector<int> mergeIndex;
        vector<int> shiftIndex;
        for (unsigned int i = 0; i < remainingShapes.size(); i++) {
            // Shift down once if we can
            if (remainingShapes[i]) {
                if (canShiftDown(remainingShapes[i])) {
                    shiftIndex.push_back(i);
                } else {
                    mergeIndex.push_back(i);
                }
            }
        }
        
        if (mergeIndex.size() > 0) {
            for (unsigned int i = 0; i < mergeIndex.size(); i++) {
                merge(remainingShapes[mergeIndex[i]]);
                
                delete remainingShapes[mergeIndex[i]];
                
                remainingShapes[mergeIndex[i]] = NULL;
            }
            
            draw();
            
            for (unsigned int i = 0; i < remainingShapes.size(); i++) {
                if (remainingShapes[i]) {
                    remainingShapes[i]->draw();
                }
            }
            
            g->Draw(); // Force redraw
            
            clearableLines = getClearableLines();

            if (clearableLines.size() > 0) {
            	doLineClear(clearableLines);
            }
            
            didFall = false;
        }
        
        if (shiftIndex.size() > 0) {
            for (unsigned int i = 0; i < shiftIndex.size(); i++) {
                if (remainingShapes[shiftIndex[i]]) {
                    remainingShapes[shiftIndex[i]]->erase();
                    remainingShapes[shiftIndex[i]]->shiftDown();
                    remainingShapes[shiftIndex[i]]->draw();
                    
                    didFall = true;
                }
            }
        }
        
        g->Draw(); // Force redraw
        
        if (didFall) {
            clock_t start = clock();
            
            while (clock() < start + 100); // Wait 100ms
        }
    }
    
    remainingShapes.clear();
}

vector<int> PlayingField::getClearableLines() {
    vector<int> clearableLines;
    
    for (int i = 0; i < getHeight(); i++) {
        bool isClearable = true;
        for (int j = 0; j < getWidth() && isClearable; j++) {
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
 *   that have the same uniqueID, replacing them with base Blocks
 */
void PlayingField::normalizeBlocks(Shape& shape) {
    for (int i = 0; i < shape.numBlocks(); i++) {
        
        // If the block we are on has a "no-ID", we don't need to check
        if (shape[i] && shape[i]->getUniqueID() != 0) {
            
            // blockField
            for (int j = 0; j < getWidth(); j++) {
                for (int k = 0; k < getHeight(); k++) {
                    if (blockField[j][k] &&
                            blockField[j][k]->getUniqueID() == shape[i]->getUniqueID())
                    {
                        Block *tmp = blockField[j][k];
                        blockField[j][k] = new Block(*tmp); // Not making a clone, this will give us a base Block
                        delete tmp;
                        blockField[j][k]->draw();
                    }
                }
            }
            
            // Passed Shape
            for (int j = i+1; j < shape.numBlocks(); j++) {
                if (shape[i]->getUniqueID() == shape[j]->getUniqueID()) {
                    Block *tmp = shape[j];
                    shape[j] = new Block(*tmp); // Not making a clone, this will give us a base Block
                    delete tmp; // Don't redraw, because these blocks aren't supposed to be visible.
                }
            }
        }
    }
}

void PlayingField::doClearedBlockEffects(Shape& clearedBlocks, vector<Shape *>& remainingShapes) {
    vector<vector<Block *> > remainingBlockField(width, vector<Block *>(height, static_cast<Block *>(NULL)));
    
    // Before we perform any special effects, temporarily directly merge any remainingShapes
    for (unsigned int i = 0; i < remainingShapes.size(); i++) {
        for (int j = 0; remainingShapes[i] && j < remainingShapes[i]->numBlocks(); j++) {
            
            Block *curBlock = (*remainingShapes[i])[j];
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
        clearedBlocks[i]->doEffect(blockField, 
                xIndexFromLocation(clearedBlocks[i]), yIndexFromLocation(clearedBlocks[i]));
        delete clearedBlocks[i];
        clearedBlocks[i] = NULL;
    }
    
    // Extract the merged remainingShapes and make them into a separate blockField
    for (unsigned int i = 0; i < remainingShapes.size(); i++) {
        for (int j = 0; remainingShapes[i] && j < remainingShapes[i]->numBlocks(); j++) {
            Block *curBlock = (*remainingShapes[i])[j];
            int indexX = xIndexFromLocation(curBlock);
            int indexY = yIndexFromLocation(curBlock);
            
            blockField[indexX][indexY] = NULL;
            remainingBlockField[indexX][indexY] = curBlock;
        }
    }
    
    remainingShapes = formShapes(remainingBlockField);
}

vector<Shape *> PlayingField::formShapes(vector<vector<Block *> >& blockField) {
    vector<Shape *> shapes;
    
    for (int i = 0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++) {
            if (blockField[j][i]) {
                Shape *curShape = new Shape(blockField[j][i]->getLocationX(), blockField[j][i]->getLocationY(),
                        blockField[j][i]->getSize(), blockField[j][i]->getPadding());
                
                r_makeShape(curShape, j, i, blockField);
                
                curShape->draw();
                
                shapes.push_back(curShape);
            }
        }
    }
    
    return shapes;
}

void PlayingField::r_makeShape(Shape *shape, int x, int y, vector<vector<Block *> >& blockField) {
    if (x < 0 || x >= getWidth() || y < 0 || y >= getHeight() || !blockField[x][y]) {
        return;
    }
    
    shape->addBlock(blockField[x][y]->makeNewClone());
    
    delete blockField[x][y];
    blockField[x][y] = NULL;
    
    r_makeShape(shape, x+1, y, blockField);
    r_makeShape(shape, x, y+1, blockField);
    r_makeShape(shape, x-1, y, blockField);
    r_makeShape(shape, x, y-1, blockField);
}

/*
 * Merges a clone of the passed Shape into the playingField
 * 
 * Any Block already in the location of the merge is deleted and its pointer is overwritten with a
 *   pointer to the newly allocated block cloned from the passed Shape
 *   
 * Allocates clones of the Blocks in the passed Shape
 * De-allocates any Blocks that may be in the same place as the merge is occurring
 * 
 * Guaranteed that the Shape pointed to by shape will not be modified
 */
void PlayingField::merge(const Shape *shape) {
    for (int i = 0; i < shape->numBlocks(); i++) {
        Block *curBlock = shape->getBlock(i)->makeNewClone();
        int indexX = xIndexFromLocation(curBlock);
        int indexY = yIndexFromLocation(curBlock);
        
        // Delete anything that may already be here
        delete blockField[indexX][indexY];
        
        blockField[indexX][indexY] = curBlock;
        
        curBlock->draw();
    }
}

int PlayingField::xIndexFromLocation(const Block *block) const {
    return (block->getLocationX()-getLocationX())/block->getTotalSize();
}

int PlayingField::yIndexFromLocation(const Block *block) const {
    return (block->getLocationY()-getLocationY())/block->getTotalSize();
}


/* ---------- Overriding from Drawable ---------- */

void PlayingField::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    
    erase();
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blockField[i][j]) {
                blockField[i][j]->setLocation(blockField[i][j]->getLocationX()+dX, blockField[i][j]->getLocationY()+dY);
            }
        }
    }
    
    bgRect.setLocation(bgRect.getLocationX()+dX, getLocationY()+dY);
    
    draw();
    
    this->x = x;
    this->y = y;
}


/* ---------- Implemented from Drawable ---------- */

void PlayingField::draw() {
    bgRect.draw();

    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blockField[i][j]) {
                blockField[i][j]->draw();
            }
        }
    }

    isVisible = true;
}

void PlayingField::erase() {
    if (isVisible) {
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (blockField[i][j]) {
                    blockField[i][j]->erase();
                }
            }
        }
        
        bgRect.erase();
        
        isVisible = false;
    }
}
