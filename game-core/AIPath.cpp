#include "AIPath.h"

AIPath::AIPath() : m_looped(false)
{
}


AIPath* AIPath::instance(){
	static AIPath AIPath;
	return &AIPath;
}

AIPath::~AIPath()
{
	clear();
}


WayPoint AIPath::begin(){
	return m_path.begin();
}


void AIPath::loopOn(){
	m_looped = true;
}


void AIPath::loopOff(){
	m_looped = false;
}


bool AIPath::finished(AutonomousObject *p_agent){
	return !(p_agent->getCurrentWayPoint() != m_path.end());
}


Common::Vector4 AIPath::currentWayPoint(AutonomousObject *p_agent){
	return *(p_agent->getCurrentWayPoint());
}


inline void AIPath::setNextWayPoint(AutonomousObject* p_agent)
{
	assert(m_path.size() > 0);


	WayPoint point = p_agent->getCurrentWayPoint();
	point++;
	if (point == m_path.end()) {
		if (m_looped) {
			p_agent->setCurrentWayPoint(m_path.begin());
		}
	}
	else {
		p_agent->setCurrentWayPoint(point);
	}
}


void AIPath::set(PathContainer p_new_AIPath){
	m_path = p_new_AIPath;
}


void AIPath::set(const AIPath &p_AIPath){
	m_path = p_AIPath.m_path;
}


void AIPath::clear(){
	m_path.clear();
}


string AIPath::toString(){
	stringstream buffer;
	int i = 1;
	buffer << "---AIPath---" << endl;
	buffer << "looped: " << (m_looped ? "true" : "false") << endl;
	/*for (WayPoint p = m_path.begin(); p != m_path.end(); ++p, ++i){
		buffer << "point " << i << ": " << p->toString() << endl;
	}*/
	return buffer.str();
}


void AIPath::print(){
	cout << toString() << endl;
}
