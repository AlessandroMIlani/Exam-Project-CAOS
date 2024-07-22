
/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include <FreeRTOSConfig.h>
#include "LocalFiles/myutils.h"
#include "task.h"
#include "queue.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "grlib.h"
#include "uart.h"

#define ulSSI_FREQUENCY ( 3500000UL )
#define mainOLED_WIDTH 128

//  ****************************************************************************
//  There are two main drivers available from the FreeRTOS libraries. The 
//  OLED screen is 128x96 pixels, but you can chose between the 128x96 driver
//  and the 1298x64 driver.
//  ** The default driver is the 128x94 driver **
//  *****************************************************************************

#define mainDRIVERLIB_y64
#ifndef mainDRIVERLIB_y64
#include "rit128x96x4.h"
#define mainOLED_HEIGHT 94

#define vDisplayClear() RIT128x96x4Clear()
#define vDisplayInit() RIT128x96x4Init( ulSSI_FREQUENCY )
#define vDisplayOn() RIT128x96x4DisplayOn()
#define vDisplayOff() RIT128x96x4DisplayOff()
#define vDisplayStringDraw RIT128x96x4StringDraw
#define vDisplayImageDraw RIT128x96x4ImageDraw

extern void RIT128x96x4Clear(void);
extern void RIT128x96x4Init(unsigned long ulFrequency);
extern void RIT128x96x4DisplayOn(void);
extern void RIT128x96x4DisplayOff(void);
extern void RIT128x96x4StringDraw(const char *pcStr, unsigned long ulX,
                        unsigned long ulY, unsigned char ucLevel);
extern void RIT128x96x4ImageDraw(const unsigned char *pucImage, unsigned long ulX,
                     unsigned long ulY, unsigned long ulWidth,
                     unsigned long ulHeight);
#else 
#include "osram128x64x4.h"
#define mainOLED_HEIGHT 64

#define vDisplayClear() OSRAM128x64x4Clear()
#define vDisplayInit() OSRAM128x64x4Init( ulSSI_FREQUENCY )
#define vDisplayOn() OSRAM128x64x4DisplayOn()
#define vDisplayOff() OSRAM128x64x4DisplayOff()
#define vDisplayStringDraw OSRAM128x64x4StringDraw
#define vDisplayImageDraw OSRAM128x64x4ImageDraw

extern void OSRAM128x64x4Clear(void);
extern void OSRAM128x64x4Init(unsigned long ulFrequency);
extern void OSRAM128x64x4DisplayOn(void);
extern void OSRAM128x64x4DisplayOff(void);
extern void OSRAM128x64x4ImageDraw(const unsigned char *pucImage, unsigned long ulX,
               unsigned long ulY, unsigned long ulWidth,
               unsigned long ulHeight);
#endif

//  ***************************************************************************
//  The debug routine is enabled by defining the debug flag. This will print
//  debug information to the UART0 port.
//  It occasionaly will be move verbose in case of errors.
//  ** By default it is disabled **
//  ** To enable it, uncomment the following line **
//  #define debug
//  ****************************************************************************
/* #define debug */
char buffer[256]; // Don't want to modify the malloc and the linke so i'll just stick with a memory leak
#ifdef debug 
#define LogDebug(m,...) sprintf(buffer, "[Debug] " m "\n",  ##__VA_ARGS__);print(buffer)
#define LogError(m,...) sprintf(buffer, "[Error] " m "|On line:%d\n",  ##__VA_ARGS__, __LINE__);printf("%s",buffer)
#endif


// ****************************************************************************
// Definition of graphical assets that will be used in the pong game
#define BALL_COL_WIDTH 12 
#define BALL_COL_HEIGHT 10
const unsigned char ballImage[] = {
  // come gli dico di prendere solo una colonna a sinistra?
  // se metto 10 se le mangia entrambe
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 
  0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
  0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00,
  0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  /* 0xFF, 0xFF, 0xFF, 0xFF, */
  /* 0xFF, 0xFF, 0xFF, 0xFF, */
  /* 0xFF, 0xFF, 0xFF, 0xFF, */
  /* 0xFF, 0xFF, 0xFF, 0xFF, */
};

