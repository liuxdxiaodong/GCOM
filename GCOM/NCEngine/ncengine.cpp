#include "ncengine.h"

namespace Lamp
{
	NCEngine::NCEngine(
		QObject* parent
		)
		: QObject(parent),
		iIsOpened(false),
		iIP(LOCAL_HOST),
		iPort(DEFAULT_PORT),
		iTcpSocket(NULL),
		iWorkMode(NCWM_Unknown),
		iXAxis(0),
		iAAxis(0),
		iYAxis(0),
		iBAxis(0),
		iZAxis(0),
		iCAxis(0)
	{
		this->iTcpSocket = new QTcpSocket(this);
		connect(this->iTcpSocket, SIGNAL(readyRead()), this, SLOT(response()));
	}

	NCEngine::~NCEngine()
	{
		this->close();
		delete this->iTcpSocket;
		this->iTcpSocket = NULL;
	}

	void NCEngine::open(
		const QString& ip,
		quint16 port
		)
	{
		if(this->iIsOpened)
		{
			this->close();
		}
		this->iIP = ip;
		this->iPort = port;
		this->iTcpSocket->connectToHost(this->iIP, this->iPort);
		this->iIsOpened = this->iTcpSocket->waitForConnected();
	}

	void NCEngine::close()
	{
		if(!this->iIsOpened)
		{
			return;
		}
		this->iTcpSocket->disconnectFromHost();
		this->iTcpSocket->waitForDisconnected();
		this->iTcpSocket->close();
		this->iIsOpened = false;
	}

	void NCEngine::request(
		const QString& content
		)
	{
		QTcpSocket::SocketState state = this->iTcpSocket->state();
		if(QTcpSocket::ConnectedState == state)
		{
			this->iTcpSocket->write(content.toLatin1());
			this->iTcpSocket->waitForBytesWritten();
		}
	}

	void NCEngine::response()
	{
		QString content;
		while(this->iTcpSocket->canReadLine())
		{
			content += this->iTcpSocket->readLine();
			content += "\n";
		}
		emit this->onResponse(content);
	}

	void NCEngine::currentPos()
	{
		QString content = "<axes><req>yes</req><auto>yes</auto><st>nc1</st><time>100</time><sub>pos</sub></axes>";
		content += "\n"; // 固定的结束标记
		this->request(content);
	}

	void NCEngine::runJob()
	{
		// 让GNC60选择程序
		// <select>表示选择程序
		// <sub>exe</sub>表示选择的程序用于运行
		// <level>file</level>此处固定，用于保留兼容或扩展
		// <st>nc1</st>命令的结束通道
		// <name>NCJob.nc</name>程序名
		// <path>D:\GNC60\GNCShared\</path>程序路径
		QString content = "<select><sub>exe</sub><level>file</level><st>nc1</st><name>"
			+ JOB_FILENAME
			+ "</name><path>"
			+ "\\\\" + this->iIP + "\\" + SHARED_FOLDER + "\\"
			+ "</path><req>yes</req></select>";
		content += "\n"; // 固定的结束标记
		this->request(content);
		// 让GNC60执行刚刚选择的程序
		content = "<mode><req>yes</req><st>nc1</st><sub>start</sub></mode>";
		content += "\n"; // 固定的结束标记
		this->request(content);
	}

	void NCEngine::reset()
	{
		QString content = "<mode><req>yes</req><st>nc1</st><sub>reset</sub></mode>";
		content += "\n"; // 固定的结束标记
		this->request(content);
	}

	const NCWorkMode& NCEngine::getWorkMode() const
	{
		return this->iWorkMode;
	}

	void NCEngine::setWorkMode(
		const NCWorkMode& mode
		)
	{
		if(mode == this->iWorkMode)
		{
			return;
		}
		QString content;
		switch(mode)
		{
		case NCWM_Man:
			{
				content = "<mode><req>yes</req><st>nc1</st><sub>man</sub></mode>";
				content += "\n"; // 固定的结束标记
				this->request(content);
			}
			break;
		case NCWM_Auto:
			{
				content = "<mode><req>yes</req><st>nc1</st><sub>auto</sub></mode>";
				content += "\n"; // 固定的结束标记
				this->request(content);
			}
			break;
		default:
			break;
		}
		this->iWorkMode = mode;
	}

	double NCEngine::getXAxis() const
	{
		return this->iXAxis;
	}

	void NCEngine::setXAxis(
		double value
		)
	{
		this->iXAxis = value;
	}

	double NCEngine::getAAxis() const
	{
		return this->iAAxis;
	}

	void NCEngine::setAAxis(
		double value
		)
	{
		this->iAAxis = value;
	}

	double NCEngine::getYAxis() const
	{
		return this->iYAxis;
	}

	void NCEngine::setYAxis(
		double value
		)
	{
		this->iYAxis = value;
	}

	double NCEngine::getBAxis() const
	{
		return this->iBAxis;
	}

	void NCEngine::setBAxis(
		double value
		)
	{
		this->iBAxis = value;
	}

	double NCEngine::getZAxis() const
	{
		return this->iZAxis;
	}

