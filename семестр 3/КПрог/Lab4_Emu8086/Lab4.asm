.model small
.stack 100h 
.data
input1 DB 14,14,"Input string: "
input2 DB 24,24,0Ah, 0Dh, "Input word to change: "
input3 DB 18,18, 0Ah, 0Dh, "Input new word: "
outputMessage DB 17,17,0Ah, 0Dh, "Result string: "
maxLength equ 200
str1MaxLength DB 0
str1Length DB '$'
str1 DB maxLength + 2 dup('$')
str2MaxLength DB maxLength
str2Length DB '$' 
str2 DB maxLength + 2  dup('$')
str3MaxLength DB maxLength
str3Length DB '$'  
str3 DB maxLength + 2  dup('$')
space DB ' ' 
ins dw 0
def dw 0
trans dw 0
drt dw 0
difference db 0
.code
start:
mov ax, @data
mov ds, ax
mov es, ax       
xor ax, ax
mov str1MaxLength, maxLength;
mov str2MaxLength, maxLength;
mov str3MaxLength, maxLength;
lea dx, input1+2
xor cx,cx
mov cl,[input1+1] 
call showString
lea dx, str1MaxLength
call getString
mov cl, [str1Length]
xor bx,bx
cmp cx, 0
je zero_str
jmp okey
zero_str:
mov bx,1
okey:
lea dx, input2+2
xor cx,cx
mov cl,[input2+1] 
call showString
lea dx, str2MaxLength
call getString
mov cl, [str2Length]
cmp cx, 0
je zero_str1
jmp okey1
zero_str1:
mov bx,1
okey1:
lea dx, input3+2
xor cx,cx
mov cl,[input3+1] 
call showString
lea dx, str3MaxLength
call getString
cmp bx,1
je output_res
xor cx, cx 
mov cl, [str3Length] 
sub cl, [str2Length]
lea di, difference
mov [di], cl
mov cl, str1MaxLength[1]
sub cl, str2MaxLength[1]
inc cl              
cld                 
lea di, str2MaxLength[2]
lea si, str1MaxLength[2]
xor ax, ax
call transform
CHECK_STRING:
mov def, 0 
call searchWord
inc si
add si, def
mov dx, def
add ins, dx
inc ins
loop CHECK_STRING
call deleteSpace
output_res:
lea dx, outputMessage+2
mov cl, outputMessage[1]
call showString
lea dx, str1
xor cx,cx
mov cl, str1MaxLength[1]
call showString 
END:
mov ax, 4c00h
int 21h
getString proc
    push ax
    mov ah, 0ah
    int 21h
    pop ax
    ret
getString endp
showString proc
    push ax
    push bx
    mov ah, 40h
    mov bx,1
    int 21h
    pop bx
    pop ax 
    ret
showString endp
searchWord proc
    push cx
    push di
    push si
    mov bx, si
    mov cl, str2Length
    repe cmpsb              
    je _EQ
    jne _NEQ
    _EQ:
    pusha
    push ins 
    xor si, si
    xor dx, dx
    mov dl, str2MaxLength[1]
    add ins, dx
    mov dx, ins
    mov si, dx
    mov bl, str1[si]
    cmp str1[si], ' '
    pop ins
    popa
    jne _NEQ                        
    call delete
    call change
    inc al
    _NEQ:
    pop si
    pop di
    pop cx
    ret
searchWord endp
delete proc
    push bx
    push di
    push si
    mov di, bx 
    xor cx, cx
    mov cl, str1Length
    repe movsb              
    pop si
    pop di
    pop bx
    ret
delete endp
change proc
    pusha
    push ins
    lea di, str1Length  
    mov cl, [difference]
    add [di], cl                 
    lea si, str1MaxLength
    lea di, str3MaxLength
    mov ch, str1MaxLength[1] 
    mov cl, str3MaxLength[1]
    xor bx, bx
    xor di, di
    Outer_Cycl:
        mov dl, str3[di]         
        push dx
        mov bl, ch
        mov si, bx
        cycl:                   
            mov dl, str1[si-1]
            mov str1[si], dl
            dec si
            cmp ins, si
            jne cycl
        pop dx
        mov str1[si], dl       
        
        inc si
        inc di
        inc ch
        inc ins
        inc def
        xor dx, dx
        mov dl, cl
        cmp di, dx 
        jne Outer_Cycl      
    pop ins
    dec def    
    popa
    ret
change endp
transform PROC
    pusha
    lea si, str2MaxLength
    lea di, str3MaxLength
    xor bx, bx
    xor di, di
    xor si, si
    mov ch, str2MaxLength[1]                
    mov cl, str3MaxLength[1]
    mov bl, ch
    mov si, bx
    cycl1:
            mov dl, str2[si-1]
            mov str2[si], dl
            dec si
            cmp trans, si
            jne cycl1
    mov dl, space
    mov str2[si], dl
    add str2MaxLength[1], 1
    mov bl, cl
    mov di, bx
    cmp di, 0
    je zero2
    cycl2:
            mov dl, str3[di-1]
            mov str3[di], dl
            dec di
            cmp trans, di
            jne cycl2
    zero2:
    mov dl, space
    mov str3[di], dl
    add str3MaxLength[1], 1
    lea si, str1MaxLength
    xor si, si
    xor cx, cx
    mov ch, str1MaxLength[1]
    mov bl, ch
    mov si, bx
    cycl3:
            mov dl, str1[si-1]
            mov str1[si], dl
            dec si
            cmp trans, si
            jne cycl3
    mov dl, space
    mov str1[si], dl
    add str1MaxLength[1], 1
    xor si, si
    xor cx, cx
    mov ch, str1MaxLength[1]
    mov bl, ch
    mov si, bx
    mov dl, space
    mov str1[si], dl
    add str1MaxLength[1], 1        
    popa
    ret
endp transform
deleteSpace PROC
    pusha
    lea si, str1MaxLength
    xor si, si
    xor cx, cx
    xor dx, dx
    mov ch, str1MaxLength[1]
    mov bl, ch
    mov di, bx
    xor si, si
    cycle:
        mov dl, str1[si+1]
        mov str1[si], dl
        inc si
        cmp si, di
        jne cycle
    sub str1MaxLength[1], 1
    popa
    ret    
endp deleteSpace    
end start