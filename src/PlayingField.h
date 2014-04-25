/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr 15, 2014
 */

#ifndef PLAYINGFIELD_H_
#define PLAYINGFIELD_H_

#include "Drawable.h"
#include "Tetromino.h"
#include "Shape.h"
#include "Rectangle.h"

#include <vector>
#include <algorithm>
#include <ctime>

/*
 * PlayingField:
 *
 * Inherits from Drawable.
 *
 * PlayingField is intended to represent the field of blocks in play, and provide methods for
 *   general core gameplay, including generating and merging tetrominos and checking whether or not
 *   a shape can move or rotate within the block field. PlayingField IS NOT intended to be
 *   inherited from.
 *
 * PlayingField defines and interprets `int width` and `int height` as the number of Blocks wide
 *   and tall the block field is.
 */
class PlayingField: public Drawable {
    public:
        
        /*
         * Instantiates a PlayingField object using default values.
         */
        PlayingField();

        /*
         * Instantiates a PlayingField object using the passed parameters.
         * 
         * Parameters:
         *   int x: The value to initialize this PlayingField object's x with
         *   int y: The value to initialize this PlayingField object's y with
         *   int width: The value to initialize this PlayingField object's width with
         *   int height: The value to initialize this PlayingField object's height with
         *   int blockSize: The value to initialize this PlayingField object's blockSize with
         *   int padding: The value to initialize this PlayingField object's padding with
         *   unsigned int foreground: The value to initialize this PlayingField object's foreground
         *     with, defaults to Color::WHITE
         *   unsigned int background: The value to initialize this PlayingField object's background
         *     with, defaults to Color::BLACK
         *   int borderWidth: The value to initialize this PlayingField object's borderWidth with,
         *     defaults to 0
         *   unsigned int borderColor: The value to initialize this PlayingField object's
         *     borderColor with, defaults to Color::GREY
         */
        PlayingField(int x, int y, int width, int height, int blockSize, int padding,
                unsigned int foreground = Color::WHITE, unsigned int background = Color::BLACK, 
                int borderWidth = 0, unsigned int borderColor = Color::GRAY);

        /*
         * Instantiates a PlayingField object that is a copy of the passed PlayingField object,
         *   except for bool isVisible, which is initialized with false.
         * 
         * Parameters:
         *   const PlayingField& other: A reference to the PlayingField object to copy from
         */
        PlayingField(const PlayingField&);

        /*
         * Destructs this PlayingField object.
         */
        ~PlayingField();

        /*
         * Assigns this PlayingField object the values of the passed PlayingField object, except
         *   for bool isVisible, which is assigned false.
         * 
         * Parameters:
         *   const PlayingField& rhs: A reference to the PlayingField object to assign from
         * 
         * Returns: A reference to this PlayingField object
         */
        PlayingField& operator =(const PlayingField&);

        /*
         * Dynamically allocates a Tetromino<BlockType> with the passed TetrominoShape centered at
         *   the top of the block field.
         * 
         * Parameters:
         *   TetrominoShape shape: The shape of the tetromino to model the Tetromino<BlockType>
         *   after
         * 
         * Returns: A pointer to the dynamically allocated Tetromino<BlockType>, or NULL if the
         *   tetromino cannot be spawned
         */
        template <typename BlockType>
        Tetromino<BlockType>* spawnNewTetromino(TetrominoShape type) const;

        /*
         * Merges a clone of the Shape pointed to by the passed pointer into the blockField,
         *   de-allocates the Shape, and then checks to see if lines need to be cleared, doing so
         *   if need be.
         *   
         * Parameters:
         *   Shape* shape: A pointer to the Shape object to merge and delete
         */
        void mergeAndDelete(Shape*);
        
        
        /*
         * Getter for blockSize.
         * 
         * Returns: The value of this PlayingField object's blockSize
         */
        int getBlockSize() const;

        /*
         * Getter for padding.
         * 
         * Returns: The value of this PlayingField object's padding
         */
        int getPadding() const;

        /*
         * Getter for the sum of blockSize and padding.
         * 
         * Returns: The value of this PlayingField object's blockSize+padding
         */
        int getTotalBlockSize() const;

        
        /*
         * Determines whether or not the Shape object pointed to by the passed pointer can be
         *   shifted up within the blockField.
         *   
         * Parameters:
         *   const Shape* shape: A pointer to the Shape object to test
         *   
         * Returns: True if the Shape can shift up within the blockField, false otherwise
         */
        bool canShiftUp(const Shape*) const;

