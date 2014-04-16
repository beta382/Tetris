/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  4, 2014
 * Date last modified:     Apr 15, 2014
 */

#include "GhostBlock.h"

//* Just put an extra slash in front to un-comment
#include "Rectangle.h"
//*/



/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a GhostBlock object using default values.
 */
GhostBlock::GhostBlock():
Block()
{
}

/*
 * Instantiates a GhostBlock object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this GhostBlock object's x with
 *   int y: The value to initialize this GhostBlock object's y with
 *   int width: The value to initialize this GhostBlock object's size with
 *   int padding: The value to initialize this GhostBlock object's padding with
 *   unsigned int foreground: The value to initialize this GhostBlock object's foreground with,
 *     defaults to Color::WHITE
 *   unsigned int background: The value to initialize this GhostBlock object's background with,
 *     defaults to Color::BLACK
 */
GhostBlock::GhostBlock(int x, int y, int size, int padding, unsigned int foreground, unsigned int background):
Block(x, y, size, padding, foreground, background)
{
}

/*
 * Instantiates a GhostBlock object that is a copy of the passed GhostBlock object, except for bool
 *   isVisible, which is initialized with false, and unsigned int uniqueID, which is initialized
 *   with 0.
 * 
 * Parameters:
 *   const GhostBlock& other: A reference to the GhostBlock object to copy from
 */
GhostBlock::GhostBlock(const GhostBlock& other):
Block(other)
{
}


/* ---------- Public ---------- */

/*
 * Assigns this GhostBlock object the values of the passed GhostBlock object, except for bool isVisible, which
 *   is assigned false, and unsigned int uniqueID, which is assigned 0.
 * 
 * Parameters:
 *   const GhostBlock& rhs: A reference to the GhostBlock object to assign from
 * 
 * Returns: A reference to this GhostBlock object
 */
GhostBlock& GhostBlock::operator =(const GhostBlock& rhs) {
    if (this != &rhs) {
        Block::operator =(rhs);
    }
    
    return *this;
}

/*
 * Destructs this Block object.
 */
GhostBlock::~GhostBlock() {
    erase();
}


/* ---------- Overriding from Block ---------- */

/*
 * Performs this GhostBlock special effect on the given blockField from the passed coordinates.
 *   Should be called when this GhostBlock is cleared from the PlayingField.
 *   
 * Parameters:
 *   <vector<vector<Block *> >& blockField: A reference to the blockField to perform the effect on
 *   int x: The x-coordinate of this GhostBlock within the blockField
 *   int y: The y-coordinate of this GhostBlock within the blockField
 */
void GhostBlock::doEffect(vector<vector<Block *> >& blockField, int x, int y) {
    // Do nothing
    
    // ExplodingBlock example, needs "Rectangle.h"
    /* Just put an extra slash in front to un-comment
    // Make a big explosion block
    
    int explosionX = (x >= 2) ? getLocationX()-getTotalSize()*2 : getLocationX()-getTotalSize()*x;
    
    int explosionY = (y >= 2) ? getLocationY()-getTotalSize()*2 : getLocationY()-getTotalSize()*y;
    
    int explosionWidth;
    
    if (x >= 2 && (blockField.size()-x-1) >= 2) {
        explosionWidth = getTotalSize()*5-getPadding();
    } else if (x >= 2) {
        explosionWidth = getTotalSize()*(blockField.size()-x+2)-getPadding();
    } else {
        explosionWidth = getTotalSize()*(x+3)-getPadding();
    }

    int explosionHeight;
    if (y >= 2 && (blockField[0].size()-y-1) >= 2) {
        explosionHeight = getTotalSize()*5-getPadding();
    } else if (y >= 2) {
        explosionHeight = getTotalSize()*(blockField.size()-y+2)-getPadding();
    } else {
        explosionHeight = getTotalSize()*(y+3)-getPadding();
    }
    
    MyRectangle explosion(explosionX, explosionY, explosionWidth, explosionHeight, Color::RED,
            getBackground());
    
    explosion.blink(3, 150);
    
    // Actually clear the blocks
    for (int i = x-2; i <= x+2; i++) {
        for (int j = y-2; j <= y+2; j++) {
            if (i >= 0 && i < (int)blockField.size() && j >= 0 && j < (int)blockField[i].size() &&
                    blockField[i][j]) {
                blockField[i][j]->erase();
                
                Block *tmp = blockField[i][j];
                blockField[i][j] = NULL;
                
                tmp->doEffect(blockField, i, j);
                delete tmp;
            }
        }
    }
    
    //*/

    // GravityBlock example, needs <ctime>
    //* Just put an extra slash in front to un-comment
    bool didFall = true;
    while (didFall) {
        didFall = false;
        
        for (unsigned int i = 0; i < blockField.size(); i++) {
            for (unsigned int j = 1; j < blockField[i].size(); j++) {
                if (blockField[i][j] && !blockField[i][j-1]) {
                    blockField[i][j]->erase();
                    blockField[i][j-1] = blockField[i][j];

                    blockField[i][j] = NULL;
                    
                    blockField[i][j-1]->setLocation(blockField[i][j-1]->getLocationX(), 
                            blockField[i][j-1]->getLocationY()-blockField[i][j-1]->getTotalSize());
                    blockField[i][j-1]->draw();
                    
                    didFall = true;
                }
            }
        }
        
        g->Draw(); // Force screen redraw
        
        util::wait(100);
    }
    //*/
}

/*
 * Allocates a clone of this GhostBlock, including it's uniqueID.
 *   
 * Returns: The address of the newly instantiated clone of this GhostBlock
 */
GhostBlock *GhostBlock::makeNewClone() {
    GhostBlock *tmp = new GhostBlock(*this);
    
    tmp->setUniqueID(getUniqueID());
    
    return tmp;
}

/*
 * Draws this GhostBlock to the screen.
 */
void GhostBlock::draw() {
    g->setColor(getForeground());
    for (int i = 0; i < getWidth(); i++) {
        g->plot(getLocationX()+i, getLocationY());
        g->plot(getLocationX()+i, getLocationY()+getHeight()-1);
    }
    
    for (int i = 1; i < getHeight()-1; i++) {
        g->plot(getLocationX(), getLocationY()+i);
        g->plot(getLocationX()+getWidth()-1, getLocationY()+i);
    }
    
    isVisible = true;
}

/*
 * Erases this GhostBlock from the screen.
 */
void GhostBlock::erase() {
    if (isVisible) {
        g->setColor(getBackground());
        for (int i = 0; i < getWidth(); i++) {
            g->plot(getLocationX()+i, getLocationY());
            g->plot(getLocationX()+i, getLocationY()+getHeight()-1);
        }
        
        for (int i = 1; i < getHeight()-1; i++) {
            g->plot(getLocationX(), getLocationY()+i);
            g->plot(getLocationX()+getWidth()-1, getLocationY()+i);
        }
        
        isVisible = false;
    }
}
