class ExamRoom {
int num = 0;
vector<int > row;
public:
    ExamRoom(int N) {
        num = N;
    }
    
    int seat() {
        if (row.size() == 0) {
        	row.push_back(0);
        	return 0;
        }
        int d = max(row[0], num - 1 - row[row.size() - 1]);
        for (int i = 1;i < row.size(); i ++) {
        	d = max(d, (row[i] - row[i - 1]) / 2);
        }
        if (d == row[0]) {
        	row.insert(row.begin(), 0);
            return 0;
        }
        else {
        	for (int i = 1; i < row.size(); i++) {
        		if ((row[i] - row[i - 1]) / 2 == d) {
        			row.insert(row.begin() + i, (row[i] + row[i - 1]) / 2);
        			return row[i];
        		}
        	}
        }
        row.push_back(num - 1);
        return num - 1;
    }
    
    void leave(int p) {
        for (int i = 0; i < row.size(); i++) {
        	if (row[i] == p)
        		row.erase(row.begin() + i);
        }
    }
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(N);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */


struct IntV
{
	static int N;
	int l, r;
	IntV(int l, int r) : l(l), r(r) {};
	int getDistance() const {
		if (l == 0) return r;
		if (r == N - 1) return N - 1 - l;
		if (l > r) return -1;
		else return (r - l) / 2;		
	} 

	int getInsertPoint() const {
		if (l == 0) return 0;
		if (r == N  - 1) return N - 1;
		else return (l + r) / 2;  
	}
	int operator < (const IntV& a) const {
		int d1 = getDistance();
		int d2 = a.getDistance();
		if(d1 != d2) return d1 > d2;
        	return l < a.l;
	}
};
int IntV :: N = 0;
class ExamRoom{
public:
	set<IntV> interval;
	map<int, int> r2l, l2r;
	ExamRoom(int N) {
		IntV::N = N;
		interval.insert(IntV(0, N - 1));
		l2r[0] = N - 1;
		r2l[N -1] = 0;
	}

	int seat() {
		auto cur = *(interval.begin());
		interval.erase(interval.begin());
		int pos = cur.getInsertPoint();
		interval.insert(IntV(cur.l, pos - 1));
		interval.insert(IntV(pos + 1, cur.r));
		l2r[cur.l] = pos - 1;
		r2l[pos - 1] = cur.l;
		l2r[pos + 1] = cur.r;
		r2l[cur.r] = pos + 1;
		return pos;

	}
	void leave(int p) {
		auto r = l2r[p + 1];
		auto l = r2l[p - 1];
		interval.erase(IntV(l, p - 1));
		interval.erase(IntV(p + 1, r));
		interval.insert(IntV(l, r));
		l2r[l] = r;
		r2l[r] = l;
		l2r.erase(p - 1);
		r2l.erase(p + 1);
	}
};


struct IntV
{
	static int N;
	int l, r;
	IntV(int l, int r) : l(l), r(r) {};
	int getDistance() const {
		if (l == 0) return r;
		if (r == N - 1) return N - 1 - l;
		if (r < l) return -1;
		else return (r - l) / 2;		
	} 

	int getInsertPoint() const {
		if (l == 0) return 0;
		if (r == N  - 1) return N - 1;
		else return (l + r) / 2; 
	}
	int operator < (const IntV& a) const {
		int d1 = getDistance();
		int d2 = a.getDistance();
		if(d1 != d2) return d1 > d2;
        	return l < a.l;
	}
};
int IntV :: N = 0;
class ExamRoom{
public:
	set<IntV> interval;
	map<int, int> r2l, l2r;
	ExamRoom(int N) {
		IntV::N = N;
		interval.clear(); l2r.clear(); r2l.clear();
		interval.insert(IntV(0, N - 1));
		l2r[0] = N - 1;
		r2l[N -1] = 0;
	}

	int seat() {
		auto cur = *(interval.begin());
		interval.erase(interval.begin());
		int pos = cur.getInsertPoint();
		cout << pos;
		interval.insert(IntV(cur.l, pos - 1));
		interval.insert(IntV(pos + 1, cur.r));
		l2r[cur.l] = pos - 1;
		r2l[pos - 1] = cur.l;
		l2r[pos + 1] = cur.r;
		r2l[cur.r] = pos + 1;
		return pos;

	}
	void leave(int p) {
		auto r = l2r[p + 1];
		auto l = r2l[p - 1];
		interval.erase(IntV(l, p - 1));
		interval.erase(IntV(p + 1, r));
		interval.insert(IntV(l, r));
		l2r[l] = r;
		r2l[r] = l;
		r2l.erase(p - 1);
		l2r.erase(p + 1);
	}
};


