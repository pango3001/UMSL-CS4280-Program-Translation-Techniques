START: NOOP
READ X
LOAD X
READ Y
SUB Y
BRZPOS ENDY
BRNEG ENDX

ENDX: NOOP
WRITE X
BR END

ENDY: NOOP
ADD X
WRITE Y
BR END

END: NOOP
STOP

X 0
Y 0
