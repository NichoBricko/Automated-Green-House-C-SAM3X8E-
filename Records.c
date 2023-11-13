#include "my_lib.c"

int days_months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int week_check = 0;

stats weeklystats[7];
stats dailystats;

float avg_sum = 0;
float avg_amount = 0;
int i = 0;

void temperature_recording(float data, recorded_time date){
  node *temp = (node*)malloc(sizeof(node));
  //if(temp == NULL)
  //removeLast(&first);
  while(temp == NULL){
    removeLast(&first);
    temp =(node*)malloc(sizeof(node));
  }
  /*if(llsize > 180){
    removeLast(&first);
  }*/
  
  //compare_values(temp);
  temp->recorded_temperature = data;
  temp->timeWhenRecorded = date;
  day_stats(*temp);
  insertFirst(&first, temp);
}
void init_valuesforweekly(){
  dailystats.max = -200;
  dailystats.min = 200;
}

void day_stats(node check){
  if(timeStamp->hour == 23 && timeStamp->minute == 59){
    if(i > 6){
      i = 0;
    }
    
    

    weeklystats[i].min = dailystats.min;
    weeklystats[i].max = dailystats.max;
    weeklystats[i].avg = avg_sum/avg_amount;
    weeklystats[i].maxTime.minute = dailystats.maxTime.minute;
    weeklystats[i].maxTime.hour = dailystats.maxTime.hour;
    weeklystats[i].minTime.minute = dailystats.minTime.minute;
    weeklystats[i].minTime.hour = dailystats.minTime.hour;
    weeklystats[i].maxTime.day = dailystats.date.day;
    weeklystats[i].date.day = check.timeWhenRecorded.day;
    weeklystats[i].date.month = check.timeWhenRecorded.month;
    weeklystats[i].date.year = check.timeWhenRecorded.year;
    dailystats.min = 200;
    dailystats.max = -200;
    //dailystats.maxTime = NULL;
    //dailystats.minTime = NULL;
    avg_sum = 0;
    avg_amount = 0;
    i++;
  }
  else{
    min(check);
    max(check);
    avg(check);
  }
}

void min(node min_check){
  if(min_check.recorded_temperature < dailystats.min){
    dailystats.min = min_check.recorded_temperature;
    dailystats.minTime = min_check.timeWhenRecorded;
  }
}


void max(node max_check){
  if(max_check.recorded_temperature > dailystats.max){
    dailystats.max = max_check.recorded_temperature;
    dailystats.maxTime = max_check.timeWhenRecorded;
  }
}

void avg(node avg_check){
  avg_sum += avg_check.recorded_temperature;
  avg_amount++;
}

void print_weeklystats(int i){
  printf("Average: %f \n", weeklystats[i].avg);
  printf("Min: %f \n", weeklystats[i].min);
  printf("Max: %f \n", weeklystats[i].max);
  printf("minTime Min: %d \n", weeklystats[i].minTime.minute);
  printf("minTime Hour: %d \n", weeklystats[i].minTime.hour);
  printf("maxTime Min: %d \n", weeklystats[i].maxTime.minute);
  printf("maxTime Hour: %d \n", weeklystats[i].maxTime.hour);
  printf("Day: %d \n", weeklystats[i].date.day);
  printf("Month: %d \n", weeklystats[i].date.month);
  printf("Year: %d \n", weeklystats[i].date.year);
}

struct stats get_weeklystats(int i){
  return (weeklystats[i]);
}

/*
day_stats createNew_day(time date, float temperature) {
  node *temp = (node*)malloc(sizeof(node));
  // temp = (struct Node)malloc(sizeof(struct Node));
  temp->recorded_temperature = temperature;
  *temp->timeWhenRecorded = date;
  temp->next = NULL;
  return *temp;
}*/

/*
void day_update(){
  if(week_check == 7){
    removeLast(&head);
    week_check--;
  }
  insertFirst(&head, day);
  day_stats * day = (day*)malloc(sizeof(day));
  week_check++;
}

float minimum_rec(node* compare){
  if (day->min == NULL){
    day->min = compare->recorded_temperature;
    return;
  }
  else{
    if(compare->recorded_temperature < day->min){
      day_->min = compare->recorded_temperature;
    }
  }
  
  return 0;
}

void compare_values(node *value){
  day->min = minimum_rec(value);
  
} */