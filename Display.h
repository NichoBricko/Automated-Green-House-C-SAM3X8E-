#ifndef  _DISPLAY_H
#define  _DISPLAY_H

void Init_Display();
void keypad_to_display(unsigned int button);
unsigned char Read_Status_Display();
void Write_Command_2_Display(unsigned char Command);
void Write_Data_2_Display(unsigned char Data);
void printDD(int num);



void date_display(time *timeStamp);
void print_character(char c);
void print_a_string(char c[]);
void write_display_pos(char *text, char x, char y);
void reset_display_pointer();
void write_menu (int pos);
void clear_display();
void write_display_pos(char *text, char x, char y);
void display_config();
void set_display_pointer(char x, char y);
void write_setup_date_layout();
char *float_to_char(float num);
void display_records(int i);
char *uint_to_char(uint64_t num);
char *int_to_char(int num);

#endif