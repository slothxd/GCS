//Our headers
#include <QDebug>
#include "mainwindow.h"

#include "stdlib.h"
#include "string"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    //Set window properties
    setMinimumWidth( 900 );
    setMinimumHeight( 600 );
    setWindowTitle( "Ground Control Station" );
    setWindowFlags( Qt::CustomizeWindowHint );

    mainLayout = new QGridLayout;
    mainLayout->setMargin( 0 );

   //Statically initialize vehicles
    v46 =  new Vehicle22(46, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0);
    v46->setColor(Qt::green);
    v46->setGraphic( ":/map_ico_ugv-01.png", 0, 0, 50, 50 );

    v69 =  new Vehicle22(69, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0);
    v69->setColor(Qt::cyan);
    v69->setGraphic( ":/map_ico_uav-01.png", 0, 0, 50, 50 );

    v2 = new Vehicle22(2, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0);
    v2->setColor(Qt::green);
    v2->setGraphic( ":/map_ico_uav-01.png", 0, 0, 50, 50 );

    v101 = new Vehicle22(101, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0);
    v101->setColor(Qt::yellow);
    v101->setGraphic( ":/map_ico_uav-02.png", 0, 0, 50, 50 );

    v102 = new Vehicle22(102, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0,
               0, 0, 0);
    v102->setColor(Qt::magenta);
    v102->setGraphic( ":/map_ico_uav-02.png", 0, 0, 50, 50 );

    //Initialize Map
    initMap();

    //Initialize widgets
    quitButton = new QPushButton( this );
    quitButton->setText( "Quit" );

    serialSelect = new SerialPortSelect( this );
    sb = new sideBar(this);
    mtb = new GcsToolbar( this );
    connect(this,SIGNAL(destroyed()), mtb, SLOT(close()));

    //Initialize networking AFTER all GUI has been created
    initNetworking();

    //Initialize database
    initDatabase();

    //Add widgets to screen
    //Temp icons, make more pretty!!
    UGV_JOYSTICK = new QPushButton();
    UGV_JOYSTICK->setText("Start Joystick Control");
    UGV_JOYSTICKSTOP = new QPushButton();
    UGV_JOYSTICKSTOP->setText("Stop Joystick Control");
    Telemetry = new TelemetryGUI();
    way = new WaypointGUI();
    Authorize = new VehicleAuthorizationGUI();
    UGV_States = new UGV_state();
    UAV_Payload = new UAVPayload();
    targeting = new targetingGUI();

    sendcmd = new QPushButton();
    sendcmd->setText("Drop payload");

    //mainLayout->addWidget( quitButton, 2, 0 );
    mainLayout->addWidget( sb, 1, 0, Qt::AlignCenter|Qt::AlignRight );
    mainLayout->addWidget( serialSelect, 1, 0, Qt::AlignTop|Qt::AlignRight);
    mainLayout->addWidget( mtb, 1, 0, Qt::AlignCenter|Qt::AlignTop);

    //Temp locations & gui!!!!!!
    mainLayout->addWidget(quitButton,4,0);

    //Set up baisic C&C gui layout
    //Gridlayout to group widgets as one
    //Gridlayout : base to have the commands
    QGridLayout* base = new QGridLayout();
    //Add the widgets that have the commands
    base->addWidget(Authorize,0,0);
    base->addWidget(Telemetry,0,1);
    base->addWidget(way,0,2);
    base->addWidget(targeting,1,0);
    //Add those commands to the mainLayout
    mainLayout->addLayout(base,2,0);

    //Set up UGV gui layout
    //Gridlayout : UGV to group UGV commands
    //Gridlayout : joyLaout to group the Joystick commands
    QGridLayout* UGVLayout = new QGridLayout();
    QGridLayout* joyLayout = new QGridLayout();
    joyLayout->addWidget(UGV_JOYSTICK,0,0);
    joyLayout->addWidget(UGV_JOYSTICKSTOP,0,1);
    UGVLayout->addLayout(joyLayout,0,0);
    UGVLayout->addWidget(UGV_States,1,0);

    //Creates label for UAV status
    QLabel* uavStatLabel = new QLabel();
    //Sets text for label
    uavStatLabel->setText("CPP UAV STATUS");
   
    //Create label to display UAV status
    uavStatusLabel = new QLabel();
    //Sets text for status as "UNKNOWN"
    uavStatusLabel->setText("UNKNOWN");

    //Create a gridlayout : UAVStatus to hold the UGV status label and dipslay
    QGridLayout* UAVStatus = new QGridLayout();
    //Add uavstatus label and display to gridlayout
    UAVStatus->addWidget(uavStatLabel,0,0,Qt::AlignCenter);
    UAVStatus->addWidget(uavStatusLabel,0,1,Qt::AlignCenter);

    //Create Button for UGV drop notification
    ugvDrop = new QPushButton();
    //Set Text for button
    ugvDrop->setText("UGV notify of drop");
    //Create gridlayout : dropCMDs for the drop commands
    QGridLayout* dropCMDs = new QGridLayout();
    //Add widgets to gridlayout
    dropCMDs->addWidget(sendcmd,0,0);
    dropCMDs->addWidget(ugvDrop,0,1);

    //Set up basic UAV layout with C&C commands
    //Create gridlayout : UAVLayout for UAV commands
    QGridLayout* UAVLayout = new QGridLayout();
    //Add UAV status, and dropCMDs layouts and UAV_payload widget
    UAVLayout->addLayout(UAVStatus,0,0);
    UAVLayout->addWidget(UAV_Payload,1,0);
    UAVLayout->addLayout(dropCMDs,2,0);

    //Set up Layout for vehicle comands
    //Create gridlayout : VehicleLayout for commands
    QGridLayout* VehicleLayout = new QGridLayout();
    //Create Label for UAV commands
    QLabel* uavLabel = new QLabel();
    //Set text for label
    uavLabel->setText("UAV commands");

    //Create Label for UGV commands
    QLabel* ugvLabel = new QLabel();
    //Set Text for label
    ugvLabel->setText("UGV commands");
    //Set Alignments for the labels to be the center
    //Have the UAV label be on the left col and the UGV to be on the right col
    VehicleLayout->addWidget(uavLabel,0,0,Qt::AlignCenter);
    VehicleLayout->addWidget(ugvLabel,0,1,Qt::AlignCenter);
    //Add the layouts to the layout
    VehicleLayout->addLayout(UAVLayout,1,0);
    VehicleLayout->addLayout(UGVLayout,1,1);
    //Add the layout to the mainLayout
    mainLayout->addLayout(VehicleLayout,3,0);

    QWidget* centralWidget = new QWidget();
    centralWidget->setLayout( mainLayout );
    setCentralWidget( centralWidget );

    showMaximized();

    //mainwindow gui connect functions for networking
    connect(serialSelect,SIGNAL(serialPortSelected(QString)),network,SLOT(network_serial_set(QString)));
    //update targets
    connect(network, SIGNAL(newTarget(Target*)),this,SLOT(update_targets(Target*)));

    //TEST METHOD FOR NEW SIGNAL
    connect(network,SIGNAL(updateVechicle(int)),this,SLOT(updateVech(int)));

    //Map Interation
    //Sets coordinate positions for waypoint baised off of click on map
    connect(mv, SIGNAL(coordDesignated(double,double)), way, SLOT(coordDesignated(double,double)));


    //C&C GUI
    //General Vehicle
    connect(Authorize,SIGNAL(authorize(int)),network,SLOT(send_vehicle_auth_request(int)));
    connect(Telemetry,SIGNAL(telemetry(int)),network,SLOT(send_telemetry_command(int)));
    connect(way,SIGNAL(waypoint(int, int, int, float,float,float)),network,SLOT(send_waypoint(int, int, int, float,float,float)));
    //Manual Targeting
    connect(targeting,SIGNAL(target(float,float,float)),network,SLOT(target(float,float,float)));

    //UAV
    //Drop
    connect(sendcmd,SIGNAL(clicked()),this,SLOT(UDrop()));
    connect(ugvDrop,SIGNAL(clicked()),this,SLOT(UGVDrop()));
    connect(this,SIGNAL(drop(int)),network,SLOT(UDrop(int)));

    //Payload
    connect(UAV_Payload,SIGNAL(arm(int)),network,SLOT(arm(int)));
    connect(UAV_Payload,SIGNAL(disarm(int)),network,SLOT(disarm(int)));

    //UGV
    //JOYSTICK
    connect(UGV_JOYSTICK,SIGNAL(clicked()),network,SLOT(start_UGV_Joystick()));
    connect(UGV_JOYSTICKSTOP,SIGNAL(clicked()),network,SLOT(stop_UGV_Joystick()));

    //UGV
    //STATE CHANGE
    connect(UGV_States,SIGNAL(AutoToManual()),network,SLOT(AutoToManual()));
    connect(UGV_States,SIGNAL(ManualToAuto()),network,SLOT(ManualToAuto()));
    connect(UGV_States,SIGNAL(Reset()),network,SLOT(Reset()));

    //MOTOR states
    connect(UGV_States,SIGNAL(DisableMotor()),network,SLOT(DisableMotor()));
    connect(UGV_States,SIGNAL(ToggleMotor()),network,SLOT(ToggleMotor()));
    connect(UGV_States,SIGNAL(EnableMotor()),network,SLOT(EnableMotor()));

    //Connect sidebar to map view layers
    connect(sb, SIGNAL(uavOn(bool)), mv, SLOT(uavLayerOn(bool)));
    connect(sb, SIGNAL(ugvOn(bool)), mv, SLOT(ugvLayerOn(bool)));
    connect(sb, SIGNAL(satelliteOn(bool)), mv, SLOT(satelliteLayerOn(bool)));
    connect(sb, SIGNAL(waypointOn(bool)), mv, SLOT(waypointLayerOn(bool)));
    connect(sb, SIGNAL(opspaceOn(bool)), mv, SLOT(opspaceLayerOn(bool)));
    connect(sb, SIGNAL(targetOn(bool)), mv, SLOT(targetLayerOn(bool)));
}

