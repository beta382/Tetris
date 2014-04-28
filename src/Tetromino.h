/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr 15, 2014
 */

#ifndef TETROMINO_H_
#define TETROMINO_H_

#include "TetrominoBase.h"
#include "util.h"

/*
 * Tetromino<BlockType>:
 *
 * Inherits from TetrominoBase.
 *
 * Tetromino<BlockType> is intended to represent a specialized Shape that contains four Blocks of
 *   the specified BlockType. Tetromino<BlockType> IS NOT intended to be inherited from.
 */

template <typename BlockType>
class Tetromino: public TetrominoBase {
_registerForLeakcheckWithID(Tetromino)
    public:
        
        /*
         * Instantiates a Tetromino<BlockType> object using default values.
         */
        Tetromino();

        /*
         * Instantiates a Tetromino<BlockType> object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this Tetromino<BlockType> object's x with
         *   int y: The value to initialize this Tetromino<BlockType> object's y with
         *   int blockSize: The value to initialize this Tetromino<BlockType> object's blockSize with
         *   int padding: The value to initialize this Tetromino<BlockType> object's padding with
         *   TetrominoShape shape: The TetrominoShape to initialize this Tetromino<BlockType> object with
         *   unsigned int background: The value to initialize this Tetromino<BlockType> object's background
         *     with, defaults to Color::BLACK
         */
        Tetromino(int x, int y, int blockSize, int padding, TetrominoShape shape,
                unsigned int background = Color::BLACK);

        /*
         * Instantiates a Tetromino<BlockType> object that is a copy of the passed Tetromino<BlockType>
         *   object, except for bool isVisible, which is initialized with false.
         * 
         * Parameters:
         *   const Tetromino<BlockType>& other: A reference to the Tetromino<BlockType> object to copy from
         */
        Tetromino(const Tetromino<BlockType>&);

        /*
         * Assigns this Tetromino<BlockType> object the values of the passed Tetromino<BlockType> object,
         *   except for bool isVisible, which is assigned false.
         * 
         * Parameters:
         *   const Tetromino<BlockType>& rhs: A reference to the Tetromino<BlockType> object to assign from
         * 
         * Returns: A reference to this Tetromino<BlockType> object
         */
        Tetromino<BlockType>& operator =(const Tetromino<BlockType>&);
        
        /* ---------- Implemented from TetrominoBase ---------- */
        
        /*
         * Allocates a clone of this Tetromino<BlockType>.
         *   
         * Returns: The address of the newly instantiated clone of this Tetromino<BlockType>
         */
        Tetromino<BlockType>* makeNewClone() const;
        
        
        // Get the shape
        TetrominoShape getShape() const;
    private:
        
        /* ---------- Implemented from TetrominoBase ---------- */

        /*
         * Initializes this Tetromino<BlockType> object with the passed TetrominoShape.
         * 
         * Parameters:
         *   TetrominoShape shape: The shape of the tetromino to model this Tetromino<BlockType> after
         */
        void initTetromino(TetrominoShape shape);
        
        
        // Private variable to store the shape
        TetrominoShape shape;
};


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a Tetromino<BlockType> object using default values.
 */
template <typename BlockType>
Tetromino<BlockType>::Tetromino():
TetrominoBase()
{
    initTetromino(S); // Picked by fair dice roll, guaranteed to be random
}

/*
 * Instantiates a Tetromino<BlockType> object using the passed parameters.
 * 
 * Parameters:
 *   int x: The value to initialize this Tetromino<BlockType> object's x with
 *   int y: The value to initialize this Tetromino<BlockType> object's y with
 *   int blockSize: The value to initialize this Tetromino<BlockType> object's blockSize with
 *   int padding: The value to initialize this Tetromino<BlockType> object's padding with
 *   TetrominoShape shape: The TetrominoShape to initialize this Tetromino<BlockType> object with
 *   unsigned int background: The value to initialize this Tetromino<BlockType> object's background
 *     with, defaults to Color::BLACK
 */
