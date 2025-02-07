#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>


// Struct for the movie linked list. 
// Taken from assignment 2
struct movie {
    char* title;
    int year;
    char* language;
    float rating;
    struct movie *next;
};

// create Movie function to build structs based on exploration: Memory Allocation in Canvas
// Taken from assignment 2
struct movie* createMovie(char* title, int year, char* language, float rating) {
    struct movie* curMovie = malloc(sizeof(struct movie));

    curMovie->title = strdup(title);
    curMovie->year = year; 
    curMovie->language = strdup(language);
    curMovie->rating = rating;
    curMovie->next = NULL;

    return curMovie;
}


/*
 * Function: processMovieFile
 *   Opens a file, reads and prints each line
 *   filePath: path to the file
 * 
 *  This function shows sample code that opens a file, then in a loop reads and prints each line in that file.
 *  You can use this code however you want in your Prog Assignment 2.
 *  
 *  TAKEN FROM ASSIGNMENT 2
 */
struct movie* processMovieFile(char* filePath){
    char *currLine = NULL;
    size_t len = 0;
    // begining of the Linked List implementation
    struct movie* head = NULL;
    struct movie* tail = NULL;
    struct movie* newMovie;
    int size = 0;

    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");
    
    // Reads the first line and does nothing to skip all the header collumns
    getline(&currLine, &len, movieFile);

    // Read the file line by line
    while(getline(&currLine, &len, movieFile) != -1)
    {
        char* tokTitle;
        char* tokYear;
        int year;
        char* tokLanguage;
        char* tokRating;
        float rating;
        char* token;
        char* savePtr;

        // Tokenization of the line to turn string into variables used to create movie struct
        token = strtok_r(currLine, ",", &savePtr);
        tokTitle = strdup(token);
        token = strtok_r(NULL, ",", &savePtr);
        tokYear = strdup(token);
        token = strtok_r(NULL, ",", &savePtr);
        tokLanguage = strdup(token);
        token = strtok_r(NULL, ",", &savePtr);
        tokRating = strdup(token);

        // converting string versions of year and rating to int and float respectively 
        year = atoi(tokYear);
        rating = strtod(tokRating,NULL);

        // creating the linked list
        newMovie = createMovie(tokTitle, year, tokLanguage, rating);

        if(head == NULL) {
            // if there is no head set the first movie as the head and tail to initiate the begining of the list
            head = newMovie;
            tail = newMovie;
        } else {
            // if the new struct is not the first one then you add it to the end of the list
            tail->next = newMovie;
            tail = newMovie;
        }
        // printf("The current tail's title is: %s\n", tail->title);
        free(tokTitle);
        free(tokYear);
        free(tokLanguage);
        free(tokRating);

        size++;       
    }

    // Free the memory allocated by getline for currLine
    free(currLine);
    // Close the file
    fclose(movieFile);

    return head;
}







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


void parse_data(struct movie* data){
    struct movie* curMovie;
    curMovie = data;
    // Iterate through linked list and print movie if it matches the year parameter
    while(curMovie != NULL) {
        //do something
    }
}












// Main function to run the entire program
int main() {

    int menu_choice; // var to store choice at the first menu 
    int second_choice; // var to store choice at the second menu
    char* file_name; // var to store the file name to be processed
    char* directory_name; // var to store the created directory name
    struct movie *data; // pointer to a linked list of movie data
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
                    //locate largest file
                    file_name = find_largest();
                    //create a directory that ends in a random numbers 0-99999
                    directory_name = create_directory();
                    //create linked list of movies and their data
                    data = processMovieFile(file_name);

                    printf("Now processing the chosen file named %s\n", file_name);
                    printf("Created directory with the name %s\n\n", directory_name);

                   
                    // free dynamically assigned memory from functions
                    free(file_name);
                    free(directory_name);
                    free(data);
                    break;
                }
                // Begin to parse the smallest file in the current directory
                else if(second_choice == 2){
                    file_name = find_smallest();
                    //create a directory that ends in a random numbers 0-99999
                    directory_name = create_directory();
                    printf("Now processing the chosen file named %s\n", file_name);
                    printf("Created directory with the name %s\n\n", directory_name);
                    
                   
                    // free dynamically assigned memory from functions
                    free(file_name);
                    free(directory_name);
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
                    //create a directory that ends in a random numbers 0-99999
                    directory_name = create_directory();
                    printf("Now processing the chosen file named %s\n", file_name);
                    printf("Created directory with the name %s\n\n", directory_name);
                    
                   
                    // free dynamically assigned memory from functions
                    free(file_name);
                    free(directory_name);
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