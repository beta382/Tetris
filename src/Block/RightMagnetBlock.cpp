/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "RightMagnetBlock.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a RightMagnetBlock object using default values.
 */
RightMagnetBlock::RightMagnetBlock():
Block()
{
}

/*
 * Instantiates a RightMagnetBlock object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this RightMagnetBlock object's x with
 *   int y: The value to initialize this RightMagnetBlock object's y with
 *   int width: The value to initialize this RightMagnetBlock object's size with
 *   int padding: The value to initialize this RightMagnetBlock object's padding with
 *   unsigned int foreground: The value to initialize this RightMagnetBlock object's foreground
 *     with, defaults to Color::WHITE
 *   unsigned int background: The value to initialize this RightMagnetBlock object's background
 *     with, defaults to Color::BLACK
 */
RightMagnetBlock::RightMagnetBlock(int x, int y, int size, int padding, unsigned int foreground,
        unsigned int background):
Block(x, y, size, padding, foreground, background)
{
}

/*
 * Instantiates a RightMagnetBlock object that is a copy of the passed RightMagnetBlock object,
 *   except for bool isVisible, which is initialized with false, and unsigned int uniqueID, which
 *   is initialized with 0.
 * 
 * Parameters:
 *   const RightMagnetBlock& other: A reference to the RightMagnetBlock object to copy from
 */
RightMagnetBlock::RightMagnetBlock(const RightMagnetBlock& other):
Block(other)
{
}

/*
 * Destructs this RightMagnetBlock object.
 */
RightMagnetBlock::~RightMagnetBlock() {
    erase();
}


/* ---------- Public ---------- */

/*
 * Assigns this RightMagnetBlock object the values of the passed RightMagnetBlock object, except
 *   for bool isVisible, which is assigned false, and unsigned int uniqueID, which is assigned 0.
 * 
 * Parameters:
 *   const RightMagnetBlock& rhs: A reference to the RightMagnetBlock object to assign from
 * 
 * Returns: A reference to this RightMagnetBlock object
 */
RightMagnetBlock& RightMagnetBlock::operator =(const RightMagnetBlock& rhs) {
    if (this != &rhs) {
        Block::operator =(rhs);
    }
    
    return *this;
}


/* ---------- Overriding from Block ---------- */

/*
 * Performs this RightMagnetBlock's special effect on the given blockField from the passed
 *   coordinates. Should be called when this RightMagnetBlock is cleared from the PlayingField.
 *   
 * Parameters:
 *   BlockField& blockField: A reference to the blockField to perform the effect on
 *   int x: The x-coordinate of this RightMagnetBlock within the blockField
 *   int y: The y-coordinate of this RightMagnetBlock within the blockField
 *   
 * Returns: The number of points the special effect accumulated
 */
int RightMagnetBlock::doEffect(BlockField& blockField, int x, int y) {
    int points = 100;
    
    bool didMagnet = true;
    while (didMagnet) {
        didMagnet = false;
        
        for (int i = 0; i < blockField.getInternalHeight(); i++) {
            for (int j = blockField.getInternalWidth()-2; j >= 0; j--) {
                if (blockField.get(j, i) && !blockField.get(j+1, i)) {
                    blockField.get(j, i)->erase();
                    blockField.at(j+1, i) = blockField.get(j, i);

                    blockField.at(j, i) = NULL;
                    
                    blockField.get(j+1, i)->setLocation(
                        blockField.get(j+1, i)->getLocationX()+blockField.get(j+1, i)->getTotalSize(), 
                        blockField.get(j+1, i)->getLocationY()
                    );
                    blockField.get(j+1, i)->draw();
                    
                    didMagnet = true;
                }
            }
        }
        
        if (didMagnet) {
            util::wait(100, g);
        }
    }
    
    return points;
}

/*
 * Allocates a clone of this RightMagnetBlock, including it's uniqueID.
 *   
 * Returns: The address of the newly instantiated clone of this RightMagnetBlock
 */
RightMagnetBlock* RightMagnetBlock::makeNewClone() const {
    RightMagnetBlock* tmp = new RightMagnetBlock(*this);
    
    tmp->setUniqueID(getUniqueID());
    
    return tmp;
}

/*
 * Draws this RightMagnetBlock to the screen.
 */
void RightMagnetBlock::draw() {
    g->setColor(getForeground());
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            
            // Outline
            if (i == 0 || i == getWidth()-1 || j == 0 || j == getHeight()-1) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Arrow head
            if ((i >= (5*getWidth())/8) && 
                    (j > i - getHeight()/2 && j < -i + (3*getHeight())/2-1))
            {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Arrow tail
            if ((i < (5*getWidth())/8) && 
                    (j >= (3*getHeight())/8 && j < (5*getHeight())/8))
            {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }
    }
    
    isVisible = true;
}
