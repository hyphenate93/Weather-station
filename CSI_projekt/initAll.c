
void init_keypad(void)
{
    *AT91C_PMC_PCER = 0x4000 | 0x2000; //Peripheral Clock PortC & PortD

    *AT91C_PIOC_PER = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 |
                      AT91C_PIO_PC5 | AT91C_PIO_PC7 | AT91C_PIO_PC8 |
                      AT91C_PIO_PC9; //Enable Port C

    *AT91C_PIOD_PER = AT91C_PIO_PD2; //Enable Buffer Pin
    *AT91C_PIOD_OER = AT91C_PIO_PD2; //Output Enable Buffer
}

void init_display(void)
{
    *AT91C_PMC_PCER = 0x4000 | 0x2000; //Peripheral Clock PortC & PortD

    *AT91C_PIOD_PER = AT91C_PIO_PD0; //Enable Reset Pin
    *AT91C_PIOD_OER = AT91C_PIO_PD0; //Output Enable Reset

    *AT91C_PIOC_PER = AT91C_PIO_PC2 | AT91C_PIO_PC3 | AT91C_PIO_PC4 |
                      AT91C_PIO_PC5 | AT91C_PIO_PC6 | AT91C_PIO_PC7 |
                      AT91C_PIO_PC8 | AT91C_PIO_PC9 | AT91C_PIO_PC12 |
                      AT91C_PIO_PC13 | AT91C_PIO_PC14 | AT91C_PIO_PC15 |
                      AT91C_PIO_PC16 | AT91C_PIO_PC17 | AT91C_PIO_PC18 |
                      AT91C_PIO_PC19; //Enable Port C

    //Buffer, Enable Output(12), Set Direction(13), C/D(14), CE(15), RD(16), WR(17) FS(18), RV(19)
    *AT91C_PIOC_OER = AT91C_PIO_PC12 | AT91C_PIO_PC13 | AT91C_PIO_PC14 |
                      AT91C_PIO_PC15 | AT91C_PIO_PC16 | AT91C_PIO_PC17 |
                      AT91C_PIO_PC18 | AT91C_PIO_PC19;
}

void init_temp(void)
{
    *AT91C_PMC_PCER = 0x8000000 | 0x1000; //Peripheral Clock TC0 & PIOB

    *AT91C_TC0_CMR = 0x1; //(*AT91C_TC0_CMR |             //Select Timer_Clock1 as TCCLK
                          //AT91C_TC_CLKS_TIMER_DIV1_CLOCK);
                          //    *AT91C_TC0_CMR      = 0x1; //(*AT91C_TC0_CMR |
                          //AT91C_TC_CLKS_TIMER_DIV2_CLOCK);

    *AT91C_TC0_CCR = 0x1;     //AT91C_TC_CLKEN;               //Enable counter
    *AT91C_TC0_CCR = 0x4;     //AT91C_TC_SWTRG;               //SW_Reset TC0_CCR0
    *AT91C_TC0_CMR = 0x60000; //(*AT91C_TC0_CMR | AT91C_TC_LDRA_FALLING |
                              //AT91C_TC_LDRB_RISING);      //Load Capture Value TC0_CMR0, A(Falling) & B(Rising)

    *AT91C_PIOB_PER = AT91C_PIO_PB25;
    *AT91C_PIOB_OER = AT91C_PIO_PB25;

    //Enable the interrupt (NVIC) with the inline declared function
    NVIC_ClearPendingIRQ(TC0_IRQn);
    NVIC_SetPriority(TC0_IRQn, 150);
    NVIC_EnableIRQ(TC0_IRQn);
}

void init_sensor(void)
{
    *AT91C_PMC_PCER = 0x800; //Enable PORT A
    *AT91C_PMC_PCER1 = 0x20; //Peripheral Clock ADC
                             //    int ADCCLOCK        = MCK /((AT91C_ADC_PRESCAL + 1) * 2);
    *AT91C_ADCC_MR = 0x200;  // ADCCLOCK = 14Mhz
}

void init_pwm(void)
{
    *AT91C_PMC_PCER1 = 0x10;                          //Peripheral Clock1 PWM
    *AT91C_PMC_PCER = 0x2000;                         //Peripheral Clock PORT C
    *AT91C_PIOC_PDR = AT91C_PIO_PB24;                 //Let peripheral control the pin REG_PIOB_PDR
    *AT91C_PIOC_ABMR = AT91C_PIO_PB24;                //Activate peripheral B to control the pin in REG_PIOB_ABSR
    *AT91C_PWMC_ENA = AT91C_PWMC_CHID7;               //Enable PWM-channel in ENA_CHID1
    *AT91C_PWMC_CH7_CMR = AT91C_PWMC_CPRE_MCK_DIV_32; //Set Pre-scaler to Master_CLK/32 in PWM_CMRx
    *AT91C_PWMC_CH7_CPRDR = 0xCD14;                   //Write a value to PWM_CPRD (20ms)
    *AT91C_PWMC_CH7_CDTYUPDR = 1340;                  //Write a value to PWM_CDTY (1ms);
                                                      //Delay(30000000)
}
