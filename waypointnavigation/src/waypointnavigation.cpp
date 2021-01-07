/******************************************************************************/
/*	NodeName:	Wegpunktnavigation des TurtleBot3 in ROS
/*	Bearbeiter:	Chiara Teresa Gruß, Robin Scheel, Jan-Luca Regenhardt
/*				Hochschule für angewandte Wissenschaft und Kunst, Fak [i]
/*	Datum:		07.01.2021, 13:27 Uhr
/******************************************************************************/

#include "waypoint_nav.h" //Einbinden der Haupt-Headerdatei

int main(int argc, char **argv) //Hauptschleife
{
	ros::init(argc, argv, "waypointnavigation"); //Initialisierung des Nodes "waypointnavigation" am Master

	rob_proj4::waypoint_nav go; //Erzeugung eines Klassenobjektes (Enthält alle weiteren Aktionen)

	ros::spin(); //Endlosschleife, in welcher der Node auf Aktionen oder ein Stop wartet.
	return 0;
}