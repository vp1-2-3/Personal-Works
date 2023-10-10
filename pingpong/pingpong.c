#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

//---------------------------- DO NOT TOUCH THIS CODE (lines 8 to 55) -------
// ABSTRACTION LAYER for differences in semaphores between Linux and macOS
//---------------------------- DO NOT TOUCH THIS CODE (lines 8 to 53) -------
#if defined __APPLE__
  #include <dispatch/dispatch.h>    // macOS ONLY
#endif 

#if defined __APPLE__ 
  #define semaphore_t dispatch_semaphore_t
#else 
  #define semaphore_t sem_t
#endif

semaphore_t semPing, semPong, semPung, semPyng;

semaphore_t sem1, sem2, sem3, sem4;

semaphore_t semaphore_create(semaphore_t* semaphore, unsigned int level) { 
  #if defined __APPLE__
    return dispatch_semaphore_create((long long)(level));
  #else 
    sem_init(semaphore, 0, level);
    return *semaphore;  
  #endif
}

void semaphore_wait(semaphore_t* semaphore) { 
  #if defined __APPLE__
    dispatch_semaphore_wait(*semaphore, DISPATCH_TIME_FOREVER);
  #else 
    sem_wait(semaphore);
  #endif
}

void semaphore_signal(semaphore_t* semaphore) { 
  #if defined __APPLE__
    dispatch_semaphore_signal(*semaphore);
  #else 
    sem_post(semaphore);
  #endif 
}

void semaphore_destroy(semaphore_t* semaphore) { 
  #if defined __APPLE__ 
    dispatch_release(*semaphore);
  #else 
    sem_destroy(semaphore);
  #endif
}
//---------------------------- DO NOT TOUCH THIS CODE (lines 8 to 55) -------

#define PINGS  5
#define PONGS PINGS

void* ping(void* x) {       // pinger thread runner (x is not used currently)
  int pings = PINGS;
  while (pings-- > 0) {
    // TODO: call semaphore_wait...
    semaphore_wait(&semPing);
    printf("ping");
    // TODO: call semaphore_signal...
    semaphore_signal(&semPong);

  }
  return NULL;
} 

void* pong(void* x) {        // ponger thread runner (x is not used currently)
  int pongs = PONGS;
  while (pongs-- > 0) {
     // TODO: call semaphore_wait...
     semaphore_wait(&semPong);
     printf("  pong\n"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semPing);

  }
  return NULL;
}

void* pong2(void* x) {        // ponger thread runner (x is not used currently)
  int pongs = PONGS;
  while (pongs-- > 0) {
     // TODO: call semaphore_wait...
     semaphore_wait(&semPong);
     printf("  pong"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semPung);

  }
  return NULL;
}

void* pong3(void* x) {        // ponger thread runner (x is not used currently)
  int pongs = PONGS;
  while (pongs-- > 0) {
     // TODO: call semaphore_wait...
     semaphore_wait(&semPong);
     printf("  pong"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semPung);
    // TODO: call semaphore_wait...
     semaphore_wait(&semPong);
     printf("  pong\n"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semPing);

  }
  return NULL;
}

void* pung(void* x) {        // ponger thread runner (x is not used currently)
  int pungs = PONGS;
  while (pungs-- > 0) {
     // TODO: call semaphore_wait...
     semaphore_wait(&semPung);
     printf("  pung\n"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semPing);
  }
  return NULL;
}

void* pung2(void* x) {        // ponger thread runner (x is not used currently)
  int pungs = PONGS;
  while (pungs-- > 0) {
     // TODO: call semaphore_wait...
     semaphore_wait(&semPung);
     printf("  pung"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semPyng);
    semaphore_wait(&semPung);
     printf("  pung"); 
    // TODO: call semaphore_signal...
    semaphore_signal(&semPong);
    
  }
  return NULL;
}

void* pyng(void* x) {       // pinger thread runner (x is not used currently)
  int pyngs = PINGS;
  while (pyngs-- > 0) {
    // TODO: call semaphore_wait...
    semaphore_wait(&semPyng);
    printf("  pyng");
    // TODO: call semaphore_signal...
    semaphore_signal(&semPung);

  }
  return NULL;
} 

void helper() {
  pthread_t pinger, ponger;
  pthread_attr_t attr;
 
  semPing = semaphore_create(&semPing, 1);
  semPong = semaphore_create(&semPong, 0);

  pthread_attr_init(&attr);
  pthread_create(&ponger, &attr, pong, NULL);    // can create ponger first -- it will wait
  pthread_create(&pinger, &attr, ping, NULL);

  pthread_join(pinger, NULL);
  pthread_join(ponger, NULL);
 
  // TODO: call semaphore_destroy twice
  semaphore_destroy(&semPing);
  semaphore_destroy(&semPong);

  // TODO: change to print five lines of ping pong using semaphores
  printf("            SUCCESS\n");
  printf("\n\tdone...\n");
}

void helper_pung() {
  pthread_t pinger, ponger, punger;
  pthread_attr_t attr;
 
  semPing = semaphore_create(&semPing, 1);
  semPong = semaphore_create(&semPong, 0);
  semPung = semaphore_create(&semPung, 0);

  pthread_attr_init(&attr);
  pthread_create(&ponger, &attr, pong2, NULL);    // can create ponger first -- it will wait
  pthread_create(&pinger, &attr, ping, NULL);
  pthread_create(&punger, &attr, pung, NULL);

  pthread_join(pinger, NULL);
  pthread_join(ponger, NULL);
  pthread_join(punger, NULL);
 
  // TODO: call semaphore_destroy twice
  semaphore_destroy(&semPing);
  semaphore_destroy(&semPong);
  semaphore_destroy(&semPung);

  // TODO: change to print five lines of ping pong using semaphores
  printf("            SUCCESS\n"); 
  printf("\n\tdone...\n");
}

