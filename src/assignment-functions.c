#include "assignment-main.h"

////FUNCTION////

void run_the_game(void)
{
    int ground_colour, level_choice;
    double* gravity;
    int COORD[2] =  {INITIAL_X_VEHICLE_POS,
                    INITIAL_Y_VEHICLE_POS};                                     //Initial (x,y)position of the centre of the "half circle of the vehicle"/hub

    double PIPE_ANGLE[1] =  {PIPE_INITIAL_ANGLE};                               //angle of barrel/pipe when first drawn
    int PIPE[2] =           {COORD[0] + PIPE_LENGTH*cos(PIPE_ANGLE[0]),
                            COORD[1] - PIPE_LENGTH*sin(PIPE_ANGLE[0])};         //(x, y)position of the end of the pipe
    int OBSTACLE_COORD[6];                                                      //x, y, x_1, y_1 (centre)coordinates of obstacle(s)

    random_seed();

    display_menu();
    level_choice = display_difficulty();                                        //Promts the user to choose difficulty
    ground_colour = display_locations(gravity);                                 //Promts the user to choose location

    initwindow(X_WINDOW, Y_WINDOW);

    draw_ground(ground_colour);
    draw_scores();
    draw_vehicle(COORD, PIPE, PIPE_ANGLE);
    move_vehicle(COORD, PIPE, PIPE_ANGLE);                                      //Decides new coords, ereases, and draws new vehicle
    draw_obstacle(level_choice, OBSTACLE_COORD);
    set_angle(PIPE_ANGLE);
    draw_projectile(PIPE, PIPE_ANGLE, OBSTACLE_COORD, gravity);

    clear_screen(ground_colour);                                                //Clears screen, redraws ground and leaves a message. Waits for a key press
    draw_scores();
    draw_vehicle(COORD, PIPE, PIPE_ANGLE);
    move_vehicle(COORD, PIPE, PIPE_ANGLE);
    draw_obstacle(level_choice, OBSTACLE_COORD);
    set_angle(PIPE_ANGLE);
    draw_projectile(PIPE, PIPE_ANGLE, OBSTACLE_COORD, gravity);

    clear_screen(ground_colour);
    draw_scores();
    draw_vehicle(COORD, PIPE, PIPE_ANGLE);
    move_vehicle(COORD, PIPE, PIPE_ANGLE);
    draw_obstacle(level_choice, OBSTACLE_COORD);
    set_angle(PIPE_ANGLE);
    draw_projectile(PIPE, PIPE_ANGLE, OBSTACLE_COORD, gravity);

    getch();
    closegraph();
}

void random_seed(void)
{
    srand (time(NULL));             //RANDOM SEED for random number-generator.
}

void display_menu(void)
{
    char key_entered;
    int switch_complete = 0;

    printf("\n\n\nWelcome to 'GAME'!\n------------------------------------------------------------------------\n\n");
    printf("1 - Start Game\n2 - Help\n3 - Exit\n\nType in the first letter of your choice, or 1-3, to proceed:\n");

    do
    {
        key_entered = getch();

        switch (key_entered)
        {
            case 'H':
            case 'h':
            case '2':
                    {display_help();
                    printf("1 - Start Game\n3 - Exit\n\nType in the first letter of your choice, 1 / 3, to proceed:\n");
                    break;}
            case 'S':
            case 's':
            case '1':
                    {switch_complete = 1;
                    break;}
            case 'E':
            case 'e':
            case '3':
                    {exit(EXIT_SUCCESS);}       //command in stdio.h
            default:
                    {printf("That was not a valid key press. Please enter a valid key:\nDo you need help: press 'H' or refer to the user manual:\n");
                    break;}
        }
        fflush(stdin);
    }while (switch_complete == 0);
}

