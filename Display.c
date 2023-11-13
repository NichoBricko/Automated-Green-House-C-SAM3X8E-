#include "my_lib.c"

void Init_Display(void){
  *AT91C_PIOD_CODR = (1<< 0); //Clear reset
  Delay(20);
  *AT91C_PIOD_SODR = (1<< 0); //Set reset
  
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x40);//Set text home address
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x40);
  Write_Command_2_Display(0x42); //Set graphic home address
  Write_Data_2_Display(0x1E);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x41); // Set text area
  Write_Data_2_Display(0x1E);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x43); // Set graphic area
  Write_Command_2_Display(0x80); // text mode
  Write_Command_2_Display(0x94); // Text on graphic off 
}

void keypad_to_display(unsigned int button){
  if((button >= 0 ) && (button < 10)){
    Write_Data_2_Display(0x10 + button);
  }
  else if(button == 10){
    Write_Data_2_Display(0x0A);
  }else if(button == 11){
    Write_Data_2_Display(0x10); 
  }else if(button == 12){
    Write_Data_2_Display(0x03); 
  }
  Write_Command_2_Display(0xC0);
  button = 11;
  Delay(200000);
  
}

//Setting up display functions
unsigned char Read_Status_Display(void){
  unsigned char Temp;
  *AT91C_PIOC_ODR = 0x3FC;//make databus as input
  *AT91C_PIOC_SODR = (1 << 13);//Set dir as input (74chip, 1 = input) 
   *AT91C_PIOC_CODR = (1 << 12);//Clear/enable output, 
  *AT91C_PIOC_SODR = (1 << 14);//Set C/D 
  *AT91C_PIOC_CODR = (1 << 15);// clear chip
  *AT91C_PIOC_CODR = (1 << 16);//clear read display
  Delay(20);// make a delay
  Temp = (*AT91C_PIOC_PDSR & 0x3FC)>>2;//read databus and save in temp
  *AT91C_PIOC_SODR = (1 << 15);//set chip select display
  *AT91C_PIOC_SODR = (1 << 16);//set read display
  *AT91C_PIOC_SODR = (1 << 12); //disble output on chip
  *AT91C_PIOC_CODR = (1 << 13);//set dir as output
  return Temp;
}

void Write_Command_2_Display(unsigned char Command){
  while((Read_Status_Display() & 0x3) != 0x3); //Wait until read finished
  *AT91C_PIOC_CODR = 0x3FC; //Clear databus
  *AT91C_PIOC_SODR = ((unsigned int)Command) << 2 ; //Set command to databus
  *AT91C_PIOC_CODR = (1 << 13);//Set dir as output
  *AT91C_PIOC_CODR = (1 << 12);//enable output
  *AT91C_PIOC_OER = 0x3FC; // set databus as output
  *AT91C_PIOC_SODR = (1 << 14); //set c/d signal high (1= command)
  *AT91C_PIOC_CODR = (1 << 15);//Clear chip select display
  *AT91C_PIOC_CODR = (1 << 17); //set write display//clear write display
  Delay(20);
  *AT91C_PIOC_SODR = (1 << 15); //set chip select display
  *AT91C_PIOC_SODR = (1 << 17); //set write display
  *AT91C_PIOC_SODR = (1 << 12);//disable output
  *AT91C_PIOC_ODR = 0x3FC;//make databus as input
}

void Write_Data_2_Display(unsigned char Data){
  while((Read_Status_Display() & 0x3) != 0x3); //Wait until read finished
  *AT91C_PIOC_CODR = 0x3FC; //Clear databus
  *AT91C_PIOC_SODR = ((unsigned int)Data) << 2 ; //Set data to databus
  *AT91C_PIOC_CODR = (1 << 13); //Set dir as output
  *AT91C_PIOC_CODR = (1 << 12);//enable output
  *AT91C_PIOC_OER = 0x3FC;//set databusa as output
  *AT91C_PIOC_CODR = (1 << 14); //set c/d signal high (1= command)
  *AT91C_PIOC_CODR = (1 << 15); //clear chip select display
  *AT91C_PIOC_CODR = (1 << 17); //set write display
  Delay(20);
  *AT91C_PIOC_SODR = (1 << 15); //clear chip select display
  *AT91C_PIOC_SODR = (1 << 17); //set write display
  *AT91C_PIOC_SODR = (1 << 12);//disable output
  *AT91C_PIOC_ODR = 0x3FC;//make databus as input
}

void printDD(int num){
  if(num > 99){
    int y1digit = num / 1000;
    int y2digit = (num % 1000) / 100;
    int y3digit = (num % 100) / 10;
    int y4digit = num % 10;
    Write_Data_2_Display(0x10 + y1digit);
    Write_Command_2_Display(0xC0);
    Write_Data_2_Display(0x10 + y2digit);
    Write_Command_2_Display(0xC0);
    Write_Data_2_Display(0x10 + y3digit);
    Write_Command_2_Display(0xC0);
    Write_Data_2_Display(0x10 + y4digit);
    Write_Command_2_Display(0xC0);
  }else{
    int fdigit = num / 10;
    int ldigit = num % 10;
    Write_Data_2_Display(0x10 + fdigit);
    Write_Command_2_Display(0xC0);
    Write_Data_2_Display(0x10 + ldigit);
    Write_Command_2_Display(0xC0);
  }
}

