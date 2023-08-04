#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* Board = NULL;
SDL_Texture* Board1 = NULL;
SDL_Texture* Board2 = NULL;
SDL_Texture* change = NULL;

SDL_Texture* bpawn = NULL;
SDL_Texture* bbishop = NULL;
SDL_Texture* bknight = NULL;
SDL_Texture* brock = NULL;
SDL_Texture* bking = NULL;
SDL_Texture* bqueen = NULL;

SDL_Texture* wpawn = NULL;
SDL_Texture* wbishop = NULL;
SDL_Texture* wknight = NULL;
SDL_Texture* wrock = NULL;
SDL_Texture* wking = NULL;
SDL_Texture* wqueen = NULL;

SDL_Texture* white = NULL;
SDL_Texture* black = NULL;
SDL_Texture* draw = NULL;
SDL_Texture* choose = NULL;
SDL_Texture* Restart = NULL;
SDL_Texture* Turn = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Chess 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	Board1 = loadTexture( "Board1.png" );
	Board = Board1;
	Board2 = loadTexture( "Board2.png" );
	change = loadTexture( "Change.png" );
	
	bpawn = loadTexture( "BPawn.png" );
	brock = loadTexture( "BRock.png" );
	bbishop = loadTexture( "BBishop.png" );
	bknight = loadTexture( "BKnight.png" );
	bqueen = loadTexture( "BQueen.png" );
	bking = loadTexture( "BKing.png" );
	
	wpawn = loadTexture( "WPawn.png" );
	wrock = loadTexture( "WRock.png" );
	wbishop = loadTexture( "WBishop.png" );
	wknight = loadTexture( "WKnight.png" );
	wqueen = loadTexture( "WQueen.png" );
	wking = loadTexture( "WKing.png" );
	
	white = loadTexture( "White.png" );
	black = loadTexture( "Black.png" );
	draw = loadTexture( "Draw.png" );
	choose = loadTexture( "Choose.png" );
	Restart = loadTexture( "Restart.png" );
	Turn = loadTexture( "Turn.png" );
	
	if( Board1 == NULL || Board2 == NULL )
	{
		printf( "Failed to load Board!\n" );
		success = false;
	}
	else if(bpawn == NULL || bbishop == NULL || bknight == NULL || bking == NULL || brock == NULL || bqueen == NULL)
	{
		printf( "Failed to load Black pieces!\n" );
		success = false;
	}
	else if(white == NULL || black == NULL || draw == NULL || choose == NULL || Restart == NULL || Turn == NULL || change == NULL )
	{
		printf( "Failed to load Texts!\n" );
		success = false;
	}
	else if(wpawn == NULL || wbishop == NULL || wknight == NULL || wking == NULL || wrock == NULL || wqueen == NULL)
	{
		printf( "Failed to load White pieces!\n" );
		success = false;
	}
	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( Board );
	Board = NULL;
	SDL_DestroyTexture( Board1 );
	Board1 = NULL;
	SDL_DestroyTexture( Board2 );
	Board2 = NULL;
	SDL_DestroyTexture( change );
	change = NULL;
	
	SDL_DestroyTexture( choose );
	choose = NULL;
	SDL_DestroyTexture( black );
	black = NULL;
	SDL_DestroyTexture( white );
	white = NULL;
	SDL_DestroyTexture( draw );
	draw = NULL;
	SDL_DestroyTexture( Restart );
	Restart = NULL;
	SDL_DestroyTexture( Turn );
	Turn = NULL;
	
	SDL_DestroyTexture( wking );
	wking = NULL;
	SDL_DestroyTexture( wpawn );
	wpawn = NULL;
	SDL_DestroyTexture( wrock );
	wrock = NULL;
	SDL_DestroyTexture( wknight );
	wknight = NULL;
	SDL_DestroyTexture( wbishop );
	wbishop = NULL;
	SDL_DestroyTexture( wqueen );
	wqueen = NULL;
	
	SDL_DestroyTexture( bking );
	bking = NULL;
	SDL_DestroyTexture( bpawn );
	bpawn = NULL;
	SDL_DestroyTexture( brock );
	brock = NULL;
	SDL_DestroyTexture( bknight );
	bknight = NULL;
	SDL_DestroyTexture( bbishop );
	bbishop = NULL;
	SDL_DestroyTexture( bqueen );
	bqueen = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

char board[8][8];
//		   y  x

int X = 4;
int Y = 7; // White king position
int x = 4;
int y = 0; // Black king position

int pawnpos[2]; // Pawn's position for En passent

bool wk = false;
bool bk = false;

bool turn = true;
bool clicked = false;
char end = '0';

