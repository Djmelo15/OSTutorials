#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"




#define BUFFER_LEN 256
#define NUM_PLAYERS 4




void tokenize(char *input, char **tokens)
{
    char *delim = " ";
    tokens[0] = strtok(input, delim);
    tokens[1] = strtok(NULL, delim);
}




void show_results(player *players, int num_players)
{
    printf("
Final Results:
");
    for (int i = 0; i < num_players; i++) {
        printf("%s: $%d
", players[i].name, players[i].score);
    }
}




int main(int argc, char *argv[])
{
    player players[NUM_PLAYERS];
    char input[BUFFER_LEN];
    char category[50], answer[50];
    int value;




    initialize_game();




    printf("Welcome to Jeopardy! Enter player names:
");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("Player %d: ", i + 1);
        scanf("%s", players[i].name);
        players[i].score = 0;
    }




    while (1) {
        display_categories();




        printf("Select player: ");
        scanf("%s", input);
        if (!player_exists(players, NUM_PLAYERS, input)) {
            printf("Invalid player name. Try again.
");
            continue;
        }




        printf("Enter category and value: ");
        scanf("%s %d", category, &value);




        if (already_answered(category, value)) {
            printf("This question has already been answered. Pick another one.
");
            continue;
        }




        display_question(category, value);
        printf("Your answer: ");
        scanf(" %[^
]s", answer);




        char *tokens[2];
        tokenize(answer, tokens);




        if (valid_answer(category, value, tokens[1])) {
            printf("Correct!
");
            update_score(players, NUM_PLAYERS, input, value);
        } else {
            printf("Incorrect! The correct answer was: %s
", answer);
        }
    }




    show_results(players, NUM_PLAYERS);
    return 0;
}
