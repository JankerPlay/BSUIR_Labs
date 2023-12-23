 ldaa #%00001111
 staa $8000
 ldaa #%11110000
 staa $8001
 ldaa #%10101010
 staa $8002
 lsl $8002
 rol $8001
 rol $8000
 tpa
 anda #%00000001
 cmpa #%00000001
 bne stop
 inc $8002
stop:
  
ss