/*
 * Authors:                Wes Cossick, Evan Green, Austin Hash, Taylor Jones
 * Assignment name:        Tetris: Spring 2014 Group Project
 * Assignment description: Write an awesome Tetris clone
 * Due date:               Apr 30, 2014
 * Date created:           Apr 10, 2014
 * Date last modified:     Apr 26, 2014
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "../Drawable.h"
#include "../Rect.h"

class Screen;

struct QUIT{};
struct NEW_SCREEN{
    NEW_SCREEN(Screen* screen = NULL): screen(screen) {}
    Screen* screen;
};

/*
 * Screen:
 * 
 * Inherits from Drawable
 *
 * Screen is intended to be the abstract base class of all objects that contain unique elements
 *   that form a single "screen". You MAY NOT independantly instantiate a Screen object, this is
 *   enforced by making the constructors protected.
 */
class Screen: public Drawable {
_registerForLeakcheckWithID(Screen)
    public:
        
        /*
         * Performs an action based on the passed key. Must be implimented by children of Screen.
         * 
         * Parameters:
         *   int key: The value of the key to perform an action based upon
         *   
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        virtual void respondToKey(int key) throw (QUIT, NEW_SCREEN)= 0;
        
        /*
         * Performs an action based on the passed Click.  Must be implimented by children of
         *   Screen.
         * 
         * Parameters:
         *   Click: The value of the Click to perform an action based upon
         *            
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        virtual void respondToClick(Click click) throw (QUIT, NEW_SCREEN) = 0;
        
        /*
         * Performs actions that should happen continuously in the background on this Screen. Must
         *   be implimented by children of Screen.
         * 
         * Returns: A pointer to the Screen object control should shift to after this function
         *   exits, or NULL if control should not shift to another Screen object
         */
        virtual void doBackground() throw (QUIT, NEW_SCREEN) = 0;
        
        /*
         * Sets Drawable member data width's, height's, and/or locations according to the size of
         *   the screen as reported by GLUT_Plotter. Useful to dynamically move/scale objects when
         *   the screen size changes.
         */
        virtual void applyLayout() = 0;
        
        /*
         * Returns whether or not this Screen object should be retained or deleted when control
         *   shifts to a different screen
         */
        bool shouldRetain() {
            return retain;
        }
        
    protected:
        
        /*
         * Instantiates a Screen object using the passed foreground color or default values.
         * 
         * Parameters:
         *   unsigned int color: The value to initialize this Screen object's foreground with,
         *     defaults to Color::BLACK
         */
        Screen(unsigned int color = Color::BLACK):
        Drawable(0, 0, g->getWidth(), g->getHeight(), color), 
                retain(false), bgRect(0, 0, width, height, color)
        {
        };
        
        /*
         * Prohibit copying or assignment
         */
        Screen(const Screen& other);
        Screen& operator =(const Screen& other);
        
        bool retain;
        
        /*
         * Represents the background fill for this Screen object.
         */
        Rect bgRect;
};

#endif /* SCREEN_H_ */
