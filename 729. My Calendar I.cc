class MyCalendar {
public:
	vector<pair<int, int>> books;
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        for( &b : books) {
        	if (start < b.second && end > b.first) return false;
        }
        books.push_back({start, end});
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

class MyCalendar {
public:
	set<pair<int, int>> books;
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
       	auto index = books.lower_bound({start, end});
       	if (index != books.end() && end > index -> first) return false;
       	if (index != books.begin() && start < (--index) -> second) return false;
       	books.insert({start, end});
       	return true;
    }
};


/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */



class MyCalendar {
public:
	map<int, int> books;
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        auto index = books.lower_bound(start);
        if (index != books.end() && end > index -> first) return false;
        if (index != books.begin() && start <(--index) -> second) return false;
        books[start] = end;
        return true;
    }
};

