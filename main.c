#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    int number;
    char name[30];
    int age;

    int score_round;
    int total_points;

    int wins;
    int losses;

    int cons_wins;
    int cons_losses;

} Player;

typedef struct
{
    int round;
    char player1[30];
    char player2[30];
    char winner[30]; // winner name or "tie"

} GameNode;

typedef struct Elementgame
{
    GameNode g;
    struct Elementgame *next;
} Elementgame;

typedef struct Element
{
    Player p;
    struct Element *next;
} Element;
typedef Elementgame *game;

typedef Element *LG;
typedef Element *LP;
typedef Element *L;

typedef struct Cell
{
    Player info;
    struct Cell *next;
} Cell;

typedef struct
{
    Cell *head;
    Cell *tail;
} queue;

void initqueue(queue *f)
{
    f->head = NULL;
    f->tail = NULL;
}
int isEmpty(queue f)
{
    return f.head == NULL;
}
void enqueue(queue *f, Player p)
{
    Cell *d = malloc(sizeof(Cell));
    d->info = p;
    d->next = NULL;

    if (isEmpty(*f))
    {
        f->head = f->tail = d;
    }
    else
    {
        f->tail->next = d;
        f->tail = d;
    }
}
int dequeue(queue *f, Player *p)
{
    if (isEmpty(*f))
        return 0;
    Cell *tmp = f->head;
    *p = tmp->info;
    f->head = tmp->next;

    if (f->head == NULL)
        f->tail = NULL;
    free(tmp);
    return 1;
}
// a function that counts the digits of a given number
int digitSum(int x)
{ 
    int s = 0;
    if (x < 0)
        x = -x;
    if (x == 0)
        return 0;
    while (x > 0)
    {
        s = s + x % 10;
        x /= 10;
    }
    return s;
}
int randomValue()
{
    return rand() % 1000000 + 1;
}
// a function that increments the wins of a player who wins in a round of a game
void player(Player *p1, Player *p2)
{ 
    int i;
    p1->score_round = 0;
    p2->score_round = 0;
    i = 0;
    int m = 0;
    while (i < 12 && m < 3)
    {
        if (digitSum(randomValue()) % 5 == 0)
        {
            p1->score_round += 1;
        }
        if (digitSum(randomValue()) % 5 == 0)
        {
            p2->score_round += 1;
        }
        if (p2->score_round > p1->score_round)
        {
            m = p2->score_round - p1->score_round;
        }
        else
        {
            m = -p2->score_round + p1->score_round;
        }
        i++;
    }
}
void insertLP(LP *head, Player p)
{
    Element *n = malloc(sizeof(Element));
    n->p = p;
    n->next = NULL;

    if (*head == NULL)
        *head = n;
    else
    {
        Element *tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = n;
    }
}
void displayLP(LP head)
{
    printf("\n LP \n");
    while (head != NULL)
    {
        printf("%s\n", head->p.name);
        head = head->next;
    }
}
void displayLG(LG head)
{
    printf("\n LG\n");
    while (head != NULL)
    {
        printf("%s (%d points)\n", head->p.name, head->p.total_points);
        head = head->next;
    }
}
void insertLG(LG *head, Player p)
{
    Element *n = malloc(sizeof(Element));
    n->p = p;
    if (*head == NULL || (*head)->p.total_points < p.total_points)
    {
        n->next = *head;
        *head = n;
    }
    else
    {
        Element *q = *head;
        while (q->next != NULL && q->next->p.total_points >= p.total_points)
        {
            q = q->next;
        }
        n->next = q->next;
        q->next = n;
    }
}
// a function that manages where a player should go after winning or loosing a game
void manageP(Player *p, queue *F1, queue *F3, LP *lp, LG *lg)
{ 
    if (p->losses >= 5)
    {
        insertLP(lp, *p);
        return;
    }
    if (p->wins >= 5)
    {
        insertLG(lg, *p);
        return;
    }
    if (p->cons_wins >= 3)
    {
        enqueue(F1, *p);
        return;
    }
    if (p->cons_losses >= 3)
    {
        enqueue(F3, *p);
        return;
    }
}
//function to track the players and their scores
void countPRound(Player *p1, Player *p2)
{ 
    player(p1, p2);
    p1->total_points += p1->score_round;
    p2->total_points += p2->score_round;

    if (p1->score_round > p2->score_round)
    {
        p1->wins++;
        p1->cons_wins++;
        p1->cons_losses = 0;
        p2->losses++;
        p2->cons_losses++;
        p2->cons_wins = 0;
    }
    else if (p1->score_round < p2->score_round)
    {
        p2->wins++;
        p2->cons_wins++;
        p2->cons_losses = 0;
        p1->losses++;
        p1->cons_losses++;
        p1->cons_wins = 0;
    }
}
// initialisation of players
void enterPlayers(queue *f)
{
    int n;
    Player p;
    printf("give me how many players are there going to be\n");
    do
    {
        scanf("%d", &n);
    } while (n < 1);

    for (int i = 0; i < n; i++)
    {
        printf(" player %d\n", i + 1);
        printf("number");
        scanf("%d", &p.number);
        printf("name\n");
        scanf("%s", p.name);
        printf("age\n");
        scanf(" %d", &p.age);

        p.score_round = 0;
        p.total_points = 0;
        p.wins = 0;
        p.losses = 0;
        p.cons_wins = 0;
        p.cons_losses = 0;
        enqueue(f, p);
    }
}
// function to get the player who will player with the winner of the last game
int getPlayer(queue *F, queue *F1, queue *F3, Player *p)
{
    if (!isEmpty(*F1))
    {
        return dequeue(F1, p);
    }
    else if (!isEmpty(*F))
    {
        return dequeue(F, p);
    }
    else if (!isEmpty(*F3))
    {
        return dequeue(F3, p);
    }
    else
    {
        return 0;
    }
}
// counts how many elements we have
int queueCount(queue *q) 
{
    int cnt = 0;
    Cell *cur = q->head;
    while (cur)
    {
        cnt++;
        cur = cur->next;
    }
    return cnt;
}
// add element at the head of the queue so that the winner player plays directly
void enqueueFront(queue *f, Player p) 
{
    Cell *d = malloc(sizeof(Cell));
    d->info = p;
    d->next = f->head;
    f->head = d;
    if (f->tail == NULL)
        f->tail = d;
}
// a functions that see who gets to play first depending on the conditions of the lists and queues
int getTwoPlayers(queue *F1, queue *F, queue *F3, LP *lp, Player *p1, Player *p2)
{
    int c1 = queueCount(F1);
    int c = queueCount(F);
    int c3 = queueCount(F3);
    int total = c1 + c + c3;
    if (total == 0)
        return 0;
    if (total == 1)
    {
        Player tmp;
        if (c1 == 1)
        {
            dequeue(F1, &tmp);
            insertLP(lp, tmp);
            return 0;
        }
        else if (c == 1)
        {
            dequeue(F, &tmp);
            insertLP(lp, tmp);
            return 0;
        }
        else
        { // c3 == 1
            dequeue(F3, &tmp);
            insertLP(lp, tmp);
            return 0;
        }
    }
    if (c1 >= 2)
    {
        dequeue(F1, p1);
        dequeue(F1, p2);
        return 1;
    }
    if (c1 == 1)
    {
        dequeue(F1, p1);
        if (c > 0)
        {
            dequeue(F, p2);
            return 1;
        }
        else
        {
            dequeue(F3, p2);
            return 1;
        }
    }
    if (c >= 2)
    {
        dequeue(F, p1);
        dequeue(F, p2);
        return 1;
    }
    if (c == 1)
    {
        dequeue(F, p1);
        if (c3 > 0)
        {
            dequeue(F3, p2);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (c3 >= 2)
    {
        dequeue(F3, p1);
        dequeue(F3, p2);
        return 1;
    }
    return 0;
}
// a function to record the games
void insertGameRecord(Elementgame **head, int round, const char *p1, const char *p2, const char *winner)
{
    Elementgame *n = malloc(sizeof(Elementgame));
    n->g.round = round;
    strncpy(n->g.player1, p1, sizeof(n->g.player1) - 1);
    n->g.player1[sizeof(n->g.player1) - 1] = '\0';
    strncpy(n->g.player2, p2, sizeof(n->g.player2) - 1);
    n->g.player2[sizeof(n->g.player2) - 1] = '\0';
    strncpy(n->g.winner, winner, sizeof(n->g.winner) - 1);
    n->g.winner[sizeof(n->g.winner) - 1] = '\0';

    n->next = NULL;
    if (*head == NULL)
    {
        *head = n;
    }
    else
    {
        Elementgame *cur = *head;
        while (cur->next)
            cur = cur->next;
        cur->next = n;
    }
}

void displayGameRecords(Elementgame *head)
{
    printf("\n--- Game Records ---\n");
    while (head != NULL)
    {
        printf("Game %d: %s vs %s -> Winner: %s\n",
               head->g.round, head->g.player1, head->g.player2, head->g.winner);
        head = head->next;
    }
}
// this function is used to see the outcome of the player in part 1 after playing 
void handleRoundOutcome(Player *playerA, Player *playerB, queue *F, queue *F1, queue *F3, LP *lp, LG *lg)
{ 
    if (playerA->score_round > playerB->score_round)
    {
        printf("Winner: %s\n", playerA->name);
        if (playerA->losses >= 5 || playerA->wins >= 5 || playerA->cons_wins >= 3 || playerA->cons_losses >= 3)
        {
            manageP(playerA, F1, F3, lp, lg);
        }
        else
        {
            enqueueFront(F, *playerA);
        }
        if (playerB->losses >= 5 || playerB->wins >= 5 || playerB->cons_wins >= 3 || playerB->cons_losses >= 3)
        {
            manageP(playerB, F1, F3, lp, lg);
        }
        else
        {
            enqueue(F, *playerB);
        }
    }
    else if (playerB->score_round > playerA->score_round)
    {
        printf("Winner: %s\n", playerB->name);
        if (playerB->losses >= 5 || playerB->wins >= 5 || playerB->cons_wins >= 3 || playerB->cons_losses >= 3)
        {
            manageP(playerB, F1, F3, lp, lg);
        }
        else
        {
            enqueueFront(F, *playerB);
        }
        if (playerA->losses >= 5 || playerA->wins >= 5 || playerA->cons_wins >= 3 || playerA->cons_losses >= 3)
        {
            manageP(playerA, F1, F3, lp, lg);
        }
        else
        {
            enqueue(F, *playerA);
        }
    }
    else
    {
        printf("Round tied. Both go to tail of F.\n");
        if (playerA->losses >= 5 || playerA->wins >= 5 || playerA->cons_wins >= 3 || playerA->cons_losses >= 3)
        {
            manageP(playerA, F1, F3, lp, lg);
        }
        else
        {
            enqueue(F, *playerA);
        }
        if (playerB->losses >= 5 || playerB->wins >= 5 || playerB->cons_wins >= 3 || playerB->cons_losses >= 3)
        {
            manageP(playerB, F1, F3, lp, lg);
        }
        else
        {
            enqueue(F, *playerB);
        }
    }
}
int pgcd(int a, int b)
{
    int r;
    while (b != 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}
// function to see if 2 nums share at least 1 digit in common
int shares_digit(int g, int x) 
{
    if (g < 0)
        g = -g;
    if (x < 0)
        x = -x;
    if (g == 0 && x == 0)
        return 1;
    while (g > 0)
    {
        int dg = g % 10;
        int temp = x;
        if (temp == 0 && dg == 0)
            return 1;
        while (temp > 0) // double loop to check each one
        {
            if (temp % 10 == dg)
                return 1;
            temp /= 10;
        }
        g /= 10;
    }
    return 0;
}
// function of how a round is played in part 2
int playRoundPart2(Player *p1, Player *p2) 
{
    p1->score_round = 0;
    p2->score_round = 0;
    int pairs_generated = 0; // number of 2 number rounds generated so far (max 8) 
    int pairs_generated_p2 = 0;

    while (pairs_generated < 4 && pairs_generated_p2 < 4)
    {   // player 1
        int a = randomValue();
        int b = randomValue();
        pairs_generated++;

        int g = pgcd(a, b);
        int award = (shares_digit(g, a) || shares_digit(g, b)) ? 1 : 0;

        p1->score_round += award;
        // player 2
        int c = randomValue();
        int d = randomValue();
        pairs_generated_p2++;

        g = pgcd(c, d);
        award = (shares_digit(g, c) || shares_digit(g, d)) ? 1 : 0;

        p2->score_round += award;

        if (abs(p1->score_round - p2->score_round) >= 3)
        {
            return 0;
        }
    }
    return 1;
}
// same as coutPRound , just that this one is played differently as the first one
void countPRoundPart2(Player *p1, Player *p2)
{
    playRoundPart2(p1, p2);
    p1->total_points += p1->score_round;
    p2->total_points += p2->score_round;

    if (p1->score_round > p2->score_round)
    {
        p1->wins++;
        p1->cons_wins++;
        p1->cons_losses = 0;
        p2->losses++;
        p2->cons_losses++;
        p2->cons_wins = 0;
    }
    else if (p1->score_round < p2->score_round)
    {
        p2->wins++;
        p2->cons_wins++;
        p2->cons_losses = 0;
        p1->losses++;
        p1->cons_losses++;
        p1->cons_wins = 0;
    } // if there is a tie , nothing is done 
}
// same as the first one handleRoundOutcome it manages players after playing 
void handleRoundOutcomePart2(Player *pA, Player *pB, queue *F, queue *F1, queue *F3, LP *lp, LG *lg)
{
    int diff = abs(pA->score_round - pB->score_round);
    if (diff >= 3)
    {
        if (pA->score_round > pB->score_round)
        {
            printf("Winner: %s\n", pA->name);
            if (pA->cons_wins >= 2)
                insertLG(lg, *pA);
            else
                enqueue(F1, *pA);

            if (pB->losses >= 2)
                insertLP(lp, *pB);
            else
                enqueue(F3, *pB);
        }
        else
        {
            printf("Winner: %s\n", pB->name);
            if (pB->cons_wins >= 2)
                insertLG(lg, *pB);
            else
                enqueue(F1, *pB);

            if (pA->losses >= 2)
                insertLP(lp, *pA);
            else
                enqueue(F3, *pA);
        }
    }
    else
    {
        if (pA->score_round > pB->score_round)
        {
            printf("Limit rule: %s has higher score -> %s to F, %s to F3\n", pA->name, pA->name, pB->name);
            if (pA->losses >= 2)
                insertLP(lp, *pA);
            else if (pA->cons_wins >= 2)
                insertLG(lg, *pA);
            else
                enqueue(F, *pA);

            if (pB->losses >= 2)
                insertLP(lp, *pB);
            else
                enqueue(F3, *pB);
        }
        else if (pB->score_round > pA->score_round)
        {
            printf("Limit rule: %s has higher score -> %s to F, %s to F3\n", pB->name, pB->name, pA->name);
            if (pB->losses >= 2)
                insertLP(lp, *pB);
            else if (pB->cons_wins >= 2)
                insertLG(lg, *pB);
            else
                enqueue(F, *pB);

            if (pA->losses >= 2)
                insertLP(lp, *pA);
            else
                enqueue(F3, *pA);
        }
        else
        {
            printf("Limit reached and tie: both go to tail of F.\n");
            if (pA->losses >= 2)
                insertLP(lp, *pA);
            else
                enqueue(F, *pA);
            if (pB->losses >= 2)
                insertLP(lp, *pB);
            else
                enqueue(F, *pB);
        }
    }
}
// function to check if a player /s val exists
void scanQueueForExactValue(queue *q, int val, int checkWins, int *found)
{
    queue temp;
    initqueue(&temp);

    while (!isEmpty(*q))
    {
        Player p;
        dequeue(q, &p);
        if ((checkWins && p.wins == val) || (!checkWins && p.losses == val))
        {
            printf(" - %s\n", p.name);
            *found = 1;
        }
        enqueue(&temp, p);
    }
    while (!isEmpty(temp))
    {
        Player p;
        dequeue(&temp, &p);
        enqueue(q, p);
    }
}
// showing stats p1 
void showPart1Stats(L lp, LG lg, queue *F, queue *F1, queue *F3)
{
    printf("\n===  Part I statistics  ===\n");

    for (int i = 1; i <= 3; i++) // a loop of 3 since we are searching for the ones who won 1 to 3 games
    {
        int found = 0;
        printf("\n Players who won exactly %d part(s):\n", i);
        Element *cur = lg;
        while (cur)
        {
            if (cur->p.wins == i)
            {
                printf(" - %s\n", cur->p.name);
                found = 1;
            }
            cur = cur->next;
        }
        scanQueueForExactValue(F, i, 1, &found);
        scanQueueForExactValue(F1, i, 1, &found);
        scanQueueForExactValue(F3, i, 1, &found);

        if (!found)
            printf(" (none)\n");

        found = 0;
        printf("Players who LOST exactly %d part(s):\n", i);
        cur = lp;
        while (cur)
        {
            if (cur->p.losses == i)
            {
                printf(" - %s\n", cur->p.name);
                found = 1;
            }
            cur = cur->next;
        }
        scanQueueForExactValue(F, i, 0, &found);
        scanQueueForExactValue(F1, i, 0, &found);
        scanQueueForExactValue(F3, i, 0, &found);

        if (!found) // in the case no one has those conditions, means they didnt loose 1 or 2 parties
            printf(" (none)\n");
    }
}
// same thing as the first one
void showPart2Stats(L lp, L lg)
{
    printf("\n=== Part II statistics ===\n");
    int found = 0;
    printf("\nPlayers who WON 1 or 2 parts:\n");
    L cur = lg;
    while (cur)
    {
        if (cur->p.wins == 1 || cur->p.wins == 2)
        {
            printf(" - %s\n", cur->p.name);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found)
        printf(" (none)\n");
    found = 0;
    printf("\nPlayers who LOST 1 or 2 parts:\n");
    cur = lp;
    while (cur)
    {
        if (cur->p.losses == 1 || cur->p.losses == 2)
        {
            printf(" - %s\n", cur->p.name);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found )
        printf(" (none)\n");
}
// function for the time og a game
void actualhour(char buffer[])
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, 30, "%H:%M:%S", tm_info);
}
void autoPlayers(queue *f)
{
    Player players[] = {  // we choosed random players 
        {1, "hana", 20, 0, 0, 0, 0, 0, 0},
        {2, "Nina", 22, 0, 0, 0, 0, 0, 0},
        {3, "Sahar", 21, 0, 0, 0, 0, 0, 0},
        {4, "Saturn", 23, 0, 0, 0, 0, 0, 0},
        {5, "aya", 24, 0, 0, 0, 0, 0, 0}};

    int n = sizeof(players) / sizeof(players[0]);

    for (int i = 0; i < n; i++)
    {
        enqueue(f, players[i]);
    }

    printf("Initial queue built automatically with %d players.\n", n);
}

int main()
{
    srand(time(NULL)); // for the time
    // intitialization of everything
    queue F, F1, F3;
    initqueue(&F);
    initqueue(&F1);
    initqueue(&F3);
    LP lp = NULL;
    LG lg = NULL;
    int j;
    // we ask if the user wants to check directly the game or he wants to enter player from his side
    printf("\ndo you want it to be auto playing or do you have specific peaple\n");
    printf(" \nchoose 1 if you want it auto , and everything else to specify\n");
    scanf("%d", &j);
    if (j == 1)
    {
        autoPlayers(&F);// in the case he didnt choose to enter players
    }
    else
    {
        enterPlayers(&F); // in the case he choose to enter the info himself 
    }
    char buffer[30]; // hour
    printf("hour of the start ");
    actualhour(buffer);
    printf("%s\n", buffer);

    int players_in_F = queueCount(&F); // num of players at the start

    int roundNumber = 1;
    Elementgame *games = NULL;

    int totalRounds = 0;
    int part2Rounds = 0;
    int inPart2 = 0;

    while (1)
    {
        int num_of_players = queueCount(&F1) + queueCount(&F) + queueCount(&F3); 
        if (num_of_players == 0) // no player = no game ( but it asks the user to enter again since the game continue)
            break;
        if (num_of_players == 1) 
        {
            Player only;
            if (queueCount(&F1) == 1)
            {
                dequeue(&F1, &only);
                insertLP(&lp, only);
            }
            else if (queueCount(&F) == 1)
            {
                dequeue(&F, &only);
                insertLP(&lp, only);
            }
            else if (queueCount(&F3) == 1)
            {
                dequeue(&F3, &only);
                insertLP(&lp, only);
            }
            break;
        }
        Player playerA, playerB;
        // the got serves to get players if it,s not got means no players 
        int got = getTwoPlayers(&F1, &F, &F3, &lp, &playerA, &playerB);
        if (!got) 
            break;
        printf("\n=== Game %d: %s vs %s ===\n", roundNumber, playerA.name, playerB.name);

        if (!inPart2) // means we are in part 1
        {
            countPRound(&playerA, &playerB);
            printf("Score this round (Part I): %s: %d - %s: %d\n",
                   playerA.name, playerA.score_round, playerB.name, playerB.score_round);

            if (playerA.score_round > playerB.score_round)
                insertGameRecord(&games, roundNumber, playerA.name, playerB.name, playerA.name);
            else if (playerB.score_round > playerA.score_round)
                insertGameRecord(&games, roundNumber, playerA.name, playerB.name, playerB.name);
            else
                insertGameRecord(&games, roundNumber, playerA.name, playerB.name, "tie");

            handleRoundOutcome(&playerA, &playerB, &F, &F1, &F3, &lp, &lg);

            totalRounds++;
            if (players_in_F > 0 && totalRounds >= 3 * players_in_F) // we check the conditions to know if we haev to switch to part 2
            {
                int remaining = queueCount(&F1) + queueCount(&F) + queueCount(&F3);
                if (remaining > 0) // here the real check of players
                {
                    showPart1Stats(lp, lg, &F, &F1, &F3);// if we started part 2 we must show stast part 1 so that data doesnt mess up
                    inPart2 = 1;
                    part2Rounds = 0;
                    printf("\n---- Switching to Part II strategy (after %d Part I rounds) ----\n", totalRounds);
                }
            }
        }
        else // we are starting part 2
        {
            countPRoundPart2(&playerA, &playerB); 

            printf("Score this round (Part II): %s: %d - %s: %d\n", playerA.name, playerA.score_round, playerB.name, playerB.score_round);

            if (playerA.score_round > playerB.score_round)
                insertGameRecord(&games, roundNumber, playerA.name, playerB.name, playerA.name);
            else if (playerB.score_round > playerA.score_round)
                insertGameRecord(&games, roundNumber, playerA.name, playerB.name, playerB.name);
            else
                insertGameRecord(&games, roundNumber, playerA.name, playerB.name, "tie");

            handleRoundOutcomePart2(&playerA, &playerB, &F, &F1, &F3, &lp, &lg);

            part2Rounds++;
            if (players_in_F > 0 && part2Rounds >= 2 * players_in_F)
            {
                int remaining = queueCount(&F1) + queueCount(&F) + queueCount(&F3);
                if (remaining > 0)
                {
                    printf("\n---- 2n Part II rounds reached: finalizing remaining players into LG/LP ----\n");
                    Player tmp;
                    while (dequeue(&F1, &tmp))
                        insertLG(&lg, tmp);
                    while (dequeue(&F, &tmp))
                        insertLP(&lp, tmp);
                    while (dequeue(&F3, &tmp))
                        insertLP(&lp, tmp);

                    break;
                }
            }
        }
        // displaying results of a round each time
        printf("Totals: %s -> wins:%d losses:%d cons_wins:%d cons_losses:%d total_pts:%d\n", playerA.name, playerA.wins, playerA.losses, playerA.cons_wins, playerA.cons_losses, playerA.total_points);
        printf("Totals: %s -> wins:%d losses:%d cons_wins:%d cons_losses:%d total_pts:%d\n", playerB.name, playerB.wins, playerB.losses, playerB.cons_wins, playerB.cons_losses, playerB.total_points);

        roundNumber++; // round nums
    }

    displayGameRecords(games);
    printf("\n--- Final LG (winners) ---\n");
    displayLG(lg);
    printf("\n--- Final LP (losers) ---\n");
    displayLP(lp);
 // managing 
    Player tmp;
    while (dequeue(&F1, &tmp))
    {
        insertLG(&lg, tmp);
    }
    while (dequeue(&F, &tmp))
    {
        insertLP(&lp, tmp);
    }
    while (dequeue(&F3, &tmp))
    {
        insertLP(&lp, tmp);
    }

    showPart2Stats(lp, lg);
// now the next commnads it,s for the requierements demanded in the project
    L l = lp;
    while (l != NULL)
    {
        if (l->p.wins == 0)
        {
            printf("%s one of the player who didnt win anything  \n", l->p.name);
        }
        l = l->next;
    }
    l = lg;
    while (l != NULL)
    {
        if (l->p.wins == 0)
        {
            printf("%s one of the player who didnt win anything  \n", l->p.name);
        }
        l = l->next;
    }
    printf("hour of the end "); // end of the game = end time game
    actualhour(buffer);
    printf("%s\n", buffer);

    return 0;
}
