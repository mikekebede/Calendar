#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *months[] = {"January","Feburary","March","April","May","June","July","August","September","October","November","December"};

int dayList[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char *week[] =  {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int isLeapYear(int year){
	if ((year%4==0 && year%100!=0) || year%400==0)
		{return 1;}
	else 
		{return 0;}

}

int dates(int month, int day, int year){ // start dates function
    // this function is going to use the input month day and year to calculate which date of the week it is going to be

	if (isLeapYear(year) == 1) //checking if the year entered is leap year and making february 29 days if true
		{dayList[1]=29;}

	if (year<1753 || month<1 || month >12 || day< 1 || day >dayList[month-1])//checking if the date is valid in the gregorian calendar which started after 1753
		{printf("Not a valid date\n");} 
	//accumulating the number of days inorder to find the exact day on the week
	for(int i = 1753 ; i < year ; i++){ /* start for loop 1*/
		if (isLeapYear(i) == 1)
		day+=366;
		else
		day+=365;
		} /*end for loop 1*/

	for(int i = 0; i < month-1; i++){ // start for
	day+= dayList[i]; //adding the days of months passed in the current year
	}// end for

    return day % 7; //gives the exact day of the week which the day is located
    
    } // end dates function



int printMonth(int month, int year){
// this function given the month and the year is going to print it out in a calendar form
	

	char* mon = months[month-1];
    int length = strlen(mon)+1+4;//allocating the writing spot for the month and year and space between them
	int spaces = (20 - length) / 2;

	
	for (int i = 0; i< spaces; i++){
		printf(" ");
	}

	//printing the month and the year on top line
	printf("%s %4d",mon, year);

	printf("\n");


	printf("Su Mo Tu We Th Fr Sa");
	printf("\n");
	int month_start=dates(month, 1, year); //finding the date for the first day of the month
	int space_counter;
	for(int i=1; i<=month_start; i++){
		printf("   ");
        space_counter+=1;
	}

    for (int i=1; i<=dayList[month-1]; i++){

		printf("%2d", i);
		printf(" ");
		if ((i+month_start) % 7 == 0){
			printf("\n");
		}
	}
	printf("\n");

return 0;
}


int printYear(int year){ 
	// this function is going to use the input year to print the calendar horizontally

	int counter=0;
	for(int i=1; i<=12;i++){
		printMonth(i,year);
		counter++;
	}
	
}
	

//this function is used to find the month when it is formatted as a string
int word_checker_function(char *month_check){
	// this function is used to reformat days that are submitted as strings by using the first 3
	// letters and comparing them to the months array

	char var1[4]; //allocating an array of four for the first three letters of the month
	var1[3]='\0'; //the last spot in the array filled with \0 as a flag to stop copying

	strncpy(var1, month_check,3); //copying  the first 3 letters from out input string
	for(int i=0;i<12;i++){ //setting up a forloop to compare our input to every month of the year
    	char var2[4];
		var2[3]='\0';

		strncpy(var2, months[i],3);

		if(strcasecmp(var1,var2)==0){//comparing the case whether or not they are upper case or lower case

			return i+1;// returning the month as a number form
		}
	}
	return 0; 
}


int main (int argc, char*argv[]){

if(argc==1){// we use the time library to print out the access our system and extract current month and current year

	time_t varr=time(NULL);
	struct tm varr2=*localtime(&varr);
	int year=varr2.tm_year+1900;
	int month=varr2.tm_mon +1;

	printMonth(month,year);}


else if (argc==2){ 
	if (atoi(argv[1])<1753 ){//if the argument is two, the only possiblity is printYear
 		printf("invalid input");}
	else{
		int year=atoi(argv[1]);
		printYear(year);}
	}

 else if(argc==3){ //if there are three arguments, there are a few possibilities:

    if(atoi(argv[2])>=1753 && atoi(argv[1])>0 && atoi(argv[1])<=12){ // possibility 1 format- ./cal 8 2016 
    int month = atoi(argv[1]);
    int year=atoi(argv[2]);
    printMonth(month, year); }
    else if(strcmp(argv[1],"-m")==0 && atoi(argv[2])>0 && atoi(argv[2])<=12 ){//possibility 2 format - ./cal -m 8 
    time_t varr=time(NULL);
    struct tm varr2=*localtime(&varr);
    int year=varr2.tm_year+1900;  // accessing time library and using it to extract current year from system
    int month=atoi(argv[2]);

	printMonth(month,year);

    }
    else if(strcmp(argv[1],"-m")==0 && word_checker_function(argv[2])>0){ //possibility 3- ./cal -m marchy   (or any variations inclusing mar as the first three character(upper or lower))
    time_t varr=time(NULL);
    struct tm varr2=*localtime(&varr);
    int year=varr2.tm_year+1900; // accessing time library and using it to extract current year from system
    int month=word_checker_function(argv[2]); //
    

    printMonth(month,year);
	} 
	else if(word_checker_function(argv[1])>0 && atoi(argv[2])>=1753){ // possibility 4 - ./cal marchy 2014  (or any variations inclusing mar as the first three character(upper or lower)
		int month=word_checker_function(argv[1]);
		int year= atoi(argv[2]);
        printMonth(month, year);

	}
	else{
	printf("Not a valid date\n");
}
 } 
else if (argc == 4){ // if it has four arguments it has only 


if (atoi(argv[3])>=1753 && atoi(argv[2])>0 && atoi(argv[2] )<=12 && strcmp(argv[1],"-m")==0){ // possibility 1- ./cal -m 8 2013
int month = atoi(argv[2]);
int year=atoi(argv[3]);
printMonth(month, year);
}
 else if (atoi(argv[3])>=1753 && word_checker_function(argv[2])>0 && strcmp(argv[1],"-m")==0){// possibility 2 - ./cal -m mar 2013 ( or any forms of mar as month letters)
 int month = word_checker_function(argv[2]);
int year=atoi(argv[3]);
printMonth(month, year);

}
else{
	printf("Not a valid date\n");
}
 }
else {
	printf("invalid input \n");
 }

return 0;
}