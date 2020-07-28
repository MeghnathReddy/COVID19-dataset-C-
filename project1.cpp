#include <iostream>
using namespace std;

class COVID19 {
protected:
    char* date;
    char* county;
    char* state;
    int fips;
    int cases;
    int deaths;

public:
    //default constructor
    COVID19() {
        date = NULL;
        county = NULL;
        state = NULL;
        fips = 0;
        cases = 0;
        deaths = 0;
    };
    //non-default constructor
    COVID19(char* da, char* co, char* s, int f, int ca, int de) {
        date = new char[11];
        for (int i = 0; i < 11; i++) {
            date[i] = da[i];
        }
        county = new char[50];
        for (int i = 0; i < 50; i++) {
            county[i] = co[i];
        }
        state = new char[50];
        for (int i = 0; i < 50; i++) {
            state[i] = s[i];
        }
        fips = f;
        cases = ca;
        deaths = de;
    }
    ~COVID19() {};
    void display();
    char* getdate();
    void setdate(char* da);
    char* getstate();
    void setstate(char* s);
    char* getcounty();
    void  setcounty(char* co);
    int getfips();
    void setfips(int f);
    int getcases();
    void setcases(int c);
    int getdeaths();
    void setdeaths(int de);

};


//getters and setters for COVID19 class

void COVID19::display() {}
char* COVID19::getdate()
{
    return date;
}

void COVID19::setdate(char* da)
{
    this->date = da;
}

char* COVID19::getstate()
{
    return state;
}

void COVID19::setstate(char* s)
{
    this->state = s;
}

char* COVID19::getcounty()
{
    return county;
}

void COVID19::setcounty(char* co)
{
    this->county = co;
}

int COVID19::getfips()
{
    return fips;
}

void COVID19::setfips(int f)
{
    this->fips = f;
}

int COVID19::getcases()
{
    return cases;
}

void COVID19::setcases(int c)
{
    this->cases = c;
}

int COVID19::getdeaths()
{
    return deaths;
}

void COVID19::setdeaths(int de)
{
    this->deaths = de;
}

//COVID19DATASET CLASS
class COVID19DataSet {
protected:
    COVID19* allData; //crate object of COVID19
    int count; //number of COVID19 objects in allData
    int size; //maximum size of array
public:
    //default constructor
    COVID19DataSet() {
        count = 0;
        size = 0;
        allData = new COVID19[0];

    };
    //non-default constructor
    COVID19DataSet(int initSize) {
        count = initSize;
        size = 0;
        allData = new COVID19[initSize];
    };
    //destructor
    ~COVID19DataSet() {
        delete[] allData;
    };
    void display();
    void addRow(COVID19& oneData);
    //to remove left trails  
    int findTotalCasesByCounty(char* county, char* state);
    int findTotalDeathsByCounty(char* county, char* state);
    int findTotalCasesByState(char* state);
    int findTotalDeathsByState(char* state);
    int findTotalCasesBySateWithDateRange(char* state,
        char* startDate, char* endDate);
    int findTotalDeathsBySateWithDateRange(char* state,
        char* startDate, char* endDate);
    char* Trim(char* szX);

};

//Functions and methods of COVID19DATA SET
void COVID19DataSet::display() {}
void COVID19DataSet::addRow(COVID19& oneData)
{
    //get row wise values and set the values by using COVID19 class getters
    allData[count].setdate(oneData.getdate());
    allData[count].setcounty(oneData.getcounty());
    allData[count].setstate(oneData.getstate());
    allData[count].setfips(oneData.getfips());
    allData[count].setcases(oneData.getcases());
    allData[count].setdeaths(oneData.getdeaths());
    count++;
}

//to remove left trails
char* COVID19DataSet::Trim(char* szX)
{
    if (' ' == szX[0]) while (' ' == (++szX)[0]);
    return szX;
}

