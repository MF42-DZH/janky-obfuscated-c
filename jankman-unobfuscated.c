#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#include <windows.h>
void delay( unsigned long ms ) {
    Sleep(ms);
}
#else
#define _BSD_SOURCE
#include <unistd.h>
void delay( unsigned long ms ) {
    unsigned int s  = ms / 1000ul;
    unsigned long ns = ( ms % 1000ul ) * 1000ul;
    sleep( s ); usleep( ns );
}
#endif

#define JANK(x) (CHARS[x])
#define SQR(x) ((x) * (x))

const char CHARS[] = { ' ', '.', '=', '#' };

double lerp( double v0, double v1, double t ) {
    return (1 - t) * v0 + t * v1;
}

int approxEqual( double a, double b, double e ) {
    return ( a >= b - e && a <= b + e );
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
    if ( cx >= -2 && cx <= 3 && cy <= SQR(acx) + 0.3 && cy >= SQR(acx) - 0.6 ) {
        total = 2;
        return total;
    }
    // Hand
    if ( approxEqual( SQR( (cx - 3) / 0.25 ) + SQR( (cy - 0.5) / 0.4 ), 1, 0.0001 ) ) {
        total = 2; 
        return total;
    }
    if ( approxEqual( SQR( (cx - 3) / 2 ) + SQR( cy + 0.5 ), 0.08, 0.0001 ) ) {
        total = 2; 
        return total;
    }
    if ( ( SQR(cx - 3.25) + SQR(cy - 0.1) <= 0.08 ) || ( SQR(cx - 3.325) + SQR(cy + 0.2) <= 0.08 ) ) { 
        total = 2;
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
        if ( ( cy >= -0.05 * cx - 0.8 ) || (cy <= -0.05 * cx - 1.55 ) ) total = 3;

        return total;
    }

    // Eyes
    if ( ( SQR(cx - 1) + SQR(cy - 0.9) <= 0.2 ) || ( SQR(cx + 0.4) + SQR(cy - 1) <= 0.2 ) ) {
        total = 1;
        if ( ( SQR(cx - 1.2) + SQR(cy - 0.75) <= 0.01 ) || ( SQR(cx + 0.25) + SQR(cy - 0.85) <= 0.01 ) ) total = 3;

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

    return 0;
}
