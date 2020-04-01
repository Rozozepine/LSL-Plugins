/* Rose Defossez */

/* LLS-Plugin */
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs.h>
#include "header/lsl_output.h"
#include "header/lsl_plugin_prop.h"
#include <QMainWindow>
#include <QAction>

#include <stdlib.h>
#include <stdio.h>


OBS_DECLARE_MODULE()



LSLProperties *lsl_prop;

void obs_module_unload(void){

}

void obsstudio_frontend_event_callback(enum obs_frontend_event event, void *private_data){
        if(event == OBS_FRONTEND_EVENT_RECORDING_STARTED)
        {       
                start_send_record();

        }else if (event == OBS_FRONTEND_EVENT_RECORDING_STOPPED)
        {
                lsl_output_disable;
                stop_send_record();
        }
        
}
bool obs_module_load(void)
{    
        obs_frontend_add_event_callback(obsstudio_frontend_event_callback, 0);
        lsl_output_init();

	QMainWindow* main_window = (QMainWindow*)obs_frontend_get_main_window();
	QAction *action = (QAction*)obs_frontend_add_tools_menu_qaction(
		"LSL plugin");
	lsl_prop = new LSLProperties(main_window);

	auto menu_cb = []
	{
		lsl_prop->setVisible(!lsl_prop->isVisible());
	};

	action->connect(action, &QAction::triggered, menu_cb);

        return true;
}