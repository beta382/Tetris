/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr 11, 2014
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
        blocks(width, vector<Block *>(height, static_cast<Block *>(NULL)))
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
        blocks(width, vector<Block *>(height, static_cast<Block *>(NULL)))
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
        blocks(width, vector<Block *>(height, static_cast<Block *>(NULL)))
{
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (other.blocks.at(i).at(j)) {
                blocks[i][j] = other.blocks.at(i).at(j)->makeNewClone();
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
                delete blocks[i][j];
            }
            
            blocks[i].clear();
        }
        
        blocks.clear();
        
        Drawable::operator =(rhs);
        blockSize = rhs.blockSize;
        padding = rhs.padding;
        bgRect = rhs.bgRect;
        
        blocks.assign(width, vector<Block *>(height, static_cast<Block *>(NULL)));
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (rhs.blocks.at(i).at(j)) {
                    blocks[i][j] = rhs.blocks.at(i).at(j)->makeNewClone();
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
            delete blocks[i][j];
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
    
    /*if (canLineClear())*/ doLineClear();
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
    
    // Check that it isn't out-of-bounds or intersecting an existing Block
    if ((block->getLocationX()-getLocationX())/block->getTotalSize() < 0 || 
        (block->getLocationX()-getLocationX())/block->getTotalSize() >= getWidth() || 
        (block->getLocationY()-getLocationY())/block->getTotalSize() < 0 || 
        (block->getLocationY()-getLocationY())/block->getTotalSize() >= getHeight() ||
         blocks.at((block->getLocationX()-getLocationX())/block->getTotalSize())
               .at((block->getLocationY()-getLocationY())/block->getTotalSize()))
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
void PlayingField::doLineClear() {
    vector<int> clearableLines;
    vector<Block *> clearedBlocks;
    cout << "---- Entered doLineClear ----" << endl;
    // This is static because we make a mutually recursive call to mergeAndDelete(Shape * later on, and
    // when that calls this function, wouldn't normally have the vector of remaining shapes
    static vector<Shape *> remainingShapes(0); 
    
    clock_t start;
    
    // Find which lines can be cleared
    for (int i = 0; i < getHeight(); i++) {
        bool isClearable = true;
        for (int j = 0; j < getWidth() && isClearable; j++) {
            if (!blocks[j][i]) {
                isClearable = false;
            }
        }
        
        if (isClearable) {
            clearableLines.push_back(i);
        }
    }
    
    // If there are lines to clear
    if (clearableLines.size() > 0) {
        
        // Blink three times
        for (int r = 0; r < 3; r++) {
            
            for (unsigned int i = 0; i < clearableLines.size(); i++) {
                for (int j = 0; j < getWidth(); j++) {
                    if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                        blocks[j][clearableLines[i]]->draw();
                    }
                }
            }
            
            g->Draw(); // Force screen redraw
            
            start = clock();
            
            while (clock() < start+150); // Wait 150ms
            
            for (unsigned int i = 0; i < clearableLines.size(); i++) {
                for (int j = 0; j < getWidth(); j++) {
                    if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                        blocks[j][clearableLines[i]]->erase();
                    }
                }
            }
            
            g->Draw(); // Force screen redraw
            
            start = clock();
            
            while (clock() < start+150); // Wait 150ms
        }
        
        // Clone, store, and then remove the blocks
        for (unsigned int i = 0; i < clearableLines.size(); i++) {
            for (int j = 0; j < getWidth(); j++) {
                if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                    clearedBlocks.push_back(blocks[j][clearableLines[i]]->makeNewClone());
                    delete blocks[j][clearableLines[i]];
                    blocks[j][clearableLines[i]] = NULL;
                }
            }
        }
        
        // Go through the list of cleared blocks and find all blocks from the same tetromino into standard blocks
        for (unsigned int i = 0; i < clearedBlocks.size(); i++) {
            
            // If the block we are on has a "no-ID", we don't need to check
            if (clearedBlocks[i]->getUniqueID() != 0) {
                
                // Go through each block on the field and check for ones with the same unique ID, and replace them
                for (int j = 0; j < getWidth(); j++) {
                    for (int k = 0; k < getHeight(); k++) {
                        if (blocks[j][k] && blocks[j][k]->getUniqueID() != 0 &&
                                blocks[j][k]->getUniqueID() == clearedBlocks[i]->getUniqueID())
                        {
                            Block *tmp = blocks[j][k];
                            blocks[j][k] = new Block(*tmp); // Not making a clone, this will give us a base Block
                            delete tmp;
                            blocks[j][k]->draw(); // Redraw the new block since what used to be there just got erased
                        }
                    }
                }
                
                // Go through the list of cleared blocks, check for ones with the same unique ID, and replace them
                for (unsigned int j = i+1; j < clearedBlocks.size(); j++) {
                    if (clearedBlocks[j]->getUniqueID() != 0 &&
                            clearedBlocks[i]->getUniqueID() == clearedBlocks[j]->getUniqueID())
                    {
                        Block *tmp = clearedBlocks[j];
                        clearedBlocks[j] = new Block(*tmp); // Not making a clone, this will give us a base Block
                        delete tmp; // Don't redraw, because these blocks aren't supposed to be visible.
                    }
                }
            }
        }
        
        // For each cleared block, perform the block's special effect, and then delete the block
        for (unsigned int i = 0; i < clearedBlocks.size(); i++) {
            clearedBlocks[i]->doOnClear(blocks, 
                    (clearedBlocks[i]->getLocationX()-getLocationX())/clearedBlocks[i]->getTotalSize(),
                    (clearedBlocks[i]->getLocationY()-getLocationY())/clearedBlocks[i]->getTotalSize());
            delete clearedBlocks[i];
        }
    } // End of "If there are lines to clear"

    if (remainingShapes.size() == 0) {
        remainingShapes = formShapes();
        g->Draw(); // Force redraw
    }
    
    if (clearableLines.size() > 0) {
        vector<Shape *> newRemainingShapes = formShapes();
        g->Draw(); // Force redraw
        
        for (unsigned int i = 0; i < newRemainingShapes.size(); i++) {
            remainingShapes.push_back(newRemainingShapes[i]);
        }
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
            
            g->Draw();
            
            doLineClear();
            
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
            
            g->Draw();
        }
        
        g->Draw(); // Force redraw
        
        if (didFall) {
            start = clock();
            
            while (clock() < start + 100); // Wait 100ms
        }
    }
    
    // At this point, we can't be called again from mergeAndDelete(Shape *), so go ahead and erase remainingShapes
    remainingShapes.clear();
    cout << "---- Exited doLineClear ----" << endl;
}