void MainWindow::initMap(){

    mv = new MapView( this );

    connect(mv, SIGNAL(MapReady()), this, SLOT(mapReady()));

    mainLayout->addWidget( mv->m_mapGraphicsView, 1, 0 );
}

//Test slot for new signal
void MainWindow::updateVech(int ID)
{
    //qDebug() << "Update at pos " << pos;

    int vehicle_ID = ID;
    qDebug() << "ID is" << vehicle_ID;
    //Temporary code=========================
    if(vehicle_ID == 2)
    {
        qDebug() << "vehicle 2";
//       qDebug() << (std::to_string(v3->getLatitude())).c_str();
//       qDebug() << (std::to_string(v3->getLongitude())).c_str();
//       qDebug() << v2->getPoint().x() << " " << v2->getPoint().y();
         v2->setPoint(mv->decimalDegreesToPoint(vList22->get(ID)->getLatitude() , vList22->get(ID)->getLongitude()));
         mv->moveVehicleGraphic(*v2, EsriRuntimeQt::Point(v2->getPoint().x(), v2->getPoint().y()));
         v2->setAngle(v2->getZVelocity());
     }
    emit update_vehicle(vehicle_ID);
}

void MainWindow::initNetworking(){

    //Setting up networking
    //Create and set up vehicle list
    Vehicle22 *vehicle = new Vehicle22();
    vehicle->setVehicleType(46);

    //Statically add specified vehicles to list
    vList22 = new vehicle_list();
    vList22->append(v46);
    vList22->append(v69);
    vList22->append(v2);
    vList22->append(v101);
    vList22->append(v102);

    vUpdate = new NodeQueue();
    targetList = new TargetList();
    network = new networking(vList22,vUpdate,targetList);
    connect(network,SIGNAL(update_queue()),this,SLOT(update_vehicle_queue()));
    connect(network,SIGNAL(vehicleStatus(int,int)),this,SLOT(vStatus(int,int)));
                                   //lat, long
    connect(network, SIGNAL(vTarget(float,float)), this, SLOT( addTarget(float,float)));
    //connect(this,SIGNAL(update_vehicle(int)), vListGUI ,SLOT((int)));
}

