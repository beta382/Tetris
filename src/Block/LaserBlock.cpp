/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "LaserBlock.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a LaserBlock object using default values.
 */
LaserBlock::LaserBlock():
Block()
{
}

/*
 * Instantiates a LaserBlock object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this LaserBlock object's x with
 *   int y: The value to initialize this LaserBlock object's y with
 *   int width: The value to initialize this LaserBlock object's size with
 *   int padding: The value to initialize this LaserBlock object's padding with
 *   unsigned int foreground: The value to initialize this LaserBlock object's foreground with,
 *     defaults to Color::WHITE
 *   unsigned int background: The value to initialize this LaserBlock object's background with,
 *     defaults to Color::BLACK
 */
LaserBlock::LaserBlock(int x, int y, int size, int padding, unsigned int foreground,
        unsigned int background):
Block(x, y, size, padding, foreground, background)
{
}

/*
 * Instantiates a LaserBlock object that is a copy of the passed LaserBlock object, except for bool
 *   isVisible, which is initialized with false, and unsigned int uniqueID, which is initialized
 *   with 0.
 * 
 * Parameters:
 *   const LaserBlock& other: A reference to the LaserBlock object to copy from
 */
LaserBlock::LaserBlock(const LaserBlock& other):
Block(other)
{
}

/*
 * Destructs this LaserBlock object.
 */
LaserBlock::~LaserBlock() {
    erase();
}


/* ---------- Public ---------- */

/*
 * Assigns this LaserBlock object the values of the passed LaserBlock object, except for bool
 *   isVisible, which is assigned false, and unsigned int uniqueID, which is assigned 0.
 * 
 * Parameters:
 *   const LaserBlock& rhs: A reference to the LaserBlock object to assign from
 * 
 * Returns: A reference to this LaserBlock object
 */
LaserBlock& LaserBlock::operator =(const LaserBlock& rhs) {
    if (this != &rhs) {
        Block::operator =(rhs);
    }
    
    return *this;
}


/* ---------- Overriding from Block ---------- */

/*
 * Performs this LaserBlock's special effect on the given blockField from the passed coordinates.
 *   Should be called when this LaserBlock is cleared from the PlayingField.
 *   
 * Parameters:
 *   BlockField& blockField: A reference to the blockField to perform the effect on
 *   int x: The x-coordinate of this LaserBlock within the blockField
 *   int y: The y-coordinate of this LaserBlock within the blockField
 *   
 * Returns: The number of points the special effect accumulated
 */
int LaserBlock::doEffect(BlockField& blockField, int x, int y) {
    int points = 100;
    
    
    
    int laserY, baseRow;
    
    if (y <= 0) {
        laserY = getLocationY()-getTotalSize()*y; // Zeros the location
        baseRow = 0;
    } else if (y >= (blockField.getInternalHeight()-1)) {
        laserY = getLocationY()+getTotalSize()*(blockField.getInternalHeight()-3-y); // Maxes the location
        baseRow = blockField.getInternalHeight()-3;
    } else {
        laserY = getLocationY()-getTotalSize();
        baseRow = y-1;
    }
    
    Rect laser(getLocationX()-getTotalSize()*x, laserY, blockField.getInternalWidth()*getTotalSize()-
            getPadding(), getTotalSize()*3-getPadding(), Color::RED, getBackground());
    
    laser.blink(3, 150);
    
    // Normalize blocks in case this got called from another block's effect
    for (int i = 0; i < blockField.getInternalWidth(); i++) {
        for (int j = 0; j < blockField.getInternalHeight(); j++) {
            if (blockField.get(i, j) && blockField.get(i, j)->getUniqueID() == getUniqueID()) {
                Block* tmp = blockField.get(i, j);
                
                // Not making a clone, this will give us a base Block
                blockField.at(i, j) = new Block(*tmp);
                delete tmp;
                blockField.get(i, j)->draw();
            }
        }
    }
    
    // Actually clear the blocks
    for (int i = baseRow; i < baseRow+3; i++) {
        for (int j = 0; j < blockField.getInternalWidth(); j++) {
            if (i >= 0 && i < blockField.getInternalHeight() && blockField.get(j, i)) {
                Block* tmp = blockField.get(j, i);
                blockField.at(j, i) = NULL;
                
                points += tmp->doEffect(blockField, j, i);
                
                delete tmp;
            }
        }
    }
    
    return points;
}

/*
 * Allocates a clone of this LaserBlock, including it's uniqueID.
 *   
 * Returns: The address of the newly instantiated clone of this LaserBlock
 */
LaserBlock* LaserBlock::makeNewClone() const {
    LaserBlock* tmp = new LaserBlock(*this);
    
    tmp->setUniqueID(getUniqueID());
    
    return tmp;
}

/*
 * Draws this LaserBlock to the screen.
 */
void LaserBlock::draw() {
    g->setColor(getForeground());
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            
            // Outline
            if (i == 0 || i == getWidth()-1 || j == 0 || j == getHeight()-1) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Beam
            if (j >= (3*getHeight())/8 && j < (5*getHeight())/8) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }
    }
    
    isVisible = true;
}

