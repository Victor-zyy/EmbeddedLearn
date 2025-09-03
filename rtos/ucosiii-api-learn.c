/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Ping-Pong implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include <string.h>
#include "board.h"
#include  <app_cfg.h>
/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
//#define  TEST_TASK
//#define  TEST_SEM
//#define  TEST_PRIO_REVERSE
//#define  TEST_FLAG
//#define  TEST_STMR
//#define  TEST_TASK_SEM
//#define  TEST_TASK_SEM2
//#define  TEST_TASK_MSG
//#define  TEST_MEM
#define  TEST_INT

/*
*********************************************************************************************************
*                                                 TCB
*********************************************************************************************************
*/
static  OS_TCB   AppTaskStartTCB;
#ifdef  TEST_TASK
static  OS_TCB   AppTaskLEDTCB;
static  OS_TCB   AppTaskLEDEM1TCB;
static  OS_TCB   AppTaskLEDEM2TCB;
static  OS_TCB   AppTaskLEDEM3TCB;
#endif


#ifdef TEST_SEM
static	OS_TCB	 AppTaskKeyS1TCB;
static	OS_TCB	 AppTaskKeyK1TCB;
#endif

#ifdef  TEST_PRIO_REVERSE
static	OS_TCB	 AppTaskHprioTCB;
static	OS_TCB	 AppTaskMprioTCB;
static	OS_TCB	 AppTaskLprioTCB;
#endif

#ifdef  TEST_FLAG
static  OS_TCB 	 AppTaskKeyFlagTCB;
static  OS_TCB 	 AppTaskLedFlagTCB;
#endif

#ifdef  TEST_STMR
static  OS_TCB 	 AppTaskTmrLedTCB;
#endif

#ifdef  TEST_TASK_SEM
static  OS_TCB   AppTaskSemPendTCB;
static  OS_TCB   AppTaskSemPostTCB;
#endif

#ifdef  TEST_TASK_SEM2
static  OS_TCB   AppTaskSemCarPendTCB;
static  OS_TCB   AppTaskSemCarPostTCB;
#endif


#ifdef  TEST_TASK_MSG
static  OS_TCB   AppTaskMsgPendTCB;
static  OS_TCB   AppTaskMsgPostTCB;
#endif

#ifdef  TEST_MEM
static  OS_TCB   AppTaskMemPendTCB;
static  OS_TCB   AppTaskMemPostTCB;
#endif

#ifdef  TEST_INT
static  OS_TCB	 AppTaskStatTCB;
#endif

OS_TCB   AppTaskUartIntPendTCB;
OS_TCB   AppTaskKeyIntPendTCB;
/*
*********************************************************************************************************
*                                                STACKS
*********************************************************************************************************
*/

static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
#ifdef  TEST_TASK
static  CPU_STK  AppTaskLEDEM1Stk[APP_TASK_LED_EM1_STK_SIZE];
static  CPU_STK  AppTaskLEDEM2Stk[APP_TASK_LED_EM2_STK_SIZE];
static  CPU_STK  AppTaskLEDEM3Stk[APP_TASK_LED_EM3_STK_SIZE];
static  CPU_STK  AppTaskLEDStk[APP_TASK_LED_STK_SIZE];
#endif

#ifdef  TEST_SEM
static 	CPU_STK	 AppTaskKeyK1Stk[APP_TASK_KEY_K1_STK_SIZE];
static 	CPU_STK	 AppTaskKeyS1Stk[APP_TASK_KEY_S1_STK_SIZE];
#endif

#ifdef  TEST_PRIO_REVERSE
static	CPU_STK  AppTaskHprioStk[APP_TASK_Hprio_STK_SIZE];
static	CPU_STK  AppTaskMprioStk[APP_TASK_Mprio_STK_SIZE];
static	CPU_STK  AppTaskLprioStk[APP_TASK_Lprio_STK_SIZE];
#endif

#ifdef  TEST_FLAG
static  CPU_STK	 AppTaskKeyFlagStk[APP_TASK_Key_Flag_STK_SIZE];
static  CPU_STK	 AppTaskLedFlagStk[APP_TASK_Led_Flag_STK_SIZE];
#endif

#ifdef  TEST_STMR
static  CPU_STK	 AppTaskTmrLedStk[APP_TASK_Tmr_Led_STK_SIZE];
#endif

#ifdef  TEST_TASK_SEM
static  CPU_STK	 AppTaskSemPostStk[APP_TASK_Sem_Post_STK_SIZE];
static  CPU_STK	 AppTaskSemPendStk[APP_TASK_Sem_Pend_STK_SIZE];
#endif

#ifdef  TEST_TASK_SEM2
static  CPU_STK	 AppTaskSemCarPostStk[APP_TASK_Sem_Car_Post_STK_SIZE];
static  CPU_STK	 AppTaskSemCarPendStk[APP_TASK_Sem_Car_Pend_STK_SIZE];
#endif

#ifdef  TEST_TASK_MSG
static  CPU_STK	 AppTaskMsgPostStk[APP_TASK_Msg_Post_STK_SIZE];
static  CPU_STK	 AppTaskMsgPendStk[APP_TASK_Msg_Pend_STK_SIZE];
#endif

