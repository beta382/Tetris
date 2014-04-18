/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  5, 2014
 * Date last modified:     Apr 15, 2014
 */

#ifndef TETROMINOBASE_H_
#define TETROMINOBASE_H_

#include "Shape.h"

/*
 * TetrominoShape:
 *
 * Enumeration of all possible shapes a TetrominoBase may take.
 */
enum TetrominoShape  {I, O, T, J, L, S, Z};

/*
 * TetrominoBase:
 *
 * Inherits from Shape.
 *
 * TetrominoBase is intended to be the abstract base class for all possible Tetromino<BlockType>
 *   classes. You MAY NOT independantly instantiate a TetrominoBase object, this is enforced by
 *   making the constructors protected.
 */
class TetrominoBase: public Shape {
    public:
    
        void* operator new(size_t size) {
            void* mem = malloc(size);
            cout << left << setw(35) << "Allocated TetrominoBase at" << mem << endl;
            leakcheck::n_new++;
            return mem;
        }
    
        void operator delete(void* mem) {
            cout << left << setw(35) << "De-allocated TetrominoBase at" << mem << endl;
            leakcheck::n_delete++;
            free(mem);
        }

        /*
         * Rotates this TetrominoBase clockwise, setting the locations of it's Blocks accordingly
         */
        void rotateCW();

        /*
         * Rotates this TetrominoBase clockwise, setting the locations of it's Blocks accordingly.
         */
        void rotateCCW();


        /*
         * Getter for offsetX.
         * 
         * Returns:  The value of this TetrominoBase object's offsetX
         */
        int getOffsetX() const;

        /*
         * Getter for offsettY.
         * 
         * Returns:  The value of this TetrominoBase object's offsetY
         */
        int getOffsetY() const;
    protected:

        /*
         * Instantiates a TetrominoBase object using default values.
         */
        TetrominoBase();

        /*
         * Instantiates a TetrominoBase object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this TetrominoBase object's x with
         *   int y: The value to initialize this TetrominoBase object's y with
         *   int blockSize: The value to initialize this TetrominoBase object's blockSize with
         *   int padding: The value to initialize this TetrominoBase object's padding with
         *   unsigned int background: The value to initialize this TetrominoBase object's
         *     background with, defaults to Color::BLACK
         */
        TetrominoBase(int x, int y, int blockSize, int padding,
                unsigned int background = Color::BLACK);

        /*
         * Instantiates a TetrominoBase object that is a copy of the passed TetrominoBase object,
         *   except for bool isVisible, which is initialized with false.
         * 
         * Parameters:
         *   const TetrominoBase& other: A reference to the TetrominoBase object to copy from
         */
        TetrominoBase(const TetrominoBase&);

        /*
         * Assigns this TetrominoBase object the values of the passed TetrominoBase object, except
         *   for bool isVisible, which is assigned false.
         * 
         * Parameters:
         *   const TetrominoBase& rhs: A reference to the TetrominoBase object to assign from
         * 
         * Returns: A reference to this TetrominoBase object
         */
        TetrominoBase& operator =(const TetrominoBase&);

        /*
         * Initializes this TetrominoBase object with the passed TetrominoShape. Must be
         *   implimented by children of TetrominoBase.
         * 
         * Parameters:
         *   TetrominoShape shape: The shape of the tetromino to model this Tetromino<BlockType>
         *     after
         */
        virtual void initTetromino(TetrominoShape type) = 0;
        
        /*
         * These variables are intended to represent the color of this Drawable object and the
         *   color of whatever lies behind this Drawable object, respectively.
         */
        int offsetX;
        int offsetY;
        
        /*
         * A shared unsigned int for all instances of objects that descend from TetrominoBase.
         *   Represents a unique identifier for each TetrominoBase object, which is passed down to
         *   all Blocks the TetrominoBase object contains. Thus, each TetrominoBase's Blocks will
         *   be able to tell if another Block is from the same Tetromino.
         */
        static unsigned int uniqueID;
};

#endif /* TETROMINOBASE_H_ */