void restart()
{
	turn = true;
	clicked = false;
	end = '0';
	int i , j;
	X = 4;
	Y = 7;
	x = 4;
	y = 0;
	wk = false;
	bk = false;
	pawnpos[0] = -1;
	pawnpos[1] = -1;
	board[0][0] = 'r';
	board[0][1] = 'n';
	board[0][2] = 'b';
	board[0][3] = 'q';
	board[0][4] = 'k';
	for (i = 5 ; i < 8 ; i++)
		board[0][i] = board[0][7-i];
	for (i = 0 ; i < 8 ; i++)
		board[1][i] = 'p';
	for (j = 2 ; j < 6 ; j++)
		for (i = 0 ; i < 8 ; i++)
			board[j][i] = 'e';
	int s = 'A' - 'a';
	for (j = 6 ; j < 8 ; j++)
		for (i = 0 ; i < 8 ; i++)
			board[j][i] = board[7-j][i] + s;
}

bool check(bool color)
{
	int xx,yy;
	int s = 0;
	if (color)
	{
		yy = Y;
		xx = X;
		if ( yy > 1 && xx > 0 )
			if (board[yy-1][xx-1] == 'p')
				return true;
		if ( yy > 1 && xx < 7 )
			if (board[yy-1][xx+1] == 'p')
				return true;
	}
	else
	{
		yy = y;
		xx = x;
		if ( yy < 6 && xx < 7 )
			if (board[yy+1][xx+1] == 'P')
				return true;
		if ( yy < 6 && xx > 0 )
			if (board[yy+1][xx-1] == 'P')
				return true;
		s = 'A' - 'a';
	}
		
	char b = 'b' + s;
	char q = 'q' + s;
	char r = 'r' + s;
	char n = 'n' + s;
	char k = 'k' + s;
	
	int i;
	int j;
	
	for ( i = -1 ; i <= 1 ; i++ )
		for ( j = -1 ; j <= 1 ; j++ )
			if ( xx+i >= 0 && xx+i < 8 && yy+j >= 0 && yy+j < 8 )
				if ( board[yy+j][xx+i] == k )
					return true;
	
	if ( yy < 7 && xx < 6 )
		if (board[yy+1][xx+2] == n)
			return true;
	
	if ( yy < 6 && xx < 7 )
		if (board[yy+2][xx+1] == n)
			return true;
			
	if ( yy < 7 && xx > 1 )
		if (board[yy+1][xx-2] == n)
			return true;
	
	if ( yy < 6 && xx > 0 )
		if (board[yy+2][xx-1] == n)
			return true;
	
	if ( yy > 0 && xx < 6 )
		if (board[yy-1][xx+2] == n)
			return true;
	
	if ( yy > 1 && xx < 7 )
		if (board[yy-2][xx+1] == n)
			return true;
	
	if ( yy > 0 && xx > 1 )
		if (board[yy-1][xx-2] == n)
			return true;
	
	if ( yy > 1 && xx > 0 )
		if (board[yy-2][xx-1] == n)
			return true;
	
	j = yy;
	for (i = xx + 1 ; i < 8 ; i++)
	{
		j++;
		if (j == 8)
			break;
		if (board[j][i] != 'e')
		{
			if (board[j][i] == q || board[j][i] == b)
				return true;
			else
				break;
		}
	}
	
	j = yy;
	for (i = xx + 1 ; i < 8 ; i++)
	{
		j--;
		if (j == -1)
			break;
		if (board[j][i] != 'e')
		{
			if (board[j][i] == q || board[j][i] == b)
				return true;
			else
				break;
		}
	}
	
	j = yy;
	for (i = xx - 1 ; i >= 0 ; i--)
	{
		j++;
		if (j == 8)
			break;
		if (board[j][i] != 'e')
		{
			if (board[j][i] == q || board[j][i] == b)
				return true;
			else
				break;
		}
	}
	
	j = yy;
	for (i = xx - 1 ; i >= 0 ; i--)
	{
		j--;
		if (j == -1)
			break;
		if (board[j][i] != 'e')
		{
			if (board[j][i] == q || board[j][i] == b)
				return true;
			else
				break;
		}
	}
	
	for (i = xx + 1 ; i < 8 ; i++)
		if (board[yy][i] != 'e')
		{
			if (board[yy][i] == q || board[yy][i] == r)
				return true;
			else
				break;
		}
	
	for (i = xx - 1 ; i >= 0 ; i--)
		if (board[yy][i] != 'e')
		{
			if (board[yy][i] == q || board[yy][i] == r)
				return true;
			else
				break;
		}
	
	for (j = yy + 1 ; j < 8 ; j++)
		if (board[j][xx] != 'e')
		{
			if (board[j][xx] == q || board[j][xx] == r)
				return true;
			else
				break;
		}
	
	for (j = yy - 1 ; j >= 0 ; j--)
		if (board[j][xx] != 'e')
		{
			if (board[j][xx] == q || board[j][xx] == r)
				return true;
			else
				break;
		}
	
	return false;
}

