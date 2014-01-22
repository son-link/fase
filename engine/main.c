#include  "fase.h"

const unsigned char data[64]= {
  0x00, 0x42, 0x11, 0+3*4,
  0x08, 0x60, 0x60, 2+0*4,
  0x09, 0x58, 0x48, 3+1*4,
  0x0a, 0x22, 0x02, 1+2*4,
  0x0b, 0x50, 0x6e, 2+1*4,
  0x0c, 0x56, 0x34, 3+3*4,
  0x0d, 0x32, 0x32, 1+2*4,
  0x0e, 0x52, 0x5e, 0+0*4,
  0x0f, 0x12, 0x5e, 0,
  0x08, 0x60, 0x30, 2,
  0x09, 0x58, 0x04, 3,
  0x0a, 0x42, 0x02, 1,
        0x04, 0x26,
        0x34, 0x50,
        0x58, 0x32,
        0x30, 0x5e,
        0x42, 0x22,
        0x11, 0x44,
        0x55, 0x08,
        0x24, 0x16};

int main(){

  // variables
  int i, x= 0, y= 0;

  // inicializar engine
  INIT;

  // pasar datos a sprites y balas
  for ( i = 0; i < 48; i++ )
    sprites[i>>2][i&3]= data[i];
  for ( i = 48; i < 64; i++ )
    bullets[i-48>>1][i&1]= data[i];

  // mostrar la primera pantalla al comienzo
  screen= 0;

  while(1){

    // esto hace que el engine procese un frame generando el escenario
    FRAME;

    // movimiento de los enemigos
    for ( i = 1; i < 12; i++ ){
      if( sprites[i][3]&1 )
        if( sprites[i][2]>0 )
          sprites[i][2]--;
        else
          sprites[i][3]^= 1;
      else
        if( sprites[i][2]<scrh*16 )
          sprites[i][2]++;
        else
          sprites[i][3]^= 1;
      if( sprites[i][3]&2 )
        if( sprites[i][1]>0 )
          sprites[i][1]--;
        else
          sprites[i][3]^= 2;
      else
        if( sprites[i][1]<scrw*16 )
          sprites[i][1]++;
        else
          sprites[i][3]^= 2;
    }

    // movimiento de las balas
    for ( i = 0; i < 8; i++ ){
      if( sprites[i][3]&4 )
        if( bullets[i][1]>0 )
          bullets[i][1]--;
        else
          sprites[i][3]^= 4;
      else
        if( bullets[i][1]<scrh*16 )
          bullets[i][1]++;
        else
          sprites[i][3]^= 4;
      if( sprites[i][3]&8 )
        if( bullets[i][0]>0 )
          bullets[i][0]--;
        else
          sprites[i][3]^= 8;
      else
        if( bullets[i][0]<scrw*16 )
          bullets[i][0]++;
        else
          sprites[i][3]^= 8;
    }

    // movimiento del protagonista
    if( ~KeybYUIOP & 0x01 ){ // P
      if( sprites[0][1]<scrw*16 )
        sprites[0][1]++;
      else if( x < mapw-1 )
        sprites[0][1]= 0,
        screen= y*mapw + ++x;
    }
    else if( ~KeybYUIOP & 0x02 ){ // O
      if( sprites[0][1]>0 )
        sprites[0][1]--;
      else if( x )
        sprites[0][1]= scrw*16,
        screen= y*mapw + --x;
    }
    if( ~KeybGFDSA & 0x01 ){ // A
      if( sprites[0][2]<scrh*16 )
        sprites[0][2]++;
      else if( y < maph-1 )
        sprites[0][2]= 0,
        screen= ++y*mapw + x;
    }
    else if( ~KeybTREWQ & 0x01 ){ // Q
      if( sprites[0][2]>0 )
        sprites[0][2]--;
      else if( y )
        sprites[0][2]= scrh*16,
        screen= --y*mapw + x;
    }
  }
}