        /*
         * Determines whether or not the Shape object pointed to by the passed pointer can be
         *   shifted down within the blockField.
         *   
         * Parameters:
         *   const Shape* shape: A pointer to the Shape object to test
         *   
         * Returns: True if the Shape can shift down within the blockField, false otherwise
         */
        bool canShiftDown(const Shape*) const;

        /*
         * Determines whether or not the Shape object pointed to by the passed pointer can be
         *   shifted left within the blockField.
         *   
         * Parameters:
         *   const Shape* shape: A pointer to the Shape object to test
         *   
         * Returns: True if the Shape can shift left within the blockField, false otherwise
         */
        bool canShiftLeft(const Shape*) const;

        /*
         * Determines whether or not the Shape object pointed to by the passed pointer can be
         *   shifted right within the blockField.
         *   
         * Parameters:
         *   const Shape* shape: A pointer to the Shape object to test
         *   
         * Returns: True if the Shape can shift right within the blockField, false otherwise
         */
        bool canShiftRight(const Shape*) const;


        /*
         * Determines whether or not the TetrominoBase object pointed to by the passed pointer
         *   can be rotated clockwise within the blockField.
         *   
         * Parameters:
         *   const Shape* shape: A pointer to the TetrominoBase object to test
         *   
         * Returns: True if the TetrominoBase object can rotate clockwise within the blockField,
         *   false otherwise
         */
        bool canRotateCW(const TetrominoBase*) const;

        /*
         * Determines whether or not the TetrominoBase object pointed to by the passed pointer can
         *   be rotated counter-clockwise within the blockField.
         *   
         * Parameters:
         *   const Shape* shape: A pointer to the TetrominoBase object to test
         *   
         * Returns: True if the TetrominoBase object can rotate counter-clockwise within the
         *   blockField, false otherwise
         */
        bool canRotateCCW(const TetrominoBase*) const;
        
        /* ---------- Overriding from Drawable ---------- */
        
        /*
         * Getter for width.
         * 
         * Returns: The value of this PlayingField object's width
         */
        int getWidth() const;
        
        /*
         * Getter for height.
         * 
         * Returns: The value of this PlayingField object's height
         */
        int getHeight() const;

        /*
         * Assigns x and y the values of the passed parameters, and properly offsets all Drawable
         *   member data to reflect the shift
         * 
         * Parameters:
         *   int x: The value to assign to this PlayingField object's x
         *   int y: The value to assign to this PlayingField object's y
         */
        void setLocation(int, int);
        
        /* ---------- Implemented from Drawable ---------- */
        
        /*
         * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
         */
        void draw();
        
        /*
         * Erases all Drawable member data from the screen in an order that preserves view
         *   heiarchy.
         */
        void erase();
    private:

        /*
         * Determines whether or not the Block object pointed to by the passed pointer can be added
         *   to the blockField without conflict.
         *   
         * Parameters:
         *   const Shape* shape: A pointer to the Block object to test
         *   
         * Returns: True if the Block object can be added to the blockField without conflict, false
         *   otherwise
         */
        bool couldAdd(const Block*) const;


        /*
         * Checks if there are lines to be cleared, and clears them if there are.
         * 
         * Is mutually recursive with doFall(vector<Shape*>&).
         * 
         * Parameters:
         *   vector<int> clearableLines: The lines to clear
         */
        void doLineClear(vector<int>);

        /*
         * Checks the blockField for lines that are able to be cleared.
         * 
         * Returns: A vector<int> of the indices of the clearable lines
         */
        vector<int> getClearableLines();

        /*
         * Runs through the passed Shape and finds all Blocks either in the blockField or the
         *   passed Shape that have the same uniqueID, replacing them with identical base Blocks.
         *   
         * Parameters:
         *   Shape& shape: A reference to the Shape to use as a base when searching for Blocks with
         *     the same uniqueID
         */
        void normalizeBlocks(Shape&);

        /*
         * For each Block in the passed Shape, performs its special effect on the blockField and
         *   the passed vector<Shape*> of fallingShapes.
         * 
         * Parameters:
         *   Shape& clearedBlocks: A reference to the Shape object who's Block's special effects
         *     should be performed.
         *   vector<Shape*>& fallingShapes: A reference to the vector<Shape*> containing pointers
         *     to the  Shape objects currently falling; since these are separate from the
         *     blockField, they must be passed separately
         */
        void doClearedBlockEffects(Shape&, vector<Shape*>&);

