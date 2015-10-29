#include "heuristicEvaluation.h"

void ind2sub(const int sub,const int cols,const int rows,int *row,int *col) {
   *row=sub/cols;
   *col=sub%cols;
}

int stableDiscsHelper(vector <int> positions, int corner, int symbol) {
	// only run on filled corners of symbol
	int nStableDiscs = 0;
	bool down, left;
	if (corner == 63) {
		down = false;
		left = true;
	} else if (corner == 56) {
		down = false;
		left = false;
	} else if (corner == 7) {
		down = true;
		left = true;
	} else {
		down = true;
		left = false;
	}
	int horInc, verInc;
	int horEnd, verEnd;
	if (down) {
		verInc = 8;
		verEnd = 24;
	} else {
		verInc = -8;
		verEnd = -24;
	}
	if (left) {
		horInc = -1;
		horEnd = -4;
	} else {
		horInc = 1;
		horEnd = 4;
	}

	for (int i = corner; i != corner + verEnd + verInc; i+=verInc) {
		// cout << " " << endl;
		if(positions[i] == symbol) {
			for (int j = i; j != i + horEnd; j+= horInc) {
				if (positions[j] == symbol) {
					// cout << j << endl;
					nStableDiscs++;
				} else {
					break;
				}
			}
		} else {
			break;
		}
	}

	return nStableDiscs;
}

int stableDiscs(vector <int> positions,int symbol) {
	// grow out from for corners
	int nStableDiscs = 0;
	nStableDiscs += stableDiscsHelper(positions,63,symbol);
	nStableDiscs += stableDiscsHelper(positions,7,symbol);
	nStableDiscs += stableDiscsHelper(positions,0,symbol);
	nStableDiscs +=	stableDiscsHelper(positions,56,symbol);

	return nStableDiscs;
}


int potentialMobility(vector <int> positions, int symbol) {
	int interior[] = {9,10,11,12,13,15,17,18,19,20,21,22,25,26,27,28,29,30,33,34,35,36,37,38,41,42,43,44,45,46,49,50,51,52,53,54};
	int cur, top, bot, lef, rig, tr, tl, bl, br;
	int potMobilility;
	for (int i : interior) {
		cur = positions[i];
		lef = positions[i-1];
		rig = positions[i+1];
		top = positions[i-8];
		bot = positions[i+8];
		tr  = positions[i-7];
		tl  = positions[i-9];
		bl  = positions[i+7];
		br  = positions[i+9];
        // Potential Mobility 
        // # of discs that the oppenent has adjacent to empty squares
		potMobilility = 0;
		if (cur == -1 && (lef == 0 || rig == 0 || top == 0 || bot == 0 || tr == 0 || tl == 0 || bl == 0 || br == 0))
			potMobilility++;
            // # of empty squares adjacent ot the opponents discs
		if (cur = -symbol && lef == 0)
			potMobilility++;
		if (cur = -symbol && rig == 0)
			potMobilility++;
		if (cur = -symbol && top == 0)
			potMobilility++;
		if (cur = -symbol && bot == 0)
			potMobilility++;
		if (cur = -symbol && tr  == 0)
			potMobilility++;
		if (cur = -symbol && tl  == 0)
			potMobilility++;
		if (cur = -symbol && bl  == 0)
			potMobilility++;
		if (cur = -symbol && br  == 0)
			potMobilility++;
	}

        // go through exterior positions 
        // go through top positions
	int topa[] = {1,2,3,4,5,6};
	for (int i : topa) {
		cur = positions[i];
		lef = positions[i-1];
		rig = positions[i+1];
		if (cur == -symbol && (lef == 0 || rig == 0))
			potMobilility++;
            // # of empty squares adjacent ot the opponents discs
		if (cur = -symbol && lef == 0)
			potMobilility++;
		if (cur = -symbol && rig == 0)
			potMobilility++;
	}

        // go through bottom positions
	int bota[] = {57,58,59,60,61,62};
	for (int i : bota) {
		cur = positions[i];
		lef = positions[i-1];
		rig = positions[i+1];
		if (cur == -symbol && (lef == 0 || rig == 0))
			potMobilility++;
            // # of empty squares adjacent ot the opponents discs
		if (cur = -symbol && lef == 0)
			potMobilility++;
		if (cur = -symbol && rig == 0)
			potMobilility++;
	}

        // go through left positions
	int lefa[] = {8,16,24,32,40,48};
	for (int i : lefa) {
		cur = positions[i];
		bot = positions[i-8];
		top = positions[i+8];
		if (cur == -1 && (top == 0 || bot == 0 ))
			potMobilility++;
            // # of empty squares adjacent ot the opponents discs
		if (cur = -symbol && top == 0)
			potMobilility++;
		if (cur = -symbol && bot  == 0)
			potMobilility++;
	}

        // go through right positions
	int riga[] = {15,23,31,39,47,55};
	for (int i : riga) {
		cur = positions[i];
		bot = positions[i-8];
		top = positions[i+8];
		if (cur == -symbol && (top == 0 || bot == 0 ))
			potMobilility++;
            // # of empty squares adjacent ot the opponents discs
		if (cur = -symbol && top == 0)
			potMobilility++;
		if (cur = -symbol && bot  == 0)
			potMobilility++;
	}

	return potMobilility;
}


