#include "TrackPath.h"

#include <fstream>
#include <stdexcept>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

using namespace std;
using namespace Common;

TrackPath::TrackPath(){}

TrackPath::~TrackPath(){}

int TrackPath::locateIndex(Vector4 realPosition, int lastIndex) {
	PathNode lastNode = this->nodes[lastIndex];
	float lastDistance = lastNode.distanceTo(realPosition);
	int direction = lastDistance > 0 ? 1 : -1;

	if (lastDistance == 0){
		return lastIndex;
	}

	// TODO make more binary rather than linear
	int directionHere = direction;
	int index = lastIndex;

	do {
		// add size to handle negative wrap around
		index = (this->nodes.size() + index + direction) % this->nodes.size();
		PathNode node = this->nodes[index];
		float dot = node.distanceTo(realPosition);
		directionHere = dot > 0 ? 1 : -1;
	} while (direction == directionHere);

	return index;
}

PathNode TrackPath::interpolateNode(Vector4 realPosition, int closestIndex) {
	int next = (closestIndex + 1) % this->nodes.size();
	int previous = (closestIndex - 1) % this->nodes.size();

	PathNode nextNode = this->nodes[next];
	PathNode closestNode = this->nodes[closestIndex];
	PathNode previousNode = this->nodes[previous];

	PathNode destination;

	if (nextNode.distanceTo(realPosition) <= previousNode.distanceTo(realPosition)) {
		destination = nextNode;
	}
	else {
		destination = previousNode;
	}

	Vector4 pV = destination.point - closestNode.point;
	float dABC = pV.lengthSquared();
	float inc = ((realPosition.x() - closestNode.point.x())*pV.x() + (realPosition.y() - closestNode.point.y())*pV.y() + (realPosition.z() - closestNode.point.z())*pV.z()) / dABC;

	PathNode finalNode;
	finalNode.point.set(closestNode.point.x() + pV.x()*inc, closestNode.point.y() + pV.y()*inc, closestNode.point.z() + pV.z()*inc, 1.0f);
	finalNode.normal = closestNode.normal;

	return finalNode;
}

TrackPath * TrackPath::fromFile(char *file) {
	ifstream fin;
	char input;

	fin.open(file);

	if (!fin || fin.fail()) {
		throw new std::runtime_error("couldn't open track path file");
	}

	TrackPath *result = new TrackPath();

	fin.get(input);
	while (!fin.eof()) {
		if (input == 'v') {
			fin.get(input);
			if (input == ' ') {
				float x, y, z;
				fin >> x >> y >> z;
				z = z * -1.0f;

				PathNode node;
				node.point = Common::Vector4(x, y, z, 1.0f);
				node.normal = Common::Vector4();
				result->nodes.push_back(node);
			}
		}

		while (input != '\n') {
			fin.get(input);
		}

		fin.get(input);
	}

	fin.close();

	for( size_t i = 0; i < result->nodes.size(); i++ ) {
		PathNode iNode = result->nodes[i];
		PathNode nextNode = result->nodes[(i + 1) % result->nodes.size()];

		// HACK just an approximation, probably bad if points aren't close together
		iNode.normal = nextNode.point - iNode.point;
		iNode.normal.normalize();
		result->nodes[i] = iNode;
	}

	return result;
}