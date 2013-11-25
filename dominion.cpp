#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;
#include <vector>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <string.h>
#include <math.h>
//#include"sound.h"
#include <assert.h>
#include <stdlib.h>
#include "texture.h"
#include "time.h"
#include "card.h"
#include <sys/time.h>

// Integration
uint num_players;
player * allplayers;
player * currentplayer;
int actions;
int money;
int extramoney;
int buys;
uint turncounter = 0;

// Sound files
//FMOD::Sound *start_screen, *main_screenS;

// random cards (not subclasses of card)
char trash[] = "images/trash.pam";
double trashPos[] = {311, 58,   118, 180 };
int trashC;
char cardback[] = "images/cardback.pam";
double cardbackPos[] = { 38, 605, 118, 180 };
double discardPos[] = { 197, 605, 118, 180 };
int cardbackC;

//================================== SCREEN INFORMATION =======================

//--------------------------- start screen -------------------------------

int startWIDTH = 700;
int startHEIGHT = 700;
char startbackground[] = "images/load_screen.pam";
// New Game button info
char newgameStatic[] = "images/new_game_static.pam";
char newgameHover[] = "images/new_game_hover.pam";
char newgameClicked[] = "images/new_game_clicked.pam";
bool newgamePressed = false, overnew = false;
double newgamePos[] = { 225, 275,   250, 90 }; // upper left coord, width,height
// Rules button info
char rulesStatic[] = "images/rules_static.pam";
char rulesHover[] = "images/rules_hover.pam";
char rulesClicked[] = "images/rules_clicked.pam";
bool rules1Pressed = false, overrules1 = false;
double rulesStartPos[] = { 225, 400,  250, 90 };


//-------------------------- player info screen --------------------------
// Player info screen
int pInfoWIDTH = 700;
int pInfoHEIGHT = 700;
char pInfobackground[] = "images/player_info_screen.pam";
// continue button
char continueStatic[] = "images/continue_static.pam";
char continueHover[] = "images/continue_hover.pam";
char continueClicked[] = "images/continue_clicked.pam";
bool continuePressed = false, overcontinue = false;
double continuePos[] = { 480, 22, 200, 80 };
// textbox1 info
bool overTextBox1 = false, TextBox1Pressed = false;
string textInBox1 = "Player 1";
double textBox1[] = { 175, 480,  175, 40 };
const unsigned int MAX_CHARS_IN_TEXTBOX = 18;
// textbox2 info
bool overTextBox2 = false, TextBox2Pressed = false;
string textInBox2 = "Player 2";
double textBox2[] = { 175, 585,  175, 40 };
// textbox3 info
bool overTextBox3 = false, TextBox3Pressed = false;
string textInBox3 = "Player 3";
double textBox3[] = { 500, 480,  175, 40 };
//textbox4 info
bool overTextBox4 = false, TextBox4Pressed = false;
string textInBox4 = "Player 4";
double textBox4[] = { 500, 585,  175, 40 };
// number buttons
// two
char twoStatic[] = "images/two_static.pam";
char twoHover[] = "images/two_hover.pam";
char twoClicked[] = "images/two_clicked.pam";
bool twoPressed = true, overtwo = false;
double twoPos[] = { 75, 225, 150, 70 };
// three
char threeStatic[] = "images/three_static.pam";
char threeHover[] = "images/three_hover.pam";
char threeClicked[] = "images/three_clicked.pam";
bool threePressed = false, overthree = false;
double threePos[] = { 275, 225, 150, 70 };
// four
char fourStatic[] = "images/four_static.pam";
char fourHover[] = "images/four_hover.pam";
char fourClicked[] = "images/four_clicked.pam";
bool fourPressed = false, overfour = false;
double fourPos[] = { 475, 225, 150, 70 };

//--------------------------- card select screen -----------------------------

// Card select screen
int cSelectWIDTH = 1280;
int cSelectHEIGHT = 800;
char cSelectbackground[] = "images/card_select_screen.pam";
// random button
char randomStatic[] = "images/random_static.pam";
char randomHover[] = "images/random_hover.pam";
char randomClicked[] = "images/random_clicked.pam";
bool randomPressed = false, overrandom = false;
double randomPos[] = { 965, 16, 270, 82 };
// start game button
char startStatic[] = "images/start_game_static.pam";
char startHover[] = "images/start_game_hover.pam";
char startClicked[] = "images/start_game_clicked.pam";
bool startPressed = false, overstart = false;
double startPos[] = { 965, 104, 270, 82 };
// red card border info
char cardBorder[] = "images/border.pam";

//----------------------------- buy screen --------------------------------

// buy screen
int buyWIDTH = 1280;
int buyHEIGHT = 800;
char buybackground[] = "images/buy_screen.pam";
// end turn button
char endturnStatic[] = "images/end_turn_static.pam";
char endturnHover[] = "images/end_turn_hover.pam";
char endturnClicked[] = "images/end_turn_clicked.pam";
bool endturnPressed = false, overend = false;
double endturnPos[] = { 980, 22,  240,90  };

//--------------------------- main (gameplay) screen ----------------------

// main (gameplay) screen
int mainWIDTH = 1280;
int mainHEIGHT = 800;
char mainbackground[] = "images/main_screen.pam";
// Buy button info
char buyStatic[] = "images/buy_static.pam";
char buyHover[] = "images/buy_hover.pam";
char buyClicked[] = "images/buy_clicked.pam";
bool buyPressed = false, overbuy = false;
double buyPos[] = { 300, 285,  170,75 };
// Rules button
bool rules2Pressed = false, overrules2 = false;
double rulesMainPos[] = { 1070, 8, 140, 55 };

//----------------------------- rules screen -----------------------------

// Rules screen info
int rulesWIDTH = 800;
int rulesHEIGHT = 800;
char rulesbackground[] = "images/rules_screen_1.pam";
char rulesbackground2[] = "images/rules_screen_2.pam";
char rulesbackground3[] = "images/rules_screen_3.pam";
// Next button
char nextStatic[] = "images/next_static.pam";
char nextHover[] = "images/next_hover.pam";
char nextClicked[] = "images/next_clicked.pam";
bool nextPressed = false, overNext = false;
double nextPos[] = { 577, 15, 200, 85 };
// Back button
char backStatic[] = "images/back_static.pam";
char backHover[] = "images/back_hover.pam";
char backClicked[] = "images/back_clicked.pam";
bool backPressed = false, overBack = false;
double backPos[] = { 23, 15, 200, 85 };
// Return button
char returnStatic[] = "images/return_static.pam";
char returnHover[] = "images/return_hover.pam";
char returnClicked[] = "images/return_clicked.pam";
bool returnPressed = false, overReturn = false;
double returnPos[] = { 23, 15, 200, 85 };
bool return2Pressed = false, overReturn2 = false;
double return2Pos[] = { 577, 15, 200, 85 };

// rules window identifier
bool rules_identifier;

//---------------------------- final screen ----------------------------------

// Final screen info
int finalWIDTH = 800;
int finalHEIGHT = 800;
char finalbackground[] = "images/final_screen.pam";
// background overlays
char confetti1[] = "images/confetti1.pam";
char confetti2[] = "images/confetti2.pam";
// Done button
char quitStatic[] = "images/quit_static.pam";
char quitHover[] = "images/quit_hover.pam";
char quitClicked[] = "images/quit_clicked.pam";
bool quitPressed = false, overQuit = false;
double quitPos[] = { 555, 515, 180, 80 };

//---------------------------- texture ids ------------------------------------

// currentscene stores info about the current state of the rules window
int currentscene = 0;

// window info: this stores the id of a window when created, and we set
//   this id to zero when a window is destroyed
int startWindowID = 0, mainWindowID = 0, buyWindowID = 0, pInfoWindowID = 0, cSelectWindowID = 0, rules1WindowID = 0, rules2WindowID = 0, rules3WindowID = 0, finalWindowID = 0;

int * WindowID[] = { &startWindowID, &mainWindowID, &buyWindowID, &pInfoWindowID, &cSelectWindowID, &rules1WindowID, &rules2WindowID, &rules3WindowID, &finalWindowID };

// red card border ID
int card_border;

// backgrounds
int start_bg, main_bg, buy_bg, pInfo_bg, cSelect_bg, rules_bg, rules2_bg, rules3_bg, final_bg;

// final screen background overlay IDs
int confetti_1, confetti_2;

// different ids for buttons (if static, hovered over, or clicked)
int newgameS, newgameH, newgameC, loadgameS, loadgameH, loadgameC, buyS, buyH, buyC, optS, optH, optC, endS, endH, endC, contS, contH, contC, randS, randH, randC, startS, startH, startC, twoS, twoH, twoC, threeS, threeH, threeC, fourS, fourH, fourC, rulesS, rulesH, rulesC, returnS, returnH, returnC, nextS, nextH, nextC, backS, backH, backC, quitS, quitH, quitC;