void helper_pyng(void* func, void* func2) {
  pthread_t pinger, ponger, punger, pynger;
  pthread_attr_t attr;
 
  semPing = semaphore_create(&semPing, 1);
  semPong = semaphore_create(&semPong, 0);
  semPung = semaphore_create(&semPung, 0);
  semPyng = semaphore_create(&semPyng, 0);

  pthread_attr_init(&attr);
  pthread_create(&ponger, &attr, func, NULL);    // can create ponger first -- it will wait
  pthread_create(&pinger, &attr, ping, NULL);
  pthread_create(&punger, &attr, func2, NULL);
  pthread_create(&pynger, &attr, pyng, NULL);

  pthread_join(pinger, NULL);
  pthread_join(ponger, NULL);
  pthread_join(punger, NULL);
  pthread_join(pynger, NULL);
 
  // TODO: call semaphore_destroy twice
  semaphore_destroy(&semPing);
  semaphore_destroy(&semPong);
  semaphore_destroy(&semPung);
  semaphore_destroy(&semPyng);

  // TODO: change to print five lines of ping pong using semaphores
  printf("            SUCCESS\n"); 
  printf("\n\tdone...\n");
}

void* num1(void* x) {       // pinger thread runner (x is not used currently)
  int pings = PINGS;
  while (pings-- > 0) {
    // TODO: call semaphore_wait...
    semaphore_wait(&sem1);
    printf("1");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem2);
    semaphore_wait(&sem1);
    printf("  1\n");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem1);

  }
  return NULL;
}

void* num2(void* x) {       // pinger thread runner (x is not used currently)
  int pings = PINGS;
  while (pings-- > 0) {
    // TODO: call semaphore_wait...
    semaphore_wait(&sem2);
    printf("  2");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem3);
    semaphore_wait(&sem2);
    printf("  2");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem1);

  }
  return NULL;
}

void* num3(void* x) {       // pinger thread runner (x is not used currently)
  int pings = PINGS;
  while (pings-- > 0) {
    // TODO: call semaphore_wait...
    semaphore_wait(&sem3);
    printf("  3");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem4);
    semaphore_wait(&sem3);
    printf("  3");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem4);
    semaphore_wait(&sem3);
    printf("  3");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem4);
    semaphore_wait(&sem3);
    printf("  3");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem2);

  }
  return NULL;
}

void* num4(void* x) {       // pinger thread runner (x is not used currently)
  int pings = PINGS;
  while (pings-- > 0) {
    // TODO: call semaphore_wait...
    semaphore_wait(&sem4);
    printf("  4");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem3);
    semaphore_wait(&sem4);
    printf("  4");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem3);
    semaphore_wait(&sem4);
    printf("  4");
    // TODO: call semaphore_signal...
    semaphore_signal(&sem3);

  }
  return NULL;
} 

void helper_num() {
  pthread_t one_, two_, three_, four_;
  pthread_attr_t attr;
 
  sem1 = semaphore_create(&sem1, 1);
  sem2 = semaphore_create(&sem2, 0);
  sem3 = semaphore_create(&sem3, 0);
  sem4 = semaphore_create(&sem4, 0);

  pthread_attr_init(&attr);
  pthread_create(&one_, &attr, num1, NULL);    // can create ponger first -- it will wait
  pthread_create(&two_, &attr, num2, NULL);
  pthread_create(&three_, &attr, num3, NULL);
  pthread_create(&four_, &attr, num4, NULL);

  pthread_join(one_, NULL);
  pthread_join(two_, NULL);
  pthread_join(three_, NULL);
  pthread_join(four_, NULL);
 
  // TODO: call semaphore_destroy twice
  semaphore_destroy(&sem1);
  semaphore_destroy(&sem2);
  semaphore_destroy(&sem3);
  semaphore_destroy(&sem4);

  // TODO: change to print five lines of ping pong using semaphores
  printf("            SUCCESS\n"); 
  printf("\n\tdone...\n");
}

int main(int argc, const char * argv[]) {
  helper();
  helper_pung();
  helper_pyng(pong3, pung2);
  helper_num();
  return 0;
}

//=========================================================================================
//  OUTPUT
//=========================================================================================

// vp@MSI:~/C++ Development Root/os/pingpong$ ./pingpong 
// ping  pong
// ping  pong
// ping  pong
// ping  pong
// ping  pong
//             SUCCESS

//         done...
// ping  pong  pung
// ping  pong  pung
// ping  pong  pung
// ping  pong  pung
// ping  pong  pung
//             SUCCESS

//         done...
// ping  pong  pung  pyng  pung  pong
// ping  pong  pung  pyng  pung  pong
// ping  pong  pung  pyng  pung  pong
// ping  pong  pung  pyng  pung  pong
// ping  pong  pung  pyng  pung  pong
//             SUCCESS

//         done...
// 1  2  3  4  3  4  3  4  3  2  1
// 1  2  3  4  3  4  3  4  3  2  1
// 1  2  3  4  3  4  3  4  3  2  1
// 1  2  3  4  3  4  3  4  3  2  1
// 1  2  3  4  3  4  3  4  3  2  1
//             SUCCESS

//         done...
// vp@MSI:~/C++ Development Root/os/pingpong$ 