#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

struct isiDataPemain{
    char name[101], email[201], username[101], password[101];
    double score;
};

// search player
int linearSearch(struct isiDataPemain player[], char email[], int totalPlayer){
    for (int i = 0; i < totalPlayer; i++){
        if (strcmp(player[i].email, email) == 0){
            return i;
        }
    }
    return -1;
}

// read players data
int loadData(struct isiDataPemain player[]){
    FILE *readPlayersData = fopen("playerRecord.txt", "r+");
    int index = 0;
    while (!feof(readPlayersData)){
        fscanf(readPlayersData, "%[^\n]\n", player[index].name);
        fscanf(readPlayersData, "%[^\n]\n", player[index].email);
        fscanf(readPlayersData, "%[^\n]\n", player[index].username);
        fscanf(readPlayersData, "%[^\n]\n", player[index].password);
        index++;
    }
    fclose(readPlayersData);

    return index; // return total players
}

// welcome page
int welcomeMenu(){
    printf("Type Racer\n");
    printf("==========================\n");
    printf("1. Login\n");
    printf("2. Create Account\n");
    printf("3. Quit\n");
    int choice = 0;
    printf("Please input your choice [1 .. 3] >> ");
    do {
        scanf("%d", &choice); getchar();
        if (choice < 1 || choice > 3){
            printf("There is no option number %d.. Please input the correct options [1 .. 3] >> ", choice);
        }
    } while (choice < 1 || choice > 3);

    return choice;
}

int loginPage(struct isiDataPemain player[], int totalPlayer){
    printf("Log in to your account [enter -1 to exit to Welcome Menu]:\n");

    // input email and account validation
    char email[201] = {0};
    printf("Email address (Ex: ..@gmail.com): ");
    char *emailValidation;
    do{
        scanf("%s", email); getchar();
        emailValidation = strstr(email, "@gmail.com");
        if (strcmp(email, "-1") == 0) return -1;
        if (emailValidation == NULL){
            printf("Invalid email\n");
            printf("Please include '@gmail.com' in your email address: ");
        }
    } while (emailValidation == NULL);

    // search data based on email
    int index = linearSearch(player, email, totalPlayer);

    // no account exist
    while (index == -1){
        system("cls");
        int choice = 0;
        printf("E-mail not found.\n");
        printf("Have No Account or Try again?");
        printf("\n1. Back to Welcome Menu\n2. Try again\nPlease input your choice [1 .. 2] >> ");
        do {
            scanf("%d", &choice); getchar();
            system("cls");
            if (choice == 1) return -1;
            if (choice == 2){
                printf("Log in to your account [enter -1 to exit to Welcome Menu]:\n");
                printf("Email address (Ex: ..@gmail.com): ");
                do {
                    scanf("%s", email); getchar();
                    emailValidation = strstr(email, "@gmail.com");
                    if (strcmp(email, "-1") == 0) return -1;
                    if (emailValidation == NULL){
                        printf("Invalid email\n");
                        printf("Please include '@gmail.com' in your email address: ");
                    }
                } while (emailValidation == NULL);
            }
            if (choice < 1 || choice > 2){
                printf("There is no option number %d.. Please input the correct option [1 .. 2] >> ", choice);
            }
        } while (choice < 1 || choice > 2);
        index = linearSearch(player, email, totalPlayer);
    }

    // verify password
    char password[101] = {0};
    printf("Password: ");
    do {
        scanf("%s", password); getchar();
        if (strcmp(password, "-1") == 0) return -1;
        if (strcmp(password, player[index].password) != 0){
            printf("Incorrect password\n");
            printf("Please try again: ");
        }
    } while (strcmp(password, player[index].password) != 0);

    system("cls");
    printf("Successfully log in!\n");
    printf("Press enter to continue to main menu.."); getchar();
    return index;
}

int mainMenu(){
    printf("Type Racer Main Menu\n");
    printf("==========================\n");
    printf("1. Play Game\n");
    printf("2. View Scoreboard\n");
    printf("3. How to Play\n");
    printf("4. Quit\n");
    int choice = 0;
    printf("Please input your choice [1 .. 4] >> ");
    do {
        scanf("%d", &choice); getchar();
        if (choice < 1 || choice > 4){
            printf("There is no option number %d.. Please input the correct options [1 .. 4] >> ", choice);
        }
    } while (choice < 1 || choice > 4);

    return choice;
}

// validate same email
int sameEmailValidation(char newEmail[], struct isiDataPemain player[], int totalPlayer){
    for (int i = 0; i < totalPlayer; i++){
        if (strcmp(newEmail, player[i].email) == 0){
            return 0;
        }
    }
    return 1;
}

