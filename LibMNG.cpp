#include<bits/stdc++.h>
using namespace std;

class User{
    private:
        string username;
        string password;
        string role; //admin or user
    public:
        User(){};
        User(string username, string password, string role){
            this->username = username;
            this->password = password;
            this->role = role;
        }
        string getUsername(){
            return this->username;
        }
        void setUsername(string username){
            this->username = username;
        }
        string getPassword(){
            return this->password;
        }
        void setPassword(string password){
            this->password = password;
        }
        string getRole(){
            return this->role;
        }
        void setRole(string role){  // Sửa lỗi: thêm tham số
            this->role = role;
        }
        string toFile(){
            return username + "|" + password + "|" + role;
        }
        void display(){
            cout << "Username: " << username << " | Role: " << role << endl;  // Sửa lỗi cout
        }
};

class Book{
    private:
        string id, name, author;
        int year, quantity;
    public:
        Book(){};
        Book(string id, string name, string author, int year, int quantity){
            this->id = id;
            this->name = name;
            this->author = author;
            this->year = year;
            this->quantity = quantity;
        }
        
        string getName(){
            return this->name;
        }    
        void setName(string name){
            this->name = name;
        }
        string getId(){
            return this->id;
        }
        void setId(string id){
            this->id = id;
        }
        string getAuthor(){
            return this->author;
        }
        void setAuthor(string author){  // Sửa lỗi: tham số
            this->author = author;
        }
        int getYear(){
            return this->year;
        }
        void setYear(int year){
            this->year = year;
        }
        int getQuantity(){
            return this->quantity;
        }
        void setQuantity(int quantity){
            this->quantity = quantity;
        }
        
        string toFile(){
            return id + "|" + name + "|" + author + "|" + to_string(year) + "|" + to_string(quantity);
        }
        
        void display(){
            cout << id << "|" << name << "|" << author << "|" << year << "|" << quantity << endl;
        }
};

class Borrowed{
    private: 
        string name, bookId, borrowDate, returnDate;
        bool returned;
    public:
        Borrowed(){};
        Borrowed(string name, string bookId, string borrowDate, string returnDate, bool returned = false){
            this->name = name;
            this->bookId = bookId;
            this->borrowDate = borrowDate;
            this->returnDate = returnDate;
            this->returned = returned;
        }
        
        string getName(){
            return this->name;
        }
        void setName(string name){
            this->name = name;
        }
        string getBookId(){
            return this->bookId;
        }
        void setBookId(string bookId){
            this->bookId = bookId;
        }
        string getBorrowDate(){
            return this->borrowDate;
        }
        void setBorrowDate(string borrowDate){
            this->borrowDate = borrowDate;
        }
        string getReturnDate(){
            return this->returnDate;
        }
        void setReturnDate(string returnDate){
            this->returnDate = returnDate;
        }
        bool getReturned(){
            return this->returned;
        }
        void setReturned(bool returned){
            this->returned = returned;
        }
        
        string toFile(){
            return name + "|" + bookId + "|" + borrowDate + "|" + returnDate + "|" + (returned ? "1" : "0");
        }
        
        void display(){
            cout << name << "|" << bookId << "|" << borrowDate << "|" << returnDate << "|" << (returned ? "Da tra" : "Chua tra") << endl;
        }
};

class LibManager{
    private:
        vector<Book> books;
        vector<Borrowed> borrowers;
        vector<User> users; 
        bool isLoggedIn;   
        User currentUser;    

        void loadUsers(){
            users.clear();
            ifstream in("User.txt");
            if(!in){
                users.push_back(User("admin", "011106", "admin"));
                saveUsers();
                return;
            }
            string line;
            while(getline(in,line)){
                if(line.empty()) continue;
                stringstream ss(line);
                string username, password, role;
                getline(ss, username, '|');
                getline(ss, password, '|');
                getline(ss, role, '|');
                users.push_back(User(username, password, role));
            }
            in.close();
        }
        
        void saveUsers(){
            ofstream out("User.txt");
            for(User &u : users) out << u.toFile() << endl;
            out.close();
        }
        
        void loadBooks(){
            books.clear();
            ifstream in("books.txt");
            if(!in) return;
            string line;
            while(getline(in, line)){
                if(line.empty()) continue;
                stringstream ss(line);
                string id, name, author, yearStr, quantityStr;
                getline(ss, id, '|');
                getline(ss, name, '|');
                getline(ss, author, '|');
                getline(ss, yearStr, '|');
                getline(ss, quantityStr, '|');
                books.push_back(Book(id, name, author, stoi(yearStr), stoi(quantityStr)));
            }
            in.close();
        }
        