// array of all these ids ( size is 48 )
int * buttonsID[] = { &newgameS, &newgameH, &newgameC, &loadgameS, &loadgameH, &loadgameC, &buyS, &buyH, &buyC, &optS, &optH, &optC, &endS, &endH, &endC, &contS, &contH, &contC, &randS, &randH, &randC, &startS, &startH, &startC, &twoS, &twoH, &twoC, &threeS, &threeH, &threeC, &fourS, &fourH, &fourC, &rulesS, &rulesH, &rulesC, &returnS, &returnH, &returnC, &nextS, &nextH, &nextC, &backS, &backH, &backC, &quitS, &quitH, &quitC };

//position of buttons ( size is 18 )
double * Buttons[] = { newgamePos, rulesStartPos, buyPos, endturnPos, continuePos, randomPos, startPos, textBox1, textBox2, twoPos, threePos, fourPos, returnPos, rulesMainPos, nextPos, backPos, return2Pos, quitPos };
//size of array (UPDATE WHEN CHANGING SIZE OF Buttons AND overButton ARRAY)
int Buttons_size = 18;

//array of bools to check if a button is being hovered over ( size is 17 )
bool * overButton[] = { &overnew, &overrules1, &overbuy, &overend, &overcontinue, &overrandom, &overstart, &overTextBox1, &overTextBox2, &overtwo, &overthree, &overfour, &overReturn, &overrules2, &overNext, &overBack, &overReturn2, &overQuit };


//==================================== END SCREEN INFORMATION ===================================


//======================================== CARD INFORMATION ======================================

// confetti
double startTime;
int confetti_height1 = -1600;
int confetti_height2;

// use this bool to check if a card has already been pressed
bool previous = false;

// check if throne room is being used
int throneroomsPlayed = 0;

// check if the user clicked a card to be used in the terminal
bool extracards = false;

// this int keeps track of the location of the card that was clicked
//   if it is one that needs the terminal
int handlocation = 0;

//actionCards holds all of the action cards being used in the game
card ** actionCards [10];

// check current action cards pressed in card select screen
int current_action_cards = 0;

// these doubles are all the positions for the action cards in the main screen
double m1[] = {11, 380, 118, 181};
double m2[] = {138, 380, 118, 181};
double m3[] = {264, 380, 118, 181};
double m4[] = {390, 380, 118, 181};
double m5[] = {516, 380, 118, 181};
double m6[] = {642, 380, 118, 181};
double m7[] = {768, 380, 118, 181};
double m8[] = {895, 380, 118, 181};
double m9[] = {1020, 380, 118, 181};
double m10[] = {1146, 380, 118, 181};

double * game_cards[] = { m1, m2, m3, m4, m5, m6, m7, m8, m9, m10 };

// buy screen

double b1[] = {115, 219, 118, 181};
double b2[] = {286, 219, 118, 181};
double b3[] = {455, 219, 118, 181};
double b4[] = {30, 411, 118, 181};
double b5[] = {201, 411, 118, 181};
double b6[] = {370, 411, 118, 181};
double b7[] = {539, 411, 118, 181};
double b8[] = {115, 604, 118, 181};
double b9[] = {286, 604, 118, 181};
double b10[] = {455, 604, 118, 181};

double * buy_action_cards[] = { b1, b2, b3, b4, b5, b6, b7, b8, b9, b10 };

//======================== END CARD INFORMATION =================

void updatetreasure();
int createNewWindow(const char *windowTitle, int Window); // declare the function
void drawfinalscreen();

//======================== DRAW FUNCTIONS ====================


//----------------------- draw simple stuff -------------------------

// the following function draws a rectangle, given
//   the upper left vertex and the width and height
void drawBox(double x, double y, double width, double height)
{
  glBegin(GL_POLYGON);
    glVertex2f(x, y);  // upper left
    glVertex2f(x, y + height);  // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);  // upper right
  glEnd();
}
void drawBox(double *pos)
{
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}

