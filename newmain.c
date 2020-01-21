/* 
 * File:   newmain.c
 * Author: Cristian Joel
 *
 * Created on 18 de enero de 2020, 13:42
 */

#define _XTAL_FREQ 4000000
#include <xc.h>     //standard include file for Microchip chips

    //Variables de timer para retardo de 1seg. (61630 -> 65535)    
    volatile char v_TMR0H = 0b11110000;
    volatile char v_TMR0L = 0b10111110;
    
    //Variable para habilitar despliegue
    volatile bit v_Seg_Act = 0;
    
    //Arreglo para unidades dec_uni
    volatile unsigned short int dec_uni_array[6];
    
int main(int argc, char** argv) {
    //Configuración de puerto A0 como salida
    TRISAbits.TRISA0 = 0;
    //Registro de control de Interrupciones (Habilitar interrupcion de TMR0)
    INTCONbits.TMR0IE = 1;
    //Interrupcion de alta prioridad
    INTCON2bits.TMR0IP = 1;
    //Registro de control de Timer0 (16 bits @256 Prescaler):
    T0CON = 0b10000111;
    //Enable global interrupts (?)
    ei();
    
    unsigned short int h = 0;
    unsigned short int m = 0;
    unsigned short int s = 0;
    
    unsigned short int posArray = 0;
    unsigned short int d = 0;
    
    while(1){
        for(h = 0; h< = 23; h++){
            for(m = 0; m <= 59; m++){
                for(s = 0; s <= 59; s++){
                    //Habilitar despliegue durante 1 segundo
                    v_Seg_Act = 1;
                    //Obtener decenas/unidades
                    dec_uni(h,posArray);
                    posArray += 2;
                    dec_uni(m,posArray);
                    posArray += 2;
                    dec_uni(s,posArray);
                    posArray = 0;
                    
                    while(v_Seg_Act == 1){
                        for(d = 0; d <= 5; d++){
                            despliegue(dec_uni_array[d]);
                            //delay
                        }
                    }
                }
            }
        }
    }   
    return 0;
}    

void dec_uni(unsigned short int n, unsigned short int posArray){
    unsigned short int v_dec = 0;
    
    while(n >= 10){
        v_dec = v_dec;
        n -= 10;
    }

    dec_uni_array[posArray] = v_dec;
    dec_uni_array[posArray + 1] = n;
}

void despliegue(unsigned short int d){
    switch(d){
        case 0:
            //Asignación de bits para numero 0
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
    }
    
    //Asignar puerto a front utilizando "d"
}

void __interrupt(high_priority) intRoutine(void){
    //Monitoreo de interrupcion por desborde para Timer0
    if(INTCONbits.TMR0IF == 1){
        //Asignación de Posicion en timer para retardo 1 seg.
        TMR0H = v_TMR0H;
        TMR0L = v_TMR0L;
        //Se limpia bit de interrupción por desborde.
        INTCONbits.TMR0IF = 0;
    }
}

//Programa para encender un led con interrupciones
/*
    //Variables de timer para retardo de 1seg. (61630 -> 65535)    
    //char v_TMR0H = 0b11110000;
    //char v_TMR0L = 0b10111110;
    //Variables de timer para retardo de 2seg. (57722 -> 65535)
    volatile char v_TMR0H = 0b11100001;
    volatile char v_TMR0L = 0b01111010;

int main(int argc, char** argv) {
    //Configuración de puerto A0 como salida
    TRISAbits.TRISA0 = 0;
    //Registro de control de Interrupciones (Habilitar interrupcion de TMR0)
    INTCONbits.TMR0IE = 1;
    //Interrupcion de alta prioridad
    INTCON2bits.TMR0IP = 1;
    //Registro de control de Timer0 (16 bits @256 Prescaler):
    T0CON = 0b10000111;
    //Enable global interrupts (?)
    ei();
    
    while(1){
    }   
    return 0;
}

void __interrupt(high_priority) timer0Int(void){
    //Monitoreo de interrupcion por desborde para Timer0
    if(INTCONbits.TMR0IF == 1){
        //Cambio de estatus en Puerto A0
        LATAbits.LATA0 ^= 1;
        //Asignación de Posicion en timer para retardo 1 seg.
        TMR0H = v_TMR0H;
        TMR0L = v_TMR0L;
        //Se limpia bit de interrupción por desborde.
        INTCONbits.TMR0IF = 0;
    }
}
*/
/*
 Encender y apagar un LED con delay:
 
int main(int argc, char** argv) {
    TRISA = 0b00000000;
    while(1){
        LATA = 0b00000001;
        __delay_ms(1000);
        LATA = 0b00000000;
        __delay_ms(1000);   
    }
    return 0;
}
 */

