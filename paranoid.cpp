// ^^^^*********----*********^^^^ //
// *       PARANOID GAME     * //
// * * * * * *  by  * * * * * * * //
// * * BASIT * FARRUKH * UMAIR * * //
//  * * * *  * * * * //
// ^^^^*********----*********^^^^ //



#include<iostream>      
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<vector>			
#include<string>
#include <sstream>

using namespace std;

// Legend for drawing using ASCII values
// 223=paddle , 248=ball , 220=boxes
int PADDLE = 223;
int BALL = 248;
int BOXES = 220;


// Main Class for the game
class paranoid
{
public:
    paranoid()
    {
		player_pos = 1500;
        points = 0;
        finished = false;
		ball_enable = false;
    }

    // draws the cursor
    void cursor();						//Paddle

    // handles player_pos collision
    void Collision();	

    // draws the ball
	friend void ball();

    // starts the game
    void MainMenu();

    // initializes the boundary
    void boundary();

    // moves the player
    void cursor_movement();

    // initialize the main grid
    void initialize_grid();

    // draw everything
    void draw();

    // draw the grid
    void draw_grid();

	// move the ball
	void ball_movement();

	// check collision with ball
	void collide(int pos);

	// check hit and respond
	void hit(int pos);

private:
    // array for holding the grid (game state)
    char arr[1850];

    // position of the player base
    int player_pos;

    // score for the game
    int points;

    // name of the player
    string name;

    // game is over
    bool finished, ball_enable;

	// string stream for holding array
	stringstream stream;

	// ball position (if any)
	int ball_pos, ball_speed;
};

void ClearScreen()
{
      HANDLE                     hStdOut;
      CONSOLE_SCREEN_BUFFER_INFO csbi;
      DWORD                      count;
      DWORD                      cellCount;
      COORD                      homeCoords = { 0, 0 };

      hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
      if (hStdOut == INVALID_HANDLE_VALUE) return;

      /* Get the number of cells in the current buffer */
      if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
      cellCount = csbi.dwSize.X *csbi.dwSize.Y;

      /* Fill the entire buffer with spaces */
      if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
        )) return;

      /* Fill the entire buffer with the current colors and attributes */
      if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
        )) return;

      /* Move the cursor home */
      SetConsoleCursorPosition( hStdOut, homeCoords );
  }


// This function draws the main Menu and starts the game
void paranoid::MainMenu()
{
	// set window size
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 500, 800, TRUE); // 800 width, 100 height

    // Get user input
    system ( "color 2A" );
    cout<<"**************************WELCOME TO PARANOID GAME*************"<<endl<<endl<<endl;
    cout<<"Enter Your Name : "; cin>>name; 
    cout<<endl<<endl;
    cout<<"                    INSTRUCTIONS      "<<endl;
    cout<<"        1. USE <- AND -> FOR MOVEMENT"<<endl;
    cout<<"        2. USE SPACEBAR TO LAUNCH THE BALL"<<endl<<endl<<endl;
    cout<<"Loading";


    // timer and start
    for (int i = 0; i < 8; i++)
    {
        Sleep(15);
        cout<<".";
    }

    // clear screen and set color
    system("cls");
    cout << "                 LETS START :-)";
    system ( "color 1B" );
    Sleep(50);

    // initialize the grid
    initialize_grid();

    // main loop keep drawing each time
    while (!finished)
    {
		cursor_movement();
		ball_movement();
        draw();
        Sleep(15.0f);
    }
}

void paranoid::initialize_grid()
{
    for(int i = 0; i < 1850 ; i++)
    {
        arr[i] = ' ';         
    }
    for ( int i=0 ; i<1850 ; i+=40 ){       //boundries
        arr[i] = char(177);
    }
    for ( int i=39 ; i<1850 ; i+=40 ){  //boundries
        arr[i] = char(177);
    }
    for(int i = 0;i < 26;i+=2)
    {
        arr[i + 47] = char(220);
    }
    for(int i = 0; i < 25 ; i++)
    {
        arr[i + 87] = char(220);
    }
    for(int i = 0; i < 26 ; i+=2)
    {
        arr[i + 127] = char(220);
    }
    for(int i = 0 ; i < 25 ; i++)
    {
        arr[i + 167] = char(220);
    }
    for(int i = 0 ; i < 26 ; i+=2)
    {
        arr[i + 207] = char(220);
    }

	// initialize the player base
	arr[player_pos - 1] = char(223);
	arr[player_pos - 2] = char(223);
	arr[player_pos] = char(223);
	arr[player_pos + 1] = char(223);
	arr[player_pos + 2] = char(223);
}