// the drawText function draws some text at location x, y
//   note:  the text to be drawn is a C-style string!
void drawText(double x, double y, const char *text)
{
  glRasterPos2f( x, y );
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

// the drawNumber function draws a number at location x, y
void drawNumber(double x, double y, double num)
{
  stringstream oss;
  oss << num; oss.flush();
  drawText(x, y, oss.str().c_str());
}


//------------------------ draw windows -------------------------------------

// FIRST WINDOW: draw start screen
void drawStartWindow()
{
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  drawTexture(start_bg,  0,0,    startWIDTH, startHEIGHT);  // texNum, x,y, width, height
  
  // draw the new game button (conditions based on mouse)
  if ( newgamePressed ) drawTexture(newgameC, newgamePos);
  else if ( overnew ) drawTexture(newgameH, newgamePos);
  else drawTexture(newgameS, newgamePos);
  
  //rules button
  if ( rules1Pressed ) drawTexture(rulesC, rulesStartPos);
  else if ( overrules1 ) drawTexture(rulesH, rulesStartPos);
  else drawTexture(rulesS, rulesStartPos);

  // tell the graphics card that we're done-- go ahead and draw!
  //   (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}

// draw the textboxes (supplementary to the player info screen)
void drawtextboxes() 
{
  // draw textbox1
  if (TextBox1Pressed) glColor3f(1,1,1); // color if cursor is overtextbox is white
  else glColor3f(.75, .75, .75); // light gray
  drawBox(textBox1);
  glColor3f(0,0,0); // black
  if ( TextBox1Pressed ) { // draw with the cursor
    string withCursor1(textInBox1);
    withCursor1 += '|';
    drawText( textBox1[0]+5, textBox1[1]+textBox1[3]-15, withCursor1.c_str() );
  }
  else drawText( textBox1[0]+5, textBox1[1]+textBox1[3]-15, textInBox1.c_str() );
  
  // draw textbox2
  if (TextBox2Pressed) glColor3f(1,1,1); // color if cursor is overtextbox is white
  else glColor3f(.75, .75, .75); // light gray
  drawBox(textBox2);
  glColor3f(0,0,0); // black
  if ( TextBox2Pressed ) { // draw with the cursor
    string withCursor2(textInBox2);
    withCursor2 += '|';
    drawText( textBox2[0]+5, textBox2[1]+textBox2[3]-15, withCursor2.c_str() );
  }
  else drawText( textBox2[0]+5, textBox2[1]+textBox2[3]-15, textInBox2.c_str() );
  
  if ( threePressed || fourPressed ) {
    // draw textbox3
    if (TextBox3Pressed) glColor3f(1,1,1); // color if cursor is overtextbox is white
    else glColor3f(.75, .75, .75); // light gray
    drawBox(textBox3);
    glColor3f(0,0,0); // black
    if ( TextBox3Pressed ) { // draw with the cursor
      string withCursor3(textInBox3);
      withCursor3 += '|';
      drawText( textBox3[0]+5, textBox3[1]+textBox3[3]-15, withCursor3.c_str() );
    }
    else drawText( textBox3[0]+5, textBox3[1]+textBox3[3]-15, textInBox3.c_str() );
  }
  if ( fourPressed ) {
    // draw textbox4
    if (TextBox4Pressed) glColor3f(1,1,1); // color if cursor is overtextbox is white
    else glColor3f(.75, .75, .75); // light gray
    drawBox(textBox4);
    glColor3f(0,0,0); // black
    if ( TextBox4Pressed ) { // draw with the cursor
      string withCursor4(textInBox4);
      withCursor4 += '|';
      drawText( textBox4[0]+5, textBox4[1]+textBox4[3]-15, withCursor4.c_str() );
    }
    else drawText( textBox4[0]+5, textBox4[1]+textBox4[3]-15, textInBox4.c_str() );
  }
}

// SECOND WINDOW: draw the player info screen
void drawpInfoWindow()
{
  glutSetWindow(pInfoWindowID);

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw the background
  drawTexture(pInfo_bg, 0, 0,  pInfoWIDTH, pInfoHEIGHT); //texNum, x,y, width, height
  
  drawtextboxes();

  // draw the continue button
  if ( continuePressed ) drawTexture(contC, continuePos);
  else if ( overcontinue ) drawTexture(contH, continuePos);
  else drawTexture(contS, continuePos);

  // draw number buttons
  if ( twoPressed ) drawTexture(twoC, twoPos);
  else if ( overtwo ) drawTexture(twoH, twoPos);
  else drawTexture(twoS, twoPos);

  if ( threePressed ) drawTexture(threeC, threePos);
  else if ( overthree ) drawTexture(threeH, threePos);
  else drawTexture(threeS, threePos);

  if ( fourPressed ) drawTexture(fourC, fourPos);
  else if ( overfour ) drawTexture(fourH, fourPos);
  else drawTexture(fourS, fourPos);
  
  glutSwapBuffers();
}

// card select helper function
void drawcselectcards() 
{
  for ( int i=0; i < 25; ++i ) {
    drawTexture(purplepile.contents[i]->cardID, (purplepile.contents[i]->cSelectScreenPos));
  }
  for ( int i=0; i < 25; ++i ) {
    if ( purplepile.contents[i]->overcard && current_action_cards < 10){ 
      if ( purplepile.contents[i]->cSelectScreenPos[0] == 22 ){
	drawTexture(purplepile.contents[i]->cardID, purplepile.contents[i]->cSelectScreenPos[0] - 22, purplepile.contents[i]->cSelectScreenPos[1] - 110, 200, 300);
	if ( purplepile.contents[i]->cSelectScreenPos[1] == 6 )
	  drawTexture(purplepile.contents[i]->cardID, purplepile.contents[i]->cSelectScreenPos[0] - 22, purplepile.contents[i]->cSelectScreenPos[1] - 5, 200, 300);
      }
      else if ( purplepile.contents[i]->cSelectScreenPos[0] == 1135 )
	drawTexture(purplepile.contents[i]->cardID, purplepile.contents[i]->cSelectScreenPos[0] - 55, purplepile.contents[i]->cSelectScreenPos[1] - 110, 200, 300);
      else
	drawTexture(purplepile.contents[i]->cardID, purplepile.contents[i]->cSelectScreenPos[0] - 42, purplepile.contents[i]->cSelectScreenPos[1] - 110, 200, 300);
    }
  }
}

void drawhighlightedcards()
{
  for ( int i=0; i < current_action_cards; ++i ) {
    drawTexture( card_border, (*(actionCards[i]))->cSelectScreenPos[0] - 4, (*(actionCards[i]))->cSelectScreenPos[1] - 4, 126, 189);
  }
}
// THIRD WINDOW: draw the card select screen
void drawcSelectWindow()
{
  glutSetWindow(cSelectWindowID);

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw background
  drawTexture(cSelect_bg, 0,0, cSelectWIDTH, cSelectHEIGHT);
  // random button
  if ( randomPressed ) drawTexture(randC, randomPos);
  else if ( overrandom ) drawTexture(randH, randomPos);
  else drawTexture(randS, randomPos);
  // start game button
  if ( startPressed ) drawTexture(startC, startPos);
  else if ( overstart ) drawTexture(startH, startPos);
  else drawTexture(startS, startPos);
  
  drawhighlightedcards();
  drawcselectcards();

  glutSwapBuffers();
}

bool done_once = 0;

// this displays the cards of the current player 
// (main window helper function)
void displaycards( player * &p) {
  // first load the textures of each card and set the number of cards to zero with setNumcards
if (!done_once) {

  for ( uint i=0; i < p->hand->size; i++){
    p->hand->contents[i]->cardID = loadTexture(p->hand->contents[i]->picture);
  }
}
  for ( uint i=0; i < p->hand->size; i++){
    p->hand->contents[i]->setNumcards();
  }  // now check how many of each card a player has
  for ( uint i=0; i < p->hand->size; i++){
    if ( p->hand->contents[i]->getNumcards() == 0 ) {
      drawTexture( p->hand->contents[i]->cardID, p->hand->contents[i]->cardMainScreenPos );
    }
    p->hand->contents[i]->addNumcards();
  }
  for ( uint i=0; i < p->hand->size; i++){
    if ( p->hand->contents[i]->overcard && p->hand->contents[i]->category == ACTION )
	drawTexture( p->hand->contents[i]->cardID, p->hand->contents[i]->cardMainScreenPos[0] - 56, p->hand->contents[i]->cardMainScreenPos[1] - 140, 230, 340);
  }
  
  // draw the top card of the discard pile
  if (!done_once) {
  if ( p->discardpile->size > 0 ){
    p->discardpile->contents[0]->cardID = loadTexture(p->discardpile->contents[0]->picture);
  }
}
  if ( p->discardpile->size > 0 ){
    drawTexture(p->discardpile->contents[0]->cardID, discardPos);
  }
  done_once = 1;
  glColor3f(0,0,0); // black
  // draw the number of each card above it
  for ( uint i=0; i < p->hand->size; i++){
    drawNumber( p->hand->contents[i]->cardMainScreenPos[0] + 54, p->hand->contents[i]->cardMainScreenPos[1] - 8, p->hand->contents[i]->getNumcards());
  }
  // draw the number of cards in the deck and in the discard pile
  if ( p->drawpile->size > 0 )
    drawNumber( cardbackPos[0] + 54, cardbackPos[1] - 8, p->drawpile->size );
  if ( p->discardpile->size > 0 )
    drawNumber( discardPos[0] + 54, discardPos[1] - 8, p->discardpile->size );
}

void update_victory_points() {
  player ** ranking;
  ranking = new player * [num_players];
  for(uint i=0; i < num_players; i++) {
    allplayers[i].victory_point_count();
  }
}

void drawRank() {
  for(uint i=0; i < num_players; i++) {
    drawText( 65, 110 + 60*i, (allplayers[i].name).c_str());
    drawNumber( 200, 110 + 60*i, allplayers[i].total_vps);
  }
}

// FOURTH WINDOW: draw the gameplay screen
void drawMainWindow()
{
  glutSetWindow(mainWindowID);  // this call may not be necessary

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw background
  drawTexture(main_bg, 0,0,  mainWIDTH, mainHEIGHT);//texNum, x,y, width, height
  
  // buy button
  if ( buyPressed ) drawTexture(buyC, buyPos);
  else if ( overbuy ) drawTexture(buyH, buyPos);
  else drawTexture(buyS, buyPos);

  //rules button
  if ( rules2Pressed ) drawTexture(rulesC, rulesMainPos);
  else if ( overrules2 ) drawTexture(rulesH, rulesMainPos);
  else drawTexture(rulesS, rulesMainPos);

  update_victory_points();

  // put their name on the screen
  glColor3f(0,0,0); // black
  drawText( 665, 50, (currentplayer->name).c_str());
  drawNumber( 1135, 127, actions);
  drawNumber( 1135, 218, buys);
  drawNumber( 1135, 297, money);
  drawRank();

  // draw the trash and cardback
  drawTexture( trashC, trashPos);
  drawTexture( cardbackC, cardbackPos);

  displaycards(currentplayer);

  drawText( 455, 210, "If a clicked card remains magnified, go to the terminal!");
  
  // tell the graphics card that we're done-- go ahead and draw!
  //   (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}

// Buy Window Helper Function:

// draw the action and victory/treasure cards
void drawbuycards()
{
  //action cards
  for ( int i=0; i < 10; ++i ) {
    if ( (*(actionCards[i]))->getSupply() > 0 ) {
      glColor3f(0,0,0);
      drawNumber( (*(actionCards[i]))->cardBuyScreenPos[0] + 50, (*(actionCards[i]))->cardBuyScreenPos[1] - 6, (*(actionCards[i]))->getSupply());
      if ( (*(actionCards[i]))->overcard && buys > 0) {
	drawTexture((*(actionCards[i]))->cardID, (*(actionCards[i]))->cardBuyScreenPos[0] - 56, (*(actionCards[i]))->cardBuyScreenPos[1] - 140, 230, 340);
      }
      else 
	drawTexture( (*(actionCards[i]))->cardID, (*(actionCards[i]))->cardBuyScreenPos);
    }
  }
  // treasure and victory cards
  for ( int i=0; i < 6; ++i ) {
    if ( treasurevictorypile.contents[i]->getSupply() > 0 ) {
      glColor3f(0,0,0);
      drawNumber( treasurevictorypile.contents[i]->cardBuyScreenPos[0] + 50, treasurevictorypile.contents[i]->cardBuyScreenPos[1] - 6, treasurevictorypile.contents[i]->getSupply());
      if ( treasurevictorypile.contents[i]->overcard && buys > 0)
	drawTexture(treasurevictorypile.contents[i]->cardID, treasurevictorypile.contents[i]->cardBuyScreenPos[0] - 56, treasurevictorypile.contents[i]->cardBuyScreenPos[1] - 140, 230, 340);
      else
	drawTexture(treasurevictorypile.contents[i]->cardID, treasurevictorypile.contents[i]->cardBuyScreenPos);
    }
  }
}

// FIFTH WINDOW: draw the buy screen
// draw buy window
void drawBuyWindow()
{
  glutSetWindow(buyWindowID);

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  
  drawTexture(buy_bg, 0,0,   buyWIDTH, buyHEIGHT);
  
  // draw the end turn button
  if ( endturnPressed ) drawTexture(endC, endturnPos);
  else if ( overend ) drawTexture(endH, endturnPos);
  else drawTexture(endS, endturnPos);

  // draw cards
  drawbuycards();

  glColor3f(0,0,0);

  drawNumber( 610, 75, money );
  drawNumber( 820, 75, buys );

  glutSwapBuffers();
}

// SIXTH WINDOW: draw the rules screen
void drawRulesWindow1()
{
  glutSetWindow(rules1WindowID);

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw background
  drawTexture(rules_bg, 0,0, rulesWIDTH, rulesHEIGHT);//texNum, x,y, width, height
  // buttons
  if ( returnPressed ) drawTexture(returnC, returnPos);
  else if ( overReturn ) drawTexture(returnH, returnPos);
  else drawTexture(returnS, returnPos);

  if ( nextPressed ) drawTexture(nextC, nextPos);
  else if ( overNext ) drawTexture(nextH, nextPos);
  else drawTexture(nextS, nextPos);

  glutSwapBuffers();
}

// SEVENTH WINDOW: draw the middle rules screens
void drawRulesWindow2()
{
  glutSetWindow(rules2WindowID);

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw background
  drawTexture(rules2_bg, 0,0, rulesWIDTH, rulesHEIGHT); //texNum, x,y, width, height
  // buttons
  if ( backPressed ) drawTexture(backC, backPos);
  else if ( overBack ) drawTexture(backH, backPos);
  else drawTexture(backS, backPos);

  if ( nextPressed ) drawTexture(nextC, nextPos);
  else if ( overNext ) drawTexture(nextH, nextPos);
  else drawTexture(nextS, nextPos);

  glutSwapBuffers();
}

// EIGHTH WINDOW: draw the last rules screen
void drawRulesWindow3()
{
  glutSetWindow(rules3WindowID);

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw background
  drawTexture(rules3_bg, 0,0, rulesWIDTH, rulesHEIGHT); //texNum, x,y, width, height
  // buttons
  if ( backPressed ) drawTexture(backC, backPos);
  else if ( overBack ) drawTexture(backH, backPos);
  else drawTexture(backS, backPos);

  if ( return2Pressed ) drawTexture(returnC, return2Pos);
  else if ( overReturn2 ) drawTexture(returnH, return2Pos);
  else drawTexture(returnS, return2Pos);

  glutSwapBuffers();
}
 
// close the window and finish the program
void exitAll()
{
  if ( startWindowID ) glutDestroyWindow(startWindowID);
  if ( mainWindowID ) glutDestroyWindow(mainWindowID);
  if ( buyWindowID ) glutDestroyWindow(buyWindowID);
  exit(0);
}

void exitWindows()
{
  for (int i = 0; i < 8; ++i ){
    if ( *(WindowID[i]) != 0 ){
      glutDestroyWindow( *(WindowID[i]) );
      *(WindowID[i]) = 0;
    }
  }
}

void drawWinner() {
  int winner = 0;
  int num_winners = 0;
  for (uint i = 0; i < num_players; ++i){
    if ( allplayers[i].total_vps > winner ){
      winner = allplayers[i].total_vps;
    }
  }
  for (uint i = 0; i < num_players; ++i){
    if ( allplayers[i].total_vps == winner )
      ++num_winners;
  }
  for (int j = num_players-1; j >= 0; --j){
    if ( allplayers[j].total_vps == winner ){
      drawText( 365, 350, (allplayers[j].name).c_str());
      break;
    }
  }
}


void drawConfetti()
{
  confetti_height2 = confetti_height1*2;
  drawTexture(confetti_1, 0-((confetti_height1+1800)/8), confetti_height1, 1100, 1600);
  drawTexture(confetti_2, (confetti_height1)/8, confetti_height2-800, 1500, 3200);
}

// LAST WINDOW: draw final screen
void drawFinalWindow()
{
  glutSetWindow(finalWindowID);

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
  drawTexture(final_bg,  0,0,    finalWIDTH, finalHEIGHT);  // texNum, x,y, width, height
  
  // draw the quit button (conditions based on mouse)
  if ( quitPressed ) drawTexture(quitC, quitPos);
  else if ( overQuit ) drawTexture(quitH, quitPos);
  else drawTexture(quitS, quitPos);

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  update_victory_points();

  //draw the winner on the screen
  glColor3f(0,0,0);
  drawWinner();
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

  drawConfetti();

  // tell the graphics card that we're done-- go ahead and draw!
  //   (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}



//=================================== END DRAWING FUNCTIONS =======================================


//----------------------- other random things -----------------------------

// this checks if the current mouse position is on any button
bool onButton(int x, int y, double * name)
{
  return x >= name[0]  && y >= name[1] &&
         x <= name[0] + name[2] &&
         y <= name[1] + name[3];
}

// this function updates the treasure value that should be displayed
//   on the screen
void updatetreasure() {
  money += extramoney;
  for(uint i = 0; i < currentplayer->hand->size; i++) {
    if (currentplayer->hand->contents[i]->category == TREASURE){
      money += ((treasure*)currentplayer->hand->contents[i])->coin;
    }
  }
}

//=================================== MOUSE FUNCTIONS ======================================================

// these mouseCoords functions alter the x and y value of the mouse
//   motion function and attempt to get the resize to work

void mouseCoords2(int &x, int&y, int w2, int h2)
{
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  float ratiox = (float)w/(float)w2;
  float ratioy = (float)h/(float)h2;
  x/=ratiox;
  y/=ratioy;
}

void mouseCoords(int &x, int&y, int window)
{
  if ( window == startWindowID )
    mouseCoords2(x, y, startWIDTH, startHEIGHT);
  else if ( window == pInfoWindowID )
    mouseCoords2(x, y, pInfoWIDTH, pInfoHEIGHT);
  else if ( window == cSelectWindowID )
    mouseCoords2(x, y, cSelectWIDTH, cSelectHEIGHT);
  else if ( window == mainWindowID )
    mouseCoords2(x, y, mainWIDTH, mainHEIGHT);
  else if ( window == buyWindowID )
    mouseCoords2(x, y, buyWIDTH, buyHEIGHT);
  else if ( window == rules1WindowID )
    mouseCoords2(x, y, rulesWIDTH, rulesHEIGHT);
}

//----------------- mouse motion helper functions -----------------------

void motion_buyscreen(int x, int y)
{
  // these are the cards on the buy screen
  for (int i=0; i < 10; ++i ) {
    // make sure we've made it past the card select screen
    if ( current_action_cards == 10) {
      if ( onButton(x,y, (*(actionCards[i]))->cardBuyScreenPos) && ( money >= (*(actionCards[i]))->cost) && (*(actionCards[i]))->getSupply() > 0 )
	(*(actionCards[i]))->overcard = true;
      else
	(*(actionCards[i]))->overcard = false;
    }
  }
  // these are the treasure and victory cards in the buy screen
  for ( int i=0; i < 6; ++i ) {
    if ( onButton(x,y, treasurevictorypile.contents[i]->cardBuyScreenPos) && ( money >= treasurevictorypile.contents[i]->cost ) )
      treasurevictorypile.contents[i]->overcard = true;
    else
      treasurevictorypile.contents[i]->overcard = false;
  }
}

// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
 void mouse_motion(int x, int y)
{
  // change the coordinates if the window size changes
  mouseCoords( x, y, glutGetWindow() );
  // check if the mouse is over any button
  for (int i = 0; i < Buttons_size; ++i){
    if ( onButton(x,y, Buttons[i]) ){
      *(overButton[i]) = true;
    }
    else *(overButton[i]) = false;
  }
  
  // textbox3 and textbox4 are only drawn if the three or four button
  //    is pressed
  if ( onButton(x,y, textBox3) && (threePressed || fourPressed) ) 
    overTextBox3 = true;
  else overTextBox3 = false;
  if ( onButton(x,y, textBox4) && fourPressed ) overTextBox4 = true;
  else overTextBox4 = false;
  
  // these are all the cards in the card select screen
  for (int i=0; i < 25; ++i) {
    if ( onButton(x,y, purplepile.contents[i]->cSelectScreenPos) && (!purplepile.contents[i]->cardPressed)) {
      purplepile.contents[i]->overcard = true;
    }
    else purplepile.contents[i]->overcard = false;
  }
  // buy screen
  if ( glutGetWindow() == buyWindowID )
    motion_buyscreen(x, y);
  // main screen
  if ( glutGetWindow() == mainWindowID ) {
    for ( uint i=0; i < currentplayer->hand->size; ++i ) {
      if ( currentplayer->hand->contents[i]->category == ACTION ) {
	if ( onButton(x,y, currentplayer->hand->contents[i]->cardMainScreenPos) && (actions > 0 || throneroomsPlayed > 0) )
	  currentplayer->hand->contents[i]->overcard = true;
	else
	  currentplayer->hand->contents[i]->overcard = false;
      }
      else currentplayer->hand->contents[i]->overcard = false;
    }
  }

  glutPostRedisplay();
}


// ------------- start screen mouse helper functions ----------

// check what has been pressed
void startmousepressed(int x, int y)
{
  if ( onButton(x,y, newgamePos) ) {
    newgamePressed = true;
  }
  else newgamePressed = false;
  
  if ( onButton(x,y, rulesStartPos) ) {
    rules1Pressed = true;
  }
  else rules1Pressed = false;
}

// creat the player info screen
void createpInfoscreen()
{
  glutInitWindowPosition(0,0); // choosing where to put it (same as the start screen)
  glutInitWindowSize(pInfoWIDTH, pInfoHEIGHT); //size
  pInfoWindowID = createNewWindow("Player Info", 2); // title and number of screen
  glutDisplayFunc(drawpInfoWindow); // assign the display function
  glOrtho(0., pInfoWIDTH-1, pInfoHEIGHT-1, 0., -1.0, 1.0); // set coords
  pInfo_bg = loadTexture(pInfobackground);
  contS = loadTexture(continueStatic);
  contH = loadTexture(continueHover);
  contC = loadTexture(continueClicked);
  twoS = loadTexture(twoStatic);
  twoH = loadTexture(twoHover);
  twoC = loadTexture(twoClicked);
  threeS = loadTexture(threeStatic);
  threeH = loadTexture(threeHover);
  threeC = loadTexture(threeClicked);
  fourS = loadTexture(fourStatic);
  fourH = loadTexture(fourHover);
  fourC = loadTexture(fourClicked);
	  
  glutPostWindowRedisplay(pInfoWindowID);
  glutSetWindow(pInfoWindowID);
}

void createrulesscreen()
{
  rules_identifier = 1;
  glutInitWindowPosition(0,0);
  glutInitWindowSize(rulesWIDTH, rulesHEIGHT); // size
  rules1WindowID = createNewWindow("Rules Screen", 6);
  glutDisplayFunc(drawRulesWindow1);
  glOrtho(0., rulesWIDTH-1, rulesHEIGHT-1, 0., -1.0, 1.0); // set coords
  rules_bg = loadTexture(rulesbackground);
  returnS = loadTexture(returnStatic);
  returnH = loadTexture(returnHover);
  returnC = loadTexture(returnClicked);
  backS = loadTexture(backStatic);
  backH = loadTexture(backHover);
  backC = loadTexture(backClicked);
  nextS = loadTexture(nextStatic);
  nextH = loadTexture(nextHover);
  nextC = loadTexture(nextClicked);
  
  glutPostWindowRedisplay(rules1WindowID);
  glutSetWindow(rules1WindowID);
}

// call this function when the mouse is pressed and released in the start screen
void mouse(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, startWindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse-- do something
      startmousepressed(x,y);
    } 
    else {
      // the user just let go the mouse-- do something
      if ( onButton(x,y, newgamePos) && newgamePressed ) {
	//if the mouse is on the button and it was pressed
	glutDestroyWindow(startWindowID);
	startWindowID = 0; 
	// create Player info screen
	createpInfoscreen();
	
      }
      else if ( onButton(x,y, rulesStartPos) && rules1Pressed ) {
	if ( 0 == rules1WindowID ) {
	  // if the mouse is on the button and it was pressed
	  // create Rules screen
	  createrulesscreen();
	}
      }

      newgamePressed = false;
      rules1Pressed = false;
    }
  }
  else if ( GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}


//--------------- player info mouse helper functions -----------------------

// check what has been pressed/ what should be pressed
//   in the player info screen
void pinfopressed(int x, int y)
{
  if ( onButton(x,y, continuePos) ) {
	continuePressed = true;
      }
      else continuePressed = false;

      if ( onButton(x,y, twoPos) ) {
	twoPressed = true;
	threePressed = false;
	fourPressed = false;
      }
      else if ( threePressed || fourPressed ) twoPressed = false;

      if ( onButton(x,y, threePos) ) {
	threePressed = true;
	twoPressed = false;
	fourPressed = false;
      }
      else if ( twoPressed || fourPressed ) threePressed = false;

      if ( onButton(x,y, fourPos) ) {
	fourPressed = true;
	twoPressed = false;
	threePressed = false;
      }
      else if ( twoPressed || threePressed ) fourPressed = false;
      if ( onButton(x,y, textBox1) ) {
	TextBox1Pressed = true;
	TextBox2Pressed = false;
	TextBox3Pressed = false;
	TextBox4Pressed = false;
      }
      else TextBox1Pressed = false;
      if ( onButton(x,y, textBox2) ) {
	TextBox2Pressed = true;
	TextBox1Pressed = false;
	TextBox3Pressed = false;
	TextBox4Pressed = false;
      }
      else TextBox2Pressed = false;
      if ( onButton(x,y, textBox3) && (threePressed || fourPressed)) {
	TextBox3Pressed = true;
	TextBox1Pressed = false;
	TextBox2Pressed = false;
	TextBox4Pressed = false;
      }
      else TextBox3Pressed = false;
      if ( onButton(x,y, textBox4) && fourPressed) {
	TextBox4Pressed = true;
	TextBox1Pressed = false;
	TextBox2Pressed = false;
	TextBox3Pressed = false;
      }
      else TextBox4Pressed = false;
}

// get the textbox information and set up the game
void textboxinfo()
{
  if ( twoPressed ) {
    num_players = 2;
    allplayers = new player [num_players];
    allplayers[0].name = textInBox1;
    allplayers[1].name = textInBox2;
  }
  else if ( threePressed ) {
    num_players = 3;
    allplayers = new player [num_players];
    allplayers[0].name = textInBox1;
    allplayers[1].name = textInBox2;
    allplayers[2].name = textInBox3;
  }
  else if ( fourPressed ){
    num_players = 4;
    allplayers = new player [num_players];
    allplayers[0].name = textInBox1;
    allplayers[1].name = textInBox2;
    allplayers[2].name = textInBox3;
    allplayers[3].name = textInBox4;
  }
}

// create the card select screen
void createcardselectscreen()
{
  glutInitWindowPosition(0,0); // choose the position
  glutInitWindowSize(cSelectWIDTH, cSelectHEIGHT); // how big
  cSelectWindowID = createNewWindow("Card Select", 3);
  glutDisplayFunc(drawcSelectWindow); // assign function
  glOrtho(0., cSelectWIDTH-1, cSelectHEIGHT-1, 0., -1.0, 1.0); // coords
  cSelect_bg = loadTexture(cSelectbackground);
  randS = loadTexture(randomStatic);
  randH = loadTexture(randomHover);
  randC = loadTexture(randomClicked);
  startS = loadTexture(startStatic);
  startH = loadTexture(startHover);
  startC = loadTexture(startClicked);
  card_border = loadTexture(cardBorder);
  for ( int i=0; i < 25; ++i)
    purplepile.contents[i]->cardID = loadTexture(purplepile.contents[i]->picture);
  //click = loadSoundFile("klick.wav");
      
  glutPostWindowRedisplay(cSelectWindowID);
  glutSetWindow(cSelectWindowID);
}

// PLAYER INFO SCREEN: player info screen mouse function
void mouse2(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, pInfoWindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // user pressed down on the mouse
      // check what was pressed/ what can be pressed
      pinfopressed(x, y);
    }
    else {
      // the user just let go of the mouse
      if ( onButton(x,y, continuePos) && continuePressed && textInBox1 != "" && textInBox2 != "" && textInBox3 != "" && textInBox4 != "") {
	// here we need to make sure that the names are entered, and
	//    then set the names for each player
	textboxinfo();
	  
	// destroy pInfo window
	glutDestroyWindow(pInfoWindowID);
	pInfoWindowID = 0;
	
	// create card select window
	createcardselectscreen();	
      }
      continuePressed = false;
    }
  }
  else if (GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}

//-------------------- card select screen helper functions --------------------

// check what has been pressed
void cardselectpressed(int x, int y)
{
  if ( onButton(x,y, randomPos) ) {
    randomPressed = true;
  }
  else randomPressed = false;
  if ( current_action_cards == 10 && onButton(x,y, startPos) ) {
    startPressed = true;
  }
  else startPressed = false;
  // check all of the action cards
  for ( int i=0; i < 25; ++i ) {
    if ( onButton(x,y, (purplepile.contents[i]->cSelectScreenPos)) 
	 && (not purplepile.contents[i]->cardPressed)) {
      purplepile.contents[i]->cardPressed = true;
      previous = false;
    }
    else if (onButton(x,y, (purplepile.contents[i]->cSelectScreenPos) ) 
	     && purplepile.contents[i]->cardPressed) previous = true;
  }
}

void setupactioncards(int x, int y) {
  for ( int i=0; i < 25; ++i ) {
    while (current_action_cards < 10) {
      if ( onButton(x,y, (purplepile.contents[i]->cSelectScreenPos) ) && (purplepile.contents[i]->cardPressed) && (not previous)) {
	actionCards[current_action_cards] = &(purplepile.contents[i]);
	for ( int n=0; n < 4; ++n ) {
	  (*(actionCards[current_action_cards]))->cardMainScreenPos[n] = (game_cards[current_action_cards])[n];
	  (*(actionCards[current_action_cards]))->cardBuyScreenPos[n] = (buy_action_cards[current_action_cards])[n];
	}
	++current_action_cards;
	previous = false;
	break;
      }
      else
	break;
    }   
  }
}

void creategameplayscreen()
{
  // create the gameplay screen
  glutInitWindowPosition(0,0);  // choose where to put it
  glutInitWindowSize(mainWIDTH,mainHEIGHT); // how big?
  mainWindowID = createNewWindow("Dominion", 4);
  glutDisplayFunc(drawMainWindow); // assign the display function
  glOrtho(0., mainWIDTH-1, mainHEIGHT-1, 0., -1.0, 1.0); // coords
  main_bg = loadTexture(mainbackground);
  buyS = loadTexture(buyStatic); // load the button textures
  buyH = loadTexture(buyHover);
  buyC = loadTexture(buyClicked);
  rulesS = loadTexture(rulesStatic);
  rulesH = loadTexture(rulesHover);
  rulesC = loadTexture(rulesClicked);
  trashC = loadTexture(trash);
  cardbackC = loadTexture(cardback);
  currentplayer = &(allplayers[turncounter % num_players]);
  actions = 1;
  money = 0;
  extramoney = 0;
  buys = 1;
  updatetreasure();
  
  //init_sound_system();
  //main_screenS = loadSoundFile("gathering_strength.wav");
  //if (USE_SOUND) playSound(main_screenS, 1);
  
  glutPostWindowRedisplay(mainWindowID);
  glutSetWindow(mainWindowID);
}
// card select screen mouse function
void mouse3(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, cSelectWindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // user pressed down
      cardselectpressed(x,y);
    }
    else {
      // user let go of the mouse
      // check if action cards were pressed
      setupactioncards(x,y);
      // check the random button
      if ( onButton(x,y, randomPos) && randomPressed ) {
	// here we need to choose random cards for the game to use
	purplepile.shuffle();
	current_action_cards = 0;
	for( uint i=0; i<10; i++){
	  actionCards[i] = &(purplepile.contents[i]);
	  for(int n=0; n<4; ++n){
	    (*(actionCards[i]))->cardMainScreenPos[n] = (game_cards[i])[n];
   	    (*(actionCards[i]))->cardBuyScreenPos[n] = (buy_action_cards[i])[n];
	  }
	  current_action_cards++;
	}
	
      }
      else if ( onButton(x,y, startPos) && startPressed ) {
	// start is pressed, destroy card select screen and
	//   make the gameplay screen
	glutDestroyWindow(cSelectWindowID);
	cSelectWindowID = 0;
	//soundoff();
	creategameplayscreen();
      }
      randomPressed = false;
      startPressed = false;
    }
  }
  else if ( GLUT_RIGHT_BUTTON == mouseButton ) { }
  glutPostRedisplay();
}

