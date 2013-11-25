#ifndef _card_
#define _card_
typedef unsigned int uint;
enum name {ADVENTURER, BUREAUCRAT, CELLAR, CHANCELLOR, CHAPEL, COPPER, COUNCILROOM, CURSE, DUCHY, ESTATE, FEAST, FESTIVAL, GARDENS, GOLD, LABORATORY, LIBRARY, MARKET, MILITIA, MINE, MOAT, MONEYLENDER, PROVINCE, REMODEL, SILVER, SMITHY, SPY, THIEF, THRONEROOM, VILLAGE, WITCH, WOODCUTTER, WORKSHOP};
enum cat {TREASURE, VICTORY, ACTION};
extern int actions;
extern int money;
extern int extramoney;
extern int buys;
extern uint num_players;
extern uint turncounter;


// ========= PILE AND CARD BEGIN HERE =================

class pile;
class card {
 public:
  int cardID;
  int cost;
  pile * location;
  cat category;
  double * cardMainScreenPos, * cardBuyScreenPos, * cSelectScreenPos;
  bool overcard;
  bool cardPressed;
  //virtual bool getOvercard()=0;
  //virtual bool getCardPressed()=0;
  const char * picture;
  name type;
  //virtual string getCategory()=0;
  virtual string getType()=0;
  virtual uint getSupply() = 0;
  virtual void reduceSupply() = 0;
  //virtual void display2()=0; // specific card information
  void display1(); // general card information
  void move(pile * &p); // moves card to a new pile
  void trash();
  virtual int getNumcards()=0;
  virtual void setNumcards()=0;
  virtual void addNumcards()=0;
};

class pile {
 public:
  uint size;
  card ** contents;
  pile() {size = 0; contents = 0;} // all piles start out empty
  void display();
  void shuffle();
  void add(pile * &p);
};

extern pile purplepile, treasurevictorypile;
//===== END PILE AND CARD ========= BEGIN CATEGORIES=========

class treasure: public card {
 public:
  uint coin;
  treasure() {category = TREASURE;}
  string getCategory() {return "treasure";}
  //void display2();
};

class victory: public card {
 public:
  int vp; // can be negative (curse cards)
  victory() {category = VICTORY;}
  string getCategory() {return "victory";}
  //const char * getCategory() {return "victory";}
  //void display2();
};
// this is the action card class definition
// however, I think it will be better to 
// wait until we have a working program with
// just treasure cards and victory cards before
// we start to implement action cards
class action: public card {
 public:
  //virtual string getType()=0;
  virtual void execute()=0;
  action(){category = ACTION;}
  string getCategory() {return "action";}
  //const char * getCategory() {return "action";}
  //virtual const char * getInstructions()=0;
  //void display2();
};

// ======CATEGORIES END=============TYPES BEGIN=======

