/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 29, 2014
 * Date last modified:     Mar 29, 2014
 */

#include "PlayingField.h"

PlayingField::PlayingField(): Drawable(0, 0, 10, 20) {
    init();
}

PlayingField::PlayingField(int x, int y): Drawable(x, y, 10, 20) {
    init();
}

PlayingField::PlayingField(int x, int y, int width, int height, unsigned int background):
        Drawable(x, y, width, height, Color::BLACK, background)
{
    init();
}

PlayingField::PlayingField(const PlayingField& other): Drawable(other) {
    init();
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (other.blocks.at(i).at(j)) {
                blocks[i][i] = other.blocks.at(i).at(j)->makeNewClone();
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
        }
        
        delete bgRect;
        
        Drawable::operator =(rhs);
        
        init();
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (rhs.blocks.at(i).at(j)) {
                    blocks[i][i] = rhs.blocks.at(i).at(j)->makeNewClone();
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
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX(), tmp.getLocationY()+tmp.getTotalSize());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftDown(Shape *const shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX(), tmp.getLocationY()-tmp.getTotalSize());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftLeft(Shape *const shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX()-tmp.getTotalSize(), tmp.getLocationY());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canShiftRight(Shape *const shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(shape->getBlock(i));
        
        // Apply transformation to our tmp Block
        tmp.setLocation(tmp.getLocationX()+tmp.getTotalSize(), tmp.getLocationY());
                
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    
    return can;
}

bool PlayingField::canRotateCW(TetrominoBase *const t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(t->getBlock(i));
        
        // Apply rotation transformation to our tmp Block
        tmp.setLocation(((tmp.getLocationY()-t->getLocationY())/tmp.getTotalSize()-t->getOffsetY()-t->getOffsetX())*
                  tmp.getTotalSize()+t->getLocationX(),
                (t->getWidth()-((tmp.getLocationX()-t->getLocationX())/tmp.getTotalSize()+t->getOffsetX())-1+
                  t->getOffsetY())*tmp.getTotalSize()+t->getLocationY());
        
        if (!couldAdd(&tmp)) {
            can = false;
        }
    }
    return can;
}

bool PlayingField::canRotateCCW(TetrominoBase *const t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block tmp = *(t->getBlock(i));
        
        // Apply rotation transformation to our tmp Block
        tmp.setLocation((t->getHeight()-((tmp.getLocationY()-t->getLocationY())/tmp.getTotalSize()-t->getOffsetY())-1-
                  t->getOffsetX())*tmp.getTotalSize()+t->getLocationX(),
                ((tmp.getLocationX()-t->getLocationX())/tmp.getTotalSize()+t->getOffsetX()+t->getOffsetY())*
                  tmp.getTotalSize()+t->getLocationY());
         
        if (!couldAdd(&tmp)) {
            can = false;
        }
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
    
    bgRect = new MyRectangle(getLocationX(), getLocationY(), BLOCK_SIZE*getWidth() + BLOCK_PADDING*(getWidth()-1),
            BLOCK_SIZE*getHeight() + BLOCK_PADDING*(getHeight()-1), getBackground());
    bgRect->draw();
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
            
            for (unsigned int i = 0; i < clearableLines.size(); i++) {
                for (int j = 0; j < getWidth(); j++) {
                    if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                        blocks[j][clearableLines[i]]->draw();
                    }
                }
            }
            
            g->Draw(); // Force screen redraw
        }
        
        // Erase the lines for good
        for (unsigned int i = 0; i < clearableLines.size(); i++) {
            for (int j = 0; j < getWidth(); j++) {
                if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                    blocks[j][clearableLines[i]]->erase();
                }
            }
        }
        
        // Clone, store, and then clear the blocks
        for (unsigned int i = 0; i < clearableLines.size(); i++) {
            for (int j = 0; j < getWidth(); j++) {
                if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                    clearedBlocks.push_back(blocks[j][clearableLines[i]]->makeNewClone());
                    delete blocks[j][clearableLines[i]];
                    blocks[j][clearableLines[i]] = NULL;
                }
            }
        }
        
        // Perform each block's special effect and delete the copy, should probably find a way to convert the remainder
        // of the special tetromino to a normal tetromino
        // TODO: Above, maybe have some sort of unique id for each Tetromino's blocks
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
                        remainingShapes[i]->shiftDown();
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

// TODO: Better name? Idk.
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
