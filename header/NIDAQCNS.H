/*********************************************************************/
/*                                                                   */
/* This file contains definitions for constants required for some    */
/* of the NI-DAQ functions.                                          */
/*                                                                   */
/* You should use symbols defined here in your programs;  do not     */
/* use the numerical values.                                         */
/*                                                                   */
/* See your NI-DAQ Function Reference Manual for details concerning  */
/* use of constants defined here.                                    */
/*                                                                   */
/*********************************************************************/
#if !defined (___nidaqcns_h___)
#define ___nidaqcns_h___

#define ND_ABOVE_HIGH_LEVEL           	11020L
#define ND_ADC_RESOLUTION             	11040L
#define ND_AI_CALDAC_COUNT            	11050L
#define ND_AI_CHANNEL_COUNT           	11060L
#define ND_AI_FIFO_INTERRUPTS         	11600L
#define ND_AO_CALDAC_COUNT            	11070L
#define ND_AO_CHANNEL_COUNT           	11080L
#define ND_AO_EXT_REF_CAPABLE         	11090L
#define ND_AO_UNIPOLAR_CAPABLE        	11095L
#define ND_ARM                        	11100L
#define ND_ARMED                      	11200L
#define ND_AUTOINCREMENT_COUNT        	11300L
#define ND_AUTOMATIC                  	11400L
#define ND_AVAILABLE_POINTS           	11500L

#define ND_BASE_ADDRESS               	12100L
#define ND_BELOW_LOW_LEVEL            	12130L
#define ND_BOARD_CLOCK                	12170L
#define ND_BUFFERED_EVENT_CNT         	12200L
#define ND_BUFFERED_PERIOD_MSR        	12300L
#define ND_BUFFERED_PULSE_WIDTH_MSR   	12400L
#define ND_BUFFERED_SEMI_PERIOD_MSR   	12500L

#define ND_CAL_CONST_AUTO_LOAD        	13050L
#define ND_CALIBRATION_FRAME_SIZE     	13060L
#define ND_CALIBRATION_FRAME_PTR      	13065L
#define ND_CJ_TEMP                    	((short)(0x8000))
#define ND_CLEAN_UP                   	13100L
#define ND_CONFIG_MEMORY_SIZE         	13150L
#define ND_COUNT                      	13200L
#define ND_COUNTER_0                  	13300L
#define ND_COUNTER_1                  	13400L
#define ND_COUNTER_1_SOURCE           	13430L
#define ND_COUNT_AVAILABLE            	13450L
#define ND_COUNT_DOWN                 	13465L
#define ND_COUNT_UP                   	13485L
#define ND_COUNT_1                    	13500L
#define ND_COUNT_2                    	13600L
#define ND_COUNT_3                    	13700L
#define ND_COUNT_4                    	13800L
#define ND_CURRENT_OUTPUT             	40200L

#define ND_DAC_RESOLUTION             	13950L
#define ND_DATA_XFER_MODE_AI          	14000L
#define ND_DATA_XFER_MODE_AO_GR1      	14100L
#define ND_DATA_XFER_MODE_AO_GR2      	14200L
#define ND_DATA_XFER_MODE_DIO_GR1     	14300L
#define ND_DATA_XFER_MODE_DIO_GR2     	14400L
#define ND_DATA_XFER_MODE_DIO_GR3     	14500L
#define ND_DATA_XFER_MODE_DIO_GR4     	14600L
#define ND_DATA_XFER_MODE_DIO_GR5     	14700L
#define ND_DATA_XFER_MODE_DIO_GR6     	14800L
#define ND_DATA_XFER_MODE_DIO_GR7     	14900L
#define ND_DATA_XFER_MODE_DIO_GR8     	15000L
#define ND_DATA_XFER_MODE_GPCTR0      	15100L
#define ND_DATA_XFER_MODE_GPCTR1      	15200L
#define ND_DEVICE_SERIAL_NUMBER       	15280L
#define ND_DEVICE_TYPE_CODE           	15300L
#define ND_DISABLED                   	15400L
#define ND_DISARM                     	15450L
#define ND_DMA_A_LEVEL                	15500L
#define ND_DMA_B_LEVEL                	15600L
#define ND_DMA_C_LEVEL                	15700L
#define ND_DONE                       	15800L
#define ND_DONT_CARE                  	15900L
#define ND_DONT_KNOW                  	15950L

