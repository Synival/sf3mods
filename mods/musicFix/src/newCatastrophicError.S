# Rewrite of the catastrophic error function to write a string from an argument.
.section .catastrophicError
.global _catastrophicError

_catastrophicError:
    mov        r4, r9
    mov.l      r8, @-r15
    sts.l      pr, @-r15
    mov.l      func_getDebugTextCoords, r8
    mov        #0x2, r5
    jsr        @r8
    mov        #0x20, r4
    mov.l      func_writeDebugUIntWithoutZeroes, r1
    mov.l      @r15, r4
    jsr        @r1
    mov        r0, r5
    mov        #0x2, r5
    jsr        @r8
    mov        #0x0, r4
    mov        r9, r4
    mov.l      func_writeDebugStr, r1
    jsr        @r1
    mov        r0, r5

# No more game for you!
loop_forever:
    bra        loop_forever
    nop

# Data
.balign 4
func_getDebugTextCoords:
    .long _getDebugTextCoords
func_writeDebugUIntWithoutZeroes:
    .long _writeDebugUIntWithoutZeroes
func_writeDebugStr:
    .long _writeDebugStr
