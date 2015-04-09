#ifndef LAMP_NCENGINE_H
#define LAMP_NCENGINE_H

#include "ncdef.h"
#include <QtCore/QFile>
#include <QtCore/QQueue>
#include <QtCore/QTextStream>
#include <QtNetwork/QTcpSocket>
#include <fstream>

#define PI 3.1415926
namespace Lamp
{
    class NCENGINE_EXPORT NCEngine : public QObject
    {
        Q_OBJECT

    signals:
        void onResponse(
            QString content
            );

    public:
        NCEngine(
            QObject* parent = 0
            );
        ~NCEngine();

    public slots:
        void open(
            const QString& ip = LOCAL_HOST,
            quint16 port = DEFAULT_PORT
            );
        void close();
        void request(
            const QString& content
            );
        void response();
        void runJob();
        void reset();

    public:
        const NCWorkMode& getWorkMode() const;
        void setWorkMode(
            const NCWorkMode& mode
            );
        double getXAxis() const;
        void setXAxis(
            double value
            );
        double getAAxis() const;
        void setAAxis(
            double value
            );
        double getYAxis() const;
        void setYAxis(
            double value
            );
        double getBAxis() const;
        void setBAxis(
            double value
            );
        double getZAxis() const;
        void setZAxis(
            double value
            );
        double getCAxis() const;
        void setCAxis(
            double value
            );
        void axisINC(const QString& axis, const QString& step, const QString& PorN);
        void axisCON(const QString& axis, const QString& PorN);
        void currentPos();
 
		void toolcircle(
			double mea_pos,
			double toolR,
			int frame);
		void toolcutlen(
			double helixAgl,
	        double toolR,
			double cutEdgelen,
			int frame);
		void toolEdgecircle(
			double mea_pos,
	        double toolR, 
			int frame);

    private:
        bool iIsOpened;
        QString iIP;
        quint16 iPort;
        QTcpSocket* iTcpSocket;
        NCWorkMode iWorkMode;
        double iXAxis;
        double iAAxis;
        double iYAxis;
        double iBAxis;
        double iZAxis;
        double iCAxis;
    };
}

#endif // LAMP_NCENGINE_H