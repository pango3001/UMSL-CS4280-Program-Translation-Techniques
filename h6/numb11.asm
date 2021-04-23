1) A program that reads in two numbers and prints out the smallest of the two numbers.

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






2) A program that keeps reading in numbers and totaling those numbers until an exact total of 100 is reached. At which it should print 100 and terminate.


START: NOOP
READ X
LOAD X
BR HUNDCHECK

HUNDCHECK: NOOP
ADD TOTAL
SUB 100
BRZERO END
ADD 100
STORE TOTAL
BR START

END: NOOP
ADD 100
STORE TOTAL
WRITE TOTAL
STOP

X 0
TOTAL 0