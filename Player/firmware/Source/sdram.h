#define SDRAM_BANK1_ADDR                 ((uint32_t)0xC0000000)
#define SDRAM_BANK2_ADDR                 ((uint32_t)0xD0000000)
#define SDRAM_MEMORY_WIDTH               FMC_SDRAM_MEM_BUS_WIDTH_32
#define SDCLOCK_PERIOD                   FMC_SDRAM_CLOCK_PERIOD_2
/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3 */
#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

static void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command){
  __IO uint32_t tmpmrd =0;
  /* Step 1:  Configure a clock configuration enable command */
  Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 2: Insert 100 us minimum delay */
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  HAL_Delay(1);

  /* Step 3: Configure a PALL (precharge all) command */
  Command->CommandMode = FMC_SDRAM_CMD_PALL;
  Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 4 : Configure a Auto-Refresh command */
  Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber = 8;
  Command->ModeRegisterDefinition = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 5: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, 0x1000);

  /* Step 6: Set the refresh rate counter */
  /* (15.62 us x Freq) - 20 */
  /* Set the device refresh counter */
  hsdram->Instance->SDRTR |= ((uint32_t)((1292)<< 1));
}

void sdram_cfg(SDRAM_HandleTypeDef *hsdram){
  FMC_SDRAM_CommandTypeDef command;

#if 0 // done in main.c
  FMC_SDRAM_TimingTypeDef  SDRAM_Timing;
  hsdram->Instance = FMC_SDRAM_DEVICE;
  
  SDRAM_Timing.LoadToActiveDelay    = 2;
  SDRAM_Timing.ExitSelfRefreshDelay = 6;
  SDRAM_Timing.SelfRefreshTime      = 4;
  SDRAM_Timing.RowCycleDelay        = 6;
  SDRAM_Timing.WriteRecoveryTime    = 2;
  SDRAM_Timing.RPDelay              = 2;
  SDRAM_Timing.RCDDelay             = 2;
  
  hsdram->Init.SDBank             = FMC_SDRAM_BANK2;
  hsdram->Init.ColumnBitsNumber   = FMC_SDRAM_COLUMN_BITS_NUM_9;
  hsdram->Init.RowBitsNumber      = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram->Init.MemoryDataWidth    = SDRAM_MEMORY_WIDTH;
  hsdram->Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram->Init.CASLatency         = FMC_SDRAM_CAS_LATENCY_3;
  hsdram->Init.WriteProtection    = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram->Init.SDClockPeriod      = SDCLOCK_PERIOD;
  hsdram->Init.ReadBurst          = FMC_SDRAM_RBURST_ENABLE;
  hsdram->Init.ReadPipeDelay      = FMC_SDRAM_RPIPE_DELAY_0;
  /* Initialize the SDRAM controller */
  if(HAL_SDRAM_Init(hsdram, &SDRAM_Timing) != HAL_OK)
    error(MEM_ERROR, "SDRAM init error");
#endif
  
  /* Program the SDRAM external device */
  SDRAM_Initialization_Sequence(hsdram, &command);
}