	void NCEngine::setZAxis(
		double value
		)
	{
		this->iZAxis = value;
	}

	double NCEngine::getCAxis() const
	{
		return this->iCAxis;
	}

	void NCEngine::setCAxis(
		double value
		)
	{
		this->iZAxis = value;
	}

	void NCEngine::axisINC(const QString& axis, const QString& step, const QString& PorN)
	{
		QString content = "<selax><req>yes</req><st>nc1</st><sub>"
			+ step
			+ "</sub><axis>"
			+ axis
			+ "</axis><direction>"
			+ PorN
			+ "</direction></selax>";
		content += "\n"; // 固定的结束标记
		this->request(content);
	}

	void NCEngine::axisCON(const QString& axis, const QString& PorN)
	{
		QString content = "<selax><req>yes</req><st>nc1</st><sub>jog</sub><axis>"
			+ axis
			+ "</axis><direction>"
			+ PorN
			+ "</direction></selax>";
		content += "\n"; // 固定的结束标记
		this->request(content);
	}



	void NCEngine::toolcircle(double mea_pos,
		double toolR,
		int frame)
	{
		QString filePath = "\\\\" + this->iIP + "\\" + SHARED_FOLDER + "\\" + JOB_FILENAME;
		QFile file(filePath);
		if(!file.open(QFile::Text | QFile::WriteOnly))
		{
			return;
		}

		double measuring_position = -mea_pos;
		double photonum = 2*PI*toolR*8/3;  //4photos each 3mm 
		double temp = 360*60/photonum;
		double rotation_speed = temp * frame;  

		QTextStream stream(&file);
		QStringList blockList;
		blockList.append(QString("N10 G91"));
		blockList.append(QString("N20 G00 X%1").arg(measuring_position));
		blockList.append(QString("N30 G01 A-360 F%1").arg(rotation_speed));
		blockList.append(QString("N40 G00 X%1 A360").arg(-measuring_position));
		blockList.append(QString("N50 M30"));
		for(QStringList::const_iterator ncIter = blockList.begin(); ncIter != blockList.end(); ++ncIter)
		{
			stream << *ncIter << "\n";
		}
		file.close();
	} 
	void NCEngine::toolcutlen(double helixAgl,
		double toolR,
		double cutEdgelen,
		int frame)
	{
		QString filePath = "\\\\" + this->iIP + "\\" + SHARED_FOLDER + "\\" + JOB_FILENAME;
		QFile file(filePath);
		if(!file.open(QFile::Text | QFile::WriteOnly))
		{
			return;
		}
		double rotation_angle = -(cutEdgelen * tan(helixAgl*PI/180)) / 
			(2 * PI * toolR) * 360;
		double photonum = 24*10/3;  //4photos each 3mm 
		double temp = 24*60/photonum;
		double rotation_speed = temp * frame;

		QTextStream stream(&file);
		QStringList blockList;
		blockList.append(QString("N10 G91"));
		blockList.append(QString("N20 #5=0"));
		blockList.append(QString("N30 WHILE[[#5*90] LT 360] DO"));
		blockList.append(QString("N40 G00 A90"));
		blockList.append(QString("N50 G01 X%1 A%2 F%3").arg(-cutEdgelen).arg(rotation_angle).arg(rotation_speed));
		blockList.append(QString("N60 G00 X%1 A%2").arg(cutEdgelen).arg(-rotation_angle));
		blockList.append(QString("N70 #5 = #5 + 1"));
		blockList.append(QString("N80 ENDWHILE"));
		blockList.append(QString("N90 G00 A-360"));
		blockList.append(QString("N100 M30"));

		for(QStringList::const_iterator ncIter = blockList.begin(); ncIter != blockList.end(); ++ncIter)
		{
			stream << *ncIter << "\n";
		}

		file.close();

	}
	void NCEngine::toolEdgecircle(double mea_pos,
		double toolR, 
		int frame)
	{
		QString filePath = "\\\\" + this->iIP + "\\" + SHARED_FOLDER + "\\" + JOB_FILENAME;
		QFile file(filePath);
		if(!file.open(QFile::Text | QFile::WriteOnly))
		{
			return;
		}
		double measuring_position = -mea_pos;
		double photonum = 2*PI*toolR*8/3;          //4photos each 3mm
		double temp = 360*60/photonum;
		double rotation_speed = temp * frame;

		QTextStream stream(&file);
		QStringList blockList;
		blockList.append(QString("N10 G91"));
		blockList.append(QString("N20 G00 X%1 Y%2 Z%3").arg(measuring_position).arg(toolR).arg(-toolR));
		blockList.append(QString("N30 G01 A-360 F%1").arg(rotation_speed));
		blockList.append(QString("N40 G00 X%1 Y%2 Z%3").arg(-measuring_position).arg(-toolR).arg(toolR));
		blockList.append(QString("N50 M30"));
		for(QStringList::const_iterator ncIter = blockList.begin(); ncIter != blockList.end(); ++ncIter)
		{
			stream << *ncIter << "\n";
		}
		file.close();
	}

}
