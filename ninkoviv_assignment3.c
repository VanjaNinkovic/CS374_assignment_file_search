#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

// function that returns a string of the largest csv file name in the directory
char* find_largest() {
    // variables to store the prefix and suffix we check before deciding to inspect file
    char prefix[] = "movies_";
    char suffix[] = ".csv";

    // open the current directory
    DIR* currDir = opendir(".");
    struct dirent *entry;
    struct stat dirStat;
    // Variables to store the current largest file name and file size
    char *largest_file_name = malloc(256 * sizeof(char));
    long largest_file_size = 0;
    long cur_file_size;

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

        // Any files that make it to this portion of the loop are files that have movies_ 
        // as a prefix and .csv as an extension to our file.
        stat(entry->d_name, &dirStat);
        cur_file_size = dirStat.st_size;
        // if file size hasnt been changed then add current file as the largest
        if(largest_file_size == 0) {
            strcpy(largest_file_name, entry->d_name);
            largest_file_size = cur_file_size;
        }
        // If the current file is larger than the largest file stored then update the newest largest file
        else if (cur_file_size > largest_file_size) { 
            strcpy(largest_file_name, entry->d_name);
            largest_file_size = cur_file_size;
        }
        
    }
    closedir(currDir);
    return largest_file_name;
}
// function that returns a string of the smallest csv file name in the directory
char* find_smallest() {
    // variables to store the prefix and suffix we check before deciding to inspect file
    char prefix[] = "movies_";
    char suffix[] = ".csv";

    // open the current directory
    DIR* currDir = opendir(".");
    struct dirent *entry;
    struct stat dirStat;
    // Variables to store the current smallest file name and file size
    char *smallest_file_name = malloc(256 * sizeof(char));
    long smallest_file_size = 0;
    long cur_file_size;

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

        // Any files that make it to this portion of the loop are files that have movies_ 
        // as a prefix and .csv as an extension to our file.
        stat(entry->d_name, &dirStat);
        cur_file_size = dirStat.st_size;
        // if file size hasnt been changed then add current file as the smallest
        if(smallest_file_size == 0) {
            strcpy(smallest_file_name, entry->d_name);
            smallest_file_size = cur_file_size;
        }
        // If the current file is smaller than the smallest file stored then update the newest smallest file
        else if (cur_file_size < smallest_file_size) { 
            strcpy(smallest_file_name, entry->d_name);
            smallest_file_size = cur_file_size;
        }
        
    }
    closedir(currDir);
    return smallest_file_name;
}

// function that returns 1 or 0 depending on if the file exists within the directory or not
int find_by_name(char* name) {
    // open the current directory
    DIR* currDir = opendir(".");
    struct dirent *entry;
    
    // read through the directory to see if the file name exists
    // If file name is found return 1 otherwise return 0
    while((entry = readdir(currDir)) != NULL){
        if(strcmp(entry->d_name, name) == 0){
            closedir(currDir);
            return 1;
        }
    }
    closedir(currDir);
    return 0;

}
// function that will create a randomly named directory when called
char* create_directory(){
    char *file_name = malloc(50 * sizeof(char));
    strcpy(file_name, "ninkoviv.movies."); // prefix to attach to all directory names)
    char suffix[10]; // space to turn int random number into a string
    int rand_num = random() % 100000; // grab random number to be suffix of file
    sprintf(suffix, "%d", rand_num); // turn number into a string
    strcat(file_name, suffix); // combine prefix and suffix into a filename

    // create diretory with rwxr-x--- permissions
    mkdir(file_name, 0750);
    return file_name;
}



// Main function to run the entire program
int main() {

    int menu_choice; // var to store choice at the first menu 
    int second_choice; // var to store choice at the second menu
    char* file_name; // var to store the file name to be processed
    char* directory_name; // var to store the created directory name
    srandom(726); // Seeded the random calls
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
                    file_name = find_largest();
                    //create a directory that ends in a random numbers 0-99999
                    directory_name = create_directory();
                    printf("The largest file in the directory is: %s\n", file_name);
                    printf("The name of the directory is: %s", directory_name);
                    
                   
                    // free dynamically assigned memory from functions
                    free(file_name);
                    free(directory_name);
                    break;
                }
                // Begin to parse the smallest file in the current directory
                else if(second_choice == 2){
                    file_name = find_smallest();
                    printf("The smallest file in the directory is: %s\n", file_name);
                    free(file_name);
                    break;
                }
                // Ask the user to enter a specific file name to parse
                else if(second_choice == 3){
                    char* custom_name = malloc(256 * sizeof(char)); // var to store user inputted file name
                    printf("Enter the complete file name: ");
                    scanf("%s", custom_name);
                    if(find_by_name(custom_name) == 0){
                        printf("The file %s was not found. Try again.\n", custom_name);
                        free(custom_name);
                        continue;
                    }
                    printf("File name '%s' found and will be processed.\n", custom_name);
                    free(custom_name);
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