void display_help(void)
{
    printf("\n\n___________________________________\nHOW TO PLAY:\n\n");
    printf("Use the numerical keys 1-3 to navigate the menus. \nAfter the graphical window pops up, position it to the lower right of your \nscreen, and make this window active again.\n");
    printf("The game is played using the arrow-keys 'LEFT' and 'RIGHT', the 'ENTER' button,\nand by the use of the numbers 0-9.\nInstructions will come by as you play if you are in doubt.\n");
    printf("Target: Hit the score markers in the ground to the left without hitting any \nobstacles. You have 3 tries.\n");

    printf("\nPress any key to return to menu:\n\n");
    getch();
}

int display_difficulty(void)
{
    char key_entered;
    int switch_complete = 0, level_choice;

    printf("\n\nChoose difficulty:\n\n");
    printf("Levels:\n\t1 - Low\n\t2 - Medium\n\t3 - High\n\nType in the first letter of your choice, or 1-3, to choose difficulty:\n\n");

    do
    {
        key_entered = getch();

        switch (key_entered)
        {
            case 'L':
            case 'l':
            case '1':
                    {level_choice = 1;
                    switch_complete = 1;
                    printf("Difficulty chosen:\tLow\n");
                    break;}
            case 'M':
            case 'm':
            case '2':
                    {level_choice = 2;
                    switch_complete = 1;
                    printf("Difficulty chosen:\tMedium\n");
                    break;}
            case 'H':
            case 'h':
            case '3':
                    {level_choice = 3;
                    switch_complete = 1;
                    printf("Difficulty chosen:\tHigh\n");
                    break;}
            default:
                    {printf("\nThat was not a valid key press. Please enter a valid key:\n\n");
                    break;}
        }
        fflush(stdin);
    }while (switch_complete == 0);

    return level_choice;
}

int display_locations(double* gravity)
{
    char key_entered;
    int switch_complete = 0, ground_colour;

    printf("\n\nChoose location:\n\n");
    printf("Locations:\n\t1 - Earth\n\t2 - Moon\n\t3 - Mars\n\nType in the number of next to the desired location:\n\n");

    do
    {
        key_entered = getch();

        switch (key_entered)
        {
            case '1':
                {
                    ground_colour = COLOUR_EARTH;
                    gravity[0] = GRAVITY_EARTH;
                    switch_complete = 1;
                    printf("Location chosen:\tEarth\t,where the gravity is 9.81 m/s^2\n");
                    break;
                }
            case '2':
                {
                    ground_colour = COLOUR_MOON;
                    gravity[0] = GRAVITY_MOON;
                    switch_complete = 1;
                    printf("Location chosen:\tthe Moon\t,where the gravity is 1.62 m/s^2\n");
                    break;
                }
            case '3':
                {
                    ground_colour = COLOUR_MARS;
                    gravity[0] = GRAVITY_MARS;
                    switch_complete = 1;
                    printf("Location chosen:\tMars\t,where the gravity is 3.71 m/s^2\n");
                    break;
                }
            default:
                {
                    printf("\nThat was not a valid location. Please enter a valid location:\n\n");
                    break;
                }
        }
        fflush(stdin);
    }while (switch_complete == 0);

    return ground_colour;
}

void draw_ground(int ground_colour)
{
    filled_rectangle(0, GROUND_LEVEL, X_WINDOW, Y_WINDOW, ground_colour);


    setbkcolor(COLOUR_BACKGROUND);   //Sets background colour, not necessary when background colour is black

    //The "GAMENAME" game
    setcolor(COLOUR_TEXT);
    initfont();
    outtextxy(10, 10, "The TANK Game v1.0");

    update_display();
}

