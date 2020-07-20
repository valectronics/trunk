/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void Timer0_init();         /* Declaration of Timer0 */
void Timer1_init();         /* Declaration of Timer1 */
void ISR_init();            /* Declaration of ISR */
void Button_debounce();