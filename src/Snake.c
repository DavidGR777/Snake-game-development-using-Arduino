/************************* Headers in Current File ***************************/
#include <time.h> // Due to rand()
#include <U8glib.h> // Due to the display
#include "snake.h" // Due to the macros for the songs and the game

/********************** Global Variables in Current File *********************/

/* For the melodies */
int melody_pin = 3;

/* Melody 01: */
double melody_pause1 = 0.4;
unsigned int melody_size1 = sizeof(Song1) /sizeof(TONE_T); 

/* Melody 02: */
double melody_pause2 = 1.3;
unsigned int melody_size2 = sizeof(Song2) /sizeof(TONE_T); 

unsigned int crash_size = sizeof(Crash) /sizeof(TONE_T); 
unsigned int bite_size = sizeof(Bite) /sizeof(TONE_T); 

/* For the snake */

int x_data[2];
int y_data[2];
int fruit;
int fruit_pos_x, fruit_pos_y;
int delaytime;
int musica;
int cont;
int change;
int end_game;

unsigned long previous_time = 0;
unsigned long waiting_time = 0;

SNAKE_T Snake[PLAYERS]; 

/********************** Display Special Configuration *************************/

U8GLIB_SH1106_128X64 u8g(10, 9, 12, 11, 13);
U8GLIB_SH1106_128X64 u8g2(10, 9, 12, 11, 13);

/**************** Prototype of Functions in Current File **********************/

void SetUp_Snake(SNAKE_T* , int );
void Move_Snake(SNAKE_T* , int* , int * , SNAKE_T*[] );
void there_is_fruit( int*, int*, SNAKE_T* , int* , int* );

void Read_Joystick (int , int , SNAKE_T* );
void cancion(TONE_T* , unsigned int , double , int , int* );
void sound_efect(int* , int*, int* );
void u8g_prepare(void);
void u8g2_prepare(void);
void Display(SNAKE_T, SNAKE_T);

/*************************** SETUP in Current File ***************************/

void setup() {

  /* Display setup : */
  u8g_prepare();
  u8g2_prepare();

  /* Analog Pins setup: */
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(melody_pin,OUTPUT);

  /* Snakes setup: */
  SetUp_Snake(&Snake[0], 10);
  SetUp_Snake(&Snake[1], 20);
  SetUp_Snake(&Snake[2], 50);
  SetUp_Snake(&Snake[3], 70);

  /* Fruit setup: */
  fruit_pos_x = 1 + rand()%118;
  fruit_pos_y = 11 + rand()%48;
  srand(time(NULL));

  /* Speed setup: */
  delaytime = 50;  
  musica = 0;
  cont = 0;
  change = 0;
  end_game = 0;

  Serial.begin(9600);
  
} /* End of SetUp() */


/*************************** LOOP in Current File ***************************/

void loop() {

  if( end_game == 0 ){

    /* Read Analog Inputs */
    y_data[0] = analogRead(A4);
    x_data[0] = analogRead(A5);  

    y_data[1] = analogRead(A2);
    x_data[1] = analogRead(A3);                                                                   
    
    for(int j = 0; j < PLAYERS; j++){
      if(Snake[j].looser == 0){
        Read_Joystick(x_data[j], y_data[j], &Snake[j]);          
        Move_Snake(&Snake[j], &musica, &cont, &Snake[2]);             
        there_is_fruit( &fruit_pos_x, &fruit_pos_y, &Snake[j], &musica, &cont);
      } 
    }          

    Display(&Snake[0], &Snake[1]);

    //Musical environment
    sound_efect(&musica, &cont, &end_game);

    delay(delaytime);

  }else{
      //Set_Score(Snake->history_size); 
      cancion(Song2, melody_size2, melody_pause2, melody_pin, &cont);
      u8g2.firstPage();  
      do {
        u8g2.drawStr(9, 20, "FINAL SCORE ");
        u8g2.drawStr(9, 40, "PY 01: ");
        u8g2.drawStr(70, 40, "PY 02: ");
        for (int i = 0; i<2; i++){
          int c = 70*i;
          u8g2.drawStr(9+c, 50, String(Snake[i].score).c_str());
          
        }
        
      } while (u8g2.nextPage());
  } /* End showing scores */

} /* End of loop() */

/************************ Functions in Current File ************************/

void u8g_prepare(void) {
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
} /* End of void u8g_prepare(void) */

