/** You must write meaningful doxygen comments and assumptions here
 */

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXRECORDS = 250;        // maximum number of records in file
int const MAXLENGTH = 32;          // maximum country name length 
int const MINAREA = 0;             // smallest possible area in km^2
char const INPUTFILE[] = "lab1data1.txt" ; //you must submit with this filename
bool debug = false;                // GLOBAL can be changed by command line

struct CountryStats   {            // data for one country     
   int population;
   int area;                       // km^2
   double density;                 // pop/area (should this be stored?)
   char countryName[MAXRECORDS];    // country name (MAXLENGTH-1 at most)  
};

/**  prototypes with doxygen style comments must go here 
*/
bool sortInput(ifstream& infile, CountryStats countries[], int& count); // e.g.

/**------------------------------- main -----------------------------
   You must write meaningful doxygen comments and assumptions here 
*/
int main( int argc, char* argv[] ) {
   debug = strcmp(argv[argc -1], "DEBUG") == 0 ? true : false; 
   cout << "1debug:" << debug << endl;
   bool successfulRead = false;
   
   CountryStats countries[MAXRECORDS]; 
   int count = 0; // number of records processed. 
                  // Must use a better variable name to eliminate this comment.
 
   ifstream infile(INPUTFILE);  // create file object and open the data file
   if (!infile)  { 
      cerr << "File could not be opened." << endl; // must be a named constant
      return false;  
   }

// get record and sort each, as encountered, by density and country name
   if ( debug ) cout << "2debug:" << debug << endl;
   successfulRead = sortInput(infile, countries, count);
   if ( debug  ) cout << "3debug:" << debug << endl; 
   if ( debug  ) cout << "successfulRead:" << successfulRead << endl;
   if ( debug  ) cout << "4debug:" << debug << endl; 
      
   if ( debug == true ) { cout << "5debug:" << debug << endl;
      cout << "in main after read, country: " 
           << countries[MAXRECORDS-1].countryName
           << ", pop: " <<  countries[MAXRECORDS-1].population 
           << ", area: " << countries[MAXRECORDS-1].area                         
           << ", density:  " << countries[MAXRECORDS-1].density  // not to specs.
           << ", count:  " << count;
   } 
                 
  // if (successfulRead)  
  {  // do all required tasks 
      
/* you must create methods to do (at least) each of the following tasks
  1.	display each record, one country per line ....
  displayList(... you figure parameters ...); // for example
  ...
  6.	explain the results of step 4 and 5 above 
*/
   } // if (successfulRead)
   
   return true;
} // int main

/* --------------------------------------------------------------------------
 functions and You must write meaningful doxygen comments and assumptions here
*/

bool sortInput(ifstream& infile, CountryStats countries[], int& count){

   infile >> countries[MAXRECORDS-1].countryName
          >> countries[MAXRECORDS-1].population
          >> countries[MAXRECORDS-1].area;
                          
   countries[MAXRECORDS-1].density = 
      /* why is this wrong? */
      countries[MAXRECORDS-1].population / countries[MAXRECORDS-1].area ; 
      count++;

   return true;
}  // bool sortInput
