#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

// function that returns a string of the largest csv file name in the directory
int find_largest() {
    // variables to store the prefix and suffix we check before deciding to inspect file
    char prefix[] = "movies_";
    char suffix[] = ".csv";

    // open the current directory
    DIR* currDir = opendir(".");
    struct dirent *entry;
    struct stat dirStat;
    // Variables to store the current largest file name and file size
    char *largest_file_name = calloc(256, sizeof(char));
    int large_file_size;

    while((entry = readdir(currDir)) != NULL){
        // checking if prefix is "movies_"
        if(strncmp(entry->d_name, prefix, strlen(prefix)) != 0){
            continue;
        }
        // check if the extension of the file is a .csv
        char *extension = strchr(entry->d_name, '.');
        if(strcmp(extension, suffix) != 0){
            continue;
        }
        printf("%s\n", entry->d_name);
        if(largest_file_name == ""){
            printf("File name is empty!\n");
        }
        
    }
    closedir(currDir);
    return 0;

}
// function that returns a string of the smallest csv file name in the directory
char* find_smallest() {

}
// function that returns 1 or 0 depending on if the file exists within the directory or not
int find_by_name() {

}



// Main function to run the entire program
int main() {

    int menu_choice; // var to store choice at the first menu 
    int second_choice; // var to store choice at the second menu
    char* file_name; // var to store the file name to be processed
    while(1) {
        
        printf("1. Select file to process\n");
        printf("2. Exit the program\n\n");
        printf("Enter a choice 1 or 2: ");
        scanf("%d", &menu_choice);

        // Conditional to begin the entire file parsing process
        if(menu_choice == 1){
            
            // loop to keep asking the user to enter an option in case they enter a file that
            // does not actually exist. Each function upon success will break this loop.
            while(1){
                printf("\nWhich file you want to process?\n");
                printf("Enter 1 to pick the largest file\n");
                printf("Enter 2 to pick the smallest file\n");
                printf("Enter 3 to specify the name of a file\n\n");
                printf("Enter a choice from 1 to 3: ");
                scanf("%d", &second_choice);

                // Begin to parse the largest file in the current directory
                if(second_choice == 1) {
                    find_largest();
                    printf("You picked the largest file!\n");
                    break;
                }
                // Begin to parse the smallest file in the current directory
                else if(second_choice == 2){
                    file_name = find_smallest();
                    printf("You picked the smallest file!\n");
                    break;
                }
                // Ask the user to enter a specific file name to parse
                else if(second_choice == 3){
                    printf("You chose to enter a specific file!\n");
                    break;
                }
                // Prompt the user to choose again as their input was incorrect
                else {
                    printf("You entered an incorrect choice. Try again.\n");
                }
            }
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