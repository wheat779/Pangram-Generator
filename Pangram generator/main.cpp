/*.
This program generated pangrams (sentences containing every letter) 
 with the same sentence format as "the quick brown fox jumps over 
 the lazy dog" but with random substitution of sentence parts.
 
A vector of strings with the sentence structure "the [adjective] 
 [color/pattern] [animal] [adjective] [preposition] the [adjective] 
 [animal]" is created . Four of these words are randomly selected,
 and the remaining three are chosen by searching for words containing
 low-frequency letters not already contained in the pangram.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>
#include <random>
#include <cmath>
#include <ctime>


using namespace std;

// Open a text file (file location is argument) delineated
// by returns and create vector
vector<string> getVectorFromFile(string fileName);

// Randomly selects and returns a string from a vector argument
string randSelect(vector<string> wordType);

// Return true if argument string is a pangram
bool isPangram(string sentence);


// Create strings holding file locations of txt files
// holding words delineated by returns
    string animalFile = "./animals.txt";
    string prepFile = "./prepositions.txt";
    string adjFile ="./adjectives.txt";
    string colorFile ="./colors.txt";
    string verbFile ="./verbs.txt";



/*
 Pangram class creates private string var each dedicated to a word fitting
 the "quick brown fox jumps over lazy dog" format of "[adjective] [color] 
 [animal] [verb] [preposition] [adjective] [animal]"
 
 These words are put into a vector, with functions for selecting words
 for the pangram. Initially four words are selected randomly, and the 
 remaining three are selected by looking for words containing low-frequency
 letters that are not already present in the pangram.
 
 The initial random selection ensures that the sentence does not solely
 contain more 'exotic' words chosen because they contain low frequency letters.
 The second selection of three words containing low frequency letters
 increases the number of sentences that end up becoming pangrams.
 */
class pangram{

    //Create vectors of the entries in the file locations
    vector<string> animals = getVectorFromFile(animalFile);
    vector<string> prepositions = getVectorFromFile(prepFile);
    vector<string> adjectives = getVectorFromFile(adjFile);
    vector<string> colors = getVectorFromFile(colorFile);
    vector<string> verbs = getVectorFromFile(verbFile);
    
    //Create strings to hold sentence portions
    string adjective1 = "adjective1";
    string color = "color";
    string animal1 = "animal1";
    string verb = "verb";
    string prep = "prep";
    string adjective2 = "adjective2";
    string animal2 = "animal2";
    
    // Vars determing the amount of random vs. non-random words
    int totalWords = 7;
    int numRandWords = 4;
    
    // Vector holding the words of the pangram sentence (minus "the"s)
    vector<string> pangram;
    
    // Vector tracking which words have been filled in the pangram
    vector<bool> wordFilled;
    
public:
    //Set the pangram vector to contain the names of each sentence part
    void emptyPangram();
    //Replace four of the sentence-part names with randomly selected words
    void randomHalfPangram();
    //Fill the remaining three words based on which low-frequency letters
    //are still needed
    void fillPangram();
    // Fills an empty word in the pangram with a word containing
    // the string (letter) in the argument
    void fillWord(string letter);
    // Outputs pangram to screen
    void coutPangram();
    // Returns a string version of the pangram vector
    string getPangram();
    // Outputs to screen the number of pangrams input into the argument
    void generatePangrams(int numPangrams);
};

int main() {
    srand(std::time(0)); // Seed random number generator with time

    pangram test; // Create pangram object
    test.generatePangrams(5); // output five pangrams to screen

}

/*
 Function takes in a file location, reads line by line and adds each line 
 as a string to a vector.
 
 Returns a vector containing each line of text.
 */
vector<string> getVectorFromFile(string fileName){
    
    stringstream ss; //Create stringstream object
    string line; // Object for holding each line of the text document
    vector<string> textVec;
    
    //read in the text file into a string stream
    ifstream textDoc (fileName);
    if(textDoc.is_open()){
        while (getline (textDoc, line)){
            
            ss << line << " ";
            textVec.push_back(line);
        }
        
        textDoc.close();
    }
    else{
        cout << "unable to open file";
        
    }
    return textVec;
}


// Randomly select a word from the string vector and return it
string randSelect(vector<string> wordType){
    return wordType[rand() % wordType.size()];
};

