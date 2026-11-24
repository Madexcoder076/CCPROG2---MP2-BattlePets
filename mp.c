/**
 * Description      : BattlePets - a text-based game that simulates a match between
 *                    a roster of BattlePets between two players.
 * Author/s         : Delos Santos, Diego; <Insert Name>
 * Section          : S20C
 * Last Modified    :
 * Acknowledgments  : 

#include <stdio.h>
#include <string.h>

#define RED "\x1b[31m" // Text Color changer
#define RESET "\x1b[0m"
#define MAX_NAME 36
#define MAX_DESC 240
#define MAX_PETS 60
#define MAX_PLAYERS 50
#define ROSTER_SIZE 3
#define NUM_ELEMENTS 8
#define MAX_ELEMENT 10

/**
 * Represents a single BattlePet in the ComPetDium
 */
struct BattlePet
{
    char name[MAX_NAME + 1];   // Name of the BattlePet (up to 36 chars, no spaces)
    char element[MAX_ELEMENT];          // Elemental affinity (e.g., "Fire", "Water")
    char desc[MAX_DESC + 1];   // Short description (up to 240 chars)
    int matchCount;            // Number of matches the BattlePet has appeared in
};

/**
 * Represents a player of the game
 */
struct Player
{
    char name[MAX_NAME + 1];   // Username (up to 36 chars, no spaces)
    int wins;                  // Number of matches won
    int losses;                // Number of matches lost
    int draws;                 // Number of matches drawn
};

/**
 * Discards everything left in the input buffer up to the newline.
 * @pre none
 */
void clearBuffer()
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF)
        c = getchar();
}

/**
 * Checks if a BattlePet name is valid: 1-36 characters, only letters and '-'.
 * @param name The name to check
 * @return 1 if valid, 0 otherwise
 * @pre name is a null-terminated string
 */
int isValidName(char name[])
{
    int i = 0;
    int valid = 1;
    int len = strlen(name);

    if (len == 0 || len > MAX_NAME)
        valid = 0;

    while (valid && i < len)
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == '-'))
            valid = 0;
        i++;
    }

    return valid;
}

/**
 * Checks if a BattlePet with the given name is already in the ComPetDium.
 * @param pets Array of BattlePets
 * @param nPets Number of BattlePets in the array
 * @param name The name to look for
 * @return 1 if the name already exists, 0 otherwise
 * @pre nPets is between 0 and MAX_PETS
 */
int nameExists(struct BattlePet pets[], int nPets, char name[])
{
    int i = 0;
    int found = 0;

    while (!found && i < nPets)
    {
        if (strcmp(pets[i].name, name) == 0)
            found = 1;
        i++;
    }

    return found;
}

/**
 * Shows the 8 elements and asks the user to pick one.
 * Keeps asking until a valid number is entered.
 * @param element Array that will hold the chosen element's name
 * @pre element can hold at least 10 characters
 */
void chooseElement(char element[])
{
    char elements[NUM_ELEMENTS][MAX_ELEMENT] = {"Fire", "Water", "Grass", "Earth",
                                                "Air", "Electric", "Ice", "Metal"};
    int nChoice = 0;
    int i;

    while (nChoice < 1 || nChoice > NUM_ELEMENTS)
    {
        printf("Element\n");
        for (i = 0; i < NUM_ELEMENTS; i++)
            printf("  [%d] %s\n", i + 1, elements[i]);
        printf(">> ");

        if (scanf("%d", &nChoice) != 1)
            nChoice = 0;
        clearBuffer();

        if (nChoice < 1 || nChoice > NUM_ELEMENTS)
            printf(RED "Invalid choice! Please try again" RESET "\n");
    }

    strcpy(element, elements[nChoice - 1]);
}

/**
 * Adds a new BattlePet to the ComPetDium.
 * @param pets Array of BattlePets
 * @param pNPets Pointer to the number of BattlePets (increased by 1 on success)
 * @pre *pNPets is between 0 and MAX_PETS
 */
