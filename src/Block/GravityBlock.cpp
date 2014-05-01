/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 23, 2014
 * Date last modified:     Apr 26, 2014
 */

#include "GravityBlock.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a GravityBlock object using default values.
 */
GravityBlock::GravityBlock():
Block()
{
}

/*
 * Instantiates a GravityBlock object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this GravityBlock object's x with
 *   int y: The value to initialize this GravityBlock object's y with
 *   int width: The value to initialize this GravityBlock object's size with
 *   int padding: The value to initialize this GravityBlock object's padding with
 *   unsigned int foreground: The value to initialize this GravityBlock object's foreground with,
 *     defaults to Color::WHITE
 *   unsigned int background: The value to initialize this GravityBlock object's background with,
 *     defaults to Color::BLACK
 */
GravityBlock::GravityBlock(int x, int y, int size, int padding, unsigned int foreground,
        unsigned int background):
Block(x, y, size, padding, foreground, background)
{
}

/*
 * Instantiates a GravityBlock object that is a copy of the passed GravityBlock object, except for
 *   bool isVisible, which is initialized with false, and unsigned int uniqueID, which is
 *   initialized with 0.
 * 
 * Parameters:
 *   const GravityBlock& other: A reference to the GravityBlock object to copy from
 */
GravityBlock::GravityBlock(const GravityBlock& other):
Block(other)
{
}

/*
 * Destructs this GravityBlock object.
 */
GravityBlock::~GravityBlock() {
    erase();
}


/* ---------- Public ---------- */

/*
 * Assigns this GravityBlock object the values of the passed GravityBlock object, except for bool
 *   isVisible, which is assigned false, and unsigned int uniqueID, which is assigned 0.
 * 
 * Parameters:
 *   const GravityBlock& rhs: A reference to the GravityBlock object to assign from
 * 
 * Returns: A reference to this GravityBlock object
 */
GravityBlock& GravityBlock::operator =(const GravityBlock& rhs) {
    if (this != &rhs) {
        Block::operator =(rhs);
    }
    
    return *this;
}


/* ---------- Overriding from Block ---------- */

/*
 * Performs this GravityBlock's special effect on the given blockField from the passed coordinates.
 *   Should be called when this GravityBlock is cleared from the PlayingField.
 *   
 * Parameters:
 *   BlockField& blockField: A reference to the blockField to perform the effect on
 *   int x: The x-coordinate of this GravityBlock within the blockField
 *   int y: The y-coordinate of this GravityBlock within the blockField
 *   
 * Returns: The number of points the special effect accumulated
 */
int GravityBlock::doEffect(BlockField& blockField, int x, int y) {
    int points = 100;
    
    bool didFall = true;
    while (didFall) {
        didFall = false;
        
        for (int i = 0; i < blockField.getInternalWidth(); i++) {
            for (int j = 1; j < blockField.getInternalHeight(); j++) {
                if (blockField.get(i, j) && !blockField.get(i, j-1)) {
                    blockField.get(i, j)->erase();
                    blockField.at(i, j-1) = blockField.get(i, j);

                    blockField.at(i, j) = NULL;
                    
                    blockField.get(i, j-1)->setLocation(blockField.get(i, j-1)->getLocationX(), 
                            blockField.get(i, j-1)->getLocationY()-blockField.get(i, j-1)->getTotalSize());
                    blockField.get(i, j-1)->draw();
                    
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
 * Allocates a clone of this GravityBlock, including it's uniqueID.
 *   
 * Returns: The address of the newly instantiated clone of this GravityBlock
 */
GravityBlock* GravityBlock::makeNewClone() const {
    GravityBlock* tmp = new GravityBlock(*this);
    
    tmp->setUniqueID(getUniqueID());
    
    return tmp;
}

/*
 * Draws this GravityBlock to the screen.
 */
void GravityBlock::draw() {
    g->setColor(getForeground());
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            
            // Outline
            if (i == 0 || i == getWidth()-1 || j == 0 || j == getHeight()-1) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Arrow left half
            if ((i > getWidth()/8 && i < getWidth()/2) && 
                    (j >= -i + getHeight()/2 && j < (3*getHeight())/8))
            {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Arrow right half
            if ((i >= getWidth()/2 && i < (7*getWidth())/8-1) && 
                    (j > i - getHeight()/2 && j < (3*getHeight())/8))
            {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Arrow tail
            if ((i >= (3*getWidth())/8 && i < (5*getWidth())/8) && 
                    (j >= (3*getHeight())/8 && j < getHeight()))
            {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }
    }
    
    isVisible = true;
}