bool move(int i , int j , int fx , int fy)
{
	char temp = board[j][i];
	
	if ( board[fy][fx] == 'K' )
	{
		if ( fx == 4 && fy == 7 && board[7][5]=='e' && board [7][7] == 'R' && i == 6 && j == 7 )
		{
			if ( check(true) )
				return false;
			if ( !wk )
			{
				X = 5;
				if ( check(true) )
				{
					X = 4;
					return false;
				}
				board[7][7] = 'e';
				board[7][4] = 'e';
				board[7][5] = 'R';
				board[7][6] = 'K';
				X = 6;
				if ( check(true) )
				{
					board[j][i] = temp;
					board[fy][fx] = 'K';
					X = 4;
					Y = 7;
					return false;
				}
				wk = true;
				pawnpos[0] = -1;
				pawnpos[1] = -1;
				return true;
			}
			return false;
		}
		if ( j - fy > -2 && j - fy < 2 && i - fx > -2 && i - fx < 2 )
		{
			board[j][i] = 'K';
			board[fy][fx] = 'e';
			Y = j;
			X = i;
			if ( check(true) )
			{
				board[j][i] = temp;
				board[fy][fx] = 'K';
				X = fx;
				Y = fy;
				return false;
			}
			wk = true;
			pawnpos[0] = -1;
			pawnpos[1] = -1;
			return true;
		}
		return false;
	}
	
	if ( board[fy][fx] == 'k' )
	{
		if ( fx == 4 && fy == 0 && board[0][5]=='e' && board [0][7] == 'r' && i == 6 && j == 0 )
		{
			if ( check(false) )
				return false;
			if ( !bk )
			{
				x = 5;
				if ( check(false) )
				{
					x = 4;
					return false;
				}
				board[0][7] = 'e';
				board[0][4] = 'e';
				board[0][5] = 'r';
				board[0][6] = 'k';
				x = 6;
				if ( check(false) )
				{
					board[j][i] = temp;
					board[fy][fx] = 'k';
					x = 4;
					y = 0;
					return false;
				}
				bk = true;
				pawnpos[0] = -1;
				pawnpos[1] = -1;
				return true;
			}
			return false;
		}
		if ( j - fy > -2 && j - fy < 2 && i - fx > -2 && i - fx < 2 )
		{
			board[j][i] = 'k';
			board[fy][fx] = 'e';
			y = j;
			x = i;
			if ( check(false) )
			{
				board[j][i] = temp;
				board[fy][fx] = 'k';
				x = fx;
				y = fy;
				return false;
			}
			bk = true;
			pawnpos[0] = -1;
			pawnpos[1] = -1;
			return true;
		}
		return false;
	}
	
	if ( board[fy][fx] == 'P' )
	{
		if ( fx == i )
		{
			if ( board[fy-1][fx] != 'e' )
				return false;
			if ( fy == 6 && j == 4 )
			{
				if ( board[4][fx] != 'e' )
					return false;
				board[4][i] = 'P';
				board[6][i] = 'e';
				if ( check(true) )
				{
					board[4][i] = 'e';
					board[6][i] = 'P';
					return false;
				}
				pawnpos[0] = 4;
				pawnpos[1] = i;
				return true;
			}
			if ( fy-1 != j )
				return false;
			board[j][i] = 'P';
			board[fy][fx] = 'e';
			if ( check(true) )
			{
				board[j][i] = 'e';
				board[fy][fx] = 'P';
				return false;
			}
			pawnpos[0] = -1;
			pawnpos[1] = -1;
			return true;
		}
		if ( !( j == fy-1 && ( fx-i == -1 || fx-i == 1) ) )
			return false;
		if ( board[j][i] == 'e' )
			if ( pawnpos[0] == j+1 && pawnpos[1] == i)
			{
				board[j][i] = 'P';
				board[fy][fx] = 'e';
				board[j+1][i] = 'e';
				if ( check(true) )
				{
					board[j][i] = 'e';
					board[fy][fx] = 'P';
					board[j+1][i] = 'p';
					return false;
				}
				pawnpos[0] = -1;
				pawnpos[1] = -1;
				return true;
			}
			else
				return false;
		else
		{
			board[j][i] = 'P';
			board[fy][fx] = 'e';
			if ( check(true) )
			{
				board[j][i] = temp;
				board[fy][fx] = 'P';
				return false;
			}
			pawnpos[0] = -1;
			pawnpos[1] = -1;
			return true;
		}
	}
	
	if ( board[fy][fx] == 'p' )
	{
		if ( fx == i )
		{
			if ( board[fy+1][fx] != 'e' )
				return false;
			if ( fy == 1 && j == 3 )
			{
				if ( board[3][fx] != 'e' )
					return false;
				board[3][i] = 'p';
				board[1][i] = 'e';
				if ( check(false) )
				{
					board[3][i] = 'e';
					board[1][i] = 'p';
					return false;
				}
				pawnpos[0] = 3;
				pawnpos[1] = i;
				return true;
			}
			if ( fy+1 != j )
				return false;
			board[j][i] = 'p';
			board[fy][fx] = 'e';
			if ( check(false) )
			{
				board[j][i] = 'e';
				board[fy][fx] = 'p';
				return false;
			}
			pawnpos[0] = -1;
			pawnpos[1] = -1;
			return true;
		}
		if ( !( j == fy+1 && ( fx-i == -1 || fx-i == 1) ) )
			return false;
		if ( board[j][i] == 'e' )
			if ( pawnpos[0] == j-1 && pawnpos[1] == i)
			{
				board[j][i] = 'p';
				board[fy][fx] = 'e';
				board[j-1][i] = 'e';
				if ( check(false) )
				{
					board[j][i] = 'e';
					board[fy][fx] = 'p';
					board[j-1][i] = 'P';
					return false;
				}
				pawnpos[0] = -1;
				pawnpos[1] = -1;
				return true;
			}
			else
				return false;
		else
		{
			board[j][i] = 'p';
			board[fy][fx] = 'e';
			if ( check(false) )
			{
				board[j][i] = temp;
				board[fy][fx] = 'p';
				return false;
			}
			pawnpos[0] = -1;
			pawnpos[1] = -1;
			return true;
		}
	}
	
	if ( board[fy][fx] == 'N')
	{
		if (fy-j == 2 || fy-j == -2)
			if(fx-i == 1 || fx-i == -1)
			{
				board[j][i] = 'N';
				board[fy][fx] = 'e';
				if ( check(true) )
				{
					board[j][i] = temp;
					board[fy][fx] = 'N';
					return false;
				}
				pawnpos[0] = -1;
				pawnpos[1] = -1;
				return true;
			}
			else
				return false;
		else if(fy-j == 1 || fy-j == -1)
			if(fx-i == 2 || fx-i == -2)
			{
				board[j][i] = 'N';
				board[fy][fx] = 'e';
				if ( check(true) )
				{
					board[j][i] = temp;
					board[fy][fx] = 'N';
					return false;
				}
				pawnpos[0] = -1;
				pawnpos[1] = -1;
				return true;
			}
			else
				return false;
		else
			return false;
	}
	
	if ( board[fy][fx] == 'n')
	{
		if (fy-j == 2 || fy-j == -2)
			if(fx-i == 1 || fx-i == -1)
			{
				board[j][i] = 'n';
				board[fy][fx] = 'e';
				if ( check(false) )
				{
					board[j][i] = temp;
					board[fy][fx] = 'n';
					return false;
				}
				pawnpos[0] = -1;
				pawnpos[1] = -1;
				return true;
			}
			else
				return false;
		else if(fy-j == 1 || fy-j == -1)
			if(fx-i == 2 || fx-i == -2)
			{
				board[j][i] = 'n';
				board[fy][fx] = 'e';
				if ( check(false) )
				{
					board[j][i] = temp;
					board[fy][fx] = 'n';
					return false;
				}
				pawnpos[0] = -1;
				pawnpos[1] = -1;
				return true;
			}
			else
				return false;
		else
			return false;
	}
	
	if ( board[fy][fx] == 'B')
	{
		int xx,yy;
		if ( fy-j == fx-i )
		{
			yy = j;
			for( xx = i + 1 ; xx < fx ; xx++)
			{
				yy++;
				if (board[yy][xx] != 'e')
					return false;
			}
			yy = fy;
			for( xx = fx + 1 ; xx < i ; xx++)
			{
				yy++;
				if (board[yy][xx] != 'e')
					return false;
			}
		}
		else if ( fy-j == i-fx )
		{
			yy = fy;
			for( xx = fx + 1 ; xx < i ; xx++)
			{
				yy--;
				if ( board[yy][xx] != 'e' )
					return false;
			}
			yy = j;
			for( xx = i + 1 ; xx < fx ; xx++)
			{
				yy--;
				if ( board[yy][xx] != 'e')
					return false;
			}
		}
		else
			return false;
		board[j][i] = 'B';
		board[fy][fx] = 'e';
		if ( check(true) )
		{
			board[j][i] = temp;
			board[fy][fx] = 'B';
			return false;
		}
		pawnpos[0] = -1;
		pawnpos[1] = -1;
		return true;
	}
	
	if ( board[fy][fx] == 'b')
	{
		int xx,yy;
		if ( fy-j == fx-i )
		{
			yy = j;
			for( xx = i + 1 ; xx < fx ; xx++)
			{
				yy++;
				if (board[yy][xx] != 'e')
					return false;
			}
			yy = fy;
			for( xx = fx + 1 ; xx < i ; xx++)
			{
				yy++;
				if (board[yy][xx] != 'e')
					return false;
			}
		}
		else if (fy-j == i-fx )
		{
			yy = fy;
			for( xx = fx + 1 ; xx < i ; xx++)
			{
				yy--;
				if (board[yy][xx] != 'e')
					return false;
			}
			yy = j;
			for( xx = i + 1 ; xx < fx ; xx++)
			{
				yy--;
				if (board[yy][xx] != 'e')
					return false;
			}
		}
		else
			return false;
		board[j][i] = 'b';
		board[fy][fx] = 'e';
		if ( check(false) )
		{
			board[j][i] = temp;
			board[fy][fx] = 'b';
			return false;
		}
		pawnpos[0] = -1;
		pawnpos[1] = -1;
		return true;
	}
	
	if ( board[fy][fx] == 'R')
	{
		int k;
		if (fx == i)
		{
			for(k = fy + 1 ; k < j ; k++)
				if (board[k][fx] != 'e')
					return false;
			for(k = j + 1 ; k < fy ; k++)
				if (board[k][fx] != 'e')
					return false;
		}
		else if (fy == j)
		{
			for(k = fx + 1 ; k < i ; k++)
				if (board[fy][k] != 'e')
					return false;
			for(k = i + 1 ; k < fx ; k++)
				if (board[fy][k] != 'e')
					return false;
		}
		else
			return false;		
		board[j][i] = 'R';
		board[fy][fx] = 'e';
		if ( check(true) )
		{
			board[j][i] = temp;
			board[fy][fx] = 'R';
			return false;
		}
		pawnpos[0] = -1;
		pawnpos[1] = -1;
		if ( fx == 7 && fy == 7)
			wk = true;
		return true;
	}
	
	if ( board[fy][fx] == 'r')
	{
		int k;
		if (fx == i)
		{
			for(k = fy + 1 ; k < j ; k++)
				if (board[k][fx] != 'e')
					return false;
			for(k = j + 1 ; k < fy ; k++)
				if (board[k][fx] != 'e')
					return false;
		}
		else if (fy == j)
		{
			for(k = fx + 1 ; k < i ; k++)
				if (board[fy][k] != 'e')
					return false;
			for(k = i + 1 ; k < fx ; k++)
				if (board[fy][k] != 'e')
					return false;
		}
		else
			return false;
		board[j][i] = 'r';
		board[fy][fx] = 'e';
		if ( check(false) )
		{
			board[j][i] = temp;
			board[fy][fx] = 'r';
			return false;
		}
		pawnpos[0] = -1;
		pawnpos[1] = -1;
		if ( fx == 7 && fy == 0)
			bk = true;
		return true;
	}
	
	if (board[fy][fx] == 'Q')
	{
		board[fy][fx] = 'B';
		if(move(i,j,fx,fy))
		{
			board[j][i] = 'Q';
			return true;
		}
		board[fy][fx] = 'R';
		bool done = move(i,j,fx,fy);
		if(done)
		{
			board[j][i] = 'Q';
			return true;
		}
		board[fy][fx] = 'Q';
		return false;
	}
	
	board[fy][fx] = 'b';
	if(move(i,j,fx,fy))
	{
		board[j][i] = 'q';
		return true;
	}
	board[fy][fx] = 'r';
	bool done = move(i,j,fx,fy);
	if(done)
	{
		board[j][i] = 'q';
		return true;
	}
	board[fy][fx] = 'q';
	return false;

}