class adventurer: public action {
 public:
  static int num_cards;
  //static char adventurerP[];
  static double adventurercSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  adventurer(){overcard = false; cardPressed = false; num_cards = 0; cost = 6; type = ADVENTURER; picture = "images/adventurer.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 22; cSelectScreenPos[1] = 6; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType(){return "adventurer";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class bureaucrat: public action {
 public:
  static int num_cards;
  //static char bureaucratP[];
  static double bureaucratcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  bureaucrat(){overcard = false; cardPressed = false; num_cards = 0; cost = 4; type = BUREAUCRAT; picture = "images/bureaucrat.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 22; cSelectScreenPos[1] = 208; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "bureaucrat";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;} 
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class cellar: public action {
 public:
  static int num_cards;
  static char cellarP[];
  static double cellarcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  cellar(){overcard = false; cardPressed = false; num_cards = 0; cost=2; type = CELLAR; picture = "images/cellar.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 178; cSelectScreenPos[1] = 208; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "cellar";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class chancellor: public action {
 public:
  static int num_cards;
  static char chancellorP[];
  static double chancellorcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  chancellor(){overcard = false; cardPressed = false; num_cards = 0; cost=3; type = CHANCELLOR; picture = "images/chancellor.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 337; cSelectScreenPos[1] = 208; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "chancellor";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class chapel: public action {
 public:
  static int num_cards;
  static char chapelP[];
  static double chapelcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  chapel(){overcard = false; cardPressed = false; num_cards = 0; cost=2; type = CHAPEL; picture = "images/chapel.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 496; cSelectScreenPos[1] = 208; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "chapel";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class copper: public treasure {
 public:
  static int num_cards;
  static char copperP[];
  static double coppermainPos[];
  static double copperbuyPos[];
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  copper() { overcard = false; cardPressed = false; num_cards = 0; coin = 1; cost = 0; type = COPPER; picture = "images/copper.pam"; cardMainScreenPos = new double [4]; cardMainScreenPos[0] = 391; cardMainScreenPos[1] = 604; cardMainScreenPos[2] = 118; cardMainScreenPos[3] = 180; cardBuyScreenPos = new double [4]; cardBuyScreenPos[0] = 788; cardBuyScreenPos[1] = 232; cardBuyScreenPos[2] = 118; cardBuyScreenPos[3] = 180;}
  string getType() { return "copper";}
  static bool overcard;
  static bool cardPressed;
  bool getOvercard() {return false;}//overcard;}
  bool getCardPressed() {return false;}//cardPressed;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class councilroom: public action {
 public:
  static int num_cards;
  static char councilroomP[];
  static double councilroomcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  councilroom(){overcard = false; cardPressed = false; num_cards = 0; cost=5; type = COUNCILROOM; picture = "images/councilroom.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 656; cSelectScreenPos[1] = 208; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "councilroom";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class curse: public victory {
 public:
  static int num_cards;
  static char curseP[];
  static double cursemainPos[];
  static uint supply;
  string getType() {return "curse";}
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  curse() { overcard = false; cardPressed = false; num_cards = 0; vp = -1; cost = 0; type = CURSE; picture=  "curse.pam"; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4]; cardMainScreenPos[0] = 768; cardMainScreenPos[1] = 605; cardMainScreenPos[2] = 118; cardMainScreenPos[3] = 180;}
  //const char * getType() { return "curse"; }
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return false;}//overcard;}
  //bool getCardPressed() {return false;}//cardPressed;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class duchy: public victory {
 public:
  static int num_cards;
  static char duchyP[];
  static double duchymainPos[];
  static double duchybuyPos[];
  static uint supply;
  string getType() {return "duchy";}
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  duchy() { overcard = false; cardPressed = false; num_cards = 0; vp = 3; cost = 5; type = DUCHY; picture = "images/duchy.pam"; cardMainScreenPos = new double [4]; cardMainScreenPos[0] = 1020; cardMainScreenPos[1] = 605; cardMainScreenPos[2] = 118; cardMainScreenPos[3] = 180; cardBuyScreenPos = new double [4]; cardBuyScreenPos[0] = 958; cardBuyScreenPos[1] = 596; cardBuyScreenPos[2] = 118; cardBuyScreenPos[3] = 180;}
  //const char * getType() { return "duchy";}
  static bool overcard;
  static bool cardPressed;
  bool getOvercard() {return false;}//overcard;}
  bool getCardPressed() {return false;}//cardPressed;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class estate: public victory {
 public:
  static int num_cards;
  static char estateP[];
  static double estatemainPos[];
  static double estatebuyPos[];
  static uint supply;
  string getType() {return "estate";}
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  estate() { overcard = false; cardPressed = false; num_cards = 0; vp = 1; cost = 2; type = ESTATE; picture = "images/estate.pam"; cardMainScreenPos = new double [4]; cardMainScreenPos[0] = 894; cardMainScreenPos[1] = 605; cardMainScreenPos[2] = 118; cardMainScreenPos[3] = 180; cardBuyScreenPos = new double [4]; cardBuyScreenPos[0] = 788; cardBuyScreenPos[1] = 596; cardBuyScreenPos[2] = 118; cardBuyScreenPos[3] = 180;}
  //const char * getType() { return "estate";}
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return false;}//overcard;}
  //bool getCardPressed() {return false;}//cardPressed;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class feast: public action {
 public:
  static int num_cards;
  static char feastP[];
  static double feastcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  feast(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = FEAST; picture = "images/feast.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 816; cSelectScreenPos[1] = 208; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "feast";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class festival: public action {
 public:
  static int num_cards;
  static char festivalP[];
  static double festivalcSelectPos[];
  //static uint supply;
  //festival() { cost = 5; type = FESTIVAL; }
  //string getType() {return "festival";}
  //uint getSupply() {return supply;}
  //void reduceSupply(){supply--;}
  //const char * getInstructions() {return "+2 actions\n+1 buy\n+2 money";}
  //void execute();
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  festival(){overcard = false; cardPressed = false; num_cards = 0; cost=5; type = FESTIVAL; picture = "images/festival.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 976; cSelectScreenPos[1] = 208; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "festival";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class gardens: public victory {
 public:
  static int num_cards;
  static char gardensP[];
  static double gardenscSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  gardens(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = GARDENS; picture = "images/gardens.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 1135; cSelectScreenPos[1] = 208; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  string getType() {return "gardens";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class gold: public treasure {
 public:
  static int num_cards;
  static char goldP[];
  static double goldmainPos[];
  static double goldbuyPos[];
  static uint supply;
  string getType() {return "gold";}
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  gold() { overcard = false; cardPressed = false; num_cards = 0; coin = 3; cost = 6; type = GOLD; picture = "images/gold.pam"; cardMainScreenPos = new double [4]; cardMainScreenPos[0] = 642; cardMainScreenPos[1] = 605; cardMainScreenPos[2] = 118; cardMainScreenPos[3] = 180; cardBuyScreenPos = new double [4]; cardBuyScreenPos[0] = 1128; cardBuyScreenPos[1] = 232; cardBuyScreenPos[2] = 118; cardBuyScreenPos[3] = 180;}
  //const char * getType() { return "gold";}
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return false;}//overcard;}
  //bool getCardPressed() {return false;}//cardPressed;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class laboratory: public action {
 public:
  static int num_cards;
  static char laboratoryP[];
  static double laboratorycSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  laboratory(){overcard = false; cardPressed = false; num_cards = 0; cost=5; type = LABORATORY; picture = "images/laboratory.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 22; cSelectScreenPos[1] = 408; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "laboratory";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class library: public action {
 public:
  static int num_cards;
  static char libraryP[];
  static double librarycSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  library(){overcard = false; cardPressed = false; num_cards = 0; cost=5; type = LIBRARY; picture = "images/library.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 178; cSelectScreenPos[1] = 408; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "library";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class market: public action {
 public:
  static int num_cards;
  static char marketP[];
  static double marketcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  market(){overcard = false; cardPressed = false; num_cards = 0; cost=5; type = MARKET; picture = "images/market.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 337; cSelectScreenPos[1] = 408; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "market";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class militia: public action {
 public:
  static int num_cards;
  static char militiaP[];
  static double militiacSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  militia(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = MILITIA; picture = "images/militia.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 496; cSelectScreenPos[1] = 408; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "militia";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class mine: public action {
 public:
  static int num_cards;
  static char mineP[];
  static double minecSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  mine(){overcard = false; cardPressed = false; num_cards = 0; cost=5; type = MINE; picture = "images/mine.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 656; cSelectScreenPos[1] = 408; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "mine";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class moat: public action {
 public:
  static int num_cards;
  static char moatP[];
  static double moatcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  moat(){overcard = false; cardPressed = false; num_cards = 0; cost=2; type = MOAT;picture = "images/moat.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 816; cSelectScreenPos[1] = 408; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "moat";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class moneylender: public action {
 public:
  static int num_cards;
  static char moneylenderP[];
  static double moneylendercSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  moneylender(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = MONEYLENDER; picture = "images/moneylender.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 976; cSelectScreenPos[1] = 408; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "moneylender";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class province: public victory {
 public:
  static int num_cards;
  static char provinceP[];
  static double provincemainPos[];
  static double provincebuyPos[];
  static uint supply;
  string getType() {return "province";}
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  province() { overcard = false; cardPressed = false; num_cards = 0; vp = 6; cost = 8; type = PROVINCE; picture = "images/province.pam"; cardMainScreenPos = new double [4]; cardMainScreenPos[0] = 1146; cardMainScreenPos[1] = 605; cardMainScreenPos[2] = 118; cardMainScreenPos[3] = 180; cardBuyScreenPos = new double [4]; cardBuyScreenPos[0] = 1128; cardBuyScreenPos[1] = 596; cardBuyScreenPos[2] = 118; cardBuyScreenPos[3] = 180;}
  //const char *  string getType()
  static bool overcard;
  static bool cardPressed;
  bool getOvercard() {return false;}//overcard;}
  bool getCardPressed() {return false;}//cardPressed;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class remodel: public action {
 public:
  static int num_cards;
  static char remodelP[];
  static double remodelcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  remodel(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = REMODEL; picture = "images/remodel.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 1135; cSelectScreenPos[1] = 408; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "remodel";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class smithy: public action {
 public:
  static int num_cards;
  static char smithyP[];
  static double smithycSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  smithy(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = SMITHY; picture = "images/smithy.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 22; cSelectScreenPos[1] = 609; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  string getType() {return "smithy";}
  static uint supply;
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class silver: public treasure {
 public:
  static int num_cards;
  static char silverP[];
  static double silvermainPos[];
  static double silverbuyPos[];
  static uint supply;
  string getType() {return "silver";}
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  silver() { overcard = false; cardPressed = false; num_cards = 0; coin = 2; cost = 3; type = SILVER; picture = "images/silver.pam"; cardMainScreenPos = new double [4]; cardMainScreenPos[0] = 516; cardMainScreenPos[1] = 605; cardMainScreenPos[2] = 118; cardMainScreenPos[3] = 180; cardBuyScreenPos = new double [4]; cardBuyScreenPos[0] = 958; cardBuyScreenPos[1] = 232; cardBuyScreenPos[2] = 118; cardBuyScreenPos[3] = 180;}
  //const char * getType() { return "silver";}
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return false;}//overcard;}
  //bool getCardPressed() {return false;}//cardPressed;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class spy: public action {
 public:
  static int num_cards;
  static char spyP[];
  //static double spycSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  spy(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = SPY; picture = "images/spy.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 178; cSelectScreenPos[1] = 609; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  static uint supply;
  string getType() {return "spy";}
  uint getSupply() {return supply;}
  void reduceSupply() {supply--;} 
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class thief: public action {
 public:
  static int num_cards;
  static char thiefP[];
  //static double thiefcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  thief(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = THIEF; picture = "images/thief.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 337; cSelectScreenPos[1] = 609; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  static uint supply;
  string getType() {return "thief";}
  uint getSupply() {return supply;}
  void reduceSupply() {supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class throneroom: public action {
 public:
  static int num_cards;
  static char throneroomP[];
  static double throneroomcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  throneroom(){overcard = false; cardPressed = false; num_cards = 0; cost=4; type = THRONEROOM; picture = "images/throneroom.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 496; cSelectScreenPos[1] = 609; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  static uint supply;
  string getType() {return "throneroom";}
  uint getSupply() {return supply;}
  void reduceSupply() {supply--;} 
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

bool nonfeastcheck();

class village: public action {
 public:
  static int num_cards;
  static char villageP[];
  static double villagecSelectPos[];
  static uint supply;
  static int cardID;
  village() { overcard = false; cardPressed = false; num_cards = 0; cost = 3; type = VILLAGE; picture = "images/village.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 656; cSelectScreenPos[1] = 609; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  string getType() {return "village";}
  //const char * getType() {return "village";}
  uint getSupply() {return supply;}
  void reduceSupply(){supply--;}
  const char * getInstructions() {return "+1 card\n+2 actions";}
  void execute();
  static bool overcard;
  static bool cardPressed;
  bool getOvercard() {return overcard;}
  bool getCardPressed() {return cardPressed;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class witch: public action {
 public:
  static int num_cards;
  static char witchP[];
  static double witchcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  witch(){overcard = false; cardPressed = false; num_cards = 0; cost=5; type = WITCH; picture = "images/witch.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 816; cSelectScreenPos[1] = 609; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  static uint supply;
  string getType() {return "witch";}
  uint getSupply() {return supply;}
  void reduceSupply() {supply--;} 
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class woodcutter: public action {
 public:
  static int num_cards;
  static char woodcutterP[];
  static double woodcuttercSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  woodcutter(){overcard = false; cardPressed = false; num_cards = 0; cost=3; type = WOODCUTTER; picture = "images/woodcutter.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 976; cSelectScreenPos[1] = 609; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  static uint supply;
  string getType() {return "woodcutter";}
  uint getSupply() {return supply;}
  void reduceSupply() {supply--;}
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

class workshop: public action {
 public:
  static int num_cards;
  static char workshopP[];
  static double workshopcSelectPos[];
  static bool overcard;
  static bool cardPressed;
  //bool getOvercard() {return overcard;}
  //bool getCardPressed() {return cardPressed;}
  workshop(){overcard = false; cardPressed = false; num_cards = 0; cost=3; type = WORKSHOP; picture = "images/workshop.pam"; cSelectScreenPos = new double [4]; cSelectScreenPos[0] = 1135; cSelectScreenPos[1] = 609; cSelectScreenPos[2] = 118, cSelectScreenPos[3] = 180; cardMainScreenPos = new double [4]; cardBuyScreenPos = new double [4];}
  void execute();
  static uint supply;
  string getType() {return "workshop";}
  uint getSupply() {return supply;}
  void reduceSupply() {supply--;} 
  int getNumcards(){return num_cards;}
  void setNumcards(){num_cards = 0;}
  void addNumcards(){++num_cards;}
};

//======== TYPES END HERE ========== BEGIN PURPLE DECK WORK ========

const uint purplecount = 32;
extern card * padventurer, *pbureaucrat, *pcellar, *pchancellor, *pchapel, *pcopper, *pcouncilroom, *pcurse, *pduchy, *pestate, *pfeast, *pfestival, *pgardens, *pgold, *plaboratory, *plibrary, *pmarket, *pmilitia, *pmine, *pmoat, *pmoneylender, *pprovince, *premodel, *psilver, *psmithy, *pspy, *pthief, *pthroneroom, *pvillage, *pwitch, *pwoodcutter, *pworkshop;

extern card ** purplestack [purplecount];
extern card ** actionCards [10];
extern pile purplepile;
void create_purple_deck();

void random_game_cards();

//===== END PURPLE DECK WORK ======== BEGIN PLAYER CLASS ========

class player {
 public:
  int total_vps; // can be negative
  pile * drawpile;
  pile * hand;
  pile * discardpile;
  pile * playedcards;
  string name;
  void purchase(string &r, pile * &p);
  void draw_hand();
  void deal_starting_deck();
  void victory_point_count();
  player();
  bool actioncardcheck();
  void draw_cards(uint n);
  void turn();
  bool moatcheck();
};

extern player * currentplayer; // will point to the current player
extern player * allplayers;
// ======= PLAYER CLASS ENDS HERE =============

#endif