//-------------- gameplay screen mouse helper functions---------------------------

// checks if the mouse pressed down on buttons/cards
void gameplaymousepressed(int x, int y)
{
  if ( onButton(x,y, buyPos) ) {
    buyPressed = true;
  }
  else buyPressed = false;
  if ( onButton(x,y, rulesMainPos) ) {
    rules2Pressed = true;
  }
  else rules2Pressed = false;
  
  for ( uint i=0; i < currentplayer->hand->size; ++i ) {
    if ( currentplayer->hand->contents[i]->category == ACTION ) {
      if ( onButton(x,y, currentplayer->hand->contents[i]->cardMainScreenPos) && (actions > 0 || throneroomsPlayed > 0))
	currentplayer->hand->contents[i]->cardPressed = true;
      else
	currentplayer->hand->contents[i]->cardPressed = false;
    }
  }
}

// creates the buy screen
void createbuyscreen()
{
  glutInitWindowPosition(0,0); //choose where to put it
  glutInitWindowSize(buyWIDTH,buyHEIGHT); // how big
  buyWindowID = createNewWindow("Buy Screen", 5);
  glutDisplayFunc(drawBuyWindow); // assign the display function
  glOrtho(0., buyWIDTH-1, buyHEIGHT-1, 0., -1.0, 1.0); // coords
  buy_bg = loadTexture(buybackground);
  endS = loadTexture(endturnStatic);
  endH = loadTexture(endturnHover);
  endC = loadTexture(endturnClicked);
  for ( int i=0; i < 10; ++i ) {
    (*(actionCards[i]))->cardID = loadTexture(((*(actionCards[i]))->picture));
  }
  for ( int i=0; i < 6; ++i ) {
    treasurevictorypile.contents[i]->cardID = loadTexture( treasurevictorypile.contents[i]->picture );
  }
  glutPostWindowRedisplay(buyWindowID);
  glutSetWindow(buyWindowID);
}

