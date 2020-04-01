#include "header/lsl_plugin_prop.h"
#include <obs-frontend-api.h>
#include "ui_lsl_plugin_prop.h"
#include <util/config-file.h>
#include "header/lsl_output.h"


LSLProperties::LSLProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LSLProperties)
{
    ui->setupUi(this);
    connect(ui->pushButtonStart, SIGNAL(clicked()),this, SLOT(onStart()));
	connect(ui->pushButtonStop, SIGNAL(clicked()), this, SLOT(onStop()));
	config_t* config = obs_frontend_get_global_config();
    config_set_default_bool(config, "LSL", "stream", false);
	config_set_default_bool(config, "LSL", "record", true);
	config_set_default_string(config, "LSL", "id_name", "test");
    bool stream = config_get_bool(config, "LSL", "stream");
	bool record = config_get_bool(config, "LSL", "record");
	const char *id_name = config_get_string(config, "LSL","id_name");
    ui->lineEdit->setText(id_name);
    ui->checkBoxRecord->setChecked(record);
    ui->checkBoxStream->setChecked(stream);
}

LSLProperties::~LSLProperties()
{
    delete ui;
}

void LSLProperties::SetVisable(){
	setVisible(!isVisible());
}
void LSLProperties::showEvent(QShowEvent *event)
{

}

void LSLProperties::closeEvent(QCloseEvent *event)
{
	SaveSetting();
}

void LSLProperties::onStart(){
    UpdateParameter();
    lsl_output_enable();
}

void LSLProperties::onStop(){
    lsl_output_disable();

}
void LSLProperties::UpdateParameter(){
    update_data.id_name = ui->lineEdit->text();
    update_data.record = ui->checkBoxRecord->isChecked();
    update_data.stream = ui->checkBoxStream->isChecked();

}
void LSLProperties::SaveSetting(){
	config_t* config = obs_frontend_get_global_config();
	if (config) {
        QString id_name = ui->lineEdit->text();
        bool record = ui->checkBoxRecord->isChecked();
        bool stream = ui->checkBoxStream->isChecked();
		config_set_bool(config, "LSL", "record", record);
		config_set_bool(config, "LSL", "stream", stream);
		config_set_string(config, "LSL", "id_name", id_name.toStdString().c_str());
	}
}