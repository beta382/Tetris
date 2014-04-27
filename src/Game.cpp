/*
 * Author:                 Austin Hash
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               May  2, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "Game.h"


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a Game object using the passed foreground color or default values.
 * 
 * Parameters:
 *   unsigned int color: The value to initialize this Game object's foreground with, defaults to
 *     Color::BLACK
 */
Game::Game(unsigned int color): 
Screen(color),
        prevTime(0), tick(500),
        field(0, 0, 10, 20, 16, 2, Color::WHITE, foreground, 2, Color::LIGHT_GRAY),
        currentTetromino(NULL), shadow(NULL),
        bgRectNext(0, 0, field.getTotalBlockSize()*5+field.getPadding(), 
                field.getTotalBlockSize()*3+field.getPadding(), Color::LIGHT_TAN, foreground),
        bgRectNext2(0, 0, bgRectNext.getWidth()+4, bgRectNext.getHeight()+4, Color::DARK_TAN, 
                foreground)
{
    init();
}

/*
 * Destructs this Game object.
 */
Game::~Game() {
    erase();
    delete currentTetromino;
    delete shadow;
}


/* ---------- Implemented from Screen ---------- */

/*
 * Performs an action based on the passed key.
 * 
 * Parameters:
 *   int key: The value of the key to perform an action based upon
 *   
 * Returns: A pointer to the Screen object control should shift to after this function exits, or
 *   NULL if control should not shift to another Screen object
 */
Screen* Game::respondToKey(int key) {
    Screen* nextScreen = NULL;
    
    switch (key) {
        case 'w':
        case Key::UP: // UP
            doSoftFall();
            break;
        case 'a':
        case Key::LEFT: // LEFT
            doShiftLeft();
            break;
        case 's':
        case Key::DOWN: // DOWN
            doShiftDown();
            break;
        case 'd':
        case Key::RIGHT: // RIGHT
            doShiftRight();
            break;
        case 'q': // Rotate CCW
            doRotateCCWWithKick();
            break;
        case 'e': // Rotate CW
            doRotateCWWithKick();
            break;
        case 'n': // New tetromino. This is solely for testing, it spawns a new tetromino without merging.
            doResetTetromino<Block>();
            break;
        case 'j': // Join tetromino. Forcefully merges the current tetromino into the playing field.
            if (!doJoinAndRespawn()) {
                nextScreen = new Game(Color::TAN); // Make this the GameOver Screen
            }
            break;
        case 'p':
            retain = true;
            nextScreen = new PauseScreen(this);
            break;
        default:
            cout << key << endl;
            break;
    }
    
    return nextScreen;
}

/*
 * Performs an action based on the passed Click.
 * 
 * Parameters:
 *   Click: The value of the Click to perform an action based upon
 *            
 * Returns: A pointer to the Screen object control should shift to after this function exits, or
 *   NULL if control should not shift to another Screen object
 */