void MainWindow::initDatabase(){
    database = new DataDaemon();
}

void MainWindow::initWidgets(){

}

//REMOVE ALL OLD QUEUE SYSTEM, USE AS REFERENCE TO CHANGE GRAPHICS
void MainWindow::update_vehicle_queue()
{
//   if(vUpdate->isEmpty())
//   {
//       qDebug() << "Queue is empty";
//   }
//   int vehicle_ID = vUpdate->dequeue();

//   for(int i = 1; i < vList22->length(); i++){
//       if(vList22->set(i)->getVehicleID() == vehicle_ID)
//       {
//           //Temporary code=========================
//           if(vehicle_ID == 46)
//           {
////               v46->setGraphic( ":/images/ugv_icon.png", 0, 0, 50, 50 );
//               //printf("%f %f\n",v69->getLatitude(), v69->getLongitude());
//               v46->setPoint(mv->decimalDegreesToPoint(vList22->set(i)->getLatitude() , vList22->set(i)->getLongitude()));
//               mv->moveVehicleGraphic(*v46, EsriRuntimeQt::Point(v46->getPoint().x(), v46->getPoint().y()));
//               v46->setAngle(v46->getZVelocity());
//           }
//           if(vehicle_ID == 69)
//           {
//               /*Moved graphic due to twin images appearing if placed in origonal spot*/
////               v69->setGraphic( ":/images/uav_icon.png", 0, 0, 50, 50 );
//               //printf("%f %f\n",v69->getLatitude(), v69->getLongitude());
//               //qDebug() << v69->getLatitude() << " " << v69->getLongitude()<< " " << v69->getHeading();
//               //qDebug() << vList22->at(i)->getLatitude() << " " << vList22->at(i)->getLongitude() << v2->getHeading();

//               //v1->setPoint(mv->decimalDegreesToPoint(34.0575057, -117.8204004));
//               v69->setPoint(mv->decimalDegreesToPoint(vList22->set(i)->getLatitude() , vList22->set(i)->getLongitude()));
//               //qDebug() << v69->getPoint().x() << " " << v69->getPoint().y();
//               mv->moveVehicleGraphic(*v69, EsriRuntimeQt::Point(v69->getPoint().x(), v69->getPoint().y()));
//               mv->rotateVehicleGraphic(*v69, v69->getHeading());
//           }
//           if(vehicle_ID == 2)
//           {
////               qDebug() << (std::to_string(v3->getLatitude())).c_str();
////               qDebug() << (std::to_string(v3->getLongitude())).c_str();
////               qDebug() << v2->getPoint().x() << " " << v2->getPoint().y();
//                v2->setPoint(mv->decimalDegreesToPoint(vList22->set(i)->getLatitude() , vList22->set(i)->getLongitude()));
//                mv->moveVehicleGraphic(*v2, EsriRuntimeQt::Point(v2->getPoint().x(), v2->getPoint().y()));
//                v2->setAngle(v2->getZVelocity());
//            }
//           if(vehicle_ID == 101)
//           {
//               //printf("%f %f\n",v101->getLatitude(), v101->getLongitude());
//               v101->setPoint(mv->decimalDegreesToPoint(vList22->set(i)->getLatitude() , vList22->set(i)->getLongitude()));
//               mv->moveVehicleGraphic(*v101, EsriRuntimeQt::Point(v101->getPoint().x(), v101->getPoint().y()));
//               v101->setAngle(v101->getHeading());
//           }
//           if(vehicle_ID == 102)
//           {
//               //printf("%f %f\n",v102->getLatitude(), v102->getLongitude());
//               v102->setPoint(mv->decimalDegreesToPoint(vList22->set(i)->getLatitude() , vList22->set(i)->getLongitude()));
//               mv->moveVehicleGraphic(*v102, EsriRuntimeQt::Point(v102->getPoint().x(), v102->getPoint().y()));
//               v102->setAngle(v102->getHeading());
//           }
//       }
//   }
//   emit update_vehicle(vehicle_ID);
}