void draw_scores (void)
{
    int i;
    int lines [NUMBER_SCORE_LINES] = {COORD_LINES};
    int lines_hight[NUMBER_SCORE_LINES] = {LINE_HIGHT};
    int lines_thickness[NUMBER_SCORE_LINES] =  {LINE_THICKNESS};

    for(i=0; i<NUMBER_SCORE_LINES; i++)
    {
        setcolor(COLOUR_SCORE_LINES);
        line(START_X_SCORE_LINES + lines[i], GROUND_LEVEL, START_X_SCORE_LINES + lines[i], GROUND_LEVEL - lines_hight[i], lines_thickness[i]);
    }

    setcolor(COLOUR_SCORE_VALUES);
    outtextxy(START_X_SCORE_LINES - 6, GROUND_LEVEL, "10 25 25 10");
    outtextxy(START_X_SCORE_LINES + 34, GROUND_LEVEL + 11, "50");
}

void draw_obstacle(int level_choice, int* obstacle_coord)
{
    if (level_choice == 1)          //Level EASY: A small obstacle with no potential to be very challenging
    {
        obstacle_coord[2] = rand_number(EASY_X_LOWER, EASY_X_UPPER);
        obstacle_coord[3] = rand_number(EASY_Y_LOWER, EASY_Y_UPPER);
        filled_circle(obstacle_coord[2], obstacle_coord[3], OBSTACLE_SIZE_SMALL, OBSTACLE_COLOUR);
    }
    if (level_choice == 2)          //Level MEDIUM: A medium sized obstacle with potential to be a bit challenging, e.g. limits are nearer targets.
    {
        obstacle_coord[0] = rand_number(MED_X_LOWER, MED_X_UPPER);
        obstacle_coord[1] = rand_number(MED_Y_LOWER, MED_Y_UPPER);
        filled_circle(obstacle_coord[0], obstacle_coord[1], OBSTACLE_SIZE_BIG, OBSTACLE_COLOUR);
    }
    if (level_choice == 3)          //Level HARD: Two small sized obstacles with potential to be very challenging/impossible.
    {
        obstacle_coord[2] = rand_number(HIGH_X_LOWER - HIGH_PHASER, HIGH_X_UPPER - HIGH_PHASER);
        obstacle_coord[3] = rand_number(HIGH_Y_LOWER + HIGH_PHASER/2, HIGH_Y_UPPER + HIGH_PHASER/2);
        obstacle_coord[4] = rand_number(HIGH_X_LOWER, HIGH_X_UPPER);
        obstacle_coord[5] = rand_number(HIGH_Y_LOWER, HIGH_Y_UPPER);
        filled_circle(obstacle_coord[2], obstacle_coord[3], OBSTACLE_SIZE_SMALL, OBSTACLE_COLOUR);
        filled_circle(obstacle_coord[4], obstacle_coord[5], OBSTACLE_SIZE_SMALL, OBSTACLE_COLOUR);
    }
    update_display();
}

void draw_vehicle(int* vehiclecoords, int* pipecoords, double* pipe_angle)              //Draws vehicle
{
    int i;
    double wheelcenter[3] = {vehiclecoords[0] - VEHICLE_SQUARE_SIDE/2, vehiclecoords[0], vehiclecoords[0] + VEHICLE_SQUARE_SIDE/2};

    setcolor(BROWN);
    line(vehiclecoords[0], vehiclecoords[1], pipecoords[0], pipecoords[1], PIPE_THICKNESS);


    filled_circle(vehiclecoords[0], vehiclecoords[1], RADIUS_HUB, VEHICLE_COLOUR_HUB);
    filled_rectangle(vehiclecoords[0] - VEHICLE_SQUARE_SIDE/2, vehiclecoords[1], vehiclecoords[0] + VEHICLE_SQUARE_SIDE/2, vehiclecoords[1] + VEHICLE_SQUARE_HIGHT, VEHICLE_COLOUR);
    for(i=0; i<3; i++)        //Draws the three wheels
    {
        filled_circle(wheelcenter[i], (int)vehiclecoords[1] + VEHICLE_SQUARE_HIGHT, VEHICLE_WHEELRADIUS, DARKGRAY);             //Different parts of one wheel, different colours for each part}
        filled_circle(wheelcenter[i], (int)vehiclecoords[1] + VEHICLE_SQUARE_HIGHT, 3*VEHICLE_WHEELRADIUS/4, LIGHTGRAY);        //Draws the three wheels
        filled_circle(wheelcenter[i], (int)vehiclecoords[1] + VEHICLE_SQUARE_HIGHT, VEHICLE_WHEELRADIUS/16, BLACK);
    }

    update_display();
}

