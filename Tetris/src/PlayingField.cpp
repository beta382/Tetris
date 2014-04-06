/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: 
 * Assignment description:
 * Due date:               
 * Date created:           Mar 29, 2014
 * Date last modified:     Mar 29, 2014
 */

#include "PlayingField.h"

PlayingField::PlayingField(GLUT_Plotter *g): Drawable(g, 0, 0, 10, 20) {
    init();
}

PlayingField::PlayingField(GLUT_Plotter *g, int x, int y): Drawable(g, x, y, 10, 20) {
    init();
}

PlayingField::PlayingField(GLUT_Plotter *g, int x, int y, int width, int height): Drawable(g, x, y, width, height) {
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
}

void PlayingField::mergeAndDelete (Shape *shape) {
    for (int i = 0; i < shape->numBlocks(); i++) {
        Block *curBlock = shape->getBlock(i)->makeNewClone();
        blocks[(curBlock->getLocationX()-getLocationX())/curBlock->getTotalSize()]
              [(curBlock->getLocationY()-getLocationY())/curBlock->getTotalSize()] = curBlock;
    }
    
    delete shape;
    
    draw(); // TODO: Probably make a `void redraw()` eventually
    
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
        myVector<Block *> tmp;
        blocks.pushBack(tmp);
        for (int j = 0; j < getHeight(); j++) {
            // Everything that is a NULL pointer represents a blank space, makes checking for overlap super-simple,
            // just gotta add checks everywhere. Initialize all Block pointers to NULL
            blocks[i].pushBack(NULL);
        }
    }
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
    myVector<int> clearableLines;
    
    // Find which lines can be cleared
    for (int i = 0; i < getHeight(); i++) {
        bool isClearable = true;
        for (int j = 0; j < getWidth() && isClearable; j++) {
            if (!blocks[j][i]) {
                isClearable = false;
            }
        }
        
        if (isClearable) {
            clearableLines.pushBack(i);
        }
    }
    
    // If there are lines to clear
    if (clearableLines.getSize() > 0) {
        
        // Blink three times
        for (int r = 0; r < 3; r++) {
            clock_t start;
            
            start = clock();
            
            while (clock() < start+150); // Wait 150ms
            
            for (int i = 0; i < clearableLines.getSize(); i++) {
                for (int j = 0; j < getWidth(); j++) {
                    if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                        blocks[j][clearableLines[i]]->erase();
                    }
                }
            }
            
            g->Draw(); // Force screen redraw
            
            start = clock();
            
            while (clock() < start+150); // Wait 150ms
            
            for (int i = 0; i < clearableLines.getSize(); i++) {
                for (int j = 0; j < getWidth(); j++) {
                    if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                        blocks[j][clearableLines[i]]->draw();
                    }
                }
            }
            
            g->Draw(); // Force screen redraw
        }
        
        // Delete and NULL the Blocks
        for (int i = 0; i < clearableLines.getSize(); i++) {
            for (int j = 0; j < getWidth(); j++) {
                if (blocks[j][clearableLines[i]]) { // Not really necessary since existence is guaranteed, but w/e
                    delete blocks[j][clearableLines[i]];
                    blocks[j][clearableLines[i]] = NULL;
                }
            }
        }
        
        // Take what's left over, form it into individual shapes, and then 
        myVector<Shape *> shapes = formShapes();
        
        for (int i = 0; i < shapes.getSize(); i++) {
            while (canShiftDown(shapes[i])) {
                shapes[i]->shiftDown();
            }
            
            mergeAndDelete(shapes[i]);
        }
    }
}

myVector<Shape *> PlayingField::formShapes() {
    myVector<Shape *> shapes;
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blocks[i][j]) {
                Shape *curShape = new Shape(g, blocks[i][j]->getLocationX(), blocks[i][j]->getLocationY(), 
                        blocks[i][j]->getSize(), blocks[i][j]->getPadding());
                
                makeShapeRecursively(curShape, i, j);
                
                shapes.pushBack(curShape);
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
        
        isVisible = false;
    }
}
