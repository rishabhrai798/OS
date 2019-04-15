/*The Sleeping-Barber Problem. A barbershop consists of a waiting room with n chairs
and a barber room with one barber chair. If there are no customers to be served the
barber goes to sleep. If a customer enters the barbershop and all chairs are occupied
then the customer leaves the shop. If the barber is busy but chairs are available,
then the customer sits in one of the free chairs. If the barber is asleep, the
customer wakes up the barber. Write a program to coordinate the barber and the customers.*/

//Code By Rishabh Rai(11704013)  K17PD

//Lovely Professional University

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>    //standard library
#include <pthread.h>
#include <semaphore.h>  //including header file for semaphore
#include <limits.h>    //for max limits of variables
#define max_client 20   //defines maximum number of clients

void *client();  //declaring fuction for client thread
void *barber();   //declaring function for barber thread

sem_t chairs_mutex;
sem_t sem_client;
sem_t sem_barber;
int num_chairs;
//int clientWait;
int main() {
	pthread_t barbert;  //declaring barber thread
	pthread_t clientids[max_client]; //array of client thread max 20
	
	printf("Main thread beginning\n");
   
   int runTime,clients,i;
   //if (argc != 5){
	   printf("Please enter HairCut  time:");
	   
	  // exit(0);
   //}
   scanf("%d",&runTime);
   printf("\nNumber of clients: ");
   scanf("%d",&clients);
   printf("\nNumber of chairs: ");
   scanf("%d",&num_chairs);
  // printf("\nClient wait time: ");
  // scanf("%d",&clientWait);
   // Initialize semaphores 
   sem_init(&chairs_mutex,0,1);
   sem_init(&sem_client,0,0);
   sem_init(&sem_barber,0,0);
   //3. Create barber thread. 
   pthread_create(&barbert, NULL, barber, NULL);
   printf("Creating barber thread with id %lu\n",barbert);
   // 4. Create client threads. 
   for (i = 0; i < clients; i++){
	   pthread_create(&clientids[i], NULL, client, NULL);
	   printf("Creating client thread with id %lu\n",clientids[i]);
   }
   // 5. Sleep.
   printf("Barber is sleeping\n"); 
  // printf("main thread sleeping for %d seconds\n", runTime);
   sleep(clients);
   // 6. Exit.  
   printf("Barber Sleeping again\n");
   exit(0);
}

void *barber() {
   int worktime;
  
   while(1) {
      // waiting for a client(sem_client) 
	  sem_wait(&sem_client);
      // waiting for mutex to access chair count (chair_mutex) 
	  sem_wait(&chairs_mutex);
      // increment number of chairs available 
	  num_chairs += 1;
	  printf("Client awakes Barber\nBarber is awake now\n");
	  printf("Barber: Taking a client. Number of chairs available = %d\n",num_chairs);
      // signal to client that barber is ready to cut their hair (sem_barber) 
	  sem_post(&sem_barber);
      // give up lock on chair count 
	  sem_post(&chairs_mutex);
      // generate random number, worktime, from 1-4 seconds for length of haircut. 
	  worktime = (rand() % 4) + 1;
      // cut hair for worktime seconds (really just call sleep()) 
	  printf("Barber: Cutting hair for %d seconds\n", worktime);
	  sleep(worktime);
    } 
}

void *client() {
   int waittime;

   while(1) {
      // locking semwait on chair
	  sem_wait(&chairs_mutex);
      // if there are no chairs then
	  if(num_chairs <= 0){
           // unlocking mutext lock on chair
		   printf("Client: Thread %u leaving with no haircut\n", (unsigned int)pthread_self());
		   //pthread_exit(NULL);
		   sem_post(&chairs_mutex);
		   pthread_exit(NULL);
	  }
      //else if there are chairs 
	  else{
           // decreasing number of chairs in barber shop
		  
		   num_chairs -= 1;
			
 		   // pthread_exit(NULL);
		   printf("Client: Thread %u Sitting to wait. Number of chairs left = %d\n",(unsigned int)pthread_self(),num_chairs);
           // signal that a customer is ready 
		   sem_post(&chairs_mutex);
           // free mutex lock on chair count 
		   sem_post(&sem_client);
           // wait for barber (sem_barber) 
		   sem_wait(&sem_barber);
           // get haircut 
		   printf("Client: Thread %u getting a haircut\n",(unsigned int)pthread_self());
 		
	  }
      // random waiting time for next haircut
	  waittime = (rand() % 1) + 1;
      // sleep for waittime seconds 
	  sleep(waittime);
     }
}
