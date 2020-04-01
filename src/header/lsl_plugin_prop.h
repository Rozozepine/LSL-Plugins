#ifndef LSL_PROP
#define LSL_PROP

#include <QDialog>
#include "obs.h"

struct lsl_upadte_data{
    QString id_name;
	bool stream;
	bool record;
};


namespace Ui {
    class LSLProperties;
}

class LSLProperties : public QDialog
{
    Q_OBJECT
public:
    explicit LSLProperties(QWidget *parent = 0);
    ~LSLProperties();
	void SetVisable();
	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);
	void EnableOptions(bool enable);
	void ShowWarning(bool show);

private Q_SLOTS:
	void onStart();
	void onStop();
private:
    Ui::LSLProperties *ui;
	struct obs_video_info video_info;
	struct lsl_upadte_data update_data;
	QString scene_name;
	void UpdateParameter();
	void SaveSetting();
};

#endif