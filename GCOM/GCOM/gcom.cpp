#include "gcom.h"
#include "../CamBox/cambox.h"
#include "../ComPort/comport.h"
#include "../NCEngine/ncengine.h"
#include "../ImgProc/imgproc.h"
#include "gcbutton.h"
#include "gtbutton.h"
#include "imageview.h"
#include <fstream>
namespace Lamp
{
	GCOM::GCOM(
		QWidget* parent,
		Qt::WFlags flags
		)
		: QMainWindow(parent, flags),
		iComPort(NULL),
		iCamBox(NULL),
		iNCEngine(NULL),
		iRecImg(false),
		iImgIdx(0),
		iImgTimer(this)
	{
		updateCamCfg(CT_500);
		this->iUi.setupUi(this);
		this->iImgData.iOriImg = cv::Mat::zeros(CamCfg::IMAGE_HEIGHT, CamCfg::IMAGE_WIDTH, CV_8UC1);
		this->iImgData.iMdfImg = cv::Mat::zeros(CamCfg::IMAGE_HEIGHT, CamCfg::IMAGE_WIDTH, CV_8UC1);
		this->iImgData.iDspImg = cv::Mat::zeros(CamCfg::ZOOM_IMAGE_HEIGHT, CamCfg::ZOOM_IMAGE_WIDTH, CV_8UC1);
		this->initToolBtn();
		this->initAxisBtn();
		this->initCtrlBtn();
		// set connections
		connect(this, SIGNAL(imgRecv()), this, SLOT(updateImg()), Qt::QueuedConnection);
		connect(this->iUi.t1Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t2Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t3Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t4Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t5Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t6Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t7Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t8Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t9Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t10Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.t11Btn, SIGNAL(clicked(GTBtnId)), SLOT(gtClicked(GTBtnId)));
		connect(this->iUi.f1Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f2Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f3Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f4Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f5Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f6Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f7Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f8Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f9Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f10Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.f11Btn, SIGNAL(clicked(GCBtnId)), SLOT(gcClicked(GCBtnId)));
		connect(this->iUi.actQuit, SIGNAL(triggered()), this, SLOT(quit()));
		connect(this->iUi.actHelp, SIGNAL(triggered()), this, SLOT(help()));
		connect(this->iUi.actAbout, SIGNAL(triggered()), this, SLOT(about()));
		connect(this->iUi.xAxisBox, SIGNAL(valueChanged(double)), this, SLOT(xAxis(double)));
		connect(this->iUi.aAxisBox, SIGNAL(valueChanged(double)), this, SLOT(aAxis(double)));
		connect(this->iUi.yAxisBox, SIGNAL(valueChanged(double)), this, SLOT(yAxis(double)));
		connect(this->iUi.bAxisBox, SIGNAL(valueChanged(double)), this, SLOT(bAxis(double)));
		connect(this->iUi.zAxisBox, SIGNAL(valueChanged(double)), this, SLOT(zAxis(double)));
		connect(this->iUi.cAxisBox, SIGNAL(valueChanged(double)), this, SLOT(cAxis(double)));
		connect(this->iUi.runNCBtn, SIGNAL(clicked()), this, SLOT(runNC()));
		connect(this->iUi.recImgBtn, SIGNAL(clicked()), this, SLOT(recImg()));
		connect(this->iUi.loadImgBtn, SIGNAL(clicked()), this, SLOT(loadImg()));
		connect(this->iUi.runEdgeBtn, SIGNAL(clicked()), this, SLOT(runEdge()));
		connect(this->iUi.runBladeBtn, SIGNAL(clicked()), this, SLOT(runBlade()));
		connect(this->iUi.fpsBtn, SIGNAL(clicked()), this, SLOT(changeFPS()));
		this->openCam();
		this->openNC();
		this->iImgTimer.setInterval(500);
		connect(&this->iImgTimer, SIGNAL(timeout()), this, SLOT(runImg()));
	}