template <typename BlockType>
Tetromino<BlockType>::Tetromino (int x, int y, int blockSize, int padding, TetrominoShape shape,
        unsigned int background):
TetrominoBase(x, y, blockSize, padding, background)
{
    initTetromino(shape);
}

/*
 * Instantiates a Tetromino<BlockType> object that is a copy of the passed Tetromino<BlockType>
 *   object, except for bool isVisible, which is initialized with false.
 * 
 * Parameters:
 *   const Tetromino<BlockType>& other: A reference to the Tetromino<BlockType> object to copy from
 */
template <typename BlockType>
Tetromino<BlockType>::Tetromino(const Tetromino<BlockType>& other):
TetrominoBase(other)
{
}

/* ---------- Public ---------- */

/*
 * Assigns this Tetromino<BlockType> object the values of the passed Tetromino<BlockType> object,
 *   except for bool isVisible, which is assigned false.
 * 
 * Parameters:
 *   const Tetromino<BlockType>& rhs: A reference to the Tetromino<BlockType> object to assign from
 * 
 * Returns: A reference to this Tetromino<BlockType> object
 */
template <typename BlockType>
Tetromino<BlockType>& Tetromino<BlockType>::operator =(const Tetromino<BlockType>& rhs) {
    if (this != &rhs) {
        TetrominoBase::operator =(rhs);
    }
    
    return *this;
}


/* ---------- Publicly Implemented from TetrominoBase ---------- */

/*
 * Allocates a clone of this Tetromino<BlockType>.
 *   
 * Returns: The address of the newly instantiated clone of this Tetromino<BlockType>
 */
template <typename BlockType>
Tetromino<BlockType>* Tetromino<BlockType>::makeNewClone() const {
    return new Tetromino<BlockType>(*this);
}


template <typename BlockType>
TetrominoShape Tetromino<BlockType>::getShape() const{
    return shape;
}


/* ---------- Privately Implemented from TetrominoBase ---------- */

/*
 * Initializes this Tetromino<BlockType> object with the passed TetrominoShape.
 * 
 * Parameters:
 *   TetrominoShape shape: The shape of the tetromino to model this Tetromino<BlockType> after
 */