// validate same username
int sameUsernameValidation(char newUsername[], struct isiDataPemain player[], int totalPlayer){
    for (int i = 0; i < totalPlayer; i++){
        if (strcmp(newUsername, player[i].username) == 0){
            return 0;
        }
    }
    return 1;
}

// create account
void createAccount(FILE *newAccount, struct isiDataPemain player[], int totalPlayer){
    puts("Please input your data [enter -1 to exit to welcome menu]:");

    // input first name
    char firstName[101] = {0};
    printf("First Name: ");
    scanf("%s", firstName); getchar();
    if (strcmp(firstName, "-1") == 0) return;

    // input email
    char email[201] = {0};
    char *emailValidation;
    printf("E-mail Address (Ex: ..@gmail.com): ");
    do {
        scanf("%s", email); getchar();
        if (strcmp(email, "-1") == 0) return;
        if (!sameEmailValidation(email, player, totalPlayer)){
            printf("%s email is already used..\n", email);
            printf("Please input another email (Ex: ..@gmail.com): ");
        }
        emailValidation = strstr(email, "@gmail.com");
        if (emailValidation == NULL){
            printf("Invalid Input\n");
            printf("Please include '@gmail.com' in the email address: ");
        }
    } while (emailValidation == NULL || !sameEmailValidation(email, player, totalPlayer));

    // input username
    char username[101] = {0};
    printf("Username: ");
    do{
        scanf("%s", username); getchar();
        if (strcmp(username, "-1") == 0) return;
        if (!sameUsernameValidation(username, player, totalPlayer)){
            printf("%s username is already used..\n", username);
            printf("Please input another username: ");
        }
    } while (!sameUsernameValidation(username, player, totalPlayer));

    // input password and confirm password
    char password[101] = {0}, confirmPassword[101] = {0};
    do {
        printf("Password: ");
        scanf("%s", password); getchar();
        if (strcmp(password, "-1") == 0) return;
        printf("Confirm Password: ");
        scanf("%s", confirmPassword); getchar();

        if (strcmp(password, confirmPassword) != 0){
            printf("The password confirmation does not match! Please repeat!\n");
        }
    } while (strcmp(password, confirmPassword) != 0);

    // successful
    system("cls");
    printf("Successfully created an account!\n");
    printf("Press enter to continue and proceed login.."); getchar();
    fprintf(newAccount, "%s\n", firstName);
    fprintf(newAccount, "%s\n", email);
    fprintf(newAccount, "%s\n", username);
    fprintf(newAccount, "%s\n", password);
    return;
}

// how to play
void howToPlay(){
    system("cls");
    puts("RULES");
	puts("================================================================================================");
	puts("");
	puts("1. Players are given 30 words to type according to the level he/she chooses");
	puts("2. If the player mistypes a word, the player will retype the word until it is correct");
	puts("3. The scoreboard will be determined based on the player's fastest typing time");
	puts("4. The time will be counted when the game starts and stops when all the words have been typed");
	puts("");
	printf("Press enter to return to Main Menu.."); getchar();
}

// choose level
int level(){
    system("cls");
    puts("Choose Difficulty Level");
	puts("==========================");
	puts("1. Easy ");
	puts("2. Medium");
	puts("3. Hard");
    puts("4. Back to main menu");
    int choice = 0;
    printf("Please input your choice [1 .. 4] >> ");
    do{
        scanf("%d", &choice); getchar();
        if (choice == 4) return -1;
        else if (choice < 1 || choice > 4){
            printf("There is no option number %d.. Please input the correct option [1 .. 4] >> ", choice);
        }
    } while (choice < 1 || choice > 4);

    return choice;
}

int readScore(FILE *score, struct isiDataPemain ranking[]){
    int transcount = 0;
    while (!feof(score)){
        fscanf(score, "%[^\n]\n", ranking[transcount].username);
        fscanf(score, "%lf\n", &ranking[transcount].score);
        transcount++;
    }

    for (int i = 0; i < transcount - 1; i++){
        for (int j = 0; j < transcount - i - 1; j++){
            if(ranking[j].score > ranking[j+1].score){
				struct isiDataPemain temp = ranking[j];
				ranking[j] = ranking[j+1];
				ranking[j+1] = temp;
			}
        }
    }

    return transcount;
}

// ranking table
void table (struct isiDataPemain ranking[], int transcount, char level[]){
    system("cls");
    printf("Difficulty level: %s\n", level);
    puts("================================================");
	printf("|  %-10s  |  %-12s   |  %-10s  |\n", "Rank", "Username", "Time");
	for(int i=0;i<transcount;i++){
		puts("================================================");
		printf("|  %-10d  |  %-12s   |  %-10.3lf  |\n", i + 1, ranking[i].username, ranking[i].score);
	}
	puts("================================================");

	printf("Press enter to return to Scoreboard Menu.."); getchar();
}