//Updates the displayed targets.
void MainWindow::update_targets(Target* t)
{
    qDebug() << "Latitude is:" << t->getLatitude();
    qDebug() << "Longitude is:" << t->getLongitude();
    //t->setGraphic(Qt::red,EsriRuntimeQt::SimpleMarkerSymbolStyle::Cross,t->getLatitude()*10000000,t->getLongitude()*10000000,10);
    //t->setGraphicID(mv->addGraphicToLayer(t->getGraphic()));
}

//Manually drop UAV and alert UGV of drop
void MainWindow::UDrop()
{
    emit drop(69);
}

void MainWindow::UGVDrop()
{
    emit drop(46);
}

void MainWindow::mapReady(){

//    qDebug() << "Adding v46";
    mv->addGraphicToLayer( v46->getGraphic() );
//    qDebug() << "Added " << v46->getGraphicID();
    connect(v46, SIGNAL(updateWaypointGraphics(Waypoint22*)), mv->getVehicleLayer(), SLOT(updateWaypointGraphics( Waypoint22*)));
    connect(v46, SIGNAL(addWaypointGraphic(Waypoint22*, QColor)), mv->getVehicleLayer(), SLOT(addWaypointToGCS(Waypoint22*, QColor)));
    connect(v46, SIGNAL(removeWaypointGraphic(int, int)), mv->getVehicleLayer(), SLOT(removeWaypointGraphic(int, int)));

//    qDebug() << "Adding v69";
    mv->addGraphicToLayer( v69->getGraphic() );
//    qDebug() << "Added " << v69->getGraphicID();
    connect(v69, SIGNAL(updateWaypointGraphics(Waypoint22*)), mv->getVehicleLayer(), SLOT(updateWaypointGraphics( Waypoint22*)));
    connect(v69, SIGNAL(addWaypointGraphic(Waypoint22*, QColor)), mv->getVehicleLayer(), SLOT(addWaypointToGCS(Waypoint22*, QColor)));
    connect(v69, SIGNAL(removeWaypointGraphic(int, int)), mv->getVehicleLayer(), SLOT(removeWaypointGraphic(int, int)));

//    qDebug() << "Adding v2";
    mv->addGraphicToLayer( v2->getGraphic() );
//    qDebug() << "Graphic " << v2->getGraphic().isEmpty();
//    qDebug() << "Added " << v2->getGraphicID();
    connect(v2, SIGNAL(updateWaypointGraphics(Waypoint22*)), mv->getVehicleLayer(), SLOT(updateWaypointGraphics( Waypoint22*)));
    connect(v2, SIGNAL(addWaypointGraphic(Waypoint22*, QColor)), mv->getVehicleLayer(), SLOT(addWaypointToGCS(Waypoint22*, QColor)));
    connect(v2, SIGNAL(removeWaypointGraphic(int, int)), mv->getVehicleLayer(), SLOT(removeWaypointGraphic(int, int)));

//    qDebug() << "Adding v101";
    mv->addGraphicToLayer( v101->getGraphic() );
    connect(v101, SIGNAL(updateWaypointGraphics(Waypoint22*)), mv->getVehicleLayer(), SLOT(updateWaypointGraphics( Waypoint22*)));
    connect(v101, SIGNAL(addWaypointGraphic(Waypoint22*, QColor)), mv->getVehicleLayer(), SLOT(addWaypointToGCS(Waypoint22*, QColor)));
    connect(v101, SIGNAL(removeWaypointGraphic(int, int)), mv->getVehicleLayer(), SLOT(removeWaypointGraphic(int, int)));

//    qDebug() << "Adding v102";
    mv->addGraphicToLayer( v102->getGraphic() );
    connect(v102, SIGNAL(updateWaypointGraphics(Waypoint22*)), mv->getVehicleLayer(), SLOT(updateWaypointGraphics( Waypoint22*)));
    connect(v102, SIGNAL(addWaypointGraphic(Waypoint22*, QColor)), mv->getVehicleLayer(), SLOT(addWaypointToGCS(Waypoint22*, QColor)));
    connect(v102, SIGNAL(removeWaypointGraphic(int, int)), mv->getVehicleLayer(), SLOT(removeWaypointGraphic(int, int)));

}