        /*
         * Performs a falling animation for each of the Shapes pointed to by the pointers in the
         *   passed vector<Shape*> and merges Shapes that have finished falling.
         * 
         * Is mutually recursive with doLineClear(vector<int> clearableLines)
         * 
         * Parameters:
         *   vector<Shape*>& fallingShapes: A vector of pointers to Shape objects that need to
         *     have a falling animation performed on them, may contain NULL pointers
         */
        void doFall(vector<Shape*>&);

        
        /*
         * Allocates contiguous Shapes objects from the Blocks in the passed blockField.
         * 
         * Parameters:
         *   vector<vector<Block*> >& blockField: The blockField to from contiguous shapes from
         *   
         * Returns: A vector of pointers to the formed Shape objects
         */
        vector<Shape*> formNewContiguousShapes(vector<vector<Block*> >&);

        /*
         * Recursively makes a Shape from contiguous Blocks in the passed blockField, starting at
         *   the passed coordinates.
         *   
         * Is recursive.
         *   
         * Parameters:
         *   Shape* shape: A pointer to the Shape object to add contiguous blocks to
         *   int x: The x-coordinate of the block to attempt to add
         *   int y: The y-coordinate of the block to attempt to add
         *   vector<vector<Block*> >& blockField: The blockField to pull Blocks from when making
         *     the Shape
         */
        void r_makeContiguousShape(Shape *, int, int, vector<vector<Block*> >&);

        /*
         * Merges a clone of the Shape pointed to by the passed pointer into the blockField.
         *   
         * Parameters:
         *   Shape* shape: A pointer to the Shape object to merge
         */
        void mergeCopy(const Shape*);


        /*
         * Determines the x-index the Block pointed to by the passed pointer would have if it were
         *   a part of the blockField, derived from it's x-coordinate.
         *   
         * Parameters:
         *   const Block* block: A pointer to the Block to determine the x-index of
         *   
         * Return: The x-index of the Block pointed to by the passed pointer
         */
        int xIndexFromLocation(const Block*) const;

        /*
         * Determines the y-index the Block pointed to by the passed pointer would have if it were
         *   a part of the blockField, derived from it's y-coordinate.
         *   
         * Parameters:
         *   const Block* block: A pointer to the Block to determine the y-index of
         *   
         * Return: The y-index of the Block pointed to by the passed pointer
         */
        int yIndexFromLocation(const Block*) const;
        
        /*
         * These variables represent the size in pixels of the blocks this PlayingField contains
         *   and the padding in pixels between blocks
         */
        int blockSize;
        int padding;
        
        /*
         * Represents the width in pixels of the border outline around this BlockField
         */
        int borderWidth;
        
        /*
         * Represents the color of this BlockField's border
         */
        unsigned int borderColor;
        
        /*
         * Represents the background fill for this PlayingField object.
         */
        MyRectangle bgRect;
        
        /*
         * Represents the border fill for this PlayingField object.
         */
        MyRectangle bgRect2;
        
        /*
         * Represents the field of Blocks at the core of the playing field
         */
        vector<vector<Block*> > blockField;
};


/* ---------- Method template implementation ---------- */

/*
 * Dynamically allocates a Tetromino<BlockType> with the passed TetrominoShape centered at the top 
 *   of the block field.
 * 
 * Parameters:
 *   TetrominoShape shape: The shape of the tetromino to model the Tetromino<BlockType> after
 * 
 * Returns: A pointer to the dynamically allocated Tetromino<BlockType>, or NULL if the tetromino
 *   cannot be spawned
 */
template <typename BlockType>
Tetromino<BlockType>* PlayingField::spawnNewTetromino (TetrominoShape type) const {
    Tetromino<BlockType>* tetromino = new Tetromino<BlockType>(
        getLocationX()+getPadding()+borderWidth+getTotalBlockSize()*(width/2),
        getLocationY()+getPadding()+borderWidth+getTotalBlockSize()*height, 
        getBlockSize(), getPadding(), type, getForeground()
    );
    
    tetromino->setLocation(
        tetromino->getLocationX()-(((tetromino->getWidth()+tetromino->getPadding())/
                tetromino->getTotalBlockSize()+1)/2)*tetromino->getTotalBlockSize(),
        tetromino->getLocationY()-tetromino->getHeight()-tetromino->getPadding()
    );
    
    // TODO: Later on, change the spawn point based on if it can actually spawn there.
    // Probably return NULL if we can't spawn period, which would special-case a "game over"
    
    return tetromino;
}

#endif /* PLAYINGFIELD_H_ */