void render( int fx , int fy )
{
	//Clear screen
	SDL_RenderClear( gRenderer );
	
	SDL_Rect bord = { 320 , 40 , 640 , 640 };
	
	//Render texture to screen
	SDL_RenderCopy( gRenderer, Board , NULL, &bord );
	
	int pawn = -1;
	int Pawn = -1;
	
	for(int j = 0 ; j < 8 ; j++)
		for(int i = 0 ; i < 8 ; i++)
		{
			SDL_Rect piece = { 330 + 80*i , 50 + 80*j , 60 , 60 };
			if(board[j][i] == 'r')
				SDL_RenderCopy( gRenderer, brock, NULL, &piece );
			else if(board[j][i] == 'b')
				SDL_RenderCopy( gRenderer, bbishop, NULL, &piece );
			else if(board[j][i] == 'n')
				SDL_RenderCopy( gRenderer, bknight, NULL, &piece );
			else if(board[j][i] == 'q')
				SDL_RenderCopy( gRenderer, bqueen, NULL, &piece );
			else if(board[j][i] == 'k')
				SDL_RenderCopy( gRenderer, bking, NULL, &piece );
			else if(board[j][i] == 'p')
			{
				SDL_RenderCopy( gRenderer, bpawn, NULL, &piece );
				if ( j == 7)
					pawn = i;
			}
			
			else if(board[j][i] == 'R')
				SDL_RenderCopy( gRenderer, wrock, NULL, &piece );
			else if(board[j][i] == 'B')
				SDL_RenderCopy( gRenderer, wbishop, NULL, &piece );
			else if(board[j][i] == 'N')
				SDL_RenderCopy( gRenderer, wknight, NULL, &piece );
			else if(board[j][i] == 'Q')
				SDL_RenderCopy( gRenderer, wqueen, NULL, &piece );
			else if(board[j][i] == 'K')
				SDL_RenderCopy( gRenderer, wking, NULL, &piece );
			else if(board[j][i] == 'P')
				{
				SDL_RenderCopy( gRenderer, wpawn, NULL, &piece );
				if ( j == 0)
					Pawn = i;
			}
			
		}
	
	SDL_Rect cnst = {10,600,300,47};
	SDL_RenderCopy( gRenderer, Restart, NULL, &cnst );
	cnst = {10,40,302,62};
	SDL_RenderCopy( gRenderer, change, NULL, &cnst );
	cnst = {980,580,152,48};
	SDL_RenderCopy( gRenderer, Turn, NULL, &cnst );
	
	SDL_Rect rect;
	
	if (end == 's' || end == 'S')
	{
		rect = {70 ,200 ,181 ,150 };
		SDL_RenderCopy( gRenderer, draw, NULL, &rect );
	}
	else if (end == 'b')
	{
		rect = {20 ,200 ,285 ,151 };
		SDL_RenderCopy( gRenderer, black, NULL, &rect );
	}
	else if (end == 'w')
	{
		rect = {20 ,200 ,286 ,151 };
		SDL_RenderCopy( gRenderer, white, NULL, &rect );
	}
	
	SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0 );
	
	if ( check(true) )
	{
		rect = { 322+80*X , 42+80*Y , 76 , 76};
		SDL_RenderDrawRect( gRenderer, &rect );
	}
	if ( check(false) )
	{
		rect = { 322+80*x , 42+80*y , 76 , 76};
		SDL_RenderDrawRect( gRenderer, &rect );
	}
	
	if ( clicked )
	{
		rect = { 322+80*fx , 42+80*fy , 76 , 76};
		SDL_SetRenderDrawColor( gRenderer, 0, 205, 255, 0 );
		SDL_RenderDrawRect( gRenderer, &rect );
		
		SDL_SetRenderDrawColor( gRenderer, 55, 0, 245, 0 );
		
		int XX = X;
		int YY = Y;
		int xx = x;
		int yy = y;
		int pawnp[2];
		pawnp[0] = pawnpos[0];
		pawnp[1] = pawnpos[1];
		bool Wk = wk;
		bool Bk = bk;
		char brd[8][8];
		int ii,jj;
		for( jj = 0 ; jj < 8 ; jj++ )
			for( ii = 0 ; ii < 8 ; ii++ )
				brd[jj][ii] = board[jj][ii];
		
		if (board[fy][fx] > 'Z')
			for ( int j = 0 ; j < 8 ; j++)
				for ( int i = 0 ; i < 8 ; i++)
				{
					if ( board[j][i] < 'Z' || board[j][i] == 'e' )
					{
						if ( move(i,j,fx,fy) )
						{
							if ( brd[j][i] != 'e' )
							{
								rect = { 322+80*i , 42+80*j , 76 , 76};
								SDL_RenderDrawRect( gRenderer, &rect );
							}
							else
							{
								rect = { 355+80*i , 75+80*j , 10 , 10};
								SDL_RenderFillRect( gRenderer, &rect );
							}
							pawnpos[0] = pawnp[0];
							pawnpos[1] = pawnp[1];
							for( jj = 0 ; jj < 8 ; jj++ )
								for( ii = 0 ; ii < 8 ; ii++ )
									board[jj][ii] = brd[jj][ii];
							bk = Bk;
							y = yy;
							x = xx;
						}
					}
				}
		
		else
			for ( int j = 0 ; j < 8 ; j++)
				for ( int i = 0 ; i < 8 ; i++)
					if ( board[j][i] > 'Z' )
					{
						if ( move(i,j,fx,fy) )
						{
							if ( brd[j][i] != 'e' )
							{
								rect = { 322+80*i , 42+80*j , 76 , 76};
								SDL_RenderDrawRect( gRenderer, &rect );
							}
							else
							{
								rect = { 355+80*i , 75+80*j , 10 , 10};
								SDL_RenderFillRect( gRenderer, &rect );
							}
							pawnpos[0] = pawnp[0];
							pawnpos[1] = pawnp[1];
							for( jj = 0 ; jj < 8 ; jj++ )
								for( ii = 0 ; ii < 8 ; ii++ )
									board[jj][ii] = brd[jj][ii];
							wk = Wk;
							Y = YY;
							X = XX;
						}
					}
	
		pawnpos[0] = pawnp[0];
		pawnpos[1] = pawnp[1];
		for( int j = 0 ; j < 8 ; j++ )
			for( int i = 0 ; i < 8 ; i++ )
				board[j][i]	= brd[j][i];
		wk = Wk;
		Y = YY;
		X = XX;
		bk = Bk;
		y = yy;
		x = xx;
	}
	
	SDL_Event e;
	int i,j;
		
	if (pawn != -1)
	{
		SDL_Rect ch = {962,42,314,68};
		SDL_RenderCopy( gRenderer, choose, NULL, &ch );
		
		ch = {1000,140,100,100};
		SDL_RenderCopy( gRenderer, bqueen, NULL, &ch );
		ch = {1140,140,100,100};
		SDL_RenderCopy( gRenderer, brock, NULL, &ch );
		ch = {1140,370,100,100};
		SDL_RenderCopy( gRenderer, bknight, NULL, &ch );
		ch = {1000,370,100,100};
		SDL_RenderCopy( gRenderer, bbishop, NULL, &ch );
		SDL_RenderPresent( gRenderer );
		bool quit = false;
		while( !quit )
		{
			SDL_PollEvent( &e );
			if(e.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&i,&j);
				if( j > 600 && j < 647 && i > 10 && i < 310 )
				{
					quit = true;
					restart();
					render(0,0);
				}
				if( j > 40 && j < 102 && i > 10 && i < 312 )
				{
					quit = true;
					if ( Board == Board1 )
						Board = Board2;
					else
						Board = Board1;
					render(0,0);
				}
				if ( i > 1000 && i < 1100 )
				{
					if ( j > 140 && j < 240 )
					{
						quit = true;
						board[7][pawn] = 'q';
						render(0,0);
					}
					else if ( j > 370 && j < 470 )
					{
						quit = true;
						board[7][pawn] = 'b';
						render(0,0);
					}
				}
				else if ( i > 1140 && i < 1240 )
					if ( j > 140 && j < 240 )
					{
						quit = true;
						board[7][pawn] = 'r';
						render(0,0);
					}
					else if ( j > 370 && j < 470 )
					{
						quit = true;
						board[7][pawn] = 'n';
						render(0,0);
					}
			}
		}
	}
	
	if (Pawn != -1)
	{
		SDL_Rect ch = {962,42,314,68};
		SDL_RenderCopy( gRenderer, choose, NULL, &ch );
		
		ch = {1000,140,100,100};
		SDL_RenderCopy( gRenderer, wqueen, NULL, &ch );
		ch = {1140,140,100,100};
		SDL_RenderCopy( gRenderer, wrock, NULL, &ch );
		ch = {1140,370,100,100};
		SDL_RenderCopy( gRenderer, wknight, NULL, &ch );
		ch = {1000,370,100,100};
		SDL_RenderCopy( gRenderer, wbishop, NULL, &ch );
		SDL_RenderPresent( gRenderer );
		bool quit = false;
		while( !quit )
		{
			SDL_PollEvent( &e );
			if(e.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&i,&j);
				if( j > 600 && j < 647 && i > 10 && i < 310 )
				{
					quit = true;
					restart();
					render(0,0);
				}
				if( j > 40 && j < 102 && i > 10 && i < 312 )
				{
					quit = true;
					if ( Board == Board1 )
						Board = Board2;
					else
						Board = Board1;
					render(0,0);
				}
				if ( i > 1000 && i < 1075 )
				{
					if ( j > 140 && j < 245 )
					{
						quit = true;
						board[0][Pawn] = 'Q';
						render(0,0);
					}
					else if ( j > 370 && j < 475 )
					{
						quit = true;
						board[0][Pawn] = 'B';
						render(0,0);
					}
				}
				else if ( i > 1120 && i < 1195 )
					if ( j > 140 && j < 245 )
					{
						quit = true;
						board[0][Pawn] = 'R';
						render(0,0);
					}
					else if ( j > 370 && j < 475 )
					{
						quit = true;
						board[0][Pawn] = 'N';
						render(0,0);
					}
			}
		}
	}
	
	rect = { 1160 , 580 , 50 , 50};
	SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
	
	if (turn)
		SDL_RenderDrawRect( gRenderer, &rect );
	else
		SDL_RenderFillRect( gRenderer, &rect );
	
	SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0 );
	
	//Update screen
	SDL_RenderPresent( gRenderer );
}