// Function returns true if string parameter contains letters a-z
bool isPangram(string sentence){
    //Sort the possible pangram alphabetically
    sort(sentence.begin(), sentence.end());
    
    // If the sorted potential pangram contains all the letters
    // included in string "alphabet", return true
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    return includes(sentence.begin(), sentence.end(), alphabet.begin(), alphabet.end());
}

/*
 Fill the empty pangram vector with place-holding sentence part names
 such that the vector holds: 
 "[adjective1] [color] [animal1] [verb] [prep] [adjective2] [animal2]"
 keeping the structure of "the quick brown fox jumps over the lazy dog"
 */
void pangram::emptyPangram(){
    pangram.push_back(adjective1);
    pangram.push_back(color);
    pangram.push_back(animal1);
    pangram.push_back(verb);
    pangram.push_back(prep);
    pangram.push_back(adjective2);
    pangram.push_back(animal2);
}
/*
 Randomly fills 4 of the 7 words in the pangram with sentence appropriate
 words. Also creates the "wordFilled" vector of bools to track which
 words in the sentence have already been filled with words (1) or are
 still empty and need to be filled (0).
 */
void pangram::randomHalfPangram(){
    // Set a vector of bools to 0, this will track which
    // words have been randomized. This is used by the "fillPangram" function
    for(int i = 0; i < totalWords; i++){
        wordFilled.push_back(0);
    }
    
    /*
     Loop runs until the number of specified random words have been
     added to the pangram vector.
     
     It does this by randomly selecting a location in the pangram vector,
     if that location still has its default word-part name (e.g. "verb")
     it is replaced with a random word from the vector containing a list
     of appropriate words for that part of the sentence.
     
     If the location in the pangram vector randomly chosen already contains
     a random word, then the loop retries another random vector location
     */
    for(int i = 0; i < numRandWords; i++){
        
        /*
         Randomly select a number corresponding to a location in the
         pangram vector, and set the string "word" to the value
         in that location. Set the tracking vector "wordFilled" to
         "true" for that location, indicating the pangram vector
         now has a random word at that location
        */
        int wordNum = rand() % pangram.size();
        string word = pangram[wordNum];
        wordFilled[wordNum] = true;
        
        // If the randomly chosen word is an adjective placeholder
        // replace it with a random adjective
        if(word == "adjective1"){
            pangram[wordNum] = randSelect(adjectives);
        }
        else if(word == "color"){
            pangram[wordNum] = randSelect(colors);
        }
        else if(word == "animal1"){
            pangram[wordNum] = randSelect(animals);
        }
        else if(word == "verb"){
            pangram[wordNum] = randSelect(verbs);
        }
        else if(word == "prep"){
            pangram[wordNum] = randSelect(prepositions);
        }
        else if(word == "adjective2"){
            pangram[wordNum] = randSelect(adjectives);
        }
        else if(word == "animal2"){
            pangram[wordNum] = randSelect(animals);
        }
        else i--; // If the randomly chosen word isn't a placeholder, rerun loop
    
    }
}

// Outputs a formatted version of the vector containing the pangram words
// to screen
void pangram::coutPangram(){
    
    for(int i = 0; i < pangram.size(); i++){
        if( i == 0 || i == 5) cout << "the "; // Put "the" before the first and fifth words
        cout << pangram[i] << " ";
    }
}
/*
 Function fills in remaining words of the pangram by selecting for words that
 contain letters that are (1) are not already present in the pangram, 
 and (2) are low frequency letters in English sentences.
 
 Selecting for words with low-frequency letters dramatically increases the
 chances that a randomly generated sentence will end up being a pangram.
 */
