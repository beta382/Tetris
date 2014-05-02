/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr  3, 2014
 * Date last modified:     Apr 27, 2014
 */

#include "GameScreen.h"

GameScreen* gs = NULL;


/* ---------- Constructors/Destructor ---------- */

/*
 * Instantiates a Game object using the passed foreground color or default values.
 * 
 * Parameters:
 *   unsigned int color: The value to initialize this Game object's foreground with, defaults to
 *     Color::BLACK
 */
GameScreen::GameScreen(unsigned int color): 
Screen(color),
        prevTime(0), tick(500), score(0), level(1),
        field(0, 0, 10, 20, 24, 3, Color::WHITE, foreground, 2, Color::LIGHT_GRAY),
        currentTetromino(NULL), nextTetromino(NULL), shadow(NULL),
        bgRectNext(0, 0, field.getTotalBlockSize()*6+field.getPadding(), 
                field.getTotalBlockSize()*4+field.getPadding(), Color::LIGHT_TAN, foreground),
        bgRectNext2(0, 0, bgRectNext.getWidth()+4, bgRectNext.getHeight()+4, Color::DARK_TAN, 
                foreground),
        logo(0, 0, 15, 2, background), 
        scoreStr(0, 0, 12, 0, "score", Color::LIGHT_GRAY, foreground), 
        levelStr(0, 0, 12, 0, "level", Color::LIGHT_GRAY, foreground),
        scoreNum(0, 0, 8, 0, util::itoa(0), Color::BLACK, foreground),
        levelNum(0, 0, 8, 0, util::itoa(1), Color::BLACK, foreground)
{
    gs = this;
    id = 3;
    init();
}

/*
 * Destructs this Game object.
 */
