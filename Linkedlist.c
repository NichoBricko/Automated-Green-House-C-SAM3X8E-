#include "my_lib.c"


char insertFirst(node **first, node *el) {
  llsize++;
  if (el != NULL){
    node *temp;
    temp = *first;
    if(temp == NULL){ //If list is empty
      (*first) = el;
      el->next = NULL;
    }
    else{
      el->next = (*first);
      (*first)= el;
    }
  }
  else{
    return 0; //No memory left
  }
  return 1;
}


/*
void insertFirst(node **first, node *el){
  if(*first == NULL){
    *first = el;
    return;
  }
  node *temp;
  temp = el;
  temp->next = *first;
  *first = temp;
}*/

void freeMem(node **first) {
  if (*first == NULL) { // list is empty
    printf("Memory is already empty");
  } else {
    node *temp;
    while (*first != NULL) {
      temp = *first;
      *first = (*first)->next;
      free(temp); // freeing is converting the value of temp to void
    }
  }
}

/*
node createNew(float temperature) {
  node *temp; //= (node*)malloc(sizeof(node));
  temp = (node*)malloc(sizeof(node));
  while(temp == NULL){
    removeLast(&first);
    temp = (node*)malloc(sizeof(node));
  }
  temp->timeWhenRecorded = timeStamp;
  temp->recorded_temperature = temperature;
  temp->next = NULL;
  return *temp;
}*/

void removeLast(node **first){
  llsize--;
  node *previous; 
  node *current;
  current = *first;
  if (*first == NULL){
    return;
  }
  while(current->next != NULL){
    previous = current;
    current = current->next;
  }
  previous->next = NULL;
  freeMem(&current);
}

void printList(node *n) {
  while (n != NULL) {

    printf("Temp: %f \n", n->recorded_temperature);
    printf("Minute: %d \n", n->timeWhenRecorded.minute);
    printf("Day: %d \n", n->timeWhenRecorded.day);
    n = n->next;
  }
  printf("\n");
  return;
}

int sizell(node **first){
  node * temp;
  int size = 0;
  temp = *first;
  if(first == NULL){
    return 0;}
  while(temp->next != NULL){
    size++;
    temp = temp->next;
  }
  return size;
}
