//Display 
unsigned char status_display(void)
{
    unsigned char temp  = 0;

    *AT91C_PIOC_ODR     = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 | 
                          AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                          AT91C_PIO_PC8 | AT91C_PIO_PC9;   //Clear Databus

    *AT91C_PIOC_SODR    = AT91C_PIO_PC13;               //Set Direction Buffer, input
    *AT91C_PIOC_CODR    = AT91C_PIO_PC12;               //Set Output Buffer
    *AT91C_PIOC_SODR    = AT91C_PIO_PC14;               //Set C/D
//    *AT91C_PIOC_SODR    = AT91C_PIO_PC17;               //Set WR
    *AT91C_PIOC_CODR    = AT91C_PIO_PC15;               //Clear CE
    *AT91C_PIOC_CODR    = AT91C_PIO_PC16;               //Clear RD

    Delay(20);
    
    int t = (*AT91C_PIOC_PDSR) & (AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 | 
                                  AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                                  AT91C_PIO_PC8 | AT91C_PIO_PC9);
    
    temp = t;
    *AT91C_PIOC_SODR    = AT91C_PIO_PC15;               //Set CE
    *AT91C_PIOC_SODR    = AT91C_PIO_PC16;               //Set RD
    *AT91C_PIOC_SODR    = AT91C_PIO_PC12;               //Disable Output Buffer
    *AT91C_PIOC_CODR    = AT91C_PIO_PC13;               //Set Direction Buffer, output
    
    return temp;
}

void command_display(unsigned char command)
{
    while((status_display() & 0xC) != 0xC){}

    unsigned int temp   = 0;
    temp = command;
    temp = temp<<2;
    
    *AT91C_PIOC_CODR    = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 | 
                          AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                          AT91C_PIO_PC8 | AT91C_PIO_PC9;   //Clear Databus
    
    *AT91C_PIOC_SODR    = temp;                         //Set Command Databus

    *AT91C_PIOC_CODR    = AT91C_PIO_PC13;               //Clear Direction Buffer, output
    *AT91C_PIOC_CODR    = AT91C_PIO_PC12;               //Enable Output Buffer
    
    *AT91C_PIOC_OER     = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 | 
                          AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                          AT91C_PIO_PC8 | AT91C_PIO_PC9;   //Set Databus
    
    *AT91C_PIOC_SODR    = AT91C_PIO_PC14;               //Set C/D
    *AT91C_PIOC_CODR    = AT91C_PIO_PC15;               //Clear CE
    *AT91C_PIOC_CODR    = AT91C_PIO_PC17;               //Clear WR

    Delay(20);

    *AT91C_PIOC_SODR    = AT91C_PIO_PC15;               //Set CE
    *AT91C_PIOC_SODR    = AT91C_PIO_PC17;               //Set WR  
    *AT91C_PIOC_SODR    = AT91C_PIO_PC12;               //Disable Output Buffer

    *AT91C_PIOC_ODR     = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 | 
                          AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                          AT91C_PIO_PC8 | AT91C_PIO_PC9;   //Clear Databus 
}    


void data_display(unsigned char data)
{
    while((status_display() & 0xC) != 0xC){}

    unsigned int temp = 0;
    temp = data;
    temp = temp<<2;

    *AT91C_PIOC_CODR      = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 | 
                            AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                            AT91C_PIO_PC8 | AT91C_PIO_PC9;   //Clear Databus 

    *AT91C_PIOC_SODR      = temp;                       //Set Data Databus

    *AT91C_PIOC_CODR      = AT91C_PIO_PC13;             //Clear Direction Buffer, Output
    *AT91C_PIOC_CODR      = AT91C_PIO_PC12;             //Enable Output Buffer 

  
    *AT91C_PIOC_OER       = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 | 
                            AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                            AT91C_PIO_PC8 | AT91C_PIO_PC9;   //Set Databus

  
    *AT91C_PIOC_CODR      = AT91C_PIO_PC14;             //Clear C/D
    *AT91C_PIOC_CODR      = AT91C_PIO_PC15;             //Clear CE  
    *AT91C_PIOC_CODR      = AT91C_PIO_PC17;             //Clear WR

    Delay(20);

    *AT91C_PIOC_SODR      = AT91C_PIO_PC15;             //Set CE
    *AT91C_PIOC_SODR      = AT91C_PIO_PC17;             //Set WR 
    *AT91C_PIOC_SODR      = AT91C_PIO_PC12;             //Disable Output Buffer

    *AT91C_PIOC_ODR       = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 | 
                            AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                            AT91C_PIO_PC8 | AT91C_PIO_PC9;   //Clear Databus  
}    

void setup_display(void)
{
    *AT91C_PIOD_CODR = AT91C_PIO_PD0;                   //Clear Reset Display
    Delay(20000);
    *AT91C_PIOD_SODR = AT91C_PIO_PD0;                   //Set Reset Display

    data_display(0x00);
    data_display(0x00);
    command_display(0x40);                              //Set Text Home Address
    data_display(0x00);
    data_display(0x40);
    command_display(0x42);                              //Set Graphic Home Address
    data_display(0x1e);
    data_display(0x00);
    command_display(0x41);                              //Set Text Area
    data_display(0x1e);
    data_display(0x00);
    command_display(0x43);                              //Set Graphic Area
    command_display(0x80);                              //Text Mode
    command_display(0x94);                              //Text On Graphic Off
}

void clear_display(void)
{
    data_display(0x00);
    data_display(0x00);
    command_display(0x24);
    
    for(int i = 0; i < 490; i++)
    {   
        data_display(0x00);
        command_display(0xC0);
    }   

    data_display(0x00);
    data_display(0x00);
    command_display(0x24);
}  


void print_display(unsigned char t)
{       
        int temp = 0;
        temp = t;
        if(temp != 0)
        {
            data_display(temp);
            command_display(0xC0);
        }
}


unsigned int print_char(void)
{
    int a = 0;
    a = press_keypad();
    unsigned int temp = 0;
    
    //Char 1-9
    if(a == 1){temp = 0x11;}      
    else if(a == 2){temp = 0x12;}
    else if(a == 3){temp = 0x13;}
    else if(a == 4){temp = 0x14;}
    else if(a == 5){temp = 0x15;}
    else if(a == 6){temp = 0x16;}
    else if(a == 7){temp = 0x17;}
    else if(a == 8){temp = 0x18;}
    else if(a == 9){temp = 0x19;}    
    else if(a == 10){temp = 0x0A;}      //Char *
    else if(a == 11){temp = 0x10;}      //Char 0
    else if(a == 12){temp = 0x03;}      //Char #
    return temp;
}