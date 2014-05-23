#include "Path.h"

Path::Path() : m_looped(false)
{
}

Path* Path::instance(){
	static Path path;
	return &path;
}


Path::~Path()
{
	clear();
}

WayPoint Path::begin(){
	return m_path.begin();
}

void Path::loopOn(){
	m_looped = true;
}

void Path::loopOff(){
	m_looped = false;
}

bool Path::finished(IFollowPath *p_agent){
	return !(p_agent->getCurrentWayPoint() != m_path.end());
}

Common::Vector4 Path::currentWayPoint(IFollowPath *p_agent){
	return *(p_agent->getCurrentWayPoint());
}

inline void Path::setNextWayPoint(IFollowPath* p_agent)
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

void Path::set(PathContainer p_new_path){
	m_path = p_new_path;
}

void Path::set(const Path &p_path){
	m_path = p_path.m_path;
}

void Path::clear(){
	m_path.clear();
}

string Path::toString(){
	stringstream buffer;
	int i = 1;
	buffer << "---Path---" << endl;
	buffer << "looped: " << (m_looped ? "true" : "false") << endl;
	for (WayPoint p = m_path.begin(); p != m_path.end(); ++p, ++i){
		buffer << "point " << i << ": " << p->toString() << endl;
	}
	return buffer.str();
}

void Path::print(){
	cout << toString() << endl;
}