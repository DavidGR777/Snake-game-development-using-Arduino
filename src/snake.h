#ifndef SNAKE_H
#define SNAKE_H

#define C4   262
#define CS4  277
#define D4   294
#define DS4  311
#define E4   330
#define F4   349
#define FS4  370
#define G4   392
#define GS4  415
#define AL4   440
#define AS4  466
#define B4   494

#define C5   523
#define CS5  554
#define D5   587
#define DS5  622
#define E5   659
#define F5   698
#define FS5  740
#define G5   784
#define GS5  831
#define AL5   880
#define AS5  932
#define B5   988

#define C6  1047
#define CS6 1109
#define D6  1175
#define DS6 1245
#define E6  1319
#define F6  1397
#define FS6 1480
#define G6  1568
#define GS6 1661
#define A6  1760
#define AS6 1865
#define B6  1976

#define C7  2093
#define CS7 2217
#define D7  2349
#define DS7 2489
#define E7  2637
#define F7  2794
#define FS7 2960
#define G7  3136
#define GS7 3322
#define A7  3520
#define AS7 3729
#define B7  3951

#define C8  4186
#define CS8 4435
#define D8  4699
#define DS8 4978
#define E8  5274
#define F8  5588
#define FS8 5920
#define G8  6272
#define GS8 6645
#define A8  7040
#define AS8 7459
#define B8  7902

//Silencio
#define QT     0

/*--------------------------------Estructura tono--------------------------*/

typedef struct {
    unsigned int  tone;   /* Tone [cycles per second: cps] */
    unsigned long length; /* Time for reproducing tone [milliseconds] */
} TONE_T;

/*-------------------------------Ambientaciones----------------------------*/
TONE_T Crash[] = {
    {F6, 200}, {E6, 200}, {DS6, 200}, {D6, 600}
};

TONE_T Bite[] = {
    {E4,  50}, {G4, 50}, {C5, 50}
};

TONE_T Song1[] = {
    { A6, 200 },  { A6, 200 },  { A6, 200 },  { A6, 200 },
    { A6, 200 },  { GS6,450 },  { E6, 200 },  { E6, 200 },
    { E6, 200 },  { B6, 200 },  { C7, 200 },  { B6, 200 },
    { A6, 200 },  { B6, 200 },  { A6, 200 },  { E6, 200 },
    { E6, 200 },  { E6, 200 },  { E6, 200 },  { E6, 200 },
    { D6, 450 },  { D6, 200 },  { D6, 200 },  { C6, 200 },
    { D6, 200 },  { E6, 200 },  { D6, 200 },  { C6, 200 },
    { D6, 200 },  { C6, 200 },
    
    { A6, 200 },  { A6, 200 },  { A6, 200 },  { A6, 200 },
    { A6, 200 },  { GS6,450 },  { E6, 200 },  { E6, 200 },
    { E6, 200 },  { B6, 200 },  { C7, 200 },  { B6, 200 },
    { A6, 200 },  { B6, 200 },  { A6, 200 },  { E6, 200 },
    { E6, 200 },  { E6, 200 },  { E6, 200 },  { E6, 200 },
    { D6, 450 },  { D6, 200 },  { D6, 200 },  { C6, 200 },
    { D6, 200 },  { E6, 200 },  { D6, 200 },  { C6, 200 },
    { D6, 200 },  { C6, 800 },  { C6, 200 },  { E6, 200 },
    { D6, 500 },  { D6, 200 },  { D6, 200 },  { C6, 200 },
    { D6, 200 },  { E6, 200 },  { D6, 200 },  { C6, 200 },
    { D6, 200 },  { C6, 200 }
};

TONE_T Song2[] = {
    { E7, 80 },  { E7, 80 },  { QT, 80 },  { E7, 80 },
    { QT, 80 },  { C7, 80 },  { E7, 80 },  { QT, 80 },
    { G7, 80 },  { QT, 80 },  { QT, 80 },  { QT, 80 },
    { G6, 80 },  { QT, 80 },  { QT, 80 },  { QT, 80 },
    
    { C7, 80 },  { QT, 80 },  { QT, 80 },  { G6, 80 },
    { QT, 80 },  { QT, 80 },  { E6, 80 },  { QT, 80 },
    { QT, 80 },  { A6, 80 },  { QT, 80 },  { B6, 80 },
    { QT, 80 },  { AS6, 80 }, { A6, 80 },  { QT, 80 },
    
    { G6, 110 }, { E7, 110 }, { G7, 110 },
    { A7, 80 },  { QT, 80 },  { F7, 80 },  { G7, 80 },
    { QT, 80 },  { E7, 80 },  { QT, 80 },  { C7, 80 },
    { D7, 80 },  { B6, 80 },  { QT, 80 },  { QT, 80 },
    
    { C7, 80 },  { QT, 80 },  { QT, 80 },  { G6, 80 },
    { QT, 80 },  { QT, 80 },  { E6, 80 },  { QT, 80 },
    { QT, 80 },  { A6, 80 },  { QT, 80 },  { B6, 80 },
    { QT, 80 },  { AS6, 80 }, { A6, 80 },  { QT, 80 },
    
    { G6, 110 }, { E7, 110 }, { G7, 110 },
    { A7, 80 },  { QT, 80 },  { F7, 80 },  { G7, 80 },
    { QT, 80 },  { E7, 80 },  { QT, 80 },  { C7, 80 },
    { D7, 80 },  { B6, 80 },  { QT, 80 },  { QT, 80 }
};

#define NONE 0
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4 
#define screenHeight 60
#define screenWidth 140
#define MAX_HISTORY_SIZE 20
#define PLAYERS 2

typedef struct {
  int 
    new_dir,
    current_dir,
    posx,
    posy,
    looser,
    history_size;
    int history[MAX_HISTORY_SIZE][2]; 
} SNAKE_T;



#endif