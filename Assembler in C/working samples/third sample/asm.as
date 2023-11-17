asd: .entry LIST
asdsad: .extern W
asdad: .extern x
asdad: .extern x1
asdad: .extern x2
.entry low

.extern x3
;

;

LOOP: add r3 , r2
 prn #48
.entry LOOP
      lea W, r2
low:  inc r7
      inc x
      mov r3 , r2
      sub r1 , r4
    bne END
      cmp K, #-6
      bne %END
      dec W
.entry END
      jmp %LOOP
      add L3 , L3
END:  stop
STR: .string "abcd"
LIST: .data 6 ,-9 ,12
      .data -100
K:    .data 31 ,1
 .extern L3