void paranoid::draw()
{
    // clear the screen first
	COORD cur = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    // clear the string stream
	stream.str(std::string());

    // draw border on top
    stream <<  endl;
    for(int k = 0;k < 40;k++ )
    {
        stream << char(219);
    }
    stream <<  endl;

    // draw the grid
    draw_grid();

    // draw border at bottom
    stream <<  endl;
    for (int k = 0;k < 40;k++ )        //botom line display
    {
        stream << char(219);
    }
    stream <<  endl;
    stream << "\n\n\n            Points:" << points<<"  "<<"PLAYER NAME : "<<name;

    // flush the stream to cout
    cout << stream.str() ;
}

void paranoid::draw_grid()
{
    for(int u = 0;u < 1850;u++)
    {
        if(u!= 0 && u % 40 == 0)
        {
            stream <<  endl;
        }        
        
        stream << arr[u];        //MAin cout statement
    }
}

// move the cursor
void paranoid::cursor_movement()
{
    if (GetAsyncKeyState(VK_LEFT))
    {
        if( arr[player_pos-3] == ' ')
        {
            arr[player_pos + 2] = ' ';
            arr[player_pos - 3]= char(223);
            player_pos--;
       }
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        if(arr[player_pos+3] == ' ')
        {   
            arr[player_pos - 2] = ' ';
            arr[player_pos + 3]=char(223);
            player_pos++;
          }
    }
    else{}

    // creates a ball on space bar 
    if(_kbhit())
    {
        char l = _getch();
        if(l == ' ')
        {
			if (!ball_enable)
			{
                ball_speed = -41;
				ball_pos = player_pos + ball_speed;
				ball_enable = true;
			}
        }
    }
}

// move the ball each time
void paranoid::ball_movement()
{
    // move the ball
    if (ball_enable)
    {
        // set ball at current position to be zero
        arr[ball_pos] = ' ';

        // collide the ball giving next position
        collide(ball_pos);

        // draw the ball over there
        if (ball_enable)
            arr[ball_pos] = char(248);
    }
}

// check if ball collides at this position
void paranoid::collide(int pos)
{
	// getting direction for collisions
	int dir_x = (ball_speed < 0) ? 40-abs(ball_speed) : ball_speed-40;
	int dir_y = (ball_speed < 0) ? -1 : 1;

	// check in xy direction and reverse both if needed
	if (arr[ball_pos+dir_y*40+dir_x] != char(' '))
	{
		if (arr[ball_pos+dir_y*40] == char(' ')	&& arr[ball_pos+dir_x] == char(' '))
		{
			hit(ball_pos+dir_y*40+dir_x);
			dir_x = -dir_x;
			dir_y = -dir_y;
		}
	}

	// check in x, y and xy directions
	if (arr[ball_pos+dir_x] != char(' '))
	{
		hit(ball_pos+dir_x);
		dir_x = -dir_x;
	}
	if (arr[ball_pos+dir_y*40] != char(' '))
	{
		hit(ball_pos+dir_y*40);
		dir_y = -dir_y;
	}
	
	// finding new ball_speed
	ball_speed = dir_x + dir_y*40;

	// move the ball now
	ball_pos = ball_pos + ball_speed;
}

// event on hitting something
void paranoid::hit(int pos)
{
	if (arr[pos] == char(220))
	{
		// delete the box and increase score
		arr[pos] = ' ';
		points++;
	}
}

int main()
{
    srand(time(0));
    paranoid *memb;
    memb = new paranoid;
    memb->MainMenu();
}