void u8g2_prepare(void) {
  u8g2.setFont(u8g_font_6x10);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDefaultForegroundColor();
  u8g2.setFontPosTop();
} /* End of void u8g_prepare(void) */


void Display(SNAKE_T *Snake1, SNAKE_T *Snake2){
  int k;
  u8g.firstPage();  
  do {
    for(k = 0; k < Snake1->history_size; k++){
      u8g.drawPixel(Snake1->history[k][0], Snake1->history[k][1]);
    }
    for(k = 0; k < Snake2->history_size; k++){
      u8g.drawPixel(Snake2->history[k][0], Snake2->history[k][1]);
    }

    u8g.drawPixel(fruit_pos_x, fruit_pos_y);

    for(k = 0; k < 120; k++){
      u8g.drawPixel(k, 10);
    }
    for(k = 0; k < 120; k++){
      u8g.drawPixel(k, 60);
    }
    for(k = 10; k < 60; k++){
      u8g.drawPixel(0, k);
    }
    for(k = 10; k < 60; k++){
      u8g.drawPixel(120, k);
    }
  } while( u8g.nextPage() );
} /* End of void Display(SNAKE_T*, SNAKE_T* ) */

void sound_efect(int *musica, int *cont, int *end_game){

  /* Game atmosphere */
  if( *musica == 0 ){      
      cancion(Song1, melody_size1, melody_pause1, melody_pin, cont);
  
  /* Eating effect */   
  }else if( *musica == 1){          
    if( *cont < 2 ){
      cancion(Bite, bite_size, melody_pause1, melody_pin, cont);
    }else{
      *musica = 0; 
    }

  /* Collision effect */
  }else if( *musica == 2){        
    if( *cont < 2 ){
      cancion(Crash, crash_size, melody_pause1, melody_pin, cont);
    }
  }/* End *musica == 2 */
  
} /* End of void sound_efect() */

void SetUp_Snake(SNAKE_T* Snake, int x){
  Snake->current_dir = DOWN; 
  Snake->new_dir = NONE; 
  Snake->posx = x;
  Snake->posy = 55; 
  Snake->looser = 0;
  Snake->score = 0;
  Snake->history_size = 1;
  
} /* End of SetUp_Snake */

void Read_Joystick (int x_data, int y_data, SNAKE_T* Snake){

  if ( (x_data >= 0) && (x_data < 400) ){
    Snake->new_dir = UP;
  } else if ( (x_data >= 700) && (x_data <= 1023) ){
    Snake->new_dir = DOWN;
  } else if ( (y_data >= 700) && (y_data <= 1023) ){
    Snake->new_dir = RIGHT;
  } else if ( (y_data >= 0) && (y_data < 400) ){
    Snake->new_dir = LEFT;
  } else if ((x_data > 400 && x_data < 700) && (y_data > 400) && (y_data < 700)) {
    Snake->new_dir = NONE; 
  }

  if (Snake->new_dir != NONE) {
    if ((Snake->new_dir == UP && Snake->current_dir == DOWN) ||
            (Snake->new_dir == DOWN && Snake->current_dir == UP) ||
            (Snake->new_dir == RIGHT && Snake->current_dir == LEFT) ||
            (Snake->new_dir == LEFT && Snake->current_dir == RIGHT)) {
            Snake->new_dir = NONE;
        }
  }

} /* End of Read_Joystick () */


