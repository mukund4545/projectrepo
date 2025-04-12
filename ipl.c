#include <stdio.h>
#include <string.h>

struct teams{
    char name[50];
    int wins;
    int lose;
    char captain[50];
}teams[10];

struct player{
    char playername[50];
    int runs;
    int wickets;
    char team[50];

}players[11];
int teamcount = 0;int playercount =0;
void saveTeamsToFile() {
    FILE *file = fopen("teams.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    for (int i = 0; i < teamcount; i++) {
        fprintf(file, "%s %s %d %d\n", teams[i].name, teams[i].captain, teams[i].wins, teams[i].lose);
    }
    fclose(file);
}
void loadTeamsFromFile() {
    FILE *file = fopen("teams.txt", "r");
    if (file == NULL) {
        printf("No previous team data found. Starting fresh.\n");
        return;
    }
    while (fscanf(file, " %49s %49s %d %d", teams[teamcount].name, teams[teamcount].captain, &teams[teamcount].wins, &teams[teamcount].lose) == 4) {
        teamcount++;
    }
    fclose(file);
}


void savePlayersToFile() {
    FILE *file = fopen("players.txt", "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    for (int i = 0; i < playercount; i++) {
        fprintf(file, "%s %s %d %d\n", players[i].playername, players[i].team, players[i].runs, players[i].wickets);
    }
    fclose(file);
}


void loadPlayersFromFile() {
    FILE *file = fopen("players.txt", "r");
    if (file == NULL) {
        printf("No previous player data found. Starting fresh.\n");
        return;
    }
    while (fscanf(file, " %49s %49s %d %d", players[playercount].playername, players[playercount].team, &players[playercount].runs, &players[playercount].wickets) == 4) {
        playercount++;
    }
    fclose(file);
}
void addteam(){

    if (teamcount > 10){
        printf("max limit for teams is reached");
    
    }
    printf("Enter the team name :");
    scanf(" %[^\n]", teams[teamcount].name);
    printf("Enter captain name: ");
    scanf(" %[^\n]", teams[teamcount].captain);
    teams[teamcount].wins = 0;
    teams[teamcount].lose = 0;

    teamcount++;
    printf("Team added successfully!\n");
    saveTeamsToFile();
    }

void addplayer(){
    if (playercount > 11){
        printf("max limit for players in team is reached");
    
    }
    printf("Enter the team name :");
    scanf(" %[^\n]", players[playercount].team);
    printf("Enter player name: ");
    scanf(" %[^\n]", players[playercount].playername);
    players[playercount].runs = 0;
    players[playercount].wickets = 0;

    playercount++;
    printf("player added successfully!\n");
    savePlayersToFile();

}
void updatematch(){
    char teamname[50];int result;
    printf("Enter the team name :");
    scanf(" %[^\n]",teamname);
    printf("Enter the match result (1 for win and 0 for loss) :");
    scanf("%d",&result);

    for(int i=0;i<10;i++){
        if(strcmp(teamname,teams[i].name)==0){
            if(result==1){
                teams[i].wins++;
            }
            else{
                teams[i].lose++; }
            printf("team score added successfully ! \n");
            saveTeamsToFile();
            return;
        }

    }
    printf("team not found ! \n");
}

void updateplayer(){
    char playername[50];int runs;int wickets;
    printf("Enter the player name :");
    scanf(" %[^\n]",playername);
    printf("Enter the runs :");
    scanf("%d",&runs);
    printf("Enter the wickets :");
    scanf("%d",&wickets);


    for(int i=0;i<11;i++){
        if(strcmp(playername,players[i].playername)==0){
            players[i].runs= runs;
            players[i].wickets= wickets;
            printf("player score added successfully ! \n");
            savePlayersToFile();
            return;
        }
            
        }

    
    printf("player not found ! \n");

}

void predictor() {
    char team1[50];
    char team2[50];
    int team1ind = -1, team2ind = -1;
    printf("Enter the name of Team 1: ");
    scanf(" %[^\n]", team1);
    printf("Enter the name of Team 2: ");
    scanf(" %[^\n]", team2);

    for (int i = 0; i < teamcount; i++) {
        if (strcmp(team1, teams[i].name) == 0) {
            team1ind = i;
        }
        if (strcmp(team2, teams[i].name) == 0) {
            team2ind = i;
        }
    }

    
    if (team1ind == -1 || team2ind == -1) {
        printf("One or both teams not found!\n");
        return;
    }

    
    if ((teams[team1ind].wins + teams[team1ind].lose) == 0 || 
        (teams[team2ind].wins + teams[team2ind].lose) == 0) {
        printf("One or both teams have no match history. Prediction cannot be made.\n");
        return;
    }

    
    float win1 = (float)(teams[team1ind].wins) * 100 / (teams[team1ind].wins + teams[team1ind].lose);
    float win2 = (float)(teams[team2ind].wins) * 100 / (teams[team2ind].wins + teams[team2ind].lose);

    
    if (win1 > win2) {
        printf("%s has a higher chance of winning (Win Percentage: %.2f%%).\n", teams[team1ind].name, win1);
    } else if (win2 > win1) {
        printf("%s has a higher chance of winning (Win Percentage: %.2f%%).\n", teams[team2ind].name, win2);
    } else {
        printf("Both teams have equal chances of winning (Win Percentage: %.2f%%).\n", win1);
    }
}
    void viewteams(){
        printf("\n--- Teams ---\n");
        for(int i =0;i<10;i++){
            printf("Team: %s, Captain: %s, Wins: %d, Losses: %d\n",
                teams[i].name, teams[i].captain,teams[i].wins, teams[i].lose);
            
        }
    }
    void viewplayers(){
        printf("\n--- players ---\n");
        for(int i =0;i<11;i++){
            printf("player: %s, team: %s, runs: %d, wickets: %d\n",
                players[i].playername, players[i].team,players[i].runs, players[i].wickets);
            
        }

    }

    int main(){
        int choice;
        loadTeamsFromFile();
    loadPlayersFromFile();
        do{
            printf("\n=========================================\n");
            printf("       IPL Management System Menu        \n");
            printf("=========================================\n");
            printf("1. Add Team\n");
            printf("2. Add Player\n");
            printf("3. Update Match Result\n");
            printf("4. Update Player Stats\n");
            printf("5. Predict Match Winner\n");
            printf("6. View Teams\n");
            printf("7. View Players\n");
            printf("8. Exit\n");
            printf("=========================================\n");
            printf("Enter the choice:");
            scanf("%d",&choice);
        switch(choice){
        case 1 : addteam();break;
        case 2 : addplayer();break;
        case 3 : updatematch();break;
        case 4 : updateplayer();break;
        case 5 : predictor();break;
        case 6 : viewteams();break;
        case 7 : viewplayers();break;
        case 8 :printf("Exiting ....\n ------- THANK YOU ------- \n");break;
        default : printf("plese eneter valid input \n");
    }
}while(choice != 8);
return 0;
    }