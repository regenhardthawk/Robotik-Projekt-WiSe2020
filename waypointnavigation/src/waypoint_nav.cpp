#include "waypoint_nav.h"

namespace rob_proj4{

	waypoint_nav::waypoint_nav(): //Initialisierung des Konstruktors einer Klasse
	seq(0),
	m_num_wp(0),
	m_update(false)
	{
		//Subscriber "/move_base/result", löst "mb_resultCallback" aus
		m_waypoint_sub = m_ns.subscribe<move_base_msgs::MoveBaseActionResult>("/move_base/result", 1, &waypoint_nav::mb_resultCallback, this);
		//Publisher auf "/move_base_simple/goal"
		m_waypoint_pub = m_np.advertise<geometry_msgs::PoseStamped>("/move_base_simple/goal", 1, this);
		read_waypoints(); //Einlesen der Wegpunkte
		update_waypoints(); //Erstes Publishen eines Wegpunktes
	}

/********** Callback-Funktion: Erreichen/Abbruch der Wegpunktnavigation **********/
	void waypoint_nav::mb_resultCallback(const move_base_msgs::MoveBaseActionResult::ConstPtr& msg){

		if(msg->status.status == 3){ //3: Ziel wurde vom Action Server erfolgreich angefahren.
			
			switch(m_update){ //Entscheidet, ob ein neuer Wegpunkt angefahren, oder eine Aktion ausgeführt werden soll.
				case true:
					update_waypoints();
					break;
				case false:
					std::cout << "SUCCEEDED: " << seq+1 << ". Goal Reached" << std::endl;
					action_waypoints();
					break;
				}
		}
		else{
			std::cout << "NOT SUCCEEDED: Goal not Reached or Aborted" << std::endl;
		}
	}

/********** Funktion: Einlesen der Wegpunkte aus einer .txt Datei **********/
	void waypoint_nav::read_waypoints(){

		float m_x, m_y, m_w; //Variablen für die Koordinatenübergabe
		
		std::ifstream inputfile("/home/jan/catkin_ws/src/waypointnavigation/src/waypoints.txt"); //Dateipfad
    	std::string line; //Variable für die aktuelle Zeile
		
		while (std::getline(inputfile, line)){ //Lese Zeile ein und führe Aktion bis Zeilenumbruch aus.
			for (int i = 0; i < line.size(); i++){ //Jedes einzelne Zeichen in der aktuellen Zeile durchgehen.
				if (line[i] == ',' || line[i] == '\t'){ //Ersetze alle Tabulatoren und Komma mit Leerzeichen

					line[i] = ' ';
				}	
			}

			if (line[0] != '#'){ //Wenn KEIN Kommentarzeichen "#" genutzt wurde, verarbeite aktuelle Zeile
				std::stringstream linebuffer(line); //Zwischenspeichern der aktuellen Zeile
				linebuffer >> m_num_wp >> m_x >> m_y >> m_w; //Abspeichern der Koordinaten in Zwischenvariablen
				std::cout << m_num_wp << ": " << m_x << "\t" << m_y << "\t" << m_w << std::endl; //Ausgabe der Wegpunkte

				m_wp.push_back(m_x); //x-Koordinate an Vektor hinten anhängen
				m_wp.push_back(m_y); //y-Koordinate an Vektor hinten anhängen
				m_wp.push_back((m_w*3.14)/180); //z-Achsenrotation an Vektor hinten anhängen (Umrechnung von Deg in Rad)
			}
		}
	}

/********** Funktion: Publishen eines Wegpunktes **********/
	void waypoint_nav::update_waypoints(){

		if(seq < m_num_wp){		//Nur ausführen, wenn neue Wegpunkte vorhanden sind
			geometry_msgs::PoseStamped Wegpunkt; //Objekt Wegpunkt vom Datentyp PoseStamped (Enthält Position und Orientierung)

			//Zusammebau der Nachricht für den Topic
			Wegpunkt.header.seq = seq; //Sequenz des Topics
			Wegpunkt.header.stamp = ros::Time::now(); //Aktueller Zeitstempel in ROS-Zeit
			Wegpunkt.header.frame_id = "map"; //frame_id (wichtig für RVis)
			
			Wegpunkt.pose.position.x = m_wp[(seq)*3+0]; //Eingabe der x-Koordinate
			Wegpunkt.pose.position.y = m_wp[(seq)*3+1]; //Eingabe der y-Koordinate
			Wegpunkt.pose.orientation = tf::createQuaternionMsgFromYaw(m_wp[(seq)*3+2]); //Eingabe der z-Achsenrotation mit Umrechnung in Quaternionen

			m_waypoint_pub.publish(Wegpunkt); //Publish des Wegpunktes
			m_update = false; //Kein Publishen eines neuen Wegpunktes, zunächst die Aktion
		}
		else std::cout << "All Waypoints processed" << std::endl;
	}

/********** Funktion: Aktion nach Ankunft an einem Wegpunkt **********/
	void waypoint_nav::action_waypoints(){

		if(seq < m_num_wp){
			geometry_msgs::PoseStamped Wegpunkt;	//Objekt Wegpunkt vom Datentyp PoseStamped (Enthält Position und Orientierung)

			//Zusammebau der Nachricht für den Topic
			Wegpunkt.header.seq = seq; //Sequenz des Topics
			Wegpunkt.header.stamp = ros::Time::now(); //Aktueller Zeitstempel in ROS-Zeit
			Wegpunkt.header.frame_id = "map"; //frame_id (wichtig für RViz)
			
			Wegpunkt.pose.position.x = m_wp[(seq)*3+0]; //Eingabe der x-Koordinate
			Wegpunkt.pose.position.y = m_wp[(seq)*3+1]; //Eingabe der y-Koordinate

			//Hier die Aktion: Drehung um 180° am Wegpunkt
			Wegpunkt.pose.orientation = tf::createQuaternionMsgFromYaw(m_wp[(seq)*3+2]+(180*(3.14/180)));

			m_waypoint_pub.publish(Wegpunkt); //Publish der Aktion am Wegpunkt
			seq++; //Erhöhung des Sequenzzählers um 1
		}
		m_update = true; //Nächster Wegpunkt kann gepublished werden
	}
} //end namespace rob_proj4