#define PADDLE_COL_WIDTH 2
#define PADDLE_COL_HEIGHT 14
const unsigned char paddleImage[] = {
  0x00,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0x00,
};
  


//*****************************************************************************
//  Definition of structures and functions that will be used in the pong game
//  ****************************************************************************
typedef struct {
    unsigned long x;
    unsigned long y;
} Coord;

typedef struct {
  Coord p_paddle_pos;
  Coord op_paddle_pos;
  Coord ball_pos;
} GameState;

#define PADDLE_OFFSET_FROM_BORDER 4

#define BOUND_PADDLE_TO_SCREEN(y) if(y > mainOLED_HEIGHT - PADDLE_COL_HEIGHT) y = (mainOLED_HEIGHT - PADDLE_COL_HEIGHT); if (!y) y = 1;// Upper bound
#define BOUND_BALL_TO_SCREEN(x, y) if(x > mainOLED_WIDTH - BALL_COL_WIDTH) x = (mainOLED_WIDTH - BALL_COL_WIDTH); if (!x) x = 1; if(y > mainOLED_HEIGHT - BALL_COL_HEIGHT) y = (mainOLED_HEIGHT - BALL_COL_HEIGHT); if (!y) y = 1;// Upper bound

#define P_COLLISION_X(x) (x == PADDLE_OFFSET_FROM_BORDER + PADDLE_COL_WIDTH - 2 || x == mainOLED_WIDTH - PADDLE_OFFSET_FROM_BORDER - BALL_COL_WIDTH - PADDLE_COL_WIDTH + 2)
#define BALL_ON_PADDLE(by, py) (((by + BALL_COL_HEIGHT/2) > py) && ((by + BALL_COL_HEIGHT/2) < py + PADDLE_COL_HEIGHT))
#define WHICH_FIELD(x) (x < mainOLED_WIDTH/2 ? 1 : 0)
// y-> y of ball, py-> y of paddle, oy-> y of opponent paddle, field-> 1 if in half of the player, 0 if in half of the opponent
#define P_COLLISION_Y(y, py, oy, field) (BALL_ON_PADDLE(y, py) && field || BALL_ON_PADDLE(y, oy) && !field)

#define BALL_ON_BORDER(y) (y == 1 || y == mainOLED_HEIGHT - BALL_COL_HEIGHT)
#define CHECK_GOAL(x) (x == PADDLE_OFFSET_FROM_BORDER - 2 || x == mainOLED_WIDTH - PADDLE_OFFSET_FROM_BORDER + 2)

#define PRINT_SCORE(p, op) sprintf(buffer, "Player:%d|Opponent:%d", p, op); vDisplayStringDraw(buffer, (mainOLED_WIDTH - 19*6) / 2, (mainOLED_HEIGHT - 9) / 2, 15)

#define NOTIFY_ACTION_INCREMENT 1
#define NOTIFY_ACTION_DECREMENT 2

void greeter_task(void* pvParameters);
Coord center_pos(char* str);
void graphical_engine_task(void* pvParameters);
void draw_paddle(Coord pos);
void draw_ball(Coord pos);
void game_engine_task(void* pvParameters);
void p_input_task(void* pvParameters);

QueueHandle_t xQueue, xInputQueue;


//**************************Start of actual codebase*****************************
int pong(void)
{
    prvSetupHardware();
    #ifdef debug 
      #ifdef mainDRIVERLIB_y64
        LogDebug("Using 128x64 driver");
      #else
        LogDebug("Using 128x96 driver");
      #endif
    #endif

    vDisplayInit();
    vDisplayOn();

    // Create a msg queue to communicate between the tasks
    xQueue = xQueueCreate(1, sizeof(GameState));
    xInputQueue = xQueueCreate(1, sizeof(uint8_t));
    if (!xQueue) {
        #ifdef debug
          LogError("Failed to create the queue");
        #endif
        return -1;
    }

    xTaskCreate(graphical_engine_task, "Graphical Engine", 1000, NULL, 1, NULL);
    xTaskCreate(game_engine_task, "Game Engine", 1000, NULL, 1, NULL);
    xTaskCreate(p_input_task, "Player Input", 1001, NULL, 1, NULL);
    vTaskStartScheduler();

    return 0;
}