Screen* Game::respondToClick(Click click) {
    // Do nothing for now
    Screen* nextScreen = NULL;
    
    return nextScreen;
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 * 
 * Returns: A pointer to the Screen object control should shift to after this function exits, or
 *   NULL if control should not shift to another Screen object
 */
Screen* Game::doBackground() {
    Screen* nextScreen = NULL;
    
    /* 
     * If we aren't initialized, initialize. We didn't initialize earlier because we don't want the 
     *   clock to start before we need it to.
     */
    if (prevTime == 0) {
        prevTime = clock();
    }
    
    clock_t curTime = clock();
    
    applyLayout();
    draw();
    
    if (curTime > prevTime+tick) {
        if (field.canShiftDown(currentTetromino)) {
            doShiftDown();
        } else if (!doJoinAndRespawn()) {
            nextScreen = new Game(Color::TAN); // Make this the GameOver Screen
        }
        
        prevTime = curTime;
    }

    return nextScreen;
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void Game::draw() {
    bgRect.draw();
    field.draw();
    
    if (shadow) {
        shadow->draw();
    }
    
    if (currentTetromino) {
        currentTetromino->draw();
    }
    
    bgRectNext2.draw();
    bgRectNext.draw();
    
    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void Game::erase() {
    if (isVisible) {
        if (currentTetromino) {
            currentTetromino->erase();
        }
        
        if (shadow) {   
            shadow->erase();
        }
        
        field.erase();
        bgRect.erase();
        
        isVisible = false;
    }
}


/*
 * Sets Drawable member data width's, height's, and/or locations according to the size of
 *   the screen as reported by GLUT_Plotter. Useful to dynamically move/scale objects when
 *   the screen size changes.
 */
void Game::applyLayout() {
    setWidth(g->getWidth());
    setHeight(g->getHeight());

    bgRect.setWidth(getWidth());
    bgRect.setHeight(getHeight());
    
    int fieldDx = 10-field.getLocationX();
    int fieldDy = 10-field.getLocationY();
    field.setLocation(field.getLocationX()+fieldDx, field.getLocationY()+fieldDy);
    
    if (currentTetromino) {
        currentTetromino->setLocation(currentTetromino->getLocationX()+fieldDx,
            currentTetromino->getLocationY()+fieldDy);
    }
    
    if (shadow) {
        shadow->setLocation(shadow->getLocationX()+fieldDx,  shadow->getLocationY()+fieldDy);
    }

    bgRectNext.setLocation(field.getLocationX()+field.getWidth()+20, 
            field.getLocationY()+field.getHeight()-bgRectNext.getHeight()-50);
    
    bgRectNext2.setLocation(bgRectNext.getLocationX()-2, bgRectNext.getLocationY()-2);
}


/* ---------- Private ---------- */

/*
 * Instantiates this Game object's dynamically allocated member data and starts the RNG.
 */
void Game::init() {
    // We initialize member data with 0s for coordinates, we actually apply the layout here
    applyLayout();
    
    srand(time(0));
    
    TetrominoShape shape = static_cast<TetrominoShape>(rand()%7); // Random TetrominoShape
    
    // Spawn a new tetromino and create a shadow in the same place
    currentTetromino = field.spawnNewTetromino<Block>(shape);
    shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), 
            currentTetromino->getLocationY(), currentTetromino->getBlockSize(),
            currentTetromino->getPadding(), shape, field.getForeground());
    
    // Have the shadow fall
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    draw();
}

/*
 * Properly performs a shift up on currentTetromino, performing checks.
 */
void Game::doShiftUp() {
    if (field.canShiftUp(currentTetromino)) {
        currentTetromino->erase();
        currentTetromino->shiftUp();
        currentTetromino->draw();
    }
}

/*
 * Properly performs a shift down on currentTetromino, performing checks.
 */
void Game::doShiftDown() {
    if (field.canShiftDown(currentTetromino)) {
        currentTetromino->erase();
        currentTetromino->shiftDown();
        currentTetromino->draw();
        
        prevTime = clock();
    }
}

/*
 * Properly performs a shift left on currentTetromino, performing checks.
 */
void Game::doShiftLeft() {
    if (field.canShiftLeft(currentTetromino)) {
        // Erase and move the current tetromino, but don't redraw it just yet
        currentTetromino->erase();
        currentTetromino->shiftLeft();
        
        // Erase the old shadow, move it to the new location of the current tetromino, and then have it fall
        shadow->erase();
        shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
        while (field.canShiftDown(shadow)) {
            shadow->shiftDown();
        }
        
        // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the shadow
        shadow->draw();
        currentTetromino->draw();
    }
}

/*
 * Properly performs a shift right on currentTetromino, performing checks.
 */
void Game::doShiftRight() {
    if (field.canShiftRight(currentTetromino)) {
        // Erase and move the current tetromino, but don't redraw it just yet
        currentTetromino->erase();
        currentTetromino->shiftRight();
        
        // Erase the old shadow, move it to the new location of the current tetromino, and then have it fall
        shadow->erase();
        shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
        while (field.canShiftDown(shadow)) {
            shadow->shiftDown();
        }
        
        // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the shadow
        shadow->draw();
        currentTetromino->draw();
    }
}

/*
 * Properly performs a clockwise rotation on currentTetromino WITHOUT performing checks.
 */
void Game::doRotateCW() {
    // Erase and rotate the current tetromino, but don't redraw it just yet
    currentTetromino->erase();
    currentTetromino->rotateCW();
    
    // Erase the old shadow, move it to the new location of the current tetromino, apply the
    // rotation, and then have it fall
    shadow->erase();
    shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
    shadow->rotateCW();
    
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the
    // shadow
    shadow->draw();
    currentTetromino->draw();
}

/*
 * Properly performs a counter-clockwise rotation on currentTetromino WITHOUT performing checks.
 */
void Game::doRotateCCW() {
    // Erase and rotate the current tetromino, but don't redraw it just yet
    currentTetromino->erase();
    currentTetromino->rotateCCW();       
    
    // Erase the old shadow, move it to the new location of the current tetromino, apply the
    // rotation, and then have it fall
    shadow->erase();
    shadow->setLocation(currentTetromino->getLocationX(), currentTetromino->getLocationY());
    shadow->rotateCCW();
    
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    // Redraw the shadow then the current tetromino, so that the current tetromino may overlap the
    // shadow
    shadow->draw();
    currentTetromino->draw();
}

/*
 * Properly performs a clockwise rotation on currentTetromino, performing checks and wall kicks.
 */
void Game::doRotateCWWithKick() {
    // If we can rotate the current tetromino CW within the block field, do so
    if (field.canRotateCW(currentTetromino)) {
        doRotateCW();
    } else { // If we can't, try doing a wall kick
        currentTetromino->erase();
        currentTetromino->shiftRight();
        if (field.canRotateCW(currentTetromino)) {
            doRotateCW();
        } else { // Reset, try other direction
            currentTetromino->shiftLeft();
            currentTetromino->shiftLeft();
            
            if (field.canRotateCW(currentTetromino)) {
                doRotateCW();
            } else { // Reset
                currentTetromino->shiftRight();
                currentTetromino->draw();
            }
        }
    }
}

/*
 * Properly performs a counter-clockwise rotation on currentTetromino, performing checks and wall
 *   kicks.
 */
void Game::doRotateCCWWithKick() {
    // If we can rotate the current tetromino CCW within the block field, do so
    if (field.canRotateCCW(currentTetromino)) {
        doRotateCCW();
    } else { // If we can't, try doing a wall kick
        currentTetromino->erase();
        currentTetromino->shiftLeft();
        if (field.canRotateCCW(currentTetromino)) {
            doRotateCCW();
        } else { // Reset, try other direction
            currentTetromino->shiftRight();
            currentTetromino->shiftRight();
            
            if (field.canRotateCCW(currentTetromino)) {
                doRotateCCW();
            } else { // Reset
                currentTetromino->shiftLeft();
                currentTetromino->draw();
            }
        }
    }
}

/*
 * Properly performs a soft fall on the currentTetromino, bringing it to the bottom of the screen
 *   without merging.
 */
void Game::doSoftFall() {
    while(field.canShiftDown(currentTetromino)) {
        doShiftDown();
        util::wait(25, g);
    }
    
    // If we can't do any "after-fall" movements, mark for locking
    if(!(field.canShiftLeft(currentTetromino) || field.canShiftRight(currentTetromino) ||
         field.canRotateCCW(currentTetromino) || field.canRotateCW(currentTetromino)))
    {
        prevTime = clock()-tick;
    }
}

/*
 * Joins the currentTetromino with the field and spawns a new one.
 * 
 * Returns: True if a Tetromino could be successfully spawned, false otherwise
 */
bool Game::doJoinAndRespawn() {
    bool couldSpawn;
    
    field.mergeAndDelete(currentTetromino);
    
    TetrominoShape shape = static_cast<TetrominoShape>(rand()%7);
    
    int blockType = rand()%(1 << 15); // Rand maxes at 0x7FFF, 15-bit number
        
    // Spawn a new tetromino and create a shadow in the same place
    
    if (blockType < (1 << 15)/20) { // 1/20
        currentTetromino = field.spawnNewTetromino<ExplodingBlock>(shape);
    } else if (blockType < ((1 << 15)/20)+((1 << 15))/30) { // 1/30
        currentTetromino = field.spawnNewTetromino<GravityBlock>(shape);
    } else {
        currentTetromino = field.spawnNewTetromino<Block>(shape);
    }
    
    couldSpawn = currentTetromino; // If currentTetromino is NULL, couldSpawn becomes false
    
    if (couldSpawn) {
        delete shadow;
        
        shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), currentTetromino->getLocationY(),
                currentTetromino->getBlockSize(), currentTetromino->getPadding(), shape,
                field.getForeground());
        
        // Have the shadow fall
        while (field.canShiftDown(shadow)) {
            shadow->shiftDown();
        }
        
        // Draw the new shadow then the new tetromino, so that the new tetromino may overlap the shadow
        draw();
    }
    
    return couldSpawn;
}
