#include "Class_Blinker.h"


/*============================================================================*/
/* Attributes access */
/*============================================================================*/
#define My_Off_Time (Me->var_attr->Off_Time)
#define My_On_Time (Me->var_attr->On_Time)
#define My_Status (Me->var_attr->Status)
#define My_Remaining_Nb_Periods (Me->var_attr->Remaining_Nb_Periods)


/*============================================================================*/
/* Private methods declaration */
/*============================================================================*/
static void Begin_On_Phase( const Class_Blinker* Me );
static void Begin_Off_Phase( const Class_Blinker* Me );


/*============================================================================*/
/* Public methods */
/*============================================================================*/
void Class_Blinker__Start(
    const Class_Blinker* Me, 
    uint16_t nb_periods,
    uint16_t on_time,
    uint16_t off_time )
{
    My_Remaining_Nb_Periods = nb_periods;
    My_On_Time = on_time;
    My_Off_Time = off_time;
    Begin_On_Phase( Me );
}
/*----------------------------------------------------------------------------*/
void Class_Blinker__Stop( const Class_Blinker* Me )
{
    Class_Triggered_Timer__Stop( Me->My_Timer );
    My_Remaining_Nb_Periods = 0;
    My_Status = BLINKER_STOPPED;
}
/*----------------------------------------------------------------------------*/
E_Blinker_Status Class_Blinker__Get_Status( const Class_Blinker* Me )
{
    return My_Status;
}


/*============================================================================*/
/* Received events */
/*============================================================================*/
void Class_Blinker__Any_Phase_Ended( const Class_Blinker* Me )
{
    if( My_Status != BLINKER_STOPPED )
    {
        if( My_Status == BLINKER_RUNNING_ON )
        { /* The phase that has just ended were a ON phase */
            Begin_Off_Phase( Me );
            (Me->On_Phase_Ended)();
        }
        else
        { /* The phase that has just ended were a OFF phase */
            if( My_Remaining_Nb_Periods == 0 )
            { /* infinite blinking */
                Begin_On_Phase( Me );
            }
            else
            {
                My_Remaining_Nb_Periods--;
                if( My_Remaining_Nb_Periods != 0 )
                {
                    Begin_On_Phase( Me );
                }
                else
                {
                    My_Status = BLINKER_STOPPED;
                }
            }
            (Me->Off_Phase_Ended)();
        }

    }
}


/*============================================================================*/
/* Private methods definition */
/*============================================================================*/
static void Begin_On_Phase( const Class_Blinker* Me )
{
    My_Status = BLINKER_RUNNING_ON;
    Class_Triggered_Timer__Start( Me->My_Timer, My_On_Time );
}
/*----------------------------------------------------------------------------*/
static void Begin_Off_Phase( const Class_Blinker* Me )
{
    My_Status = BLINKER_RUNNING_OFF;
    Class_Triggered_Timer__Start( Me->My_Timer, My_Off_Time ); 
}