void erease_vehicle(int* vehiclecoords, int* pipecoords, double* pipe_angle)            //Draws vehicle in background colour
{
    int i;
    double wheelcenter[3] = {vehiclecoords[0] - VEHICLE_SQUARE_SIDE/2, vehiclecoords[0], vehiclecoords[0] + VEHICLE_SQUARE_SIDE/2};

    setcolor(COLOUR_BACKGROUND);
    line(vehiclecoords[0], vehiclecoords[1], pipecoords[0], pipecoords[1], PIPE_THICKNESS);


    filled_circle(vehiclecoords[0], vehiclecoords[1], RADIUS_HUB, COLOUR_BACKGROUND);
    filled_rectangle(vehiclecoords[0] - VEHICLE_SQUARE_SIDE/2, vehiclecoords[1], vehiclecoords[0] + VEHICLE_SQUARE_SIDE/2, vehiclecoords[1] + VEHICLE_SQUARE_HIGHT, COLOUR_BACKGROUND);
    for(i=0; i<3; i++)
    {
        filled_circle(wheelcenter[i], (int)vehiclecoords[1] + VEHICLE_SQUARE_HIGHT, VEHICLE_WHEELRADIUS, COLOUR_BACKGROUND);
        filled_circle(wheelcenter[i], (int)vehiclecoords[1] + VEHICLE_SQUARE_HIGHT, 3*VEHICLE_WHEELRADIUS/4, COLOUR_BACKGROUND);
        filled_circle(wheelcenter[i], (int)vehiclecoords[1] + VEHICLE_SQUARE_HIGHT, VEHICLE_WHEELRADIUS/16, COLOUR_BACKGROUND);
    }

    update_display();
}

void move_vehicle(int* coords, int* pipecoords, double* angle)
{
    int key_pressed;
    int move_right = MIN_MOVE, move_left = MIN_MOVE;

    printf("\n\nUse the left or right arrow key to move the vehicle,\n then press ENTER to choose launch angle\n");
    printf("\n<-- LEFT -- or -- RIGHT -->\n\n\n");

    key_pressed = getch();                                              //First getch
    do
    {
        if ((key_pressed == 0) || (key_pressed == 224))
        {
                key_pressed = getch();
                if (key_pressed == ARROW_LEFT)                                                  //Left arrow
                {
                            if (coords[0] - VEHICLE_WIDTH/2 - move_left >= BORDER)              //Checking capability to move left
                            {
                                erease_vehicle(coords, pipecoords, angle);                      //Drawing the vehicle again
                                coords[0] -= move_left;                                         //Defining new position
                                pipecoords[0] -= move_left;

                                if (move_left < MAX_MOVE)                                       //If MAX_STRIDE isn't reached, up the acceleration
                                {
                                    move_left += ACCELERATION;
                                    move_right = MIN_MOVE;                                      //Makes the stride in the opposite direction to MIN_STRIDE
                                }
                            }
                            else
                            {
                                coords[0] = coords[0];                                          //Coordinates stay the same
                            }
                }
                else if  (key_pressed == ARROW_RIGHT)                                               //Right arrow
                {
                            if (coords[0] + VEHICLE_WIDTH/2 + move_right <= X_WINDOW/2 - BORDER)
                            {
                                erease_vehicle(coords, pipecoords, angle);
                                coords[0] += move_right;
                                pipecoords[0] += move_right;

                                if (move_right < MAX_MOVE)
                                {
                                    move_right += ACCELERATION;
                                    move_left = MIN_MOVE;
                                }
                            }
                            else
                            {
                                coords[0] = coords[0];
                            }
                }
                draw_vehicle(coords, pipecoords, angle);                            //Drawing vehicle in new/not-new position
        }
        else if (key_pressed == ENTER)
        {
            break;
        }
        else
        {
            printf("\nError: The key pressed was not a left/right arrow key.\nIf you are happy with placement of the vehicle, press 'ENTER' to choose angle:\n");
        }
        key_pressed = getch();                  //Getch called again to make the second getch-call in the top of the loop work

    }
    while (key_pressed != ENTER);
}

