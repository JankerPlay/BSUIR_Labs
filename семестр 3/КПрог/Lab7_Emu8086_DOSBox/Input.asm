.model small
.stack 100h;
.data
        
        inputMessage    db "Input string please", 0Dh, 0Ah, '$'
        endMessage      db "Your message:", 0Dh, 0Ah, '$'
        str             db 256 dup('$') 
        enterLine       db 0Dh, 0Ah, '$' 
        
.code            

print macro txt                  
    
    mov dx,offset txt
    mov ah,09h
    int 21h
endm   

input macro buf
    mov dx,offset buf
    mov ah,0Ah
    int 21h
endm

start:        
        mov ax, data
        mov ds, ax
        
        print inputMessage
        input str
        print enterLine
        print endMessage
        print [str+2] 
        
end start;
  