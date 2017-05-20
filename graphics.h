
/*

This header file contains functions for graphics operations.

*/

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

// Draw rectangular battle area.
void DrawBattleArea()
{
    COORD c = GetCursorPosition();
    int i , j;

    SetCursorPosition(main_box_upper_left_position);

    // Upper side...
    putchar(NORTHWEST_WALL);
    for(i = main_box_upper_left_position.X + 1 ; i < main_box_lower_right_position.X ; i++) putchar(NORTH_WALL);
    putchar(NORTHEAST_WALL);

    putchar('\n');

    // Middle...
    for(i = main_box_upper_left_position.Y + 1 ; i < main_box_lower_right_position.Y ; i++)
    {
        putchar(WEST_WALL);
        for(j = main_box_upper_left_position.X + 1 ; j < main_box_lower_right_position.X ; j++) printf(" ");
        putchar(EAST_WALL);
        putchar('\n');
    }

    // Lower side...
    putchar(SOUTHWEST_WALL);
    for(i = main_box_upper_left_position.X + 1 ; i < main_box_lower_right_position.X ; i++) putchar(SOUTH_WALL);
    putchar(SOUTHEAST_WALL);

    SetCursorPosition(c);
}

// Return 'OBJECT' from cursor position specified by the 'where' parameter.
OBJECT GetObject(const COORD where)
{
    COORD c = CursorToCoordinate(where);

    return object[c.X][c.Y];
}

// Put 'object' to cursor position specified by the 'where' parameter.
void SetObject(const OBJECT object_to_put , const COORD where)
{
    COORD c = GetCursorPosition();
    COORD d = CursorToCoordinate(where);

    object[d.X][d.Y] = object_to_put;

    int o;
    if     (object_to_put == NOTHING)   o = SPACE_KEY;
    else if(object_to_put == LIVE_CELL) o = LIVE_CELL_GRAPHIC;
    SetCursorPosition(where);
    printf("%c" , o);

    SetCursorPosition(c);
}

// Return 'OBJECT' from current cursor position.
OBJECT GetCurrentObject()
{
    return GetObject(GetCursorPosition());
}

// Put 'object' to current cursor position.
void SetCurrentObject(const OBJECT object_to_put)
{
    SetObject(object_to_put , GetCursorPosition());
}

// Clear inside the battle area.
void ClearMainArea()
{
    COORD c;

    for(c.X = starting_position.X ; c.X <= ending_position.X ; c.X++) for(c.Y = starting_position.Y ; c.Y <= ending_position.Y ; c.Y++) if(GetObject(c) != NOTHING) SetObject(NOTHING , c);
}

#endif
