        include ndefload.asm
        DEFINE  border_loading 0
      IF  smooth=0
        DEFINE  desc  $fe80
        DEFINE  ramt  $fd00+notabl
      ELSE
        DEFINE  desc  $fc81+notabl
        DEFINE  ramt  desc
      ENDIF
        display "----------------------------"
        display /A,0x8000-tmpbuf-stasp-mainrw, " bytes free"
        display "____________________________"
        output  loader.bin
        org     $5b06+ini-prnbuf
ini     ld      de, desc
        di
        db      $de, $c0, $37, $0e, $8f, $39, $96 ;OVER USR 7 ($5ccb)
        ld      hl, $5ccb+descom-ini
        ld      bc, $7f
        ldir
      IF  border_loading=0
        xor     a
      ELSE
        ld      a, border_loading
      ENDIF
        out     ($fe), a
        ld      hl, $5ccb+descom-ini-1
        ld      de, $5aff
        call    desc
        ld      hl, $8000-maplen
        ld      de, engicm
        push    hl
        call    $07f4
        di
        pop     hl
        ld      de, ramt-maplen
        ld      bc, maplen
        ldir
        ld      hl, $8000-maplen+engicm-1
        ld      de, ramt-1-maplen
        call    desc
        ld      sp, $5b06
        ld      de, $ffff
        ld      hl, ramt-1-maplen-codel2-codel1-codel0-bl2len
      IF  smooth=0
        ld      bc, $101
        lddr
        ld      e, $7f
        ld      bc, $180-notabl
      ELSE
        ld      bc, $300-notabl
      ENDIF
        lddr
        ld      hl, $5ccb+prnbuf-ini
        ld      de, $5b06
        push    de
        ld      c, screen-prnbuf
        ldir
        ret
prnbuf  ld      a, $17
        ld      bc, $7ffd
        out     (c), a
        ld      ($fff8), a
        ld      a, $10
        out     (c), a
        ld      a, ($fff8)
        cp      $17
        ld      de, ramt-1-maplen
        jr      z, next
        ld      hl, ramt-1-maplen-codel2
        ld      bc, codel1
        lddr
        ld      hl, init1
        ld      ($fffd), hl
        ld      hl, frame1
        ld      ($fffa), hl
        ld      a, $c3
        ld      ($fff6), a
        jr      copied
next    call    ramt-maplen-12
        jr      z, copied
        ld      hl, ramt-1-maplen-codel2-codel1
        ld      bc, codel0
        lddr
        ld      hl, init0
        ld      ($fffd), hl
        ld      hl, frame0
        ld      ($fffa), hl
copied  ld      hl, ramt-1-maplen-codel2-codel1-codel0-bl2len-$281-$7f*smooth+notabl
        ld      de, $7fff
        ld      bc, $23f8
        lddr
      IF  bl2len>0
        ld      hl, ramt-maplen-codel2-codel1-codel0-1
        ld      de, $10000-stasp+bl2len-1
        ld      bc, bl2len
        lddr
      ENDIF
        ld      hl, $ffff
        ld      ($fffe-stasp), hl
        ld      hl, $8000+maincm-1
        ld      de, $8040+mainrw-1
        call    desc
        ld      hl, $8040
        ld      de, $8000
        ld      sp, 0x10000-tmpbuf-stasp
        push    de
        ld      bc, mainrw
        ldir
        ret
screen  incbin  loading.rcs.zx7b
descom  org     desc
        include dzx7b_rcs.asm