void addPet(struct BattlePet pets[], int *pNPets)
{
    char name[MAX_NAME + 2];
    char desc[MAX_DESC + 2];
    int valid = 0;

    if (*pNPets >= MAX_PETS)
        printf(RED "The ComPetDium is full!" RESET "\n");
    else
    {
        do
        {
            printf("\nName (letters and - only, max %d): ", MAX_NAME);
            scanf(" %37[^\n]", name);
            clearBuffer();

            if (!isValidName(name))
                printf(RED "Invalid name!" RESET "\n");
            else if (nameExists(pets, *pNPets, name))
                printf(RED "That name already exists!" RESET "\n");
            else
                valid = 1;
        } while (!valid);

        chooseElement(pets[*pNPets].element);

        valid = 0;
        do
        {
            printf("Description (max %d characters): ", MAX_DESC);
            scanf(" %241[^\n]", desc);
            clearBuffer();

            if (strlen(desc) > MAX_DESC)
                printf(RED "Invalid description!" RESET "\n");
            else
                valid = 1;
        } while (!valid);

        strcpy(pets[*pNPets].name, name);
        strcpy(pets[*pNPets].desc, desc);
        pets[*pNPets].matchCount = 0;
        (*pNPets)++;

        printf("BattlePet added!\n");
    }
}

/**
 * Fills in the details of one BattlePet.
 * @param pPet Pointer to the BattlePet to fill in
 * @param name Name of the BattlePet
 * @param element Elemental affinity of the BattlePet
 * @param desc Short description of the BattlePet
 * @pre strings fit within the limits of struct BattlePet
 */
void setPet(struct BattlePet *pPet, char name[], char element[], char desc[])
{
    strcpy(pPet->name, name);
    strcpy(pPet->element, element);
    strcpy(pPet->desc, desc);
    pPet->matchCount = 0;
}

/**
 * Loads the 16 initial BattlePets (Appendix D) into the array.
 * @param pets Array that will hold the BattlePets
 * @return The number of BattlePets loaded
 * @pre pets can hold at least 16 BattlePets
 */
int loadDefaultPets(struct BattlePet pets[])
{
    setPet(&pets[0], "Solaraffe", "Fire", "A fiery and majestic giraffe that harnesses the power of the sun.");
    setPet(&pets[1], "Firepupp", "Fire", "A loyal, flame-breathing dog that races through the night with fiery speed.");
    setPet(&pets[2], "Hydrake", "Water", "A sleek, serpentine creature that can summon powerful waves and whip through currents with ease.");
    setPet(&pets[3], "Meowguro", "Water", "A playful, aquatic catfish with feline-like agility in the water.");
    setPet(&pets[4], "Grawl", "Grass", "A wise and stealthy owl, covered in leaves and vines, blending into nature.");
    setPet(&pets[5], "Barkbear", "Grass", "A sturdy bear with a bark-like skin, nearly indestructible in nature's wilds.");
    setPet(&pets[6], "Terrashark", "Earth", "An earth-dwelling predator with the fierce speed and agility of a shark.");
    setPet(&pets[7], "Roarland", "Earth", "A fierce, rock-covered tiger with the ability to cause earth tremors with every roar.");
    setPet(&pets[8], "Airsting", "Air", "A graceful, flying stingray that glides through the air with the elegance of the wind.");
    setPet(&pets[9], "Zephyram", "Air", "A fast-moving ram that uses the power of the wind to leap great distances.");
    setPet(&pets[10], "Zaprat", "Electric", "A rat with fur that crackles with electric energy, using it to stun foes.");
    setPet(&pets[11], "Joltaroo", "Electric", "A kangaroo with electric energy that surges through its powerful legs when it jumps.");
    setPet(&pets[12], "Hailhound", "Ice", "A swift, fierce dog that can summon hailstorms, using the frozen pellets as weapons.");
    setPet(&pets[13], "Crocodice", "Ice", "A massive crocodile whose scales are covered in a thick layer of ice, allowing it to stalk through frozen waters.");
    setPet(&pets[14], "Steelephant", "Metal", "A massive elephant with skin as tough as steel, capable of trampling through anything.");
    setPet(&pets[15], "Rustcoon", "Metal", "A clever raccoon with metallic fur that can withstand rust and corrosion, scavenging through abandoned factories.");

    return 16;
}

