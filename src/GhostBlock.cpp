/*
 * Author:                 Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr  4, 2014
 * Date last modified:     Apr 26, 2014
 */

#include "GhostBlock.h"


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

/*
 * Destructs this GhostBlock object.
 */
GhostBlock::~GhostBlock() {
    erase();
}


/* ---------- Public ---------- */

/*
 * Assigns this GhostBlock object the values of the passed GhostBlock object, except for bool
 *   isVisible, which is assigned false, and unsigned int uniqueID, which is assigned 0.
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


/* ---------- Overriding from Block ---------- */

/*
 * Performs this GhostBlock's special effect on the given blockField from the passed coordinates.
 *   Should be called when this GhostBlock is cleared from the PlayingField.
 *   
 * Parameters:
 *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the effect on
 *   int x: The x-coordinate of this GhostBlock within the blockField
 *   int y: The y-coordinate of this GhostBlock within the blockField
 *   
 * Returns: The number of points the special effect accumulated
 */
int GhostBlock::doEffect(vector<vector<Block*> >& blockField, int x, int y) {
    return 0;
}

/*
 * Allocates a clone of this GhostBlock, including it's uniqueID.
 *   
 * Returns: The address of the newly instantiated clone of this GhostBlock
 */
GhostBlock* GhostBlock::makeNewClone() const {
    GhostBlock* tmp = new GhostBlock(*this);
    
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
