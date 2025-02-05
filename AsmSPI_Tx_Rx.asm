    #include <xc.inc>
    
    TXbyte   equ    0x10
    TXcnt    equ    0x12
    SDOPort  equ    PORTC 
    SCLPort  equ    PORTB 
    SDOPin   equ    7
    SCLPin   equ    1 
   
    PSECT SPI_TX,class=CODE,reloc=2,optim=inline
    PSECT HW_SPI_TX,class=CODE,reloc=2,optim=inline
    
    global   _SPI_TX
    global   _HW_SPI_TX
    
;----------------software SPI transmit-------------
_SPI_TX:
    movwf    TXbyte, 0
    movlw    9
    movwf    TXcnt, 0
_StartTx: 
    dcfsnz   TXcnt,1, 0
    return
    bcf      SCLPort, SCLPin, 0
    btfsc    TXbyte, 7, 0
    goto     _SDOset
    goto     _SDOclr 
    
_SDOset:
    bsf      SDOPort, SDOPin, 0
    rlncf    TXbyte, 1, 0
    bsf      SCLPort, SCLPin, 0
    goto     _StartTx
_SDOclr:    
    bcf      SDOPort, SDOPin, 0
    rlncf    TXbyte, 1, 0
    bsf      SCLPort, SCLPin, 0
    goto     _StartTx
;--------------------------------------------------
    
;-------------hardware SPI transmit/receive--------    
_HW_SPI_TX:
    movwf    SSPBUF, 0
_START_HW_TX:   
    btfss    SSPSTAT, 0, 0
    goto     _START_HW_TX
    movf     SSPBUF, 0, 0   
    return
;--------------------------------------------------    
end
