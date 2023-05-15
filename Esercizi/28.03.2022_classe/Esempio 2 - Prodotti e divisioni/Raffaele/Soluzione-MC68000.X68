ORG $1000
START:
move.l #4095, d1
move #41, d2
move #33, d3
move.w #29041, d0
divu d1, d0
move.w d0, d5
move d5,d4
muls d3,d4
addi #113, d3
move d3, d6
divs #3, d6
move.w d6, d5
move.l d5, d6
divs #5, d6
swap d6
move.w d6, d3
muls #52, d2
move d2, d6
divs d3, d6
move.w d6, d1
swap d6
move.w d6, d2
END    START 
