#include "target.h"
#include <string>

using namespace std;



// lastUp will start at 0
Target::Target(const string &name, ostream &out) : out{out}, name{name},
	curDepends{0}, lastUp{0}, depends{new Target*[maxDepends]}, parent{nullptr} {}

Target::~Target() {
	delete [] depends;
	// should just delete array and not delete any other targets.
}

bool Target::isLeaf() const {

	#ifdef DEBUG
	cerr << "curDepends of " << name << " is: " << curDepends << endl;
	#endif


  if (curDepends == 0) return true;

  return false;
}

void Target::addDepend(Target *d) {

	#ifdef DEBUG
	cerr << 7 << endl;
	#endif

	// Check if depend already exists
	for (int i = 0; i < curDepends; ++i) {

		#ifdef DEBUG
		cerr << 8 << endl;
		#endif

		if (d == depends[i]) {

			#ifdef DEBUG
			cerr << 7 << endl;
			#endif
			return; // nothing happens
		}
	}

	#ifdef DEBUG
	cerr << 9 << endl;
	#endif

	// Is there room?
	if (curDepends == maxDepends) {
		out << "Max dependencies exceeded" << endl;
		return;
	}

	#ifdef DEBUG
	cerr << 10 << endl;
	#endif

	// assumes depend is new, and max not exceeded, updates d's parent
	depends[curDepends] = d;
	d->parent = this;
	++curDepends;
}

// no dependencies
void Target::update(const int time) {
	if (isLeaf()) {

		#ifdef DEBUG
		cerr << "c" << endl;
		#endif

		lastUp = time;

		#ifdef DEBUG
		cerr << "d" << endl;
		#endif

		out << name << " updated at time " << time << endl;

	}
	else out << "Cannot update non-leaf object" << endl;
}

int Target::lastUpdated() const {
  return lastUp;
}

// has dependencies
// recurse through tree of dependencies update when leaf, then build
void Target::build(int time) {
	lastUp = time;
	cout << "Building " << name << endl;
}
