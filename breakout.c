//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//
 
// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"
 
// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
 
// number of rows of bricks
#define ROWS 5
 
// number of columns of bricks
#define COLS 10
 
// radius of ball in pixels
#define RADIUS 10
 
// lives
#define LIVES 3
 
// paddle width and height in pixels
#define PAD_HEIGHT 10
#define PAD_WIDTH 100
 
double x_velocity = 1;
double y_velocity = 2;
 
// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
 
int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));
 
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
 
    // instantiate bricks
    initBricks(window);
 
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
 
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
 
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
 
    // number of bricks initially
    int bricks = COLS * ROWS;
 
    // number of lives initially
    int lives = LIVES;
 
    // number of points initially
    int points = 0;
 
    // keep playing until game over 
    // TODO
    while (lives > 0 && bricks > 0)
    {
        move(ball, x_velocity, y_velocity);
        if(getX(ball) + getWidth(ball) >= getWidth(window))
        {
            x_velocity = -x_velocity;
        }
        else if(getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }
        else if(getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
        else if(getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball, 190, 290);
            setLocation(paddle, 180, 560);
            waitForClick();
        }
        pause(10);
         
        GObject object = detectCollision(window, ball);
        if (object != NULL && strcmp(getType(object), "GLabel") != 0)
        if (strcmp(getType(object), "GRect") == 0)
        {
            if (object == paddle)
            {
                y_velocity = -y_velocity;
                x_velocity = -x_velocity;
            }
            else
            {
                removeGWindow(window, object);
                bricks--;
                points++;
                y_velocity = -y_velocity;
                x_velocity = -x_velocity;
            }
        }
         
        //Update scoreboard
        updateScoreboard(window, label, points);
         
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL)
        {
            //if the event was mouse movement
            if(getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle)/2;
                double y = 560;
                setLocation(paddle, x, y);
            }
        }
    }   
    // You win! or...lose...
    if(bricks > 0)
    {
        GLabel verdict = newGLabel("You lose, lol.");
        setFont(verdict, "SansSerif-50");
        setColor(verdict, "C71585");
        add(window, verdict);
        setLocation(verdict, 45, 150);
    }
    else
    {
        GLabel verdict = newGLabel("You win!!");
        setFont(verdict, "SansSerif-50");
        setColor(verdict, "C71585");
        add(window, verdict);
        setLocation(verdict, 185, 150);
    }
 
    // wait for click before exiting
    waitForClick();
 
    // game over
    closeGWindow(window);
    return 0;
}
 
/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO (DONE)
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
        {
            if(i == 0 && j == 0)
            {
            GRect brick = newGRect(2, 30, 37.8, 10);
            setColor(brick, "RED");
            setFilled(brick, true);
            add(window, brick);
            }
            else if(i == 0)
            {
            GRect brick = newGRect(2 + (40 * j), 30, 37.8, 10);
            setColor(brick, "RED");
            setFilled(brick, true);
            add(window, brick);
            }
            else if(i == 1)
            {
            GRect brick = newGRect(2 + (40 * j), 30 + (12 * i), 37.8, 10);
            setColor(brick, "ORANGE");
            setFilled(brick, true);
            add(window, brick);
            }
            else if(i == 2)
            {
            GRect brick = newGRect(2 + (40 * j), 30 + (12 * i), 37.8, 10);
            setColor(brick, "YELLOW");
            setFilled(brick, true);
            add(window, brick);
            }
            else if(i == 3)
            {
            GRect brick = newGRect(2 + (40 * j), 30 + (12 * i), 37.8, 10);
            setColor(brick, "GREEN");
            setFilled(brick, true);
            add(window, brick);
            }
            else if(i == 4)
            {
            GRect brick = newGRect(2 + (40 * j), 30 + (12 * i), 37.8, 10);
            setColor(brick, "BLUE");
            setFilled(brick, true);
            add(window, brick);
            }
        }
}
 
/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO (DONE)
    GOval ball = newGOval(190, 290, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}
 
/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    //TODO (DONE)
    GRect paddle = newGRect(180, 560, 40, 10);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}
 
/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel(" ");
    setFont(label, "SansSerif-50");
    setColor(label, "C71585");
    add(window, label);
    setLocation(label, 185, 300);// TODO
    return label;
}
 
 
/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);
 
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}
 
/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);
 
    // for checking for collisions
    GObject object;
 
    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
 
    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
 
    // no collision
    return NULL;
}