#ifdef  TEST_MEM
static  CPU_STK	 AppTaskMemPostStk[APP_TASK_Mem_Post_STK_SIZE];
static  CPU_STK	 AppTaskMemPendStk[APP_TASK_Mem_Pend_STK_SIZE];
#endif

#ifdef  TEST_INT
static  CPU_STK	 AppTaskUartIntPendStk[APP_TASK_Uart_Int_Pend_STK_SIZE];
static  CPU_STK	 AppTaskKeyIntPendStk[APP_TASK_Key_Int_Pend_STK_SIZE];
static	CPU_STK	 AppTaskStatStk[APP_TASK_Stat_STK_SIZE];
#endif

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void  AppTaskStart  (void *p_arg);
#ifdef TEST_TASK
static  void  AppTaskLED  	(void *p_arg);
static  void  AppTaskLEDEM1 (void *p_arg);
static  void  AppTaskLEDEM2 (void *p_arg);
static  void  AppTaskLEDEM3 (void *p_arg);
#endif

#ifdef  TEST_SEM
static  void  AppTaskKeyK1 (void *p_arg);
static  void  AppTaskKeyS1 (void *p_arg);
#endif

#ifdef  TEST_PRIO_REVERSE
static  void  AppTaskHprio (void *p_arg);
static  void  AppTaskMprio (void *p_arg);
static  void  AppTaskLprio (void *p_arg);
#endif

#ifdef  TEST_FLAG
static  void  AppTaskKeyFlag (void *p_arg);
static  void  AppTaskLedFlag (void *p_arg);
#endif

#ifdef  TEST_STMR
static  void  AppTaskTmrLed( void *p_arg );
#endif

#ifdef  TEST_TASK_SEM
static  void  AppTaskSemPost( void *p_arg );
static  void  AppTaskSemPend( void *p_arg );
#endif

#ifdef  TEST_TASK_SEM2
static  void  AppTaskSemCarPost( void *p_arg );
static  void  AppTaskSemCarPend( void *p_arg );
#endif

#ifdef  TEST_TASK_MSG
static  void  AppTaskMsgPost( void *p_arg );
static  void  AppTaskMsgPend( void *p_arg );
#endif

#ifdef  TEST_MEM
static  void  AppTaskMemPost( void *p_arg );
static  void  AppTaskMemPend( void *p_arg );
#endif

#ifdef  TEST_INT
static  void  AppTaskUartIntPend( void *p_arg );
static  void  AppTaskKeyIntPend( void *p_arg );
static  void  AppTaskStat( void *p_arg );
#endif
/*
 * Kernel Object Definition
 */
 
OS_Q queue;
OS_SEM sem;
OS_SEM tsem;
OS_MUTEX mutex;
OS_FLAG_GRP flag_grp;
OS_MEM mem;
uint8_t uCArray[3][20];
/**
 * Main application entry point.
 */
int main( void )
{
    OS_ERR  err;
    // Target board initialisation
    BoardInitMcu( );
    BoardInitPeriph( );


    CPU_IntDis( );                                      		    /* Disable all interrupts.                              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */
		
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR ) AppTaskStart,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cpu_clk_freq;
    CPU_INT32U  cnts;
    OS_ERR      err;
		CPU_SR_ALLOC();


   (void)p_arg;

    CPU_Init();

    cpu_clk_freq = GetBoardCPUClkFreq( );                           /* Determine SysTick reference freq.                    */
    cnts = cpu_clk_freq / (CPU_INT32U)OSCfg_TickRate_Hz;        /* Determine nbr SysTick increments                     */
    OS_CPU_SysTickInit( cnts );                                   /* Init uC/OS periodic time src (SysTick).              */

    Mem_Init();                                                 /* Initialize Memory Management Module                  */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

    CPU_IntDisMeasMaxCurReset();
		
		OSSchedRoundRobinCfg( (CPU_BOOLEAN)DEF_ENABLED,
													(OS_TICK) 0,
													(OS_ERR *)&err);
		/*
		* Use OSTaskChangePrio and Test
		* 
		*
		*/
		OSQCreate( (OS_Q *)&queue,
							 (CPU_CHAR *)"queue test",
							 (OS_MSG_QTY) 20,
							 (OS_ERR *)&err );
		
		OSSemCreate( (OS_SEM *)&sem,
								 (CPU_CHAR *)"sem for 2' test",
								 (OS_SEM_CTR) 5,
								 (OS_ERR *)&err );
		
		// two value semaphore
		OSSemCreate( (OS_SEM *)&tsem,
						 (CPU_CHAR *)"tsem for 2' test",
						 (OS_SEM_CTR) 1,
						 (OS_ERR *)&err );
		OSMutexCreate( (OS_MUTEX *)&mutex,
									 (CPU_CHAR *)"mutex for 2' test",
									 (OS_ERR *)&err );

		OSFlagCreate( (OS_FLAG_GRP *)&flag_grp,
									(CPU_CHAR *)"flag test",
									(OS_FLAGS) 0,
									(OS_ERR *)&err );
		OSMemCreate( (OS_MEM *)&mem,
								 (CPU_CHAR *)"mem array",
								 (void *)uCArray,
								 (OS_MEM_QTY)3,
								 (OS_MEM_SIZE)20,
								 (OS_ERR *)&err );
									