	GCOM::~GCOM()
	{
		this->closeCam();
		this->closeNC();
	}

	void GCOM::recvImg(
		const cv::Mat* image
		)
	{
		CopyMemory(this->iImgData.iOriImg.data, image->data, CamCfg::IMAGE_LENGTH);
		this->iUi.camView->recvImg(image);
		emit this->imgRecv();
	}

	void GCOM::updateImg()
	{
		if(this->iRecImg)
		{
			//this->iRecImg = false;
			QString fileName = "CAM_IMG_";
			if(this->iImgIdx < 10)
			{
				fileName += "00";
			}
			else if(this->iImgIdx < 100)
			{
				fileName += "0";
			}
			fileName += QString::number(this->iImgIdx);
			fileName += ".bmp";
			cv::imwrite(fileName.toStdString(), this->iImgData.iOriImg);
			++this->iImgIdx;
		}
	}

	void GCOM::gtClicked(GTBtnId id)
	{
		switch(id)
		{
		case GTBI_ZoomFit:
			this->iUi.camView->zoomFit();
			break;
		case GTBI_ZoomIn:
			this->iUi.camView->zoomIn();
			break;
		case GTBI_ZoomOut:
			this->iUi.camView->zoomOut();
			break;
		case GTBI_LightOn:
			break;
		case GTBI_LightOff:
			break;
		case GTBI_AxisUp:
			break;
		case GTBI_AxisDown:
			break;
		case GTBI_AxisLeft:
			break;
		case GTBI_AxisRight:
			break;
		default:
			break;
		}
	}

	void GCOM::gcClicked(GCBtnId id)
	{
		switch(id)
		{
		case GCBI_Home:
			this->swtichToMain();
			break;
		case GCBI_Main1:
			this->swtichToSelectCutter();
			break;
		case GCBI_Main2:
			this->swtichToMeasureCutter();
			break;
		case GCBI_Main3:
			this->swtichToSwitchWindow();
			break;
		case GCBI_Main4:
			this->swtichToOperateCAD();
			break;
		case GCBI_Cutter1:
			break;
		case GCBI_Cutter2:
			break;
		case GCBI_Cutter3:
			break;
		case GCBI_Measure1:
			break;
		case GCBI_Measure2:
			break;
		case GCBI_Measure3:
			break;
		case GCBI_Window1:
			break;
		case GCBI_Window2:
			break;
		case GCBI_Window3:
			break;
		case GCBI_CAD1:
			break;
		case GCBI_CAD2:
			break;
		case GCBI_CAD3:
			break;
		case GCBI_CAD4:
			break;
		default:
			break;
		}
	}

	void GCOM::quit()
	{
		this->close();
	}

	void GCOM::help()
	{
	}

	void GCOM::about()
	{
	}

	void GCOM::xAxis(double value)
	{
		this->iNCEngine->setWorkMode(NCWM_Man);
		this->iNCEngine->axisINC("X", "inc1", value > this->iNCEngine->getXAxis() ? "positive" : "negative");
		this->iNCEngine->setXAxis(value);
	}

	void GCOM::aAxis(double value)
	{
		this->iNCEngine->setWorkMode(NCWM_Man);
		this->iNCEngine->axisINC("A", "inc1", value > this->iNCEngine->getAAxis() ? "positive" : "negative");
		this->iNCEngine->setAAxis(value);
	}

	void GCOM::yAxis(double value)
	{
		this->iNCEngine->setWorkMode(NCWM_Man);
		this->iNCEngine->axisINC("Y", "inc1", value > this->iNCEngine->getYAxis() ? "positive" : "negative");
		this->iNCEngine->setYAxis(value);
	}

	void GCOM::bAxis(double value)
	{
		this->iNCEngine->setWorkMode(NCWM_Man);
		this->iNCEngine->axisINC("B", "inc1", value > this->iNCEngine->getBAxis() ? "positive" : "negative");
		this->iNCEngine->setBAxis(value);
	}

