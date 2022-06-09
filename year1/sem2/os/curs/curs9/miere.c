#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BEES 30 
#define BEARS 5
#define MEAL 20

pthread_mutex_t m;
pthread_cond_t c;
int honey = 10 * MEAL;

void* bee(void*a) {
  while(1){
    pthread_mutex_lock(&m);
    honey++;
    printf("+");
    pthread_mutex_unlock(&m);
  }
  return 0;
}

void* bear(void*a) {
  while(1){
    pthread_mutex_lock(&m);
    if(honey > MEAL){
      honey -= MEAL;
      printf("M");
    }
    else {
      pthread_cond_signal(&c);
      printf("!");
    }
    pthread_mutex_unlock(&m);
  }
  return 0;

}

void* ranger(void*a) {
  while(1){
    pthread_mutex_lock(&m);
    while(honey >= MEAL) {
      pthread_cond_wait(&c, &m);
    }
    honey += 5 * MEAL;
    printf("       ");
    pthread_mutex_unlock(&m);
  }
}

int main(){
  pthread_t bees[BEES], bears[BEARS], rngr;
  int i;

  pthread_mutex_init(&m, NULL);
  pthread_cond_init(&c, NULL);

  pthread_create(&rngr, NULL, ranger, NULL);

  for(i = 0;i < BEES;++i){
    pthread_create(&bees[i], NULL, bee, NULL);
  }
  for(i = 0;i < BEARS;++i){
    pthread_create(&bears[i], NULL, bear, NULL);
  }

  pthread_join(rngr, NULL);
  for(i = 0;i < BEES;++i){
    pthread_join(bees[i], NULL);
  }
  for(i = 0;i < BEARS;++i){
    pthread_join(bears[i], NULL);
  }


  pthread_mutex_destroy(&m);
  pthread_cond_destroy(&c);


  return 0;
}