void greeter_task(void* pvParameters)
{
    #ifdef debug
      LogDebug("Greeter task started");
    #endif
    char* title;
    char* subtitle;
    Coord pos_title, pos_subtitle;


    title = "Pong";
    subtitle = "Press any to start";
    pos_title = center_pos(title);
    pos_subtitle = center_pos(subtitle);

    vDisplayStringDraw(title, pos_title.x, pos_title.y, 15);
    vDisplayStringDraw(subtitle, pos_subtitle.x, pos_subtitle.y + 20, 15);

    for(;;);

    UARTCharGet(UART0_BASE);
      vDisplayClear();
      #ifdef debug
        LogDebug("Starting pong game");
      #endif
}

void game_engine_task(void* pvParameters)
{
  #ifdef debug
    LogDebug("Game engine task started");
  #endif
  // Initial configuration of the game state
  Coord p_paddle_pos;
  p_paddle_pos.x = PADDLE_OFFSET_FROM_BORDER;
  p_paddle_pos.y = mainOLED_HEIGHT / 2 - PADDLE_COL_HEIGHT / 2;

  Coord op_paddle_pos;
  op_paddle_pos.x = mainOLED_WIDTH - PADDLE_OFFSET_FROM_BORDER - PADDLE_COL_WIDTH;
  op_paddle_pos.y = mainOLED_HEIGHT / 2 - BALL_COL_HEIGHT / 2;

  Coord ball_pos;
  ball_pos.x = mainOLED_WIDTH / 2 - BALL_COL_WIDTH / 2;
  ball_pos.y = mainOLED_HEIGHT / 2 - BALL_COL_HEIGHT / 2;

  GameState game_state;
  game_state.p_paddle_pos = p_paddle_pos;
  game_state.op_paddle_pos = op_paddle_pos;
  game_state.ball_pos = ball_pos;

  unsigned int p_score, op_score;
  p_score = 0;
  op_score = 0;

  uint8_t last_p_touched; // 1 if player touched the ball, 0 otherwise
  int8_t x_speed = -2, y_speed = 0;
  #ifdef debug
    LogDebug("Initial game state: p_paddle_pos(%d, %d), op_paddle_pos(%d, %d), ball_pos(%d, %d)", game_state.p_paddle_pos.x, game_state.p_paddle_pos.y, game_state.op_paddle_pos.x, game_state.op_paddle_pos.y, game_state.ball_pos.x, game_state.ball_pos.y);
  #endif

  if(!xQueue) {
    #ifdef debug
      LogError("Queue not initialized");
    #endif
    return;
  }
  
  // Game loop
  for(;;) {
    // check consistency of the game state
    BOUND_PADDLE_TO_SCREEN(game_state.p_paddle_pos.y);
    BOUND_PADDLE_TO_SCREEN(game_state.op_paddle_pos.y);
    BOUND_BALL_TO_SCREEN(game_state.ball_pos.x, game_state.ball_pos.y);
    // Draw game state if queue is not full
    if(xQueueSend(xQueue, &game_state, portMAX_DELAY) == pdTRUE) {
      #ifdef debug
        // Log max size and occupied size of the queue
        LogDebug("Queue Size before sending: %d/%d", uxQueueMessagesWaiting(xQueue), uxQueueSpacesAvailable(xQueue)+uxQueueMessagesWaiting(xQueue));
        // log sent data to the queue
        LogDebug("Sent game state: p_paddle_pos(%d, %d), op_paddle_pos(%d, %d), ball_pos(%d, %d)", game_state.p_paddle_pos.x, game_state.p_paddle_pos.y, game_state.op_paddle_pos.x, game_state.op_paddle_pos.y, game_state.ball_pos.x, game_state.ball_pos.y);
      #endif
    }

    // Check if the ball is touching the paddle
    if(P_COLLISION_X(game_state.ball_pos.x) && P_COLLISION_Y(game_state.ball_pos.y, game_state.p_paddle_pos.y, game_state.op_paddle_pos.y, WHICH_FIELD(game_state.ball_pos.x))) {
      #ifdef debug
        LogDebug("Collision with paddle");
      #endif
      x_speed = -x_speed; //Invert x direction of ball
      // If shot coming from top, go down, otherwise go up
      y_speed = y_speed < 0 ? -1 : 1;
    }

    if(BALL_ON_BORDER(game_state.ball_pos.y)) {
      #ifdef debug
        LogDebug("Collision with border");
      #endif
      y_speed = -y_speed; //Invert y direction of ball
    }

    if(CHECK_GOAL(game_state.ball_pos.x)) {
      #ifdef debug
        LogDebug("Goal");
      #endif
      if(!WHICH_FIELD(game_state.ball_pos.x)) {
        p_score++;
      } else {
        op_score++;
      }
      //clear game_state queue
      xQueueReceive(xQueue, &game_state, 0);
      
      vDisplayClear();
      vTaskDelay(pdMS_TO_TICKS(100));
      PRINT_SCORE(p_score, op_score);
      vTaskDelay(pdMS_TO_TICKS(2000));
      vDisplayClear();

      // Reset game state to initial state
      game_state.p_paddle_pos.y = mainOLED_HEIGHT / 2 - PADDLE_COL_HEIGHT / 2;
      game_state.op_paddle_pos.y = mainOLED_HEIGHT / 2 - PADDLE_COL_HEIGHT / 2;
      game_state.ball_pos.x = mainOLED_WIDTH / 2 - BALL_COL_WIDTH / 2;
      game_state.ball_pos.y = mainOLED_HEIGHT / 2 - BALL_COL_HEIGHT / 2;
      x_speed = -2; y_speed = 0;
      continue;
    }


    // update positions of the game state
    game_state.ball_pos.x += x_speed;
    game_state.ball_pos.y += y_speed;
    /* game_state.p_paddle_pos.y++; */
    game_state.op_paddle_pos.y = game_state.ball_pos.y;
   
    // Chill out half a sec, in the meanwhile we should listen for input
    if(xQueueReceive(xInputQueue, &last_p_touched, pdMS_TO_TICKS(70)) == pdTRUE) {
      if(last_p_touched == NOTIFY_ACTION_INCREMENT) {
        game_state.p_paddle_pos.y--;
      } else if(last_p_touched == NOTIFY_ACTION_DECREMENT) {
        game_state.p_paddle_pos.y++;
      }
    }
  }
}

