/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Mar 29, 2014
 * Date last modified:     Apr 16, 2014
 */

#include "PlayingField.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a PlayingField object using default values.
 */
PlayingField::PlayingField():
Drawable(0, 0, 10, 20),
        blockSize(10), padding(0),
        bgRect(x, y, (blockSize+padding)*width-padding, (blockSize+padding)*height-padding,
          foreground, background),
        blockField(width, vector<Block*>(height, static_cast<Block*>(NULL)))
{
}

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
 *   unsigned int foreground: The value to initialize this PlayingField object's foreground with,
 *     defaults to Color::WHITE
 *   unsigned int background: The value to initialize this PlayingField object's background with,
 *     defaults to Color::BLACK
 */
PlayingField::PlayingField(int x, int y, int width, int height, int blockSize, int padding,
  unsigned int foreground, unsigned int background):
Drawable(x, y, width, height, foreground, background),
        blockSize(blockSize), padding(padding), 
        bgRect(x, y, (blockSize+padding)*width-padding, (blockSize+padding)*height-padding,
          foreground, background),
        blockField(width, vector<Block*>(height, static_cast<Block*>(NULL)))
{
}

/*
 * Instantiates a PlayingField object that is a copy of the passed PlayingField object, except for
 *   bool isVisible, which is initialized with false.
 * 
 * Parameters:
 *   const PlayingField& other: A reference to the PlayingField object to copy from
 */
PlayingField::PlayingField(const PlayingField& other): 
Drawable(other),
        blockSize(other.blockSize), padding(other.padding), bgRect(other.bgRect),
        blockField(width, vector<Block*>(height, static_cast<Block*>(NULL)))
{
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (other.blockField.at(i).at(j)) {
                blockField[i][j] = other.blockField.at(i).at(j)->makeNewClone();
            }
        }
    }
}

/*
 * Destructs this PlayingField object.
 */
PlayingField::~PlayingField() {
    erase();
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            delete blockField[i][j];
        }
    }
}


/* ---------- Public ---------- */

/*
 * Assigns this PlayingField object the values of the passed PlayingField object, except for bool
 *   isVisible, which is assigned false.
 * 
 * Parameters:
 *   const PlayingField& rhs: A reference to the PlayingField object to assign from
 * 
 * Returns: A reference to this PlayingField object
 */
PlayingField& PlayingField::operator =(const PlayingField& rhs) {
    if  (this != &rhs) {
        erase();
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                delete blockField[i][j];
            }
            
            blockField[i].clear();
        }
        
        blockField.clear();
        
        Drawable::operator =(rhs);
        blockSize = rhs.blockSize;
        padding = rhs.padding;
        bgRect = rhs.bgRect;
        
        blockField.assign(width, vector<Block*>(height, static_cast<Block*>(NULL)));
        
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (rhs.blockField.at(i).at(j)) {
                    blockField[i][j] = rhs.blockField.at(i).at(j)->makeNewClone();
                }
            }
        }
        
        draw();
    }
    
    return *this;
}

/*
 * Merges a clone of the Shape pointed to by the passed pointer into the blockField, de-allocates
 *   the Shape, and then checks to see if lines need to be cleared, doing so if need be.
 *   
 * Parameters:
 *   Shape* shape: A pointer to the Shape object to merge and delete
 */
void PlayingField::mergeAndDelete (Shape* shape) {
    mergeCopy(shape);
    
    delete shape;
    
    draw();
    
    vector<int> clearableLines = getClearableLines();

    if (clearableLines.size() > 0) {
    	doLineClear(clearableLines);
    }
}

/*
 * Determines whether or not the Shape object pointed to by the passed pointer can be shifted up
 *   within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Shape object to test
 *   
 * Returns: True if the Shape can shift up within the blockField, false otherwise
 */