// create rules1 screen
void createrules1screen()
{
  rules_identifier = 0;
  glutInitWindowPosition(0,0);
  glutInitWindowSize(rulesWIDTH, rulesHEIGHT);
  rules1WindowID = createNewWindow("Rules Screen", 6);
  glutDisplayFunc(drawRulesWindow1);
  glOrtho(0., rulesWIDTH-1, rulesHEIGHT-1, 0., -1.0, 1.0);
  rules_bg = loadTexture(rulesbackground);
  returnS = loadTexture(returnStatic);
  returnH = loadTexture(returnHover);
  returnC = loadTexture(returnClicked);
  nextS = loadTexture(nextStatic);
  nextH = loadTexture(nextHover);
  nextC = loadTexture(nextClicked);
  
  glutPostWindowRedisplay(rules1WindowID);
  glutSetWindow(rules1WindowID);
}

// this checks if action cards were clicked
//   (supplements the gameplay screen mouse funct)
void checkclickedactions(int x, int y)
{
  bool cardplayed = false;
  //extramoney = 0;
  for ( uint i=0; i < currentplayer->hand->size && cardplayed == false && (actions > 0 || throneroomsPlayed > 0); ++i ) {
    if ( currentplayer->hand->contents[i]->category == ACTION ) {
      if ( onButton(x,y, currentplayer->hand->contents[i]->cardMainScreenPos) && currentplayer->hand->contents[i]->cardPressed) {
	cardplayed = true;
	if ( currentplayer->hand->contents[i]->getType() == "throneroom" ){
	  action * activecard;
	  activecard = (action *)currentplayer->hand->contents[i];
	  activecard->move(currentplayer->playedcards);
	  if ( actions > 0 )
	    actions--;
	  throneroomsPlayed++;
	  extracards = false;
	}
	else if ( currentplayer->hand->contents[i]->getType() == "bureaucrat" 
		  || currentplayer->hand->contents[i]->getType() == "cellar" 
		  || currentplayer->hand->contents[i]->getType() == "chancellor"
		  || currentplayer->hand->contents[i]->getType() == "chapel" 
		  || currentplayer->hand->contents[i]->getType() == "feast" 
		  || currentplayer->hand->contents[i]->getType() == "library" 
		  || currentplayer->hand->contents[i]->getType() == "militia" 
		  || currentplayer->hand->contents[i]->getType() == "mine"
		  || currentplayer->hand->contents[i]->getType() == "remodel" 
		  || currentplayer->hand->contents[i]->getType() == "spy" 
		  || currentplayer->hand->contents[i]->getType() == "thief" 
		  || currentplayer->hand->contents[i]->getType() == "workshop"){
	  action * activecard;
	  activecard = (action *)currentplayer->hand->contents[i];
	  activecard->move(currentplayer->playedcards);
	  if (throneroomsPlayed > 0 ){
	    drawText( 575, 280, "Continue your turn in the terminal!");
	    activecard->execute();
	    activecard->execute();
	    throneroomsPlayed--;
	  }
	  else {
	    drawText( 575, 280, "Continue your turn in the terminal!");
	    activecard->execute();
	    actions--;
	  }
	}
	else {
	  action * activecard;
	  activecard = (action *)currentplayer->hand->contents[i];
	  activecard->move(currentplayer->playedcards);
	  if (throneroomsPlayed > 0 ){
	    activecard->execute();
	    activecard->execute();
	    throneroomsPlayed--;
	  }
	  else {
	    activecard->execute();
	    actions--;
	  }
	  extracards = false;
	}
      }
      money = 0;
      updatetreasure();
      //extramoney = 0;
    }
  }
}

