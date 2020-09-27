/*Welcome to Hangman!!!
Included features: Two human players or one player vs computer that creates a random word,
play to a chosen amount of points, displayed word with "Hangman" animation*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

void delay (unsigned int mSecs) //allows clock to delay console in milliseconds
{
    clock_t endTime = clock() + mSecs;
    while (endTime > clock());
}

//Initialisation variables:
char choice; //user input to choose 1 or 2 player mode
string player1; //name of Player 1
string player2; //name of Player 2
int P1_points = 0; //Player 1's points
int P2_points = 0; //Player 2's points
int total_points = 0; //Number of points a player needs to win
int chances = 8; // number of chances
int wrongG = 0; //number of wrong guesses

int comp_points = 0; //computers points

int winNum = 0; //int to test if the whole word has been found
int round_number = 1; //the round the game is on, even = player 2 guessing, odd = player 1 guessing

char guessed_letters[7]; //array for incorrectly guessed letters (determine size using a wrongG int?)

char title[] = {"WELCOME TO HANGMAN!!!"};

char compWinMess[] = {"HAHAHA TASTE DEFEAT PUNY HUMAN"};
char compLoseMess1[] = {"CONGRATULATIONS THIS TIME "};
char compLoseMess2[] = {". YOU HAVE DEFEATED ME BUT YOUR VICTORY WILL NOT LAST FOREVER... "};


//Functions:
void checkWrongGuesses (int remChances) //function to check wrong guesses and print level of Hangman animation
{
    if (remChances == 7)
    {
        cout << '\n' << '\n' << '\n' << '\n' << '\n' << " _" << '\n' << '\n';
    }
    else if (remChances == 6)
    {
        cout << '\n' << '\n' << "|" << '\n' << "|" << '\n' << "|" << '\n' << "|_" << '\n' << '\n';
    }
    else if (remChances == 5)
    {
        cout << '\n' << "____" << '\n' << "|" << '\n' << "|" << '\n' << "|" << '\n' << "|_" << '\n' << '\n';
    }
    else if (remChances == 4)
    {
        cout << '\n' << "____" << '\n' << "|  0" << '\n' << "|" << '\n' << "|" << '\n' << "|_" << '\n'<< '\n';
    }
    else if (remChances == 3)
    {
        cout << '\n' << "____" << '\n' << "|  0" << '\n' << "|  |" << '\n' << "|" << '\n' << "|_" << '\n' << '\n';
    }
    else if (remChances == 2)
    {
        cout << '\n' << "____" << '\n' << "|  0" << '\n' << "| -|" << '\n' << "|" << '\n' << "|_" << '\n' << '\n';
    }
    else if (remChances == 1)
    {
        cout << '\n' << "____" << '\n' << "|  0" << '\n' << "| -|-" << '\n' << "|" << '\n'<< "|_" << '\n' << '\n';
    }
    else if (remChances <= 0)
    {
        cout << '\n' << "____" << '\n' << "|  0" << '\n' << "| -|- " << '\n' << "|  |" << '\n' << "|_" << '\n' << '\n';
    }
}

void checkWinningPlayer (int play1points, string player1name, int play2points, string player2name, int theTotalPoints) //function to check if a player has won
{
    if (play1points == theTotalPoints)
    {
        cout << "Congratulations " << player1name << " you are the overall winner with " << play1points
        << " points!! Unlucky " << player2name << " better luck next time...";
    }

    if (play2points == theTotalPoints)
    {
        cout << "Congratulations " << player2name << " you are the overall winner with " << play2points
        << " points!! Unlucky " << player1name << " better luck next time...";
    }
}

void checkWinVsComp (string player1name, int play1points, int theTotalPoints, int computer_points)
{
    if (play1points == theTotalPoints)
        {
            cout << "Congratulations " << player1name << " you are the overall winner with " << play1points
            << " points!! You are superior to HAL";
            delay(2500);
            system("cls");
            cout << "HAL: ";
            for (int i = 0; i < 26; i++) {cout << compLoseMess1[i]; delay(250);}
            cout << player1name;
            delay(250);
            for (int i = 0; i < 66; i++) {cout << compLoseMess2[i]; delay(250);}
        }

        if (computer_points == theTotalPoints)
        {
            cout << "HAL is the overall winner with " << computer_points
            << " points!! Unlucky " << player1name << " better luck next time...";
            delay(2500);
            system("cls");
            cout << "HAL: ";
            for (int i = 0; i < 30; i++) {cout << compWinMess[i]; delay(250);}
        }
}

string createWord(string typingPlayer, string guessingPlayer) //function to create and return the word to be guessed
{
    cout << typingPlayer << " enter a word (no spaces), " << guessingPlayer << " look away: ";
    string word;
    cin >> word;
    return(word);
}

string createUnderscoredWord(string typedWord) //function to convert typed word into "_ _ _ _" format
{
    int length = 0;
    length = typedWord.length();
    int newLength = (2 * length);
    char newWord[newLength];

    for (int i = 0; i < (newLength - 1); i++)
    {
        if (i%2 == 0)
        {
            newWord[i] = '_';
        }
        else if (i%2 == 1)
        {
            newWord[i] = ' ';
        }
    }

    string finalWord = "";
    for (int k = 0; k < newLength - 1; k++)
    {
        finalWord = finalWord + newWord[k];
    }
    return(finalWord);
}

int checkCompletedWord(string typedWord, string underscoredWord) //function to check is the word has been fully found
{                                                                //(error when word.length() = 11?? winNum gets too big??
    int l = typedWord.length();
    int n = 0;
    char char_array[l];
    strcpy(char_array, underscoredWord.c_str()); //copies _Word string into an array of chars to see if any element is an underscore

    for (int i=0; i < l; i++) //searches for completed word i.e. no underscores
    {
        if (underscoredWord[(2*i)] != '_')
        {
            n++; //increments n when an underscore is found
        }
    }
    return(n);
}

char checkGuessedLetter(string guessingPlayer, int chancesRemaining, char letter)
{
    bool lCheck = true;
    while (lCheck)
    {
        cout << '\n' << player2 << ", guess a letter, you have " << chances << " chance(s) remaining: ";
        cin >> letter;

        int counter = 0;
        for (int i = 0; i < wrongG; i++)
        {
            if (letter == guessed_letters[i]) {cout << "You have already guessed '" << letter << "'."; counter++;}
        }
        if (counter != 0) {lCheck = false;}
    }
    return(letter);
}


//String array with all the computer's words
string allWords38[] = {
                       "ace", "age", "aim", "app", "ash", "bad", "bar", "bay", "bid", "bug", "car", "cat", "cry", "cue", "dad", "den", "die", "dig",
                       "dot", "dry", "ear", "eat", "egg", "eye", "fan", "far", "fix", "fly", "foe", "fur", "gap", "gem", "god", "guy", "had", "her",
                       "hid", "how", "hug", "ice", "ivy", "jab", "jaw", "jog", "keg", "key", "lab", "law", "leg", "lie", "log", "mad", "nag", "nap",
                       "nut", "oak", "oil", "orb", "pad", "pay", "pea", "pit", "pub", "rag", "ran", "rib", "rug", "sad", "say", "sea", "see", "she",
                       "sip", "six", "spy", "sum", "tab", "tax", "ten", "toe", "too", "tug", "urn", "vet", "war", "web", "wet", "who", "zip", "zoo",
                       "able", "acid", "aged", "also", "area", "army", "away", "baby", "back", "ball", "band", "bank", "base", "bath", "bear", "beat", "been",
                       "beer", "bell", "belt", "best", "bill", "bird", "blow", "blue", "boat", "body", "bomb", "bond", "bone", "book", "boom", "born", "boss",
                       "both", "bowl", "bulk", "burn", "bush", "busy", "call", "calm", "came", "camp", "card", "care", "case", "cash", "cast", "cell", "chat",
                       "chip", "city", "club", "coal", "coat", "code", "cold", "come", "cook", "cool", "cope", "copy", "core", "cost", "crew", "crop", "dark",
                       "data", "date", "dawn", "days", "dead", "deal", "dean", "dear", "debt", "deep", "deny", "desk", "dial", "diet", "disc", "disk", "does",
                       "done", "door", "dose", "down", "draw", "drew", "drop", "drug", "dual", "duke", "dust", "duty", "each", "earn", "ease", "east", "easy",
                       "edge", "else", "even", "ever", "evil", "exit", "face", "fact", "fail", "fair", "fall", "farm", "fast", "fate", "fear", "feed", "feel",
                       "feet", "fell", "felt", "file", "fill", "film", "find", "fine", "fire", "firm", "fish", "five", "flat", "flow", "food", "foot", "ford",
                       "form", "fort", "four", "free", "from", "fuel", "full", "fund", "gain", "game", "gate", "gave", "gear", "gene", "gift", "girl", "give",
                       "glad", "goal", "goes", "gold", "golf", "gone", "good", "grew", "grey", "grow", "gulf", "hair", "half", "hall", "hand", "hang", "hard",
                       "harm", "hate", "have", "head", "hear", "heat", "held", "hell", "help", "here", "hero", "high", "hill", "hire", "hold", "hole", "holy",
                       "home", "hope", "host", "hour", "huge", "hung", "hunt", "hurt", "idea", "inch", "into", "iron", "item", "join", "jump", "jury", "just",
                       "keen", "keep", "kept", "kick", "kill", "kind", "king", "knee", "knew", "know", "lack", "lady", "laid", "lake", "land", "lane", "last",
                       "late", "lead", "left", "less", "life", "lift", "like", "line", "link", "list", "live", "load", "loan", "lock", "logo", "long", "look",
                       "lord", "lose", "loss", "lost", "love", "luck", "made", "mail", "main", "make", "male", "many", "mass", "matt", "meal", "mean", "meat",
                       "meet", "menu", "mere", "mile", "milk", "mill", "mind", "mine", "miss", "mode", "mood", "moon", "more", "most", "move", "much", "must",
                       "name", "navy", "near", "neck", "need", "news", "next", "nice", "nick", "nine", "none", "nose", "note", "okay", "once", "only", "onto",
                       "open", "oral", "over", "pace", "pack", "page", "paid", "pain", "pair", "palm", "park", "part", "pass", "past", "path", "peak", "pick",
                       "pink", "pipe", "plan", "play", "plot", "plug", "plus", "poll", "pool", "poor", "port", "post", "pull", "pure", "push", "race", "rail",
                       "rain", "rank", "rare", "rate", "read", "real", "rear", "rely", "rent", "rest", "rice", "rich", "ride", "ring", "rise", "risk", "road",
                       "rock", "role", "roll", "roof", "room", "root", "rose", "rule", "rush", "safe", "said", "sake", "sale", "salt", "same", "sand", "save",
                       "seat", "seed", "seek", "seem", "seen", "self", "sell", "send", "sent", "sept", "ship", "shop", "shot", "show", "shut", "sick", "side",
                       "sign", "site", "size", "skin", "slip", "slow", "snow", "soft", "soil", "sold", "sole", "some", "song", "soon", "sort", "soul", "spot",
                       "star", "stay", "step", "stop", "such", "suit", "sure", "take", "tale", "talk", "tall", "tank", "tape", "task", "team", "tell", "tend",
                       "term", "test", "text", "than", "that", "them", "then", "they", "thin", "this", "thus", "till", "time", "tiny", "told", "toll", "tone",
                       "took", "tool", "tour", "town", "tree", "trip", "true", "tune", "turn", "twin", "type", "unit", "upon", "used", "user", "wage", "wait",
                       "wake", "walk", "wall", "want", "ward", "warm", "wash", "wave", "ways", "weak", "wear", "week", "well", "went", "were", "west", "what",
                       "when", "whom", "wide", "wife", "wild", "will", "wind", "wine", "wing", "wire", "wise", "wish", "with", "wood", "word", "wore", "work",
                       "yard", "yeah", "year", "your", "zero", "zone",
                       "about", "above", "abuse", "actor", "acute", "admit", "adopt", "adult", "after", "again", "agent", "agree", "ahead", "alarm", "album",
                       "alert", "alike", "alive", "allow", "alone", "along", "alter", "among", "anger", "angel", "angle", "angry", "apart", "apple", "apply",
                       "arena", "argue", "arise", "array", "aside", "asset", "audio", "audit", "avoid", "award", "aware", "badly", "baker", "bases", "basic",
                       "basis", "beach", "began", "begin", "begun", "being", "below", "bench", "billy", "birth", "black", "blame", "blind", "block", "blood",
                       "board", "boost", "booth", "bound", "brain", "brand", "bread", "break", "breed", "brief", "bring", "broad", "broke", "brown", "build",
                       "built", "buyer", "cable", "carry", "catch", "cause", "chain", "chair", "chart", "chase", "cheap", "check", "chest", "chief", "child",
                       "chose", "civil", "claim", "class", "clean", "clear", "click", "clock", "close", "coach", "coast", "could", "count", "court", "cover",
                       "craft", "crash", "cream", "crime", "cross", "crowd", "crown", "curve", "cycle", "daily", "dance", "dated", "dealt", "death", "debut",
                       "delay", "depth", "doing", "doubt", "dozen", "draft", "drama", "drawn", "dream", "dress", "drill", "drink", "drive", "drove", "dying",
                       "eager", "early", "earth", "eight", "elite", "empty", "enemy", "enjoy", "enter", "entry", "equal", "error", "event", "every", "exact",
                       "exist", "extra", "faith", "false", "fault", "fibre", "field", "fifth", "fifty", "fight", "final", "first", "fixed", "flash", "fleet",
                       "floor", "fluid", "focus", "force", "forth", "forty", "forum", "found", "frame", "frank", "fraud", "fresh", "front", "fruit", "fully",
                       "funny", "giant", "given", "glass", "globe", "going", "grace", "grade", "grand", "grant", "grass", "great", "green", "gross", "group",
                       "grown", "guard", "guess", "guest", "guide", "happy", "heart", "heavy", "hence", "henry", "horse", "hotel", "house", "human", "ideal",
                       "image", "index", "inner", "input", "issue", "joint", "judge", "known", "label", "large", "laser", "later", "laugh", "layer", "learn",
                       "lease", "least", "leave", "legal", "level", "light", "limit", "links", "lives", "local", "logic", "loose", "lower", "lucky", "lunch",
                       "lying", "magic", "major", "maker", "march", "maria", "match", "maybe", "mayor", "meant", "media", "metal", "might", "minor", "minus",
                       "mixed", "model", "money", "month", "moral", "motor", "mount", "mouse", "mouth", "movie", "music", "needs", "never", "newly", "night",
                       "noise", "north", "noted", "novel", "nurse", "occur", "ocean", "offer", "often", "order", "other", "ought", "paint", "panel", "paper",
                       "party", "peace", "phase", "phone", "photo", "piece", "pilot", "pitch", "place", "plain", "plane", "plant", "plate", "point", "pound",
                       "power", "press", "price", "pride", "prime", "print", "prior", "prize", "proof", "proud", "prove", "queen", "quick", "quiet", "quite",
                       "radio", "raise", "range", "rapid", "ratio", "reach", "ready", "refer", "right", "rival", "river", "rough", "round", "route", "royal",
                       "rural", "scale", "scene", "scope", "score", "sense", "serve", "seven", "shall", "shape", "share", "sharp", "sheet", "shelf", "shell",
                       "shift", "shirt", "shock", "shoot", "short", "shown", "sight", "since", "sixth", "sixty", "sized", "skill", "sleep", "slide", "small",
                       "smart", "smile", "smith", "smoke", "solid", "solve", "sorry", "sound", "south", "space", "spare", "speak", "speed", "spend", "spent",
                       "split", "spoke", "sport", "staff", "stage", "stake", "stand", "start", "state", "steam", "steel", "stick", "still", "stock", "stone",
                       "stood", "store", "storm", "story", "strip", "stuck", "study", "stuff", "style", "sugar", "suite", "super", "sweet", "table", "taken",
                       "taste", "taxes", "teach", "teeth", "theft", "their", "theme", "there", "these", "thick", "thing", "think", "third", "those", "three",
                       "threw", "throw", "tight", "times", "tired", "title", "today", "topic", "total", "touch", "tough", "tower", "track", "trade", "train",
                       "treat", "trend", "trial", "tried", "tries", "truck", "truly", "trust", "truth", "twice", "under", "union", "unity", "until", "upper",
                       "upset", "urban", "usage", "usual", "valid", "value", "video", "virus", "visit", "vital", "voice", "waste", "watch", "water", "wheel",
                       "where", "which", "while", "white", "whole", "whose", "woman", "women", "world", "worry", "worse", "worst", "worth", "would", "wound",
                       "write", "wrong", "wrote", "yield", "young", "youth",
                       "abroad", "accept", "access", "across", "acting", "action", "active", "actual", "advice", "advise", "affect", "afford", "afraid",
                       "agency", "agenda", "almost", "always", "amount", "animal", "annual", "answer", "anyone", "anyway", "appeal", "appear", "around",
                       "arrive", "artist", "aspect", "assess", "assist", "assume", "attack", "attend", "august", "author", "avenue", "backed", "barely",
                       "battle", "beauty", "became", "become", "before", "behalf", "behind", "belief", "belong", "better", "beyond", "bishop", "border",
                       "bottle", "bottom", "bought", "branch", "breath", "bridge", "bright", "broken", "budget", "burden", "bureau", "button", "camera",
                       "cancer", "cannot", "carbon", "career", "castle", "casual", "caught", "centre", "chance", "change", "charge", "choice", "choose",
                       "chosen", "church", "circle", "client", "closed", "closer", "coffee", "column", "combat", "coming", "common", "comply", "copper",
                       "corner", "costly", "county", "couple", "course", "covers", "create", "credit", "crisis", "custom", "damage", "danger", "dealer",
                       "debate", "decade", "decide", "defeat", "defend", "define", "degree", "demand", "depend", "deputy", "desert", "design", "desire",
                       "detail", "detect", "device", "differ", "dinner", "direct", "doctor", "dollar", "domain", "double", "driven", "driver", "during",
                       "easily", "eating", "editor", "effect", "effort", "eighth", "either", "eleven", "emerge", "empire", "employ", "enable", "ending",
                       "energy", "engage", "engine", "enough", "ensure", "entire", "entity", "equity", "escape", "estate", "ethnic", "exceed", "except",
                       "excess", "expand", "expect", "expert", "export", "extend", "extent", "fabric", "facing", "factor", "failed", "fairly", "fallen",
                       "family", "famous", "father", "fellow", "female", "figure", "filing", "finger", "finish", "fiscal", "flight", "flying", "follow",
                       "forced", "forest", "forget", "formal", "format", "former", "foster", "fought", "fourth", "friend", "future", "garden", "gather",
                       "gender", "global", "golden", "ground", "growth", "guilty", "handed", "handle", "happen", "hardly", "headed", "health", "height",
                       "hidden", "holder", "honest", "impact", "import", "income", "indeed", "injury", "inside", "intend", "intent", "invest", "island",
                       "itself", "jersey", "junior", "killed", "labour", "latest", "latter", "launch", "lawyer", "leader", "league", "leaves", "legacy",
                       "length", "lesson", "letter", "lights", "likely", "linked", "liquid", "listen", "little", "living", "losing", "lucent", "luxury",
                       "mainly", "making", "manage", "manner", "manual", "margin", "marine", "marked", "market", "martin", "master", "matter", "mature",
                       "medium", "member", "memory", "mental", "merely", "merger", "method", "middle", "mining", "minute", "mirror", "mobile", "modern",
                       "modest", "module", "moment", "morris", "mostly", "mother", "motion", "moving", "murder", "museum", "mutual", "myself", "narrow",
                       "nation", "native", "nature", "nearby", "nearly", "nights", "nobody", "normal", "notice", "notion", "number", "object", "obtain",
                       "office", "offset", "online", "option", "orange", "origin", "output", "packed", "palace", "parent", "partly", "patent", "people",
                       "period", "permit", "person", "phrase", "picked", "planet", "player", "please", "plenty", "pocket", "police", "policy", "prefer",
                       "pretty", "prince", "prison", "profit", "proper", "proven", "public", "pursue", "raised", "random", "rarely", "rather", "rating",
                       "reader", "really", "reason", "recall", "recent", "record", "reduce", "reform", "regard", "regime", "region", "relate", "relief",
                       "remain", "remote", "remove", "repair", "repeat", "replay", "report", "rescue", "resort", "result", "retail", "retain", "return",
                       "reveal", "review", "reward", "riding", "rising", "robust", "ruling", "safety", "salary", "sample", "saving", "saying", "scheme",
                       "school", "screen", "search", "season", "second", "secret", "sector", "secure", "seeing", "select", "seller", "senior", "series",
                       "server", "settle", "severe", "sexual", "should", "signal", "signed", "silent", "silver", "simple", "simply", "single", "sister",
                       "slight", "smooth", "social", "solely", "sought", "source", "soviet", "speech", "spirit", "spoken", "spread", "spring", "square",
                       "stable", "status", "steady", "stolen", "strain", "stream", "street", "stress", "strict", "strike", "string", "strong", "struck",
                       "studio", "submit", "sudden", "suffer", "summer", "summit", "supply", "surely", "survey", "switch", "symbol", "system", "taking",
                       "talent", "target", "taught", "tenant", "tender", "tennis", "thanks", "theory", "thirty", "though", "threat", "thrown", "ticket",
                       "timely", "timing", "tissue", "toward", "travel", "treaty", "trying", "twelve", "twenty", "unable", "unique", "united", "unless",
                       "unlike", "update", "useful", "valley", "varied", "vendor", "versus", "victim", "vision", "visual", "volume", "wealth", "weekly",
                       "weight", "window", "winner", "winter", "within", "wonder", "worker", "writer", "yellow",
                       "ability", "absence", "academy", "account", "accused", "achieve", "acquire", "address", "advance", "adverse", "advised", "adviser",
                       "against", "airline", "airport", "alcohol", "alleged", "already", "analyst", "ancient", "another", "anxiety", "anxious", "anybody",
                       "applied", "arrange", "arrival", "article", "assault", "assumed", "assured", "attempt", "attract", "auction", "average", "backing",
                       "balance", "banking", "barrier", "battery", "bearing", "beating", "because", "bedroom", "believe", "beneath", "benefit", "besides",
                       "between", "billion", "binding", "brother", "brought", "burning", "cabinet", "calling", "capable", "capital", "captain", "caption",
                       "capture", "careful", "carrier", "caution", "ceiling", "central", "centric", "century", "certain", "chamber", "channel", "chapter",
                       "charity", "charter", "checked", "chicken", "chronic", "circuit", "classes", "classic", "climate", "closing", "closure", "clothes",
                       "collect", "college", "combine", "comfort", "command", "comment", "compact", "company", "compare", "compete", "complex", "concept",
                        "concern", "concert", "conduct", "confirm", "connect", "consent", "consist", "contact", "contain", "content", "contest", "context",
                        "control", "convert", "correct", "council", "counsel", "counter", "country", "crucial", "crystal", "culture", "current", "cutting",
                        "dealing", "decided", "decline", "default", "defence", "deficit", "deliver", "density", "deposit", "desktop", "despite", "destroy",
                        "develop", "devoted", "diamond", "digital", "discuss", "disease", "display", "dispute", "distant", "diverse", "divided", "drawing",
                        "driving", "dynamic", "eastern", "economy", "edition", "elderly", "element", "engaged", "enhance", "essence", "evening", "evident",
                        "exactly", "examine", "example", "excited", "exclude", "exhibit", "expense", "explain", "explore", "express", "extreme", "factory",
                        "faculty", "failing", "failure", "fashion", "feature", "federal", "feeling", "fiction", "fifteen", "filling", "finance", "finding",
                        "fishing", "fitness", "foreign", "forever", "formula", "fortune", "forward", "founder", "freedom", "further", "gallery", "gateway",
                        "general", "genetic", "genuine", "greater", "hanging", "heading", "healthy", "hearing", "heavily", "helpful", "helping", "herself",
                        "highway", "himself", "history", "holding", "holiday", "housing", "however", "hundred", "husband", "illegal", "illness", "imagine",
                        "imaging", "improve", "include", "initial", "inquiry", "insight", "install", "instant", "instead", "intense", "interim", "involve",
                        "jointly", "journal", "journey", "justice", "justify", "keeping", "killing", "kingdom", "kitchen", "knowing", "landing", "largely",
                        "lasting", "leading", "learned", "leisure", "liberal", "liberty", "library", "license", "limited", "listing", "logical", "loyalty",
                        "machine", "manager", "married", "massive", "maximum", "meaning", "measure", "medical", "meeting", "mention", "message", "million",
                        "mineral", "minimal", "minimum", "missing", "mission", "mistake", "mixture", "monitor", "monthly", "morning", "musical", "mystery",
                        "natural", "neither", "nervous", "network", "neutral", "notable", "nothing", "nowhere", "nuclear", "nursing", "obvious", "offense",
                        "officer", "ongoing", "opening", "operate", "opinion", "optical", "organic", "outcome", "outdoor", "outlook", "outside", "overall",
                        "pacific", "package", "painted", "parking", "partial", "partner", "passage", "passing", "passion", "passive", "patient", "pattern",
                        "payable", "payment", "penalty", "pending", "pension", "percent", "perfect", "perform", "perhaps", "phoenix", "picking", "picture",
                        "pioneer", "plastic", "pointed", "popular", "portion", "poverty", "precise", "predict", "premier", "premium", "prepare", "present",
                        "prevent", "primary", "printer", "privacy", "private", "problem", "proceed", "process", "produce", "product", "profile", "program",
                        "project", "promise", "promote", "protect", "protein", "protest", "provide", "publish", "purpose", "pushing", "radical", "railway",
                        "readily", "reading", "reality", "realize", "receipt", "receive", "recover", "reflect", "regular", "related", "release", "remains",
                        "removal", "removed", "replace", "request", "require", "reserve", "resolve", "respect", "respond", "restore", "retired", "revenue",
                        "reverse", "routine", "running", "satisfy", "science", "section", "segment", "serious", "service", "serving", "session", "setting",
                        "seventh", "several", "shortly", "showing", "silence", "similar", "sitting", "sixteen", "skilled", "smoking", "society", "somehow",
                        "someone", "speaker", "special", "species", "sponsor", "station", "storage", "strange", "stretch", "student", "studied", "subject",
                        "succeed", "success", "suggest", "summary", "support", "suppose", "supreme", "surface", "surgery", "surplus", "survive", "suspect",
                        "sustain", "teacher", "telling", "tension", "theatre", "therapy", "thought", "through", "tonight", "totally", "touched", "towards",
                        "traffic", "trouble", "turning", "typical", "unknown", "unusual", "upgrade", "upscale", "utility", "variety", "various", "vehicle",
                        "venture", "version", "veteran", "victory", "viewing", "village", "violent", "virtual", "visible", "waiting", "walking", "wanting",
                        "warning", "warrant", "wearing", "weather", "website", "wedding", "weekend", "welcome", "welfare",
                        "absolute", "abstract", "academic", "accepted", "accident", "accuracy", "accurate", "achieved", "acquired", "activity", "actually",
                        "addition", "adequate", "adjacent", "adjusted", "advanced", "advisory", "advocate", "affected", "aircraft", "alliance", "although",
                        "analysis", "announce", "anything", "anywhere", "apparent", "appendix", "approach", "approval", "argument", "artistic", "assembly",
                        "assuming", "athletic", "attached", "attitude", "attorney", "audience", "autonomy", "aviation", "bachelor", "bacteria", "baseball",
                        "bathroom", "becoming", "birthday", "boundary", "breaking", "breeding", "building", "bulletin", "business", "calendar", "campaign",
                        "capacity", "casualty", "catching", "category", "cautious", "cellular", "ceremony", "chairman", "champion", "chemical", "children",
                        "circular", "civilian", "clearing", "clinical", "clothing", "collapse", "colonial", "commence", "commerce", "complain", "complete",
                        "composed", "compound", "comprise", "computer", "conclude", "concrete", "conflict", "confused", "congress", "consider", "constant",
                        "consumer", "continue", "contract", "contrary", "contrast", "convince", "corridor", "coverage", "covering", "creation", "creative",
                        "criminal", "critical", "crossing", "cultural", "currency", "customer", "database", "daughter", "daylight", "deadline", "deciding",
                        "decision", "decrease", "deferred", "definite", "delicate", "delivery", "describe", "designer", "detailed", "diabetes", "dialogue",
                        "diameter", "directly", "director", "disabled", "disaster", "disclose", "discount", "discover", "disorder", "disposal", "distance",
                        "distinct", "district", "dividend", "division", "doctrine", "document", "domestic", "dominant", "dominate", "doubtful", "dramatic",
                        "dressing", "dropping", "duration", "dynamics", "earnings", "economic", "educated", "efficacy", "eighteen", "election", "electric",
                        "eligible", "emerging", "emphasis", "employee", "engaging", "engineer", "enormous", "entirely", "entrance", "envelope", "equality",
                        "equation", "estimate", "evaluate", "eventual", "everyday", "everyone", "evidence", "exchange", "exciting", "exercise", "explicit",
                        "exposure", "extended", "external", "facility", "familiar", "featured", "feedback", "festival", "finished", "firewall", "flagship",
                        "flexible", "floating", "football", "foothill", "forecast", "foremost", "formerly", "fourteen", "fraction", "franklin", "frequent",
                        "friendly", "frontier", "function", "generate", "generous", "governor", "graduate", "graphics", "grateful", "guardian", "guidance",
                        "handling", "hardware", "heritage", "historic", "homeless", "homepage", "hospital", "humanity", "identify", "identity", "ideology",
                        "imperial", "incident", "included", "increase", "indicate", "indirect", "industry", "informal", "informed", "inherent", "initiate",
                        "innocent", "inspired", "instance", "integral", "intended", "interact", "interest", "interior", "internal", "interval", "intimate",
                        "invasion", "involved", "isolated", "judicial", "junction", "keyboard", "landlord", "language", "laughter", "learning", "leverage",
                        "lifetime", "lighting", "likewise", "limiting", "literary", "location", "magazine", "magnetic", "maintain", "majority", "marginal",
                        "marriage", "material", "maturity", "maximize", "meantime", "measured", "medicine", "medieval", "memorial", "merchant", "midnight",
                        "military", "minimize", "minister", "ministry", "minority", "mobility", "moderate", "momentum", "monetary", "moreover", "mortgage",
                        "mountain", "mounting", "movement", "multiple", "national", "negative", "nineteen", "northern", "notebook", "numerous", "observer",
                        "occasion", "offering", "official", "offshore", "operator", "opponent", "opposite", "optimism", "optional", "ordinary", "organize",
                        "original", "overcome", "overhead", "overseas", "overview", "painting", "parallel", "parental", "patented", "patience", "peaceful",
                        "periodic", "personal", "persuade", "petition", "physical", "pipeline", "platform", "pleasant", "pleasure", "politics", "portable",
                        "portrait", "position", "positive", "possible", "powerful", "practice", "precious", "pregnant", "presence", "preserve", "pressing",
                        "pressure", "previous", "princess", "printing", "priority", "probable", "probably", "producer", "profound", "progress", "property",
                        "proposal", "prospect", "protocol", "provided", "provider", "province", "publicly", "purchase", "pursuant", "quantity", "question",
                        "rational", "reaction", "received", "receiver", "recovery", "regional", "register", "relation", "relative", "relevant", "reliable",
                        "reliance", "religion", "remember", "renowned", "repeated", "reporter", "republic", "required", "research", "reserved", "resident",
                        "resigned", "resource", "response", "restrict", "revision", "rigorous", "romantic", "sampling", "scenario", "schedule", "scrutiny",
                        "seasonal", "secondly", "security", "sensible", "sentence", "separate", "sequence", "sergeant", "shipping", "shortage", "shoulder",
                        "simplify", "situated", "slightly", "software", "solution", "somebody", "somewhat", "southern", "speaking", "specific", "spectrum",
                        "sporting", "standard", "standing", "straight", "strategy", "strength", "striking", "struggle", "stunning", "suburban", "suitable",
                        "superior", "supposed", "surgical", "surprise", "survival", "sweeping", "swimming", "symbolic", "sympathy", "syndrome", "tactical",
                        "tailored", "takeover", "tangible", "taxation", "teaching", "tendency", "terminal", "terrible", "thinking", "thirteen", "thorough",
                        "thousand", "together", "tomorrow", "touching", "tracking", "training", "transfer", "treasury", "triangle", "tropical", "turnover",
                        "ultimate", "umbrella", "universe", "unlawful", "unlikely", "variable", "vertical", "violence", "volatile", "warranty", "weakness",
                        "weighted", "whatever", "whenever", "wherever", "wildlife", "wireless", "withdraw", "woodland", "workshop", "yourself"};

//Char array with the letters the computer can guess, number is equal to frequency used in language (unused for now/probably ever)
char compLetters[] = {
                      'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e',
                      't', 't', 't', 't', 't', 't', 't', 't', 't',
                      'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a',
                      'i', 'i', 'i', 'i', 'i', 'i', 'i', 'i',
                      'n', 'n', 'n', 'n', 'n', 'n', 'n', 'n',
                      'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o',
                      's', 's', 's', 's', 's', 's', 's', 's',
                      'h', 'h', 'h', 'h', 'h', 'h',
                      'r', 'r', 'r', 'r', 'r', 'r',
                      'd', 'd', 'd', 'd',
                      'l', 'l', 'l', 'l',
                      'u', 'u', 'u', 'u',
                      'c', 'c', 'c',
                      'm', 'm', 'm',
                      'f', 'f', 'f',
                      'w', 'w',
                      'y', 'y',
                      'g', 'g',
                      'p', 'p',
                      'b', 'b',
                      'v', 'v',
                      'k', 'q', 'j', 'x', 'z'};


//Main program
int main()
{
    delay(1000);
    for (int i = 0; i < 22; i++) {cout << title[i]; delay(250);} //prints title letter by letter
    delay(400);
    system("cls");

    while (((choice != '1') && (choice != '2'))) //while choice is neither 1 or 2
    {
        cout << "Press 1 for one player (vs computer), or press 2 for two player (pvp): ";
        cin >> choice;
        system("cls");
        if ((choice != '1') && (choice != '2'))
        {
            cout << "ERROR. Incorrect input. Try again...";
            delay(2000);
            system("cls");
        }
    }

    if (choice == '2') //then you are playing vs another player
    {
        cout << "Player 1 enter your name: ";
        cin >> player1;
        cout << '\n' << "Player 2 enter your name: ";
        cin >> player2;

        cout << '\n' << "You get 1 point for winning each round (guessing a word or not having your word guessed)." << '\n';

        bool wCheck2 = true;
        while (wCheck2) //while the check is true this runs, two if clauses cause this to change to false and exit
        {
            cout << "How many points would you like to play to? ";
            cin >> total_points;
            system("cls");

            if (total_points <= 0) {cout << "ERROR. You cannot have 0 or negative points. Try again. "; delay(2000); system("cls");}
            else if (total_points >= 8) {cout  << "ERROR. " << total_points << " is too many points. Try again. "; delay(2000); system("cls");}
            else {wCheck2 = false;}
        } //while loop is over so total points has been selected
        system("cls");

        while (((P1_points != total_points) && (P2_points != total_points))) //while neither player has won the whole game
        {
            if (round_number%2 != 0 && ((P1_points != total_points) && (P2_points != total_points))) //if its an odd round (1,3,5.. etc.)
            {                                                                                        //and no player has reached total points
                chances = 8;
                winNum, wrongG = 0; //reinitialise chances, winNum and wrongG to default values

                if (round_number != 1) //displays point scores unless it's round 1 (obviously 0 - 0)
                {
                    cout << "This is Round: " << round_number << ". " << player1 << " has " << P1_points << " point(s). "
                    << player2 << " has " << P2_points << " point(s)" << '\n' << "Remember it's first to " << total_points << " points!" << '\n' << '\n';
                }

                string word {createWord(player1, player2)}; //initialize string word with the return value of createWord (which is word)
                                                            //runs createWord function for Player 1 & 2, returns the typed in word

                string _Word {createUnderscoredWord(word)}; //initialize string _Word with the return value of createUnderscoredWord
                                                            //returns typed word in "_ _ _ _" format as a string

                system("cls");

                //loop to check if a given letter is in the word or not, also checks remaining chances for animation and checks for completed word
                while ((chances != 0) && (winNum != word.length())) //chances = 0 no more guesses, winNum = word length then all the letters have been found
                {
                    cout << '\n' << _Word << '\n' << '\n';

                    cout << "You have already guessed: ";
                    for (int i = 0; i < wrongG; i++) {cout << guessed_letters[i] << ", ";}

                    char letter;
                    bool lCheck = true;
                    //loop to check if a guessed letter has already been guessed incorrectly
                    while (lCheck)
                    {
                        cout << '\n' << player2 << ", guess a letter, you have " << chances << " chance(s) remaining: ";
                        cin >> letter;

                        int counter = 0;
                        for (int i = 0; i < wrongG; i++)
                        {
                            if (letter == guessed_letters[i])
                                {
                                    cout << "You have already guessed '" << letter << "'.";
                                    delay(1500);
                                    counter++;
                                    system("cls");
                                    checkWrongGuesses(chances); //checks how many chances you have left and prints animation
                                    cout << '\n' << _Word << '\n' << '\n';
                                    cout << "You have already guessed: ";
                                    for (int i = 0; i < wrongG; i++) {cout << guessed_letters[i] << ", ";}
                                }
                        }
                        if (counter == 0) {lCheck = false;}
                    }

                    int j = 0;
                    j = word.find(letter, j); //searches if letter is found in the word

                    if (j == string::npos) //if j is not in the word
                    {
                        chances--; //decrease chances
                        wrongG++; //increase wrong guesses
                        guessed_letters[wrongG - 1] = letter; //the incorrect letter gets placed as an element in the array at wrongG - 1 position
                        cout << '\n' << "Incorrect :( ";
                        delay(400);
                    }
                    else //j is not the end of the string (so is in the word)
                    {
                        while(j != string::npos) //while j is not the end of the string
                        {
                            _Word[(2*j)] = letter; //inserts letter at position j
                            j = word.find(letter, j+1);
                        }
                        cout << '\n' << "Correct!! ";
                        delay(400);
                    }

                    system("cls");
                    checkWrongGuesses(chances); //checks how many chances you have left and prints animation

                    int n {checkCompletedWord(word, _Word)}; //checks for completed word and returns n to increment winNum
                    winNum = n;
                }

                //Now either there are no more chances or the whole word has been found, the round is over
                if (chances == 0) //no more chances, full animation drawn
                {
                    cout << "Unlucky " << player2 << ", the word was: '" << word << "'"
                    << '\n' << '\n' << "Congratulations " << player1 << "!! ";
                    P1_points++;
                }
                else //the whole word has been found
                {
                    cout << "Congratulations " << player2 << "!! You successfully guessed: '" << word << "'"
                    << '\n' << '\n' << "Unlucky " << player1 << " :( ";
                    P2_points++;
                }

                delay(2500);
                round_number++; //move onto the next round
                system("cls");
            }


            if (round_number%2 == 0 && ((P1_points != total_points) && (P2_points != total_points))) //if its an even round (2,4,6.. etc.)
            {                                                                                        //and no player has reached total points
                chances = 8;
                winNum, wrongG = 0; //reinitialise chances, winNum and wrongG to default values

                if (round_number != 1) //displays point scores unless it's round 1 (obviously 0-0)
                {
                    cout << "This is Round: " << round_number << ". " << player1 << " has " << P1_points << " point(s). "
                    << player2 << " has " << P2_points << " point(s)" << '\n' << "Remember it's first to " << total_points << " points!" << '\n' << '\n';
                }

                string word {createWord(player2, player1)}; //initialize string word with the return value of createWord (which is word)
                                                            //runs createWord function for Player 1 & 2, returns the typed in word

                string _Word {createUnderscoredWord(word)}; //initialize string _Word with the return value of createUnderscoredWord
                                                            //returns typed word in "_ _ _ _" format as a string

                system("cls");

                //loop to check if a given letter is in the word or not, also checks wrong guesses for animation and checks for completed word
                while (chances != 0 && winNum != word.length()) //chances = 0 no more guesses, winNum = word length then all the letters have been found
                {
                    cout << '\n' << _Word << '\n' << '\n';

                    cout << "You have already guessed: ";
                    for (int i = 0; i < wrongG; i++) {cout << guessed_letters[i] << ", ";}

                    char letter;
                    bool lCheck = true;
                    //loop to check if a guessed letter has already been guessed incorrectly
                    while (lCheck)
                    {
                        cout << '\n' << player1 << ", guess a letter, you have " << chances << " chance(s) remaining: ";
                        cin >> letter;

                        int counter = 0;
                        for (int i = 0; i < wrongG; i++)
                        {
                            if (letter == guessed_letters[i])
                                {
                                    cout << "You have already guessed '" << letter << "'.";
                                    delay(1500);
                                    counter++;
                                    system("cls");
                                    checkWrongGuesses(chances); //checks how many chances you have left and prints animation
                                    cout << '\n' << _Word << '\n' << '\n';
                                    cout << "You have already guessed: ";
                                    for (int i = 0; i < wrongG; i++) {cout << guessed_letters[i] << ", ";}
                                }
                        }
                        if (counter == 0) {lCheck = false;}
                    }

                    int j = 0;
                    j = word.find(letter, j); //searches if letter is found in the word

                    if (j == string::npos) //if j is not in the word
                    {
                        chances--; //decrease chances
                        wrongG++; //increase wrong guesses
                        guessed_letters[wrongG - 1] = letter; //the incorrect letter gets placed as an element in the array at wrongG - 1 position
                        cout << '\n' << "Incorrect :( ";
                        delay(400);
                    }
                    else //j is not the end of the string (so is in the word)
                    {
                        while(j != string::npos) //while j is not the end of the string
                        {
                            _Word[(2*j)] = letter; //inserts letter at position j
                            j = word.find(letter, j+1);
                        }
                        cout << '\n' << "Correct!!";
                        delay(400);
                    }

                    system("cls");
                    checkWrongGuesses(chances); //checks how many chances you have left and prints animation

                    int n {checkCompletedWord(word, _Word)}; //checks for completed word and returns n to increment winNum
                    winNum = n;
                }

                //Now either there are no more chances or the whole word has been found, the round is over
                if (chances == 0) //no more chances, full animation drawn
                {
                    cout << "Unlucky " << player1 << ", the word was: '" << word << "'"
                    << '\n' << '\n' << "Congratulations " << player2 << "!!";
                    P2_points++;
                }
                else //the whole word has been found
                {
                    cout << "Congratulations " << player1 << "!! You successfully guessed: '" << word << "'"
                    << '\n' << '\n' << "Unlucky " << player2 << " :(";
                    P1_points++;
                }

                delay(2500);
                round_number++; //move onto the next round
                system("cls");
            }
        } //end of while means either Player 1 or Player 2 has reached the total points

        checkWinningPlayer(P1_points, player1, P2_points, player2, total_points); //checks to see which player has won and prints winning message

    }


    if (choice == '1') //then you are playing one player vs the computer
    {
        cout << "At your own risk you have chosen to face HAL the Hangman computer..." << '\n' << "He's a fierce competitor so good luck :) " ;
        delay(2000);
        cout << '\n' << '\n' << "Player 1 enter your name: ";
        cin >> player1;
        system("cls");

        srand(time(NULL));
        int randRound = (rand()%5)+1; //random number 1-5 as a suggestion for points to play to

        cout << "You get 1 point for winning each round (guessing HAL's word). " << '\n'
        << "HAL would like to play to " << randRound << " points, but you can choose." << '\n' << '\n';

        bool wCheck = true;
        while (wCheck) //while the check is true this runs, two if clauses cause this to change to false and exit
        {
            cout << "How many points would you like to play to, " << player1 << "? ";
            cin >> total_points;
            system("cls");

            if (total_points == randRound)
            {
                cout << "Looks like you agreed with HAL on playing to " << randRound << " points, let's get started!!";
                wCheck = false;
            }
            if (total_points != randRound && total_points < 6 && total_points > 0)
            {
                cout << "Looks like you chose to play to " << total_points << " points, instead of HAL's preferred " << randRound << " points."
                << '\n' << "Careful don't make HAL too angry... ";
                wCheck = false;
            }
            if (total_points <= 0)
            {
                cout << "ERROR. You cannot have 0 or negative points. Try again. " << '\n';
            }
            if (total_points >= 6)
            {
                cout << total_points << " is too many points. HAL will get tired before then." << '\n';
            }
        } //while loop is over so total points has been selected
        delay(3500);
        system("cls");

        while ((P1_points != total_points) && (comp_points != total_points)) //while neither player 1 or computer has won
        {
            chances = 8;
            winNum = 0;
            wrongG = 0; //reinitialise chances, winNum and wrongG to default values

            if (round_number != 1) //displays point scores unless it's round 1 (obviously 0-0)
            {
                cout << "This is Round: " << round_number << ". " << player1 << " has " << P1_points << " point(s). HAL has " <<
                comp_points << " point(s)" << '\n' << "Remember it's first to " << total_points << " points!" << '\n' << '\n';
            }

            cout << "HAL is thinking of a word, be patient... ";
            delay(4500);
            system("cls");

            srand(time(NULL));
            int lenL = sizeof(allWords38)/sizeof(allWords38[0]);
            int randWordPos = (rand()%lenL) - 1;
            string randWord = allWords38[randWordPos];

            string comp_Word {createUnderscoredWord(allWords38[randWordPos])};
            int k = randWord.length();

            //loop to check if a given letter is in the word or not, also checks remaining chances for animation and checks for completed word
            while ((chances != 0) && (winNum != k)) //chances = 0 no more guesses, winNum = word length then all the letters have been found
            {
                cout << '\n' << comp_Word << '\n' << '\n';

                cout << "You have already guessed: ";
                for (int i = 0; i < wrongG; i++) {cout << guessed_letters[i] << ", ";}

                char letter;
                bool lCheck = true;
                //loop to check if a guessed letter has already been guessed incorrectly
                while (lCheck)
                {
                    cout << '\n' << player1 << ", guess a letter, you have " << chances << " chance(s) remaining: ";
                    cin >> letter;

                    int counter = 0;
                    for (int i = 0; i < wrongG; i++)
                    {
                        if (letter == guessed_letters[i])
                            {
                                cout << "You have already guessed '" << letter << "'.";
                                delay(1500);
                                counter++;
                                system("cls");
                                checkWrongGuesses(chances); //checks how many chances you have left and prints animation
                                cout << '\n' << comp_Word << '\n' << '\n';
                                cout << "You have already guessed: ";
                                for (int i = 0; i < wrongG; i++) {cout << guessed_letters[i] << ", ";}
                            }
                    }
                    if (counter == 0) {lCheck = false;}
                }

                int j = 0;
                j = randWord.find(letter, j); //searches if letter is found in the word

                if (j == string::npos) //if j is not in the word
                {
                    chances--; //decrease chances
                    wrongG++; //increase wrong guesses
                    guessed_letters[wrongG - 1] = letter; //the incorrect letter gets placed as an element in the array at wrongG - 1 position
                    cout << '\n' << "Incorrect :( ";
                    delay(400);
                }
                else //j is not the end of the string (so is in the word)
                {
                    while(j != string::npos) //while j is not the end of the string
                    {
                        comp_Word[(2*j)] = letter; //inserts letter at position j
                        j = randWord.find(letter, j+1);
                    }
                    cout << '\n' << "Correct!!";
                    delay(400);
                }

                system("cls");
                checkWrongGuesses(chances); //checks how many chances you have left and prints animation

                int n {checkCompletedWord(randWord, comp_Word)}; //checks for completed word and returns n to increment winNum
                winNum = n;


            }

            //Now either there are no more chances or the whole word has been found, the round is over
            if (chances == 0) //no more chances, full animation drawn
            {
                cout << "Unlucky " << player1 << ", the word was: '" << randWord << "'"
                << '\n' << '\n' << "HAL has proven his superiority ";
                comp_points++;
            }
            else //the whole word has been found
            {
                cout << "Congratulations " << player1 << "!! You successfully guessed HAL's word: '" << randWord << "'"
                << '\n' << '\n' << "HAL is getting more angry ";
                P1_points++;
            }

            delay(2500);
            round_number++; //move onto next round
            system("cls");
        }

        //Now either player 1 or computer has reached the total points and won the game
        checkWinVsComp (player1, P1_points, total_points, comp_points);
    }

    cout << endl;
}


//check guess cannot be a function because within it chances can be changed and the guessed letter has to be added to an array
//and the new underscored word has to be returned this cannot all be done and returned in one function
//atm computer cannot guess letters because creating a new array with a new length cannot be done in a loop due to C++ limitations
//limitations: _Word cannot be > 10 characters long or winNum goes too large idk why
