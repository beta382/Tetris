/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr 26, 2014
 */

#ifndef TETROMINO_H_
#define TETROMINO_H_

#include "TetrominoBase.h"

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
         *   int blockSize: The value to initialize this Tetromino<BlockType> object's blockSize
         *     with
         *   int padding: The value to initialize this Tetromino<BlockType> object's padding with
         *   TetrominoShape shape: The TetrominoShape to initialize this Tetromino<BlockType>
         *     object with
         *   unsigned int background: The value to initialize this Tetromino<BlockType> object's
         *     background with, defaults to Color::BLACK
         */
        Tetromino(int x, int y, int blockSize, int padding, TetrominoShape shape,
                unsigned int background = Color::BLACK);

        /*
         * Instantiates a Tetromino<BlockType> object that is a copy of the passed
         *   Tetromino<BlockType> object, except for bool isVisible, which is initialized with
         *   false.
         * 
         * Parameters:
         *   const Tetromino<BlockType>& other: A reference to the Tetromino<BlockType> object to
         *     copy from
         */
        Tetromino(const Tetromino<BlockType>&);

        /*
         * Assigns this Tetromino<BlockType> object the values of the passed Tetromino<BlockType>
         *   object, except for bool isVisible, which is assigned false.
         * 
         * Parameters:
         *   const Tetromino<BlockType>& rhs: A reference to the Tetromino<BlockType> object to
         *     assign from
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
    private:
        
        /* ---------- Implemented from TetrominoBase ---------- */

        /*
         * Initializes this Tetromino<BlockType>.
         */
        void initTetromino();
};


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a Tetromino<BlockType> object using default values.
 */
template <typename BlockType>
Tetromino<BlockType>::Tetromino():
TetrominoBase()
{
    initTetromino(); // Picked by fair dice roll, guaranteed to be random
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
TetrominoBase(x, y, blockSize, padding, shape, background)
{
    initTetromino();
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


/* ---------- Privately Implemented from TetrominoBase ---------- */

/*
 * Initializes this Tetromino<BlockType> object with the passed TetrominoShape.
 */
template <typename BlockType>
void Tetromino<BlockType>::initTetromino () {
    
    // Some heights/widths are "fudged", so that this fake bounding rectangle can apply desired
    // rotations.
    switch (shape) {
        case I:
            addBlock<BlockType>(0, 4).addBlock<BlockType>(1, 4).
                addBlock<BlockType>(2, 4).addBlock<BlockType>(3, 4);
            
            setForeground(Color::BLUE);
            setBackground(getBackground());
            setWidth(4);
            setHeight(5); // Fudged
            realWidth = 4;
            realHeight = 1;
            offsetY = 2;
            break;
        case O:
            addBlock<BlockType>(0, 0).addBlock<BlockType>(0, 1).
                addBlock<BlockType>(1, 0).addBlock<BlockType>(1, 1);
            
            setForeground(Color::GREEN);
            setBackground(getBackground());
            setWidth(2);
            setHeight(2);
            realWidth = 2;
            realHeight = 2;
            break;
        case T:
            addBlock<BlockType>(1, 1).addBlock<BlockType>(0, 2).
                addBlock<BlockType>(1, 2).addBlock<BlockType>(2, 2);
            
            setForeground(Color::BROWN);
            setBackground(getBackground());
            setWidth(3);
            setHeight(3); // Fudged
            realWidth = 3;
            realHeight = 2;
            offsetY = 1;
            break;
        case J:
            addBlock<BlockType>(2, 1).addBlock<BlockType>(0, 2).
                addBlock<BlockType>(1, 2).addBlock<BlockType>(2, 2);
            
            setForeground(Color::GRAY);
            setBackground(getBackground());
            setWidth(3);
            setHeight(3); // Fudged
            realWidth = 3;
            realHeight = 2;
            offsetY = 1;
            break;
        case L:
            addBlock<BlockType>(0, 1).addBlock<BlockType>(0, 2).
                addBlock<BlockType>(1, 2).addBlock<BlockType>(2, 2);
            
            setForeground(Color::RED);
            setBackground(getBackground());
            setWidth(3);
            setHeight(3); // Fudged
            realWidth = 3;
            realHeight = 2;
            offsetY = 1;
            break;
        case S:
            addBlock<BlockType>(0, 0).addBlock<BlockType>(1, 0).
                addBlock<BlockType>(1, 1).addBlock<BlockType>(2, 1);
            
            setForeground(Color::DARK_GREEN);
            setBackground(getBackground());
            setWidth(3);
            setHeight(2);
            realWidth = 3;
            realHeight = 2;
            break;
        case Z:
            addBlock<BlockType>(1, 0).addBlock<BlockType>(2, 0).
                addBlock<BlockType>(0, 1).addBlock<BlockType>(1, 1);
            
            setForeground(Color::CYAN);
            setBackground(getBackground());
            setWidth(3);
            setHeight(2);
            realWidth = 3;
            realHeight = 2;
            break;
    }
    
    for (int i = 0; i < numBlocks(); i++) {
        blocks[i]->setUniqueID(uniqueID);
    }
    
    uniqueID++;
}

#endif /* TETROMINO_H_ */