// gameplay screen mouse function
void mouse4(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, mainWindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse-- do something
      gameplaymousepressed(x,y);
    }
    else {
      // the user just let go of the mouse
      if ( onButton(x,y, buyPos) && buyPressed ) {
	if ( 0 == buyWindowID ) {
	  // create the buy screen
	  createbuyscreen();
	}
      }
      else if ( onButton(x,y, rulesMainPos) && rules2Pressed ) {
	if ( 0 == rules1WindowID ) {
	  // create the rules screen
	  createrules1screen();
	}
      }
      checkclickedactions(x,y);
      
      buyPressed = false;
      rules2Pressed = false;
    }
  }
  else if (GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}

//-------------------- buy screen helper functions ------------------------------

void buyscreenpressed(int x, int y)
{
  if ( onButton(x,y, endturnPos) ) {
    endturnPressed = true;
  }
  else endturnPressed = false;
  if (buys > 0) {
    for ( int i=0; i < 10; ++i) {
      if ( onButton(x,y, (*(actionCards[i]))->cardBuyScreenPos) && ((*(actionCards[i]))->getSupply() > 0 ))
	(*(actionCards[i]))->cardPressed = true;
      
      else
	(*(actionCards[i]))->cardPressed = false;
    }
    for ( int i=0; i < 6; ++i) {
      if ( onButton(x,y, treasurevictorypile.contents[i]->cardBuyScreenPos) && treasurevictorypile.contents[i]->getSupply() > 0 && buys > 0) treasurevictorypile.contents[i]->cardPressed = true;
      else treasurevictorypile.contents[i]->cardPressed = false;
    }
  }
}