void date_display(time *timeStamp){
  print_a_string("DATE: ");
  printDD(timeStamp->day);
  Write_Data_2_Display(0x0F);
  Write_Command_2_Display(0xC0);
  printDD(timeStamp->month);
  Write_Data_2_Display(0x0D);
  Write_Command_2_Display(0xC0);
  printDD(timeStamp->year);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0xC0);
  
  set_display_pointer(30, 0);
  
  
  print_a_string("TIME: ");
  printDD(timeStamp->hour);
  Write_Data_2_Display(0x1A);
  Write_Command_2_Display(0xC0);
  printDD(timeStamp->minute);
  Write_Data_2_Display(0x1A);
  Write_Command_2_Display(0xC0);
  printDD(timeStamp->second);
  
  

}

void reset_display_pointer(void){
  Write_Data_2_Display(0x0);
  Write_Data_2_Display(0x0);
  Write_Command_2_Display(0x24);
  
}

void set_display_pointer(char x, char y){
  Write_Data_2_Display(x);
  Write_Data_2_Display(y);
  Write_Command_2_Display(0x24);
  
}

void clear_display(void){
  reset_display_pointer();
  for(int i = 0; i < 640; i++){//640 total icons 
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0xC0); 
  }
  reset_display_pointer();
}

void print_character(char c){
  Write_Data_2_Display(c - 0x20);
  Write_Command_2_Display(0xC0);
}

void print_a_string(char c[]){
  for(int i = 0; c[i] != '\0'; i++){
    print_character(c[i]);
  }
}

void write_display_pos(char *text, char x, char y){
  Write_Data_2_Display(x);
  Write_Data_2_Display(y);
  Write_Command_2_Display(0x24);
  
  print_a_string(text);
  
}



void write_menu (int pos) {
  write_display_pos("MENU", 122 + pos, 0);
  write_display_pos("----------------------", 152 + pos, 0);
  write_display_pos("| 1. Setup Date      |", 182 + pos, 0);
  write_display_pos("| 2. Temperature     |", 212 + pos, 0);
  write_display_pos("| 3.                 |", 242 +pos, 0);
  write_display_pos("| 4. Record of Temps |", 16 + pos, 1);
  write_display_pos("| 5. Enable Fastmode |", 46 + pos, 1);
  write_display_pos("| 6.                 |", 76 + pos, 1);
  write_display_pos("----------------------", 106 + pos, 1);
                   
}

void write_setup_date_layout(){
   write_display_pos("Setup Date", 10, 0);
   write_display_pos("------------------------------", 30, 0);
   write_display_pos("New Date: DD/MM-YYYY", 60, 0);
   write_display_pos("New Time: HH:MM:SS", 90, 0);
   write_display_pos("Press * to Reset.", 74, 1);
   write_display_pos("Press # to Quit.", 104, 1);
}

char char_arrayf[1000];

char *float_to_char(float num){
    sprintf(char_arrayf, "%f", num);
    return char_arrayf;
}

char char_arrayi[1000];

char *int_to_char(int num){
    sprintf(char_arrayi, "%d", num);
    return char_arrayi;
}

char char_arrayu[1000];

char *uint_to_char(uint64_t num){
    sprintf(char_arrayu, "%llu", num);
    return char_arrayu;
}

void display_records(int i){
  write_display_pos("DAILY RECORD OF TEMPS", 0,0);
  update_Rec_time(first);

  
    write_display_pos("------------------------------", 30, 0);
    set_display_pointer(60, 0);
    print_a_string("DATE: ");
    printDD(timeStamp->day);
    Write_Data_2_Display(0x0F);
    Write_Command_2_Display(0xC0);
    printDD(timeStamp->month);
    Write_Data_2_Display(0x0D);
    Write_Command_2_Display(0xC0);
    printDD(timeStamp->year);
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0xC0);
    
    write_display_pos("Minimum: ", 90, 0);
    write_display_pos(" - Temp: ", 120, 0);
    write_display_pos(float_to_char(weeklystats[i].min), 129, 0);
    write_display_pos(" - Time: ", 150, 0);
    set_display_pointer(159, 0);
    printDD(weeklystats[i].minTime.hour);
    write_display_pos(":", 161, 0);
    set_display_pointer(162, 0);
    printDD(weeklystats[i].minTime.minute);
    
    write_display_pos("Maximum: ", 210, 0);
    write_display_pos(" - Temp: ", 240, 0);
    write_display_pos(float_to_char(weeklystats[i].max), 249, 0);
    write_display_pos(" - Time: ", 14, 1);
    set_display_pointer(23, 1);
    printDD(weeklystats[i].maxTime.hour);
    write_display_pos(":", 25, 1);
    set_display_pointer(26, 1);
    printDD(weeklystats[i].maxTime.minute);
    
    write_display_pos("Average Temp: ", 74, 1);
    write_display_pos(float_to_char(weeklystats[i].avg), 88, 1);
    
    first = first->next;
  
}

void display_config(){
  *AT91C_PIOD_PER = (1 << 0);//enable pin 25
  *AT91C_PIOD_OER = (1 << 0);//enable output
  *AT91C_PIOC_PER = 0xFF040;//enable pins c6, c12-c19
  *AT91C_PIOC_OER = 0xFF000;//output control pins
  *AT91C_PIOC_PPUDR= 0xFF040;
}

//End of setting up display