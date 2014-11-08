#include "include/database/datadaemon.h"

datadaemon::datadaemon(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Attempting to open database";
    db = QSqlDatabase::addDatabase("QSQLITE");                                                      // Create the SQLite connection
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.db");        // Location of SQLite database (User home folder).  Will later change.
    qDebug() << "Database made in: " << QDir::homePath() + QDir::separator() + "database.db";

    if(db.open()){      
        qDebug() << "Database opened successfully.";

        if (!db.tables().contains("log")) {                                                                           // Check if database already exists.  If not, populate table "log"
            qDebug() << "Database is not populated.  Populating now...";

            QString queryString = QString("CREATE TABLE IF NOT EXISTS log(updatedon DATETIME, vehid INTEGER, vehtype INTEGER, latitude REAL, longitude REAL, altitude INTEGER, heading REAL, waypointid INTEGER, waypointtype INTEGER, xacc REAL, yacc REAL, rollrate REAL, pitchrate REAL, yawrate REAL, velocity REAL, roll REAL, pitch REAL, yaw REAL, mode INTEGER, state INTEGER, battstatus INTEGER);");
            QSqlQuery query(queryString);
        }

        else {
            qDebug() << "Database pre-existed.  Continuing without change...";
        }

        db.close();
    }
    else{
        qDebug() << "FATAL ERROR OPENING DATABASE";
    }
}

void datadaemon::log(QVector<Vehicle> &vehicleStore)
{
    for (int i = 0; i < vehicleStore.size(); i++) {
        if (vehicleStore[i].getNeedsUpdate()) {
            db.open();
        
            if ( !db.open() ) {                        // Check if database opened correctly
                qDebug() << db.lastError();
                qFatal( "Failed to connect." );
            }
        
            qDebug( "Database connected successfully.");        // Log correct opening
            
            //QString queryString = QString("INSERT INTO log (vehid, vehtype, latitude, longitude, altitude, heading, waypointid, waypointtype, xacc, yacc, rollrate, pitchrate, yawrate, velocity, roll, pitch, yaw, mode, state, battstatus) VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16', '%17', '%18', '%19', '%20')").arg(curr.getVehicleID()).arg(curr.getVehicleType()).arg(curr.getLatitude()).arg(curr.getLongitude()).arg(curr.getAltitude()).arg(curr.getHeading()).arg(curr.getWayPointID()).arg(curr.getWayPointType()).arg(curr.getXAcceleration()).arg(curr.getYAcceleration()).arg(curr.getRollRate()).arg(curr.getPitchRate()).arg(curr.getYawRate()).arg(curr.getVelocity()).arg(curr.getRoll()).arg(curr.getPitch()).arg(curr.getYaw()).arg(curr.getMode()).arg(curr.getState()).arg(curr.getBatteryStatus());
            
            //QSqlQuery query(queryString);               // Cast queryString into query for SQL prep
            //query.prepare(queryString);                 // Write it!
            
            db.close();
        }
    }
}