vector<Shape *> PlayingField::formShapes() {
    vector<Shape *> shapes;
    
    for (int i = 0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++) {
            if (blocks[j][i]) {
                Shape *curShape = new Shape(blocks[j][i]->getLocationX(), blocks[j][i]->getLocationY(),
                        blocks[j][i]->getSize(), blocks[j][i]->getPadding());
                
                makeShapeRecursively(curShape, j, i);
                
                curShape->draw();
                
                shapes.push_back(curShape);
            }
        }
    }
    
    return shapes;
}

void PlayingField::makeShapeRecursively(Shape *shape, int x, int y) {
    if (x < 0 || x >= getWidth() || y < 0 || y >= getHeight() || !blocks[x][y]) {
        return;
    }
    
    shape->addBlock(blocks[x][y]->makeNewClone());
    
    delete blocks[x][y];
    blocks[x][y] = NULL;
    
    makeShapeRecursively(shape, x+1, y);
    makeShapeRecursively(shape, x, y+1);
    makeShapeRecursively(shape, x-1, y);
    makeShapeRecursively(shape, x, y-1);
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
        int indexX = (curBlock->getLocationX()-getLocationX())/curBlock->getTotalSize();
        int indexY = (curBlock->getLocationY()-getLocationY())/curBlock->getTotalSize();
        
        // Delete anything that may already be here
        delete blocks[indexX][indexY];
        
        blocks[indexX][indexY] = curBlock;
        
        curBlock->draw();
    }
}

/* ---------- Overriding from Drawable ---------- */

void PlayingField::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    
    erase();
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blocks[i][j]) {
                blocks[i][j]->setLocation(blocks[i][j]->getLocationX()+dX, blocks[i][j]->getLocationY()+dY);
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
            if (blocks[i][j]) {
                blocks[i][j]->draw();
            }
        }
    }

    isVisible = true;
}

void PlayingField::erase() {
    if (isVisible) {
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (blocks[i][j]) {
                    blocks[i][j]->erase();
                }
            }
        }
        
        bgRect.erase();
        
        isVisible = false;
    }
}
