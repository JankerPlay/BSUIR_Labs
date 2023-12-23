 ldx #$00
 ldy #$100
swap_loop:
 ldaa $0000,x
 staa $00ff
 ldaa $0000,y
 staa $0000,x
 ldaa $00ff
 staa $0000,y
 inx
 dey
 cpy #$80
 bcc swap_loop