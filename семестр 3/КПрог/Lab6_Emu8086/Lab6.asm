		.model tiny 
		.code 
		      
print macro str 
    push ax
    push dx
    mov ah, 09h
    mov dx,offset str
    int 21h
    pop dx
    pop ax 
endm            
		
print_error macro str
    print str
    ret
endm     

input_str macro buf 
    push ax
    push dx       
    mov dx, offset buf
    mov ah, 0Ah
    int 21h
    pop dx
    pop ax
endm 

MAX_SYMBOL_COUNT equ 10
BUFFER_SIZE equ 1024             
	org 100h	    
    cld  
    mov cl, [0080h]
    cmp cl, 1
    jle command_line_error       
    mov si, 0082h
    mov di, offset path_to_file 
         
init_lp:    
    cmp [si],0dh
    je init_end
    cmp [si], ' '
    je init_end      
    movsb    
    loop init_lp
         
init_end:
    mov [di], 0h   
          
main:
    print s_string_ph     
    mov search_string, MAX_SYMBOL_COUNT 
    input_str search_string 
    print new_line
    mov di,offset search_string + 1 
    mov cl, [di]
    mov search_len,cl 
    inc cl
    mov insert_string, cl   
    print s_insert_ph
    input_str insert_string
     mov di, offset search_string + 1  
    mov cl, [di]      
    mov di, offset insert_string + 1 
    cmp cl, [di]        
    jne length_error   
    mov di,offset insert_string + 1 
    mov cl, [di]
    mov insert_len,cl 
    print new_line 
     
open_file:
    mov ax,3d02h
    mov dx, offset path_to_file
    int 21h
    jc open_error
    mov handle, ax 
    
read_from_file:    
    mov ah, 3fh
    mov bx, handle
    mov dx, offset buffer
    mov cx, BUFFER_SIZE
    int 21h
    jc read_error 
    mov read_bytes, ax  
    cmp ax, 0
    je save_and_exit    
   
first:
    mov di, offset buffer 
    mov cx, BUFFER_SIZE
    mov si, offset search_string + 2
    mov al, [si]   
    
f_loop:
    cmp cx, 0
    je next_part        
    cmp [di],0h
    je save_and_exit
    cmp [di],al     
    pushf
    inc di
    popf  
    loopne f_loop 
    je found      

next_part:
    call write_to_file        
    mov ax, 4201h
    mov bx, handle
    mov cx, 0
    mov dx, 0
    int 21h 
    jc seek_error
    mov begin_pointer[0], dx
    mov begin_pointer[2], ax   
    jmp read_from_file

found:
    push di
    push cx
    push ax
    dec di
    mov si, offset search_string + 2
    xor cx,cx
    mov cl, search_len
    repe cmpsb
    pushf
    dec di
    popf
    je replace
    pop ax
    pop cx
    pop di 
    jmp f_loop 

replace:    
    xor cx,cx
    mov cl,search_len
    sub di,cx
    inc di      
    mov si, offset insert_string + 2 
    rep movsb 
    pop ax
    pop cx
    inc cx
    sub cl,search_len
    sbb ch,0
    add sp, 2
    jmp f_loop  

write_to_file proc near:  
    mov ax, 4200h
    mov bx, handle
    mov cx, begin_pointer[0]
    mov dx, begin_pointer[2]
    int 21h
    jc seek_error    

    mov ah, 40h
    mov bx, handle
    mov cx, read_bytes 
    mov dx, offset buffer 
    int 21h   
    jc write_error
    ret

close_file proc near:  
    mov ah, 3eh
    mov bx, handle
    int 21h 
    jc close_error
    ret  

save_and_exit:
    call write_to_file       
exit:
    call close_file
    ret

length_error:
    print new_line
    print_error lenght_error_ph    
open_error:
    print_error open_error_ph
read_error:                           
    print_error read_error_ph         
close_error:
    print close_error_ph      
write_error:
    print_error write_error_ph 
seek_error:
    print_error seek_error_ph
command_line_error:
    print_error command_line_error_ph    
 
path_to_file db 50 dup(?)   
handle dw 0  
read_bytes dw ?  
search_string db 256 dup(?)
search_len db 0
insert_len db 0
begin_pointer dw 2 dup(0)                  
insert_string db 256 dup(?)                  
s_string_ph db "Enter a search string: $" 
s_insert_ph db "Enter a insert string: $"
write_error_ph db "Writing file error",  0Dh, 0Ah, '$' 
seek_error_ph db "Seek error", 0Dh, 0Ah, '$'
lenght_error_ph db "Error string lenght", 0Dh, 0Ah, '$'
close_error_ph db "Closing file error", 0Dh, 0Ah, '$'
open_error_ph db "Opening file error", 0Dh, 0Ah, '$'  
read_error_ph db "Reading file error", 0Dh, 0Ah, '$' 
command_line_error_ph db "Command line parameters error", 0Dh, 0Ah, '$'
new_line db 0Ah, 0Dh, '$'     
buffer db 512 dup(?)