bool stalemate(bool color)
{
	int XX = X;
	int YY = Y;
	int xx = x;
	int yy = y;
	int pawnp[2];
	pawnp[0] = pawnpos[0];
	pawnp[1] = pawnpos[1];
	bool Wk = wk;
	bool Bk = bk;
	char brd[8][8];
	
	int i,j,i2,j2;
	for( j = 0 ; j < 8 ; j++ )
		for( i = 0 ; i < 8 ; i++ )
			brd[j][i] = board[j][i];
	
	if(color)
	{
		for( j = 0 ; j < 8 ; j++ )
			for( i = 0 ; i < 8 ; i++ )
				for( j2 = 0 ; j2 < 8 ; j2++ )
					for( i2 = 0 ; i2 < 8 ; i2++ )
						if ( board[j2][i2] > 'Z' && board[j][i] < 'Z' )
							if ( move(i2,j2,i,j) )
							{
								for( j = 0 ; j < 8 ; j++ )
									for( i = 0 ; i < 8 ; i++ )
										board[j][i]	= brd[j][i];
								wk = Wk;
								Y = YY;
								X = XX;
								pawnpos[0] = pawnp[0];
								pawnpos[1] = pawnp[1];
								return false;
							}
		return true;
	}
	for( j = 0 ; j < 8 ; j++ )
		for( i = 0 ; i < 8 ; i++ )
			for( j2 = 0 ; j2 < 8 ; j2++ )
				for( i2 = 0 ; i2 < 8 ; i2++ )
					if ( ( board[j2][i2] < 'Z' || board[j2][i2] == 'e' )  && board[j][i] > 'Z' && board[j][i] != 'e' )
						if ( move(i2,j2,i,j) )
						{
							for( j = 0 ; j < 8 ; j++ )
								for( i = 0 ; i < 8 ; i++ )
									board[j][i]	= brd[j][i];
							bk = Bk;
							y = yy;
							x = xx;
							pawnpos[0] = pawnp[0];
							pawnpos[1] = pawnp[1];
							return false;
						}
	return true;
}

