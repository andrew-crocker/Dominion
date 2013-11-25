#include<iostream>
#include<stdlib.h>
using namespace std;
#include "card.h"

//=========BEGIN CARD CLASS===========

void card::display1() {
  cout << getType() << " ";
}

void card::move(pile * &p) {
  if (p == location) // both pointers point to the same pile
    cout << "moving nowhere" << endl;
  else {
    location->size--;
    card ** shrunkencards;
    if(location->size == 0)
      shrunkencards = 0;
    else{
      bool pastcard = false;
      shrunkencards = new card * [location->size];
      for(uint i = 0; i < location->size; i++){
	if (location->contents[i] == this)
	  pastcard = true;
	if (pastcard == false)
	  shrunkencards[i] = location->contents[i];
	else // pastcard == true
	  shrunkencards[i] = location->contents[i+1];
      }
    }    
    delete [] location->contents;
    location->contents = shrunkencards; //updating the pointer
    location = p; //updating the pointer
    location->size++;
    card ** growncards;
    growncards = new card * [location->size];
    for(uint i=0; i < location->size - 1; i++)
      growncards[i] = location->contents[i];
    growncards[location->size - 1] = this;/*add the card to
					    the top of the pile*/
    if(location->contents != 0)
      delete [] location->contents;
    location->contents = growncards;
  }
}

void card::trash() {
  location->size--;
  card ** shrunkencards;
  if(location->size == 0)
    shrunkencards = 0;
  else{
    bool pastcard = false;
    shrunkencards = new card * [location->size];
    for(uint i = 0; i < location->size; i++) {
      if(location->contents[i] == this)
	pastcard = true;
      if(pastcard == false)
	shrunkencards[i] = location->contents[i];
      else // pastcard == true
	shrunkencards[i] = location->contents[i+1];
    }
  }
  delete [] location->contents;
  location->contents = shrunkencards; // pointer now points to shorter array
  delete this;
}

//=======END CARD CLASS=========BEGIN PILE CLASS=========

void pile::add(pile * &p) {
  card ** combination;
  combination = new card * [size + p->size];
  for(uint i=0; i<size; i++)
    combination[i] = contents[i];
  for(uint j=0; j<p->size; j++){
    combination[size + j] = p->contents[j];
    p->contents[j]->location = this;
  }
  size += p->size;
  p->size = 0;
  if(contents != 0)
    delete [] contents;
  if(p->contents != 0)
    delete [] p->contents;
  p->contents = 0;
  contents = combination;
}

void pile::display() {
  for(uint i = 0; i < size; i++)      
    contents[i]->display1();
  cout << endl;
}

void pile::shuffle() {
  card ** newcontents = new card * [size];
  for(uint i=0; i<size; i++)
    newcontents[i] = 0;
  for(uint i=0; i<size; i++) {
    float d48 = drand48();
    //cout << i << " d48 = " << d48 << endl;
    double k = (size - i)*d48;
    uint j = (uint)k;
    uint t=0;
    uint m=0;
    while(m < j) {
      m++;
      t++;
      while(newcontents[t] != 0)
	t++;
    }
    while(newcontents[t] != 0)
      t++;
    if(newcontents[t] != 0)
      cout << "warning" << endl;
    else
      newcontents[t] = contents[i];
  }
  if(contents != 0)
    delete [] contents;
  contents = newcontents;
  }

//===== BEGIN PURPLE DECK WORK ========

card * padventurer, *pbureaucrat, *pcellar, *pchancellor, *pchapel, *pcopper, *pcouncilroom, *pcurse, *pduchy, *pestate, *pfeast, *pfestival, *pgardens, *pgold, *plaboratory, *plibrary, *pmarket, *pmilitia, *pmine, *pmoat, *pmoneylender, *pprovince, *premodel, *psilver, *psmithy, *pspy, *pthief, *pthroneroom, *pvillage, *pwitch, *pwoodcutter, *pworkshop;

card ** purplestack [purplecount] = {&padventurer, &pbureaucrat, &pcellar, &pchancellor, &pchapel, &pcopper, &pcouncilroom, &pcurse, &pduchy, &pestate, &pfeast, &pfestival, &pgardens, &pgold, &plaboratory, &plibrary, &pmarket, &pmilitia, &pmine, &pmoat, &pmoneylender, &pprovince, &premodel, &psilver, &psmithy, &pspy, &pthief, &pthroneroom, &pvillage, &pwitch, &pwoodcutter, &pworkshop};

pile purplepile;
pile treasurevictorypile;

void create_purple_deck() {
  //cout << "hi" << endl;
  padventurer = new adventurer;
  adventurer::supply = 10;
  pbureaucrat = new bureaucrat;
  bureaucrat::supply = 10;
  pcellar = new cellar;
  cellar::supply = 10;
  pchancellor = new chancellor;
  chancellor::supply = 10;
  pchapel = new chapel;
  chapel::supply = 10;
  pcopper = new copper;
  copper::supply = 60;
  pcouncilroom = new councilroom;
  councilroom::supply = 10;
  pcurse = new curse;
  curse::supply = 30;
  pduchy = new duchy;
  duchy::supply = 12;
  pestate = new estate;
  estate::supply = 24;
  pfeast = new feast;
  feast::supply = 10;
  pfestival = new festival;
  festival::supply = 10;
  pgardens = new gardens;
  gardens::supply = 12;
  pgold = new gold;
  gold::supply = 30;
  plaboratory = new laboratory;
  laboratory::supply = 10;
  plibrary = new library;
  library::supply = 10; 
  pmarket = new market;
  market::supply = 10;
  pmilitia = new militia;
  militia::supply = 10;  
  pmine = new mine;
  mine::supply = 10;
  pmoat = new moat;
  moat::supply = 10;
  pmoneylender = new moneylender;
  moneylender::supply = 10;
  pprovince = new province;
  province::supply = 12;
  premodel = new remodel;
  remodel::supply = 10;
  psilver = new silver;
  silver::supply = 40;
  psmithy = new smithy;
  smithy::supply = 10;
  pspy = new spy;
  spy::supply = 10;
  pthief = new thief;
  thief::supply = 10;
  pthroneroom = new throneroom;
  throneroom::supply = 10;
  pvillage = new village;
  village::supply = 10;
  pwitch = new witch;
  witch::supply = 10;
  pwoodcutter = new woodcutter;
  woodcutter::supply = 10;
  pworkshop = new workshop;
  workshop::supply = 10;
  //cout << "hi again" << endl;
  purplepile.size = purplecount - 7;
  treasurevictorypile.size = 7;
  treasurevictorypile.contents = new card * [7];
  treasurevictorypile.contents[0] = new copper;
  treasurevictorypile.contents[1] = new silver;
  treasurevictorypile.contents[2] = new gold;
  treasurevictorypile.contents[3] = new estate;
  treasurevictorypile.contents[4] = new duchy;
  treasurevictorypile.contents[5] = new province;
  treasurevictorypile.contents[6] = new curse;
  purplepile.contents = new card * [purplepile.size];
  for(uint i=0, j=0; i < purplecount && j < purplepile.size; i++, j++){
    while( (*(purplestack[i]))->category != ACTION && (*(purplestack[i]))->type !=  GARDENS ){
      i++;
    }
    purplepile.contents[j] = *(purplestack[i]);
  }
}

