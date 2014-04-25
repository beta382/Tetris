/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  4, 2014
 * Date last modified:     Apr 15, 2014
 */

#ifndef GHOSTBLOCK_H_
#define GHOSTBLOCK_H_

#include "Block.h"
#include "util.h"

/*
 * GhostBlock:
 *
 * Inherits from Block.
 *
 * GhostBlock is intended to represent a single block outline, to be used to show where a Block may
 *   end up. GhostBlock IS NOT intended to be inherited from.
 */
class GhostBlock: public Block {
#ifdef DO_LEAKCHECK
    _registerForLeakcheckWithID(GhostBlock)
#endif
    
    public:

        /*
         * Instantiates a GhostBlock object using default values.
         */
        GhostBlock();

        /*
         * Instantiates a GhostBlock object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this GhostBlock object's x with
         *   int y: The value to initialize this GhostBlock object's y with
         *   int width: The value to initialize this GhostBlock object's size with
         *   int padding: The value to initialize this GhostBlock object's padding with
         *   unsigned int foreground: The value to initialize this GhostBlock object's foreground
         *     with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this GhostBlock object's background
         *     with, defaults to Color::BLACK
         */
        GhostBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);

        /*
         * Instantiates a GhostBlock object that is a copy of the passed GhostBlock object, except
         *   for bool isVisible, which is initialized with false, and unsigned int uniqueID, which
         *   is initialized with 0.
         * 
         * Parameters:
         *   const GhostBlock& other: A reference to the GhostBlock object to copy from
         */
        GhostBlock(const GhostBlock&);

        /*
         * Assigns this GhostBlock object the values of the passed GhostBlock object, except for
         *   bool isVisible, which is assigned false, and unsigned int uniqueID, which is assigned
         *   0.
         * 
         * Parameters:
         *   const GhostBlock& rhs: A reference to the GhostBlock object to assign from
         * 
         * Returns: A reference to this GhostBlock object
         */
        GhostBlock& operator =(const GhostBlock&);

        /*
         * Destructs this GhostBlock object.
         */
        ~GhostBlock();
        
        /* ---------- Overriding from Block ---------- */

        /*
         * Performs this GhostBlock special effect on the given blockField from the passed
         *   coordinates. Should be called when this GhostBlock is cleared from the PlayingField.
         *   
         * Parameters:
         *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the
         *     effect on
         *   int x: The x-coordinate of this GhostBlock within the blockField
         *   int y: The y-coordinate of this GhostBlock within the blockField
         *   
         * Returns: The number of points the special effect accumulated
         */
        int doEffect(vector<vector<Block*> >&, int x, int y);

        /*
         * Allocates a clone of this GhostBlock, including it's uniqueID.
         *   
         * Returns: The address of the newly instantiated clone of this GhostBlock
         */
        GhostBlock* makeNewClone() const;


        /*
         * Draws this GhostBlock to the screen.
         */
        void draw();
};

#endif /* GHOSTBLOCK_H_ */
