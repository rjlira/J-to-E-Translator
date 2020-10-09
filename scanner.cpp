#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 11 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Paolo Rimando
/* RE:
(vowel | vowel n | consonant vowel | consonant vowel n |
   consonant-pair vowel | consonant-pair vowel n)^+   
 */
bool word (string s)
{

  int state = 0;
  int charpos = 0;

  while(s[charpos] != '\0')
    {
      //cout << "state " << state << endl;
      //cout << "char " << s[charpos] << endl;

      if(state == 0){// q0 ************
	switch(s[charpos]){
	case 'a': case 'e':
	case 'i': case 'o':
	case 'u':
	case 'E': case 'I':
	  state = 1; // q010
	  break;
	case 'd': case 'w':
        case 'y': case 'z':
        case 'j':
          state = 2; // qsa
          break;
	case 'b': case 'm':
        case 'k': case 'n':
        case 'h': case 'p':
        case 'r': case 'g':
          state = 3; // qy
          break;
	case 't':
	  state = 4; // qt
	  break;
	case 's':
	  state = 5; // qs
	  break;
	case 'c':
	  state = 6; // qc
	  break;
	default:
	  return false;
	}
      }
      else if(state == 1){// q0q1 ************
	switch(s[charpos]){
	case 'n':
	  state = 0; // q0
	  break;
	case 'a': case 'e':
        case 'i': case 'o':
        case 'u':
        case 'E': case 'I':
	  break; // stay q0q1
	case 'd': case 'w':
        case 'y': case 'z':
        case 'j':
	  state = 2; // qsa
	  break;
	case 'b': case 'm':
        case 'k':
        case 'h': case 'p':
        case 'r': case 'g':
	  state = 3; // qy
	  break;
	case 't':
	  state = 4; // qt
	  break;
        case 's':
	  state = 5; // qs
	  break;
        case 'c':
	  state = 6; // qc
	  break;
	default:
	  return false;
	}
      }
      else if(state == 2){// qsa ************
	switch(s[charpos]){
	case 'a': case 'e':
        case 'i': case 'o':
        case 'u':
        case 'E': case 'I':
	  state = 1; // q0q1
	  break;
	default:
	  return false;
	}
      }
      else if(state == 3){// qy ************
	switch(s[charpos]){
	case 'a': case 'e':
        case 'i': case 'o':
        case 'u':
        case 'E': case 'I':
	  state = 1; // q0q1
	  break;
        case 'y':
	  state = 2; // qsa
	  break;
	default:
	  return false;
	}
      }
      else if(state == 4){// qt ************
	switch(s[charpos]){
	case 'a': case 'e':
        case 'i': case 'o':
        case 'u':
        case 'E': case 'I':
          state = 1; // q0q1
	  break;
        case 's':
          state = 2; // qsa
	  break;
        default:
          return false;
	}
      }
      else if(state == 5){// qs ************
	switch(s[charpos]){
	case 'a': case 'e':
        case 'i': case 'o':
        case 'u':
        case 'E': case 'I':
          state = 1; // q0q1
	  break;
        case 'h':
          state = 2; // qsa
	  break;
        default:
          return false;
        }
      }
      else if(state == 6){// qc ************
	switch(s[charpos]){
        case 'h':
          state = 2; // qsa
	  break;
        default:
          return false;
        }
      }

      charpos++;
    }
      
  if(state == 0 || state == 1)
    {return true;}
  else{return false;}

  //}
  /* replace the following todo the word dfa  **
  while (s[charpos] != '\0') 
    {
      if (state == 0 && s[charpos] == 'a')
      state = 1;
      else
      if (state == 1 && s[charpos] == 'b')
      state = 2;
      else
      if (state == 2 && s[charpos] == 'b')
      state = 2;
      else
	  return(false);
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
  */
}

// PERIOD DFA
// Done by: ** Paolo Rimando
bool period (string s)
{  // complete this **
  if(s == "."){
    return true;
  }else{
    return false;
  }
}


// ------ Three  Tables -------------------------------------

// TABLES Done by: Ralph Lira

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBPAST, VERBNEG, VERBPASTNEG,
		IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBPAST", "VERBNEG", "VERBPASTNEG",
			"IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM" }; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.

string reservedWords[30][2] = {
  {"masu", ""},
  {"masen", ""},
  {"mashita", ""},
  {"masendeshita", ""},
  {"desu", ""},
  {"deshita", ""},
  {"o", ""},
  {"wa", ""},
  {"ni", ""},
  {"watashi", "I/me"},
  {"anata", "you"},
  {"kare", "he/him"},
  {"kanojo", "she/her"},
  {"sore", "it"},
  {"mata", "Also"},
  {"soshite", "Then"},
  {"shikashi", "However"},
  {"dakara", "Therefore"},
  {"eofm", ""}

};

tokentype reservedWordsType[30] = {
  VERB,
  VERBNEG,
  VERBPAST,
  VERBPASTNEG,
  IS,
  WAS,
  OBJECT,
  SUBJECT,
  DESTINATION,
  PRONOUN,
  PRONOUN,
  PRONOUN,
  PRONOUN,
  PRONOUN,
  CONNECTOR,
  CONNECTOR,
  CONNECTOR,
  CONNECTOR,
  EOFM
};


// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Esai Delgado
int scanner(tokentype& tt, string& w)
{
  bool reserved = false;
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.
  fin >> w;
  if(w == "eofm")
    return 0;

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */
  if(period(w))
    tt = PERIOD;
  else if(word(w))
    {
      for(int i = 0; i < 30; i++)
	{
	  if(w == reservedWords[i][0])
	    {
	      tt = reservedWordsType[i];
	      reserved = true;
	    }
	}
      if(!reserved)
	{
	  if(w[w.length() - 1] == 'I' || w[w.length() - 1] == 'E')
	    tt = WORD2;
	  else
	    tt = WORD1;
	}
    }
  else
    {
      cout << "LEXICAL ERROR: " << w << " is not a valid token" << endl;
      tt = ERROR;
    }
  return 0;

}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