void random_game_cards() {
  purplepile.shuffle();
  for(uint i=0; i<10; i++)
    *(actionCards[i]) = purplepile.contents[i];
}

//============END PURPLE DECK========BEGIN EXECUTE METHODS===============

void adventurer::execute() {
  uint numTreasure = 0;
  card * activecard;
  bool deck_exhausted = false;
  pile * testedcards;
  testedcards = new pile;
  testedcards->size = 0;
  testedcards->contents = 0;
  while(numTreasure < 2 && deck_exhausted == false){
    if(currentplayer->drawpile->size == 0 && currentplayer->drawpile->contents == 0){
      currentplayer->drawpile->add(currentplayer->discardpile);//flips discard pile
      currentplayer->drawpile->shuffle();
    }
    if(currentplayer->drawpile->size==0 && currentplayer->discardpile->size==0 && currentplayer->drawpile->contents==0 && currentplayer->discardpile->contents==0)
      deck_exhausted = true;
    else{
      activecard = currentplayer->drawpile->contents[currentplayer->drawpile->size - 1]; // top card of player's deck
      if(activecard->category == TREASURE){
	numTreasure++;
	activecard->move(currentplayer->hand);
      }
      else
	activecard->move(testedcards);
    }
  } // Now two treasure cards have been added
  currentplayer->discardpile->add(testedcards);
}

