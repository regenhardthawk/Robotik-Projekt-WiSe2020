# Robotik-Projekt-WiSe2020
**Studierenden:** Chiara Teresa Gruß, Robin Scheel, Jan-Luca Regenhardt  
**Gruppe:** 4  
**Modul:** Robotik und Embedded Systems (MA)

Das Projekt Nr.3 hat zum Ziel, den mobilen Roboter TurtleBot3 der Firma ROBOTIS in der Simulationsumgebung Gazebo sequentiell Wegpunkte abfahren zu lassen. Diese Wegpunkte werden aus einer Textdatei eingelesen und abgefahren. An jedem Wegpunkt angekommen, führt der Roboter eine vorher definierte Aktion aus.

Dieses Repository beinhaltet alle notwendigen Dateien, um das Projekt nachvollziehen zu können und den Roboter Wegpunkte abfahren zu lassen.

## Inhalt
| Datei | Beschreibung|
|-------|-------------|
| turtlebot3_HAWK1.launch | ROSLAUNCH Datei zum starten von Gazebo mit dem Gabaeudemodell |
| HAWKC_Ebene1.world | Weltdatei aus Gazebo mit dem Gebaudemodell |
| Gabaeudemodell/Box1.par | Kartonmodell 600mm x 150mm x 600mm |
| Gabaeudemodell/Box2.par | Kartonmodell 500mm x 400mm x 500mm |
| Gabaeudemodell/Box3.par | Kartonmodell 300mm x 300mm x 1000mm |
| Gabaeudemodell/Grundriss.par | Grundriss-Skizze der Ebene mit Wandextrusion |
| Gabaeudemodell/HAWK_Ebene1.asm | Zusammebau Grundriss.par mit Boxen, Tischen und Schraenken |
| Gabaeudemodell/HAWK_Ebene1.dft | Zeichnung der Ebene für die Erstellung der RViz MAP |
| Gabaeudemodell/HAWK_Ebene1.stl | Mesh für den Modellimport in Gazebo |
| Gabaeudemodell/Schrank.par | Schrankmodell 1-Fach |
| Gabaeudemodell/Schrank_groß3.asm | Schrankzusammenbau 3-Fach |
| Gabaeudemodell/Schrank_groß7.asm | Schrankzusammenbau 7-Fach |
| Gabaeudemodell/Tisch.par | Tischmodell |

## Aufteilung der Arbeit
**Das Programm entstand zu gleichen Teilen in Gruppenarbeit.**
| *Kapitel*/Abschnitt | BearbeiterIn |
|-------------------|--------------|
| **Einleitung** | Ch.Gruß |
| Aufbau der Arbeit | Ch.Gruß |
| **Technische Grundlagen** | Ch.Gruß |
| Robot Operating System | R.Scheel |
| TurtleBot3 | Ch.Gruß
| Simulationsumgebung Gazebo | J.Regenhardt |
| Modellbildung | J.Regenhardt |
| Visualisierung RViz | J.Regenhardt |
| Mapping | J.Regenhardt |
| Global- und Local-Planner | Ch.Gruß |
| Pfadplanung mit Roadmap | Ch.Gruß |
| Pfadplanung mit Zellzerlegung | Ch.Gruß |
| Pfadplanung mit Potentialfeld | Ch.Gruß |
| Koordinatensystem und Wegpunkt | Ch.Gruß |
| Topic und Nodes im Robot State Maschine | R.Scheel |
| **Programmaufbau** | R.Scheel |
| Initialisierung | R.Scheel |
| Erläuterung der Funktionen | R.Scheel |
| Wegpunkte einlesen | R.Scheel |
| Wegpunkte publishen | R.Scheel |
| Wegpunktstatus | R.Scheel |
| Aktion am Wegpunkt | R.Scheel |
| **Fazit** | R.Scheel |