	void GCOM::zAxis(double value)
	{
		this->iNCEngine->setWorkMode(NCWM_Man);
		this->iNCEngine->axisINC("Z", "inc1", value > this->iNCEngine->getZAxis() ? "positive" : "negative");
		this->iNCEngine->setZAxis(value);
	}

	void GCOM::cAxis(double value)
	{
		this->iNCEngine->setWorkMode(NCWM_Man);
		this->iNCEngine->axisINC("C", "inc1", value > this->iNCEngine->getCAxis() ? "positive" : "negative");
		this->iNCEngine->setCAxis(value);
	}

	void GCOM::runNC()
	{

		this->iNCEngine->setWorkMode(NCWM_Auto);
		std::fstream file;
		file.open("test.txt",std::ios::in);
		char index;
		double posi;
		int frame;
		double helixAgl;
		double toolR;
		double cutEdgelen;
		file >> index >> posi >> helixAgl >> toolR >> cutEdgelen >> frame ;
		
		switch (index)
		{
		case '0':
			this->iNCEngine->toolcircle(posi, toolR, frame);
			break;
		case '1':
			this->iNCEngine->toolcutlen(helixAgl, toolR, cutEdgelen, frame);
			break;
		case '2':
			this->iNCEngine->toolEdgecircle(posi, toolR, frame);
			break;
		default:
			break;
		}
		file.close();
		this->iNCEngine->runJob();
	}

	void GCOM::recImg()
	{
		this->iRecImg = !this->iRecImg;
		this->iImgIdx = 0;
	}

	void GCOM::loadImg()
	{
		QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
		if(dir.isEmpty())
		{
			return;
		}
		this->iImgs.clear();
		this->loadImg(dir);
		if(this->iImgs.empty())
		{
			return;
		}
		cv::Mat* img = &this->iImgs[0];
		this->iUi.camView->recvImg(img);
	}

	void GCOM::runEdge()
	{
		this->iUi.camView->setActType(AT_Edge);
		this->iImgIdx = 0;
		this->iImgTimer.start();
	}

	void GCOM::runBlade()
	{
		this->iUi.camView->setActType(AT_Blade);
		this->iImgIdx = 0;
		this->iImgTimer.start();
	}

	void GCOM::runImg()
	{
		if(this->iImgIdx >= this->iImgs.size())
		{
			switch(this->iUi.camView->getActType())
			{
			case AT_Edge:
				this->iUi.camView->fitEdge();
				break;
			default:
				break;
			}
			this->iImgTimer.stop();
			return;
		}
		cv::Mat* img = &this->iImgs[this->iImgIdx];
		this->iUi.camView->recvImg(img);
		++this->iImgIdx;
	}

	void GCOM::changeFPS()
	{
		if(!this->iComPort)
		{
			return;
		}
		this->iComPort->changeFPS((USHORT)this->iUi.fpsBox->value());
	}

	void GCOM::openCom()
	{
		this->closeCom();
		this->iComPort = new ComPort();
		this->iComPort->open();
	}

	void GCOM::closeCom()
	{
		if(this->iComPort)
		{
			delete this->iComPort;
			this->iComPort = NULL;
		}
	}

	void GCOM::openCam()
	{
		// close current camera
		this->closeCam();
		// open camera
		//GrabMode mode = GM_FreeRunning;
		GrabMode mode = GM_TriggeredExt;
		if(GM_TriggeredExt == mode)
		{
			this->openCom();
		}
		this->iCamBox = new CamBox(1);
		if(!this->iCamBox->open(mode, this->iIdMap))
		{
			delete this->iCamBox;
			this->iCamBox = NULL;
			QMessageBox::critical(this, "GCOM", tr("Failed to open camera!"));
			return;
		}
		this->iCamBox->start();
		connect(this->iCamBox, SIGNAL(sendImg0(const cv::Mat*)), this, SLOT(recvImg(const cv::Mat*)), Qt::DirectConnection);
		this->iCamBox->startRec(0);
	}

