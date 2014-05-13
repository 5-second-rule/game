#include "Path.h"


Path::Path() : m_looped(false)
{
	createRandomPath(40, 0, 0, 0, 100, 100, 100);
	vector<Vector4> v;
	v.push_back(Vector4(0, 0, 5));
	v.push_back(Vector4(0, 0, 10));
	v.push_back(Vector4(5, 0, 10));
	v.push_back(Vector4(10, 0, 40));
	v.push_back(Vector4(-10, 30, 32));
	set(v);
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

PathContainer Path::createRandomPath(int NumWaypoints,
	float MinX,
	float MinY,
	float MinZ,
	float MaxX,
	float MaxY,
	float MaxZ)
{
	m_path.clear();

	float midX = (MaxX + MinX) / 2.0f;
	float midY = (MaxY + MinY) / 2.0f;
	float midZ = (MaxZ + MinZ) / 2.0f;

	float smaller = min(midX, min(midY, midZ));

	float spacing = TwoPi / (float)NumWaypoints;

	for (int i = 0; i<NumWaypoints; ++i)
	{
		float RadialDist = (float)RandInRange(smaller*0.2f, smaller);

		Vector4 temp(RadialDist, 0.0f, 0.0f);

		temp = Common::rotateAroundOrigin(temp, i*spacing);
		temp += Vector4(midX, midY, midZ, 0);

		m_path.push_back(temp);
	}
	return m_path;
}

bool Path::finished(IFollowPath *p_agent){
	return !(p_agent->getCurrentWayPoint() != m_path.end());
}

Vector4 Path::currentWayPoint(IFollowPath *p_agent){
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
	} else {
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