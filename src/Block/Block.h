/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Mar 27, 2014
 * Date last modified:     Apr 26, 2014
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "../Drawable.h"
//#include "../Shape/BlockField.h"
class BlockField;

/*
 * Block:
 *
 * Inherits from Drawable.
 *
 * Block is intended to represent a single block, and define behaviors specific to that block.
 *   Block IS intended to be inherited from.
 */
class Block: public Drawable {
_registerForLeakcheckWithID(Block)
    public:

        /*
         * Instantiates a Block object using default values.
         */
        Block();

        /*
         * Instantiates a Block object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this Block object's x with
         *   int y: The value to initialize this Block object's y with
         *   int width: The value to initialize this Block object's size with
         *   int padding: The value to initialize this Block object's padding with
         *   unsigned int foreground: The value to initialize this Block object's foreground with,
         *     defaults to Color::WHITE
         *   unsigned int background: The value to initialize this Block object's background with,
         *     defaults to Color::BLACK
         */
        Block(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);

        /*
         * Instantiates a Block object that is a copy of the passed Block object, except for bool
         *   isVisible, which is initialized with false, and unsigned int uniqueID, which is
         *   initialized with 0.
         * 
         * Parameters:
         *   const Block& other: A reference to the Block object to copy from
         */
        Block(const Block&);

        /*
         * Destructs this Block object.
         */
        ~Block();
        
        /*
         * Assigns this Block object the values of the passed Block object, except for bool
         *   isVisible, which is assigned false, and unsigned int uniqueID, which is assigned 0.
         * 
         * Parameters:
         *   const Block& rhs: A reference to the Block object to assign from
         * 
         * Returns: A reference to this Block object
         */
        Block& operator =(const Block&);


        /*
         * Getter for size.
         * 
         * Returns: The value of this Block object's width
         */
        int getSize() const;

        /*
         * Getter for padding.
         * 
         * Returns: The value of this Block object's padding
         */
        int getPadding() const;

        /*
         * Getter for the sum of blockSize and padding.
         * 
         * Returns: The value of this Block object's width+padding
         */
        int getTotalSize() const;


        /*
         * Getter for uniqueID.
         * 
         * Returns: The value of this Block object's uniqueID
         */
        unsigned int getUniqueID() const;

        /*
         * Assigns uniqueID the value of the passed parameter.
         *  
         * Parameters:
         *   unsigned int id: The value to assign to this Block object's uniqueID
         */
        void setUniqueID(unsigned int);


        /*
         * Performs this Block's special effect on the given blockField from the passed
         *   coordinates. Should be called when this Block is cleared from the PlayingField.
         *   
         * Parameters:
         *   BlockField& blockField: A reference to the blockField to perform the
         *     effect on
         *   int x: The x-coordinate of this Block within the blockField
         *   int y: The y-coordinate of this Block within the blockField
         *   
         * Returns: The number of points the special effect accumulated
         */
        virtual int doEffect(BlockField&, int x, int y);

        /*
         * Allocates a clone of this Block, including it's uniqueID. Should be overridden by Block
         *   subclasses so that you can clone a Block of the propper class into a polymorphic Block
         *   pointer without knowing the class of the Block you are cloning.
         *   
         * Returns: The address of the newly instantiated clone of this Block
         */
        virtual Block* makeNewClone() const;
        
        /* ---------- Implemented from Drawable ---------- */

        /*
         * Draws this Block to the screen.
         */
        void draw();

        /*
         * Erases this Block from the screen.
         */
        void erase();
    protected:
        
        /*
         * This variable represents the padding in pixels between this Block and an adjacent Block
         */
        int padding;
        
        /*
         * This variable represents a unique identifier that each Block will have. Blocks from the
         *   same TetrominoBase should have the same uniqueID. 
         */
        unsigned int uniqueID;
};

#endif /* BLOCK_H_ */
