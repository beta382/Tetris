/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr  4, 2014
 * Date last modified:     Apr 26, 2014
 */

#include "TetrominoBase.h"

/*
 * A shared unsigned int for all instances of objects that descend from TetrominoBase. Represents
 *   a unique identifier for each TetrominoBase object, which is passed down to all Blocks the 
 *   TetrominoBase object contains. Thus, each TetrominoBase's Blocks will be able to tell if
 *   another Block is from the same Tetromino.
 */
unsigned int TetrominoBase::uniqueID = 1; // Reserve 0 as a "no-ID"


/* ---------- Protected Constructors/Destructor ---------- */

/*
 * Instantiates a TetrominoBase object using default values.
 */
TetrominoBase::TetrominoBase():
Shape(),
        offsetX(0), offsetY(0), realWidth(0), realHeight(0)
{
}

/*
 * Instantiates a TetrominoBase object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this TetrominoBase object's x with
 *   int y: The value to initialize this TetrominoBase object's y with
 *   int blockSize: The value to initialize this TetrominoBase object's blockSize with
 *   int padding: The value to initialize this TetrominoBase object's padding with
 *   unsigned int background: The value to initialize this TetrominoBase object's background with,
 *     defaults to Color::BLACK
 */
TetrominoBase::TetrominoBase (int x, int y, int blockSize, int padding, unsigned int background):
Shape(x, y, blockSize, padding, background),
        offsetX(0), offsetY(0), realWidth(0), realHeight(0)
{
}

/*
 * Instantiates a TetrominoBase object that is a copy of the passed TetrominoBase object, except
 *   for bool isVisible, which is initialized with false.
 * 
 * Parameters:
 *   const TetrominoBase& other: A reference to the TetrominoBase object to copy from
 */
TetrominoBase::TetrominoBase(const TetrominoBase& other):
Shape(other),
        offsetX(other.offsetX), offsetY(other.offsetY), realWidth(other.realWidth),
        realHeight(other.realHeight)
{
}


/* ---------- Public ---------- */

/*
 * Rotates this TetrominoBase clockwise, setting the locations of it's Blocks accordingly
 */
void TetrominoBase::rotateCW() {
    for (unsigned int i = 0; i < blocks.size(); i++) {
        blocks[i]->setLocation(
            ((blocks[i]->getLocationY()-getLocationY())/blocks[i]->getTotalSize()-offsetY-offsetX)
                *blocks[i]->getTotalSize()+getLocationX(),
            (width-((blocks[i]->getLocationX()-getLocationX())/blocks[i]->getTotalSize()+offsetX)-1
                +offsetY)*blocks[i]->getTotalSize()+getLocationY()
        );
    }
    
    swap(width, height);
    swap(realWidth, realHeight);
}

/*
 * Rotates this TetrominoBase clockwise, setting the locations of it's Blocks accordingly.
 */
void TetrominoBase::rotateCCW() {
    for (unsigned int i = 0; i < blocks.size(); i++) {
        blocks[i]->setLocation(
            (height-((blocks[i]->getLocationY()-getLocationY())/blocks[i]->getTotalSize()-offsetY)
                -1-offsetX)*blocks[i]->getTotalSize()+getLocationX(),
            ((blocks[i]->getLocationX()-getLocationX())/blocks[i]->getTotalSize()+offsetX+offsetY)
                *blocks[i]->getTotalSize()+getLocationY()
        );
    }
    
    swap(width, height);
    swap(realWidth, realHeight);
}

int TetrominoBase::getRealWidth() const {
    return realWidth*getTotalBlockSize()-getPadding();
}

int TetrominoBase::getRealHeight() const {
    return realHeight*getTotalBlockSize()-getPadding();
}

/* ---------- Protected ---------- */

/*
 * Assigns this TetrominoBase object the values of the passed TetrominoBase object, except for bool
 *   isVisible, which is assigned false.
 * 
 * Parameters:
 *   const TetrominoBase& rhs: A reference to the TetrominoBase object to assign from
 * 
 * Returns: A reference to this TetrominoBase object
 */
TetrominoBase& TetrominoBase::operator =(const TetrominoBase& rhs) {
    if (this != &rhs) {
        Shape::operator =(rhs);
        offsetX = rhs.offsetX;
        offsetY = rhs.offsetY;
    }
    
    return *this;
}