/**
 * Displays all BattlePets as a numbered list (name and element only).
 * @param pets Array of BattlePets
 * @param nPets Number of BattlePets in the array
 * @pre nPets is between 0 and MAX_PETS
 */
void showPetList(struct BattlePet pets[], int nPets)
{
    int i;

    printf("\nComPetDium\n");
    for (i = 0; i < nPets; i++)
        printf("  [%d] %s (%s)\n", i + 1, pets[i].name, pets[i].element);
}

/**
 * Displays a player's roster grid using BattlePet array indices.
 * @param pets Array of BattlePets in the ComPetDium
 * @param roster 3x3 grid containing BattlePet indices or -1 for empty slots
 * @pre roster contains either -1 or a valid index into pets
 */
void displayRoster(struct BattlePet pets[], int roster[ROSTER_SIZE][ROSTER_SIZE])
{
    int row, col;

    printf("\nMatch Roster\n");
    for (row = 0; row < ROSTER_SIZE; row++)
    {
        for (col = 0; col < ROSTER_SIZE; col++)
        {
            if (roster[row][col] == -1)
                printf("< > ");
            else
                printf("<%s> ", pets[roster[row][col]].name);
        }
        printf("\n");
    }
}

/**
 * Creates a 3x3 roster by selecting BattlePets from the ComPetDium.
 * A BattlePet can only be selected once in the current player's roster.
 * @param pets Array of BattlePets in the ComPetDium
 * @param nPets Number of BattlePets available
 * @param roster 3x3 grid to store the selected BattlePet indices
 * @param playerNum Player number (1 or 2), used in prompts
 * @pre nPets is at least ROSTER_SIZE * ROSTER_SIZE and at most MAX_PETS
 * @pre roster is a valid 3x3 array
 */
