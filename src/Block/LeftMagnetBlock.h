/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#ifndef LEFTMAGNETBLOCK_H_
#define LEFTMAGNETBLOCK_H_

#include "Block.h"
#include "../Shape/BlockField.h"

/*
 * LeftMagnetBlock:
 *
 * Inherits from Block.
 *
 * LeftMagnetBlock is intended to represent a Block that causes all blocks to fall to the left
 *   when it is cleared. LeftMagnetBlock IS NOT intended to be inherited from.
 */
class LeftMagnetBlock: public Block {
_registerForLeakcheckWithID(LeftMagnetBlock)
    public:

        /*
         * Instantiates a LeftMagnetBlock object using default values.
         */
        LeftMagnetBlock();

        /*
         * Instantiates a LeftMagnetBlock object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this LeftMagnetBlock object's x with
         *   int y: The value to initialize this LeftMagnetBlock object's y with
         *   int width: The value to initialize this LeftMagnetBlock object's size with
         *   int padding: The value to initialize this LeftMagnetBlock object's padding with
         *   unsigned int foreground: The value to initialize this LeftMagnetBlock object's
         *     foreground with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this LeftMagnetBlock object's
         *     background with, defaults to Color::BLACK
         */
        LeftMagnetBlock(int x, int y, int size, int padding,
                unsigned int foreground = Color::WHITE, unsigned int background = Color::BLACK);

        /*
         * Instantiates a LeftMagnetBlock object that is a copy of the passed LeftMagnetBlock
         *   object, except for bool isVisible, which is initialized with false, and unsigned int
         *   uniqueID, which is initialized with 0.
         * 
         * Parameters:
         *   const LeftMagnetBlock& other: A reference to the LeftMagnetBlock object to copy from
         */
        LeftMagnetBlock(const LeftMagnetBlock&);

        /*
         * Assigns this LeftMagnetBlock object the values of the passed LeftMagnetBlock object,
         *   except for bool isVisible, which is assigned false, and unsigned int uniqueID, which
         *   is assigned 0.
         * 
         * Parameters:
         *   const LeftMagnetBlock& rhs: A reference to the LeftMagnetBlock object to assign from
         * 
         * Returns: A reference to this LeftMagnetBlock object
         */
        LeftMagnetBlock& operator =(const LeftMagnetBlock&);

        /*
         * Destructs this LeftMagnetBlock object.
         */
        ~LeftMagnetBlock();
        
        /* ---------- Overriding from Block ---------- */

        /*
         * Performs this LeftMagnetBlock special effect on the given blockField from the passed
         *   coordinates. Should be called when this LeftMagnetBlock is cleared from the
         *   PlayingField.
         *   
         * Parameters:
         *   BlockField& blockField: A reference to the blockField to perform the
         *     effect on
         *   int x: The x-coordinate of this LeftMagnetBlock within the blockField
         *   int y: The y-coordinate of this LeftMagnetBlock within the blockField
         *   
         * Returns: The number of points the special effect accumulated
         */
        int doEffect(BlockField&, int x, int y);

        /*
         * Allocates a clone of this LeftMagnetBlock, including it's uniqueID.
         *   
         * Returns: The address of the newly instantiated clone of this LeftMagnetBlock
         */
        LeftMagnetBlock* makeNewClone() const;


        /*
         * Draws this LeftMagnetBlock to the screen.
         */
        void draw();
};

#endif /* LEFTMAGNETBLOCK_H_ */
