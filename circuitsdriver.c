//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3=========4=========5=========6=========7**
//Author information
//  Author name: Justin Stewart
//  Author email: scubastew@csu.fullerton.edu
//  Author location: Long Beach, Calif.
//Course information
//  Course number: CPSC240
//  Assignment number: 2
//  Due date: 2015-Sep-10
//Project information
//  Project title: Four-Device Current Calculator
//  Purpose: The purpose of this project is to demonstrate vector operations by using given watts and voltage and calculating the resulting current.
//  Status: Executed wih no errors.
//  Project files: circuitsdriver.c, circuitsmain.asm
//Module information
//  File name: circuitsdriver.c
//  This module's call name: circuits.out  This module is invoked by the user.
//  Language: C
//  Date last modified: 2015-Sep-09
//  Purpose: This module is the top level driver: it will call circuits
//  Status: Executed with no errors.
//  Future enhancements: None planned
//Translator information (Tested in Linux shell)
//  Gnu compiler: gcc -c -m64 -Wall -std=c99 -l circuitsdriver.lis -o circuitsdriver.o circuitsdriver.c
//  Gnu linker:   gcc -m64 -o circuits.out circuitsdriver.o circuitsmain.o
//  Execute:      ./circuits.out
//References and credits
//  No references: this module is standard C language
//Format information
//  Page width: 172 columns
//  Begin comments: 61
//  Optimal print specification: Landscape, 7 points, monospace, 8½x11 paper
//
//===== Begin code area ===================================================================================================================================================

#include <stdio.h>
#include <stdint.h>

extern double circuits();

int main()
{
 double return_code=-99.9;	//Init double return value
 printf("%s","Welcome to Electric Circuit Processing by Justin Stewart.\n");
 return_code = circuits();
 printf("%s %1.18lf\n","The driver received this number: ", return_code);
 printf("%s","The driver program will now return 0 to the operating system.  Have a nice day.\n");
 return 0;
}//End of main

//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3=========4=========5=========6=========7**
