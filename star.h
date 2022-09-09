//The number of rows in the frame buffer
#define MaxRow  31

//The number of columns in the frame buffer
#define MaxCol 61

//The maximum number of stars in a 'completely filled' universe
#define MaxStar 189

//The maximum number of star pairs that can be named in a universe
#define MaxPair 945

//The length of the universe in light years
#define MaxX 60

//The width of the universe in light years
#define MaxY 30

//A structure to store data about a star
typedef struct
{
  //A unique number (identifier) for this star. Identifiers start at 0.
	int id;
  //The star's x coordinate in the universe
	double x;
  //The star's y coordinate in the universe
	double y;				
	char name[30];
	int named;
} Star;

//A structure to store data about a pair of named stars
typedef struct
{
  //pointer to the first star in this pair
	Star* h;
  //pointer to the second star in this pair
	Star* w;		
  //The distance between the two stars of this pair
	double d;					
} Pair;

//array of stars
extern Star *stars[MaxStar];
//array of named pairs of stars
extern Pair *pairs[MaxPair];
//number of stars in the universe
extern int numStars;
//number of named star pairs
extern int numPairs;

//prototypes of the functions that we need to implement
//the functions themselves are in the graph.c, logic.c, and main.c files

//graphics functions
void clearBuffer ();
void plot (int row, int col, char c);
char peek (int row, int col);
void writeAt (int row, int col, char* text);
void showBuffer ();
//program logic functions
Star* findStarByXY(double x, double y, double tolerance);
int bigBang (int n_stars);
double pointDistance (double x1, double y1, double x2, double y2);
Pair* closestPair ();
int nameStar (Star *s, char* first_name, char* sur_name);
Pair* findPairByName (char* name);
int saveUniverse ();
int loadUniverse();
//main interface functions
void printStar (Star*);
void listStars ();
void listPairs ();
void drawUniverse ();
void tagPair (Pair* p);
