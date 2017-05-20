/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"
///
#define ledpart_one  1
#define ledpart_two  2
#define ledpart_three 3
#define input_password_statue 5
#define name_patter_flash    1
#define lcd_display_roll     2

///
/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */

extern u8 G_au8DebugScanfBuffer[];
extern u8 G_u8DebugScanfCharCount;
/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
	LedOff(BLUE);
	LedOff(YELLOW);
	LedOff(RED);
	LedOff(PURPLE);
	//PWMAudioOff(BUZZER1);
	//PWMAudioSetFrequency(BUZZER1,500);
/*
 LedOn(BLUE);
 LedToggle(PURPLE);
 LedPWM(RED,LED_PWM_10);
 LedBlink(YELLOW,LED_2HZ);
 */
  /* If good initialization, set state to Idle */
  if( 1 )
  {
   // UserApp1_StateMachine = UserApp1SM_Idle;
   UserApp1_StateMachine =      Lcd_display;
     //UserApp1_StateMachine =BCD_code_display;
    // ledon
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_FailedInit;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */
//***
//
//
void Lcd_display(void)
{
   static u8* u8_string= "Hello world!";//数组和指针是一样
   u8 u8_len      = 0;
   u8_len         = strlen(u8_string);
   static u8 u8_counter =0;
   static u8 u8_lcd_display_patter =0;
   static BOOL ON_OFF_turn   = FALSE;
  /* if(G_u32SystemTime1ms%300==0)///
   	{ 
   	  //LCDCommand(LCD_CLEAR_CMD);//可以显示刷新
   	  LCDClearChars(LINE1_START_ADDR,u8_counter);
   	  LCDMessage(LINE1_START_ADDR+u8_counter,u8_string);
	  u8_counter++;
	  if((u8_counter+u8_len)>=40)
	  	u8_counter =0;
	  
   	}*/

  switch (u8_lcd_display_patter)
  	{
  	   case name_patter_flash:
          if(G_u32SystemTime1ms%500==0)
          	{
			  	if(ON_OFF_turn==1){
			    ON_OFF_turn =0;
				LCDMessage(LINE1_START_ADDR,"Hello EIE");
					}
				else
					
					{ON_OFF_turn=0;
				     LCDClearChars(LINE1_START_ADDR,40);//clear the lcd 
					}
  			}
		 //
	   	 break;
		case lcd_display_roll:
          
			
		 break;
  	}
    if(WasButtonPressed(BUTTON1))
    	{
    	   ButtonAcknowledge(BUTTON1);
		   u8_lcd_display_patter =name_patter_flash;//flash display the name 
		   	
    	}
	if(WasButtonPressed(BUTTON2))
		{
      
		   ButtonAcknowledge(BUTTON2);
		   u8_lcd_display_patter= lcd_display_roll;
		}
   if(WasButtonPressed(BUTTON0))
   	{
   	   ButtonAcknowledge(BUTTON0);
	   u8_string = G_au8DebugScanfBuffer;
   	}
}
void Buzzled_song(void)//tiger
{
  static u8 u8_count_next =0;
  static BOOL B_off_buzzel=FALSE;
   u8 u8_songs[] =
   	{1,1,1,1,2,2,2,2,3,3,3,3,1,1,1,1,
   	 1,1,1,1,2,2,2,2,3,3,3,3,1,1,1,1,
   	 3,3,3,3,4,4,4,4,5,5,5,5,5,5,5,5,
   	 3,3,3,3,4,4,4,4,5,5,5,5,5,5,5,5,
   	 5,5,6,5,5,4,3,3,3,3,1,1,1,1,
   	 5,5,6,5,5,4,3,3,3,3,1,1,1,1,
   	 1,1,1,1,1,5,5,5,5,1,1,1,1,1,1,1,
   	 1,1,1,1,1,5,5,5,5,1,1,1,1,1,1,1,0
   	};
  // if(u8_songs[u8_count_next]!=0)
   	
   	  switch (u8_songs[u8_count_next])
   	  	{
   	  	  case 1:
		  	PWMAudioSetFrequency(BUZZER1,131);
				PWMAudioSetFrequency(BUZZER2,145);
				PWMAudioSetFrequency(BUZZER2,131);
				
		  	break;
		  case 2:
		  	PWMAudioSetFrequency(BUZZER1,147);
			PWMAudioSetFrequency(BUZZER2,160);
			PWMAudioSetFrequency(BUZZER2,147);
			
		  	break;
		  case 3:
		  	PWMAudioSetFrequency(BUZZER1,165);
			PWMAudioSetFrequency(BUZZER2,170);
			PWMAudioSetFrequency(BUZZER2,165);;
			
		  	break;
		  case 4:
		  	PWMAudioSetFrequency(BUZZER1,175);
			PWMAudioSetFrequency(BUZZER2,190);
			PWMAudioSetFrequency(BUZZER2,175);
			
		  	break;
          case 5:
		  	PWMAudioSetFrequency(BUZZER1,196);
			PWMAudioSetFrequency(BUZZER2,196);
			
			
		  	break;
		  case 0:
		  	u8_count_next =0;
		  	break;
		  	
		  }
	  if(B_off_buzzel == TRUE)
	  	{
		  if(G_u32SystemTime1ms%100==0)
		  	{
		  	 u8_count_next++;
			 LedToggle(LCD_GREEN);
			 // LedToggle(LCD_RED);
			   LedToggle(LCD_BLUE);
			 for(u8 u8_temp_1=0;u8_temp_1<=7;u8_temp_1++)
			 	{
			 	LedOff(u8_temp_1);
			 	}
			 for(u8 u8_temp_2=0;u8_temp_2<=u8_songs[u8_count_next];u8_temp_2++)
			 	
			 	LedOn(u8_temp_2);
			 DebugPrintf("your tone:\r\n");
				DebugPrintNumber(u8_songs[u8_count_next]);
				DebugPrintf("\r\n");
		  	}
	  }
	  if(WasButtonPressed(BUTTON0))
	  	{
		  	ButtonAcknowledge(BUTTON0);
			if(B_off_buzzel==FALSE)
				{
				u8_count_next=0;
				PWMAudioOn(BUZZER1);
				PWMAudioOn(BUZZER2);
				B_off_buzzel = TRUE;
				}
			else
				{B_off_buzzel =FALSE;

				PWMAudioOff(BUZZER1);
				PWMAudioOff(BUZZER2);
			}
	  	}
	  
}
//
void Debug_serial_port(void)
{   u8 u8_temp = 0;
    static u8 u8_temp_counter=0;
	static u8 u8_temp_counter1=0;
	static u8 u8_temp_bit     =0;
    u8 u8_name[] ="yankui";
	static u8 u8_bit_set      =0;
	u8 u8_character[] = "*********";
    u8 string_u8[]="\n\rCharacters in buffer: ";
	static u8 u8NumCharsMessage[] = "\n\rCharacters in buffer: ";
	static bool send_port = FALSE;
	if(WasButtonPressed(BUTTON0))
		{ButtonAcknowledge(BUTTON0);
	     DebugPrintf(string_u8);
		 DebugLineFeed();
		   if(send_port == FALSE)
		   	send_port= TRUE;
		   else 
		   	send_port= FALSE;
		  }
        
  
  /* Print message with number of characters in scanf buffer */
  if(WasButtonPressed(BUTTON3))
  {
	   ButtonAcknowledge(BUTTON3);
	   
	    u8_temp_counter1=0;//重新计算
	   /* DebugPrintf(u8NumCharsMessage);//为什么多一个0.
	    DebugPrintNumber(G_u8DebugScanfCharCount);
	    DebugLineFeed();
		DebugPrintf("\r\n***");
		DebugPrintf("\r\n");
		//DebugPrintf(G_au8DebugScanfBuffer);
		//G_au8DebugScanfBuffer[]={};*/
	 // }
	  for(u8_temp=0;u8_temp<=G_u8DebugScanfCharCount;u8_temp++)
	  	{ 
	          //if(G_au8DebugScanfBuffer[u8_temp]== 'y')
	          { 
	            if(G_au8DebugScanfBuffer[u8_temp]== u8_name[u8_temp_counter])
	          	{
	          	u8_temp_counter++;
					if(u8_temp_counter>=6)
						{
						u8_temp_counter = 0;
						u8_temp_counter1++;
						}
	          	  
	          	  //send_port= TRUE;
	          	}
	          }
			  	///again back
	  	}
  	}
  if(WasButtonPressed(BUTTON2))
	  	{
	  	   DebugPrintf("\r\n***\r\n");
			ButtonAcknowledge(BUTTON2);
			DebugPrintNumber(u8_temp_counter1);
			DebugPrintf("\r\n***");
			DebugPrintf("\r\n");
			DebugPrintf("your name:\r\n");
			//DebugPrintf(u8_name);
			DebugPrintf("******\r\n");
			//DebugPrintf(G_au8DebugScanfBuffer);
	  	}
  if(WasButtonPressed(BUTTON1))
	  	{
		  	ButtonAcknowledge(BUTTON1);
		  	for(u8_temp_counter=0;u8_temp_counter<=4;u8_temp_counter++)
			  	{
			  	  if(u8_temp_counter1%(10^u8_temp_counter)==0)//求出多少位
				  	continue;
				  else
				  	u8_bit_set++;  //计算输入名字次数的位数
			  	}
		  	
		  	 for(u8_temp_counter=0;u8_temp_counter<=u8_bit_set;u8_temp_counter++)
		  	 	{
		  	 	   u8_character[u8_temp_counter]='*';
		  	 	}
	                   DebugPrintf("\r\n");
		  	   DebugPrintf(u8_character);
			   DebugPrintf("\r\n");
			   DebugPrintf("*");
			   DebugPrintNumber(u8_temp_counter1);
			   DebugPrintf("*");
			   DebugPrintf("\r\n");
	                   
	                  DebugPrintf(u8_character);
	                  DebugPrintf("\r\n");
				//DebugPrintf(G_au8DebugScanfBuffer);
	  	}
	//DebugLineFeed();//this is what useful?
}
//
void buzzle_test(void)
{
   static BOOL  b_on_off = FALSE;
   PWMAudioSetFrequency(BUZZER1,500);
   if(WasButtonPressed(BUTTON0))
   	{
   	    ButtonAcknowledge(BUTTON0);
		if (b_on_off==FALSE)
			{
			  PWMAudioOff(BUZZER1);
			  b_on_off =  TRUE;
			}
		else
			{
			PWMAudioOn(BUZZER1);
			b_on_off  = FALSE;}
		
   	}
}
//to complete the code to scord 
void led_display_rat(void)
{
     static u32 u32_led_counter = 0;
	 
	 static BOOL B_BUTTON_PUSHE = FALSE;
	 static u8 tmep_led =0;
	 static BOOL b_led_display  = FALSE;
	 static u8  u8_temp_number  = 0;
	 static u8  u8_mode_case    = 0;
	 switch (u8_mode_case)
	 		{
				case 0 ://ready
				if(WasButtonPressed(BUTTON3))
					{
					ButtonAcknowledge(BUTTON3);
					u8_mode_case = 1;//to begin mode
					}
				break;
				case 1:
					if(G_u32SystemTime1ms%500==0)
						{
						LedOn(RED);
							}
					else if(G_u32SystemTime1ms%2001==0)
						{
						LedOff(RED);
						u8_mode_case =2;//game start
						}
				break;
				case 2://game cycle 10 times
				     //if(u8_temp_number==0)
				     	{
				     B_BUTTON_PUSHE = TRUE;
				     	}
					 u8_mode_case =3;
					//if((u8_temp_number>=10)||(B_BUTTON_PUSHE==FALSE))//
					   // u8_mode_case =3;
					break;		
	 	}
	     if(u8_mode_case == 3)//game cycle
	     	{
	     	 if(B_BUTTON_PUSHE == TRUE)
	     	 	{
                  B_BUTTON_PUSHE =FALSE;
                  tmep_led = u32_led_counter%4;//rand one led
                  LedOn(tmep_led);//turn on
 	 	        }
			if(WasButtonPressed(tmep_led))
			    {
			      LedOff(tmep_led);
			      ButtonAcknowledge(tmep_led);//turn off tmep leds
			      B_BUTTON_PUSHE = TRUE;
			    }
			   
	     	}
	 /*
	 if(B_BUTTON_PUSHE == TRUE)
	 	{
	 	 if(G_u32SystemTime1ms%500==0)
	 	 	{
		 	 if(b_led_display == FALSE)
			 {b_led_display = TRUE;
			 tmep_led = u32_led_counter%8;
                         }
			 else
			 {b_led_display=  FALSE;
                         }
	 	 	}
	 	}
	 if(WasButtonPressed(BUTTON3))
	 	{
	 	  ButtonAcknowledge(BUTTON3);
		  if(B_BUTTON_PUSHE ==FALSE)
		  	B_BUTTON_PUSHE = TRUE;
		  else
		  	B_BUTTON_PUSHE =FALSE;
	 	}
	 if(b_led_display == TRUE)
	 	{
	 	
		LedOn(tmep_led);
	 	}
         else
                LedOff(tmep_led);
	 //else
	 //	LedOff(tmep_led);*/
	 u32_led_counter=rand();
}
void viclie(void)//back and forth the led light
	{
	static u8 u8_counter = 0;//increase the number
	 const  u16 u16_const = 1000;//const for second
	 static u16 u16_constant_for =0;
	 static BOOL B_turn_right_left = FALSE;
	 static u8 u8_counter_led_patter2 =0;
	 static u8 u8_patter         =0 ;


	 ///other partern led display.
	 if(G_u32SystemTime1ms%5000==0)
	 	{
	 	for(u8_counter=0;u8_counter<=7;u8_counter++)
	 	{
	 	    LedOff(u8_counter);
	 	}
	 	  u8_patter = ledpart_one;
		  u8_counter = 0;
		  u16_constant_for =0;
	 	}
	 else if(G_u32SystemTime1ms%10001==0)
	 	{
	 	  for(u8_counter=0;u8_counter<=7;u8_counter++)
	 	{
	 	    LedOff(u8_counter);
	 	}
	 	   u8_patter = ledpart_two;
		   u8_counter = 0;
		  u16_constant_for =0;
	 	}
	 else if (G_u32SystemTime1ms%15001 ==0)//容易出错的地方
	 	{
	 	for(u8_counter=0;u8_counter<=7;u8_counter++)
	 	{
	 	    LedOff(u8_counter);
	 	}
	 	u8_patter    = ledpart_three;
		u8_counter = 0;
		  u16_constant_for =0;
	 	}

	 ///led patter
	 switch (u8_patter)
	 	{
	 	case ledpart_three:///fade the led 
			if(G_u32SystemTime1ms%200==0)
				{for(u8_counter=0;u8_counter<=7;u8_counter++)
					{
					LedPWM(u8_counter,u16_constant_for);
					
					}
			      u16_constant_for++;
				  if(u16_constant_for==20)
				  	u16_constant_for=0;
				}
			break;
	 	case ledpart_one:
			 loop_pattern_one:	 if(u16_constant_for<=u16_const/(u8_counter*6+1))//loop:
								 	{
								 	 //if(B_turn_right_left==FALSE)
								 	  LedOn(4+u8_counter);//forth
									// else
									  LedOn(3-u8_counter);//back
									  //u8
									  u16_constant_for++;
							                  //u8_counter++;
								 	}
						 else
						 	{
								//if(B_turn_right_left == FALSE)
									
							 	LedOff(4+u8_counter);
								//else
									LedOff(3-u8_counter);
							 	u16_constant_for = 0;
								if(u8_counter==3)
						                {
						            if(B_turn_right_left==FALSE)
										B_turn_right_left = TRUE;
									else
										B_turn_right_left=FALSE;
									u8_counter   =0;
									goto loop_pattern_one;

									//break;
						                }
			                u8_counter++;
					//
				 	}
		 break;
		 case ledpart_two:
	 
			  loop_pattern_two:	 if(u16_constant_for<=u16_const/(u8_counter*6+1))//loop:
				 	{
				 	 if(B_turn_right_left==FALSE)
				 	  LedOn(u8_counter);//forth
					 else
					  LedOn(7-u8_counter);//back
					  //u8
					  u16_constant_for++;
			                  //u8_counter++;
				 	}
				 else
				 	{
				 	if(B_turn_right_left == FALSE)
						
				 	LedOff(u8_counter);
					else
						LedOff(7-u8_counter);
				 	u16_constant_for = 0;
					if(u8_counter==7)
			                {
			            if(B_turn_right_left==FALSE)
							B_turn_right_left = TRUE;
						else
							B_turn_right_left=FALSE;
						u8_counter   =0;
						goto loop_pattern_two;

						//break;
			                }
			                u8_counter++;
					//
				 	}
		 break;
	 	}
	 
	}
void test_led(void)
{   
     static bool led_on = FALSE;
	 if(WasButtonPressed(BUTTON3))
	 	{
	 	ButtonAcknowledge(BUTTON3);
		if(led_on == FALSE)
			{
			 led_on= TRUE;
			}
		else
			led_on = FALSE;
	 	}
	 if(led_on== TRUE)
	 	{LedOn(RED);}
	 else
	 	LedOff(RED);
}
void double_button_push(void)
	{
     static u8 u8_ledon_count = 0;//indect led on
     static u32 u32_old_time  = 0;//old time
     static u8 u8_button_times =0;//push button times
     static u8 double_conf     =0;//
     static BOOL B_PUSH        =FALSE;
     if(WasButtonPressed(BUTTON1))//open double state
     	{
     	 ButtonAcknowledge(BUTTON1);
		 
		  if(B_PUSH==FALSE)
		  	{
                          for(u8 u8_temp=0;u8_temp<=7;u8_temp++)
                            {
                               LedOff(u8_temp);
                            }
                          B_PUSH=TRUE;
		  	}
		  else
		  	B_PUSH= FALSE;
		  
     	}
     if(WasButtonPressed(BUTTON0))//button0 implement double
          {
             ButtonAcknowledge(BUTTON0);
             for(u8 u8_temp=0;u8_temp<=7;u8_temp++)
                  //{
                     LedOff(u8_temp);
             
            if(u8_button_times==1)
                  {
                     if((G_u32SystemTime1ms-u32_old_time)>=500)//
                     double_conf=0;//double false
                     else
                          double_conf=1;//yes
                     u8_button_times=0;
                     
                  }
             else
                  {
                    u32_old_time= G_u32SystemTime1ms;
                    u8_button_times=1;
		   double_conf=0;
                  }
                  
          //}
          }
     if((G_u32SystemTime1ms-u32_old_time)>=700)//按下后一段时间就单键恢复
        u8_button_times=0;
       
    if(B_PUSH==TRUE)
    	{
	   if(double_conf==0)
	   	{

	   	  if(G_u32SystemTime1ms%500==0)
	   	  	{
	   	  	 LedOn(u8_ledon_count);
			
			 if(u8_ledon_count>=7)
			 	{
			 	 for(u8 u8_temp=0;u8_temp<=7;u8_temp++)
				   	{
				   	   LedOff(u8_temp);
				   	}
			 	u8_ledon_count=0;
			 	}
			  u8_ledon_count++;
	   	  	}
	   	}
	   else
	   	{
	   	  if(G_u32SystemTime1ms%500==0)
	   	  	{
	   	  	   LedOn(7-u8_ledon_count);
			  
			   if(u8_ledon_count>=7)
			 	{
			 	 for(u8 u8_temp=0;u8_temp<=7;u8_temp++)
				   	{
				   	   LedOff(u8_temp);
				   	}
			 	u8_ledon_count=0;
			 	}
			    u8_ledon_count++;
	   	  	}
	   	}
    	  }
	}
        //}
void password_input_button(void)
	{
	  
	  static u8 u8_password_save[10]={0};//save password
	  static u8 u8_password_input[10]={0};
	  static u8 u8_mode          =0;
	  static u8 u8_counter_password = 0;
	  static u32 u32_double_button_old=0;
	  static u8 u8_99=0;
	  static u8 u8_temp  =0;
	  static BOOL B_right_password =FALSE;
	  //PWMAudioOff(BUZZER1);
	  PWMAudioSetFrequency(BUZZER1,500);//open buzzle
	  if(WasButtonPressed(BUTTON3))
	  	{
	  	ButtonAcknowledge(BUTTON3);
	  	//if(IsButtonPressed(BUTTON0))
	  		//{
	  		switch(u8_mode)
	  			{
	  			  case 0://开始设置密码
				  	u8_mode = input_password_statue;
					break;
				  case 5://输入密码
				  	u8_mode = 9;//输入密码模式
                    break;
				  case 9:
				  	u8_mode = 11;//确认密码；
				  	u32_double_button_old= G_u32SystemTime1ms;//记录当时按下按钮
					break;
				  /*case 11:
				  	if((G_u32SystemTime1ms-u32_double_button_old)<=100)
						u8_mode = 13;
					else
						u8_mode = 9;//input password mode
				    break;
				  case 13:
				  	u8_mode =5;//back to setting password
				  	break;
				  	*/
				  case 22:
				  	LedOff(WHITE);
				    LedOff(BLUE);
				    LedOff(RED);
					PWMAudioOff(BUZZER1);
				  	B_right_password =FALSE;
				  	u8_mode = 9;//back to input password mode
				  	break;
				  
	  			}
	  	    //u8_mode=5;//setting password mode 
	  	    //PWMAudioOn(BUZZER1);
		  		//}
  	    //else 
    	  //	{
    	  //	 u8_mode =9;//input password mode
  		// PWMAudioOff(BUZZER1);
    	 // 	}
		
		  	
	  	}
       switch(u8_mode)
       	{
       	    case input_password_statue://setting password
				//for(u8_temp=0;u8_temp<=3;u8_temp++)
				LedOn(BLUE);
                                LedOff(RED);
                                LedOff(WHITE);
				if(WasButtonPressed(BUTTON1))
					{
					  u8_password_save[u8_temp] = 1;
					   ButtonAcknowledge(BUTTON1);
					   u8_temp++;
					}
				if(WasButtonPressed(BUTTON0))
					{
					  u8_password_save[u8_temp] = 0;
					   ButtonAcknowledge(BUTTON0);
					   u8_temp++;
					}
				if(WasButtonPressed(BUTTON2))
					{
					  u8_password_save[u8_temp] = 2;
					   ButtonAcknowledge(BUTTON2);
					   u8_temp++;
					}
				if((u8_temp>=10)||(WasButtonPressed(BUTTON3)))
					{
					  ButtonAcknowledge(BUTTON3);//end password
					  u8_mode = 9;
					  u8_temp = 0;
					  	
					}
				
				break;
			case 9:
				LedOn(RED);
				LedOff(BLUE);
				LedOff(WHITE);
					
				if(WasButtonPressed(BUTTON1))
					{
					  u8_password_input[u8_temp] = 1;
					   ButtonAcknowledge(BUTTON1);
					   u8_temp++;
					}
				if(WasButtonPressed(BUTTON0))
					{
					  u8_password_input[u8_temp] = 0;
					   ButtonAcknowledge(BUTTON0);
					   u8_temp++;
					}
				if(WasButtonPressed(BUTTON2))
					{
					  u8_password_input[u8_temp] = 2;
					   ButtonAcknowledge(BUTTON2);
					   u8_temp++;
					}
				if((u8_temp>=10))
					{
					 // ButtonAcknowledge(BUTTON3);
					  u8_mode = 11;
					  u8_temp = 0;
					  	
					}
				break;
			case 11:
				LedOn(WHITE);
				LedOff(BLUE);
				LedOff(RED);
				for(u8_temp=0;u8_temp<=9;u8_temp++)
					{
					if(u8_password_input[u8_temp]==u8_password_save[u8_temp])
						B_right_password=TRUE;
					else

					{B_right_password=FALSE;
					break;
						}
					
					}
				u8_mode= 22;//check the button mode
				break;
			 case 22:
			 	LedOn(WHITE);
				LedOn(BLUE);
				LedOn(RED);
			 	if(B_right_password ==TRUE)
			 		{
			 		if(G_u32SystemTime1ms%1000==0)
			 			{
			 			LedOn(LCD_GREEN);
			 			}
					else if(G_u32SystemTime1ms%2001==0)
						{
						LedOff(LCD_GREEN);
						}
			 		}
				else
					{
					  if(G_u32SystemTime1ms%1000==0)
					  	{
					  	PWMAudioOff(BUZZER1);
					  	}
					  else if(G_u32SystemTime1ms%2002==0)
					  	{
					  	PWMAudioOn(BUZZER1);
					  	}
					}
			 	break;
       	}
	 /* if(WasButtonPressed(BUTTON1))
	  	{
	  	  ButtonAcknowledge(BUTTON1);
		  	if(IsButtonPressed(BUTTON0))
		  		{
		  	    u8_mode=5;//setting password mode 
		  	    PWMAudioOn(BUZZER1);
			  		}
	  	    else 
	    	  	{
	    	  	 u8_mode =9;//input password mode
	  		 PWMAudioOff(BUZZER1);
	    	  	}
			
	  	}
	  */
	  //while
	/*  if((u8_mode == 5))///why cannot do this 
	  	{
	  	 if(G_u32SystemTime1ms%1000==0)
	  	 	{
		 	LedOn(LCD_RED);
	  	 	}
		 else if(G_u32SystemTime1ms%500==0)
		 	{
		 	LedOff(LCD_RED);
		 	}
		 	
	  	    PWMAudioOff(BUZZER1);
	  	    if(WasButtonPressed(BUTTON0))
	  	    	{
	  	    	LedOn(RED);
	  	    	u8_password_save[u8_counter_password] = 0;
				ButtonAcknowledge(BUTTON0);
				u8_counter_password++;
				LedOff(RED);
	  	    	}
			if(WasButtonPressed(BUTTON1))
				{
				u8_password_save[u8_counter_password] = 1;
				ButtonAcknowledge(BUTTON1);
				u8_counter_password++;
				}
			if(WasButtonPressed(BUTTON2))
				{
				u8_password_save[u8_counter_password] = 2;
				ButtonAcknowledge(BUTTON2);
				u8_counter_password++;
				}
			if(WasButtonPressed(BUTTON3))
				{
				  u8_mode = 9;
				  ButtonAcknowledge(BUTTON3);
				}
			if(u8_counter_password>=11)
				{
				u8_mode= 9;
				LedOn(RED);
				
				u8_counter_password = 0;
				//break;
				}
			
	  	}
	  if(u8_mode==9)
	  	{
	  	   // LedOn(LCD_GREEN);
	  	}*/
	}
void password_button(void)
	{  
	     static u8 u8_password[4]={0,2,3,1};
		 static u8 u8_input_button[4]={0};
		 static  u8 u8_counter_buttton_press=0;
		 static  BOOL B_Pass_No[3]= FALSE;
		 u8 u8_temp_number     =0;
		 if(u8_counter_buttton_press<=3)//you can input the password
			 	{
			 	B_Pass_No[0] = FALSE;//initation the logic parameter
			 	
			 if(WasButtonPressed(BUTTON0))
			 	{
			 	  u8_input_button[u8_counter_buttton_press]=0;
				  LedOn(WHITE);
			 	  
			 	  ButtonAcknowledge(BUTTON0);
				  u8_counter_buttton_press++;
				  LedOff(WHITE);
			 	}

			 if(WasButtonPressed(BUTTON1))
			 	{
			 	 u8_input_button[u8_counter_buttton_press]=1;
				 ButtonAcknowledge(BUTTON1);
				 u8_counter_buttton_press++;
			 	}
			 if(WasButtonPressed(BUTTON2))
			 	{
			 	u8_input_button[u8_counter_buttton_press]=2;
				ButtonAcknowledge(BUTTON2);
				u8_counter_buttton_press++;
			 	}
			 if(WasButtonPressed(BUTTON3))
			 	{
			 	  u8_input_button[u8_counter_buttton_press]=3;
				  	ButtonAcknowledge(BUTTON3);
				  u8_counter_buttton_press++;
			 	}
		 	}
		 if(u8_counter_buttton_press==4)//stop input password
		 	LedOn(RED);
		// for(u8_temp_number=0;u8_temp_number<=3;u8_temp_number++)
		 	//{
		 	do{
		 	  if(u8_password[u8_temp_number]==u8_input_button[u8_temp_number])
			  	{u8_temp_number++;
			     B_Pass_No[0]= TRUE;
		 	  	}
			  else
			  	{
			  	  B_Pass_No[0]=FALSE;
				  break;
			  	}
			  	
		      } 	
			 while(u8_temp_number<=3);//}
	   if(B_Pass_No[0]==TRUE)
	   	{
	   	    if(G_u32SystemTime1ms%1000==0)
				LedToggle(BLUE);
			u8_counter_buttton_press=0;// start new input 
	   	}
		 
	}
//
void Eie_classmate_work()
{

   static  u32 u32counter=0;
        u32 u32randvalue;
        u8  u8value=0;
        u8  u8counter=0;
         u32counter++;
         if(u32counter<500){
            return; 
         }
         u32counter=0;
         u32randvalue=rand();
         u8value=0;
         for(u8counter=0;u8counter<4;u8counter++){
           
             u8value+=(u32randvalue&0x000000ff);
             u32randvalue>>=8;
           
         }
         u8value&=0x0f;
         if(u8value>7){
            u8value-=8; 
         }
         for(u8counter=0;u8counter<8;u8counter++)
         {
           LedOff(u8counter);
          }
   
}
void button_pressed(void)
{ 
  static bool B_ispressed[3] = FALSE;
 if(  IsButtonPressed(BUTTON0)==TRUE)
 	{
 	  if(B_ispressed[0]==FALSE)
 	  	{
 	  	   LedOn(RED);
 	  	  B_ispressed[0] =TRUE;
 	  	}
	  else
	  	{
	  	B_ispressed[0]=FALSE;
		LedOff(RED);
	  	}
	  
 	   //LedOn(RED);
 	}

 if(WasButtonPressed(BUTTON1))
 	{
 	    if(B_ispressed[1]==FALSE)
 	    	{
 	    	B_ispressed[1]= TRUE;
			LedOn(BLUE);
 	    	}
		else
			{
			B_ispressed[1]=FALSE;
			LedOff(BLUE);
			}
		ButtonAcknowledge(BUTTON1);
 	}
    
}
//pwm toggle test
void Led_API_test(void)
	{bool B_button_pressed[4]= FALSE;
	
     if(WasButtonPressed(BUTTON0))
     	{
     	  if(B_button_pressed[0]==FALSE)
		  	B_button_pressed[0]= TRUE;
		  else
		  	B_button_pressed[0] = FALSE;
     	 ButtonAcknowledge(BUTTON0);
     	}
	 if(WasButtonPressed(BUTTON1))
	 	{
	 	if(B_button_pressed[1]==FALSE)
			B_button_pressed[1]=TRUE;
		else
			B_button_pressed[1]=FALSE;
	 	 ButtonAcknowledge(BUTTON1);
		 
	 	}
	 if(B_button_pressed[0]==TRUE)
	 	{
	 	if(G_u32SystemTime1ms%1000==0)
	 	LedToggle(RED);
	 	}
	 if(B_button_pressed[1]==TRUE)
	 	{
	 	//LedPWM(LedNumberType eLED_,LedRateType ePwmRate_)
	 	}
	}

/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/
//test 2017-5-6
void BCD_code_display(void)
{
  static u16 u16_counter = 0;//this varible for counter the 1S
  static u8 a_u8_binary[8] =0;//to determine what light on
  u8 u8_temp_counter =0;//for tempoary save 
  static u8 u8_temp_counter_on=0;//for change the the decema 
  if(G_u32SystemTime1ms%1000==0)
  {
     u16_counter++;
	 if(u16_counter>=99)
	 	u16_counter=0;
  }
  ///decade 
  u8_temp_counter_on=u16_counter/10;
  for(u8_temp_counter=4;u8_temp_counter<=7;u8_temp_counter++)
  	{
     a_u8_binary[u8_temp_counter] = u8_temp_counter_on%2;
	 u8_temp_counter_on=u8_temp_counter_on/2;
  	}
  ///signal 
  u8_temp_counter_on=u16_counter%10;
  	for(u8_temp_counter=0;u8_temp_counter<=3;u8_temp_counter++)
  		{a_u8_binary[u8_temp_counter]=u8_temp_counter_on%2;
	     u8_temp_counter_on=u8_temp_counter_on/2;
  		}
	for(u8_temp_counter=0;u8_temp_counter<=7;u8_temp_counter++)
		{
		 if(a_u8_binary[u8_temp_counter]==1)
		 	LedOn(u8_temp_counter);
		 else
		 	LedOff(u8_temp_counter);
		}

	
  
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

//
void double_led(void)
{
  u8 u8_counter = 0;
  if(G_u32SystemTime1ms%500==0)
    for(u8_counter=0;u8_counter<=4;u8_counter++)
    {
      LedOn(u8_counter+2);
    }
  if(G_u32SystemTime1ms%2000==0)
  {
     for(u8_counter=0;u8_counter<=7;u8_counter++)
       LedOff(u8_counter);
  }
  if(G_u32SystemTime1ms%10000==0)
      UserApp1_StateMachine = all_led;
    
    
}

//all led light.
void all_led(void)
{u8 u8_counter=0;
    if(G_u32SystemTime1ms%1000==0)
    {
     for(u8_counter=0;u8_counter<=7;u8_counter++)
     {
       LedOn(u8_counter);
      //LedOn(RED);
     }
    }
    if(G_u32SystemTime1ms%2000==0)
    {
      for(u8_counter=0;u8_counter<=7;u8_counter++)
      {
        LedOff(u8_counter);
      }
    }
    if(G_u32SystemTime1ms%10000==0)//10
      UserApp1_StateMachine = double_led;
   
    
      
}
///
/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
static u8 u8_pwm_red = 0;
 if(G_u32SystemTime1ms%1000==0)//blink purple
 	{
 	LedToggle(PURPLE);
	u8_pwm_red++;
	if(u8_pwm_red>=20)
		u8_pwm_red=0;

	LedPWM(RED,u8_pwm_red);
 	}
 
 
} /* end UserApp1SM_Idle() */
    
#if 0
/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserApp1SM_FailedInit(void)          
{
    
} /* end UserApp1SM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
