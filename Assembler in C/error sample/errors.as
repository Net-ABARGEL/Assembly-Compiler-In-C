asd: .entry LIST
 .extern W
.entry low

.extern x33

LOOP:a add r3 , 
 prn #48
.entry LOOP
      lea W, r2
low:  inc r7
      inc x
2do:     mov r3 ,
      sub r1 , r4
      bne END , asds
      cmp K, #-6
      bne %END
      dec W
.entry END
      jmp %LOOP
      add %L3 , L3
      .entry rrr2
END:  stop
STR: .string "abcd"
LIST: .data 6 ,-9 ,12
      .data -100
K:    .data 31 ,1
 .extern L3