GameScreen::~GameScreen() {
    erase();
    delete currentTetromino;
    delete shadow;
    delete nextTetromino;
    gs = NULL;
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
void GameScreen::respondToKey(int key) throw (QUIT, NEW_SCREEN) {
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
        case 'p':
        case ' ':
            doPause();
            break;
        case Key::ESC:
            doExit();
            break;
    }
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
void GameScreen::respondToClick(Click click) throw (QUIT, NEW_SCREEN) {
    // Do nothing for now
}

/*
 * Performs actions that should happen continuously in the background on this Screen.
 * 
 * Returns: A pointer to the Screen object control should shift to after this function exits, or
 *   NULL if control should not shift to another Screen object
 */
void GameScreen::doBackground() throw (QUIT, NEW_SCREEN) {
    // If we previously retained this and returned, stop saying to retain or we'll leak
    if (retain) {
        retain = false;
    }
    
    applyLayout();
    draw();

    clock_t curTime = clock();
    
    /* 
     * If we aren't initialized, initialize. We didn't initialize earlier because we don't want the 
     *   clock to start before we need it to.
     */
    if (prevTime <= 0) {
        prevTime += curTime;
    }
    
    if (curTime > prevTime+tick) {
        if (field.canShiftDown(currentTetromino)) {
            doShiftDown();
        } else if (!doJoinAndRespawn()) {
            doGameOver();
        }
        
        prevTime = curTime;
    }
}


/* ---------- Implemented from Drawable ---------- */

/*
 * Draws all Drawable member data to the screen in an order that preserves view heiarchy.
 */
void GameScreen::draw() {
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

    if (nextTetromino) {
        nextTetromino->draw();
    }
    
    logo.draw();
    scoreStr.draw();
    levelStr.draw();
    
    scoreNum.draw();
    levelNum.draw();
    
    isVisible = true;
}

/*
 * Erases all Drawable member data from the screen in an order that preserves view heiarchy.
 */
void GameScreen::erase() {
    if (isVisible) {
        levelNum.erase();
        scoreNum.erase();
        levelStr.erase();
        scoreStr.erase();
        
        
        logo.erase();
        
        if (nextTetromino) {
            nextTetromino->erase();
        }
        
        bgRectNext.erase();
        bgRectNext2.erase();
        
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
void GameScreen::applyLayout() {
    setWidth(g->getWidth());
    setHeight(g->getHeight());
    
    bgRect.setWidth(getWidth());
    bgRect.setHeight(getHeight());
    
    int fieldDx = (getHeight()-field.getHeight())/2-field.getLocationX();
    int fieldDy = (getHeight()-field.getHeight())/2-field.getLocationY();
    field.setLocation(field.getLocationX()+fieldDx, field.getLocationY()+fieldDy);
    
    if (currentTetromino) {
        currentTetromino->setLocation(currentTetromino->getLocationX()+fieldDx,
            currentTetromino->getLocationY()+fieldDy);
    }
    
    if (shadow) {
        shadow->setLocation(shadow->getLocationX()+fieldDx,  shadow->getLocationY()+fieldDy);
    }
    
    logo.setLocation((field.getLocationX()+field.getWidth()+getWidth())/2-logo.getWidth()/2,
            getHeight()-logo.getHeight()-30);
    
    bgRectNext2.setLocation(logo.getLocationX()+logo.getWidth()/2-bgRectNext2.getWidth()/2, 
            logo.getLocationY()-bgRectNext2.getHeight()-field.getTotalBlockSize());
    
    bgRectNext.setLocation(bgRectNext2.getLocationX()+2, bgRectNext2.getLocationY()+2);
    
    if (nextTetromino) {
        nextTetromino->setLocation(
            bgRectNext.getLocationX()+bgRectNext.getWidth()-nextTetromino->getWidth()
                -(bgRectNext.getWidth()/2-nextTetromino->getRealWidth()/2),
            bgRectNext.getLocationY()+bgRectNext.getHeight()-nextTetromino->getHeight()
                -(bgRectNext.getHeight()/2-nextTetromino->getRealHeight()/2)
        );
    }
    
    scoreStr.setLocation(bgRectNext2.getLocationX()+bgRectNext2.getWidth()/2
            -scoreStr.getWidth()/2, bgRectNext2.getLocationY()-scoreStr.getHeight()-50);
    
    scoreNum.setLocation(scoreStr.getLocationX()+scoreStr.getWidth()/2-scoreNum.getWidth()/2,
            scoreStr.getLocationY()-scoreNum.getHeight()-15);
    
    levelStr.setLocation(scoreNum.getLocationX()+scoreNum.getWidth()/2-levelStr.getWidth()/2,
            scoreNum.getLocationY()-levelStr.getHeight()-50);
    
    levelNum.setLocation(levelStr.getLocationX()+levelStr.getWidth()/2-levelNum.getWidth()/2,
            levelStr.getLocationY()-levelNum.getHeight()-15);
}

int GameScreen::getScore() const {
    return score;
}

int GameScreen::getLevel() const {
    return level;
}


/* ---------- Private ---------- */

/*
 * Instantiates this Game object's dynamically allocated member data and starts the RNG.
 */
void GameScreen::init() {
    srand(time(0));
    
    // Spawn a new tetromino and create a shadow in the same place
    currentTetromino = field.spawnNewTetromino<Block>(static_cast<TetrominoShape>(rand()%7));
    shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(), 
            currentTetromino->getLocationY(), currentTetromino->getBlockSize(),
            currentTetromino->getPadding(), currentTetromino->getShape(), field.getForeground());
    
    // Have the shadow fall
    while (field.canShiftDown(shadow)) {
        shadow->shiftDown();
    }
    
    nextTetromino = new Tetromino<Block>(0, 0, field.getBlockSize(), field.getPadding(),
            static_cast<TetrominoShape>(rand()%7), bgRectNext.getForeground());
    
    draw();
}

/*
 * Properly performs a shift up on currentTetromino, performing checks.
 */
void GameScreen::doShiftUp() {
    if (field.canShiftUp(currentTetromino)) {
        currentTetromino->erase();
        currentTetromino->shiftUp();
        currentTetromino->draw();
    }
}

/*
 * Properly performs a shift down on currentTetromino, performing checks.
 */
void GameScreen::doShiftDown() {
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
void GameScreen::doShiftLeft() {
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
void GameScreen::doShiftRight() {
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
void GameScreen::doRotateCW() {
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
void GameScreen::doRotateCCW() {
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
void GameScreen::doRotateCWWithKick() {
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
            } else { // Reset, try shifting down, we might be at the top of the screen 
                currentTetromino->shiftRight();
                currentTetromino->shiftDown();
                
                if (field.canRotateCW(currentTetromino)) {
                    doRotateCW();
                } else { // Reset
                    currentTetromino->shiftUp();
                    currentTetromino->draw();
                }
            }
        }
    }
}

/*
 * Properly performs a counter-clockwise rotation on currentTetromino, performing checks and wall
 *   kicks.
 */
void GameScreen::doRotateCCWWithKick() {
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
            } else { // Reset, try shifting down, we might be at the top of the screen 
                currentTetromino->shiftLeft();
                currentTetromino->shiftDown();
                
                if (field.canRotateCCW(currentTetromino)) {
                    doRotateCCW();
                } else { // Reset
                    currentTetromino->shiftUp();
                    currentTetromino->draw();
                }
            }
        }
    }
}

/*
 * Properly performs a soft fall on the currentTetromino, bringing it to the bottom of the screen
 *   without merging.
 */
void GameScreen::doSoftFall() {
    while(field.canShiftDown(currentTetromino)) {
        doShiftDown();
        util::wait(25, g);
    }
    
    // If we can't do any "after-fall" movements, mark for locking

     if (!field.canShiftLeft(currentTetromino) && !field.canShiftRight(currentTetromino) &&
        ((!field.canRotateCCW(currentTetromino) && !field.canRotateCW(currentTetromino)) || 
                currentTetromino->getShape() == O))
    {
        prevTime = clock()-tick;
    }
}

/*
 * Joins the currentTetromino with the field and spawns a new one.
 * 
 * Returns: True if a Tetromino could be successfully spawned, false otherwise
 */
bool GameScreen::doJoinAndRespawn() {
    bool couldSpawn;
    
    TetrominoBase* tmp = currentTetromino;
    currentTetromino = NULL;
    shadow->erase();
    field.mergeAndDelete(tmp, scoreCallback);
    
    TetrominoShape shape = static_cast<TetrominoShape>(rand()%7);
    
    int blockType = rand();
    
    currentTetromino = field.spawnNewTetromino(nextTetromino);

    if (blockType < (RAND_MAX/50)) { // 1/50
        nextTetromino = new Tetromino<ExplodingBlock>(0, 0, field.getBlockSize(),
                field.getPadding(), shape, bgRectNext.getForeground());
    } else if (blockType < 2*(RAND_MAX/50)) { // 1/50
        nextTetromino = new Tetromino<LaserBlock>(0, 0, field.getBlockSize(),
                field.getPadding(), shape, bgRectNext.getForeground());
    } else if (blockType < 2*(RAND_MAX/50)+(RAND_MAX/69)) { // 1/69
        nextTetromino = new Tetromino<LeftMagnetBlock>(0, 0, field.getBlockSize(),
                field.getPadding(), shape, bgRectNext.getForeground());
    } else if (blockType < 2*(RAND_MAX/50)+2*(RAND_MAX/69)) { // 1/69
        nextTetromino = new Tetromino<RightMagnetBlock>(0, 0, field.getBlockSize(),
                field.getPadding(), shape, bgRectNext.getForeground());
    } else if (blockType < 2*(RAND_MAX/50)+3*(RAND_MAX/69)) { // 1/69
        nextTetromino = new Tetromino<GravityBlock>(0, 0, field.getBlockSize(),
                field.getPadding(), shape, bgRectNext.getForeground());
    } else { // ~11/12
        nextTetromino = new Tetromino<Block>(0, 0, field.getBlockSize(), field.getPadding(),
                shape, bgRectNext.getForeground());
    }
    
    couldSpawn = currentTetromino; // If currentTetromino is NULL, couldSpawn becomes false

    if (couldSpawn) {
        delete shadow;
        
        shadow = new Tetromino<GhostBlock>(currentTetromino->getLocationX(),
                currentTetromino->getLocationY(), currentTetromino->getBlockSize(),
                currentTetromino->getPadding(), currentTetromino->getShape(), 
                field.getForeground());
        
        // Have the shadow fall
        while (field.canShiftDown(shadow)) {
            shadow->shiftDown();
        }
        
        applyLayout();
        
        draw();
        
        // We may have waited while merging, reset the tick
        prevTime = clock();
    }
    
    return couldSpawn;
}

void GameScreen::setScore(int score) {
    this->score = score;
    
    int old_level = level;
    level = score/500 + 1;
    
    levelNum.setString(util::itoa(level));
    scoreNum.setString(util::itoa(score));
    
    if(level > old_level) {
        PlaySound("sounds/level_up.wav", NULL, SND_ASYNC);
    }
    
    //Changes fall speed as levels increase, caps speed at 40
    tick = (500 - 20*(level-1));
            
    if (tick < 40) {
        tick = 40;
    }
}

void GameScreen::doPause() throw (NEW_SCREEN) {
    retain = true;
    prevTime -= clock(); 
    throw NEW_SCREEN(new PauseScreen(this));
}

void GameScreen::doExit() throw (NEW_SCREEN) {
    retain = true;
    prevTime -= clock();
    throw NEW_SCREEN(new ConfirmScreen(this));
}

void GameScreen::doGameOver() throw (NEW_SCREEN) {
    retain = true;
    throw NEW_SCREEN(new GameOverScreen(this));
}

void scoreCallback(int points) {
    gs->scoreNum.erase();
    gs->levelNum.erase();
    gs->setScore(gs->getScore()+points);
    gs->applyLayout();
    gs->scoreNum.draw();
    gs->levelNum.draw();
    gs->g->Draw();
}
