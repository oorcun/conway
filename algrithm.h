
/*

This header file contains algorithm functions.

*/

#ifndef _ALGRITHM_H_
#define _ALGRITHM_H_

// Find number of neighbours of one cell (opposite ends counts as neighbours).
// Coordinates are relative to main area.
int NumberOfNeighbours(COORD cell)
{
    int c = 0 , dx , dy;
    COORD sp = CursorToCoordinate(starting_position);
    COORD ep = CursorToCoordinate(ending_position);

    //North..
    dx = cell.X == sp.X ? ep.X : cell.X - 1;
    dy = cell.Y;
    if(object[dx][dy] == LIVE_CELL) c++;
    //Northwest..
    dx = cell.X == sp.X ? ep.X : cell.X - 1;
    dy = cell.Y == sp.Y ? ep.Y : cell.Y - 1;
    if(object[dx][dy] == LIVE_CELL) c++;
    //West..
    dx = cell.X;
    dy = cell.Y == sp.Y ? ep.Y : cell.Y - 1;
    if(object[dx][dy] == LIVE_CELL) c++;
    //Southwest..
    dx = cell.X == ep.X ? sp.X : cell.X + 1;
    dy = cell.Y == sp.Y ? ep.Y : cell.Y - 1;
    if(object[dx][dy] == LIVE_CELL) c++;
    //South..
    dx = cell.X == ep.X ? sp.X : cell.X + 1;
    dy = cell.Y;
    if(object[dx][dy] == LIVE_CELL) c++;
    //Southeast..
    dx = cell.X == ep.X ? sp.X : cell.X + 1;
    dy = cell.Y == ep.Y ? sp.Y : cell.Y + 1;
    if(object[dx][dy] == LIVE_CELL) c++;
    //East..
    dx = cell.X;
    dy = cell.Y == ep.Y ? sp.Y : cell.Y + 1;
    if(object[dx][dy] == LIVE_CELL) c++;
    //Northeast..
    dx = cell.X == sp.X ? ep.X : cell.X - 1;
    dy = cell.Y == ep.Y ? sp.Y : cell.Y + 1;
    if(object[dx][dy] == LIVE_CELL) c++;

    return c;
}

// Updates neighbour array.
void UpdateNeighbour()
{
    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;
    COORD c;

    for(c.X = 0 ; c.X < cs ; c.X++) for(c.Y = 0 ; c.Y < rs ; c.Y++) neighbour[c.X][c.Y] = NumberOfNeighbours(c);
}

// Starts evolution.
void Start()
{
    COORD c;
    int rs = main_box_lower_right_position.X - main_box_upper_left_position.X - 1;
    int cs = main_box_lower_right_position.Y - main_box_upper_left_position.Y - 1;
    char s[1024];

    UpdateNeighbour();

    WriteMenu("ENTER = stop , S = increase speed , D = decrease speed");

    for(;;)
    {
        for(c.X = 0 ; c.X < cs ; c.X++) for(c.Y = 0 ; c.Y < rs ; c.Y++)
            if(object[c.X][c.Y] == LIVE_CELL)
            {
                if(neighbour[c.X][c.Y] < 2 || neighbour[c.X][c.Y] > 3) SetObject(NOTHING , CoordinateToCursor(c));
            }
            else
                if(neighbour[c.X][c.Y] == 3) SetObject(LIVE_CELL , CoordinateToCursor(c));

        UpdateNeighbour();

        generation++;

        if(kbhit())
        {
            int i = getch();
            if     (i == 's' || i == 'S') { if(speed < 1000) speed++; }
            else if(i == 'd' || i == 'D') { if(speed > 1)    speed--; }
            else if(i == ENTER_KEY) break;
        }

        sprintf(s , "Speed = %d ticks/sec , Generation = %d" , speed , generation);
        WriteInformation(s);

        Sleep(1000 / speed);
    }

    WriteMenu("ARROWS = move , C = put , D = kill , DELETE = reset all , R = random , S = save , L = load , ENTER = start , ESC = exit");
}

// Creates random seed.
void Random()
{
    COORD c , d = GetCursorPosition();
    char s[1024] , ss[1024];

    do
    {
        strcpy(s , "Enter cell infrequency factor (1 < digit): ");
        WriteInformation(s);
        c = info_position;
        c.X += strlen(s);
        SetCursorPosition(c);
        gets(ss);
    } while(!isdigit(ss[0]) || ss[0] < '2');

    cell_infrequency_factor = ss[0] - 48;

    for(c.X = starting_position.X ; c.X <= ending_position.X ; c.X++) for(c.Y = starting_position.Y ; c.Y <= ending_position.Y ; c.Y++)
    {
        if(rand() % cell_infrequency_factor) SetObject(NOTHING , c);
        else                                 SetObject(LIVE_CELL , c);
    }

    SetCursorPosition(d);
}

#endif