// score board
void scoreboard(){
    system("cls");
    int choice = level();
    if (choice == -1) return;

    struct isiDataPemain ranking[100];
    int transcount = 0;
    system("cls");
    if (choice == 1){
        char level[15] = "Easy";
        FILE *easyScoreboard = fopen("EasyScore.txt", "r");
        transcount = readScore(easyScoreboard, ranking);
        fclose(easyScoreboard);

        if (ranking[0].score == 0){
            printf("There is no Highscore yet...\nPress enter to return to Scoreboard Menu..."); getchar();
            scoreboard();
        } else{
            table(ranking, transcount, level);
            scoreboard();
        }
    } else if (choice == 2){
        char level[15] = "Medium";
        FILE *medScoreboard = fopen("MediumScore.txt", "r");
        transcount = readScore(medScoreboard, ranking);
        fclose(medScoreboard);

        if (ranking[0].score == 0){
            printf("There is no Highscore yet...\nPress enter to return to Scoreboard Menu..."); getchar();
            scoreboard();
        } else{
            table(ranking, transcount, level);
            scoreboard();
        }
    } else if (choice == 3){
        char level[15] = "Hard";
        FILE *hardScoreboard = fopen("HardScore.txt", "r");
        transcount = readScore(hardScoreboard, ranking);
        fclose(hardScoreboard);

        if (ranking[0].score == 0){
            printf("There is no Highscore yet...\nPress enter to return to Scoreboard Menu..."); getchar();
            scoreboard();
        } else{
            table(ranking, transcount, level);
            scoreboard();
        }
    }
}

// choose words set
int chooseSet(char level[]){
    int choice = 0;
    printf("Difficulty level: %s\n\n", level);
    printf("Please input your desired set [1 .. 10][enter -1 to return to Play Game Menu] >> ");
    do {
        scanf("%d", &choice); getchar();
        if (choice == -1) break;
        if (choice < 1 || choice > 10){
            printf("There is no option number %d.. Please input the correct option [1 .. 10][enter -1 to return to Play Game Menu] >> ", choice);
        }
    } while (choice < 1 || choice > 10);

    return choice;
}

// read words from file
void readWords(FILE *words, char typeWords[][101], int set){
    while (!feof(words)){
        int temp = 0, count = 0;
        fscanf(words, "%d\n", &temp);
        while (count < 49){
            fscanf(words, "%[^,],", typeWords[count]);
            count++;
        }
        fscanf(words, "%[^\n]\n", typeWords[count]);
        count++;

        if (temp == set) return;
    }
}

// play the game
void play(char words[][101]){
    system("cls");
    srand(time(NULL));
    for (int i = 0; i < 30; i++){
        char temp[101] = {0};
        int index = rand() % 50;;
        do{
            printf("%s\n", words[index]);
            printf(">> ");
            scanf("%[^\n]", temp); getchar();

            if (strcmp(words[index], temp) == 0){
                printf("correct! :D\n");
            }
            else{
                printf("incorrect :(\n");
                printf("Please enter the correct answer!\n");
            }

            system("cls");
        } while (strcmp(words[index], temp) != 0);
    }
}

// start
double start(char words[][101], struct isiDataPemain player[], int number){
    system("cls");
    printf("Are you ready?\n");
    printf("Press enter to start the game.."); getchar();
    clock_t time;
    time = clock();
    play(words);
    time = clock() - time;
    double time_taken = (double)time/CLOCKS_PER_SEC;
    printf("You took %.3lf seconds to complete\n", time_taken);
    printf("Press enter to continue to Play Game Menu.."); getchar();
    return time_taken;
}