bool PlayingField::canShiftUp(const Shape* shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block* tmp = shape->getBlock(i)->makeNewClone();
        
        // Apply transformation to our tmp Block
        tmp->setLocation(tmp->getLocationX(), tmp->getLocationY()+tmp->getTotalSize());
                
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Determines whether or not the Shape object pointed to by the passed pointer can be shifted down
 *   within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Shape object to test
 *   
 * Returns: True if the Shape can shift down within the blockField, false otherwise
 */
bool PlayingField::canShiftDown(const Shape* shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block* tmp = shape->getBlock(i)->makeNewClone();
        
        // Apply transformation to our tmp Block
        tmp->setLocation(tmp->getLocationX(), tmp->getLocationY()-tmp->getTotalSize());
                
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Determines whether or not the Shape object pointed to by the passed pointer can be shifted left
 *   within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Shape object to test
 *   
 * Returns: True if the Shape can shift left within the blockField, false otherwise
 */
bool PlayingField::canShiftLeft(const Shape* shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block* tmp = shape->getBlock(i)->makeNewClone();
        
        // Apply transformation to our tmp Block
        tmp->setLocation(tmp->getLocationX()-tmp->getTotalSize(), tmp->getLocationY());
                
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Determines whether or not the Shape object pointed to by the passed pointer can be shifted right
 *   within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Shape object to test
 *   
 * Returns: True if the Shape can shift right within the blockField, false otherwise
 */
bool PlayingField::canShiftRight(const Shape* shape) const {
    bool can = true;
    
    for (int i = 0; i < shape->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block* tmp = shape->getBlock(i)->makeNewClone();
        
        // Apply transformation to our tmp Block
        tmp->setLocation(tmp->getLocationX()+tmp->getTotalSize(), tmp->getLocationY());
                
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Determines whether or not the TetrominoBase object pointed to by the passed pointer can be
 *   rotated clockwise within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the TetrominoBase object to test
 *   
 * Returns: True if the TetrominoBase object can rotate clockwise within the blockField, false
 *   otherwise
 */
bool PlayingField::canRotateCW(const TetrominoBase* t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block* tmp = t->getBlock(i)->makeNewClone();
        
        // Apply rotation transformation to our tmp Block
        tmp->setLocation(
            ((tmp->getLocationY()-t->getLocationY())/tmp->getTotalSize()-t->getOffsetY()-
              t->getOffsetX())*tmp->getTotalSize()+t->getLocationX(),
            (t->getWidth()-((tmp->getLocationX()-t->getLocationX())/tmp->getTotalSize()+
              t->getOffsetX())-1+t->getOffsetY())*tmp->getTotalSize()+t->getLocationY()
        );
        
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}

/*
 * Determines whether or not the TetrominoBase object pointed to by the passed pointer can be
 *   rotated counter-clockwise within the blockField.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the TetrominoBase object to test
 *   
 * Returns: True if the TetrominoBase object can rotate counter-clockwise within the blockField,
 *   false otherwise
 */
bool PlayingField::canRotateCCW(const TetrominoBase* t) const {
    bool can = true;
    
    for (int i = 0; i < t->numBlocks() && can; i++) {
        // Create a tmp duplicate, since we actually are applying transformations
        Block* tmp = t->getBlock(i)->makeNewClone();
        
        // Apply rotation transformation to our tmp Block
        tmp->setLocation(
            (t->getHeight()-((tmp->getLocationY()-t->getLocationY())/tmp->getTotalSize()-
              t->getOffsetY())-1-t->getOffsetX())*tmp->getTotalSize()+t->getLocationX(),
            ((tmp->getLocationX()-t->getLocationX())/tmp->getTotalSize()+t->getOffsetX()+
              t->getOffsetY())*tmp->getTotalSize()+t->getLocationY()
        );
         
        if (!couldAdd(tmp)) {
            can = false;
        }
        
        delete tmp;
    }
    
    return can;
}


/* ---------- Private ---------- */

/*
 * Determines whether or not the Block object pointed to by the passed pointer can be added to the
 *   blockField without conflict.
 *   
 * Parameters:
 *   const Shape* shape: A pointer to the Block object to test
 *   
 * Returns: True if the Block object can be added to the blockField without conflict, false
 *   otherwise
 */
bool PlayingField::couldAdd(const Block* block) const {
    bool can = true;
    
    int xIndex = xIndexFromLocation(block);
    int yIndex = yIndexFromLocation(block);
    
    // Check that it isn't out-of-bounds or intersecting an existing Block
    if (xIndex < 0 || xIndex >= getWidth() || yIndex < 0 || yIndex >= getHeight() ||
            blockField.at(xIndex).at(yIndex))
    {
        can = false;
    }
    
    return can;
}

/*
 * Checks if there are lines to be cleared, and clears them if there are.
 * 
 * Is mutually recursive with doFall(vector<Shape*>&).
 * 
 * Parameters:
 *   vector<int> clearableLines: The lines to clear
 */
void PlayingField::doLineClear(vector<int> clearableLines) {
    // Static because this recurses with doFall, maintains the remaining shapes across calls, is
    // always cleared/reset before exiting the top-level of a single call.
	static vector<Shape*> fallingShapes;
	
	vector<Shape*> newFallingShapes;

	// Extract all the clearable lines into a single Shape
	Shape clearedBlocks;
	for (unsigned int i = 0; i < clearableLines.size(); i++) {
		for (int j = 0; j < getWidth(); j++) {
			clearedBlocks.addBlock(blockField[j][clearableLines[i]]->makeNewClone());
			delete blockField[j][clearableLines[i]];
			blockField[j][clearableLines[i]] = NULL;
		}
	}

	clearedBlocks.blink(3, 150);

	normalizeBlocks(clearedBlocks);

	doClearedBlockEffects(clearedBlocks, fallingShapes);

	// See if we have any new shapes to form, and add them to fallingShapes
	newFallingShapes = formNewContiguousShapes(blockField);

	for (unsigned int i = 0; i < newFallingShapes.size(); i++) {
		fallingShapes.push_back(newFallingShapes[i]);
	}

	// Maintains proper order since we might add new shapes out-of-order
	sort(fallingShapes.begin(), fallingShapes.end(), compareShapePointerByLocation);

	doFall(fallingShapes);
    
	// Clear fallingShapes when this finally exits, should be totally NULL at this point
    fallingShapes.clear();
}

/*
 * Checks the blockField for lines that are able to be cleared.
 * 
 * Returns: A vector<int> of the indices of the clearable lines
 */
vector<int> PlayingField::getClearableLines() {
    vector<int> clearableLines;
    
    for (int i = 0; i < getHeight(); i++) {
        bool isClearable = true;
        for (int j = 0; j < getWidth() && isClearable; j++) {
            if (!blockField[j][i]) {
                isClearable = false;
            }
        }
        
        if (isClearable) {
            clearableLines.push_back(i);
        }
    }
    
    return clearableLines;
}

/*
 * Runs through the passed Shape and finds all Blocks either in the blockField or the passed Shape
 *   that have the same uniqueID, replacing them with identical base Blocks.
 *   
 * Parameters:
 *   Shape& shape: A reference to the Shape to use as a base when searching for Blocks with the
 *     same uniqueID
 */
void PlayingField::normalizeBlocks(Shape& shape) {
    for (int i = 0; i < shape.numBlocks(); i++) {
        
        // If the block we are on has a "no-ID", we don't need to check
        if (shape[i] && shape[i]->getUniqueID() != 0) {
            
            // blockField
            for (int j = 0; j < getWidth(); j++) {
                for (int k = 0; k < getHeight(); k++) {
                    if (blockField[j][k] &&
                            blockField[j][k]->getUniqueID() == shape[i]->getUniqueID())
                    {
                        Block* tmp = blockField[j][k];
                        
                        // Not making a clone, this will give us a base Block
                        blockField[j][k] = new Block(*tmp);
                        delete tmp;
                        blockField[j][k]->draw();
                    }
                }
            }
            
            // Passed Shape
            for (int j = i+1; j < shape.numBlocks(); j++) {
                if (shape[i]->getUniqueID() == shape[j]->getUniqueID()) {
                    Block* tmp = shape[j];
                    
                    // Not making a clone, this will give us a base Block
                    shape[j] = new Block(*tmp); 
                    delete tmp; // Don't redraw, these blocks aren't supposed to be visible
                }
            }
        }
    }
}

/*
 * For each Block in the passed Shape, performs its special effect on the blockField and the passed
 *   vector<Shape*> of fallingShapes.
 * 
 * Parameters:
 *   Shape& clearedBlocks: A reference to the Shape object who's Block's special effects should be
 *     performed.
 *   vector<Shape*>& fallingShapes: A reference to the vector<Shape*> containing pointers to the 
 *     Shape objects currently falling; since these are separate from the blockField, they must
 *     be passed separately
 */
void PlayingField::doClearedBlockEffects(Shape& clearedBlocks, vector<Shape*>& fallingShapes) {
    vector<vector<Block*> > remainingBlockField(width,
            vector<Block*>(height, static_cast<Block*>(NULL)));
    
    // Before we perform any special effects, temporarily directly merge any fallingShapes
    for (unsigned int i = 0; i < fallingShapes.size(); i++) {
        for (int j = 0; fallingShapes[i] && j < fallingShapes[i]->numBlocks(); j++) {
            
            Block* curBlock = (*fallingShapes[i])[j];
            int indexX = xIndexFromLocation(curBlock);
            int indexY = yIndexFromLocation(curBlock);
            
            // Delete anything that may already be here
            delete blockField[indexX][indexY];
            
            blockField[indexX][indexY] = curBlock;
            
            curBlock->draw();
        }
    }
    
    // For each cleared block, perform the block's special effect, and then delete the block
    for (int i = 0; i < clearedBlocks.numBlocks(); i++) {
        clearedBlocks[i]->doEffect(blockField, 
                xIndexFromLocation(clearedBlocks[i]), yIndexFromLocation(clearedBlocks[i]));
    }
    
    // Extract the merged fallingShapes and make them into a separate blockField
    for (unsigned int i = 0; i < fallingShapes.size(); i++) {
        for (int j = 0; fallingShapes[i] && j < fallingShapes[i]->numBlocks(); j++) {
            Block* curBlock = (*fallingShapes[i])[j];
            int indexX = xIndexFromLocation(curBlock);
            int indexY = yIndexFromLocation(curBlock);
            
            blockField[indexX][indexY] = NULL;
            remainingBlockField[indexX][indexY] = curBlock;
            
            // NULL the leftover Block pointer copy in fallingShapes
            (*fallingShapes[i])[j] = NULL;
        }
        
        // Deletes dynamically allocated Shape, doesn't delete Blocks because they were NULLed
        delete fallingShapes[i];
    }
    
    // Takes a blockField made from the potentially modified original fallingShapes and forms new
    // shapes out of them. Effectively refreshes fallingShapes post-special effects
    fallingShapes = formNewContiguousShapes(remainingBlockField);
}

/*
 * Performs a falling animation for each of the Shapes pointed to by the pointers in the passed
 *   vector<Shape*> and merges Shapes that have finished falling.
 * 
 * Is mutually recursive with doLineClear(vector<int> clearableLines)
 * 
 * Parameters:
 *   vector<Shape*>& fallingShapes: A vector of pointers to Shape objects that need to have a
 *     falling animation performed on them, may contain NULL pointers
 */
void PlayingField::doFall(vector<Shape*>& fallingShapes) {
	bool didFall = true;
	// While we are still shifting down...
	while(didFall) {
		didFall = false;

		vector<int> mergeIndex;
		vector<int> shiftIndex;
		for (unsigned int i = 0; i < fallingShapes.size(); i++) {
			// Shift down once if we can
			if (fallingShapes[i]) {
				if (canShiftDown(fallingShapes[i])) {
					shiftIndex.push_back(i);
				} else {
					mergeIndex.push_back(i);
				}
			}
		}

		// Merge all the mergeable shapes
		if (mergeIndex.size() > 0) {
			for (unsigned int i = 0; i < mergeIndex.size(); i++) {
				mergeCopy(fallingShapes[mergeIndex[i]]);

				delete fallingShapes[mergeIndex[i]];

				fallingShapes[mergeIndex[i]] = NULL;
			}

			draw();

			for (unsigned int i = 0; i < fallingShapes.size(); i++) {
				if (fallingShapes[i]) {
					fallingShapes[i]->draw();
				}
			}

			g->Draw(); // Force redraw

			// Since we merged, see if we need to clear new lines
			vector<int> clearableLines = getClearableLines();

			if (clearableLines.size() > 0) {
				doLineClear(clearableLines);
			}

			didFall = false;
		}

		// Shift all the shiftable shapes
		if (shiftIndex.size() > 0) {
			for (unsigned int i = 0; i < shiftIndex.size(); i++) {
				// These can be NULL since from previous calls, since all calls pass the same data
				if (fallingShapes.size() > 0 && fallingShapes[shiftIndex[i]]) {
					fallingShapes[shiftIndex[i]]->erase();
					fallingShapes[shiftIndex[i]]->shiftDown();
					fallingShapes[shiftIndex[i]]->draw();
					
					didFall = true;
				}
			}
		}

		g->Draw(); // Force redraw

		util::wait(100);
	}
}

/*
 * Allocates contiguous Shapes objects from the Blocks in the passed blockField.
 * 
 * Parameters:
 *   vector<vector<Block*> >& blockField: The blockField to from contiguous shapes from
 *   
 * Returns: A vector of pointers to the formed Shape objects
 */
vector<Shape*> PlayingField::formNewContiguousShapes(vector<vector<Block*> >& blockField) {
    vector<Shape*> shapes;
    
    for (unsigned int i = 0; blockField.size() > 0 && i < blockField[0].size(); i++) {
        for (unsigned int j = 0; j < blockField.size(); j++) {
            if (blockField[j][i]) {
                Shape* curShape = new Shape(blockField[j][i]->getLocationX(),
                        blockField[j][i]->getLocationY(), blockField[j][i]->getSize(),
                        blockField[j][i]->getPadding());

                r_makeContiguousShape(curShape, j, i, blockField);
                
                curShape->draw();
                
                shapes.push_back(curShape);
            }
        }
    }
    
    return shapes;
}

/*
 * Recursively makes a Shape from contiguous Blocks in the passed blockField, starting at the
 *   passed coordinates.
 *   
 * Is recursive.
 *   
 * Parameters:
 *   Shape* shape: A pointer to the Shape object to add contiguous blocks to
 *   int x: The x-coordinate of the block to attempt to add
 *   int y: The y-coordinate of the block to attempt to add
 *   vector<vector<Block*> >& blockField: The blockField to pull Blocks from when making the Shape
 */
void PlayingField::r_makeContiguousShape(Shape* shape, int x, int y, 
        vector<vector<Block*> >& blockField)
{
    if (x < 0 || x >= static_cast<int>(blockField.size()) || y < 0 ||
            y >= static_cast<int>(blockField[x].size()) || !blockField[x][y]) {
        return;
    }
    
    shape->addBlock(blockField[x][y]);
    
    blockField[x][y] = NULL;
    
    r_makeContiguousShape(shape, x+1, y, blockField);
    r_makeContiguousShape(shape, x, y+1, blockField);
    r_makeContiguousShape(shape, x-1, y, blockField);
    r_makeContiguousShape(shape, x, y-1, blockField);
}

/*
 * Merges a clone of the Shape pointed to by the passed pointer into the blockField.
 *   
 * Parameters:
 *   Shape* shape: A pointer to the Shape object to merge
 */
void PlayingField::mergeCopy(const Shape* shape) {
    for (int i = 0; i < shape->numBlocks(); i++) {
        Block* curBlock = shape->getBlock(i)->makeNewClone();
        int indexX = xIndexFromLocation(curBlock);
        int indexY = yIndexFromLocation(curBlock);
        
        // Delete anything that may already be here
        delete blockField[indexX][indexY];
        
        blockField[indexX][indexY] = curBlock;
        
        curBlock->draw();
    }
}

/*
 * Determines the x-index the Block pointed to by the passed pointer would have if it were a part
 *   of the blockField, derived from it's x-coordinate.
 *   
 * Parameters:
 *   const Block* block: A pointer to the Block to determine the x-index of
 *   
 * Return: The x-index of the Block pointed to by the passed pointer
 */
int PlayingField::xIndexFromLocation(const Block* block) const {
    return (block->getLocationX()-getLocationX())/block->getTotalSize();
}

/*
 * Determines the y-index the Block pointed to by the passed pointer would have if it were a part
 *   of the blockField, derived from it's y-coordinate.
 *   
 * Parameters:
 *   const Block* block: A pointer to the Block to determine the y-index of
 *   
 * Return: The y-index of the Block pointed to by the passed pointer
 */
int PlayingField::yIndexFromLocation(const Block* block) const {
    return (block->getLocationY()-getLocationY())/block->getTotalSize();
}


/* ---------- Overriding from Drawable ---------- */

/*
 * Assigns x and y the values of the passed parameters, and properly offsets all Drawable member
 *   data to reflect the shift
 * 
 * Parameters:
 *   int x: The value to assign to this PlayingField object's x
 *   int y: The value to assign to this PlayingField object's y
 */
void PlayingField::setLocation(int x, int y) {
    int dX = x - getLocationX();
    int dY = y - getLocationY();
    
    erase();
    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blockField[i][j]) {
                blockField[i][j]->setLocation(blockField[i][j]->getLocationX()+dX,
                        blockField[i][j]->getLocationY()+dY);
            }
        }
    }
    
    bgRect.setLocation(bgRect.getLocationX()+dX, getLocationY()+dY);
    
    draw();
    
    this->x = x;
    this->y = y;
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void PlayingField::draw() {
    bgRect.draw();

    for (int i = 0; i < getWidth(); i++) {
        for (int j = 0; j < getHeight(); j++) {
            if (blockField[i][j]) {
                blockField[i][j]->draw();
            }
        }
    }

    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void PlayingField::erase() {
    if (isVisible) {
        for (int i = 0; i < getWidth(); i++) {
            for (int j = 0; j < getHeight(); j++) {
                if (blockField[i][j]) {
                    blockField[i][j]->erase();
                }
            }
        }
        
        bgRect.erase();
        
        isVisible = false;
    }
}
