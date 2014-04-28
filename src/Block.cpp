/*
 * Author:                 Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 15, 2014
 */

#include "Block.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a Block object using default values.
 */
Block::Block ():
Drawable(0, 0, 10, 10),
        padding(0), uniqueID(0)
{
}

/*
 * Instantiates a Block object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this Block object's x with
 *   int y: The value to initialize this Block object's y with
 *   int width: The value to initialize this Block object's size with
 *   int padding: The value to initialize this Block object's padding with
 *   unsigned int foreground: The value to initialize this Block object's foreground with, defaults
 *     to Color::WHITE
 *   unsigned int background: The value to initialize this Block object's background with, defaults
 *     to Color::BLACK
 */
Block::Block (int x, int y, int size, int padding, unsigned int foreground, unsigned int background):
Drawable(x, y, size, size, foreground, background),
        padding(padding), uniqueID(0)
{
}

/*
 * Instantiates a Block object that is a copy of the passed Block object, except for bool isVisible,
 *   which is initialized with false, and unsigned int uniqueID, which is initialized with 0.
 * 
 * Parameters:
 *   const Block& other: A reference to the Block object to copy from
 */
Block::Block (const Block& other):
Drawable(other),
        padding(other.padding), uniqueID(0)
{
}

/*
 * Destructs this Block object.
 */
Block::~Block() {
    erase();
}


/* ---------- Public ---------- */

/*
 * Assigns this Block object the values of the passed Block object, except for bool isVisible, which
 *   is assigned false, and unsigned int uniqueID, which is assigned 0.
 * 
 * Parameters:
 *   const Block& rhs: A reference to the Block object to assign from
 * 
 * Returns: A reference to this Block object
 */
Block& Block::operator =(const Block& rhs) {
    if (this != &rhs) {
        Drawable::operator =(rhs);
        padding = rhs.padding;
        uniqueID = 0;
    }
    
    return *this;
}

/*
 * Getter for size.
 * 
 * Returns: The value of this Block object's width
 */
int Block::getSize() const {
    return width;
}

/*
 * Getter for padding.
 * 
 * Returns: The value of this Block object's padding
 */
int Block::getPadding() const {
    return padding;
}

/*
 * Getter for the sum of blockSize and padding.
 * 
 * Returns: The value of this Block object's width+padding
 */
int Block::getTotalSize() const {
    return getSize()+getPadding();
}

/*
 * Getter for uniqueID.
 * 
 * Returns: The value of this Block object's uniqueID
 */
unsigned int Block::getUniqueID() const {
    return uniqueID;
}

/*
 * Assigns uniqueID the value of the passed parameter.
 *  
 * Parameters:
 *   unsigned int id: The value to assign to this Block object's uniqueID
 */
void Block::setUniqueID(unsigned int id) {
    uniqueID = id;
}

/*
 * Performs this Block's special effect on the given blockField from the passed coordinates. Should
 *   be called when this Block is cleared from the PlayingField.
 *   
 * Parameters:
 *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the effect on
 *   int x: The x-coordinate of this Block within the blockField
 *   int y: The y-coordinate of this Block within the blockField
 *   
 * Returns: The number of points the special effect accumulated
 */
int Block::doEffect(vector<vector<Block*> >& blockField, int x, int y) {
    return 0;
}

/*
 * Allocates a clone of this Block, including it's uniqueID. Should be overridden by Block
 *   subclasses so that you can clone a Block of the propper class into a polymorphic Block pointer
 *   without knowing the class of the Block you are cloning.
 *   
 * Returns: The address of the newly instantiated clone of this Block
 */
Block* Block::makeNewClone() const {
    Block* tmp = new Block(*this);
    
    tmp->setUniqueID(getUniqueID());
    
    return tmp;
}

/* ---------- Implemented from Drawable ---------- */

/*
 * Draws this Block to the screen.
 */
void Block::draw() {
    g->setColor(getForeground());
    for (int i = 0; i < getSize(); i++) {
        for (int j = 0; j < getSize(); j++) {
            g->plot(getLocationX()+i, getLocationY()+j);
        }
    }
    
    isVisible = true;
}

/*
 * Erases this Block from the screen.
 */
void Block::erase() {
    if (isVisible) {
        g->setColor(getBackground());
        for (int i = 0; i < getSize(); i++) {
            for (int j = 0; j < getSize(); j++) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }

        isVisible = false;
    }
}