void graphical_engine_task(void* pvParameters)
{
  #ifdef debug
    LogDebug("Graphical engine task started");
  #endif

  if(!xQueue) {
    #ifdef debug
      LogError("Queue not initialized");
    #endif
    return;
  }

  GameState game_state;

  for(;;){
    if(xQueueReceive(xQueue, &game_state, portMAX_DELAY) == pdTRUE) {
      // Log all 
      #ifdef debug
        LogDebug("Received game state: p_paddle_pos(%d, %d), op_paddle_pos(%d, %d), ball_pos(%d, %d)", game_state.p_paddle_pos.x, game_state.p_paddle_pos.y, game_state.op_paddle_pos.x, game_state.op_paddle_pos.y, game_state.ball_pos.x, game_state.ball_pos.y);
      #endif

      // Draw game state
      draw_ball(game_state.ball_pos);
      draw_paddle(game_state.p_paddle_pos);
      draw_paddle(game_state.op_paddle_pos);
    }
  }
}

void draw_ball(Coord pos)
{
  vDisplayImageDraw(ballImage, pos.x, pos.y, BALL_COL_WIDTH, BALL_COL_HEIGHT  );
}

void draw_paddle (Coord pos)
{
  vDisplayImageDraw(paddleImage, pos.x, pos.y, PADDLE_COL_WIDTH, PADDLE_COL_HEIGHT);
}

void p_input_task(void* pvParameters)
{
  #ifdef debug
    LogDebug("Input task started");
  #endif
  char c;
  uint8_t action;
  while(1) {
    c = UARTCharGet(UART0_BASE);
    if(c == 'w') {
      action = NOTIFY_ACTION_INCREMENT;
      xQueueSend(xInputQueue, &action, 0);
    } else if(c == 's') {
      action = NOTIFY_ACTION_DECREMENT;
      xQueueSend(xInputQueue, &action, 0);
    }
  }
}

Coord center_pos(char* str)
{
  Coord pos;

  pos.x = (mainOLED_WIDTH - strlen(str) * 6) / 2;
  pos.y = (mainOLED_HEIGHT - 9) / 2;
  return pos;
}

