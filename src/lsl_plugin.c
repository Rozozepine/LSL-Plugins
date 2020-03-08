/* Rose Defossez */

/* LLS-Plugin */
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs.h>
#include "header/lsl_filter.h"



#include <stdlib.h>
#include <stdio.h>


OBS_DECLARE_MODULE()

extern struct obs_source_info lsl_filter;


void obs_module_unload(void){

}
void obsstudio_frontend_event_callback(enum obs_frontend_event event, void *private_data){
        if(event == OBS_FRONTEND_EVENT_RECORDING_STARTED)
        {       
                set_status(1);
                printf("start");

        }else if (event == OBS_FRONTEND_EVENT_RECORDING_STOPPED)
        {
                set_status(0);
                printf("stop");
        }
        
}
bool obs_module_load(void)
{       
        obs_frontend_add_event_callback(obsstudio_frontend_event_callback, 0);
        obs_register_source(&lsl_filter);
        return true;
}