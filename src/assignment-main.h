#include <graphics_lib.h>
#include <amio_lib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <time.h>

////DEFINES////

#define ENTER                   13
#define ARROW_LEFT              75
#define ARROW_UP                72
#define ARROW_RIGHT             77
#define ARROW_DOWN              80

#define X_WINDOW                1000            //X/Y- graphics window
#define Y_WINDOW                720

#define RADIUS_HUB              30             //Vehicle data & dependants
#define VEHICLE_SQUARE_SIDE     2*(RADIUS_HUB + 8)
#define VEHICLE_SQUARE_HIGHT    RADIUS_HUB
#define PIPE_LENGTH             80
#define PIPE_THICKNESS          4
#define PIPE_INITIAL_ANGLE      PI/4
#define VEHICLE_WHEELRADIUS     15
#define VEHICLE_WIDTH           VEHICLE_SQUARE_SIDE + 2*VEHICLE_WHEELRADIUS
#define X_POS_MAX               X_WINDOW/2 - VEHICLE_WIDTH
#define X_POS_MIN               VEHICLE_WIDTH
#define INITIAL_X_VEHICLE_POS   X_WINDOW/4 //center of hub
#define INITIAL_Y_VEHICLE_POS   Y_WINDOW-150
#define GROUND_LEVEL            INITIAL_Y_VEHICLE_POS + VEHICLE_SQUARE_HIGHT + VEHICLE_WHEELRADIUS

#define MIN_MOVE                1       //MAX/MIN movement while moving
#define MAX_MOVE                12
#define ACCELERATION            1
#define BORDER                  1       //BORDER, distance from edge


#define OBSTACLE_SIZE_SMALL     40      //Obstacle sizes and random_number-limits
#define OBSTACLE_SIZE_BIG       60
#define OBSTACLE_COLOUR         YELLOW
#define EASY_X_LOWER            X_WINDOW/2
#define EASY_X_UPPER            X_WINDOW
#define EASY_Y_LOWER            Y_WINDOW/3
#define EASY_Y_UPPER            GROUND_LEVEL - 200
#define MED_X_LOWER             5*X_WINDOW/8
#define MED_X_UPPER             X_WINDOW - 50
#define MED_Y_LOWER             Y_WINDOW/2
#define MED_Y_UPPER             GROUND_LEVEL - 150
#define HIGH_X_LOWER            X_WINDOW - 250
#define HIGH_X_UPPER            X_WINDOW - 80
#define HIGH_PHASER             120
#define HIGH_Y_LOWER            GROUND_LEVEL - 250
#define HIGH_Y_UPPER            GROUND_LEVEL - 100

#define GRAVITY_EARTH           9.81
#define GRAVITY_MOON            1.62
#define GRAVITY_MARS            3.71

#define VEHICLE_COLOUR          GREEN               //Different colours in use
#define VEHICLE_COLOUR_HUB      LIGHTGREEN
#define COLOUR_PROJECTILE       WHITE
#define COLOUR_EARTH            GREEN
#define COLOUR_MOON             DARKGRAY
#define COLOUR_MARS             LIGHTRED
#define COLOUR_TEXT             YELLOW
#define COLOUR_BACKGROUND       BLACK
#define COLOUR_SCORE_LINES      YELLOW
#define COLOUR_SCORE_VALUES     WHITE

#define NUMBER_SCORE_AREAS      5                   //Score lines placement/drawing
#define NUMBER_SCORE_LINES      NUMBER_SCORE_AREAS + 1
#define LINE_THICKNESS          3, 2, 1, 1, 2, 3
#define LINE_HIGHT              10, 12, 15, 15, 12, 10
#define COORD_LINES             0, 30, 40, 45, 55, 85
#define START_X_SCORE_LINES     X_WINDOW - 145

////Prototypes////

void run_the_game(void);
void random_seed(void);
void display_menu(void);
void display_help(void);
int display_difficulty(void);
int display_locations(double* gravity);
void draw_ground(int ground_colour);
void draw_scores(void);
void draw_obstacle(int level_choice, int* obstacle_coord);
void draw_vehicle(int* vehiclecoords, int* pipecoords, double* pipe_angle);
void erease_vehicle(int* vehiclecoords, int* pipecoords, double* pipe_angle);
void move_vehicle(int* coords, int* pipecoords, double* angle);
double set_angle(double* angle);
void draw_projectile(int* pipecoords, double* angle, int* obstaclecoords, double* gravity);
void clear_screen(int ground_colour);
