/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr  9, 2014
 */

#include "PlayingField.h"

PlayingField::PlayingField(): Drawable(0, 0, 10, 20) {
    blockSize = 10;
    padding = 0;
    init();
}

PlayingField::PlayingField(int x, int y, int width, int height, int blockSize, int padding, unsigned int foreground,
        unsigned int background): Drawable(x, y, width, height, foreground, background)
{
    this->blockSize = blockSize;
    this->padding = padding;
    init();
}

PlayingField::PlayingField(const PlayingField& other): Drawable(other) {
    blockSize = other.blockSize;
    padding = other.padding;
    init();
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (other.blocks.at(i).at(j)) {
                blocks[i][j] = other.blocks.at(i).at(j)->makeNewClone();
            }
        }
    }
}

PlayingField& PlayingField::operator =(const PlayingField& rhs) {
    if  (this != &rhs) {
        erase();
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (blocks[i][j]) {
                    delete blocks[i][j];
                }
            }
            
            blocks[i].clear();
        }
        
        blocks.clear();
        
        delete bgRect;
        
        Drawable::operator =(rhs);
        blockSize = rhs.blockSize;
        padding = rhs.padding;
        
        init();
        
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

PlayingField::~PlayingField() {
    erase();
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blocks[i][j]) {
                delete blocks[i][j];
            }
        }
    }
    
    delete bgRect;
}

void PlayingField::mergeAndDelete (Shape *shape) {
    for (int i = 0; i < shape->numBlocks(); i++) {
        Block *curBlock = shape->getBlock(i)->makeNewClone();
        blocks[(curBlock->getLocationX()-getLocationX())/curBlock->getTotalSize()]
              [(curBlock->getLocationY()-getLocationY())/curBlock->getTotalSize()] = curBlock;
    }
    
    delete shape;
    
    draw();
    
    doLineClear();
}

bool PlayingField::canShiftUp(Shape *const shape) const {
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

bool PlayingField::canShiftDown(Shape *const shape) const {
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

bool PlayingField::canShiftLeft(Shape *const shape) const {
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

bool PlayingField::canShiftRight(Shape *const shape) const {
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

bool PlayingField::canRotateCW(TetrominoBase *const t) const {
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

bool PlayingField::canRotateCCW(TetrominoBase *const t) const {
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

void PlayingField::init() {
    for (int i = 0; i < getWidth(); i++) {
        vector<Block *> tmp;
        blocks.push_back(tmp);
        for (int j = 0; j < getHeight(); j++) {
            // Everything that is a NULL pointer represents a blank space, makes checking for overlap super-simple,
            // just gotta add checks everywhere. Initialize all Block pointers to NULL
            blocks[i].push_back(NULL);
        }
    }
    
    bgRect = new MyRectangle(getLocationX(), getLocationY(), blockSize*getWidth() + padding*(getWidth()-1),
            blockSize*getHeight() + padding*(getHeight()-1), getForeground(), getBackground());

    draw();
}

bool PlayingField::couldAdd(Block *const block) const {
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

void PlayingField::doLineClear() {
    vector<int> clearableLines;
    vector<Block *> clearedBlocks;
    vector<Shape *> remainingShapes;
    
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
        
        // For each cleared block, perform the block's special effect
        for (unsigned int i = 0; i < clearedBlocks.size(); i++) {
            clearedBlocks[i]->doOnClear(blocks, 
                    (clearedBlocks[i]->getLocationX()-getLocationX())/clearedBlocks[i]->getTotalSize(),
                    (clearedBlocks[i]->getLocationY()-getLocationY())/clearedBlocks[i]->getTotalSize());
            delete clearedBlocks[i];
        }
        
        
        // Take what's left over, form it into individual shapes
        remainingShapes = formShapes();
        // Note that after this, the field is entirely NULL
        
        // Take each of those shapes and push them all the way down. This should be hierarchically safe because 
        // formShapes() starts it's search at (0,0) and works it's way up, so the first shapes should always be entirely
        // lower than the next shape
        bool didFall = true;
        // While we are still shifting down...
        while(didFall) {
            didFall = false;
            // For each shape...
            for (unsigned int i = 0; i < remainingShapes.size(); i++) {
                // Shift down once if we can
                if (remainingShapes[i]) {
                    if (canShiftDown(remainingShapes[i])) {
                        remainingShapes[i]->erase();
                        remainingShapes[i]->shiftDown();
                        remainingShapes[i]->draw();
                        didFall = true;
                    } else {
                        mergeAndDelete(remainingShapes[i]);
                        remainingShapes[i] = NULL; // For existence checking
                    }
                }
            }
            
            g->Draw();
            
            if (didFall) {
                start = clock();
                
                while (clock() < start + 100);
            }
        }
    }
}

vector<Shape *> PlayingField::formShapes() {
    vector<Shape *> shapes;
    
    for (int i = 0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++) {
            if (blocks[j][i]) {
                Shape *curShape = new Shape(blocks[j][i]->getLocationX(), blocks[j][i]->getLocationY(),
                        blocks[j][i]->getSize(), blocks[j][i]->getPadding());
                
                makeShapeRecursively(curShape, j, i);
                
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
    
    bgRect->setLocation(bgRect->getLocationX()+dX, getLocationY()+dY);
    
    draw();
    
    this->x = x;
    this->y = y;
}


/* ---------- Implemented from Drawable ---------- */

void PlayingField::draw() {
    bgRect->draw();

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
        
        bgRect->erase();
        
        isVisible = false;
    }
}