	void GCOM::closeCam()
	{
		if(this->iCamBox)
		{
			delete this->iCamBox;
			this->iCamBox = NULL;
		}
		this->closeCom();
	}

	void GCOM::openNC()
	{
		this->closeNC();
		this->iNCEngine = new NCEngine(this);
		this->iNCEngine->open();
	}

	void GCOM::closeNC()
	{
		if(this->iNCEngine)
		{
			delete this->iNCEngine;
			this->iNCEngine = NULL;
		}
	}

	void GCOM::initToolBtn()
	{
		this->iUi.t1Btn->initButton(GTBI_ZoomFit, tr(":/GCOM/Resources/ZoomFit.png"));
		this->iUi.t2Btn->initButton(GTBI_ZoomIn, tr(":/GCOM/Resources/ZoomIn.png"));
		this->iUi.t3Btn->initButton(GTBI_ZoomOut, tr(":/GCOM/Resources/ZoomOut.png"));
		this->iUi.t4Btn->initButton(GTBI_LightOn, tr(":/GCOM/Resources/LightOn.png"));
		this->iUi.t5Btn->initButton(GTBI_LightOff, tr(":/GCOM/Resources/LightOff.png"));
	}

	void GCOM::resetTooBtn()
	{
		this->iUi.t1Btn->resetButton();
		this->iUi.t2Btn->resetButton();
		this->iUi.t3Btn->resetButton();
		this->iUi.t4Btn->resetButton();
		this->iUi.t5Btn->resetButton();
		this->iUi.t6Btn->resetButton();
		this->iUi.t7Btn->resetButton();
		this->iUi.t8Btn->resetButton();
		this->iUi.t9Btn->resetButton();
		this->iUi.t10Btn->resetButton();
		this->iUi.t11Btn->resetButton();
	}

	void GCOM::initAxisBtn()
	{
		this->iUi.upBtn->initButton(GTBI_AxisUp, tr(":/GCOM/Resources/AxisUp.png"));
		this->iUi.downBtn->initButton(GTBI_AxisDown, tr(":/GCOM/Resources/AxisDown.png"));
		this->iUi.leftBtn->initButton(GTBI_AxisLeft, tr(":/GCOM/Resources/AxisLeft.png"));
		this->iUi.rightBtn->initButton(GTBI_AxisRight, tr(":/GCOM/Resources/AxisRight.png"));
	}

	void GCOM::initCtrlBtn()
	{
		this->swtichToMain();
	}

	void GCOM::resetCtrlBtn()
	{
		this->iUi.f1Btn->resetButton();
		this->iUi.f2Btn->resetButton();
		this->iUi.f3Btn->resetButton();
		this->iUi.f4Btn->resetButton();
		this->iUi.f5Btn->resetButton();
		this->iUi.f6Btn->resetButton();
		this->iUi.f7Btn->resetButton();
		this->iUi.f8Btn->resetButton();
		this->iUi.f9Btn->resetButton();
		this->iUi.f10Btn->resetButton();
		this->iUi.f11Btn->resetButton();
	}

	void GCOM::swtichToMain()
	{
		this->resetCtrlBtn();
		this->iUi.f1Btn->initButton(GCBI_Main1, tr(":/GCOM/Resources/Main1.png"), tr("Select\nCutter"), tr("F1"));
		this->iUi.f2Btn->initButton(GCBI_Main2, tr(":/GCOM/Resources/Main2.png"), tr("Measure\nCutter"), tr("F2"));
		this->iUi.f3Btn->initButton(GCBI_Main3, tr(":/GCOM/Resources/Main3.png"), tr("Switch\nWindow"), tr("F3"));
		this->iUi.f4Btn->initButton(GCBI_Main4, tr(":/GCOM/Resources/Main4.png"), tr("CAD\nOperation"), tr("F4"));
	}

