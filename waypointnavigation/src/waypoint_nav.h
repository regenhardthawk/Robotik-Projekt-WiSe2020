#include "ros/ros.h" //ROS-Standard Bibliothek
#include "geometry_msgs/PoseStamped.h" //Publisher Objekt
#include "move_base_msgs/MoveBaseActionResult.h" //Subscriber Objekt
#include <tf/tf.h> //Transformation (für Quaternionen)
#include <vector>									
#include <iostream> //C++ Bibliothek für Konsolenausgabe
#include <fstream> //Zum Auslesen der Wegpunkt-Datei
#include <string>

namespace rob_proj4
{
	class waypoint_nav
	{
	public:
		waypoint_nav();		//Standardkonstuktor

	private:

		//Callback wenn der Action-Server die Ankunft-Nachricht für einen Wegpunkt published
		void mb_resultCallback(const move_base_msgs::MoveBaseActionResult::ConstPtr& msg);

		//Funktionen zum Auslesen und Publishen der Wegpunkte. Und Aktion nach ankunft am Wegpunkt.
		void read_waypoints();
		void update_waypoints();
		void action_waypoints();

		//Handler für das abonnieren des Ergebnisses der Navigation
		ros::NodeHandle m_ns;
		ros::Subscriber m_waypoint_sub;

		//Hander für das Publishen eines Wegpunktes
		ros::NodeHandle m_np;
		ros::Publisher m_waypoint_pub;
		
		std::vector<float> m_wp; //Vektor-Objekt zum zwischenspeichern der Wegpunkte aus der Datei.
		int m_num_wp; //Zähler, wie viele Wegpunkte geladen wurden.
		int seq; //Aktueller Stand (Sequenz) der Wegpunkte.
		bool m_update; //Schalter, ob entweder ein Wegpunkt angefahren oder eine Aktion ausgeführt werden soll.
	};
}