void bureaucrat::execute(){
  player * current_target;
  string response;
  response = "silver";
  currentplayer->purchase(response, currentplayer->drawpile);
  for(uint i= turncounter + 1; currentplayer != &(allplayers[i % num_players]); i++){
    current_target = &(allplayers[i % num_players]);
    if( current_target->moatcheck() == false){
      bool has_victory_card = false;
      bool victory_card_moved = false;
      for(uint j = 0; j < current_target->hand->size; j++)//check hand for victory card
	if(current_target->hand->contents[j]->category == VICTORY)
	  has_victory_card = true;
      if(has_victory_card == true){
	cout << current_target->name << ", you must place a victory card on top of your deck." << endl;
	while(victory_card_moved == false) {
	  cout << "Here is your current hand:" << endl;
	  current_target->hand->display();
	  cout << "Which card will you put back: ";
	  cin >> response;
	  //DO A BUNCH OF STUFF TO GET THE CARD OUT OF THEIR HAND BACK TO THEIR DECK
	  for(uint i=0; i < current_target->hand->size && victory_card_moved == false; i++){
	    if(current_target->hand->contents[i]->getType() == response && current_target->hand->contents[i]->category == VICTORY){
	      current_target->hand->contents[i]->move(current_target->drawpile);
	      victory_card_moved = true;
	    }
	  }
	  if(victory_card_moved == false)
	    cout << "Sorry, you don't have a victory card with that name" << endl << endl;
	} // end while loop (victory card has been moved)
      }	
    }
  }
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void cellar::execute() {
  actions++;
  uint discardcounter = 0;
  bool done = false;
  string response;
  bool cardreached;
  while(done == false && currentplayer->hand->size > 0){
    cardreached = false;
    cout << "Here is your current hand:" << endl;
    currentplayer->hand->display();
    cout << "Name a card to discard it, or say 'done' to stop discarding and start drawing:" << endl;
    cin >> response;
    if(response == "done")
      done = true;
    else{
      cardreached = false;
      for(uint i=0; i<currentplayer->hand->size && cardreached==false; i++){//for every card in their hand
	if(currentplayer->hand->contents[i]->getType() == response){//if their card is what they asked for
	  cardreached = true;
	  currentplayer->hand->contents[i]->move(currentplayer->discardpile); // discard the card
	  discardcounter++;
	} // end if (card they wanted)
      } // end for loop (cards in their hand)
      if(cardreached == false)
	cout << "Sorry, you don't have a card with that name" << endl;     
      // otherwise card was reached, so for loop has been left
    } // end else (response wasn't "done")
  }// end while loop (all cards have been discarded)
  currentplayer->draw_cards(discardcounter);
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void chancellor::execute() {
  extramoney += 2;
  cout << "Would you like to put your deck into your discard pile? (yes or no): ";
  string response;
  cin >> response;
  while(response != "yes" && response != "no" && response != "y" && response != "n"){
    cout << "Sorry, that response was not valid. Please try again: ";
    cin >> response;
  }
  if(response == "yes" || response == "y")
    currentplayer->discardpile->add(currentplayer->drawpile);
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void chapel::execute() {
  uint trashcounter = 0;
  bool done = false;
  string response;
  bool cardreached;
  while(done == false && currentplayer->hand->size > 0 && trashcounter < 4){
    cardreached = false;
    cout << "Here is your current hand:" << endl;
    currentplayer->hand->display();
    cout << endl;
    cout << "You can trash up to " << 4 - trashcounter << " more cards" << endl;
    cout << "Name a card to trash it, or say 'done' to stop trashing cards:" << endl;
    cin >> response;
    if(response == "done")
      done = true;
    else{
      cardreached = false;
      for(uint i=0; i<currentplayer->hand->size && cardreached==false; i++){//for every card in their hand
	if(currentplayer->hand->contents[i]->getType() == response){//if their card is what they asked for
	  cardreached = true;
	  currentplayer->hand->contents[i]->trash(); // trash the card
	  trashcounter++;
	} // end if (card they wanted)
      } // end for loop (cards in their hand)
      if(cardreached == false)
	cout << "Sorry, you don't have a card with that name" << endl;     
      // otherwise card was reached, so for loop has been left
    } // end else (response wasn't "done")
  }// end while loop (all cards have been discarded)
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void councilroom::execute() {
  currentplayer->draw_cards(4);
  buys += 1;
  for(uint i=0; i < num_players; i++)
    if(currentplayer != &(allplayers[i])) // each *other* player
      allplayers[i].draw_cards(1); // draws a card
}

void feast::execute() {
  string response;
  bool cardTrashed;
  // need code to add a new card (costing up to 5)
  bool namevalid = false;
  bool done = false;
  while(done == false){
    cout << "Here are the cards that you can add to your discard pile:" << endl;
    for(uint i=0; i < 10; i++){
      if( (*(actionCards[i]))->cost <= 5){
	(*(actionCards[i]))->display1();
      }
    }
    for(uint i=0; i<7; i++){
      if( treasurevictorypile.contents[i]->cost <= 5){
	treasurevictorypile.contents[i]->display1();
      }
    }
    cout << "Which card would you like: ";
    cin >> response;
    for(uint i=0; i < 10; i++){ // for every card IN THE GAME (fix this)
      if( (*(actionCards[i]))->getType() == response){// if it's what they wanted
	namevalid = true;
	if( (*(actionCards[i]))->cost <= 5){// if the card isn't too expensive
	  if( (*(actionCards[i]))->getSupply() > 0){// if there are any left
	    currentplayer->purchase(response, currentplayer->discardpile);
	    done = true;
	  }// end if (any copies left)
	  else // none left
	    cout << "Sorry, there are none left" << endl;
	}// end if (not too expensive)
	else // too expensive
	  cout << "Sorry, that's too expensive." << endl;
      } //end if (what they wanted)--go back
    } // for loop exited (gone through deck)
    if(done == false)
      cout << "Please select a different card." << endl << endl;
  } // while loop exited (card has been gained)
  trash(); // feast is trashed
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void festival::execute() {
  actions += 2;
  extramoney += 2;
  buys += 1;
}

void laboratory::execute() {
  currentplayer->draw_cards(2);
  actions += 1;
}

void library::execute() {
  pile * setasidecards;
  string response;
  bool response_valid;
  setasidecards = new pile; // default pile constructor
  while(currentplayer->hand->size < 7 && (currentplayer->drawpile->size > 0 || currentplayer->discardpile->size > 0) ){
    if(currentplayer->drawpile->size == 0){
      currentplayer->drawpile->add(currentplayer->discardpile);
      currentplayer->drawpile->shuffle();
    }  
    cout << "Here is your current hand:" << endl;
    currentplayer->hand->display();
    if(currentplayer->drawpile->contents[currentplayer->drawpile->size - 1]->category == ACTION){
      cout << "You have a " << currentplayer->drawpile->contents[currentplayer->drawpile->size - 1]->getType() << endl;
      response_valid = false;
      while(response_valid == false){
	cout << "Bearing in mind that you have " << actions << " actions left, please enter A to Add to your hand or D to Discard:" << endl;
	cin >> response;
	if(response == "A" || response == "a"){
	  currentplayer->draw_cards(1);
	  response_valid = true;
	}
	else if(response == "D" || response == "d"){
	  currentplayer->drawpile->contents[currentplayer->drawpile->size - 1]->move(setasidecards);
	  response_valid = true;
	}
	else
	  cout << "That was not a valid response" << endl;
      }// end the while loop (we know whether card was added discarded)
    }// end if (action card)
    else // not action card
      currentplayer->draw_cards(1);
  }// end while loop (now they have 7 cards)
  currentplayer->discardpile->add(setasidecards);
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void market::execute() {
  currentplayer->draw_cards(1);
  actions += 1;
  buys += 1;
  extramoney += 1;
  /*cout << "Here is your new hand:" << endl;
    currentplayer->hand->display();*/
}

void militia::execute(){
  extramoney += 2;
  player * current_target;
  string response;
  bool cardDropped;
  for(uint i= turncounter + 1; currentplayer != &(allplayers[i % num_players]); i++){
    current_target = &(allplayers[i % num_players]);
    if(current_target->moatcheck() == false){
      while(current_target->hand->size > 3) {
	cardDropped = false;
	while (cardDropped == false){
	  cout << current_target->name << ", here is your current hand: " << endl;
	  current_target->hand->display();
	  cout << "You must discard until you have 3 cards." << endl;
	  cout << "Please name a card to discard: ";
	  cin >> response;
	  for(uint i=0; i < current_target->hand->size && cardDropped == false; i++){//for every card in hand
	    if(current_target->hand->contents[i]->getType() == response) {// if it was requested
	      cout << "You have dropped: " << current_target->hand->contents[i]->getType() << endl;
	      current_target->hand->contents[i]->move(current_target->discardpile);
	      cardDropped = true;
	    }
	  }// end for loop (hand searched for requested card)
	  if(cardDropped == false)
	    cout << "Sorry, you don't have a card with that name." << endl;
	} // end while loop (a card has been named and dropped)
      } // end while loop (hand size down to 3)
    } // end if (player had no moat)
  }// end for loop (has cycled through all players)
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void mine::execute() {
  bool copperpresent=false, silverpresent=false, cardTrashed = false;
  string response, newcard;
  for(uint i=0; i < currentplayer->hand->size; i++){
    if(currentplayer->hand->contents[i]->type == COPPER)
      copperpresent = true;
    if(currentplayer->hand->contents[i]->type == SILVER)
      silverpresent = true;
  }// end first cycling through player's hand
  
  if(copperpresent && silverpresent){
    // send user to terminal
    cout << "You have two options. Either trash a copper for a silver or trash a silver for a gold." << endl;
    cout << "Here is your current hand: " << endl;
    currentplayer->hand->display();
    cout << endl << endl;
    cout << "Please name the card you would like to trash (copper or silver): ";
    cin >> response;
    while(response != "copper" && response != "silver"){
      cout << "Sorry, that's not a valid answer. Please answer again (copper or silver): ";
      cin >> response;
    }
    if(response == "copper"){
      for(uint i=0; i<currentplayer->hand->size && cardTrashed == false; i++){
	if(currentplayer->hand->contents[i]->type == COPPER){
	  currentplayer->hand->contents[i]->trash();
	  newcard = "silver";
	  currentplayer->purchase(newcard, currentplayer->hand);
	  cardTrashed = true;
	}
      }
    }
    else if(response == "silver"){
      for(uint i=0; i<currentplayer->hand->size && cardTrashed == false; i++){
	if(currentplayer->hand->contents[i]->type == SILVER){
	  currentplayer->hand->contents[i]->trash();
	  newcard = "gold";
	  currentplayer->purchase(newcard, currentplayer->hand);
	  cardTrashed = true;
	}
      }
    }
  } // end if (both copper and silver present)
  else if(copperpresent){
    for(uint i=0; i<currentplayer->hand->size && cardTrashed == false; i++){
      if(currentplayer->hand->contents[i]->type == COPPER){
	currentplayer->hand->contents[i]->trash();
	newcard = "silver";
	currentplayer->purchase(newcard, currentplayer->hand);
	cardTrashed = true;
      }
    }
  }
  else if(silverpresent){
    for(uint i=0; i<currentplayer->hand->size && cardTrashed == false; i++){
      if(currentplayer->hand->contents[i]->type == SILVER){
	currentplayer->hand->contents[i]->trash();
	newcard = "gold";
	currentplayer->purchase(newcard, currentplayer->hand);
	cardTrashed = true;
      }
    }
  }
  else
    cout << "Sorry, you have no treasure cards that can be upgraded." << endl;
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void moat::execute() {
  currentplayer->draw_cards(2);
  /*cout << "Here is your new hand:" << endl;
  currentplayer->hand->display();*/
}

void moneylender::execute() {
  bool foundcopper = false;
  for(uint i=0; i < currentplayer->hand->size && foundcopper == false; i++){
    if(currentplayer->hand->contents[i]->type == COPPER){
      currentplayer->hand->contents[i]->trash();
      foundcopper = true;
    }
  }
  if(foundcopper == true)
    extramoney += 3;
}

void remodel::execute(){
  string response;
  uint oldcost;
  bool cardTrashed;
  cout << "Here is your new hand:" << endl;
  currentplayer->hand->display();
  cout << "Which card would you like to trash: ";
  cin >> response;
  for(uint i=0; i < currentplayer->hand->size && cardTrashed == false; i++){
    if(currentplayer->hand->contents[i]->getType() == response){
      oldcost = currentplayer->hand->contents[i]->cost;
      currentplayer->hand->contents[i]->trash();
      cardTrashed = true;
    }
  }
  // need code to add a new card (costing up to oldcost + 2)
  bool namevalid = false;
  bool done = false;
  while(done == false){
    cout << "Here are the cards that you can add to your hand:" << endl;
    for(uint i=0; i<10 && namevalid == false; i++)
      if( (*(actionCards[i]))->cost <= oldcost + 2)
	(*(actionCards[i]))->display1();
    for(uint i=0; i<7 && namevalid == false; i++)
      if( treasurevictorypile.contents[i]->cost <= oldcost + 2)
	treasurevictorypile.contents[i]->display1();
    cout << "Which card would you like: ";
    cin >> response;
    for(uint i=0; i < 10; i++){ // for every card IN THE GAME (fix this)
      if( (*(actionCards[i]))->getType() == response){// if it's what they wanted
	namevalid = true;
	if( (*(actionCards[i]))->cost <= oldcost + 2){// if the card isn't too expensive
	  if( (*(actionCards[i]))->getSupply() > 0){// if there are any left
	    currentplayer->purchase(response, currentplayer->discardpile);
	    done = true;
	  }// end if (any copies left)
	  else // none left
	    cout << "Sorry, there are none left" << endl;
	}// end if (not too expensive)
	else // too expensive
	  cout << "Sorry, that's too expensive." << endl;
      } //end if (what they wanted)--go back
    } // for loop exited (gone through available cards)
    for(uint i=0; i < 7; i++){ // for every card IN THE GAME (fix this)
      if( treasurevictorypile.contents[i]->getType() == response){// if it's what they wanted
	namevalid = true;
	if( treasurevictorypile.contents[i]->cost <= oldcost + 2){// if the card isn't too expensive
	  if( treasurevictorypile.contents[i]->getSupply() > 0){// if there are any left
	    currentplayer->purchase(response, currentplayer->discardpile);
	    done = true;
	  }// end if (any copies left)
	  else // none left
	    cout << "Sorry, there are none left" << endl;
	}// end if (not too expensive)
	else // too expensive
	  cout << "Sorry, that's too expensive." << endl;
      } //end if (what they wanted)--go back
    } // for loop exited (gone through available cards)


    if(namevalid == false) // if they didn't name an actual card
      cout << "Sorry, that's not a valid name." << endl;
    if(done == false)
      cout << "Please select a different card." << endl << endl;
  } // while loop exited (card has been gained)
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void smithy::execute() {
  currentplayer->draw_cards(3);
}

void spy::execute() {
  currentplayer->draw_cards(1);
  actions++;
  cout << "Here is your current hand: " << endl;
  currentplayer->hand->display();
  cout << "You have " << actions << " actions remaining." << endl;
  string response;
  for(uint i=0; i < num_players; i++){
    if(allplayers[i].drawpile->size == 0){
      allplayers[i].drawpile->add(allplayers[i].discardpile);
      allplayers[i].drawpile->shuffle();
    }
    if(allplayers[i].drawpile->size > 0 && (allplayers[i].moatcheck() == false || &(allplayers[i]) == currentplayer)){
      cout << "The top of " << allplayers[i].name << "'s deck has a " << allplayers[i].drawpile->contents[allplayers[i].drawpile->size - 1]->getType() << endl;
      cout << "keep or discard: " << endl;
      cin >> response;
      while(response != "keep" && response != "k" && response != "discard" && response != "d")
	cout << "Sorry that's not a valid response. Please try again: " << endl;
      if(response == "d" || response == "discard")
	allplayers[i].drawpile->contents[allplayers[i].drawpile->size - 1]->move(allplayers[i].discardpile);
    }
  } 
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void thief::execute() {
  player * current_target;
  string response;
  card * onlycard, * card1, *card2;
  for(uint i= turncounter + 1; currentplayer != &(allplayers[i % num_players]); i++){
    current_target = &(allplayers[i % num_players]);
    if(current_target->drawpile->size == 0){
      current_target->drawpile->add(current_target->discardpile);
      current_target->drawpile->shuffle();
    }
    if(current_target->moatcheck() == false && current_target->drawpile->size > 0){
      if(current_target->drawpile->size == 1){
	onlycard = current_target->drawpile->contents[0]; // assigns pointer to pointer
	if(onlycard->category == TREASURE){
	  cout << current_target->name << " has a " << onlycard->getType() << "." << endl;
	  cout << "Do you want to trash it or take it?" << endl;
	  cout << "Please type 'trash' or 'take': " << endl;
	  cin >> response;
	  while(response != "trash" && response != "take"){
	    cout << "That's not a valid answer. Try again: " << endl;
	    cin >> response;
	  }
	  if(response == "take")
	    onlycard->move(currentplayer->discardpile);
	  else
	    onlycard->trash();
	}
	else
	  onlycard->move(current_target->discardpile);
      } // end if (only one card in draw pile)
      else{ // 2+ card in draw pile
	card1 = current_target->drawpile->contents[current_target->drawpile->size - 1];
	card2 = current_target->drawpile->contents[current_target->drawpile->size - 2];
	if(card1->category == TREASURE)
	  if(card2->category == TREASURE){
	    cout << current_target->name << " has a " << card1->getType() << " and a " << card2->getType() << "." << endl;
	    cout << "Which card do you want to trash: " << endl;
	    cin >> response;
	    while(response != card1->getType() && response != card2->getType() ){
	      cout << "That's not one of them. Please try again: " << endl;
	      cin >> response;
	    }
	    if(response == card1->getType()){ // card1
	      card2->move(current_target->discardpile);
	      cout << "You've chosen " << response << "." << endl;
	      cout << "Please choose 'take' or 'trash': " << endl;
	      cin >> response;
	      while(response != "take" && response != "trash"){
		cout << "Not a valid response. Please try again: " << endl;
		cin >> response;
	      }
	      if(response == "take")
		card1->move(currentplayer->discardpile);
	      else
		card1->trash();
	    }	      
	    else if(response == card2->getType()){ // card2 
	      card1->move(current_target->discardpile);
	      	      card2->move(current_target->discardpile);
	      cout << "You've chosen " << response << "." << endl;
	      cout << "Please choose 'take' or 'trash': " << endl;
	      cin >> response;
	      while(response != "take" && response != "trash"){
		cout << "Not a valid response. Please try again: " << endl;
		cin >> response;
	      }
	      if(response == "take")
		card2->move(currentplayer->discardpile);
	      else
		card2->trash();
	    }
	  }
	  else{ // card 2 wasn't treasure
	    cout << current_target->name << " revealed a " << card1->getType() << " and a " << card2->getType() << endl;
	    card2->move(current_target->discardpile);
	    cout << "Please choose 'take' or 'trash' for the " << card1->getType() << ": ";
	    cin >> response;
	    while(response != "take" && response != "trash"){
	      cout << "Not a valid response. Please try again: " << endl;
	      cin >> response;
	    }
	    if(response == "take")
	      card1->move(currentplayer->discardpile);
	    else
	      card1->trash();
	  }
	else{ // card 1 wasn't treasure
	  if(card2->category == TREASURE){ // card 2 is treasure
	    cout << current_target->name << " revealed a " << card1->getType() << " and a " << card2->getType() << endl;
	    card1->move(current_target->discardpile);
	    cout << "Please choose 'take' or 'trash' for the " << card2->getType() << ": ";
	    cin >> response;
	    while(response != "take" && response != "trash"){
	      cout << "Not a valid response. Please try again: " << endl;
	      cin >> response;
	    }
	    if(response == "take")
	      card2->move(currentplayer->discardpile);
	    else
	      card2->trash();
	  }
	  else{// neither is treasure
	    card1->move(current_target->discardpile);
	    card2->move(current_target->discardpile);
	    cout << current_target->name << " revealed no treasure." << endl;
	  }
	}
      }
    }// end if (cards in deck and no moat)
    else{
      if(current_target->drawpile->size == 0) // empty deck
	cout << current_target->name << " has an empty deck." << endl;
      else if(current_target->moatcheck() == true) // moat
	cout << current_target->name << " has a moat." << endl;
    }
  }// end for loop (onto next player)
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

bool nonfeastcheck() {
  bool nonfeastactioncardpresent = false;
  for(uint i=0; i<currentplayer->hand->size; i++){
    if(currentplayer->hand->contents[i]->category == ACTION && currentplayer->hand->contents[i]->type != FEAST){
      nonfeastactioncardpresent = true;
    }
  }
  return nonfeastactioncardpresent;
}

void throneroom::execute() {
  if(nonfeastcheck()){ // global function; only execute throne room if there is something that's not a feast
    action * doubledcard;
    string response;
    bool cardchosen = false;
    while(cardchosen == false){
      cout << "Here is your current hand:" << endl;
      currentplayer->hand->display(); cout<<endl<<endl;
      cout << "Please choose an action card (not a feast) to use twice:" << endl;
      cin >> response;
      for(uint i=0; i<currentplayer->hand->size && cardchosen == false; i++){//for each card in their hand, until they choose one
	if(currentplayer->hand->contents[i]->getType() == response){//if it's their chosen card
	  if(currentplayer->hand->contents[i]->category == ACTION){//if it's an action card
	    if(currentplayer->hand->contents[i]->type != FEAST){//if it's not a feast
	      doubledcard = (action *)currentplayer->hand->contents[i];//set pointer equal to other pointer
	      cardchosen = true;
	    } // end if (not feast)
	    else // if it is a feast
	      cout << "Sorry, you can't throne room a feast (since it cannot be trashed twice)" << endl;
	  } // end if (action card)
	  else // action card or victory card
	    cout << "Sorry, only action cards can be throneroomed." << endl;
	} // end if (chosen card)
      }// end the for loop (entire hand has been checked, or card found)
    } // end while loop (now card has been chosen)
    doubledcard->move(currentplayer->playedcards);
    doubledcard->execute();
    doubledcard->execute();
  }
  else{
    cout << "Sorry, you only have feasts which can't be throneroomed, since they can't be trashed twice." << endl;
    // giving the action and the card back might be difficult with the use of a second throne room
  }
}

void village::execute() {
  actions += 2;
  currentplayer->draw_cards(1);
}

void witch::execute() {
  currentplayer->draw_cards(2);
  /*cout << "Here is your new hand: " << endl;
  currentplayer->hand->display();*/
  player * current_target;
  string response;
  //if(curse::supply >= num_players - 1){
    for(uint i= turncounter + 1; currentplayer != &(allplayers[i % num_players]); i++) { // each other player
      current_target = &(allplayers[i % num_players]);
      if(current_target->moatcheck() == false && curse::supply > 0){ //                      who doesn't have a moat
	response = "curse";
	current_target->purchase(response, current_target->discardpile);//                   gains a curse card
      }
    }
    //}
/*else if(curse::supply > 0){
    cout << "There are only " << curse::supply << " curses left." << endl;
    cout << "Your opponents are: " << endl;
    for(uint i= turncounter + 1; currentplayer != &(allplayers[i % num_players]); i++)
      cout << allplayers[i % num_players].name << endl;
    if(curse::supply == 1){
      bool personnamed = false;
      while(personnamed == false){
	cout << "Whom will you curse: " << endl;     
	cin >> response;
	for(uint i= turncounter + 1; currentplayer != &(allplayers[i % num_players]); i++){
	  if(response == allplayers[i % num_players].name){
	    response = "curse";
	    allplayers[i % num_players].purchase(response, allplayers[i % num_players].discardpile);
	    personnamed = true;
	  }
	  if(personnamed == false)
	    cout << "Sorry, you don't have any opponents by that name. Try again." << endl;
	}
      }
    }
    else{ // 2 curses left and 3 opponents
      bool personnamed = false;
      while(personnamed == false){
	cout << "Whom will you spare: " << endl;     
	cin >> response;
	for(uint i= turncounter + 1; currentplayer != &(allplayers[i % num_players]); i++)
	  if(response != allplayers[i % num_players].name)
	    personnamed = true;
	if(personnamed == false)
	  cout << "Sorry, you don't have any opponents by that name. Try again." << endl;
      }
      for(uint i= turncounter + 1; currentplayer != &(allplayers[i % num_players]); i++){
	if(response != allplayers[i % num_players].name){
	  response = "curse";
	  allplayers[i % num_players].purchase(response, allplayers[i % num_players].discardpile);
	}
      }
    } 
    }*/
//else // none left
    //  cout << "Sorry, there are no curse cards left." << endl;
    cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

void woodcutter::execute() {
  buys += 1;
  extramoney += 2;
  /*cout << "Here is your new hand:" << endl;
    currentplayer->hand->display();*/
}

void workshop::execute() {
  string response;
  bool cardTrashed;
  // need code to add a new card (costing up to 4)
  bool namevalid = false;
  bool done = false;
  while(done == false){
    cout << "Here are the cards that you can add to your discard pile:" << endl;
    for(uint i=0; i < 10; i++){
      if( (*(actionCards[i]))->cost <= 4){
	(*(actionCards[i]))->display1();
      }
    }
    for(uint i=0; i<7; i++){
      if( treasurevictorypile.contents[i]->cost <= 4){
	treasurevictorypile.contents[i]->display1();
      }
    }
    cout << "Which card would you like: ";
    cin >> response;
    for(uint i=0; i < 10; i++){ // for every card IN THE GAME (fix this)
      if( (*(actionCards[i]))->getType() == response){// if it's what they wanted
	namevalid = true;
	if( (*(actionCards[i]))->cost <= 4){// if the card isn't too expensive
	  if( (*(actionCards[i]))->getSupply() > 0){// if there are any left
	    currentplayer->purchase(response, currentplayer->discardpile);
	    done = true;
	  }// end if (any copies left)
	  else // none left
	    cout << "Sorry, there are none left" << endl;
	}// end if (not too expensive)
	else // too expensive
	  cout << "Sorry, that's too expensive." << endl;
      } //end if (what they wanted)--go back
    } // for loop exited (gone through deck)
    if(done == false)
      cout << "Please select a different card." << endl << endl;
  } // while loop exited (card has been gained)
  cout << "Go back to the gameplay screen to continue your turn!" << endl;
}

//===============END ACTION CARD METHODS==========BEGIN PLAYER CLASS========

bool player::moatcheck() {
  bool moatfound = false;
  for(uint i=0; i < hand->size; i++)
    if(hand->contents[i]->type == MOAT)
      moatfound = true;
  return moatfound;
}

void player::purchase(string &r, pile * &p){
  card * c;
  if("adventurer" == r)
    c = new adventurer;
  else if("bureaucrat" == r)
    c = new bureaucrat;
  else if("cellar" == r)
    c = new cellar;
  else if("chancellor" == r)
    c = new chancellor;
  else if("chapel" == r)
    c = new chapel;
  else if("copper" == r)
    c = new copper;
  else if("councilroom" == r)
    c = new councilroom;
  else if("curse" == r)
    c = new curse;
  else if("duchy" == r)
    c = new duchy;
  else if("estate" == r)
    c = new estate;
  else if("feast" == r)
    c = new feast;
  else if("festival" == r)
    c = new festival;
  else if("gardens" == r)
    c = new gardens;
  else if("gold" == r)
    c = new gold;
  else if("laboratory" == r)
    c = new laboratory;
  else if("library" == r)
    c = new library;
  else if("market" == r)
    c = new market;
  else if("militia" == r)
    c = new militia;
  else if("mine" == r)
    c = new mine;
  else if("moat" == r)
    c = new moat;
  else if("moneylender" == r)
    c = new moneylender;
  else if("province" == r)
    c = new province;
  else if("remodel" == r)
    c = new remodel;
  else if("silver" == r)
    c = new silver;
  else if("smithy" == r)
    c = new smithy;
  else if("spy" == r)
    c = new spy;
  else if("thief" == r)
    c = new thief;
  else if("throneroom" == r)
    c = new throneroom;
  else if("village" == r)
    c = new village;
  else if("witch" == r)
    c = new witch;
  else if("woodcutter" == r)
    c = new woodcutter;
  else if("workshop" == r)
    c = new workshop;
  else {
    c = 0;
    cout << "warning";
  }
  p->size++;
  card ** growncards;
  growncards = new card * [p->size];
  for(uint i = 0; i < p->size - 1; i++)
    growncards[i] = p->contents[i];
  growncards[p->size - 1] = c; // card is added to end (top) of discard pile
  if (p->contents != 0)
    delete [] p->contents;
  p->contents = growncards;
  c->location = p;
  c->reduceSupply();
}

void player::draw_cards(uint n) {
  //cout << "drawing " << n << " cards" << endl;
  uint startingsize;
  startingsize = drawpile->size;
  if(startingsize <= n) {
    //cout << "starting size was less than " << n << endl;
    hand->add(drawpile); // this adds the *drawpile* to the *hand*
    n -= startingsize;
    if(drawpile->size != 0 || drawpile->contents != 0)
      cout << "warning" << endl;
    else{
      //cout << "more cards needed to be drawn" << endl;
      drawpile->size = discardpile->size;
      drawpile->contents = discardpile->contents;
      discardpile->size = 0;
      discardpile->contents = 0;
      for(uint i = 0; i < drawpile->size; i++)
	drawpile->contents[i]->location = drawpile;
      drawpile->shuffle();
      //cout << currentplayer->name << " deck shuffled" << endl;
      if(drawpile->size < n){/*this is if the newly shuffled 
			       discard pile is short on stuff too!*/
	hand->add(drawpile);
	//cout << "Sorry, this is all the cards in your deck." << endl;
      }
      else{
	for(uint i = 0; i < n; i++)/*only draw the cards that
				     haven't been drawn yet*/
	  drawpile->contents[drawpile->size - 1]->move(hand);
      }
    }
  }
  else
    for(uint i = 0; i < n; i++)
      drawpile->contents[drawpile->size - 1]->move(hand);
}

void player::draw_hand() {
  if(hand->size == 0 && hand->contents == 0){
    draw_cards(5);
  }
  else
    cout << "warning" << endl;
}

void player::deal_starting_deck() {
  drawpile->size = 10;
  drawpile->contents = new card * [10];
  for(int i = 0; i < 10; i++) {
    if (i < 7) {
      drawpile->contents[i] = new copper;
      drawpile->contents[i]->location = drawpile;
      copper::supply--;
    }
    else {
      drawpile->contents[i] = new estate;
      drawpile->contents[i]->location = drawpile;
      estate::supply--;
    }
  }
}

player::player() {
  total_vps = 0;
  /* draw pile and discard pile start out
     empty (default pile constructor is called) */
  drawpile = new pile;
  hand = new pile;
  discardpile = new pile;
  playedcards = new pile;
  deal_starting_deck();
  drawpile->shuffle();
  draw_hand();
}

bool player::actioncardcheck() {
  for(uint i=0; i < hand->size; i++)
    if(hand->contents[i]->category == ACTION && hand->contents[i]->type != THRONEROOM) // there must be at least one non-TR action card
      return true;
  return false;
}

void player::turn() {
  cout << name << ", here is your hand:" << endl;
  hand->display();
  cout << endl;
  actions = 1;
  extramoney = 0;
  buys = 1;
  bool done = false;
  bool actionsover = false;
  string response;
  while(actions > 0 && done == false && actionsover == false && actioncardcheck()){/* until they are out of actions *or* out of action cards*/
    cout << "You have ";
    if(actions == 1) cout << "1 action";
    else cout << actions << " actions";
    cout << " left and ";
    if(buys == 1) cout << "1 buy";
    else cout << buys << "buys";
    cout << ". Please type the name of the action card you wish to use next, or type 'buy' to skip to the buy phase, or type 'done' to end your turn." << endl;
    cout << "\nEnter your response here: " << endl;
    cin >> response;
    //const char * response = Response.c_str();
    if (response == "buy")
      actionsover = true;
    else if (response == "done")
      done = true;
    else{
      bool pastcard = false; // determines whether one copy of the action card has already been removed from their hand
      for(int i=0; i < hand->size && pastcard == false; i++){//for every card in their hand
	if(hand->contents[i]->category == ACTION){//if it's an action card
	  if(hand->contents[i]->getType() == response){//if it's the right type
	    action * activecard; // will point to the card being used
	    activecard = (action *)hand->contents[i]; // different pointer but same card
	    activecard->move(playedcards);//move the card to playedcards
	    actions--;
	    activecard->execute();/*do what it says; active card
				    pointer should not have changed*/
	    pastcard = true;
	  }//if right type ended
	}//if action card ended
      }//for loop ended
    }
  }
  if(done == false) {// do all of the following only if they chose to buy something
    for(uint i = 0; i < hand->size; i++)
      if (hand->contents[i]->category == TREASURE){
	extramoney += ((treasure*)hand->contents[i])->coin;
      }
    while(buys > 0 && done == false) {
      cout << "These are the cards that are in the game, with supply listed:" << endl;
      for(uint i = 0; i < purplecount; i++){
	if (*(purplestack[i]) != 0) // if the card is available
	  cout << (*(purplestack[i]))->getType() << " (" << (*(purplestack[i]))->getSupply() << ") ";
      }
      cout << endl << endl;
      if(buys == 1)	
	cout << "You have 1 buy ";      
      else
	cout << "You have " << buys << " buys ";      
      cout << "and a total of " << money << " buying power." << endl << endl;      
      cout << "These are the cards that you can buy:" << endl;
      for(uint i = 0; i < purplecount; i++)
	if (*(purplestack[i]) != 0) // if the card is available
	  if ((*(purplestack[i]))->cost <= money) // if they have enough money
	    cout << (*(purplestack[i]))->getType() << " ";
      cout << endl << endl;      
      cout << "Please enter the name of the card you would like to buy, or type 'done' to end your turn:" << endl;
      cin >> response;
      cout << endl;
      if(response == "done")
	done = true;
      else {
	bool name_valid_and_covered = false; // have we reached the card with the right name?
	bool message_printed = false;
	for(uint i = 0; i < purplecount && name_valid_and_covered == false; i++){
	  cout << "i = " << i << endl;
	  cout << "considering " << (*(purplestack[i]))->getType();
	  if((*(purplestack[i])) != 0){//if the card is available
	    cout << "card is available" << endl;
	    if((*(purplestack[i]))->getSupply() > 0){// if there are any left
	      cout << "there is at least one left" << endl;
	      if ( (*(purplestack[i]))->getType() == response){ // if it's the card they wanted
		cout << "this is what you wanted" << response << endl;
		name_valid_and_covered = true;//the name is valid, so stop cycling through cards
		if ((*(purplestack[i]))->cost <= money){//if they have enough money
		  purchase(response, discardpile); // put the card in their deck
		  money -= (*(purplestack[i]))->cost; // reduce buying power
		  buys--; // reduce number of buys
		  cout << "You have bought a " << response << endl;
		}
		else {// if they don't have enough money
		  cout << "Sorry, you don't have enough money." << endl;
		  message_printed = true;
		}
	      }// end if (card they wanted)
	    }// end if (any cards left)
	    else{ // if there are none left
	      cout << "Sorry, there are none left" << endl;
	      message_printed = true;
	    }
	  }// end if (card available)
	}// end of for loop cycling; we've now cycled through the entire purple deck
	if(name_valid_and_covered == false && message_printed == false) // if none of the available cards match their input
	  cout << "Sorry, that is not a valid name" << endl;
      }// end of else statement; we went through this if the user did not say "done"
    } //end of while loop; once we are here the user is finished buying things
    
    //!!CLEANUP PHASE!!
    discardpile->add(playedcards); // drop played cards in discard pile
    discardpile->add(hand); // drop hand in discard pile
    draw_hand();
  }
}

void player::victory_point_count() {
  total_vps = 0;int num_cards = 0;
  victory * activecard;
  for(uint i=0; i < drawpile->size; i++){
    num_cards++;
  }
  for(uint i=0; i < hand->size; i++){
    num_cards++;
  }
  for(uint i=0; i < discardpile->size; i++){
    num_cards++;
  }
  for(uint i=0; i < playedcards->size; i++){
    num_cards++;
  }
  for(uint i=0; i < drawpile->size; i++){
    if(drawpile->contents[i]->category == VICTORY){
      activecard = (victory *)drawpile->contents[i];
      if(activecard->type == GARDENS)
	activecard->vp = num_cards / 10;      
      total_vps += activecard->vp;
    }
  }
  for(uint i=0; i < hand->size; i++){
    if(hand->contents[i]->category == VICTORY){
      activecard = (victory *)hand->contents[i];
      if(activecard->type == GARDENS)
	activecard->vp = num_cards / 10;
      total_vps += activecard->vp;
    }
  }
  for(uint i=0; i < discardpile->size; i++){
    if(discardpile->contents[i]->category == VICTORY){
      activecard = (victory *)discardpile->contents[i];
      if(activecard->type == GARDENS)
	activecard->vp = num_cards / 10;
      total_vps += activecard->vp;
    }
  }
  for(uint i=0; i < playedcards->size; i++){
    if(playedcards->contents[i]->category == VICTORY){
      activecard = (victory *)playedcards->contents[i];
      if(activecard->type == GARDENS)
	activecard->vp = num_cards / 10;
      total_vps += activecard->vp;
    }
  }
}

uint adventurer::supply;
int adventurer::num_cards;
bool adventurer::overcard;
bool adventurer::cardPressed;
uint bureaucrat::supply;
int bureaucrat::num_cards;
bool bureaucrat::overcard;
bool bureaucrat::cardPressed;
uint cellar::supply;
int cellar::num_cards;
bool cellar::overcard;
bool cellar::cardPressed;
uint chancellor::supply;
int chancellor::num_cards;
bool chancellor::overcard;
bool chancellor::cardPressed;
uint chapel::supply;
int chapel::num_cards;
bool chapel::overcard;
bool chapel::cardPressed;
uint copper::supply;
int copper::num_cards;
bool copper::overcard;
bool copper::cardPressed;
uint councilroom::supply;
int councilroom::num_cards;
bool councilroom::overcard;
bool councilroom::cardPressed;
uint curse::supply;
int curse::num_cards;
bool curse::overcard;
bool curse::cardPressed;
uint duchy::supply;
int duchy::num_cards;
bool duchy::overcard;
bool duchy::cardPressed;
uint estate::supply;
int estate::num_cards;
bool estate::overcard;
bool estate::cardPressed;
uint feast::supply;
int feast::num_cards;
bool feast::overcard;
bool feast::cardPressed;
uint festival::supply;
int festival::num_cards;
bool festival::overcard;
bool festival::cardPressed;
uint gardens::supply;
int gardens::num_cards;
bool gardens::overcard;
bool gardens::cardPressed;
uint gold::supply;
int gold::num_cards;
bool gold::overcard;
bool gold::cardPressed;
uint laboratory::supply;
int laboratory::num_cards;
bool laboratory::overcard;
bool laboratory::cardPressed;
uint library::supply;
int library::num_cards;
bool library::overcard;
bool library::cardPressed;
uint market::supply;
int market::num_cards;
bool market::overcard;
bool market::cardPressed;
uint militia::supply;
int militia::num_cards;
bool militia::overcard;
bool militia::cardPressed;
uint mine::supply;
int mine::num_cards;
bool mine::overcard;
bool mine::cardPressed;
uint moat::supply;
int moat::num_cards;
bool moat::overcard;
bool moat::cardPressed;
uint moneylender::supply;
int moneylender::num_cards;
bool moneylender::overcard;
bool moneylender::cardPressed;
uint province::supply;
int province::num_cards;
bool province::overcard;
bool province::cardPressed;
uint remodel::supply;
int remodel::num_cards;
bool remodel::overcard;
bool remodel::cardPressed;
uint silver::supply;
int silver::num_cards;
bool silver::overcard;
bool silver::cardPressed;
uint smithy::supply;
int smithy::num_cards;
bool smithy::overcard;
bool smithy::cardPressed;
uint spy::supply;
int spy::num_cards;
bool spy::overcard;
bool spy::cardPressed;
uint thief::supply;
int thief::num_cards;
bool thief::overcard;
bool thief::cardPressed;
uint throneroom::supply;
int throneroom::num_cards;
bool throneroom::overcard;
bool throneroom::cardPressed;
uint village::supply;
int village::num_cards;
bool village::overcard;
bool village::cardPressed;
uint witch::supply;
int witch::num_cards;
bool witch::overcard;
bool witch::cardPressed;
uint woodcutter::supply;
int woodcutter::num_cards;
bool woodcutter::overcard;
bool woodcutter::cardPressed;
uint workshop::supply;
int workshop::num_cards;
bool workshop::overcard;
bool workshop::cardPressed;
