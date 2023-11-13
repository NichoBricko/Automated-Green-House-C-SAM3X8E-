#include "my_lib.c"

#define AT91C_PIOD_AIMER (AT91_CAST(AT91_REG *) 0x400E14B0)
#define AT91C_PIOD_DIFSR (AT91_CAST(AT91_REG *) 0x400E1484)
#define AT91C_PIOD_SCDR (AT91_CAST(AT91_REG *) 0x400E148C)
#define AT91C_PWMC_CMRx (AT91_CAST(AT91_REG *) 0x4009422C) 

//void Write_Command_2_Display(unsigned char Command);
//void Write_Data_2_Display(unsigned char Data);
//void Delay(int Value);
//void display_config();
//void Systick_setup();

node *first;
//stats *head;
int dely = 0;
int e_dely = 0;


int delyset = 0;
int delycount = 0;

int mesdly = 0;
int mesdly2 = 0;
//int temp_flag = 0;
int incr;
int rec_flag;
int fastmode_check = 0;
//time *timeStamp;
time *checktime;
int get_tempflag = 0;
int get_tempflag2 = 0;
//int row[] = {2, 3, 4, 5};
//int col[] = {7, 8, 9};
int check_incr;

int r_min;
int r_hour;
int r_day;
int r_month;
int r_year;



int llsize;

float temperature;
//Getting keypad inputs

//End of keypad inputs


int incr = 0;

void SysTick_Handler(void){
  dely++;
  incr++;
  
  //manipulating systick delay, between the temp measures.
  //in order to continue updating the time in the systick.
  if(get_tempflag == 1) {
    startMeas1();
    get_tempflag = 0;
    get_tempflag2 = 1;
    dely = 0;
  }
  if(get_tempflag2 == 1 && dely > 15){
    startMeas2();
    get_tempflag2 = 0;
  }
  
  if(dely >= 1500)
    dely = 0;
  
  //update_time() includes a flag that triggers the temp meas
  //everytime a minute increases
  
  if(fastmode_check == 1){
      if(incr >= 33){
        update_time(timeStamp);
        get_tempflag = 1;
        incr = 0;
      }
    }else if(fastmode_check == 0){
      if(incr >= 1000){
        update_time(timeStamp);
        get_tempflag = 1;
        incr = 0;
      }
    }
}


void Systick_fastmode(){
  if(fastmode_check == 0){
    fastmode_check = 1;
    write_display_pos("enabled", 66, 1);
    while(func() != 0);
  }else{
    fastmode_check = 0;
    write_display_pos("       ", 66, 1);
    while(func() != 0);
  }
}


int main(){
  SystemInit();
  //SysTick_Config(SystemCoreClock*0.001);
  SysTick_Config(84000-1);
  keypad_config();
  display_config();
  Init_Display();
  clear_display();
  reset_display_pointer();
  //Systick_setup();
  init_valuesforweekly();
  Init_TimerTemp();
  //startMeas();
  get_tempflag = 1;
  
  timeStamp = (time*)malloc(sizeof(time));
  checktime = (time*)malloc(sizeof(time));
  set_time(timeStamp,55,59,23,21,3,2022);
  
  //write_menu(-2);
  reset_display_pointer();
  int setup_date_nicely[] = {0,1,3,4,6,7,8,9,30,31,33,34,36,37};
  
  while(1){
    reset_display_pointer();
    
    date_display(timeStamp);
    write_menu(-2);
    //print_attributes(timeStamp);
    //SysTick_Handler();

    
    int date[14];
    int p;
    int i;
    int key = func();
    if(key > 0  && key < 7){
      switch(key){
      case 1:
        while(func() != 0);
        i = 0;
        int temp;
        clear_display();
        //set_display_pointer(150, 0);
        write_display_pos("Setup Date", 10, 0);
        write_display_pos("------------------------------", 30, 0);
        write_display_pos("New Date: DD/MM-YYYY", 60, 0);
        write_display_pos("New Time: HH:MM:SS", 90, 0);
        write_display_pos("Press * to Reset.", 74, 1);
        write_display_pos("Press # to Quit.", 104, 1);
        
        while(i != 15){
          if(func() > 0 && func() != 10 && func() != 12){
            
            if(func() == 11)
              temp = 0;
            else
              temp = func();
              while(func() != 0);
            date[i] = temp;
            set_display_pointer(70+setup_date_nicely[i], 0);
            keypad_to_display(temp);
            i++;
            
          }
          
          if (func() == 10) {
            i = 0;
            write_display_pos("New Date: DD/MM-YYYY", 60, 0);
            write_display_pos("New Time: HH:MM:SS", 90, 0);
          }
          
          if (func() == 12) {
            i = 15;
          }
          //date_display(timeStamp);  
          if (i == 14){
            array_to_date(checktime, date);
            if(valid_time(checktime) == 0){
              i = 0;
              clear_display();
              date_display(checktime);
              write_display_pos("****INVALID DATE****", 184, 0);
              dely = 0;
              while(dely < 900);
              clear_display();
              write_setup_date_layout();
            }
            else{
              array_to_date(timeStamp, date);
              i++;
            }
            
          }
        }
        clear_display();
        break;
        
        case 2:
          p = 0;
          
          clear_display();
          while(func() != 12){
            if(func() == 6)
              p++;
            if(func() == 4 && p > 0)
              p--;
          display_records(p);
          
          }
          clear_display();
        break;
          
          //write_display_pos(int_to_char(llsize), 200, 0);
          //printList(first);
          //print_weeklystats(0);
          //print_weeklystats(1);


                 
        case 5:
          Systick_fastmode();
          
          
        /*
        SysTick_Config(SystemCoreClock*0.0001);
        while (func() != 12){
          date_display(timeStamp);
        }
        SysTick_Config(SystemCoreClock*0.001);
        clear_display();
        */
        break;
      }        
    }    
  }
  //return 0;
}