void endturncreate(int x, int y)
{
  currentplayer->discardpile->add(currentplayer->hand);
  currentplayer->draw_hand();
  ++turncounter;
  currentplayer = &(allplayers[turncounter % num_players]);
  actions = 1;
  money = 0;
  extramoney = 0;
  buys = 1;
  updatetreasure();
  throneroomsPlayed = 0;
  extracards = false;
  glutDestroyWindow(buyWindowID);
  buyWindowID = 0;
  glutDestroyWindow(mainWindowID);
  mainWindowID = 0;
  // recreate the gameplay screen
  glutInitWindowPosition(0,0);  // choose where to put it
  glutInitWindowSize(mainWIDTH,mainHEIGHT); // how big?
  mainWindowID = createNewWindow("Dominion", 4);
  glutDisplayFunc(drawMainWindow); // assign the display function
  glOrtho(0., mainWIDTH-1, mainHEIGHT-1, 0., -1.0, 1.0); // coords
  main_bg = loadTexture(mainbackground);
  buyS = loadTexture(buyStatic); // load the button textures
  buyH = loadTexture(buyHover);
  buyC = loadTexture(buyClicked);
  rulesS = loadTexture(rulesStatic);
  rulesH = loadTexture(rulesHover);
  rulesC = loadTexture(rulesClicked);
  trashC = loadTexture(trash);
  cardbackC = loadTexture(cardback);
  
  glutPostWindowRedisplay(mainWindowID);
  glutSetWindow(mainWindowID);
}

// if cards are pressed in the buy screen, figure out what 
//  to do with them and where to put them
void buycardspressed(int x, int y)
{
  for ( int i=0; i < 10; ++i ) {
    if ( onButton(x,y, (*(actionCards[i]))->cardBuyScreenPos) && (*(actionCards[i]))->cardPressed && money >=  (*(actionCards[i]))->cost && buys > 0) {
      string response = (*(actionCards[i]))->getType();
      currentplayer->purchase( response, currentplayer->discardpile);
      currentplayer->discardpile->contents[currentplayer->discardpile->size - 1]->cardMainScreenPos = new double [4];
      for ( int j=0; j < 4; ++j)
	currentplayer->discardpile->contents[currentplayer->discardpile->size - 1]->cardMainScreenPos[j] = (*(actionCards[i]))->cardMainScreenPos[j];
      
      money -= (*(actionCards[i]))->cost;
      buys--;
    }
  }
  for ( int i=0; i < 6; ++i ) {
    if ( onButton(x,y, treasurevictorypile.contents[i]->cardBuyScreenPos) && treasurevictorypile.contents[i]->cardPressed && money >=  treasurevictorypile.contents[i]->cost && buys > 0) {
      string response = treasurevictorypile.contents[i]->getType();
      currentplayer->purchase( response, currentplayer->discardpile);
      money -= treasurevictorypile.contents[i]->cost;
      buys--;
    }
  }
}

// checks to see if the game is over
void endgamecheck()
{
  bool endgame = 0;
  if (treasurevictorypile.contents[5]->getSupply() == 0 )
    endgame = 1;
  else {
    int pilecheck = 0;
    for (int i = 0; i < 10; ++i){
      if ( (*(actionCards[i]))->getSupply() == 0 ){
	++pilecheck;
      }
    }
    if ( pilecheck == 3 )
      endgame = 1;
  }
  if ( endgame ) {
    exitWindows();
    drawfinalscreen();
  }
}

	
// buy screen mouse function
void mouse5(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, buyWindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse -- do something
      buyscreenpressed(x,y);  
    }
  
    else {
      // the user just let go of the mouse -- do something
      if ( onButton(x,y, endturnPos) && endturnPressed ) {
	// we're going back to the gameplay screen, show next players hand
	endturncreate(x,y);
	endgamecheck();
      }
      buycardspressed(x,y);
      endturnPressed = false;
    }
  }
  else if ( GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}

// rules screen 1 mouse function
void mouse6(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, rules1WindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse-- do something
      if ( onButton(x,y, returnPos) ) {
	returnPressed = true;
      }
      else returnPressed = false;
      if ( onButton(x,y, nextPos) ) {
	nextPressed = true;
      }
      else nextPressed = false;
    }
    else {
      // the user just let go of the mouse
      if ( onButton(x,y, returnPos) && returnPressed ) {
	// if the mouse is on the button and it was pressed
	glutDestroyWindow(rules1WindowID);
	rules1WindowID = 0;
	if ( rules_identifier == 0 ) {
	  glutPostWindowRedisplay(mainWindowID);
	  glutSetWindow(mainWindowID);
	}
	else if ( rules_identifier == 1 ) {
	  glutPostWindowRedisplay(startWindowID);
	  glutSetWindow(startWindowID);
	}
      }
      else if ( onButton(x,y, nextPos) && nextPressed ) {
	// if the mouse is on the button and it was pressed
	glutDestroyWindow(rules1WindowID);
	rules1WindowID = 0;
	glutInitWindowPosition(0,0);
	glutInitWindowSize(rulesWIDTH, rulesHEIGHT);
	rules2WindowID = createNewWindow("Rules Screen", 7);
	glutDisplayFunc(drawRulesWindow2);
	glOrtho(0., rulesWIDTH-1, rulesHEIGHT-1, 0., -1.0, 1.0);
	rules2_bg = loadTexture(rulesbackground2);
	backS = loadTexture(backStatic);
	backH = loadTexture(backHover);
	backC = loadTexture(backClicked);
	nextS = loadTexture(nextStatic);
	nextH = loadTexture(nextHover);
	nextC = loadTexture(nextClicked);
	
	glutPostWindowRedisplay(rules2WindowID);
	glutSetWindow(rules2WindowID);
      }
      
      returnPressed = false;
      nextPressed = false;
    }
  }
  else if ( GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}

// rules screen 2 mouse function
void mouse7(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, rules2WindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse-- do something
      if ( onButton(x,y, backPos) ) {
	backPressed = true;
      }
      else backPressed = false;
      if ( onButton(x,y, nextPos) ) {
	nextPressed = true;
      }
      else nextPressed = false;
    }
    else {
      // the user just let go of the mouse
      if ( onButton(x,y, backPos) && backPressed ) {
	// if the mouse is on the button and it was pressed
	glutDestroyWindow(rules2WindowID);
	rules2WindowID = 0;
	glutInitWindowPosition(0,0);
	glutInitWindowSize(rulesWIDTH, rulesHEIGHT);
	rules1WindowID = createNewWindow("Rules Screen", 6);
	glutDisplayFunc(drawRulesWindow1);
	glOrtho(0., rulesWIDTH-1, rulesHEIGHT-1, 0., -1.0, 1.0);
	rules_bg = loadTexture(rulesbackground);
	returnS = loadTexture(returnStatic);
	returnH = loadTexture(returnHover);
	returnC = loadTexture(returnClicked);
	nextS = loadTexture(nextStatic);
	nextH = loadTexture(nextHover);
	nextC = loadTexture(nextClicked);

	glutPostWindowRedisplay(rules1WindowID);
	glutSetWindow(rules1WindowID);
      }
      else if ( onButton(x,y, nextPos) && nextPressed ) {
	// if the mouse is on the button and it was pressed
	glutDestroyWindow(rules2WindowID);
	rules2WindowID = 0;
	glutInitWindowPosition(0,0);
	glutInitWindowSize(rulesWIDTH, rulesHEIGHT);
	rules3WindowID = createNewWindow("Rules Screen", 8);
	glutDisplayFunc(drawRulesWindow3);
	glOrtho(0., rulesWIDTH-1, rulesHEIGHT-1, 0., -1.0, 1.0);
	rules3_bg = loadTexture(rulesbackground3);
	backS = loadTexture(backStatic);
	backH = loadTexture(backHover);
	backC = loadTexture(backClicked);
	returnS = loadTexture(returnStatic);
	returnH = loadTexture(returnHover);
	returnC = loadTexture(returnClicked);

	glutPostWindowRedisplay(rules3WindowID);
	glutSetWindow(rules3WindowID);
      }	
      backPressed = false;
      nextPressed = false;
    }
  }
  else if ( GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}

