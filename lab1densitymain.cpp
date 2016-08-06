/**
 * @Lab01 Population Density
 * @author Sean Lai
 * @January 12, 2014
 *
 * This program will intake a text file of data containing country name,
 * country area, and country population. The methods will read the file
 * and creates an array that sorts the list of countries from order of
 * highest density to lowest density.
 *
 * Additional information will be printed, such as median density, average
 * density, highest and lowest density etc.
 *
 */

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXRECORDS = 250;        // maximum number of records in file
int const MAXLENGTH = 32;          // maximum country name length
int const MINAREA = 0;             // smallest possible area in km^2
char const INPUTFILE[] = "lab1data1.txt" ;  // you must submit with this filename

struct CountryStats   {            // data for one country
    int population;
    int area;                       // km^2
    double density;                 // pop/area (should this be stored?)
    char countryName[MAXLENGTH];    // country name (MAXLENGTH-1 at most)
};

/** Prototype functions contain two methods, sortInput and displayRecords.
 sortInput will take the text file and sort them to an array from most to
 least density using insertion sort.
 displayRecords will use the sorted Array and print informations such as
 median and average densities of countries.
 displayExplanation shows my explanation that explains why the two averages
 area significantly different.
 */
bool sortInput(ifstream& infile, CountryStats countries[], int& count); // e.g.
void displayRecords(CountryStats countries[], int& leastDensity);
void displayExplanation();

/**------------------------------- main -----------------------------
 Main file to run the program, will catch an error if the file is different
 from the named constant, which in this case 'lab1data1.txt'.
 Runs the sortInput if the file could be read, and then runs the displayRecords.
 Also contains the debug codes.
 */
int main( int argc, char* argv[] ) {
    bool debug = strcmp(argv[argc -1], "DEBUG") == 0 ? true : false;
    
    CountryStats countries[MAXRECORDS];
    int indexCount = 0; // number of records processed. Must use a better variable name to eliminate this comment.
    int leastDensity = 0;
    
    ifstream infile(INPUTFILE);  // create file object and open the data file
    if (!infile)  {
        cerr << "File could not be opened." << endl; // must be a named constant
        return false;
    }
    
    // get record and sort each, as encountered, by density and country name
    bool successfulRead = sortInput(infile, countries, indexCount);
    
    if (debug){
        cout << "in main, country: " << countries[MAXRECORDS].countryName
        << ", pop: " <<  countries[MAXRECORDS].population
        << ", area: " << countries[MAXRECORDS].area
        << ", density:  " << countries[MAXRECORDS].density  // not to specs.
        << ", count:  " << indexCount;
    }
    
    // If the file is read and sorted successfully, the sorted Array will be used
    // to display records and data.
    if (successfulRead)  {
        displayRecords(countries, leastDensity);
        displayExplanation();
    }
    
    return true;
} // int main

/* ----------------------------------------------------------------------------
 Sorts the input file, and prints the array of the newly created
 construct contain name, area, population and density of countries in
 the order of highest to lowest population density.
 I've approached this differently from the pseudocode, I am searching
 for index where the new country density is larger than the current, and
 if found, it will bump all the current one down by one.
 
 @param infile text file containing data for the countries
 @param countries[] the array data containing the countries
 @param indexCount int variable that counts the number of countries inserted
 */
bool sortInput(ifstream& infile, CountryStats countries[], int& indexCount){
    CountryStats newCountry;
    double VaticanCityArea = 0.44;
    // This loop will make all the density -1, so it's easier to identify data for
    // the array indexes that's not filled up.
    for (int i = 0; i < MAXRECORDS; i++) {
        countries[i].density = -1;
    }
    while (!infile.eof()) {
        infile >> newCountry.countryName
        >> newCountry.population
        >> newCountry.area;
        // Exception is made for Vatican City, which has area less than 1 km^2,
        // the true area for Vatican city in real number is 0.44 km^2.
        if (newCountry.area == 0) {
            newCountry.density =
            (double) newCountry.population / VaticanCityArea ;
        }
        else {
            newCountry.density =
            (double) newCountry.population / (double) newCountry.area ;
        }
        indexCount++;
        int checkCount = MAXRECORDS;
        bool keepChecking = true;
        
        while (keepChecking && checkCount >= MAXRECORDS - indexCount ) {
            checkCount--;
            if (newCountry.density > countries[checkCount].density) {
                
                for (int j = MAXRECORDS - indexCount; j < checkCount; j++) {
                    countries[j] = countries[j+1];
                }
                countries[checkCount] = newCountry;
                keepChecking = false;
            }
            else if (newCountry.density == countries[checkCount].density && strcmp(newCountry.countryName, countries[checkCount].countryName) > 0) {
                for (int j = MAXRECORDS - indexCount; j < checkCount; j++) {
                    countries[j] = countries[j+1];
                }
                countries[checkCount] = newCountry;
                keepChecking = false;
            }
            else {
                keepChecking = true;
            }
        }
    }
    return true;
}

/* ----------------------------------------------------------------------------
 Using the sorted array of country data, records and displays the data including
 most and least dense country, median density, arithmetic average of densities,
 and sum of all population divided by sum of all areas. Also contains my explanation
 for the difference in the two methods of average calculation.
 
 @param countries[] the array data containing the sorted countries
 @param leastDensity int variable that counts the number of indexes not used in the
 sorted array.
 */
void displayRecords(CountryStats countries[], int& leastDensity) {
    
    // Variables that will store the data for total density, total population,
    // and total area.
    double totalDensity = 0;
    double totalPopulation = 0;
    double totalArea = 0;
    
    // The main loop to calculate all the datas, and prints the base sorted array
    for(int i = MAXRECORDS - 1; i >= 0; i--) {
        if (countries[i].density != -1) {
            totalDensity = totalDensity + countries[i].density;
            totalArea = totalArea + (double) countries[i].area;
            totalPopulation = totalPopulation + (double) countries[i].population;
            cout << countries[i].countryName << " " << countries[i].area << " " << countries[i].population << " " << countries[i].density << endl;
        }
        else {
            leastDensity++;
        }
    }
    // Since the file is not exactly 250 countries, leastDensity variable will find the
    // index that cuts off the least dense country.
    cout << endl << "Most dense country: " << countries[MAXRECORDS-1].countryName
    << endl << "Least dense country: " << countries[leastDensity].countryName
    << endl;
    
    // Median calculation will differ depending on if the data contains odd or even
    // number of indexes.
    int medianIndex = (MAXRECORDS - leastDensity) / 2;
    if (medianIndex % 2 == 0){
        cout << "Median density is: " << ((double)countries[medianIndex].density
                                          + (double)countries[medianIndex + 1].density)/2 << endl;
    }
    else {
        cout << "Median density is: " << (double) countries[medianIndex].density << endl;
    }
    cout << "Arithmetic Average of all densities: "
    << totalDensity / MAXRECORDS - leastDensity << endl;
    cout << "Sum of all population / Sum of all area = "
    << totalPopulation / totalArea << endl;
}
/* ----------------------------------------------------------------------------
 My explanation for why the average of arithmetic and sum of all population/area
 is different from each other, and which one is a more representation.
 */
void displayExplanation() {
    // My explanation goes here for the difference of the above two calculations.
    cout << endl << "The arithmetic average and sum of all P/A is significantly " << endl
    << "different because arithmetic average is a scaled down data being calculated," << endl
    << "and thus having a less accurate representation than the sum P/A. Since sum " << endl
    << "of all P/A is using all of the raw data combined, it is the most accurate calculation.";
}

