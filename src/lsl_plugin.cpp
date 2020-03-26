/* Rose Defossez */

/* LLS-Plugin */
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs.h>
#include "header/lsl_output.h"



#include <stdlib.h>
#include <stdio.h>


OBS_DECLARE_MODULE()





void obs_module_unload(void){

}

void obsstudio_frontend_event_callback(enum obs_frontend_event event, void *private_data){
        if(event == OBS_FRONTEND_EVENT_RECORDING_STARTED)
        {       
                lsl_output_enable();
                start_send();

        }else if (event == OBS_FRONTEND_EVENT_RECORDING_STOPPED)
        {
                lsl_output_disable();
                stop_send();
        }
        
}
bool obs_module_load(void)
{    
        obs_frontend_add_event_callback(obsstudio_frontend_event_callback, 0);
        lsl_output_init();
        return true;
}