int COVID19DataSet::findTotalCasesByCounty(char* county, char* state)
{
    int totalcases = 0;
    for (int i = 0; i < count; i++) {
        int comparestate = 1;
        int comparecounty = 1;
        int lengthstate = sizeof(allData[i].getstate());
        int lengthcounty = sizeof(allData[i].getcounty());
        char* trimstate_command = Trim(state); //to remove leading spaces of state from command.txt
        char* trimstate_csv = allData[i].getstate(); //to remove leading spaces of state from csv if any
        char* trimcounty_command = Trim(county); //to remove leading spaces of county from command.txt
        char* trimcounty_csv = allData[i].getcounty(); //to remove leading spaces of state from csv if any

        for (int j = 0; j < lengthstate; j++) {
            if (trimstate_command[j] != trimstate_csv[j]) {
                comparestate = 0;
            }
        }
        for (int j = 0; j < lengthcounty; j++) {
            if (trimcounty_command[j] != trimcounty_csv[j]) {
                comparecounty = 0;
            }
        }
        if (comparestate && comparecounty) { //both state and county are equal
            totalcases = totalcases + allData[i].getcases();
        }
    }

    return totalcases;
}

int COVID19DataSet::findTotalDeathsByCounty(char* county, char* state)
{
    int totalcases = 0;
    for (int i = 0; i < count; i++) {
        int comparestate = 1;
        int comparecounty = 1;
        int lengthstate = sizeof(allData[i].getstate());
        int lengthcounty = sizeof(allData[i].getcounty());
        char* trimstate_command = Trim(state); //to remove leading spaces of state from command.txt
        char* trimstate_csv = allData[i].getstate(); //to remove leading spaces of state from csv if any
        char* trimcounty_command = Trim(county); //to remove leading spaces of county from command.txt
        char* trimcounty_csv = allData[i].getcounty(); //to remove leading spaces of state from csv if any

        for (int j = 0; j < lengthstate; j++) {
            if (trimstate_command[j] != trimstate_csv[j]) {
                comparestate = 0;
            }
        }
        for (int j = 0; j < lengthcounty; j++) {
            if (trimcounty_command[j] != trimcounty_csv[j]) {
                comparecounty = 0;
            }
        }
        if (comparestate && comparecounty) { //both state and county are equal
            totalcases = totalcases + allData[i].getdeaths();
        }
    }

    return totalcases;
}

int COVID19DataSet::findTotalCasesByState(char* state)
{
    int totalcases = 0;
    for (int i = 0; i < count; i++) {
        int comparestate = 1;
        int lengthstate = sizeof(allData[i].getstate());
        char* trimstate_command = Trim(state); //to remove leading spaces of state from command.txt
        char* trimstate_csv = allData[i].getstate(); //to remove leading spaces of state from csv if any

        for (int j = 0; j < lengthstate; j++) {
            if (trimstate_command[j] != trimstate_csv[j]) {

                comparestate = 0;
            }
        }
        if (comparestate) { //state in covid19 data set==command line state
            totalcases = totalcases + allData[i].getcases();
        }
    }
    return totalcases;
};
int COVID19DataSet::findTotalDeathsByState(char* state) {
    int totalcases = 0;
    for (int i = 0; i < count; i++) {
        int comparestate = 1;
        int lengthstate = sizeof(allData[i].getstate());
        char* trimstate_command = Trim(state); //to remove leading spaces of state from command.txt
        char* trimstate_csv = allData[i].getstate(); //to remove leading spaces of state from csv if any

        for (int j = 0; j < lengthstate; j++) {
            if (trimstate_command[j] != trimstate_csv[j]) {

                comparestate = 0;
            }
        }
        if (comparestate) { //state in covid19 data set==command line state
            totalcases = totalcases + allData[i].getdeaths();
        }
    }
    return totalcases;
}


