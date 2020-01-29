; test function calls

#entry :main

sub:
    set r2 $0069 ; return value
    mov r3 sp ; retval dest [sp-4]
    set at $4
    sub r3 r3 at
    stw r3 r2 ; store retval
    ret

main:
    set r1 $0041 ; arg1
    psh r1
    call ::sub
    ; return is at [sp-4]
    pop at ; pop the return address
    pop r1 ; pop arg1
    hlt