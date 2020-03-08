/* lls_filter.c */


#include <obs-module.h>
#include <stdio.h>
#include <obs.h>
#include <lsl_c.h>

struct lsl_filter {
	obs_source_t *source;
	int frame_number;
	char string_marker[10];
	lsl_streaminfo info;
	lsl_outlet outlet;
};

int STATUS = 0;

void set_status(int new_status){
	STATUS = new_status; 
}

static const char *filter_getname(void *unused)
{
	UNUSED_PARAMETER(unused);
	return "LSL-Filter";
}
static void filter_destroy(void *data)
{
}

static void *filter_create(obs_data_t *settings, obs_source_t *source)
{
	struct lsl_filter *lsl = bzalloc(sizeof(struct lsl_filter));
	lsl->frame_number = 0;
	lsl->info = lsl_create_streaminfo("test","Markers", 1, LSL_IRREGULAR_RATE, cft_int32, NULL);
	lsl->outlet = lsl_create_outlet(lsl->info, 0, 360);
	UNUSED_PARAMETER(settings);


	return lsl;
}

struct obs_source_frame *lsl_filter_data(void *data, struct obs_source_frame *frame){
	struct lsl_filter *lsl = data;
	if(STATUS == 1){
		int32_t tab[1];
		tab[0] = (int) lsl->frame_number;
		lsl_push_sample_i(lsl->outlet, tab);
		lsl->frame_number ++;
	}
	return frame;
}

struct obs_source_info lsl_filter = {
	.id = "lsl_filter",
	.type = OBS_SOURCE_TYPE_FILTER,
	.output_flags = OBS_SOURCE_ASYNC_VIDEO,
	.get_name = filter_getname,
	.create = filter_create,
	.destroy = filter_destroy,
	.filter_video = lsl_filter_data,
};


