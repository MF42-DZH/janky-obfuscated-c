#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int NUMERICAL_JANK; typedef unsigned int UNSIGNED_JANK; typedef double DOUBLY_FLOAT_JANK;

#define QS (64)
typedef struct { NUMERICAL_JANK x; NUMERICAL_JANK y; NUMERICAL_JANK s; } Quote;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#include <windows.h>
void dl( unsigned long ms ) { Sleep(ms); }
#else
#define __USE_MISC
#include <unistd.h>
void dl( unsigned long ms ) { UNSIGNED_JANK s = ms / 1000ul; unsigned long ns = ( ms % 1000ul ) * 1000ul; sleep( s ); usleep( ns ); }
#endif

#define JANKITUP(x) (CS[x])
#define S(x) ((x) * (x))
#define I(x) (x * iv)

const char CS[] = { ' ', '.', ':', '=', '#' };

#define STRAMT (10)
const char LS[] = "\x19\x08\x06\x0c\x1e\x41\x0d\x0b\x2e\x19"; const char* SS[] = {
    "072097032104097032104097032104097044032104097032104097032104097032104097033",
    "065068086065078067069068",
    "074097110107121033",
    "073039109032074097110107109097110033",
    "073032078069069068032084079032084065076075032065066079085084032084072069032074065078075033",
    "084104101032116105099107098111120032101110097098108101115032116104101032115119105116099104032097110100032116104101032115119105116099104032101110097098108101115032116104101032098117116116111110033",
    "087072069069069069069069069069069069033",
    "074097110107032105116032117112033",
    "089111117032100105100110039116032099104101099107032116104101032116105099107098111120032111110032121111117114032066108117045084097099107033",
    "099032111032110032099032101032114032116032032032112032105032116032099032104"
};

DOUBLY_FLOAT_JANK lerp( DOUBLY_FLOAT_JANK v0, DOUBLY_FLOAT_JANK v1, DOUBLY_FLOAT_JANK t ) { return (1 - t) * v0 + t * v1; }
NUMERICAL_JANK isJank( DOUBLY_FLOAT_JANK x, DOUBLY_FLOAT_JANK y, DOUBLY_FLOAT_JANK

                       iv ) { NUMERICAL_JANK t = 0; if ( S(I(x)) + S(I(y)) <= 5.0)
              t = 2; DOUBLY_FLOAT_JANK acx = (I(x) - 2) / 8; if ( I(x) >= -0 && I(x) <= 3.25
         && I(y) <= S(acx) + 0.3 &&I(y) >=S(acx) -0.6 ){ t = 3; return t; } if(S((I(x) - 3) / 0.25 )
       + S( (I(y) - 0.5) / 0.4 ) <= 1 ) { t = 3; return t; }if (S((I(x)- 3)/ 2)+S(I(y)+ 0.5 )<= 0.08 ) { t = 3; 
     return t; } if ( ( S(I(x) - 3.25) + S(I(y) - 0.1) <= 0.08 ) || ( S(I(x) - 3.325) + S(I(y) +0.2)<= 0.08 )){t= 3;
    return t; } if ( ( I(y) <=           -0.05 * I(x) - 0.6 ) && ( S(I(x)            - 0.1)+S(I(y) + 0.3) <= 2.25)){
    t = 1; DOUBLY_FLOAT_JANK               lcx = (I(x) + 0.5) / 1.25; if              ( I(y) <= -1 * S(lcx) - 1 )t= 2;
    if ( ( I(y) >= -0.05 *                 I(x) - 0.8 ) || (I(y)<= -0.05               * I(x) - 1.55 ) ) t = 4; return t;
    } if ( ( S(I(x) - 1) +          S(I(y) - 0.9) <= 0.2 ) || ( S(I(x) +          0.4) + S(I(y) - 1) <= 0.2 ) )  { t = 1;
    if ( ( S(I(x) - 1.2) +          S(I(y) - 0.75) <= 0.01 ) || ( S(I(x)         + 0.25) + S(I(y) - 0.85)    <= 0.01 ) )                                                 t = 4;
    return t; } return t; }         NUMERICAL_JANK main( void ) { srand(         time( NULL ) );          NUMERICAL_JANK                                                 ctr = 0;
    DOUBLY_FLOAT_JANK vle = 0;   Quote   qsl[ QS ]; for ( NUMERICAL_JANK   i = 0; i < QS; ++i ) { qsl[ i ].y = rand() % 60;            qsl[ i ].s = rand() % STRAMT; qsl[ i ].x =
    ( -1 * (rand() % 120) ) - *(LS + qsl[ i ].s); } initscr(); cbreak(); noecho(); while ( ctr < 140 ) { if   ( ctr < 60 ) vle         = lerp( 1, 0.09,   (DOUBLY_FLOAT_JANK) ctr
    / 60 ); else if ( ctr >= 80 ) vle = lerp( 0.09, 0.15, (DOUBLY_FLOAT_JANK) (ctr - 80) / 60 );else vle = 0.09; for ( NUMERICAL_JANK y= 30; y >= -30; --y ) { for ( NUMERICAL_JANK
    x = -40; x <= 60; ++x ) { mvaddch( -y + 30, 2 * x + 50, JANKITUP( isJank( (x - 1.5), y, vle ) ) ); mvaddch( -y + 30, 2 * x + 51, JANKITUP( isJank( (x - 1.5), y, vle ) ) ); }
    } refresh(); ++ctr; dl( 50 ); } NUMERICAL_JANK xs[ 1200 ] = { 0 }; NUMERICAL_JANK ys[ 1200 ] = { 0 };for ( NUMERICAL_JANK i = 0; i < 1200; ++i ) { xs[ i ] = rand() % 160;
    ys[ i ] = rand() % 60; } while ( 1 ) { for ( NUMERICAL_JANK i = 0; i < 1200; ++i ) { mvaddch( ys[i], xs[i], '.' ); }for ( NUMERICAL_JANK i = 0; i < QS; ++i ) {
    UNSIGNED_JANK len = *(LS + qsl[ i ].s); char* s = calloc( len + 1, sizeof( char ) ); for ( UNSIGNED_JANK l = 0; l < len; ++l ) { char cur[ 4 ] = { '\0' };
    memcpy(cur, SS[qsl[i].s] + l * 3, 3); s[l] = atoi(cur); } mvaddch( qsl[i].y, qsl[i].x - 1, ' ' ); for ( UNSIGNED_JANK c = 0;
    c < strlen( s ); ++c ) if (qsl[i].x + c < 159) mvaddch( qsl[i].y, qsl[i].x + c, s[ c ] ); if ( rand() % 4 )
    qsl[i].x += 1; if ( qsl[i].x >= 160 ) { qsl[ i ].y = rand() % 60; qsl[ i ].s = rand() % STRAMT;qsl[ i ].x = ( -1 *
     (rand() % 15) )                                                                              - *(LS + qsl[ i ].s);
      } free( s ); }                                                                          for ( NUMERICAL_JANK
        y = 30; y >=                                                                                 -30; --y ) {
           for ( NUMERICAL_JANK                                                     x = -40; x <= 60; ++x ) {
                char t =              JANKITUP( isJank( (x - 1.5),                     y, 0.15 ) );
                      if ( t !=   ' ' ) { mvaddch( -y + 30, 2 * x +                     50, t );
                          mvaddch( -y + 30, 2 * x + 51, t ); } } } refresh(); dl( 100 ); 
                                          } endwin(); return 0; }

//                                       Oh no, codebase's busted!
//                                      It's gone and janked itself!
