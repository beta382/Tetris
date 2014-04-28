/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "LeftMagnetBlock.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a LeftMagnetBlock object using default values.
 */
LeftMagnetBlock::LeftMagnetBlock():
Block()
{
}

/*
 * Instantiates a LeftMagnetBlock object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this LeftMagnetBlock object's x with
 *   int y: The value to initialize this LeftMagnetBlock object's y with
 *   int width: The value to initialize this LeftMagnetBlock object's size with
 *   int padding: The value to initialize this LeftMagnetBlock object's padding with
 *   unsigned int foreground: The value to initialize this LeftMagnetBlock object's foreground
 *     with, defaults to Color::WHITE
 *   unsigned int background: The value to initialize this LeftMagnetBlock object's background
 *     with, defaults to Color::BLACK
 */
LeftMagnetBlock::LeftMagnetBlock(int x, int y, int size, int padding, unsigned int foreground,
        unsigned int background):
Block(x, y, size, padding, foreground, background)
{
}

/*
 * Instantiates a LeftMagnetBlock object that is a copy of the passed LeftMagnetBlock object,
 *   except for bool isVisible, which is initialized with false, and unsigned int uniqueID, which
 *   is initialized with 0.
 * 
 * Parameters:
 *   const LeftMagnetBlock& other: A reference to the LeftMagnetBlock object to copy from
 */
LeftMagnetBlock::LeftMagnetBlock(const LeftMagnetBlock& other):
Block(other)
{
}

/*
 * Destructs this LeftMagnetBlock object.
 */
LeftMagnetBlock::~LeftMagnetBlock() {
    erase();
}


/* ---------- Public ---------- */

/*
 * Assigns this LeftMagnetBlock object the values of the passed LeftMagnetBlock object, except
 *   for bool isVisible, which is assigned false, and unsigned int uniqueID, which is assigned 0.
 * 
 * Parameters:
 *   const LeftMagnetBlock& rhs: A reference to the LeftMagnetBlock object to assign from
 * 
 * Returns: A reference to this LeftMagnetBlock object
 */
LeftMagnetBlock& LeftMagnetBlock::operator =(const LeftMagnetBlock& rhs) {
    if (this != &rhs) {
        Block::operator =(rhs);
    }
    
    return *this;
}


/* ---------- Overriding from Block ---------- */

/*
 * Performs this LeftMagnetBlock's special effect on the given blockField from the passed
 *   coordinates. Should be called when this LeftMagnetBlock is cleared from the PlayingField.
 *   
 * Parameters:
 *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the effect on
 *   int x: The x-coordinate of this LeftMagnetBlock within the blockField
 *   int y: The y-coordinate of this LeftMagnetBlock within the blockField
 *   
 * Returns: The number of points the special effect accumulated
 */
int LeftMagnetBlock::doEffect(vector<vector<Block*> >& blockField, int x, int y) {
    int points = 100;
    
    bool didMagnet = true;
    while (didMagnet) {
        didMagnet = false;
        
        for (unsigned int i = 0; i < blockField[0].size(); i++) {
            for (unsigned int j = 1; j < blockField.size(); j++) {
                if (blockField[j][i] && !blockField[j-1][i]) {
                    blockField[j][i]->erase();
                    blockField[j-1][i] = blockField[j][i];

                    blockField[j][i] = NULL;
                    
                    blockField[j-1][i]->setLocation(
                        blockField[j-1][i]->getLocationX()-blockField[j-1][i]->getTotalSize(), 
                        blockField[j-1][i]->getLocationY()
                    );
                    blockField[j-1][i]->draw();
                    
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
 * Allocates a clone of this LeftMagnetBlock, including it's uniqueID.
 *   
 * Returns: The address of the newly instantiated clone of this LeftMagnetBlock
 */
LeftMagnetBlock* LeftMagnetBlock::makeNewClone() const {
    LeftMagnetBlock* tmp = new LeftMagnetBlock(*this);
    
    tmp->setUniqueID(getUniqueID());
    
    return tmp;
}

/*
 * Draws this LeftMagnetBlock to the screen.
 */
void LeftMagnetBlock::draw() {
    g->setColor(getForeground());
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            
            // Outline
            if (i == 0 || i == getWidth()-1 || j == 0 || j == getHeight()-1) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Arrow head
            if ((i < (3*getWidth())/8) && 
                    (j >= -i + getHeight()/2 && j < i + getHeight()/2))
            {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Arrow tail
            if ((i >= (3*getWidth())/8) && 
                    (j >= (3*getHeight())/8 && j < (5*getHeight())/8))
            {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }
    }
    
    isVisible = true;
}