// play game menu
void playGame(struct isiDataPemain player[], int number){
    system("cls");
    int choice = level();
    if (choice == -1) return;

    system("cls");
    char typeWords[51][101] = {0};
    int wordsSet = 0, transcount = 0;
    struct isiDataPemain ranking[100];
    if (choice == 1){
        char level[15] = "Easy";
        wordsSet = chooseSet(level);
        if (wordsSet != -1){
            // read words
            FILE *words = fopen("easyLevel.txt", "r");
            readWords(words, typeWords, wordsSet);
            fclose(words);

            player[number].score = start(typeWords, player, number);
            FILE *score = fopen("EasyScore.txt", "r+");
            transcount = readScore(score, ranking);
            if (transcount >= 50){
                if (ranking[49].score > player[number].score){
                    ranking[49] = player[number];
                }
                fclose(score);

                FILE *easy = fopen("EasyScore.txt", "w");
                for (int i = 0; i < 50; i++){
                    fprintf(score, "%s\n", ranking[i].username);
                    fprintf(score, "%.3lf\n", ranking[i].score);
                }
                fclose(easy);
            }
            if (transcount < 50){
                FILE *add = fopen("EasyScore.txt", "a+");
                fprintf(add, "%s\n%.3lf\n", player[number].username, player[number].score);
                fclose(add);
            }
        }
    } else if (choice == 2){
        char level[15] = "Medium";
        wordsSet = chooseSet(level);
        if (wordsSet != -1) {
            // read words
            FILE *words = fopen("mediumLevel.txt", "r");
            readWords(words, typeWords, wordsSet);
            fclose(words);

            player[number].score = start(typeWords, player, number);
            FILE *score = fopen("MediumScore.txt", "r+");
            transcount = readScore(score, ranking);
            if (transcount >= 50){
                if (ranking[49].score > player[number].score){
                    ranking[49] = player[number];
                }
                fclose(score);

                FILE *medium = fopen("MediumScore.txt", "w");
                for (int i = 0; i < 50; i++){
                    fprintf(score, "%s\n", ranking[i].username);
                    fprintf(score, "%.3lf\n", ranking[i].score);
                }
                fclose(medium);
            }
            if (transcount < 50){
                FILE *add = fopen("MediumScore.txt", "a+");
                fprintf(add, "%s\n%.3lf\n", player[number].username, player[number].score);
                fclose(add);
            }
        }
    } else if (choice == 3){
        char level[15] = "Hard";
        wordsSet = chooseSet(level);
        if (wordsSet != -1){
            // read words
            FILE *words = fopen("hardLevel.txt", "r");
            readWords(words, typeWords, wordsSet);
            fclose(words);

            player[number].score = start(typeWords, player, number);
            FILE *score = fopen("HardScore.txt", "r+");
            transcount = readScore(score, ranking);
            if (transcount >= 50){
                if (ranking[49].score > player[number].score){
                    ranking[49] = player[number];
                }
                fclose(score);

                FILE *hard = fopen("HardScore.txt", "w");
                for (int i = 0; i < 50; i++){
                    fprintf(score, "%s\n", ranking[i].username);
                    fprintf(score, "%.3lf\n", ranking[i].score);
                }
                fclose(hard);
            }
            if (transcount < 50){
                FILE *add = fopen("HardScore.txt", "a+");
                fprintf(add, "%s\n%.3lf\n", player[number].username, player[number].score);
                fclose(add);
            }
        }
    }

    playGame(player, number);
}

int main(){
    struct isiDataPemain player[50];
    int totalPlayer = loadData(player);

    do {
        system("cls");
        int welcomeOption = 0, mainOption = 0;
        char quitWelcome[15] = {0}, quitMain[15] = {0};

        welcomeOption = welcomeMenu();
        system("cls");
        // quit game
        if (welcomeOption == 3){
            printf("Are you sure you want to quit the game? [Yes/No] >> ");
            do {
                scanf("%s", quitWelcome); getchar();
                if (strcmp(quitWelcome, "Yes") != 0 && strcmp(quitWelcome, "No") != 0){
                    printf("Please input the correct options [Yes/No] >> ");
                } else if (strcmp(quitWelcome, "Yes") == 0) return 0;
            } while (strcmp(quitWelcome, "Yes") != 0 && strcmp(quitWelcome, "No") != 0);
        } else if (welcomeOption == 1){ // game login
            int number = loginPage(player, totalPlayer); // urutan player di file record
            if (number != -1){
                do {
                    system("cls");
                    mainOption = mainMenu();
                    // quit main menu
                    if (mainOption == 4){
                        system("cls");
                        printf("Are you sure you want to log out? [Yes/No] >> ");
                        do {
                            scanf("%s", quitMain); getchar();
                            if (strcmp(quitMain, "Yes") != 0 && strcmp(quitMain, "No") != 0){
                                printf("Please input the correct options [Yes/No] >> ");
                            } else if (strcmp(quitMain, "Yes") == 0) break;
                        } while (strcmp(quitMain, "Yes") != 0 && strcmp(quitMain, "No") != 0);
                    } else if (mainOption == 3){
                        howToPlay();
                    } else if (mainOption == 2){
                        scoreboard();
                    } else if (mainOption == 1){
                        playGame(player, number);
                    }
                } while (strcmp(quitMain, "Yes") != 0);
            }
        } else if (welcomeOption == 2){ // create account
            system("cls");
            FILE *newAccount = fopen("playerRecord.txt", "a+");
            createAccount(newAccount, player, totalPlayer); // Create Account
            fclose(newAccount);

            totalPlayer = loadData(player);
        }
    } while (1);

    return 0;
}