void createRoster(struct BattlePet pets[], int nPets, int roster[ROSTER_SIZE][ROSTER_SIZE], int playerNum)
{
    int row, col, i, choice, valid;
    int picked[MAX_PETS] = {0};

    for (row = 0; row < ROSTER_SIZE; row++)
        for (col = 0; col < ROSTER_SIZE; col++)
            roster[row][col] = -1;

    printf("\nPlayer %d - Create your roster\n", playerNum);
    for (row = 0; row < ROSTER_SIZE; row++)
    {
        for (col = 0; col < ROSTER_SIZE; col++)
        {
            valid = 0;
            while (!valid)
            {
                displayRoster(pets, roster);
                printf("\nComPetDium\n");
                for (i = 0; i < nPets; i++)
                {
                    if (picked[i])
                        printf("  [x] %s\n", pets[i].name);
                    else
                        printf("  [%d] %s\n", i + 1, pets[i].name);
                }
                printf("Choose a BattlePet for position [%d][%d]: ", row, col);

                if (scanf("%d", &choice) != 1)
                    choice = 0;
                clearBuffer();

                if (choice < 1 || choice > nPets)
                    printf(RED "Invalid selection. Enter a number from 1 to %d." RESET "\n", nPets);
                else if (picked[choice - 1])
                    printf(RED "That BattlePet is already in your roster. Choose another." RESET "\n");
                else
                {
                    roster[row][col] = choice - 1;
                    picked[choice - 1] = 1;
                    valid = 1;
                }
            }
        }
    }

    printf("\nPlayer %d roster completed!\n", playerNum);
    displayRoster(pets, roster);
    printf("\nPress Enter to continue...");
    clearBuffer();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

/**
 * Displays the full details of one BattlePet.
 * @param pet The BattlePet to display
 * @pre none
 */
void showPetDetails(struct BattlePet pet)
{
    printf("\nName       : %s\n", pet.name);
    printf("Element    : %s\n", pet.element);
    printf("Description: %s\n", pet.desc);
    printf("Matches    : %d\n", pet.matchCount);
}

/**
 * Lets the user pick a BattlePet from the list to view its details.
 * Keeps asking until a valid number is entered. 0 goes back.
 * @param pets Array of BattlePets
 * @param nPets Number of BattlePets in the array
 * @pre nPets is between 0 and MAX_PETS
 */
void viewPets(struct BattlePet pets[], int nPets)
{
    int nChoice = -1;

    while (nChoice != 0)
    {
        showPetList(pets, nPets);
        printf("Enter number to view details (0 to go back): ");

        if (scanf("%d", &nChoice) != 1)
            nChoice = -1;
        clearBuffer();

        if (nChoice >= 1 && nChoice <= nPets)
            showPetDetails(pets[nChoice - 1]);
        else if (nChoice != 0)
            printf(RED "Invalid choice! Please try again" RESET "\n");
    }
}

/**
 * ComPetDium submenu. Edit and Delete come in later milestones.
 * @param pets Array of BattlePets
 * @param pNPets Pointer to the number of BattlePets (changes when one is added)
 * @pre *pNPets is between 0 and MAX_PETS
 */
void competdiumMenu(struct BattlePet pets[], int *pNPets)
{
    int nChoice = -1;

    while (nChoice != 0)
    {
        printf("\nComPetDium Menu\n");
        printf("  [1] View BattlePets\n");
        printf("  [2] Add BattlePet\n");
        printf("  [0] Back\n");
        printf(">> ");

        if (scanf("%d", &nChoice) != 1)
            nChoice = -1;
        clearBuffer();

        if (nChoice == 1)
            viewPets(pets, *pNPets);
        else if (nChoice == 2)
            addPet(pets, pNPets);
        else if (nChoice != 0)
            printf(RED "Invalid choice! Please try again" RESET "\n");
    }
}

/**
 * Checks if a username is valid: 1-36 characters, no spaces.
 * @param name The username to check
 * @return 1 if valid, 0 otherwise
 * @pre name is a null-terminated string
 */
int isValidUsername(char name[])
{
    int i = 0;
    int valid = 1;
    int len = strlen(name);

    if (len == 0 || len > MAX_NAME)
        valid = 0;

    while (valid && i < len)
    {
        if (name[i] == ' ')
            valid = 0;
        i++;
    }

    return valid;
}

/**
 * Checks if a player with the given username already exists.
 * @param players Array of players
 * @param nPlayers Number of players in the array
 * @param name The username to look for
 * @return 1 if the username already exists, 0 otherwise
 * @pre nPlayers is between 0 and MAX_PLAYERS
 */
int playerExists(struct Player players[], int nPlayers, char name[])
{
    int i = 0;
    int found = 0;

    while (!found && i < nPlayers)
    {
        if (strcmp(players[i].name, name) == 0)
            found = 1;
        i++;
    }

    return found;
}

/**
 * Asks for a new username and adds the player with 0 wins, losses, and draws.
 * Keeps asking until the username is valid and not taken.
 * @param players Array of players
 * @param pNPlayers Pointer to the number of players (increased by 1)
 * @return The index of the newly added player
 * @pre *pNPlayers is less than MAX_PLAYERS
 */
int addPlayer(struct Player players[], int *pNPlayers)
{
    char name[MAX_NAME + 2];
    int valid = 0;
    int index;

    do
    {
        printf("New player username (no spaces): ");
        scanf(" %37[^\n]", name);
        clearBuffer();

        if (!isValidUsername(name))
            printf(RED "Invalid username! Max %d characters, no spaces." RESET "\n", MAX_NAME);
        else if (playerExists(players, *pNPlayers, name))
            printf(RED "That username is already taken!" RESET "\n");
        else
            valid = 1;
    } while (!valid);

    index = *pNPlayers;
    strcpy(players[index].name, name);
    players[index].wins = 0;
    players[index].losses = 0;
    players[index].draws = 0;
    (*pNPlayers)++;

    return index;
}

/**
 * Lets a player be chosen from the list or created as a new player.
 * Keeps asking until a valid choice is made.
 * @param players Array of players
 * @param pNPlayers Pointer to the number of players
 * @param playerNum 1 or 2, shown in the title
 * @param taken Index of a player that cannot be chosen (-1 if none)
 * @return The index of the chosen player in the players array
 * @pre *pNPlayers is between 0 and MAX_PLAYERS
 */
int choosePlayer(struct Player players[], int *pNPlayers, int playerNum, int taken)
{
    int nChoice;
    int index = -1;
    int i;

    while (index < 0)
    {
        printf("\nPlayer %d\n", playerNum);
        printf("  [1] <New player>\n");
        for (i = 0; i < *pNPlayers; i++)
            printf("  [%d] %s\n", i + 2, players[i].name);
        printf(">> ");

        if (scanf("%d", &nChoice) != 1)
            nChoice = -1;
        clearBuffer();

        if (nChoice == 1)
        {
            if (*pNPlayers >= MAX_PLAYERS)
                printf(RED "The player list is full!" RESET "\n");
            else
                index = addPlayer(players, pNPlayers);
        }
        else if (nChoice >= 2 && nChoice <= *pNPlayers + 1)
        {
            if (nChoice - 2 == taken)
                printf(RED "That player is already Player 1!" RESET "\n");
            else
                index = nChoice - 2;
        }
        else
            printf(RED "Invalid choice! Please try again" RESET "\n");
    }

    return index;
}

int main()
{
    struct BattlePet pets[MAX_PETS];     // the ComPetDium
    struct Player players[MAX_PLAYERS];  // all known players
    int nPets;                           // how many BattlePets are in the ComPetDium
    int nPlayers = 0;                    // how many players there are
    int p1;                              // index of Player 1 in players
    int p2;                              // index of Player 2 in players
    int roster1[ROSTER_SIZE][ROSTER_SIZE];
    int roster2[ROSTER_SIZE][ROSTER_SIZE];
    int nChoice = 0;

    nPets = loadDefaultPets(pets);

    do
    {
        printf("\nMain Menu\n");
        printf("  [1] Battle!\n");
        printf("  [2] ComPetDium\n");
        printf("  [3] View Statistics\n");
        printf("  [0] Exit\n");
        printf(">> ");

        if (scanf("%d", &nChoice) != 1)
            nChoice = -1;
        clearBuffer(); // runs after EVERY read, so input like "3abc" is handled too

        if (nChoice == 1)
        {
            if (nPets < ROSTER_SIZE * ROSTER_SIZE)
                printf(RED "Not enough BattlePets to create a roster. At least %d are required." RESET "\n",
                       ROSTER_SIZE * ROSTER_SIZE);
            else
            {
                p1 = choosePlayer(players, &nPlayers, 1, -1);
                createRoster(pets, nPets, roster1, 1);
                p2 = choosePlayer(players, &nPlayers, 2, p1);
                createRoster(pets, nPets, roster2, 2);
                printf("\n%s vs. %s\n", players[p1].name, players[p2].name);
            }
        }
        else if (nChoice == 2)
            competdiumMenu(pets, &nPets);
        else if (nChoice == 3)
            printf("Player is viewing Statistics\n");
        else if (nChoice == 0)
            printf("Exiting...\n");
        else
            printf(RED "Invalid Choice! Please try again" RESET "\n");

    } while (nChoice != 0);

    return 0;
}