int main( int argc, char* args[] )
{
	int i,j,fx,fy;
	restart();
	
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			render(0 , 0);
			
			//While application is running
			while( !quit )
			{
				if(stalemate(turn))
					if(turn)
						if ( check(true) )
							end = 'b';
						else
							end = 's';
					else
						if ( check(false) )
							end = 'w';
						else
							end = 'S';
				
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
						quit = true;
					if(e.type == SDL_MOUSEBUTTONUP)
					{
						SDL_GetMouseState(&i,&j);
						if( j > 600 && j < 647 && i > 10 && i < 310 )
							restart();
						if( j > 40 && j < 102 && i > 10 && i < 312 )
							if ( Board == Board1 )
								Board = Board2;
							else
								Board = Board1;
						i = i - 320;
						j = j - 40;
						if ( i > 0 )
							i /= 80;
						if ( j > 0 )
							j /= 80;
						if( i < 8 && i >= 0 && j < 8 && j >= 0 )
						{
							if( clicked )
							{
								if( turn && board[j][i] < 'Z' && board[j][i] > 'A')
								{
									fx = i;
									fy = j;
								}
								else if( !turn && board[j][i] < 'z' && board[j][i] > 'a' && board[j][i] != 'e')
								{
									fx = i;
									fy = j;
								}
								else
								{
									bool s = move(i,j,fx,fy);
									clicked = false;
									if ( s )
									{
										if ( turn )
											turn = false;
										else
											turn = true;
									}
								}
							}
							else if( turn )
							{
								if( board[j][i] < 'Z' && board[j][i] > 'A' )
								{
									clicked = true;
									fx = i;
									fy = j;
								}
							}
							else if( board[j][i] < 'z' && board[j][i] > 'a' && board[j][i] != 'e' )
							{
								clicked = true;
								fx = i;
								fy = j;
							}
						}
					}
				}
				render(fx , fy);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
