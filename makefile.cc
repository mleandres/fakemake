#include "makefile.h"
#include <iostream>
#include <string>
using namespace std;

Makefile::Makefile(ostream &out)
	: out{out}, curTargets{0}, time{1}, targs{new Target*[maxTargets]} {
}

Makefile::~Makefile() {
	for (int i = 0; i < curTargets; ++i) {
		delete targs[i]; //
	}
	delete [] targs;
}

void Makefile::addDepend(const string &t, const string &d) {
	int tar = findTarg(t);

	#ifdef DEBUG
	cerr << 1 << endl;
	#endif

	if (tar == -1) {
		makeNewTarg(t);
		tar = curTargets - 1;
	}

	#ifdef DEBUG
	cerr << "targs[" << tar << "] is now: " << targs[tar]->name << endl;
	#endif

	int dep = findTarg(d);
	if (dep == -1) {
		makeNewTarg(d);
		dep = curTargets - 1;
	}

	#ifdef DEBUG
	cerr << "targs[" << dep << "] is now: " << targs[dep]->name << endl;
	#endif

	targs[tar]->addDepend(targs[dep]);

	#ifdef DEBUG
	cerr << "curDepends of targs[" << tar << "] is: " << targs[tar]->curDepends << endl;
	cerr << "curDepends of targs[" << dep << "] is: " << targs[dep]->curDepends << endl;
	#endif
}

// Update leaf file (always updates time)
void Makefile::changeTarget(const string &t) {

	#ifdef DEBUG
	cerr << "a" << endl;
	#endif

	int i = findTarg(t);

	#ifdef DEBUG
	cerr << "target " << t << " found at position: " << i << endl;
	#endif

	if (i != -1) {
		targs[i]->update(time);
	}

	++time;

}

void Makefile::rebuild(const string &t) {
	// go through target graph and build???
	int n = findTarg(t);
	recurse(targs[n]);
}

// update criteria is if leaf->lastUp > parent->lastUp
// recurse traverses graph of nodes
void Makefile::recurse(Target *t) {
	for (int i = 0; i < t->curDepends; ++i) {
		if (t->isLeaf()) {
			return; // we've gone too far!!
		}
		else {
			Target *c = t->depends[i]; //child
			recurse(c);
			// check if dependent is newer than current
			if (c->lastUpdated() > t->lastUpdated()) {
				t->build(time);
			}
		}
	}
}

// finds array location of target, returns -1 if it does not exist
int Makefile::findTarg(const string &t) {
	for (int i = 0; i < curTargets; i++) {
		if (targs[i]->name == t) return i;
	}
	return -1;
}

// checks if currently at max dependencies
bool Makefile::atMax() const {
	return curTargets == maxTargets;
}

// makes a new target if max not exceeded
void Makefile::makeNewTarg(const string &t) {

	#ifdef DEBUG
	cerr << 2 << endl;
	#endif

	if (!atMax()) {
		targs[curTargets] = new Target{t, out};

		#ifdef DEBUG
		cerr << 3 << endl;
		#endif

		++curTargets;
	}
	else out << "Max targets exceeded" << endl;
}