/**
 * @brief MainWindow::addVehicle Add a new vehicle to our list of observable vehicles
 * @param vech vehicle ID number
 * @param type type of vehicle
 */
void MainWindow::addVehicle(int vech, int type)
{
    //TODO: graphics!!!!!!1
    /*0 - default
      1 - UAV
      2 - UGV */
    Vehicle22 *v = new Vehicle22();
    v->setVehicleID(vech);
    v->setVehicleType(type);
    switch(vech)
    {
        case 1:
            v->setGraphic( ":/images/uav_icon.png", 0, 0, 50, 50 );
            break;

        case 2:
            v->setGraphic( ":/images/ugv_icon.png", 0, 0, 50, 50 );
            break;

        default:
            break;
    }
    vList22->append(v);
}

/**
 * @brief MainWindow::vStatus Displayes vehcile status
 * @param vech vehicle type
 * @param mode current mode of vehicle
 */
void MainWindow::vStatus(int vech, int mode)
{
    switch(mode)
    {
        case 0:
            uavStatusLabel->setText("Startup");
            break;

        case 1:
            uavStatusLabel->setText("Manual Mode");
            break;
        case 2:
            uavStatusLabel->setText("Assisted Mode");
            break;

        case 3:
            uavStatusLabel->setText("Autonomous Mode");
            break;

        case 4:
            uavStatusLabel->setText("Collision Avoidence Mode");
            break;

        case 5:
             uavStatusLabel->setText("Seek & Destroy");
             break;

        default:
             uavStatusLabel->setText("Unknown Status Recieved");
    }
    /*
     * switch(status)
     * {
     *     case 0:
     *       uavStatusLabel->setText("In state");
     *     case 1:
     *       uavStatusLabel->setText("Ready");
     * }
     */
}

