# CS1_PA2
 Queues and Linked Lists

Soccer Match Ticketing Queues
Monster Country’s soccer tournament has greatly benefited from your PA1 code. The event features
thrilling matches with top teams, and it has become the talk of the town, drawing people from all over
to purchase tickets. Tickets must be bought in advance, but the ticketing center wasn’t prepared to handle
such a high volume of customers. There is only one counter with a single employee working to sell
tickets. To disguise this, the center has set up 12 lines, with customers directed to one of them. Note that,
some lines out of these 12 lines could be empty as well.

When a customer arrives, their arrival time, last name, line number, and the number of tickets they plan
to buy are recorded before they join a queue to meet the ticketing employee. Upon reaching the counter,
they must also provide details for each ticket they are purchasing, which adds to the processing time.
After assisting a customer, the cashier checks the status of all the active lines. The customer at the front
of each queue with the fewest tickets will be served next. If multiple customers are buying the same
minimum number of tickets, the cashier will choose the one from the lowest-numbered line. The lines
are numbered from 1 to 12, and any empty lines are ignored.

The time it takes for the cashier to process a customer is 20 seconds, plus 10 seconds per ticket. For
example, if a customer is buying 5 tickets, the checkout time would be 20 + (10 * 5) = 70 seconds.
It’s important to note that some of these 12 lines could be empty.

The Problem
You will write a program that reads information about customers: which line they go to the back of (1
through 12), at what time (in seconds) they enter that line, and the number of tickets they will buy, and
determines at what time each customer will check out.

The Input (Must be read from standard inputs using scanf (If you use file i/o, it will fail all test
cases and you will get zero))
The first line will contain a single positive integer, c (c ≤ 25), representing the number of test cases to
process. The test cases follow.

The first line of each test case will have a single positive integer, n (n ≤ 500,000), the number of
customers who are buying tickets. (Note: there can be 1 or 2 test cases with the maximum number of
customers while grading. The rest will be a fair bit smaller.)

The next n lines will have information about each customer. These n lines will be sorted from earliest
event to latest event. Each of these lines will start with a positive integer, t (t ≤ 109), representing the
time, in seconds, from the beginning of the simulation that the customer steps into a line. This is followed
by another positive integer, m (m ≤ 12), representing which line the customer steps into. This is followed
by the name of the customer, a single word string of 1 to 15 uppercase letters. The last item on the line
will be a positive integer, x (x ≤ 100), representing the number of tickets the customer is buying. It is
guaranteed that all of the check-in times are unique and that all of the customer names are unique as
well.

The Output (must be standard console output using printf (output to file using file i/o fprintf will receive zero))
For each customer, in the order that they get checked out, print a single line with the following format:
   CUSTOMER left the counter at time T from line X.
where CUSTOMER is the name of the customer checking out, X is the line they entered to check out,
and T is the number of seconds AFTER the start of the simulation, that they complete checking out.
(Thus, this time is the time they complete their order and leave the counter. This considers when they
were able to meet the employee at the counter, and the time needed to complete the order.)
After printing the output for a test case, print the following line

======
Sample Input
2
5
10 1 HUDSON 12
12 6 ADAM 8
13 1 MOHAMMAD 40
22 6 MATTHEW 39
100000 12 ANEESHA 53
8
100 1 AISHA 100
200 2 WILLIAM 99
300 3 MARIO 98
400 4 ABRAHAM 97
500 5 MIRAZIZ 96
600 6 JACOB 95
700 7 KEVIN 94
800 8 JEOVANI 93

Sample Output
HUDSON left the counter at time 150 from line 1.
ADAM left the counter at time 250 from line 6.
MATTHEW left the counter at time 660 from line 6.
MOHAMMAD left the counter at time 1080 from line 1.
ANEESHA left the counter at time 100550 from line 12.
======
AISHA left the counter at time 1120 from line 1.
JEOVANI left the counter at time 2070 from line 8.
KEVIN left the counter at time 3030 from line 7.
JACOB left the counter at time 4000 from line 6.
MIRAZIZ left the counter at time 4980 from line 5.
ABRAHAM left the counter at time 5970 from line 4.
MARIO left the counter at time 6970 from line 3.
WILLIAM left the counter at time 7980 from line 2.
======

Implementation Restrictions
1. You must create a struct that stores information about a customer (name, number of tickets, line
number, time entering line). Note that the storage of the line number is redundant, but is designed to ease
implementation. Also, you must create a function that can create a customer using dynamic memory
allocation, fill out the customer and then return the customer. You have to use this function whenever
you need to create a customer.

2. You must create a node struct for a linked list of customers. This struct should have a pointer to a
customer struct, and a pointer to a node struct.

3. You must create a struct to store a queue of customers. This struct should have two pointers – one to
the front of the queue and one to the back.

4. You must implement all of the lines as an array of queues of size 12 (stored as a constant). Note that
each queue is a linked list.

5. You must dynamically allocate memory as appropriate for linked lists.

6. Your queue must contain the following functions for queue operations and you must use them when
applicable :
   a) init
   b) Enqueue
   c) Dequeue
   d) Peek: Returns the front of the queue WITHOUT dequeuing
   e) Empty (returns 1 if the queue is empty, 0 if it is not)

7. You should never access the properties of a queue from outside of queue-related functions. Also, a
queue function should not access the properties of another queue. For example, the init function of a
queue should access only the properties of that particular queue.

8. You must manage memory appropriately. Specifically, when you dequeue, you should free the
memory for the node, but not for the customer. The memory for the customer will be freed later, right
after you calculate when the customer will finish checking out.

9. You should not store all the test cases and process them. You need to read each test case at a time and
process them.

10. You are not allowed to use any sorting algorithm in this assignment. If you maintain an array of
queues (where each queue is a linked list), and put the customer in the appropriate queue, you can
easily avoid using any sorting algorithm in this assignment.

11. Given the nature of the problem, you can initially assign each customer to their respective queue
before starting the checkout process. While this approach may not be suitable for all simulations, as
some require processing in chronological order, it works in this case because there is only one counter.
The key consideration when selecting a queue is the arrival time. For example, if the current time is
100, and three queues have customers who arrived before time 100 while the others have customers
who arrived after time 100, you should disregard the customers in the queues where the arrival time is
after 100. If all queues have customers who arrived after time 100, select the queue with the customer
who arrived first. Since arrival times are unique, there will be no ties.