#define ND_EDGE_SENSITIVE             	16000L
#define ND_ENABLED                    	16050L
#define ND_EXTERNAL                   	16060L
#define ND_EXTERNAL_CALIBRATE         	16100L

#define ND_FACTORY_CALIBRATION_DATE   	16200L
#define ND_FACTORY_CALIBRATION_EQUIP  	16210L
#define ND_FACTORY_EEPROM_AREA        	16220L
#define ND_FREQ_OUT                   	16400L
#define ND_FSK                        	16500L

#define ND_GATE                       	17100L
#define ND_GATE_POLARITY              	17200L
#define ND_GPCTR0_GATE                	17300L
#define ND_GPCTR0_OUTPUT              	17400L
#define ND_GPCTR0_SOURCE              	17500L
#define ND_GPCTR1_GATE                	17600L
#define ND_GPCTR1_OUTPUT              	17700L
#define ND_GPCTR1_SOURCE              	17800L
#define ND_GROUND_DAC_REFERENCE       	17900L

#define ND_HARDWARE                   	18000L
#define ND_HIGH                       	18050L
#define ND_HIGH_HYSTERESIS            	18080L
#define ND_HIGH_TO_LOW                	18100L
#define ND_HW_ANALOG_TRIGGER          	18900L

#define ND_INITIAL_COUNT              	19100L
#define ND_INIT_PLUGPLAY_DEVICES      	19110L
#define ND_INSIDE_REGION              	19150L
#define ND_INTERNAL                   	19160L
#define ND_INTERNAL_100_KHZ           	19200L
#define ND_INTERNAL_10_MHZ            	19300L
#define ND_INTERNAL_20_MHZ            	19400L
#define ND_INTERNAL_TIMER             	19500L
#define ND_INTERRUPTS                 	19600L
#define ND_INTERRUPT_A_LEVEL          	19700L
#define ND_INTERRUPT_B_LEVEL          	19800L
#define ND_INTERRUPT_TRIGGER_MODE     	19850L
#define ND_IN_CHANNEL_CLOCK_TIMEBASE  	19900L
#define ND_IN_CHANNEL_CLOCK_TB_POL    	20000L
#define ND_IN_CONVERT                 	20100L
#define ND_IN_CONVERT_POL             	20200L
#define ND_IN_DATA_FIFO_SIZE          	20250L
#define ND_IN_EXTERNAL_GATE           	20300L
#define ND_IN_EXTERNAL_GATE_POL       	20400L
#define ND_IN_SCAN_CLOCK_TIMEBASE     	20500L
#define ND_IN_SCAN_CLOCK_TB_POL       	20600L
#define ND_IN_SCAN_IN_PROG            	20650L
#define ND_IN_SCAN_START              	20700L
#define ND_IN_SCAN_START_POL          	20800L
#define ND_IN_START_TRIGGER           	20900L
#define ND_IN_START_TRIGGER_POL       	21000L
#define ND_IN_STOP_TRIGGER            	21100L
#define ND_IN_STOP_TRIGGER_POL        	21200L
#define ND_INTERRUPT_EVERY_SAMPLE     	11700L
#define ND_INTERRUPT_HALF_FIFO        	11800L
#define ND_IO_CONNECTOR               	21300L

#define ND_LEVEL_SENSITIVE            	24000L
#define ND_LOW                        	24050L
#define ND_LOW_HYSTERESIS             	24080L
#define ND_LOW_TO_HIGH                	24100L
#define ND_LPT_DEVICE_MODE            	24200L

#define ND_NEGATIVE                   	26100L
#define ND_NEW                        	26190L
#define ND_NI_DAQ_SW_AREA             	26195L
#define ND_NO                         	26200L
#define ND_NO_STRAIN_GAUGE            	26225L
#define ND_NO_TRACK_AND_HOLD          	26250L
#define ND_NONE                       	26300L
#define ND_NOT_APPLICABLE             	26400L
#define ND_NUMBER_DIG_PORTS           	26500L

#define ND_OFF                        	27010L
#define ND_ON                         	27050L
#define ND_OUT_DATA_FIFO_SIZE         	27070L
#define ND_OUT_EXTERNAL_GATE          	27080L
#define ND_OUT_EXTERNAL_GATE_POL      	27082L
#define ND_OUT_START_TRIGGER          	27100L
#define ND_OUT_START_TRIGGER_POL      	27102L
#define ND_OUT_UPDATE                 	27200L
#define ND_OUT_UPDATE_POL             	27202L
#define ND_OUT_UPDATE_CLOCK_TIMEBASE  	27210L
#define ND_OUT_UPDATE_CLOCK_TB_POL    	27212L
#define ND_OUTPUT_MODE                	27230L
#define ND_OUTPUT_POLARITY            	27240L
#define ND_OUTPUT_STATE               	27250L
#define ND_OUTPUT_TYPE                	40000L
#define ND_OTHER_GPCTR_OUTPUT         	27300L
#define ND_OTHER_GPCTR_TC             	27400L