void MainWindow::keyPressEvent(QKeyEvent* event){

    switch(event->key()){
        case Qt::Key_A:
            //34.0575057,-117.8204004 Pomona
            v69->setPoint(EsriRuntimeQt::Point(v69->getPoint().x() - 100000, v69->getPoint().y()));
            mv->moveVehicleGraphic(*v69, EsriRuntimeQt::Point(v69->getPoint().x(), v69->getPoint().y()));
            break;
        case Qt::Key_S:
            v2->setPoint(EsriRuntimeQt::Point(v2->getPoint().x(), v2->getPoint().y() - 100000));
            mv->moveVehicleGraphic(*v2, EsriRuntimeQt::Point(v2->getPoint().x(), v2->getPoint().y()));
            break;
        case Qt::Key_W:
            v46->setPoint(EsriRuntimeQt::Point(v46->getPoint().x(), v46->getPoint().y() + 100000));
            mv->moveVehicleGraphic(*v46, EsriRuntimeQt::Point(v46->getPoint().x(), v46->getPoint().y()));
            break;
        case Qt::Key_D:
            v2->setPoint(EsriRuntimeQt::Point(v2->getPoint().x() + 100000, v2->getPoint().y()));
            mv->moveVehicleGraphic(*v2, EsriRuntimeQt::Point(v2->getPoint().x(), v2->getPoint().y()));
            break;
        case Qt::Key_I:
            mv->rotateVehicleGraphic(*v2, 45);
            break;
        default:
            //Do nothing
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event){
    switch(event->key()){
        case Qt::Key_A:
            break;
        default:
            //Do nothing
            break;
    }
}

/* BEGIN SLOTS */

void MainWindow::addTarget(float lat, float lon){
    Target target(lat, lon, 0, 0, 0, 0);
    target.setGraphic(Qt::red, EsriRuntimeQt::SimpleMarkerSymbolStyle::X,
                      mv->decimalDegreesToPoint(lat, lon), 20);
    mv->addGraphicToLayer(target.getGraphic());
}

/* END SLOTS */

MainWindow::~MainWindow(){
    //delete widget;?
}