        void saveBooks(){
            ofstream out("books.txt");
            for(Book &b : books) out << b.toFile() << endl;
            out.close();
        }
        
        void loadBorrows(){
            borrowers.clear();
            ifstream in("person.txt");
            if(!in) return;
            string line;
            while(getline(in, line)){
                if(line.empty()) continue;
                stringstream ss(line);
                string name, bookId, bDate, rDate, status;
                getline(ss, name, '|');
                getline(ss, bookId, '|');
                getline(ss, bDate, '|');
                getline(ss, rDate, '|');
                getline(ss, status, '|');
                borrowers.push_back(Borrowed(name, bookId, bDate, rDate, status == "1"));
            }
            in.close();
        }
        
        void savePerson(){
            ofstream out("person.txt");
            for(Borrowed &p : borrowers) out << p.toFile() << endl;
            out.close();
        }

        bool login(){
            string username, password;
            cout << "\n<============== Đăng Nhập ============>";
            cout << "\nUsername: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
            
            for(User &u : users){
                if(u.getUsername() == username && u.getPassword() == password){
                    isLoggedIn = true;
                    currentUser = u;
                    cout << "Đăng nhập thành công!\n";
                    return true;
                }
            }
            cout << "ERROR: Sai username hoặc mật khẩu!\n";
            return false;
        }

        void registerUser(){
            string username, password;
            cout << "\n<============ Đăng ký ==========>\n";
            cout << "Username: ";
            getline(cin, username);
            
            for(User &u : users){
                if(u.getUsername() == username){
                    cout << "Tên đăng nhập đã tồn tại!\n";
                    return;
                }
            }
            
            cout << "Password: ";
            getline(cin, password);
            users.push_back(User(username, password, "user"));
            saveUsers();
            cout << "Đăng ký thành công!\n";
        }

        void logout(){
            currentUser = User();
            isLoggedIn = false;
            cout << "Đăng xuất thành công!\n";
        }

        bool isAdmin(){
            return isLoggedIn && currentUser.getRole() == "admin";
        }

        void searchBook(){
            if(books.empty()){
                cout << "Thư viện trống!\n";
                return;
            }
            
            cout << "\n===== Tìm sách =====\n";
            cout << "Tìm theo:\n1. ID\n2. Tên sách\nChọn: ";
            int choice;
            cin >> choice;
            cin.ignore();
            
            if(choice != 1 && choice != 2){
                cout << "Lựa chọn không hợp lệ!\n";
                return;
            }
            
            string keyword;
            cout << "Nhập từ khóa: ";
            getline(cin, keyword);
            
            bool found = false;
            for(Book &book : books){
                if((choice == 1 && book.getId().find(keyword) != string::npos) ||
                   (choice == 2 && book.getName().find(keyword) != string::npos)){
                    if(!found){
                        cout << "Kết quả tìm kiếm:\n";
                        found = true;
                    }
                    book.display();
                }
            }
            
            if(!found){
                cout << "Không tìm thấy sách!\n";
            }
        }

        void returnBook(){
            if(borrowers.empty()){
                cout << "Không có sách đang mượn!\n";
                return;
            }
            
            string bookId, personName;
            cout << "\n===== Trả sách =====\n";
            cout << "Nhập mã sách: ";
            getline(cin, bookId);
            cout << "Nhập tên người mượn: ";
            getline(cin, personName);
            
            bool found = false;
            for(Borrowed &borrow : borrowers){
                if(borrow.getBookId() == bookId && borrow.getName() == personName && !borrow.getReturned()){
                    borrow.setReturned(true);
                    
                    for(Book &book : books){
                        if(book.getId() == bookId){
                            book.setQuantity(book.getQuantity() + 1);
                            break;
                        }
                    }
                    
                    found = true;
                    saveBooks();
                    savePerson();
                    cout << "Trả sách thành công!\n";
                    break;
                }
            }
            
            if(!found){
                cout << "Không tìm thấy thông tin mượn sách!\n";
            }
        }

        void showMainMenu(){
            int choice;
            do{
                cout << "\n=============== MENU CHÍNH ===========\n";
                cout << "1. Hiển thị sách\n";
                cout << "2. Mượn sách\n";
                cout << "3. Tìm sách\n"; 
                cout << "4. Trả sách\n";
                if(isAdmin()){
                    cout << "5. Thêm sách (Admin)\n";
                    cout << "6. Hiển thị người mượn (Admin)\n";
                }
                cout << "7. Đăng xuất\n";
                cout << "0. Thoát\n";
                cout << "Chọn: ";
                cin >> choice;
                cin.ignore();

                switch(choice){
                    case 1: 
                        displayBook(); 
                        break;
                    case 2: 
                        borrowBook(); 
                        break;
                    case 3: 
                        searchBook(); 
                        break;
                    case 4: 
                        returnBook(); 
                        break;
                    case 5: 
                        if(isAdmin()) addBook();
                        else cout << "Không có quyền!\n";
                        break;
                    case 6: 
                        if(isAdmin()) displayBorrowers();
                        else cout << "Không có quyền!\n";
                        break;
                    case 7: 
                        logout(); 
                        return;
                    case 0: 
                        cout << "Thoát chương trình!\n";
                        exit(0);
                    default: 
                        cout << "Lựa chọn không hợp lệ!\n";
                }
            } while(true);
        }

