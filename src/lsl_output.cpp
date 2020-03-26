#include <obs-module.h>
#include <stdio.h>
#include <obs.h>
#include <lsl_c.h>

struct lsl_output_data
{
    obs_output_t *output;
    int delay;
    int frame_number;
    int64_t lat_video_ts;
	char string_marker[10];
	lsl_streaminfo info;
	lsl_outlet outlet;
};

obs_output_t *lsl_out;
bool output_running = false;
bool output_send = false;

static const char *lsl_output_getname(void *unused){
    UNUSED_PARAMETER(unused);
    return obs_module_text("LSL Output");
};

static void lsl_output_destroy(void *data){
    output_running = false;
    output_send = false;
    struct lsl_output_data *out_data = (struct lsl_output_data*) data;
    if(out_data){
        bfree(data);
    }
}

static void *lsl_output_create(obs_data_t *settings, obs_output_t *output){
    struct lsl_output_data *data = (struct lsl_output_data *) bzalloc(sizeof(struct lsl_output_data));
    data->output = output;
    data->info = lsl_create_streaminfo("test","Markers", 1, LSL_IRREGULAR_RATE, cft_int32, "test");
    data->outlet = lsl_create_outlet(data->info, 0, 360);
    return data;
}

static bool lsl_output_start(void *data){
        struct lsl_output_data *out_data = (struct lsl_output_data*) data;
        output_running = true;
        obs_output_begin_data_capture(out_data->output,0);
        blog(LOG_INFO, "start LSL output");
        return true;
        
}
static void lsl_output_stop(void *data, uint64_t ts){
        struct lsl_output_data *out_data = (struct lsl_output_data*) data;
        obs_output_end_data_capture(out_data->output);
        output_running = false;
        output_send = false;
}



static void lsl_outuput_run(void *param, struct video_data *frame){
    if(output_running)
        return;

    struct lsl_output_data *out_data = (struct lsl_output_data*) param;
    out_data->lat_video_ts = frame->timestamp;
	int32_t tab[1];
	tab[0] = (int) out_data->frame_number;
	lsl_push_sample_i(out_data->outlet, tab);
	out_data->frame_number ++;
    
}
static obs_properties_t *lsl_output_properties(void *data)
{
        obs_properties_t *ppts = obs_properties_create();
        obs_properties_add_bool(ppts, "my_bool",
                        obs_module_text("MyBool"));
        UNUSED_PARAMETER(data);
        return ppts;
}

struct obs_output_info create_output_info()
{
	struct obs_output_info output_info = {};
    output_info.id                   = "lsl_output";
    output_info.flags                = OBS_OUTPUT_VIDEO;
    output_info.get_name             = lsl_output_getname;
    output_info.create               = lsl_output_create;
    output_info.destroy              = lsl_output_destroy;
    output_info.start                = lsl_output_start;
    output_info.stop                 = lsl_output_stop;
    output_info.raw_video            = lsl_outuput_run;
    output_info.get_properties       = lsl_output_properties;
    return output_info;
}

void lsl_output_init(){
    obs_output_info lsl_output = create_output_info();
    obs_register_output(&lsl_output);
    obs_data_t *setting = obs_data_create();
    lsl_out = obs_output_create("lsl_output", "lsl_out", setting, NULL);
    obs_data_release(setting);

}
void lsl_output_enable(){
    obs_output_start(lsl_out);
}
void lsl_output_disable(){
    obs_output_stop(lsl_out);
}
void start_send(){
	output_send = true; 
}
void stop_send(){
    output_send = false;
}