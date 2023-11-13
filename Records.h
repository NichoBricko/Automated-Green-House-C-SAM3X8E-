#ifndef Records_H
#define Records_H

typedef struct stats stats;
struct stats{
  recorded_time date;
  recorded_time maxTime;
  recorded_time minTime;
  float min;
  float max;
  float avg;
  struct stats *next;
};

void temperature_recording(float data, recorded_time date);
void compare_values(node *value);
void day_stats(node check);
void min(node min_check);
void max(node max_check);
void avg(node avg_check);
void print_weeklystats(int i);

extern stats weeklystats[7];

void init_valuesforweekly();

extern stats *head;
extern node *first;
//extern time* timeStamp;

extern int r_min;
extern int r_hour;
extern int r_day;
extern int r_month;
extern int r_year;

extern int llsize;



#endif