/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 27, 2014
 * Date last modified:     Apr 27, 2014
 */

#ifndef RIGHTMAGNETBLOCK_H_
#define RIGHTMAGNETBLOCK_H_

#include "Block.h"
#include "util.h"

/*
 * RightMagnetBlock:
 *
 * Inherits from Block.
 *
 * RightMagnetBlock is intended to represent a Block that causes all blocks to fall to the right
 *   when it is cleared. RightMagnetBlock IS NOT intended to be inherited from.
 */
class RightMagnetBlock: public Block {
_registerForLeakcheckWithID(RightMagnetBlock)
    public:

        /*
         * Instantiates a RightMagnetBlock object using default values.
         */
        RightMagnetBlock();

        /*
         * Instantiates a RightMagnetBlock object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this RightMagnetBlock object's x with
         *   int y: The value to initialize this RightMagnetBlock object's y with
         *   int width: The value to initialize this RightMagnetBlock object's size with
         *   int padding: The value to initialize this RightMagnetBlock object's padding with
         *   unsigned int foreground: The value to initialize this RightMagnetBlock object's
         *     foreground with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this RightMagnetBlock object's
         *     background with, defaults to Color::BLACK
         */
        RightMagnetBlock(int x, int y, int size, int padding,
                unsigned int foreground = Color::WHITE, unsigned int background = Color::BLACK);

        /*
         * Instantiates a RightMagnetBlock object that is a copy of the passed RightMagnetBlock
         *   object, except for bool isVisible, which is initialized with false, and unsigned int
         *   uniqueID, which is initialized with 0.
         * 
         * Parameters:
         *   const RightMagnetBlock& other: A reference to the RightMagnetBlock object to copy from
         */
        RightMagnetBlock(const RightMagnetBlock&);

        /*
         * Assigns this RightMagnetBlock object the values of the passed RightMagnetBlock object,
         *   except for bool isVisible, which is assigned false, and unsigned int uniqueID, which
         *   is assigned 0.
         * 
         * Parameters:
         *   const RightMagnetBlock& rhs: A reference to the RightMagnetBlock object to assign from
         * 
         * Returns: A reference to this RightMagnetBlock object
         */
        RightMagnetBlock& operator =(const RightMagnetBlock&);

        /*
         * Destructs this RightMagnetBlock object.
         */
        ~RightMagnetBlock();
        
        /* ---------- Overriding from Block ---------- */

        /*
         * Performs this RightMagnetBlock special effect on the given blockField from the passed
         *   coordinates. Should be called when this RightMagnetBlock is cleared from the
         *   PlayingField.
         *   
         * Parameters:
         *   <vector<vector<Block*> >& blockField: A reference to the blockField to perform the
         *     effect on
         *   int x: The x-coordinate of this RightMagnetBlock within the blockField
         *   int y: The y-coordinate of this RightMagnetBlock within the blockField
         *   
         * Returns: The number of points the special effect accumulated
         */
        int doEffect(vector<vector<Block*> >&, int x, int y);

        /*
         * Allocates a clone of this RightMagnetBlock, including it's uniqueID.
         *   
         * Returns: The address of the newly instantiated clone of this RightMagnetBlock
         */
        RightMagnetBlock* makeNewClone() const;


        /*
         * Draws this RightMagnetBlock to the screen.
         */
        void draw();
};

#endif /* RIGHTMAGNETBLOCK_H_ */