int ESAC(int moveNumber) {
    return 312 + 6.24*moveNumber;
}

int CMAC(int moveNumber) {
    if (moveNumber < 25) 
        return 50 + 2*moveNumber;
    if (moveNumber > 25)
        return 75 + moveNumber;
}

int PAI(int moveNumber) {
	if (moveNumber < 30) {
		return 0.5;
	} else if (moveNumber > 30) {
		return 100;
	}
}

int heuristic4(othelloBoard board, int nSpacesRemaining,int symbol) {
	return rand() % 1000;
}

int heuristic5(othelloBoard board, int nSpacesRemaining,int symbol) {
    // do heuristic from perspective of player with p.symbol = 1
	int val = 0;
	vector <int> positions = board.positions;

	unordered_map<int, list<int>> validMoves = board.validMoves(1);
	unordered_map<int, list<int>> otherValidMoves = board.validMoves(-1);

    //check if game is over		
	if ((validMoves.begin() == validMoves.end()) || (nSpacesRemaining == 0)) {   
		if ((otherValidMoves.begin() == otherValidMoves.end()) || (nSpacesRemaining == 0)) {
			int s = accumulate(board.positions.begin(), board.positions.end(), 0);
			if (s > 0) {
                	// cout << "White wins!" << endl;
				return 45678900 + s;
			}
			if (s < 0) {
                	// cout << "Black wins!" << endl;
				return -45678900 + s;
			}
		}
	}

	// mobility
	int	p = validMoves.size();
	int	o = otherValidMoves.size();

	double mobility;
	if (p > o) {
		mobility = (100*p)/(p+o);
	} else if (p < o) {
		mobility = -(100*o)/(p+o);
	} else {
		mobility = 0;
	}

	int pPotMob = potentialMobility(positions, 1);
	int oPotMob = potentialMobility(positions, -1);

	double potMobility;
	if (pPotMob > oPotMob) {
		potMobility = (100*pPotMob)/(pPotMob+oPotMob);
	} else if (pPotMob < oPotMob) {
		potMobility = -(100*oPotMob)/(pPotMob+oPotMob);
	} else {
		potMobility = 0;
	}

	double corners;
	int cornerInds[4] = {0,7,56,63};
	int pCorners = 0;
	int oCorners = 0;

	for (auto i : cornerInds) {
		if (positions[i] == 1) {
			pCorners++;
		} else if (positions[i] == -1) {
			oCorners++;
		}
	} 

	if (pCorners > oCorners) {
		corners = 100 * (pCorners ) / (pCorners + oCorners);
	} else if(oCorners > pCorners) {
		corners = -100 * (oCorners) / (pCorners + oCorners);
	} else {
		corners = 0;
	}

	int pStable = stableDiscs(positions,1);
	int oStable = stableDiscs(positions,-1);

	double stability;

	if (pStable > oStable) {
		stability = 100 * (pStable ) / (pStable + oStable);
	} else if(oStable > pStable) {
		stability = -100 * (oStable) / (pStable + oStable);
	} else {
		stability = 0;
	}

	// coin parity
	int d = accumulate(board.positions.begin(), board.positions.end(), 0);
	int t = inner_product(board.positions.begin(),board.positions.end(),board.positions.begin(),0);
	double parity = 100*d/t;

	// cout << "S" << endl;
	// cout << mobility << endl;
	// cout << potMobility << endl;
	// cout << corners << endl;

	// board.draw(validMoves,1);

	return round(50*mobility + 10*potMobility + 10*PAI(board.nMoves)*parity + 80*corners + 0*stability);
}


int heuristicEvaluation::heuristic(othelloBoard board, int nSpacesRemaining,int symbol) {
	if (hIndex == 1) {
	} else if (hIndex == 2) {
	} else if (hIndex == 3) {
	} else if (hIndex == 4) {
		return heuristic4(board, nSpacesRemaining,symbol);
	} else if (hIndex == 5) {
		return heuristic5(board, nSpacesRemaining,symbol);
	}
}

heuristicEvaluation::heuristicEvaluation() {

}

// int main() {
// 	cout << "Hello World";
// }