int COVID19DataSet::findTotalCasesBySateWithDateRange(char* state, char* startDate, char* endDate)
{
    int totalcases = 0;

    //for start range of date from command.txt
    char startyeararr[4] = { startDate[0], startDate[1], startDate[2], startDate[3] };
    int startyear = atoi(startyeararr);

    char startmontharr[2] = { startDate[5] , startDate[6] };
    int startmonth = atoi(startmontharr);


    char startdayarr[2] = { startDate[8] , startDate[9] };
    int startday = atoi(startdayarr);

    //for end range of date from command.txt
    char endyeararr[4] = { endDate[0], endDate[1], endDate[2], endDate[3] };
    int endyear = atoi(endyeararr);

    char endmontharr[2] = { endDate[5] , endDate[6] };
    int endmonth = atoi(endmontharr);


    char enddayarr[2] = { endDate[8] , endDate[9] };
    int endday = atoi(enddayarr);

    for (int i = 0; i < count; i++) {
        int comparestate = 1;
        int lengthstate = sizeof(allData[i].getstate());
        char* trimstate_command = Trim(state); //to remove leading spaces of state from command.txt
        char* trimstate_csv = allData[i].getstate(); //to remove leading spaces of state from csv if any


        for (int j = 0; j < lengthstate; j++) {
            if (trimstate_command[j] != trimstate_csv[j]) {

                comparestate = 0;
            }
        }

        //processing date of csv

        char* csvdate = allData[i].getdate();
        char yeararr[4] = { csvdate[0], csvdate[1], csvdate[2], csvdate[3] };
        int year = atoi(yeararr);

        char montharr[2] = { csvdate[5], csvdate[6] };
        int month = atoi(montharr);

        char dayarr[4] = { csvdate[8], csvdate[9] };
        int day = atoi(dayarr);


        if (comparestate) {
            //check for the date in command file if it falls between the range of date available in csv
            if ((year<startyear and year>endyear) or (year == startyear and month < startmonth) or (year == endyear and month > endmonth) or (month == startmonth and day < startday) or (month == endmonth and day > endday)) {
                totalcases += 0;
            }
            else {
                totalcases = totalcases + allData[i].getcases();
            }

        }
    }
    return totalcases;
}

int COVID19DataSet::findTotalDeathsBySateWithDateRange(char* state, char* startDate, char* endDate)
{
    int totalcases = 0;

    //for start range
    char startyeararr[4] = { startDate[0], startDate[1], startDate[2], startDate[3] };
    int startyear = atoi(startyeararr);

    char startmontharr[2] = { startDate[5] , startDate[6] };
    int startmonth = atoi(startmontharr);


    char startdayarr[2] = { startDate[8] , startDate[9] };
    int startday = atoi(startdayarr);

    //for end range
    char endyeararr[4] = { endDate[0], endDate[1], endDate[2], endDate[3] };
    int endyear = atoi(endyeararr);

    char endmontharr[2] = { endDate[5] , endDate[6] };
    int endmonth = atoi(endmontharr);


    char enddayarr[2] = { endDate[8] , endDate[9] };
    int endday = atoi(enddayarr);

    for (int i = 0; i < count; i++) {
        int comparestate = 1;
        int lengthstate = sizeof(allData[i].getstate());
        char* trimstate_command = Trim(state); //to remove leading spaces of state from command.txt
        char* trimstate_csv = allData[i].getstate(); //to remove leading spaces of state from csv if any


        for (int j = 0; j < lengthstate; j++) {
            if (trimstate_command[j] != trimstate_csv[j]) {

                comparestate = 0;
            }
        }

        //processing date of csv

        char* csvdate = allData[i].getdate();
        char yeararr[4] = { csvdate[0], csvdate[1], csvdate[2], csvdate[3] };
        int year = atoi(yeararr);

        char montharr[2] = { csvdate[5], csvdate[6] };
        int month = atoi(montharr);

        char dayarr[4] = { csvdate[8], csvdate[9] };
        int day = atoi(dayarr);


        if (comparestate) {
            //check for the date in command file if it falls between the range of date available in csv
            if ((year<startyear and year>endyear) or (year == startyear and month < startmonth) or (year == endyear and month > endmonth) or (month == startmonth and day < startday) or (month == endmonth and day > endday)) {
                totalcases += 0;
            }
            else {
                totalcases = totalcases + allData[i].getdeaths();
            }

        }
    }
    return totalcases;
}