    public:
        LibManager(){
            loadUsers();
            loadBooks();
            loadBorrows();
            isLoggedIn = false;
        }

        void showLoginMenu(){
            int choice;
            do{
                cout << "\n=============== Thư Viện ===========\n";
                cout << "1. Đăng nhập\n";
                cout << "2. Đăng ký\n";
                cout << "0. Thoát\n";
                cout << "Chọn: ";
                cin >> choice;
                cin.ignore();

                switch(choice){
                    case 1: 
                        if(login()){
                            showMainMenu();
                        }
                        break;
                    case 2: 
                        registerUser();
                        break;
                    case 0: 
                        cout << "Thoát chương trình!\n";
                        return;
                    default: 
                        cout << "Lựa chọn không hợp lệ!\n";
                }
            } while(true);
        }

        void addBook(){
            string id, title, author;
            int year, quantity;
            cout << "Nhập mã sách: "; 
            getline(cin, id);
            cout << "Nhập tên sách: "; 
            getline(cin, title);
            cout << "Tên tác giả: "; 
            getline(cin, author);
            cout << "Nhập năm xuất bản: "; 
            cin >> year;
            cout << "Nhập số lượng: "; 
            cin >> quantity;
            cin.ignore();
            books.push_back(Book(id, title, author, year, quantity));
            saveBooks();
            cout << "SUCCESS\n";
        }

        void displayBook(){
            if(books.empty()){
                cout << "Thư viện trống!\n";
                return;
            }
            cout << "\n============ DANH SÁCH SÁCH ===========\n";
            for(int i = 0; i < (int)books.size(); i++){
                books[i].display();
            }
        }

        void borrowBook(){
            if(books.empty()){
                cout << "Thư viện trống!\n";
                return;
            }
            
            string borrowName, borrowDate, returnDate;
            cout << "\n===== Mượn sách =====\n";
            cout << "Tìm sách theo:\n";
            cout << "1. ID\n";
            cout << "2. Tên sách\n";
            cout << "Chọn: ";
            int choice;
            cin >> choice;
            cin.ignore();
            
            int index = -1;
            bool found = false;

            if(choice == 1){
                string id;
                cout << "Nhập ID: ";
                getline(cin, id);
                for(int i = 0; i < (int)books.size(); i++){
                    if(books[i].getId() == id){
                        index = i;
                        found = true;
                        break;
                    }
                }
            } else if(choice == 2){
                string title;
                cout << "Nhập tên sách: ";
                getline(cin, title);
                for(int i = 0; i < (int)books.size(); i++){
                    if(books[i].getName().find(title) != string::npos){
                        index = i;
                        found = true;
                        break;
                    }
                }
            } else {
                cout << "Lựa chọn không hợp lệ!\n";
                return;
            }

            if(!found){
                cout << "Không tìm thấy sách!\n";
                return;
            }

            Book &b = books[index];
            cout << "\nĐã tìm thấy sách:\n";
            b.display();
            
            if(b.getQuantity() <= 0){
                cout << "Sách đã hết!\n";
                return;
            }

            cout << "Nhập tên người mượn: ";
            getline(cin, borrowName);
            cout << "Nhập ngày mượn (dd/mm/yyyy): ";
            getline(cin, borrowDate);
            cout << "Nhập ngày trả (dd/mm/yyyy): ";
            getline(cin, returnDate);

            b.setQuantity(b.getQuantity() - 1);
            borrowers.push_back(Borrowed(borrowName, b.getId(), borrowDate, returnDate, false));

            saveBooks();
            savePerson();
            cout << "Mượn sách thành công!\n";
        }

        void displayBorrowers(){
            if(borrowers.empty()){
                cout << "Không có người mượn!\n";
                return;
            }
            cout << "\n======= DANH SÁCH NGƯỜI MƯỢN ======\n";
            for(int i = 0; i < (int)borrowers.size(); i++){
                borrowers[i].display();
            }
        }
};

int main(){
    LibManager lib;
    lib.showLoginMenu();
    return 0;
}