void pangram::fillPangram(){
    // Create a object that will hold a string version
    // of the non-placeholder words in our pangram vector
    string pangramSentence;
    
    // Create a vector holding the English letters that have a frequency
    // of less than >1% in English sentences
    vector<string> lowFreqLetters;
    lowFreqLetters.push_back("j");
    lowFreqLetters.push_back("x");
    lowFreqLetters.push_back("q");
    lowFreqLetters.push_back("w");
    lowFreqLetters.push_back("f");
    lowFreqLetters.push_back("v");
    lowFreqLetters.push_back("m");
    lowFreqLetters.push_back("y");
    lowFreqLetters.push_back("z");
    
    /*
     Appends word from our pangram vector to our pangramSentence string
     if it was already set to a random word by the randomHalfPangram 
     function. If the entry in our pangram vector contains a placeholder
     it is skipped.
     
     Thus pangramSentence holds the first half of our pangram sentence.
     */
    for(int i = 0; i < totalWords; i++){
        if(wordFilled[i] == 1){
            pangramSentence.append(pangram[i]);
        }
    }
    
    // Set int wordCount to the current number of words in
    // our pangram.
    int wordCount = numRandWords;
    
    /*
     Loop runs through the vector of low-frequency words (by increasing i)
     until wordCount == totalWords. Thus the loop ends when all words are
     filled, or there are not more low-frequency letters to add.
     */
    for(int i = 0; wordCount != totalWords; i++){
        
        /*
         If the pangramSentence doesn't have the current lowFrequencyLetter
         randomly select a word that isn't filled yet that contains that 
         letter. Then increase the current count of words present in the
         pangram.
         */
        if(pangramSentence.find(lowFreqLetters[i]) == string::npos){
            fillWord(lowFreqLetters[i]);
            wordCount++;
        }
        // If we have exhausted the list of lowFrequencyLetters, end the loop
        if(i == lowFreqLetters.size() -1){
            wordCount = totalWords;
        }
    }
}

/*
 Function takes a string letter as an argument for what low 
 frequency letter is needed. It randomly selects from missing words 
 in the pangram sentence and when one is found to contain the needed
 letter, it adds that word to the pangram.
 */
void pangram::fillWord(string letter){
    
    // Start loop
    bool looping = 1;
    while(looping){
    
        // Randomly select word location in pangram vector
        int wordSelect = rand() % totalWords;
    
        // If that location doesn't have a word...
        if(wordFilled[wordSelect] == 0){
        
        // If the randomly selected location is pangram[0] or pangram[5]
        // then it's an adjective. Randomly select an adjective.
        if(wordSelect == 0 || wordSelect == 5){
            string adjective = randSelect(adjectives);
            // If the chosen word contains the desired letter
            // add to the pangram, mark this location as filled
            // by a word, and end the loop.
            if(adjective.find(letter) != string::npos){
                pangram[wordSelect] = adjective;
                looping = 0;
                wordFilled[wordSelect] = 1;
            }
            // If the randomly selected word does not contain the
            // desired letter, rerun the loop.
        }
    
        else if(wordSelect == 1){
            string color = randSelect(colors);
            if(color.find(letter) != string::npos){
                pangram[wordSelect] = color;
                looping = 0;
                wordFilled[wordSelect] = 1;
            }
        }
        else if(wordSelect == 2 || wordSelect == 6){
            string animal = randSelect(animals);
            if(animal.find(letter) != string::npos){
                pangram[wordSelect] = animal;
                looping = 0;
                wordFilled[wordSelect] = 1;
            }
        }
        else if(wordSelect == 3){
            string verb = randSelect(verbs);
            if(verb.find(letter) != string::npos){
                pangram[wordSelect] = verb;
                looping = 0;
                wordFilled[wordSelect] = 1;
            }
        }
        else if(wordSelect == 4){
            string prep = randSelect(prepositions);
            if(prep.find(letter) != string::npos){
                pangram[wordSelect] = prep;
                looping = 0;
                wordFilled[wordSelect] = 1;
            }
        }
        else cout << "no word found";
    }
    }
}

// Returns pangram vector as a formatted string sentence
string pangram::getPangram(){
    string pangramString;
    
    for(int i = 0; i < pangram.size(); i++){
        // Put "the" before the first and sixth words
        // "THE quick brown fox jumps over THE lazy dog"
        if( i == 0 || i == 5) pangramString.append("the ");
        
        pangramString.append(pangram[i]);
        pangramString.append(" ");
    }
    return pangramString;
}

// Output to screen the number of pangrams specified in the argument
void pangram::generatePangrams(int numPangrams){
    
    // Create a count of how many pangrams have been output
    int pangramCount = 0;
    
    while(pangramCount < numPangrams){
        class pangram test; // Create pangram object
        test.emptyPangram(); // Format with placeholders
        test.randomHalfPangram(); // Randomize 4 words
        test.fillPangram(); // Fill with needed lowFreq words
        string pan = test.getPangram(); // Format pangram object to string
        
        // If it's a pangram, output it to screen, and increase pangram count
        // otherwise, try again.
        if(isPangram(pan)){
            test.coutPangram();
            cout << endl << endl;
            pangramCount++;
        }
    }
}

