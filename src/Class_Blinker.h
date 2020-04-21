#ifndef CLASS_BLINKER_H
#define CLASS_BLINKER_H


/*============================================================================*/
/* Inclusions */
/*============================================================================*/
/* Attributes */
#include <stdint.h>


/* Associated objects */
#include "Class_Triggered_Timer.h"


/*============================================================================*/
/* Types */
/*============================================================================*/
typedef enum {
    BLINKER_RUNNING_ON,
    BLINKER_RUNNING_OFF,
    BLINKER_STOPPED
} E_Blinker_Status;


/*============================================================================*/
/* Class */
/*============================================================================*/
typedef struct {
    uint16_t Off_Time;
    uint16_t On_Time;
    E_Blinker_Status Status;
    uint16_t Remaining_Nb_Periods;
} Class_Blinker_Var;

typedef struct {

    /* Variable attributes */
    Class_Blinker_Var* var_attr;

    /* Sent events */
    void(*Off_Phase_Ended)(void);
    void(*On_Phase_Ended)(void);

    /* Associated objects */
    const Class_Triggered_Timer* My_Timer;

} Class_Blinker;


/*============================================================================*/
/* Public methods */
/*============================================================================*/
void Class_Blinker__Start(
    const Class_Blinker* Me, 
    uint16_t nb_periods,
    uint16_t on_time,
    uint16_t off_time );
void Class_Blinker__Stop( const Class_Blinker* Me );
E_Blinker_Status Class_Blinker__Get_Status( const Class_Blinker* Me );


/*============================================================================*/
/* Received events */
/*============================================================================*/
void Class_Blinker__Any_Phase_Ended( const Class_Blinker* Me );


#endif