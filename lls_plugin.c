/* Rose Defossez */

/* LLS-Plugin */
#include <obs-module.h>

OBS_DECLARE_MODULE()

/* Implements common ini-based locale (optional) */
/* OBS_MODULE_USE_DEFAULT_LOCALE("lls-plugins","en-Us") */

extern struct obs_source_info  test_filter;  /* Defined in lls_filter.c  */


bool obs_module_load(void)
{
        obs_register_source(&test_filter);
        return true;
}