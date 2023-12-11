int press_keypad(void)
{
    int keyPressed = 0;
    *AT91C_PIOD_CODR = AT91C_PIO_PD2;
    *AT91C_PIOC_OER = AT91C_PIO_PC8 | AT91C_PIO_PC9 | AT91C_PIO_PC7;
    int col[] = {AT91C_PIO_PC8, AT91C_PIO_PC9, AT91C_PIO_PC7};
    int row[] = {AT91C_PIO_PC5, AT91C_PIO_PC2, AT91C_PIO_PC3, AT91C_PIO_PC4};

    for (int i = 0; i < 3; i++) //Step through columns
    {
        *AT91C_PIOC_SODR = AT91C_PIO_PC8 | AT91C_PIO_PC9 | AT91C_PIO_PC7;
        *AT91C_PIOC_CODR = col[i]; //Clear column

        for (int j = 0; j < 4; j++) //Step through rows
        {
            int colRow = *AT91C_PIOC_PDSR & row[j];
            if (colRow == 0) //Compare column & row = 0
            {
                keyPressed = j * 3 + i + 1;
                *AT91C_PIOC_ODR = AT91C_PIO_PC8 | AT91C_PIO_PC9 | AT91C_PIO_PC7;
                *AT91C_PIOD_SODR = AT91C_PIO_PD2;
                keyPressed = keyPressed;
                return keyPressed; //Return key that was pressed
            }
        }
    }
    *AT91C_PIOC_ODR = AT91C_PIO_PC8 | AT91C_PIO_PC9 | AT91C_PIO_PC7;
    *AT91C_PIOD_SODR = AT91C_PIO_PD2;
    return keyPressed; //No key pressed, return 0
}