//Parse the CVS file
int Parse(char* currentnew_line, char* token, int idx, int currentnew_lineSize, int tokenSize, char delimiter) {
    int position, j;

    for (int i = 0; i < tokenSize; ++i) {
        token[i] = '\0';
    }
    position = idx;
    j = 0;

    while (currentnew_line[position] != delimiter) {
        token[j] = currentnew_line[position];
        ++j;
        ++position;
    }
    token[j] = '\0';
    return position;
}

//For command 5 and 6 to validate 2 worded states
int ParseCommand(char* currentnew_line, char* token, int idx, int currentnew_lineSize, int tokenSize, char delimiter, int check) {
    int position, j;

    for (int i = 0; i < tokenSize; ++i) {
        token[i] = '\0';
    }
    position = idx;
    j = 0;

    while (currentnew_line[position] != delimiter) {
        token[j] = currentnew_line[position];
        ++j;
        ++position;
    }
    if (check != 1) {
        token[j] = '\0';
    }
    else {
        token[j - 1] = '\0';
    }

    return position;
}

int main()
{
    int index;
    int counts = 0;
    int command = 0;
    char* csvfile_name = new char[16];
    char current_new_line[256];
    char comma = ',';
    char comma1 = '\0';

    //variables to hold the data set values
    char datetype[11];
    char countytype[50];
    char statetype[50];
    char fipstype[6];
    char casetype[8];
    char deathstype[8];
    COVID19 oneRow;
    COVID19DataSet* myData = new COVID19DataSet(counts);
    cin >> counts;
    cin >> csvfile_name;
    FILE* dataFie = fopen(csvfile_name, "r");
    fgets(current_new_line, 256, dataFie);
    for (int i = 0; i < counts; i++) {
        index = 0;
        fgets(current_new_line, 256, dataFie);
        index = Parse(current_new_line, datetype, index, 256, 11, comma);
        index = Parse(current_new_line, countytype, index + 1, 256, 50, comma);
        index = Parse(current_new_line, statetype, index + 1, 256, 50, comma);
        index = Parse(current_new_line, fipstype, index + 1, 256, 6, comma);
        index = Parse(current_new_line, casetype, index + 1, 256, 8, comma);
        index = Parse(current_new_line, deathstype, index + 1, 256, 8, comma1);

        oneRow = COVID19(datetype, countytype, statetype, atoi(fipstype), atoi(casetype), atoi(deathstype)); //SET ROW
        myData->addRow(oneRow); //SET ROWS OF CSV ONE BY ONE TO ALLDATA OBJECT
    }
    while (!cin.eof()) {

        cin >> command;
        switch (command) {
            //Based on command file 1-6 input following switch statements are implemented
        case 1: {
            //Get cases by county and state
            char new_line[256]; //length of current line in command file
            int iter = 0;
            char c; //to store present idex
            int result1 = 0; //to store results from the function call
            cin.get(c);
            while (c != '\n') {
                cin.get(c);
                new_line[iter] = c;
                iter++;
            }
            char counties1[50];
            char newstates1[50];
            int newcommand1 = 0;

            newcommand1 = Parse(new_line, counties1, newcommand1, 256, 50, ',');
            newcommand1 = Parse(new_line, newstates1, newcommand1 + 1, 256, 50, '\n');
            result1 = (*myData).findTotalCasesByCounty(counties1, newstates1);
            cout << counties1 << " County," << newstates1 << ", " << result1 << " CASES" << endl;

            break;
        }

        case 2: {
            //Get deaths by county and state
            char new_line[256];
            int iter = 0;
            int result2 = 0;
            char c;

            cin.get(c);
            while (c != '\n') {
                cin.get(c);
                new_line[iter] = c;
                iter++;
            }
            char counties2[50];
            char newstates2[50];
            int newcommand2 = 0;

            newcommand2 = Parse(new_line, counties2, newcommand2, 256, 50, ',');
            newcommand2 = Parse(new_line, newstates2, newcommand2 + 1, 256, 50, '\n');
            result2 = (*myData).findTotalDeathsByCounty(counties2, newstates2);
            cout << counties2 << " County," << newstates2 << ", " << result2 << " DEATHS" << endl;
            break;
        }

        case 3: {
            //get cases by state
            char new_line[256];
            int iter = 0;
            char c;
            int result3 = 0;

            cin.get(c);
            while (c != '\n') {
                cin.get(c);
                new_line[iter] = c;
                iter++;
            }

            char newstates3[50];
            int newcommand3 = 0;
            newcommand3 = Parse(new_line, newstates3, newcommand3, 256, 50, '\n');
            result3 = (*myData).findTotalCasesByState(newstates3);

            cout << newstates3 << ", " << result3 << " CASES" << endl;
            break;
        }

        case 4: {
            //get deaths by states
            char new_line[256];
            int iter = 0;
            char c;
            int result4 = 0;
            cin.get(c);
            while (c != '\n') {
                cin.get(c);
                new_line[iter] = c;
                iter++;
            }
            char newstates4[50];
            int newcommand4 = 0;
            newcommand4 = Parse(new_line, newstates4, newcommand4, 256, 50, '\n');
            result4 = (*myData).findTotalDeathsByState(newstates4);
            cout << newstates4 << ", " << result4 << " DEATHS" << endl;
            break;
        }

        case 5: {
            //get cases by date range
            char new_line[256];
            int iter = 0;
            char c;
            int result5 = 0;

            cin.get(c);
            while (c != '\n') {
                cin.get(c);
                new_line[iter] = c;
                iter++;
            }
            char newstates[50];
            char startDate[11];
            char endDate[11];

            int newcommand5 = 0;
            //newcommand5 = ParseCommand(new_line, newstates, newcommand5, iter, 50, ' ');
            newcommand5 = ParseCommand(new_line, newstates, newcommand5, 256, 50, '2', 1);
            newcommand5 = ParseCommand(new_line, startDate, newcommand5, 256, 11, ' ', 0);
            newcommand5 = ParseCommand(new_line, endDate, newcommand5 + 1, 256, 11, '\n', 0);

            result5 = (*myData).findTotalCasesBySateWithDateRange(newstates, startDate, endDate);
            cout << newstates << ", " << startDate << " to " << endDate << ", " << result5 << " CASES" << endl;
            break;
        }

        case 6: {
            //get deaths by date range
            char new_line[256];
            int iter = 0;
            char c;
            int result6 = 0;
            cin.get(c);
            do {
                cin.get(c);
                new_line[iter] = c;
                iter++;
            } while (
                !cin.eof() or c != '\n');


            char newstates[50];
            char startDate[11];
            char endDate[11];

            int newcommand6 = 0;
            newcommand6 = ParseCommand(new_line, newstates, newcommand6, 256, 50, '2', 1);
            newcommand6 = ParseCommand(new_line, startDate, newcommand6, 256, 11, ' ', 0);
            newcommand6 = ParseCommand(new_line, endDate, newcommand6 + 1, 256, 11, '\n', 0);

            result6 = (*myData).findTotalDeathsBySateWithDateRange(newstates, startDate, endDate);
            cout << newstates << ", " << startDate << " to " << endDate << ", " << result6 << " DEATHS" << endl;
            break;
        }

        }
    }
    return 0;
    delete myData;

}