void Move_Snake(SNAKE_T* Snake, int* musica, int *cont, SNAKE_T Snakes[2]) {
  typedef enum {MOVING, FINISHING} STATE_T; 
  static STATE_T state = MOVING;

  if (1) {
    switch(state) {
      case MOVING:
        /* Update the position based on the current direction */
        if (Snake->new_dir == NONE) {
          if (Snake->current_dir == UP) {
            Snake->posy++;
          } else if (Snake->current_dir == DOWN) {
            Snake->posy--;
          } else if (Snake->current_dir == RIGHT) {
            Snake->posx++;
          } else if (Snake->current_dir == LEFT) {
            Snake->posx--;
          }
        } else if (Snake->new_dir == UP) {
          Snake->posy++;
          Snake->current_dir = UP;
        } else if (Snake->new_dir == DOWN ) {
          Snake->posy--;
          Snake->current_dir = DOWN;
        } else if (Snake->new_dir == RIGHT) {
          Snake->posx++;
          Snake->current_dir = RIGHT;
        } else if (Snake->new_dir == LEFT) {
          Snake->posx--;
          Snake->current_dir = LEFT;
        }

        /* Checking collision with herself and other snakes */
        for (int l = 0; l < PLAYERS; l++) {
          for (int i = (l == l ? 1 : 0); i < Snakes[l].history_size; i++) {
            if (Snake->posx == Snakes[l].history[i][0] && Snake->posy == Snakes[l].history[i][1]) {
              state = FINISHING; 
              break;
            }      
          } 
        if (state == FINISHING) break;
        }

        /* Checking boundaries collision */
        if (!(Snake->posx > 0 && Snake->posx < screenWidth) || !(Snake->posy > 10 && Snake->posy < screenHeight)) {
          state = FINISHING;
        } else {

          for (int i = Snake->history_size - 1; i > 0; i--) {
            Snake->history[i][0] = Snake->history[i - 1][0];
            Snake->history[i][1] = Snake->history[i - 1][1];
          }

          /* Save the current position as the latest in history */
          Snake->history[0][0] = Snake->posx;
          Snake->history[0][1] = Snake->posy;

          state = MOVING;
        }
      break; /* End of MOVING */

      case FINISHING:
        *cont = 0;
        Snake->looser = 1;
        *musica = 2;
        //delaytime -= 10;
        end_game++;
        state = FINISHING;
      break; /* End of FINISHING */

    } /* End of switch(state) */
  } /* End of if(1) */
} /* End of Move_Snake() */


void there_is_fruit( int *fruit_pos_x, int *fruit_pos_y, SNAKE_T *Snake, int* musica, int *cont){

  static int fruit = 0;
  if( Snake->posx == *fruit_pos_x && Snake->posy == *fruit_pos_y ){
    Snake->history_size++;
    Snake->score++; 
    *musica = 1;
    *cont = 0;
    if (delaytime > 0 ){
      delaytime -=10;
    }
    fruit = 1;
  }

  if(fruit == 1){
    *fruit_pos_x = 1 + rand()%118;
    *fruit_pos_y = 20 + rand()%39;
    fruit = 0;
  }
  
} /* End of there_is_fruit */

void cancion(TONE_T *melody, unsigned int melody_size , double melody_pause, int pin, int *cont){
  typedef enum{THERE_IS_NOTE, IS_A_SILENCE, DELAY_A, DELAY_B, NOTE_COMPLETED, HIGH_TIME, LOW_TIME} SONG_T;
  static int period_high;
  static int i = 0;
  static unsigned long initial_time = 0;
  static unsigned long tone_time = 0;
  static SONG_T state = THERE_IS_NOTE;

  if(1){
    switch(state){

      case THERE_IS_NOTE:        //¿AÚN QUEDAN NOTAS?
        if( i <= melody_size ){
          state = IS_A_SILENCE;
        }else{
          *cont = *cont +1;
          i = 0;
          state = THERE_IS_NOTE;
        }
      break;
      
      case IS_A_SILENCE:       //¿ES UN SILENCIO?
        if(melody[i].tone == 0){
          initial_time = micros();
          state = DELAY_A;
        }else{
          period_high = 1000000/(melody[i].tone *2);
          tone_time = micros();
          state = NOTE_COMPLETED;
        }     
      break; 
  
      case DELAY_A:       //DELAY A 
        if(micros() - initial_time <= (melody[i].length)*1000){
          state = DELAY_A;
        }else{
          tone_time = micros();
          state = DELAY_B;
        }     
      break;
  
      case DELAY_B:       //DELAY B    
        if( micros() - initial_time <= ((melody[i].length)*melody_pause*1000)){
          state = DELAY_B;
        }else{
          i++;
          state = THERE_IS_NOTE;
        }     
      break;
  
      case NOTE_COMPLETED:     //¿Duracion completa?
        if( micros() - tone_time <= (melody[i].length)*1000){
          initial_time = micros();
          digitalWrite(pin, HIGH); 
          state = HIGH_TIME;
        }else{
          initial_time = micros();
          state = DELAY_B;
        }      
      break;
  
      case HIGH_TIME:     //Tiempo arriba        
        if(micros() - initial_time <= period_high){
          state = HIGH_TIME;
        }else{
          digitalWrite(pin, LOW);
          initial_time = micros();
          state = LOW_TIME;
        }     
      break;
  
      case LOW_TIME:     //Tiempo abajo
        if(micros() - initial_time <= period_high){
          state = LOW_TIME;
        }else{
          state = NOTE_COMPLETED;
        }   
      break;
      
    } /* End switch(case) */
  } /* End if(TRUE) */
} /* End cancion */
