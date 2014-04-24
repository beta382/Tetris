/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 30, 2014
 * Date last modified:     Apr 15, 2014
 */

#include "Shape.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a Shape object using default values.
 */
Shape::Shape():
Drawable(),
        blockSize(10), padding(0)
{
}

/*
 * Instantiates a Shape object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this Shape object's x with
 *   int y: The value to initialize this Shape object's y with
 *   int blockSize: The value to initialize this Shape object's blockSize with
 *   int padding: The value to initialize this Shape object's padding with
 *   unsigned int background: The value to initialize this Shape object's background with,
 *     defaults to Color::BLACK
 */
Shape::Shape (int x, int y, int blockSize, int padding, unsigned int background):
Drawable(x, y, 0, 0, Color::WHITE, background),
        blockSize(blockSize), padding(padding)
{
}

/*
 * Instantiates a Shape object that is a copy of the passed Shape object, except for bool
 *   isVisible, which is initialized with false.
 * 
 * Parameters:
 *   const Shape& other: A reference to the Shape object to copy from
 */
Shape::Shape(const Shape& other):
Drawable(other),
        blockSize(other.blockSize), padding(other.padding)
{
    for (int i = 0; i < other.numBlocks(); i++) {
        if (other.blocks.at(i)) {
            addBlock(other.blocks.at(i)->makeNewClone());
        }
    }
}

/*
 * Destructs this Shape object.
 */
Shape::~Shape() {
    erase();
    for (unsigned int i = 0; i < blocks.size(); i++) {
        delete blocks[i];
    }
}


/* ---------- Public ---------- */

/*
 * Assigns this Shape object the values of the passed Shape object, except for bool isVisible,
 *   which is assigned false.
 * 
 * Parameters:
 *   const Shape& rhs: A reference to the Shape object to assign from
 * 
 * Returns: A reference to this Shape object
 */
Shape& Shape::operator =(const Shape& rhs) {
    if (this != &rhs) {
        erase();
        
        for (unsigned int i = 0; i < blocks.size(); i++) {
            delete blocks[i];
        }
        
        blocks.clear();
        
        Drawable::operator =(rhs);
        blockSize = rhs.blockSize;
        padding = rhs.padding;
        
        for (int i = 0; i < rhs.numBlocks(); i++) {
            if (rhs.blocks.at(i)) {
                addBlock(rhs.blocks.at(i)->makeNewClone());
            }
        }
        
        draw();
    }
    
    return *this;
}

/*
 * Getter for the Block pointer at the passed index of this Shape.
 * 
 * Parameters:
 *   int index: The index of the Block pointer to get
 *   
 * Returns: A the Block pointer at the specified index
 */
Block* Shape::getBlock(int index) const {
    return blocks.at(index);
}

/*
 * Adds a Block pointer to this Shape.
 * 
 * Parameters:
 *   Block* block: The Block pointer to add to this Shape
 *   
 * Returns: A reference to this Shape object
 */
Shape& Shape::addBlock(Block* block) {
    blocks.push_back(block);
    
    return *this;
}

/*
 * Getter for the number of Block pointers in this Shape.
 * 
 * Returns: The number of Block pointers in this Shape
 */
int Shape::numBlocks() const {
    return blocks.size();
}

/*
 * Getter for blockSize.
 * 
 * Returns: The value of this Shape object's blockSize
 */
int Shape::getBlockSize() const {
    return blockSize;
}

/*
 * Getter for padding.
 * 
 * Returns: The value of this Shape object's padding
 */
int Shape::getPadding() const {
    return padding;
}

/*
 * Getter for the sum of blockSize and padding.
 * 
 * Returns: The value of this Shape object's blockSize+padding
 */
int Shape::getTotalBlockSize() const {
    return getBlockSize()+getPadding();
}

/*
 * Shifts all the Blocks in this Shape up one totalBlockSize.
 */
void Shape::shiftUp () {
    setLocation(getLocationX(), getLocationY()+getTotalBlockSize());
}

/*
 * Shifts all the Blocks in this Shape down one totalBlockSize.
 */
void Shape::shiftDown () {
    setLocation(getLocationX(), getLocationY()-getTotalBlockSize());
}

/*
 * Shifts all the Blocks in this Shape left one totalBlockSize.
 */
void Shape::shiftLeft () {
    setLocation(getLocationX()-getTotalBlockSize(), getLocationY());
}

/*
 * Shifts all the Blocks in this Shape right one totalBlockSize.
 */
void Shape::shiftRight () {
    setLocation(getLocationX()+getTotalBlockSize(), getLocationY());
}

