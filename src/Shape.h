/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 30, 2014
 * Date last modified:     Apr 15, 2014
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Drawable.h"
#include "Block.h"

#include <vector>

/*
 * Shape:
 *
 * Inherits from Drawable.
 *
 * Shape is intended to represent and be a wrapper for a collection of Blocks, and provide methods
 *   for interfacing with and manipulating the Blocks. Shape IS intended to be inherited from.
 */
class Shape: public Drawable {
    public:

        /*
         * Instantiates a Shape object using default values.
         */
        Shape();

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
        Shape(int x, int y, int blockSize, int padding, unsigned int background = Color::BLACK);

        /*
         * Instantiates a Shape object that is a copy of the passed Shape object, except for bool
         *   isVisible, which is initialized with false.
         * 
         * Parameters:
         *   const Shape& other: A reference to the Shape object to copy from
         */
        Shape(const Shape&);

        /*
         * Destructs this Shape object.
         */
        ~Shape();

        /*
         * Assigns this Shape object the values of the passed Shape object, except for bool
         *   isVisible, which is assigned false.
         * 
         * Parameters:
         *   const Shape& rhs: A reference to the Shape object to assign from
         * 
         * Returns: A reference to this Shape object
         */
        Shape& operator =(const Shape&);


        /*
         * Getter for the Block pointer at the passed index of this Shape.
         * 
         * Parameters:
         *   int index: The index of the Block pointer to get
         *   
         * Returns: A the Block pointer at the specified index
         */
        Block* getBlock(int) const;

        /*
         * Adds a Block pointer to this Shape.
         * 
         * Parameters:
         *   Block* block: The Block pointer to add to this Shape
         *   
         * Returns: A reference to this Shape object
         */
        Shape& addBlock(Block*);

        /*
         * Getter for the number of Block pointers in this Shape.
         * 
         * Returns: The number of Block pointers in this Shape
         */
        int numBlocks() const;


        /*
         * Getter for blockSize.
         * 
         * Returns: The value of this Shape object's blockSize
         */
        int getBlockSize() const;

        /*
         * Getter for padding.
         * 
         * Returns: The value of this Shape object's padding
         */
        int getPadding() const;

        /*
         * Getter for the sum of blockSize and padding.
         * 
         * Returns: The value of this Shape object's blockSize+padding
         */
        int getTotalBlockSize() const;


        /*
         * Shifts all the Blocks in this Shape up one totalBlockSize.
         */
        void shiftUp();

        /*
         * Shifts all the Blocks in this Shape down one totalBlockSize.
         */
        void shiftDown();

        /*
         * Shifts all the Blocks in this Shape left one totalBlockSize.
         */
        void shiftLeft();

        /*
         * Shifts all the Blocks in this Shape right one totalBlockSize.
         */
        void shiftRight();


        /*
         * Accesses the Block pointer at the specified index and returns a reference to the
         *   pointer.
         * 
         * Parameters:
         *   int index: The index of the Block pointer to return a reference to
         *   
         * Returns: A reference to the requested Block pointer
         */
        Block*& operator [](int);
        
        /* ---------- Overriding from Drawable ---------- */

        /*
         * Assigns x and y the values of the passed parameters, and properly offsets all Drawable
         *   member data to reflect the shift
         * 
         * Parameters:
         *   int x: The value to assign to this Shape object's x
         *   int y: The value to assign to this Shape object's y
         */
        void setLocation(int, int);

        /*
         * Assigns foreground the value of the passed parameter, and applies the same foreground
         *   color to all Drawable member data.
         *  
         * Parameters:
         *   unsigned int foreground: The value to assign to this Shape object's foreground
         */
        void setForeground (unsigned int);

        /*
         * Assigns background the value of the passed parameter, and applies the same background
         *   color to all Drawable member data.
         *  
         * Parameters:
         *   unsigned int background: The value to assign to this Shape object's background
         */
        void setBackground (unsigned int);
        
        /* ---------- Implemented from Drawable ---------- */
        
        /*
         * Getter for width.
         * 
         * Returns: The value of this Shape object's width
         */
        int getWidth() const;
        
        /*
         * Getter for height.
         * 
         * Returns: The value of this Shape object's height
         */
        int getHeight() const;
        
        /*
         * Draws all Drawable member data to the screen.
         */
        void draw();
        
        /*
         * Erases all Drawable member data from the screen.
         */
        void erase();
    protected:
        
        /*
         * Represents the Blocks that this Shape contains
         */
        vector<Block*> blocks;
        
        /*
         * These variables represent the size in pixels of the blocks this Shape contains and the
         *   padding in pixels between blocks
         */
        int blockSize;
        int padding;
};

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
bool compareShapePointerByLocation(const Shape* lhs, const Shape* rhs);

#endif /* SHAPE_H_ */