// rules screen mouse 3 function
void mouse8(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, rules3WindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      // the user just pressed down on the mouse-- do something
      if ( onButton(x,y, return2Pos) ) {
	return2Pressed = true;
      }
      else return2Pressed = false;
      if ( onButton(x,y, backPos) ) {
	backPressed = true;
      }
      else backPressed = false;
    }
    else {
      // the user just let go of the mouse
      if ( onButton(x,y, return2Pos) && return2Pressed ) {
	// if the mouse is on the button and it was pressed
	glutDestroyWindow(rules3WindowID);
	rules3WindowID = 0;
	if ( rules_identifier == 0 ) {
	  glutPostWindowRedisplay(mainWindowID);
	  glutSetWindow(mainWindowID);
	}
	else if ( rules_identifier == 1 ) {
	  glutPostWindowRedisplay(startWindowID);
	  glutSetWindow(startWindowID);
	}
      }
      else if ( onButton(x,y, backPos) && backPressed ) {
	// if the mouse is on the button and it was pressed
	glutDestroyWindow(rules3WindowID);
	rules3WindowID = 0;
	glutInitWindowPosition(0,0);
	glutInitWindowSize(rulesWIDTH, rulesHEIGHT);
	rules2WindowID = createNewWindow("Rules Screen", 7);
	glutDisplayFunc(drawRulesWindow2);
	glOrtho(0., rulesWIDTH-1, rulesHEIGHT-1, 0., -1.0, 1.0);
	rules_bg = loadTexture(rulesbackground2);
	backS = loadTexture(backStatic);
	backH = loadTexture(backHover);
	backC = loadTexture(backClicked);
	nextS = loadTexture(nextStatic);
	nextH = loadTexture(nextHover);
	nextC = loadTexture(nextClicked);

	glutPostWindowRedisplay(rules2WindowID);
	glutSetWindow(rules2WindowID);
      }
      return2Pressed = false;
      backPressed = false;
    }
  }
  else if ( GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}

// mouse function for the final screen!!!
void mouse9(int mouseButton, int state, int x, int y)
{
  mouseCoords(x, y, finalWindowID);
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {
      if ( onButton(x,y, quitPos) ) {
	quitPressed = true;
      }
      else quitPressed = false;
    }
    else {    // mouse has been released
      if ( onButton(x,y, quitPos) && quitPressed ) {
	exitAll();
      }
      quitPressed = false;
    }
  }
  else if ( GLUT_RIGHT_BUTTON == mouseButton ) {
  }
  glutPostRedisplay();
}

// process keyboard events
void keyboard( unsigned char c, int x, int y )
{
  if ( TextBox1Pressed ) { // intercept keyboard press, to place in text box
   
    if ( '\b'==c || 127==c ) { // handle backspace
      if ( textInBox1.length() > 0 ) 
	textInBox1.erase(textInBox1.end()-1);
    } 
    else if ( c >= 32 && c <= 126 ) { // check for printable character
      // check that we don't overflow the box
      if ( textInBox1.length() < MAX_CHARS_IN_TEXTBOX ) textInBox1 += c;
    }
  }
  else if ( TextBox2Pressed ) 
    {
      if ( '\b'==c || 127==c ) { // handle backspace
	if ( textInBox2.length() > 0 ) 
	  textInBox2.erase(textInBox2.end()-1);
      } 
      else if ( c >= 32 && c <= 126 ) { // check for printable character
	// check that we don't overflow the box
	if ( textInBox2.length() < MAX_CHARS_IN_TEXTBOX ) textInBox2 += c;
      }
    }
  else if ( TextBox3Pressed ) 
    {
      if ( '\b'==c || 127==c ) { // handle backspace
	if ( textInBox3.length() > 0 ) textInBox3.erase(textInBox3.end()-1);
      } 
      else if ( c >= 32 && c <= 126 ) { // check for printable character
	// check that we don't overflow the box
	if ( textInBox3.length() < MAX_CHARS_IN_TEXTBOX ) textInBox3 += c;
      }
    }
  else if ( TextBox4Pressed ) 
    {
      if ( '\b'==c || 127==c ) { // handle backspace
	if ( textInBox4.length() > 0 ) textInBox4.erase(textInBox4.end()-1);
      } 
      else if ( c >= 32 && c <= 126 ) { // check for printable character
	// check that we don't overflow the box
	if ( textInBox4.length() < MAX_CHARS_IN_TEXTBOX ) textInBox4 += c;
      }
    }
  /*else {
    switch(c) {
      case 'q':
      case 'Q':
      case 27:
        exitAll();
        break;
      default:
        break;
	}*/
  glutPostRedisplay();
}

// create a window and return the id (I really don't know what this does)
int createNewWindow(const char *windowTitle, int Window)
{
  int id = glutCreateWindow(windowTitle);
  assert( 0 != id );
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // begin setting up the coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // allow blending (for transparent textures)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  // register callbacks
  
  // start screen
  if ( Window == 1 ) {
    glutMouseFunc(mouse);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }

  // player info screen
  else if ( Window == 2 ) {
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse2);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }
  // card select screen
  else if ( Window == 3 ) {
    for (int i=0; i < 25; ++i) {
      purplepile.contents[i]->cardPressed = false;
  }
    glutMouseFunc(mouse3);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }
  // gameplay screen
  else if ( Window == 4 ) {
    done_once = 0;
    glutMouseFunc(mouse4);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }
  // buy screen
  else if ( Window == 5 ) {
    glutMouseFunc(mouse5);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }
  // rules screen
  else if ( Window == 6 ) {
    glutMouseFunc(mouse6);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }

  // rules screen 2
  else if ( Window == 7 ) {
    glutMouseFunc(mouse7);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }

  // rules screen 3
  else if ( Window == 8 ) {
    glutMouseFunc(mouse8);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }

  // final screen
  else if ( Window == 9 ) {
    glutMouseFunc(mouse9);
    glutMotionFunc(mouse_motion);
    glutPassiveMotionFunc(mouse_motion);
  }

  return id;
}

void init_gl_window()
{
  char name[] = "Dominion";
  char *argv[] = { name };
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  
  // build the start screen
  glutInitWindowSize(startWIDTH, startHEIGHT);
  glutInitWindowPosition(0,0);
  startWindowID = createNewWindow("Dominion", 1);
  glutDisplayFunc(drawStartWindow);
  glOrtho(0., startWIDTH-1, startHEIGHT-1, 0., -1.0, 1.0); //coordinate system
  start_bg = loadTexture(startbackground); //loading the background
  newgameS = loadTexture(newgameStatic);
  newgameH = loadTexture(newgameHover);
  newgameC = loadTexture(newgameClicked);
  rulesS = loadTexture(rulesStatic);
  rulesH = loadTexture(rulesHover);
  rulesC = loadTexture(rulesClicked);
  //if ( USE_SOUND) playSound(start_screen, 0);

  glutMainLoop();
}

double getCurrentTime()
{
  struct timeval tv = {0,0};
  struct timezone tz;
  gettimeofday(&tv, &tz);
  return tv.tv_sec + tv.tv_usec/(double)1000000.;
}

void idle()
{
  double elapsedTime = getCurrentTime() - startTime;
  elapsedTime *= 100;
  if ( (int)elapsedTime > confetti_height1 ) {
    confetti_height1++;
    if ( confetti_height1 > 800 ) {
      confetti_height1 = -1600;
    }
    glutPostRedisplay();
  }
}

void drawfinalscreen()
{ 
  // build the final screen
  glutInitWindowSize(finalWIDTH, finalHEIGHT);
  glutInitWindowPosition(0,0);
  finalWindowID = createNewWindow("Winner", 9);
  glutDisplayFunc(drawFinalWindow);
  glOrtho(0., finalWIDTH-1, finalHEIGHT-1, 0., -1.0, 1.0); //coordinate system
  final_bg = loadTexture(finalbackground); //loading the background
  confetti_1 = loadTexture(confetti1);
  confetti_2 = loadTexture(confetti2);
  quitS = loadTexture(quitStatic);
  quitH = loadTexture(quitHover);
  quitC = loadTexture(quitClicked);
  glutIdleFunc(idle);
  glutMainLoop();
}

int main()
{
  //init_sound_system();
  //start_screen = loadSoundFile("buy_screen.wav");
  srand48(time(NULL));
  create_purple_deck();
  startTime = getCurrentTime();
  init_gl_window();
  drawfinalscreen();
}