#define ND_PAUSE                      	28040L
#define ND_PAUSE_ON_HIGH              	28045L
#define ND_PAUSE_ON_LOW               	28050L
#define ND_PFI_0                      	28100L
#define ND_PFI_1                      	28200L
#define ND_PFI_2                      	28300L
#define ND_PFI_3                      	28400L
#define ND_PFI_4                      	28500L
#define ND_PFI_5                      	28600L
#define ND_PFI_6                      	28700L
#define ND_PFI_7                      	28800L
#define ND_PFI_8                      	28900L
#define ND_PFI_9                      	29000L
#define ND_PRE_ARM                    	29050L
#define ND_POSITIVE                   	29100L
#define ND_PREPARE                    	29200L
#define ND_PROGRAM                    	29300L
#define ND_PULSE                      	29350L
#define ND_PULSE_SOURCE               	29500L
#define ND_PULSE_TRAIN_GNR            	29600L

#define ND_REGLITCH                   	31000L
#define ND_RESERVED                   	31100L
#define ND_RESET                      	31200L
#define ND_RESUME                     	31250L
#define ND_RETRIG_PULSE_GNR           	31300L
#define ND_REVISION                   	31350L
#define ND_RTSI_0                     	31400L
#define ND_RTSI_1                     	31500L
#define ND_RTSI_2                     	31600L
#define ND_RTSI_3                     	31700L
#define ND_RTSI_4                     	31800L
#define ND_RTSI_5                     	31900L
#define ND_RTSI_6                     	32000L
#define ND_RTSI_CLOCK                 	32100L

#define ND_SC_2040_MODE               	32500L
#define ND_SC_2043_MODE               	32600L
#define ND_SELF_CALIBRATE             	32700L
#define ND_SET_DEFAULT_LOAD_AREA      	32800L
#define ND_SIMPLE_EVENT_CNT           	33100L
#define ND_SINGLE_PERIOD_MSR          	33200L
#define ND_SINGLE_PULSE_GNR           	33300L
#define ND_SINGLE_PULSE_WIDTH_MSR     	33400L
#define ND_SINGLE_TRIG_PULSE_GNR      	33500L
#define ND_SOFTWARE                   	33600L
#define ND_SOURCE                     	33700L
#define ND_SOURCE_POLARITY            	33800L
#define ND_STRAIN_GAUGE               	33850L
#define ND_STRAIN_GAUGE_EX0           	33875L
#define ND_SUB_REVISION               	33900L

#define ND_TC_REACHED                 	34100L
#define ND_THE_AI_CHANNEL             	34400L
#define ND_TOGGLE                     	34700L
#define ND_TOGGLE_GATE                	34800L
#define ND_TRACK_AND_HOLD             	34850L
#define ND_TRIG_PULSE_WIDTH_MSR       	34900L

#define ND_UI2_TC                     	35100L
#define ND_UP_DOWN                    	35150L
#define ND_UP_TO_1_DMA_CHANNEL        	35200L
#define ND_UP_TO_2_DMA_CHANNELS       	35300L
#define ND_USE_CAL_CHAN               	36000L
#define ND_USER_EEPROM_AREA           	37000L
#define ND_USER_EEPROM_AREA_2         	37010L
#define ND_USER_EEPROM_AREA_3         	37020L
#define ND_USER_EEPROM_AREA_4         	37030L
#define ND_USER_EEPROM_AREA_5         	37040L

#define ND_VOLTAGE_OUTPUT             	40100L
#define ND_VOLTAGE_REFERENCE          	38000L

#define ND_YES                        	39100L

#define ND_DIO128_SELECT_INPUT_PORT   	41100L
#define ND_DIO128_GET_PORT_THRESHOLD  	41200L
#define ND_DIO128_SET_PORT_THRESHOLD  	41300L

#define ND_AO48DC_SELECT_AO_CHANNEL   	42100L
#define ND_AO48DC_GET_POWERUP_VALUE   	42200L
#define ND_AO48DC_SET_POWERUP_STATE   	42300L
#endif