double set_angle(double* angle)
{
    printf("Type in desired launch angle:\n");
    do
        {   printf("(Must be between 0 and 90 degrees)\n");
            scanf("%lf", angle);
            fflush(stdin);
        }
    while (angle[0] >= 90 || angle[0] < 0);


    angle[0] *= (2* PI / 360);              //Converting to radians

    return angle[0];                        //Not necessary
}

void draw_projectile(int* pipecoords, double* angle, int* obstaclecoords, double* gravity)
{
    int initial_x, initial_y;
    int x_pos, y_pos;
    double vel_x, vel_y;
    double velocity, time;
    double limit_obstackle_small, limit_obstackle_small_2, limit_obstackle_big;
    double projectile_obstackle_radius_small, projectile_obstackle_radius_small_2, projectile_obstackle_radius_big;

    printf("\n\nPut in initial velocity (m/s) for the projectile to be launched:\n");                         //Asking for starting velocity
    do
    {   printf("(Should be around 20-150 m/s, depending on the gravity\n");
        scanf("%lf", &velocity);
        fflush(stdin);
    }
    while ((velocity <= 0)||(velocity > 200));

    vel_x = velocity * cos(angle[0]);
    vel_y = velocity * sin(angle[0]);           //Setting initial velocity in x and y direction

    initial_x = pipecoords[0];                                                             //Setting initial position
    initial_y = pipecoords[1];
    setcolor(COLOUR_PROJECTILE);
    x_pos = initial_x + 1;
    moveto(initial_x, initial_y);                                                       //Moving coordinates to initial positions

    do
    {
        time = (x_pos - initial_x) / vel_x;
        y_pos = (int)(initial_y - (vel_y * time) + (0.5 * gravity[0] * time * time));
                                                                                                                    //Limits of each obstacle determined:
        projectile_obstackle_radius_small = pow((double)(x_pos - obstaclecoords[2]), (double)2) + pow((double)(y_pos - obstaclecoords[3]), (double)2);
        projectile_obstackle_radius_small_2 = pow((double)(x_pos - obstaclecoords[4]), (double)2) + pow((double)(y_pos - obstaclecoords[5]), (double)2);
        projectile_obstackle_radius_big = pow((double)(x_pos - obstaclecoords[0]), (double)2) + pow((double)(y_pos - obstaclecoords[1]), (double)2);
        limit_obstackle_small = sqrt(projectile_obstackle_radius_small);
        limit_obstackle_small_2 = sqrt(projectile_obstackle_radius_small_2);
        limit_obstackle_big = sqrt(projectile_obstackle_radius_big);

        if (y_pos > GROUND_LEVEL)
        {
            lineto(x_pos, GROUND_LEVEL, 1);                 //Making sure the target hits the ground properly
            break;
        }
        else if(limit_obstackle_small < OBSTACLE_SIZE_SMALL)
        {
            break;
        }
        else if(limit_obstackle_small_2 < OBSTACLE_SIZE_SMALL)
        {
            break;
        }
        else if(limit_obstackle_big < OBSTACLE_SIZE_BIG)
        {
            break;
        }
    lineto(x_pos, y_pos, 1);
    x_pos++;
    }
    while (x_pos < X_WINDOW);

    update_display();
}

void clear_screen (int ground_colour)
{
    printf("\nPress any key to continue:\n");
    getch();
    cleardevice();
    draw_ground (ground_colour);
}
