#include <stdio.h>
#include <stdlib.h>
#include <string.h>






// Main function to run the entire program
int main() {

    int menu_choice;
    while(1) {
        
        printf("1. Select file to process\n");
        printf("2. Exit the program\n\n");
        printf("Enter a choice 1 or 2: ");
        scanf("%d", &menu_choice);

        // Conditional to begin the entire file parsing process
        if(menu_choice == 1){
            printf("You selected to process a file!\n");
            break;
        }
        // breaks the while loop and ends the software
        else if(menu_choice == 2){
            break;
        }
        // Error handling if user enters incorrect integer
        else{
            printf("You entered an incorrect choice. Try again.\n");
            continue;
        }
    } 
}