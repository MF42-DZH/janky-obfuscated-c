#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#include <windows.h>
void delay( unsigned long ms ) {
    Sleep(ms);
}
#else
#define __USE_MISC
#include <unistd.h>
void delay( unsigned long ms ) {
    unsigned int s  = ms / 1000ul;
    unsigned long ns = ( ms % 1000ul ) * 1000ul;
    sleep( s ); usleep( ns );
}
#endif

#define QUOTES (64)
typedef struct {
    int x;
    int y;
    int s;
} Quote;

#define JANK(x) (CHARS[x])
#define SQR(x) ((x) * (x))

const char CHARS[] = { ' ', '.', ':', '=', '#' };

#define STRAMT (10)
const char LENGTHS[] = "\x19\x08\x06\x0c\x1e\x41\x0d\x0b\x2e\x19";
const char* STRINGS[] = {
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

double lerp( double v0, double v1, double t ) {
    return (1 - t) * v0 + t * v1;
}

int isJank( double x, double y, double interval ) {
    double cx = x * interval;
    double cy = y * interval;
    int total = 0;

    // '=' if in body
    if ( SQR(cx) + SQR(cy) <= 5.0) {
        total = 2;
    }
    
    // '=' if in arm / hand
    double acx = (cx - 2) / 8;
    // Arm
    if ( cx >= -0 && cx <= 3.25 && cy <= SQR(acx) + 0.3 && cy >= SQR(acx) - 0.6 ) {
        total = 3;
        return total;
    }
    // Hand
    if ( SQR( (cx - 3) / 0.25 ) + SQR( (cy - 0.5) / 0.4 ) <= 1 ) {
        total = 3; 
        return total;
    }
    if ( SQR( (cx - 3) / 2 ) + SQR( cy + 0.5 ) <= 0.08 ) {
        total = 3; 
        return total;
    }
    if ( ( SQR(cx - 3.25) + SQR(cy - 0.1) <= 0.08 ) || ( SQR(cx - 3.325) + SQR(cy + 0.2) <= 0.08 ) ) { 
        total = 3;
        return total;
    }

    // '.' if in mouth / eyes
    // Mouth
    if ( ( cy <= -0.05 * cx - 0.6 ) && ( SQR(cx - 0.1) + SQR(cy + 0.3) <= 2.25 ) ) {
        total = 1;
        // Tongue
        double lcx = (cx + 0.5) / 1.25;
        if ( cy <= -1 * SQR(lcx) - 1 ) total = 2;

        // Teeth
        if ( ( cy >= -0.05 * cx - 0.8 ) || (cy <= -0.05 * cx - 1.55 ) ) total = 4;

        return total;
    }

    // Eyes
    if ( ( SQR(cx - 1) + SQR(cy - 0.9) <= 0.2 ) || ( SQR(cx + 0.4) + SQR(cy - 1) <= 0.2 ) ) {
        total = 1;
        if ( ( SQR(cx - 1.2) + SQR(cy - 0.75) <= 0.01 ) || ( SQR(cx + 0.25) + SQR(cy - 0.85) <= 0.01 ) ) total = 4;

        return total;
    }

    // '#' if in pupils
    // '=' if in tongue
    // '#' if in teeth

    return total;
}

int main( void ) {
    #if 0
    for ( int y = 30; y >= -30; --y ) {
        for ( int x = -40; x <= 40; ++x ) {
            printf( "%c", JANK( isJank( x, y, 0.1 ) ) );
        }
        printf( "\n" );
    }
    #endif

    srand( time( NULL ) );
    int counter = 0;
    double value = 0;

    Quote quotes[ QUOTES ];
    for ( int i = 0; i < QUOTES; ++i ) {
        quotes[ i ].y = rand() % 60;
        quotes[ i ].s = rand() % STRAMT;
        quotes[ i ].x = ( -1 * (rand() % 120) ) - *(LENGTHS + quotes[ i ].s);
    }

    initscr();
    cbreak();
    noecho();

    while ( counter < 140 ) {
        if ( counter < 60 ) value = lerp( 1, 0.09, (double) counter / 60 );
        else if ( counter >= 80 ) value = lerp( 0.09, 0.15, (double) (counter - 80) / 60 );
        else value = 0.09;

        for ( int y = 30; y >= -30; --y ) {
            for ( int x = -40; x <= 60; ++x ) {
                mvaddch( -y + 30, 2 * x + 50, JANK( isJank( (x - 1.5), y, value ) ) );
                mvaddch( -y + 30, 2 * x + 51, JANK( isJank( (x - 1.5), y, value ) ) );
            }
        }
        refresh();

        ++counter;
        delay( 50 );
    }

    int xs[ 1200 ] = { 0 };
    int ys[ 1200 ] = { 0 };
    for ( int i = 0; i < 1200; ++i ) {
        xs[ i ] = rand() % 160;
        ys[ i ] = rand() % 60;
    }

    while ( 1 ) {
        // DOTS
        for ( int i = 0; i < 1200; ++i ) {
            mvaddch( ys[i], xs[i], '.' );
        }

        // QUOTES
        for ( int i = 0; i < QUOTES; ++i ) {
            unsigned int len = *(LENGTHS + quotes[ i ].s);
            char* str = calloc( len + 1, sizeof( char ) );
            for ( unsigned int l = 0; l < len; ++l ) {
                char cur[ 4 ] = { '\0' };
                memcpy(cur, STRINGS[quotes[i].s] + l * 3, 3);
                str[l] = atoi(cur);
            }

            mvaddch( quotes[i].y, quotes[i].x - 1, ' ' );
            for ( unsigned int c = 0; c < strlen( str ); ++c ) if (quotes[i].x + c < 159) mvaddch( quotes[i].y, quotes[i].x + c, str[ c ] );

            if ( rand() % 4 ) quotes[i].x += 1;
            if ( quotes[i].x >= 160 ) {
                quotes[ i ].y = rand() % 60;
                quotes[ i ].s = rand() % STRAMT;
                quotes[ i ].x = ( -1 * (rand() % 15) ) - *(LENGTHS + quotes[ i ].s);
            }

            free( str );
        }

        // JANKMAN
        for ( int y = 30; y >= -30; --y ) {
            for ( int x = -40; x <= 60; ++x ) {
                char t = JANK( isJank( (x - 1.5), y, 0.15 ) );
                if ( t != ' ' ) {
                    mvaddch( -y + 30, 2 * x + 50, t );
                    mvaddch( -y + 30, 2 * x + 51, t );
                }
            }
        }

        refresh();
        delay( 100 );
    }

    endwin();
    return 0;
}
