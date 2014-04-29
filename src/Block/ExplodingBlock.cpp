/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 23, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "ExplodingBlock.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a ExplodingBlock object using default values.
 */
ExplodingBlock::ExplodingBlock():
Block()
{
}

/*
 * Instantiates a ExplodingBlock object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this ExplodingBlock object's x with
 *   int y: The value to initialize this ExplodingBlock object's y with
 *   int width: The value to initialize this ExplodingBlock object's size with
 *   int padding: The value to initialize this ExplodingBlock object's padding with
 *   unsigned int foreground: The value to initialize this ExplodingBlock object's foreground with,
 *     defaults to Color::WHITE
 *   unsigned int background: The value to initialize this ExplodingBlock object's background with,
 *     defaults to Color::BLACK
 */
ExplodingBlock::ExplodingBlock(int x, int y, int size, int padding, unsigned int foreground,
        unsigned int background):
Block(x, y, size, padding, foreground, background)
{
}

/*
 * Instantiates a ExplodingBlock object that is a copy of the passed ExplodingBlock object, except
 *   for bool isVisible, which is initialized with false, and unsigned int uniqueID, which is
 *   initialized with 0.
 * 
 * Parameters:
 *   const ExplodingBlock& other: A reference to the ExplodingBlock object to copy from
 */
ExplodingBlock::ExplodingBlock(const ExplodingBlock& other):
Block(other)
{
}

/*
 * Destructs this ExplodingBlock object.
 */
ExplodingBlock::~ExplodingBlock() {
    erase();
}


/* ---------- Public ---------- */

/*
 * Assigns this ExplodingBlock object the values of the passed ExplodingBlock object, except for
 *   bool isVisible, which is assigned false, and unsigned int uniqueID, which is assigned 0.
 * 
 * Parameters:
 *   const ExplodingBlock& rhs: A reference to the ExplodingBlock object to assign from
 * 
 * Returns: A reference to this ExplodingBlock object
 */
ExplodingBlock& ExplodingBlock::operator =(const ExplodingBlock& rhs) {
    if (this != &rhs) {
        Block::operator =(rhs);
    }
    
    return *this;
}


/* ---------- Overriding from Block ---------- */

/*
 * Performs this ExplodingBlock's special effect on the given blockField from the passed
 *   coordinates. Should be called when this ExplodingBlock is cleared from the PlayingField.
 *   
 * Parameters:
 *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the effect on
 *   int x: The x-coordinate of this ExplodingBlock within the blockField
 *   int y: The y-coordinate of this ExplodingBlock within the blockField
 *   
 * Returns: The number of points the special effect accumulated
 */
int ExplodingBlock::doEffect(vector<vector<Block*> >& blockField, int x, int y) {
    int points = 100;
    
    // Make an explosion rectangle
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
    
    // Normalize blocks in case this got called from another block's effect
    for (unsigned int i = 0; i < blockField.size(); i++) {
        for (unsigned int j = 0; j < blockField[i].size(); j++) {
            if (blockField[i][j] && blockField[i][j]->getUniqueID() == getUniqueID()) {
                Block* tmp = blockField[i][j];
                
                // Not making a clone, this will give us a base Block
                blockField[i][j] = new Block(*tmp);
                delete tmp;
                blockField[i][j]->draw();
            }
        }
    }
    
    // Actually clear the blocks
    for (int i = x-2; i <= x+2; i++) {
        for (int j = y-2; j <= y+2; j++) {
            if (i >= 0 && i < static_cast<int>(blockField.size()) &&
                j >= 0 && j < static_cast<int>(blockField[i].size()) && blockField[i][j])
            {
                Block* tmp = blockField[i][j];
                blockField[i][j] = NULL;
                
                if (tmp->getUniqueID() != getUniqueID()) {
                    points += tmp->doEffect(blockField, i, j);
                }
                
                delete tmp;
            }
        }
    }
    
    return points;
}

/*
 * Allocates a clone of this ExplodingBlock, including it's uniqueID.
 *   
 * Returns: The address of the newly instantiated clone of this ExplodingBlock
 */
ExplodingBlock* ExplodingBlock::makeNewClone() const {
    ExplodingBlock* tmp = new ExplodingBlock(*this);
    
    tmp->setUniqueID(getUniqueID());
    
    return tmp;
}

/*
 * Draws this ExplodingBlock to the screen.
 */
void ExplodingBlock::draw() {
    g->setColor(getForeground());
    
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            
            // Outline
            if (i == 0 || i == getWidth()-1 || j == 0 || j == getHeight()-1) {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
            
            // Inner box #1
            if ((i >= (2*getWidth())/8 && i < (6*getWidth())/8) &&
                    (j >= (2*getHeight())/8 && j < (6*getHeight())/8))
            {
                g->plot(getLocationX()+i, getLocationY()+j);
            }
        }
    }
    
    isVisible = true;
}
