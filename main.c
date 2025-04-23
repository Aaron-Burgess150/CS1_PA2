#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer {
    char *name;
    int tickets;
    int line;
    int time;
};

struct node {
    struct Customer *customer;
    struct node *next;
};

struct queue {
    struct node *front;
    struct node *back;
};

//function prototypes
void init(struct queue *qPtr);
void enQueue(struct queue *qPtr, struct Customer *customer);
struct Customer* deQueue(struct queue *qPtr);
struct Customer* peek(struct queue *qPtr);
int empty(struct queue *qPtr);
struct Customer* createCustomer(char *name, int tickets, int line, int time);
void freeCustomer(struct Customer *customer);

int main(void) {
    struct queue queue[12];
    for (int i = 0; i < 12; i++) {
        init(&queue[i]); //make each queue an actual queue
    }
    int c; //number of test cases
    int n; //number of customers
    scanf("%d", &c);
    for (int i = 0; i < c; i++) { //for each test case
        scanf("%d", &n);
        for (int j = 0; j < n; j++) { //for each customer
            //create and scan for time, line, name, and number of tickets
            int time, line, tickets;
            char name[16];
            scanf("%d", &time);
            scanf("%d", &line);
            scanf("%s", name);
            scanf("%d", &tickets);
            //make a customer to pass to the enQueue function (the line is the line scanned - 1
            struct Customer *customer = createCustomer(name, tickets, line, time);
            enQueue(&queue[line-1], customer);
        }

        //checkout process
        int time = 0; //keep track of time
        for (int j = 0; j < n; j++) { //for each customer
            int lowest_time = 1000000001; //actual lowest time
            int index = 0; //queue the person with the lowest time is in
            int waiting = 0; //1 is there is someone waiting with time lower than time itself
            int lowest_tickets = 101; //to find which queue has the person with the least amount of tickets with a time lower than time
            struct Customer *check; //for the peek function
            for (int k = 0; k < 12; k++) { //for each queue
                if (empty(&queue[k])) { //if the queue is empty, go to the next queue
                    continue;
                }
                check = peek(&queue[k]); //get the customer at the start of each queue that has customers
                if (waiting) { //if someone is waiting
                    if (check->time < time) { //check the times of the people waiting
                        if (check->tickets < lowest_tickets) { //if that customer has a lower number of tickets out of the people waiting
                            lowest_tickets = check->tickets;
                            index = k;
                        }
                    }
                }
                else{ //no one waiting
                    if (check->time < time) { //did the person at the start of each line join the line at the current time
                        waiting = 1; //someone is now waiting
                        lowest_tickets = check->tickets;
                        index = k;
                    }
                    else { //no new person waiting
                        if (check->time < lowest_time) { //keeps track of who is to be served
                            lowest_time = check->time;
                            index = k;
                        }
                    }
                }
            }
            check = deQueue(&queue[index]); //serve the person at the start of the queue

            //calculate the time variable for each test case
            if (!waiting) {
                time = check->time;
            }
            time += 20 + (10*check->tickets);
            printf("%s left the counter at time %d from line %d.\n", check->name, time, check->line);

            //free the Customer that got dequeue after printing out their information
            freeCustomer(check);
        }
        printf("======\n");
    }
}

void init(struct queue *qPtr){
    qPtr->front = NULL;
    qPtr->back = NULL;
}

void enQueue(struct queue *qPtr, struct Customer *customer) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation error");
        return;
    }

    newNode->customer = customer;
    newNode->next = NULL;

    //check if queue is empty
    if (empty(qPtr)) {
        qPtr->front = newNode;
        qPtr->back = newNode;
        return;
    }

    //add temp to end of queue and make the new back the temp
    qPtr->back->next = newNode;
    qPtr->back = newNode;
}

struct Customer* deQueue(struct queue *qPtr) {
    if (empty(qPtr)) {
        return NULL;
    }
    struct Customer *saveCustomer = qPtr->front->customer;
    struct node *temp = qPtr->front;

    qPtr->front = qPtr->front->next;

    free(temp);
    return saveCustomer;
}

struct Customer* peek(struct queue *qPtr){
    if (qPtr->front != NULL) {
        return qPtr->front->customer;
    }
    return NULL;
}

int empty(struct queue *qPtr) {
    return qPtr->front == NULL;
}

struct Customer* createCustomer(char *name1, int tickets, int line, int time) {
    struct Customer *newCustomer = (struct Customer *)malloc(sizeof(struct Customer));
    if (newCustomer == NULL) {
        printf("Memory allocation error for the customer");
        return NULL;
    }

    newCustomer->name = (char *)malloc(sizeof(char)*(strlen(name1) + 1));
    if (newCustomer->name == NULL) {
        printf("Memory allocation error for the customer's name");
        free(newCustomer);
        return NULL;
    }

    strcpy(newCustomer->name, name1);
    newCustomer->tickets = tickets;
    newCustomer->line = line;
    newCustomer->time = time;

    return newCustomer;
}

void freeCustomer(struct Customer *customer) {
    free(customer->name);
    free(customer);
}