#ifdef TEST_TASK								 
    OSTaskCreate((OS_TCB     *)&AppTaskLEDTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task LED",
                 (OS_TASK_PTR ) AppTaskLED,
                 (void       *) 0,
                 //(OS_PRIO     ) APP_TASK_LED_PRIO,
								 (OS_PRIO     ) APP_TASK_LED_EM1_PRIO,
                 (CPU_STK    *)&AppTaskLEDStk[0],
                 (CPU_STK_SIZE) APP_TASK_LED_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_LED_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
		 OSTaskCreate((OS_TCB     *)&AppTaskLEDEM1TCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task LED EM1",
                 (OS_TASK_PTR ) AppTaskLEDEM1,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_LED_EM1_PRIO,
                 (CPU_STK    *)&AppTaskLEDEM1Stk[0],
                 (CPU_STK_SIZE) APP_TASK_LED_EM1_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_LED_EM1_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 200u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
		 OSTaskCreate((OS_TCB     *)&AppTaskLEDEM2TCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task LED EM2",
                 (OS_TASK_PTR ) AppTaskLEDEM2,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_LED_EM1_PRIO,
                 (CPU_STK    *)&AppTaskLEDEM2Stk[0],
                 (CPU_STK_SIZE) APP_TASK_LED_EM2_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_LED_EM2_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 200u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif

#ifdef TEST_SEM
		 /* For Semaphore Task usage testing */
		 OSTaskCreate((OS_TCB     *)&AppTaskKeyK1TCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task KeyK1",
                 (OS_TASK_PTR ) AppTaskKeyK1,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_LED_EM1_PRIO,
                 (CPU_STK    *)&AppTaskKeyK1Stk[0],
                 (CPU_STK_SIZE) APP_TASK_KEY_K1_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_KEY_K1_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 200u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

		 OSTaskCreate((OS_TCB     *)&AppTaskKeyS1TCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task KeyK1",
                 (OS_TASK_PTR ) AppTaskKeyS1,
                 (void       *) 0,
                 (OS_PRIO     ) APP_TASK_LED_EM1_PRIO,
                 (CPU_STK    *)&AppTaskKeyS1Stk[0],
                 (CPU_STK_SIZE) APP_TASK_KEY_S1_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_KEY_S1_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 200u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif

#ifdef TEST_PRIO_REVERSE
    OSTaskCreate((OS_TCB     *)&AppTaskHprioTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Hprio",
                 (OS_TASK_PTR ) AppTaskHprio,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Hprio_PRIO,
                 (CPU_STK    *)&AppTaskHprioStk[0],
                 (CPU_STK_SIZE) APP_TASK_Hprio_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Hprio_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
    OSTaskCreate((OS_TCB     *)&AppTaskMprioTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Mprio",
                 (OS_TASK_PTR ) AppTaskMprio,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Mprio_PRIO,
                 (CPU_STK    *)&AppTaskMprioStk[0],
                 (CPU_STK_SIZE) APP_TASK_Mprio_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Mprio_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
    OSTaskCreate((OS_TCB     *)&AppTaskLprioTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Hprio",
                 (OS_TASK_PTR ) AppTaskLprio,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Lprio_PRIO,
                 (CPU_STK    *)&AppTaskLprioStk[0],
                 (CPU_STK_SIZE) APP_TASK_Lprio_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Lprio_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif


#ifdef TEST_FLAG
    OSTaskCreate((OS_TCB     *)&AppTaskKeyFlagTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task KeyFlag",
                 (OS_TASK_PTR ) AppTaskKeyFlag,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Key_Flag_PRIO,
                 (CPU_STK    *)&AppTaskKeyFlagStk[0],
                 (CPU_STK_SIZE) APP_TASK_Key_Flag_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Key_Flag_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSTaskCreate((OS_TCB     *)&AppTaskLedFlagTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task KeyFlag",
                 (OS_TASK_PTR ) AppTaskLedFlag,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Led_Flag_PRIO,
                 (CPU_STK    *)&AppTaskLedFlagStk[0],
                 (CPU_STK_SIZE) APP_TASK_Led_Flag_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Led_Flag_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif

#ifdef  TEST_STMR
    OSTaskCreate((OS_TCB     *)&AppTaskTmrLedTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task TmrLed",
                 (OS_TASK_PTR ) AppTaskTmrLed,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Tmr_Led_PRIO,
                 (CPU_STK    *)&AppTaskTmrLedStk[0],
                 (CPU_STK_SIZE) APP_TASK_Tmr_Led_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Tmr_Led_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);								 
#endif

#if TEST_TASK_SEM
    OSTaskCreate((OS_TCB     *)&AppTaskSemPostTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskSemPost",
                 (OS_TASK_PTR ) AppTaskSemPost,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Post_PRIO,
                 (CPU_STK    *)&AppTaskSemPostStk[0],
                 (CPU_STK_SIZE) APP_TASK_Sem_Post_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Sem_Post_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);	
								 
    OSTaskCreate((OS_TCB     *)&AppTaskSemPendTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskSemPend",
                 (OS_TASK_PTR ) AppTaskSemPend,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskSemPendStk[0],
                 (CPU_STK_SIZE) APP_TASK_Sem_Pend_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Sem_Pend_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif
#ifdef TEST_TASK_SEM2
    OSTaskCreate((OS_TCB     *)&AppTaskSemCarPostTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskSemPost",
                 (OS_TASK_PTR ) AppTaskSemCarPost,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Post_PRIO,
                 (CPU_STK    *)&AppTaskSemCarPostStk[0],
                 (CPU_STK_SIZE) APP_TASK_Sem_Car_Post_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Sem_Car_Post_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);	
								 
    OSTaskCreate((OS_TCB     *)&AppTaskSemCarPendTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskSemPend",
                 (OS_TASK_PTR ) AppTaskSemCarPend,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskSemCarPendStk[0],
                 (CPU_STK_SIZE) APP_TASK_Sem_Car_Pend_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Sem_Car_Pend_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

#endif
#ifdef TEST_TASK_MSG
    OSTaskCreate((OS_TCB     *)&AppTaskMsgPendTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskMsgPend",
                 (OS_TASK_PTR ) AppTaskMsgPend,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskMsgPendStk[0],
                 (CPU_STK_SIZE) APP_TASK_Msg_Pend_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Msg_Pend_STK_SIZE,
                 (OS_MSG_QTY  ) 1u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
    OSTaskCreate((OS_TCB     *)&AppTaskMsgPostTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskMsgPend",
                 (OS_TASK_PTR ) AppTaskMsgPost,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskMsgPostStk[0],
                 (CPU_STK_SIZE) APP_TASK_Msg_Post_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Msg_Post_STK_SIZE,
                 (OS_MSG_QTY  ) 1u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif
#ifdef TEST_MEM
    OSTaskCreate((OS_TCB     *)&AppTaskMemPendTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskMemPend",
                 (OS_TASK_PTR ) AppTaskMemPend,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskMemPendStk[0],
                 (CPU_STK_SIZE) APP_TASK_Mem_Pend_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Mem_Pend_STK_SIZE,
                 (OS_MSG_QTY  ) 1u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
    OSTaskCreate((OS_TCB     *)&AppTaskMemPostTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskMemPend",
                 (OS_TASK_PTR ) AppTaskMemPost,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskMemPostStk[0],
                 (CPU_STK_SIZE) APP_TASK_Mem_Post_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Mem_Post_STK_SIZE,
                 (OS_MSG_QTY  ) 1u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif

#ifdef TEST_INT
    OSTaskCreate((OS_TCB     *)&AppTaskUartIntPendTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskUartIntPend",
                 (OS_TASK_PTR ) AppTaskUartIntPend,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskUartIntPendStk[0],
                 (CPU_STK_SIZE) APP_TASK_Uart_Int_Pend_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Uart_Int_Pend_STK_SIZE,
                 (OS_MSG_QTY  ) 1u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
    OSTaskCreate((OS_TCB     *)&AppTaskKeyIntPendTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskKeyIntPend",
                 (OS_TASK_PTR ) AppTaskKeyIntPend,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskKeyIntPendStk[0],
                 (CPU_STK_SIZE) APP_TASK_Key_Int_Pend_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Key_Int_Pend_STK_SIZE,
                 (OS_MSG_QTY  ) 1u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
								 
    OSTaskCreate((OS_TCB     *)&AppTaskStatTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App TaskStat",
                 (OS_TASK_PTR ) AppTaskStat,
                 (void       *) 0,
								 (OS_PRIO     ) APP_TASK_Sem_Pend_PRIO,
                 (CPU_STK    *)&AppTaskStatStk[0],
                 (CPU_STK_SIZE) APP_TASK_Stat_STK_SIZE / 10,
                 (CPU_STK_SIZE) APP_TASK_Stat_STK_SIZE,
                 (OS_MSG_QTY  ) 1u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
#endif							 		 
			OSTaskDel ( NULL, 
								(OS_ERR	*) &err);
			// Test Whether if this function will be returned
			GpioWrite( &Em3, 1);
}

#ifdef TEST_TASK
static uint8_t data_str[20] = { 'z', 'h', 'a', 'n', 'g' };

static void  AppTaskLED( void *p_arg )
{
	
		OS_ERR p_err ;
		uint16_t times = 0;
		uint8_t data = 0;
		OS_REG_ID	os_id = 0;
		OS_MSG_SIZE msg_size = 0;
		char *p_msg = NULL;
	
		p_arg = p_arg;
		OSTaskSuspend( (OS_TCB *) NULL,
									 (OS_ERR *) &p_err);
	
		if( ( os_id = OSTaskRegGetID( (OS_ERR *)&p_err ) )!= 0 )
			while( 1 );
		OSTaskRegSet( (OS_TCB *) NULL,
									(OS_REG_ID) os_id,
									(OS_REG	) 89,
									(OS_ERR *)&p_err);
		while( 1 ) {
				GpioWrite( &Led1, 0);
				OSTimeDly( 1000, OS_OPT_TIME_DLY, &p_err);
				GpioWrite( &Led1, 1);
				OSTimeDly( 1000, OS_OPT_TIME_DLY, &p_err);
				times++;

				if( 5 == times )
				{
						OSTaskChangePrio( (OS_TCB	 *)&AppTaskLEDTCB,
															(OS_PRIO	)1,
															(OS_ERR	 *)&p_err);
						OSTaskSuspend( (OS_TCB *) &AppTaskLEDEM1TCB,
													 (OS_ERR *)	&p_err);
						OSTaskSuspend( (OS_TCB *) &AppTaskLEDEM2TCB,
													 (OS_ERR *)	&p_err);
					
					 OSTaskCreate((OS_TCB     *)&AppTaskLEDEM3TCB,                /* Create the start task                                */
												 (CPU_CHAR   *)"App Task LED EM3",
												 (OS_TASK_PTR ) AppTaskLEDEM3,
												 (void       *) 0,
												 (OS_PRIO     ) APP_TASK_LED_EM1_PRIO,
												 (CPU_STK    *)&AppTaskLEDEM3Stk[0],
												 (CPU_STK_SIZE) APP_TASK_LED_EM3_STK_SIZE / 10,
												 (CPU_STK_SIZE) APP_TASK_LED_EM3_STK_SIZE,
												 (OS_MSG_QTY  ) 5u,
												 (OS_TICK     ) 200u,
												 (void       *) 0,
												 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
												 (OS_ERR     *)&p_err);
												 
						if( OSTaskRegGet( (OS_TCB *)NULL,
															 (OS_REG_ID) os_id,
															 (OS_ERR *)&p_err) != 89)
								while( 1 );

						while( 1 )
						{
								GpioWrite( &Led1, 0);
								//DelayMs( 1000 );
								OSTimeDly( 1000, OS_OPT_TIME_DLY, &p_err);
								GpioWrite( &Led1, 1);
								//DelayMs( 1000 );
								OSTimeDly( 1000, OS_OPT_TIME_DLY, &p_err);
								p_msg = OSQPend( (OS_Q *)&queue,
												 (OS_TICK)0,
												 (OS_OPT)OS_OPT_PEND_BLOCKING,
												 (OS_MSG_SIZE *)&msg_size,
												 (CPU_TS *)NULL,
												 (OS_ERR *)&p_err );
								//UartPutChar( &Uart5, 'a' );
								if( p_err != OS_ERR_PEND_ABORT )
								{
										UartPutBuffer( &Uart3, (uint8_t *)p_msg, msg_size );
								}
								else {
										while( 1 )
										{
												UartPutBuffer( &Uart3, (uint8_t *)data_str, 5 );
												OSTimeDly( 1000, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
										}
										
								}
						}
				
				}	
		}
	
}


void  AppTaskLEDEM1( void *p_arg )
{
		OS_ERR p_err = 0 ;
		p_arg = p_arg;
		
		while( 1 ) {
				GpioWrite( &Em1, 0);
				//OSTimeDly( 1000, OS_OPT_TIME_DLY, &p_err);
				DelayMs( 1000 );
				GpioWrite( &Em1, 1);
				//OSTimeDly( 1000, OS_OPT_TIME_DLY, &p_err);
				DelayMs( 1000 );
		}
	
}

void  AppTaskLEDEM2( void *p_arg )
{
		OS_ERR p_err ;
		p_arg = p_arg;
		
		DelayMs( 5000 );
		OSTaskResume( (OS_TCB *) &AppTaskLEDTCB,
									(OS_ERR *) &p_err);

		while( 1 ) {
				GpioWrite( &Em2, 0);
				DelayMs( 1000 );
				GpioWrite( &Em2, 1);
				DelayMs( 1000 );
		}
	
}

void  AppTaskLEDEM3( void *p_arg )
{
		OS_ERR p_err ;
		uint8_t time = 0;
		p_arg = p_arg;

		while( 1 ) {
				OSQPost( (OS_Q *)&queue,
								 (void *)"ucosIII test rodata section DMA",
								 (OS_MSG_SIZE) sizeof("ucosIII test rodata section DMA"),
								 (OS_OPT) OS_OPT_POST_FIFO | OS_OPT_POST_ALL,
								 (OS_ERR *)&p_err );
				time++;
				GpioWrite( &Em3, 0);
				DelayMs( 1000 );
				GpioWrite( &Em3, 1);
				DelayMs( 1000 );
				/* To Simulate the error occurs */
				if( 10 == time )
				{
						OSTimeDly( 5000, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
						OSQPendAbort(	(OS_Q *)&queue,
													OS_OPT_PEND_ABORT_1,
													(OS_ERR *)&p_err );
						while(1);
				}
		}
	
}
#endif

#ifdef TEST_SEM
/* Park Car Get */
static void  AppTaskKeyK1( void *p_arg )
{
		
		OS_ERR p_err;
		OS_SEM_CTR ctr = 0;
		p_arg = p_arg;
	
		while( 1 )
		{
				if( GpioRead( &K1 ) == GPIO_PIN_RESET )
				{
						OSTimeDly( 100, OS_OPT_TIME_DLY, &p_err );
						if( GpioRead( &K1 ) == GPIO_PIN_RESET )
						{
								ctr = OSSemPend( (OS_SEM *)&sem,
																 (OS_TICK) 0,
																 (OS_OPT) OS_OPT_PEND_BLOCKING,
																 (CPU_TS *)NULL,
																 (OS_ERR *)&p_err );
								GpioToggle( &Em3 );
								UartPutBuffer( &Uart3, (uint8_t *)&ctr, 1 );
						}
				}
				OSTimeDly( 10, OS_OPT_TIME_DLY, &p_err );
		}
}


/* Park Car Release */
static void AppTaskKeyS1( void *p_arg )
{
		// in case of warning
		OS_ERR p_err;
		OS_SEM_CTR ctr = 0;
		p_arg = p_arg;

		while( 1 )
		{
				if( GpioRead( &S1 ) ==  GPIO_PIN_RESET )
				{
						OSTimeDly( 100, OS_OPT_TIME_DLY, &p_err );
						if( GpioRead( &S1 ) ==  GPIO_PIN_RESET )
						{
								ctr = OSSemPost( (OS_SEM *)&sem, OS_OPT_POST_ALL, (OS_ERR*)&p_err );
								GpioToggle( &Em2 );
								UartPutBuffer( &Uart3, (uint8_t *)ctr, sizeof(ctr) );
						}
				}
				OSTimeDly( 10, OS_OPT_TIME_DLY, &p_err );
		}
}
#endif

#ifdef TEST_PRIO_REVERSE
// Highest Prio Task
static void AppTaskHprio( void *p_arg )
{
		OS_ERR p_err;
		p_arg = p_arg;
	
		while( 1 )
		{
				UartPutChar( &Uart3, 'H' );
				GpioToggle( &Led1 );
				#if 0
				OSSemPend( (OS_SEM *)&tsem,
									 (OS_TICK)0,
									 (OS_OPT)OS_OPT_PEND_BLOCKING,
									 (CPU_TS *)NULL,
									 (OS_ERR *)&p_err );
				#endif
				OSMutexPend( (OS_MUTEX *)&mutex,
										 (OS_TICK )0,
										 (OS_OPT)OS_OPT_PEND_BLOCKING,
										 (CPU_TS *)NULL,
										 (OS_ERR *)&p_err );
			
				UartPutChar( &Uart3, 'h' );
				GpioToggle( &Em1 );
				#if 0
				OSSemPost( (OS_SEM *)&tsem,
									 (OS_OPT)OS_OPT_POST_1,
									 (OS_ERR *)&p_err );
				#endif
				OSMutexPost( (OS_MUTEX *)&mutex,
										 (OS_OPT)OS_OPT_POST_NONE,
										 (OS_ERR *)&p_err );
										 
				OSTimeDlyHMSM( 0, 0, 0, 10, OS_OPT_TIME_PERIODIC, (OS_ERR *)&p_err );
		}
}

// Middle Prio Task
static void AppTaskMprio( void *p_arg )
{
		OS_ERR p_err;
		p_arg = p_arg;
		while( 1 )
		{
				GpioToggle( &Em2 );
				UartPutChar( &Uart3, 'M' );
				OSTimeDlyHMSM( 0, 0, 0, 500, OS_OPT_TIME_PERIODIC, (OS_ERR *)&p_err );
		}
}


// Low Prio Task
static void AppTaskLprio( void *p_arg )
{
		OS_ERR p_err;
		static uint32_t i  = 0;
		p_arg = p_arg;
		
		
		while( 1 )
		{
			
				UartPutChar( &Uart3, 'L' );
				OSMutexPend( (OS_MUTEX *)&mutex,
										 (OS_TICK )0,
										 (OS_OPT)OS_OPT_PEND_BLOCKING,
										 (CPU_TS *)NULL,
										 (OS_ERR *)&p_err );
				#if 0
				OSSemPend( (OS_SEM*) &tsem,
									 (OS_TICK)0,
									 (OS_OPT)OS_OPT_PEND_BLOCKING,
									 (CPU_TS *)NULL,
									 (OS_ERR *)&p_err );
				#endif
				for( i = 0; i < 600000; i++ )
				{
						OSSched();
				}
				
				UartPutChar( &Uart3, 'l' );
				GpioToggle( &Em3 );
				#if 0	
				OSSemPost( (OS_SEM *)&tsem, 
									 (OS_OPT)OS_OPT_POST_1,
									 (OS_ERR *)&p_err );
				#endif
				OSMutexPost( (OS_MUTEX *)&mutex,
						 (OS_OPT)OS_OPT_POST_NONE,
						 (OS_ERR *)&p_err );
				OSTimeDlyHMSM( 0, 0, 0, 200, OS_OPT_TIME_PERIODIC, (OS_ERR *)&p_err );
		}
}

#endif

#ifdef TEST_FLAG
#define KEY_EVENT1 (0x01 << 0)
#define KEY_EVENT2 (0x01 << 1)


static void AppTaskLedFlag( void *p_arg )
{
		OS_ERR p_err;
		p_arg = p_arg;
		
		while( 1 )
		{
				OSFlagPend( (OS_FLAG_GRP *)&flag_grp,
										(OS_FLAGS) KEY_EVENT1,
										(OS_TICK)0,
										(OS_OPT) OS_OPT_PEND_FLAG_CLR_ANY | OS_OPT_PEND_BLOCKING | OS_OPT_PEND_FLAG_CONSUME ,
										//(OS_OPT) OS_OPT_PEND_FLAG_SET_ANY | OS_OPT_PEND_BLOCKING ,
										(CPU_TS *)NULL,
										(OS_ERR *) &p_err );
				GpioToggle( &Led1 );
		}
}

static void AppTaskKeyFlag( void *p_arg )
{
		OS_ERR p_err;
		p_arg = p_arg;
		
		while( 1 )
		{
				if( GpioRead( &S1 ) == GPIO_PIN_RESET )
				{
						OSTimeDly( 100, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
						if( GpioRead( &S1 ) == GPIO_PIN_RESET )
						{
								OSFlagPost( (OS_FLAG_GRP *)&flag_grp,
														(OS_FLAGS)KEY_EVENT1,
														(OS_OPT)OS_OPT_POST_FLAG_CLR,
														(OS_ERR *)&p_err );
						}
				}
				OSTimeDly( 20, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
		}
}
#endif

#ifdef TEST_STMR
static void TmrCallBack( OS_TMR * p_tmr, void *p_arg )
{
		GpioToggle( &Led1 );
		UartPutBuffer( &Uart3, (uint8_t *)p_arg, 12 );
}

static void AppTaskTmrLed( void *p_arg )
{
		OS_ERR p_err;
		OS_TMR mytmr;
		p_arg = p_arg;
	
		OSTmrCreate( (OS_TMR *)&mytmr,
								 (CPU_CHAR *)"mytmr test",
								 (OS_TICK )10, //1s after
								 (OS_TICK )10, //1s period
								 (OS_OPT)OS_OPT_TMR_PERIODIC ,
								 (OS_TMR_CALLBACK_PTR)TmrCallBack,
								 (void *)"Callback Tmr",
								 (OS_ERR *)&p_err );
		OSTmrStart( (OS_TMR *)&mytmr, (OS_ERR *)&p_err );
		while( 1 )
		{
				OSTimeDly( 1000, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
		}
}
#endif

#ifdef TEST_TASK_SEM
static  void  AppTaskSemPost( void *p_arg )
{
		OS_ERR p_err;
	  p_arg = p_arg;
		while( 1 )
		{
			if( GpioRead( &S1 ) == GPIO_PIN_RESET )
			{
					OSTimeDly( 100, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
					if( GpioRead( &S1 ) == GPIO_PIN_RESET )
					{
							OSTaskSemPost( (OS_TCB *)&AppTaskSemPendTCB,
														 (OS_OPT) OS_OPT_POST_NONE,
														 (OS_ERR *)&p_err );
					}
			}
			
			OSTimeDlyHMSM( 0, 0, 0, 20, OS_OPT_TIME_PERIODIC, (OS_ERR *)&p_err );
		}
}
static  void  AppTaskSemPend( void *p_arg )
{
		OS_ERR p_err;
		p_arg = p_arg;
	
		while( 1 )
		{
				OSTaskSemPend( (OS_TICK)0,
											 (OS_OPT)OS_OPT_PEND_BLOCKING,
											 (CPU_TS *)NULL,
											 (OS_ERR *)&p_err );
				GpioToggle( &Led1 );
		}
}
#endif



#ifdef TEST_TASK_SEM2
static  void  AppTaskSemCarPost( void *p_arg )
{
		OS_ERR p_err;
		OS_SEM_CTR ctr = 0;
	  p_arg = p_arg;
		while( 1 )
		{
			if( GpioRead( &S1 ) == GPIO_PIN_RESET )
			{
					OSTimeDly( 100, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
					if( GpioRead( &S1 ) == GPIO_PIN_RESET )
					{
							ctr = OSTaskSemPost( (OS_TCB *)&AppTaskSemCarPendTCB,
														 (OS_OPT) OS_OPT_POST_NONE,
														 (OS_ERR *)&p_err );
							UartPutChar( &Uart3, ctr ); 
					}
			}
			
			OSTimeDlyHMSM( 0, 0, 0, 20, OS_OPT_TIME_PERIODIC, (OS_ERR *)&p_err );
		}
}
static  void  AppTaskSemCarPend( void *p_arg )
{
		OS_ERR p_err;
		OS_SEM_CTR ctr = 0;
		p_arg = p_arg;
	
		while( 1 )
		{
				if( GpioRead( &K1 ) == GPIO_PIN_RESET )
				{
						OSTimeDly( 100, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
						if( GpioRead( &K1 ) == GPIO_PIN_RESET )
						{
								ctr = OSTaskSemPend( (OS_TICK)0,
															 (OS_OPT)OS_OPT_PEND_BLOCKING,
															 (CPU_TS *)NULL,
															 (OS_ERR *)&p_err );
								GpioToggle( &Led1 );
								UartPutChar( &Uart3, ctr );			
						}
				}
				OSTimeDlyHMSM( 0, 0, 0, 20, OS_OPT_TIME_PERIODIC, (OS_ERR *)&p_err );
		}
}
#endif


#ifdef TEST_TASK_MSG
static void AppTaskMsgPend( void *p_arg )
{
		OS_ERR p_err;
		OS_MSG_SIZE msg_size;
		void * msg = NULL;
		p_arg = p_arg;
		OSTimeDly( 5000, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
		while( 1 )
		{
				msg = OSTaskQPend( (OS_TICK)0,
													 (OS_OPT)OS_OPT_PEND_BLOCKING,
													 (OS_MSG_SIZE *)&msg_size,
										       (CPU_TS *)NULL,
													 (OS_ERR *)&p_err );
				UartPutBuffer( &Uart3, (uint8_t *)msg, msg_size );
				OSTimeDly( 200, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
		}
}

static void AppTaskMsgPost( void *p_arg )
{
		OS_ERR p_err;
		p_arg = p_arg;
		while( 1 )
		{
				OSTaskQPost( (OS_TCB *)&AppTaskMsgPendTCB,
										 (void *)"Msg1\r\n",
										 (OS_MSG_SIZE)sizeof("Msg1\r\n"),
										 (OS_OPT)OS_OPT_POST_FIFO,
										 (OS_ERR *)&p_err );
				OSTaskQPost( (OS_TCB *)&AppTaskMsgPendTCB,
										 (void *)"Msg2\r\n",
										 (OS_MSG_SIZE)sizeof("Msg2\r\n"),
										 (OS_OPT)OS_OPT_POST_FIFO,
										 (OS_ERR *)&p_err );
										 
				OSTimeDly( 5000, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
			
		}
	
}
#endif


#ifdef TEST_MEM
static void AppTaskMemPend( void *p_arg )
{
		OS_ERR p_err;
		OS_MSG_SIZE msg_size;
		void * msg = NULL;
		p_arg = p_arg;

		while( 1 )
		{
				msg = OSTaskQPend( (OS_TICK)0,
													 (OS_OPT)OS_OPT_PEND_BLOCKING,
													 (OS_MSG_SIZE *)&msg_size,
										       (CPU_TS *)NULL,
													 (OS_ERR *)&p_err );
				UartPutBuffer( &Uart3, (uint8_t *)msg, msg_size );
				//OSTimeDly( 200, OS_OPT_TIME_DLY, (OS_ERR *)&p_err );
				OSMemPut( (OS_MEM *)&mem,
									(void *)msg,
									(OS_ERR *)&p_err );
		}
}

static void AppTaskMemPost( void *p_arg )
{
		OS_ERR p_err;
	  void * msg = NULL;
		uint32_t count = 0;
		p_arg = p_arg;
		while( 1 )
		{
				msg = OSMemGet( (OS_MEM *)&mem,
											  (OS_ERR *)&p_err );
				Str_FmtNbr_Int32S( count++, 20, DEF_NBR_BASE_DEC, ' ', DEF_NO, DEF_NO, msg );
				OSTaskQPost( (OS_TCB *)&AppTaskMemPendTCB,
										 (void *)msg,
										 (OS_MSG_SIZE)20,
										 (OS_OPT)OS_OPT_POST_NONE,
										 (OS_ERR *)&p_err );
			  OSTimeDlyHMSM( 0, 0, 1, 0, OS_OPT_TIME_PERIODIC, (OS_ERR *)&p_err );
		}
	
}
#endif


#ifdef TEST_INT
static void AppTaskUartIntPend( void *p_arg )
{
		OS_ERR p_err;
		
		p_arg = p_arg;
	
		while( 1 )
		{
				OSTaskSemPend( (OS_TICK)0,
											 (OS_OPT)OS_OPT_PEND_BLOCKING,
											 (CPU_TS *)NULL,
											 (OS_ERR *)&p_err );
				GpioToggle( &Em1 );
		}
}


static void AppTaskKeyIntPend( void *p_arg )
{
		OS_ERR p_err;
		
		p_arg = p_arg;
	
		while( 1 )
		{
				OSTaskSemPend( (OS_TICK)0,
											 (OS_OPT)OS_OPT_PEND_BLOCKING,
											 (CPU_TS *)NULL,
											 (OS_ERR *)&p_err );
				GpioToggle( &Em2 );
		}	
}

static void AppTaskStat( void *p_arg )
{
		OS_ERR p_err;
		uint8_t msg[10];
		p_arg = p_arg;
	
		while( 1 )
		{
				// CPU Usage
			
				Str_FmtNbr_Int32S( OSStatTaskCPUUsage / 100, 10, DEF_NBR_BASE_DEC, ' ', DEF_NO, DEF_NO, (char *)msg );
				UartPutBuffer( &Uart3, msg, 10 );
#if 0
				Str_FmtNbr_Int32S( AppTaskKeyIntPendTCB.CPUUsage / 100, 10, DEF_NBR_BASE_DEC, ' ', DEF_NO, DEF_NO, (char *)msg );
				UartPutBuffer( &Uart3, msg, 10 );				
				Str_FmtNbr_Int32S( AppTaskUartIntPendTCB.CPUUsage / 100, 10, DEF_NBR_BASE_DEC, ' ', DEF_NO, DEF_NO, (char *)msg );
				UartPutBuffer( &Uart3, msg, 10 );	
				// Stack
				Str_FmtNbr_Int32S( AppTaskKeyIntPendTCB.StkUsed, 10, DEF_NBR_BASE_DEC, ' ', DEF_NO, DEF_NO, (char *)msg );
				UartPutBuffer( &Uart3, msg, 10 );
				Str_FmtNbr_Int32S( AppTaskKeyIntPendTCB.StkFree, 10, DEF_NBR_BASE_DEC, ' ', DEF_NO, DEF_NO, (char *)msg );
				UartPutBuffer( &Uart3, msg, 10 );				
				Str_FmtNbr_Int32S( AppTaskUartIntPendTCB.StkUsed, 10, DEF_NBR_BASE_DEC, ' ', DEF_NO, DEF_NO, (char *)msg );
				UartPutBuffer( &Uart3, msg, 10 );	
				Str_FmtNbr_Int32S( AppTaskUartIntPendTCB.StkFree, 10, DEF_NBR_BASE_DEC, ' ', DEF_NO, DEF_NO, (char *)msg );
				UartPutBuffer( &Uart3, msg, 10 );	
 
#endif
				OSTimeDlyHMSM( 0, 0, 0, 500, OS_OPT_TIME_PERIODIC, (OS_ERR *)&p_err );
		}
}
#endif