template <typename BlockType>
void Tetromino<BlockType>::initTetromino (TetrominoShape shape) {
    Block* block1, * block2, * block3, * block4;
    
    this->shape = shape;
    
    // Some heights/widths are "fudged", so that this fake bounding rectangle can apply desired
    // rotations.
    switch (shape) {
        case I:
            block1 = new BlockType(getLocationX(), getLocationY()+getTotalBlockSize()*4,
                    getBlockSize(), getPadding());
            block2 = new BlockType(getLocationX()+getTotalBlockSize(),
                    getLocationY()+getTotalBlockSize()*4, getBlockSize(), getPadding());
            block3 = new BlockType(getLocationX()+getTotalBlockSize()*2,
                    getLocationY()+getTotalBlockSize()*4, getBlockSize(), getPadding());
            block4 = new BlockType(getLocationX()+getTotalBlockSize()*3,
                    getLocationY()+getTotalBlockSize()*4, getBlockSize(), getPadding());
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::BLUE);
            setBackground(getBackground());
            setWidth(4);
            setHeight(5); // Fudged
            offsetY = 2;
            break;
        case O:
            block1 = new BlockType(getLocationX(), getLocationY(), getBlockSize(), getPadding());
            block2 = new BlockType(getLocationX()+getTotalBlockSize(), getLocationY(),
                    getBlockSize(), getPadding());
            block3 = new BlockType(getLocationX(), getLocationY()+getTotalBlockSize(),
                    getBlockSize(), getPadding());
            block4 = new BlockType(getLocationX()+getTotalBlockSize(),
                    getLocationY()+getTotalBlockSize(), getBlockSize(), getPadding());
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::GREEN);
            setBackground(getBackground());
            setWidth(2);
            setHeight(2);
            break;
        case T:
            block1 = new BlockType(getLocationX()+getTotalBlockSize(),
                    getLocationY()+getTotalBlockSize(), getBlockSize(), getPadding());
            block2 = new BlockType(getLocationX(), getLocationY()+getTotalBlockSize()*2,
                    getBlockSize(), getPadding());
            block3 = new BlockType(getLocationX()+getTotalBlockSize(),
                    getLocationY()+getTotalBlockSize()*2, getBlockSize(), getPadding());
            block4 = new BlockType(getLocationX()+getTotalBlockSize()*2,
                    getLocationY()+getTotalBlockSize()*2, getBlockSize(), getPadding());
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::BROWN);
            setBackground(getBackground());
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case J:
            block1 = new BlockType(getLocationX()+getTotalBlockSize()*2,
                    getLocationY()+getTotalBlockSize(), getBlockSize(), getPadding());
            block2 = new BlockType(getLocationX(), getLocationY()+getTotalBlockSize()*2,
                    getBlockSize(), getPadding());
            block3 = new BlockType(getLocationX()+getTotalBlockSize(),
                    getLocationY()+getTotalBlockSize()*2, getBlockSize(), getPadding());
            block4 = new BlockType(getLocationX()+getTotalBlockSize()*2,
                    getLocationY()+getTotalBlockSize()*2, getBlockSize(), getPadding());
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::GRAY);
            setBackground(getBackground());
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case L:
            block1 = new BlockType(getLocationX(), getLocationY()+getTotalBlockSize(),
                    getBlockSize(), getPadding());
            block2 = new BlockType(getLocationX(), getLocationY()+getTotalBlockSize()*2,
                    getBlockSize(), getPadding());
            block3 = new BlockType(getLocationX()+getTotalBlockSize(),
                    getLocationY()+getTotalBlockSize()*2, getBlockSize(), getPadding());
            block4 = new BlockType(getLocationX()+getTotalBlockSize()*2,
                    getLocationY()+getTotalBlockSize()*2, getBlockSize(), getPadding());
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::RED);
            setBackground(getBackground());
            setWidth(3);
            setHeight(3); // Fudged
            offsetY = 1;
            break;
        case S:
            block1 = new BlockType(getLocationX(), getLocationY(), getBlockSize(), getPadding());
            block2 = new BlockType(getLocationX()+getTotalBlockSize(), getLocationY(),
                    getBlockSize(), getPadding());
            block3 = new BlockType(getLocationX()+getTotalBlockSize(),
                    getLocationY()+getTotalBlockSize(), getBlockSize(), getPadding());
            block4 = new BlockType(getLocationX()+getTotalBlockSize()*2,
                    getLocationY()+getTotalBlockSize(), getBlockSize(), getPadding());
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::DARK_GREEN);
            setBackground(getBackground());
            setWidth(3);
            setHeight(2);
            break;
        case Z:
            block1 = new BlockType(getLocationX()+getTotalBlockSize(), getLocationY(),
                    getBlockSize(), getPadding());
            block2 = new BlockType(getLocationX()+getTotalBlockSize()*2, getLocationY(),
                    getBlockSize(), getPadding());
            block3 = new BlockType(getLocationX(), getLocationY()+getTotalBlockSize(),
                    getBlockSize(), getPadding());
            block4 = new BlockType(getLocationX()+getTotalBlockSize(),
                    getLocationY()+getTotalBlockSize(), getBlockSize(), getPadding());
            
            addBlock(block1).addBlock(block2).addBlock(block3).addBlock(block4);
            
            setForeground(Color::CYAN);
            setBackground(getBackground());
            setWidth(3);
            setHeight(2);
            break;
    }
    
    for (int i = 0; i < numBlocks(); i++) {
        blocks[i]->setUniqueID(uniqueID);
    }
    
    uniqueID++;
}

#endif /* TETROMINO_H_ */
