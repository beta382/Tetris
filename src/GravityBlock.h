/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr 23, 2014
 * Date last modified:     Apr 23, 2014
 */

#ifndef GRAVITYBLOCK_H_
#define GRAVITYBLOCK_H_

#include "Block.h"
#include "util.h"

#include <ctime>

/*
 * GravityBlock:
 *
 * Inherits from Block.
 *
 * GravityBlock is intended to represent a Block that causes all blocks to fall to the bottom when
 *   it is cleared. GravityBlock IS NOT intended to be inherited from.
 */
class GravityBlock: public Block {
#ifdef DO_LEAKCHECK
    _registerForLeakcheckWithID(GravityBlock)
#endif
    
    public:

        /*
         * Instantiates a GravityBlock object using default values.
         */
        GravityBlock();

        /*
         * Instantiates a GravityBlock object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this GravityBlock object's x with
         *   int y: The value to initialize this GravityBlock object's y with
         *   int width: The value to initialize this GravityBlock object's size with
         *   int padding: The value to initialize this GravityBlock object's padding with
         *   unsigned int foreground: The value to initialize this GravityBlock object's foreground
         *     with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this GravityBlock object's background
         *     with, defaults to Color::BLACK
         */
        GravityBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);

        /*
         * Instantiates a GravityBlock object that is a copy of the passed GravityBlock object,
         *   except for bool isVisible, which is initialized with false, and unsigned int uniqueID,
         *   which is initialized with 0.
         * 
         * Parameters:
         *   const GravityBlock& other: A reference to the GravityBlock object to copy from
         */
        GravityBlock(const GravityBlock&);

        /*
         * Assigns this GravityBlock object the values of the passed GravityBlock object, except
         *   for bool isVisible, which is assigned false, and unsigned int uniqueID, which is
         *   assigned 0.
         * 
         * Parameters:
         *   const GravityBlock& rhs: A reference to the GravityBlock object to assign from
         * 
         * Returns: A reference to this GravityBlock object
         */
        GravityBlock& operator =(const GravityBlock&);

        /*
         * Destructs this GravityBlock object.
         */
        ~GravityBlock();
        
        /* ---------- Overriding from Block ---------- */

        /*
         * Performs this GravityBlock special effect on the given blockField from the passed
         *   coordinates. Should be called when this GravityBlock is cleared from the PlayingField.
         *   
         * Parameters:
         *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the
         *     effect on
         *   int x: The x-coordinate of this GravityBlock within the blockField
         *   int y: The y-coordinate of this GravityBlock within the blockField
         *   
         * Returns: The number of points the special effect accumulated
         */
        int doEffect(vector<vector<Block*> >&, int x, int y);

        /*
         * Allocates a clone of this GravityBlock, including it's uniqueID.
         *   
         * Returns: The address of the newly instantiated clone of this GravityBlock
         */
        GravityBlock* makeNewClone() const;


        /*
         * Draws this GravityBlock to the screen.
         */
        void draw();
};

#endif /* GRAVITYBLOCK_H_ */
