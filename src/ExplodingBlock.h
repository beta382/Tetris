/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr 23, 2014
 * Date last modified:     Apr 23, 2014
 */

#ifndef EXPLODINGBLOCK_H_
#define EXPLODINGBLOCK_H_

#include "Block.h"
#include "Rectangle.h"
#include "util.h"

/*
 * ExplodingBlock:
 *
 * Inherits from Block.
 *
 * ExplodingBlock is intended to represent a Block that explodes when it is cleared. ExplodingBlock
 *   IS NOT intended to be inherited from.
 */
class ExplodingBlock: public Block {
_registerForLeakcheckWithID(ExplodingBlock)
    public:

        /*
         * Instantiates a ExplodingBlock object using default values.
         */
        ExplodingBlock();

        /*
         * Instantiates a ExplodingBlock object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this ExplodingBlock object's x with
         *   int y: The value to initialize this ExplodingBlock object's y with
         *   int width: The value to initialize this ExplodingBlock object's size with
         *   int padding: The value to initialize this ExplodingBlock object's padding with
         *   unsigned int foreground: The value to initialize this ExplodingBlock object's
         *     foreground with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this ExplodingBlock object's
         *     background with, defaults to Color::BLACK
         */
        ExplodingBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);

        /*
         * Instantiates a ExplodingBlock object that is a copy of the passed ExplodingBlock object,
         *   except for bool isVisible, which is initialized with false, and unsigned int uniqueID,
         *   which is initialized with 0.
         * 
         * Parameters:
         *   const ExplodingBlock& other: A reference to the ExplodingBlock object to copy from
         */
        ExplodingBlock(const ExplodingBlock&);

        /*
         * Assigns this ExplodingBlock object the values of the passed ExplodingBlock object,
         *   except for bool isVisible, which is assigned false, and unsigned int uniqueID, which
         *   is assigned 0.
         * 
         * Parameters:
         *   const ExplodingBlock& rhs: A reference to the ExplodingBlock object to assign from
         * 
         * Returns: A reference to this ExplodingBlock object
         */
        ExplodingBlock& operator =(const ExplodingBlock&);

        /*
         * Destructs this ExplodingBlock object.
         */
        ~ExplodingBlock();
        
        /* ---------- Overriding from Block ---------- */

        /*
         * Performs this ExplodingBlock special effect on the given blockField from the passed
         *   coordinates. Should be called when this ExplodingBlock is cleared from the
         *   PlayingField.
         *   
         * Parameters:
         *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the
         *     effect on
         *   int x: The x-coordinate of this ExplodingBlock within the blockField
         *   int y: The y-coordinate of this ExplodingBlock within the blockField
         *   
         * Returns: The number of points the special effect accumulated
         */
        int doEffect(vector<vector<Block*> >&, int x, int y);

        /*
         * Allocates a clone of this ExplodingBlock, including it's uniqueID.
         *   
         * Returns: The address of the newly instantiated clone of this ExplodingBlock
         */
        ExplodingBlock* makeNewClone() const;


        /*
         * Draws this ExplodingBlock to the screen.
         */
        void draw();
};

#endif /* EXPLODINGBLOCK_H_ */
