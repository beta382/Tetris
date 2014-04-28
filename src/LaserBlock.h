/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#ifndef LASERBLOCK_H_
#define LASERBLOCK_H_

#include "Block.h"
#include "util.h"
#include "Rectangle.h"

/*
 * LaserBlock:
 *
 * Inherits from Block.
 *
 * LaserBlock is intended to represent a single block outline, to be used to show where a Block may
 *   end up. LaserBlock IS NOT intended to be inherited from.
 */
class LaserBlock: public Block {
_registerForLeakcheckWithID(LaserBlock)
    public:

        /*
         * Instantiates a LaserBlock object using default values.
         */
        LaserBlock();

        /*
         * Instantiates a LaserBlock object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this LaserBlock object's x with
         *   int y: The value to initialize this LaserBlock object's y with
         *   int width: The value to initialize this LaserBlock object's size with
         *   int padding: The value to initialize this LaserBlock object's padding with
         *   unsigned int foreground: The value to initialize this LaserBlock object's foreground
         *     with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this LaserBlock object's background
         *     with, defaults to Color::BLACK
         */
        LaserBlock(int x, int y, int size, int padding, unsigned int foreground = Color::WHITE,
                unsigned int background = Color::BLACK);

        /*
         * Instantiates a LaserBlock object that is a copy of the passed LaserBlock object, except
         *   for bool isVisible, which is initialized with false, and unsigned int uniqueID, which
         *   is initialized with 0.
         * 
         * Parameters:
         *   const LaserBlock& other: A reference to the LaserBlock object to copy from
         */
        LaserBlock(const LaserBlock&);

        /*
         * Assigns this LaserBlock object the values of the passed LaserBlock object, except for
         *   bool isVisible, which is assigned false, and unsigned int uniqueID, which is assigned
         *   0.
         * 
         * Parameters:
         *   const LaserBlock& rhs: A reference to the LaserBlock object to assign from
         * 
         * Returns: A reference to this LaserBlock object
         */
        LaserBlock& operator =(const LaserBlock&);

        /*
         * Destructs this LaserBlock object.
         */
        ~LaserBlock();
        
        /* ---------- Overriding from Block ---------- */

        /*
         * Performs this LaserBlock special effect on the given blockField from the passed
         *   coordinates. Should be called when this LaserBlock is cleared from the PlayingField.
         *   
         * Parameters:
         *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the
         *     effect on
         *   int x: The x-coordinate of this LaserBlock within the blockField
         *   int y: The y-coordinate of this LaserBlock within the blockField
         *   
         * Returns: The number of points the special effect accumulated
         */
        int doEffect(vector<vector<Block*> >&, int x, int y);

        /*
         * Allocates a clone of this LaserBlock, including it's uniqueID.
         *   
         * Returns: The address of the newly instantiated clone of this LaserBlock
         */
        LaserBlock* makeNewClone() const;


        /*
         * Draws this LaserBlock to the screen.
         */
        void draw();
};

#endif /* LAsERBLOCK_H_ */
