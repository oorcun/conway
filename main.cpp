/*

Written by Orçun Altınsoy on June 2014.

*/

#include "all.h"

int main()
{
    srand(time(NULL));

    SetConsoleWindowSize(ROW_SIZE , COLUMN_SIZE);

    DrawBattleArea();

    WriteMenu("ARROWS = move , C = put , D = kill , DELETE = reset all , R = random , S = save , L = load , ENTER = start , ESC = exit");

    SetCursorPosition(starting_position);

    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;
    // Allocate memory for 'object' array...
    object = (OBJECT**)malloc(sizeof(OBJECT*) * cs);
    for(int i = 0 ; i < cs ; i++) object[i] = (OBJECT*)malloc(sizeof(OBJECT) * rs);
    // Fill 'object' array with spaces...
    for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) object[i][j] = NOTHING;
    // Allocate memory for 'neighbour' array...
    neighbour = (int**)malloc(sizeof(int*) * cs);
    for(int i = 0 ; i < cs ; i++) neighbour[i] = (int*)malloc(sizeof(int) * rs);
    // Fill 'neighbour' array with zeros...
    for(int i = 0 ; i < cs ; i++) for(int j = 0 ; j < rs ; j++) neighbour[i][j] = 0;

    int c;
    for(;;)
    {
        c = getch();

        if(c == SPECIAL_KEY)
        {
            c = getch();
            if(c == UP_KEY)     { if(!IsCursorNearNorthWall()) MoveCursor(UP);    continue; }
            if(c == LEFT_KEY)   { if(!IsCursorNearWestWall())  MoveCursor(LEFT);  continue; }
            if(c == DOWN_KEY)   { if(!IsCursorNearSouthWall()) MoveCursor(DOWN);  continue; }
            if(c == RIGHT_KEY)  { if(!IsCursorNearEastWall())  MoveCursor(RIGHT); continue; }
            if(c == DELETE_KEY) { ClearMainArea(); generation = 0; continue; }
        }
        if(c == 'c' || c == 'C') { SetCurrentObject(LIVE_CELL); continue; }
        if(c == 'd' || c == 'D') { SetCurrentObject(NOTHING); continue; }
        if(c == 'r' || c == 'R') { Random(); continue; }
        if(c == 'l' || c == 'L') { Load(); continue; }
        if(c == 's' || c == 'S') { Save(); continue; }
        if(c == ENTER_KEY) { Start(); continue; }
        if(c == ESC_KEY) return 0;
    }
}
