#include "TrackPath.h"

#include <fstream>
#include <stdexcept>
using namespace std;

TrackPath::TrackPath()
{
}


TrackPath::~TrackPath()
{
}

TrackPath * TrackPath::fromFile(char *file) {
	ifstream fin;
	char input;

	fin.open(file);

	if (fin.fail()) {
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

	for (int i = 0; i < result->nodes.size(); i++) {
		PathNode iNode = result->nodes[i];
		PathNode nextNode = result->nodes[(i + 1) % result->nodes.size()];

		// HACK just an approximation, probably bad if points aren't close together
		iNode.normal = nextNode.point - iNode.point;
		iNode.normal.normalize();
		result->nodes[i] = iNode;
	}

	return result;
}