/*
 * Accesses the Block pointer at the specified index and returns a reference to the pointer.
 * 
 * Parameters:
 *   int index: The index of the Block pointer to return a reference to
 *   
 * Returns: A reference to the requested Block pointer
 */
Block*& Shape::operator [](int index) {
    return blocks[index];
}

/* ---------- Overriding from Drawable ---------- */

/*
 * Assigns x and y the values of the passed parameters, and properly offsets all Drawable member
 *   data to reflect the shift
 * 
 * Parameters:
 *   int x: The value to assign to this Shape object's x
 *   int y: The value to assign to this Shape object's y
 */
void Shape::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    for (unsigned int i = 0; i < blocks.size(); i++) {
        if (blocks[i]) {
            blocks[i]->setLocation(blocks[i]->getLocationX()+dX, blocks[i]->getLocationY()+dY);
        }
    }
    
    this->x = x;
    this->y = y;
}

/*
 * Assigns foreground the value of the passed parameter, and applies the same foreground color to 
 *   all Drawable member data.
 *  
 * Parameters:
 *   unsigned int foreground: The value to assign to this Shape object's foreground
 */
void Shape::setForeground (unsigned int foreground) {
    for (unsigned int i = 0; i < blocks.size(); i++){
        if (blocks[i]) {
            blocks[i]->setForeground(foreground);
        }
    }
    
    this->foreground = foreground;
}

/*
 * Assigns background the value of the passed parameter, and applies the same background color to 
 *   all Drawable member data.
 *  
 * Parameters:
 *   unsigned int background: The value to assign to this Shape object's background
 */
void Shape::setBackground(unsigned int background) {
    for (unsigned int i = 0; i < blocks.size(); i++){
        if (blocks[i]) {
            if (blocks[i]) {
                blocks[i]->setBackground(background);
            }
        }
    }
    
    this->background = background;
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Getter for width.
 * 
 * Returns: The value of this Shape object's width
 */
int Shape::getWidth() const {
    int val = 0;
    
    if (width != 0) {
        val = width*(blockSize+padding) - padding;
    } else {
        int min;
        int max;
        
        for (int i = 0; i < numBlocks(); i++) {
            if (blocks[i]) {
                if (i == 0) {
                    min = blocks[i]->getLocationX();
                    max = min;
                } else if (blocks[i]->getLocationX() < min) {
                    min = blocks[i]->getLocationX();
                } else if (blocks[i]->getLocationX() > max) {
                    min = blocks[i]->getLocationX();
                }
            }
        }
        
        val = max-min + blockSize;
    }
    
    return val;
}

/*
 * Getter for height.
 * 
 * Returns: The value of this Shape object's height
 */
int Shape::getHeight() const {
    int val = 0;
    
    if (height != 0) {
        val = height*(blockSize+padding) - padding;
    } else {
        int min;
        int max;
        
        for (int i = 0; i < numBlocks(); i++) {
            if (blocks[i]) {
                if (i == 0) {
                    min = blocks[i]->getLocationY();
                    max = min;
                } else if (blocks[i]->getLocationY() < min) {
                    min = blocks[i]->getLocationY();
                } else if (blocks[i]->getLocationY() > max) {
                    min = blocks[i]->getLocationY();
                }
            }
        }
        
        val = max-min + blockSize;
    }
    
    return val;
}

/*
 * Draws all Drawable member data to the screen.
 */
void Shape::draw() {
    for (unsigned int i = 0; i < blocks.size(); i++) {
        if (blocks[i]) {
            blocks[i]->draw();
        }
    }
    
    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen.
 */
void Shape::erase() {
    if (isVisible) {
        for (unsigned int i = 0; i < blocks.size(); i++) {
            if (blocks[i]) {
                blocks[i]->erase();
            }
        }
        
        isVisible = false;
    }
}


/* ---------- Non-member ---------- */

/*
 * Compares the two Shapes pointed to by the passed pointers, determining which is greater than the
 *   other based on which one has a greater y-coordinate, or, if their y-coordinates are the same,
 *   which has a greater x-coordinate. Returns a result logically equivalent to "lhs < rhs".
 *   
 * Parameters:
 *   const Shape* lhs: A pointer to a Shape object on the left-hand-side of this comparison
 *   const Shape* rhs: A pointer to a Shape object on the left-hand-side of this comparison
 *   
 * Returns: True if lhs is less than rhs, false otherwise
 */
bool compareShapePointerByLocation(const Shape* lhs, const Shape* rhs) {
    bool result = false;
    
    if (lhs->getLocationY() < rhs->getLocationY() || 
            (lhs->getLocationY() == rhs->getLocationY() && 
             lhs->getLocationX() < rhs->getLocationX()))
    {
        result = true;
    }
    
    return result;
}