	void GCOM::swtichToSelectCutter()
	{
		this->resetCtrlBtn();
		this->iUi.f1Btn->initButton(GCBI_Home, tr(":/GCOM/Resources/GCOM.png"), tr("Back\nHome"), tr("F1"));
		this->iUi.f2Btn->initButton(GCBI_Cutter1, tr(":/GCOM/Resources/Cutter1.png"), tr("Select\nCutter"), tr("F2"));
		this->iUi.f3Btn->initButton(GCBI_Cutter2, tr(":/GCOM/Resources/Cutter2.png"), tr("Select\nCutter"), tr("F3"));
		this->iUi.f4Btn->initButton(GCBI_Cutter3, tr(":/GCOM/Resources/Cutter3.png"), tr("Select\nCutter"), tr("F4"));
	}

	void GCOM::swtichToMeasureCutter()
	{
		this->resetCtrlBtn();
		this->iUi.f1Btn->initButton(GCBI_Home, tr(":/GCOM/Resources/GCOM.png"), tr("Back\nHome"), tr("F1"));
		this->iUi.f2Btn->initButton(GCBI_Measure1, tr(":/GCOM/Resources/Measure1.png"), tr("Measure\nCutter"), tr("F2"));
		this->iUi.f3Btn->initButton(GCBI_Measure2, tr(":/GCOM/Resources/Measure2.png"), tr("Measure\nCutter"), tr("F3"));
		this->iUi.f4Btn->initButton(GCBI_Measure3, tr(":/GCOM/Resources/Measure3.png"), tr("Measure\nCutter"), tr("F4"));
	}

	void GCOM::swtichToSwitchWindow()
	{
		this->resetCtrlBtn();
		this->iUi.f1Btn->initButton(GCBI_Home, tr(":/GCOM/Resources/GCOM.png"), tr("Back\nHome"), tr("F1"));
		this->iUi.f2Btn->initButton(GCBI_Window1, tr(":/GCOM/Resources/Window1.png"), tr("Switch\nWindow"), tr("F2"));
		this->iUi.f3Btn->initButton(GCBI_Window2, tr(":/GCOM/Resources/Window2.png"), tr("Switch\nWindow"), tr("F3"));
		this->iUi.f4Btn->initButton(GCBI_Window3, tr(":/GCOM/Resources/Window3.png"), tr("Switch\nWindow"), tr("F4"));
	}

	void GCOM::swtichToOperateCAD()
	{
		this->resetCtrlBtn();
		this->iUi.f1Btn->initButton(GCBI_Home, tr(":/GCOM/Resources/GCOM.png"), tr("Back\nHome"), tr("F1"));
		this->iUi.f2Btn->initButton(GCBI_CAD1, tr(":/GCOM/Resources/CAD1.png"), tr("CAD\nOperation"), tr("F2"));
		this->iUi.f3Btn->initButton(GCBI_CAD2, tr(":/GCOM/Resources/CAD2.png"), tr("CAD\nOperation"), tr("F3"));
		this->iUi.f4Btn->initButton(GCBI_CAD3, tr(":/GCOM/Resources/CAD3.png"), tr("CAD\nOperation"), tr("F4"));
		this->iUi.f5Btn->initButton(GCBI_CAD4, tr(":/GCOM/Resources/CAD4.png"), tr("CAD\nOperation"), tr("F5"));
	}

	void GCOM::loadImg(
		const QString& dirName
		)
	{
		QDir dir(dirName);
		QStringList fileNames = dir.entryList(QStringList() << "*.bmp");
		for(size_t strIdx = 0; strIdx < fileNames.size(); strIdx += 5)
		{
			QString fileName = dirName + "\\" + fileNames[strIdx];
			cv::Mat image = cv::imread(fileName.toStdString(), 0);
			this->iImgs.push_back(image);
		}
	}
}
