#include <iostream> // library untuk menampilkan dan menginput 
#include <vector> // library dynamic array
#include <string> // library untuk pengaturan string (membantu proses pembuatan kode buku)
#include <unordered_map> // library untuk menghubungkan vertex satu dengan vertex lainnya (membantu proses pembuatan graph)
#include <stack> // library stack (membantu proses pembuatan graph DFS)
#include <list> // library pembuatan tabel hash (membantu proses tabel hash)
#include <ctime> // library pengaksesan waktu (membantu proses pembuatan string tanggal peminjaman buku pada tabel hash)
using namespace std;

struct BookData{ // struct vector (dynamic array) untuk menyimpan data buku
    string CodeBook; // kode buku di perpus
    string Title; // nama judul
    string Author; // nama penulis
    int Year; // tahun perilisan buku
};
vector<BookData> CorneliusLibrary = {
    {"022014", "Bumi", "Tere Liye", 2014},
    {"022015", "Bulan", "Tere Liye", 2015},
    {"132016", "Matahari", "Tere Liye", 2016},
    {"022017", "Bintang", "Tere Liye", 2017},
    {"032018", "Ceros dan Batazoar", "Tere Liye", 2018},
    {"112018", "Komet", "Tere Liye", 2018},
    {"112019", "Komet Minor", "Tere Liye", 2019},
    {"192022", "Selena", "Tere Liye", 2020},
    {"142021", "Nebula", "Tere Liye", 2021},
    {"192022", "Si Putih", "Tere Liye", 2022},
    {"003188", "Clean Code", "Robert Cecil Martin", 2008},
    {"020199", "The Pragmatic Programmer", "Andy Hunt & Dave Thomas", 1999},
    {"201918", "The Rust Programming Language", "Steve Klabnik", 2018},
    {"111018", "Kotlin Programming: From Idea to Production", "JetBrains", 2018},
    {"003815", "C++: The Complete Reference", "Herbert Schildt", 2015},
    {"000339", "Competitive Programming: Algorithms and Techniques", "Cormen, Leiserson, Rivest, Stein", 2009},
    {"016515", "Python Crash Course", "Eric Matthes", 2015},
    {"001115", "Automate the Boring Stuff with Python", "Al Sweigart", 2015},
    {"061215", "Fluent Python", "Luciano Ramalho", 2015},
};
void InputBookData(BookData& Book); // fungsi memasukkan data buku baru
string GenerateCodeBook(string Title,string Author,int Year); // fungsi membuat kode buku di perpus
void DeleteBookData(vector<BookData>& Book, string &TargetedTitle); // fungsi menghapus data buku

// PENGAPLIKASIAN TREE
struct TreeBook{ // tree untuk penyimpanan data buku (untuk pencarian author)
    BookData Data; // data buku
    TreeBook *Left; // child sebelah kiri (memiliki urutan huruf lebih kecil)
    TreeBook *Right; // child sebelah kanan (memiliki urutan huruf lebih kecil)
};
TreeBook *Author;
void Create(TreeBook *&Author); // fungsi membuat tree
int IsEmpty(TreeBook *Author); // fungsi untuk memeriksa apakah tree kosong atau tidak
TreeBook* InsertNode(TreeBook *&Author, BookData &Book); // fungsi untuk menginputkan node ke dalam tree
void DisplayInOrder(TreeBook *Author); // fungsi untuk menampilkan daftar buku secara urut berdasarkan huruf depan buku
TreeBook* SearchAuthor(TreeBook *Author, string &TargetedAuthor); // fungsi untuk mencari author buku menggunakkan BST (Binary Search Tree)
TreeBook* DeleteNode(TreeBook *Author,string &TargetedTitle); // fungsi untuk menghapus buku dari tree
TreeBook *FindMax(TreeBook *Author); // fungsi untuk mencari node paling ujung kanan (yang akan membantu fungsi DeleteNode)

// PENGAPLIKASIAN GRAPH
struct Graph{ // graph untuk penyaranan buku
    int Books; // jumlah buku yang ada dalam penyaranan
    unordered_map<string,vector<string>> AdjList; // unordered_map untuk merepresentasikan daftar ketetanggaan
};
Graph TereLiyeRecommend;
Graph PythonRecommend;
Graph LearnOtherRecommend;
void AddLine(Graph &Recommendation, string From, string To);
void DFS(const Graph &Recommendation, const string &From);

// PENGAPLIKASIAN SORT
void SortBooksByTitle(vector<BookData>& CorneliusLibrary); // fungsi untuk mengurutkan buku berdasarkan judul
void QuickSort(vector<BookData>& CorneliusLibrary,int Low, int High); // menggunakkan fungsi quick sort
int Part(vector<BookData>& CorneliusLibrary,int Low, int High); // partisi pada quick sort
void Swap(BookData& i, BookData& j); // pertukaran posisi struct pada quick sort

// PENGAPLIKASIAN SEARCH
int BinarySearchByTitle(vector<BookData>& CorneliusLibrary, string &TargetedTitle);// fungsi untuk mencari judul menggunakkan binary search

string GetCurrentDate(); // fungsi untuk mendapatkan tanggal hari ini

// PENGAPLIKASIAN TABLE HASH DAN COLLISION HANDLING
const int TableSize = 25; // ukuran table hash
struct BorrowerData{ // data peminjam yang akan dimasukkan table hash 
    BookData Book; // data buku 
    string BorrowerName; // nama peminjam
    string BorrowDate; // tanggal peminjaman buku
};
vector<list<BorrowerData>> BookTable(TableSize); // table hash berisikan buku yang ada dalam perpus
vector<list<BorrowerData>> BorrowTable(TableSize); // table hash berisikan data peminjam yang meminjam buku
int HashFunction(string &CodeBook); // fungsi hashing
void AddBook(BookData &Book); // fungsi memasukkan data buku ke dalam table hash
BookData* FindBookBasedOnTitle(string &TargetedTitle); // fungsi mencari buku berdasarkan judul
void BorrowBookBasedOnTitle(string &TargetedTitle, string &BorrowerName, string &BorrowDate); // fungsi meminjam buku berdasarkan judul
BookData* FindBookBasedOnAuthor(string &TargetedAuthor); // fungsi mencari buku berdasarkan author
void BorrowBookBasedOnAuthor(string &TargetedAuthor, string &BorrowerName, string &BorrowDate); // fungsi meminjam buku berdasarkan author
void DisplayBorrowList(); // fungsi untuk menampilkan semua data peminjaman

int main(){
TereLiyeRecommend.Books = 10;
PythonRecommend.Books = 3;
LearnOtherRecommend.Books = 3;
AddLine(TereLiyeRecommend, "Bumi", "Bulan");
AddLine(TereLiyeRecommend, "Bulan", "Matahari");
AddLine(TereLiyeRecommend, "Matahari", "Bintang");
AddLine(TereLiyeRecommend, "Bintang", "Ceros dan Batazoar");
AddLine(TereLiyeRecommend, "Ceros dan Batazoar", "Komet");
AddLine(TereLiyeRecommend, "Komet", "Komet Minor");
AddLine(TereLiyeRecommend, "Komet Minor", "Selena");
AddLine(TereLiyeRecommend, "Selena", "Nebula");
AddLine(TereLiyeRecommend, "Nebula", "Si Putih");

AddLine(PythonRecommend, "Python Crash Course", "Automate the Boring Stuff with Python");
AddLine(PythonRecommend, "Python Crash Course", "Fluent Python");
AddLine(PythonRecommend, "Automate the Boring Stuff with Python", "Python Crash Course");
AddLine(PythonRecommend, "Automate the Boring Stuff with Python", "Fluent Python");
AddLine(PythonRecommend, "Fluent Python", "Python Crash Course");
AddLine(PythonRecommend, "Fluent Python", "Automate the Boring Stuff with Python");

AddLine(LearnOtherRecommend, "C++: The Complete Reference", "The Rust Programming Language");
AddLine(LearnOtherRecommend, "C++: The Complete Reference", "Kotlin Programming: From Idea to Production");
AddLine(LearnOtherRecommend, "The Rust Programming Language", "C++: The Complete Reference");
AddLine(LearnOtherRecommend, "The Rust Programming Language", "Kotlin Programming: From Idea to Production");
AddLine(LearnOtherRecommend, "Kotlin Programming: From Idea to Production", "C++: The Complete Reference");
AddLine(LearnOtherRecommend, "Kotlin Programming: From Idea to Production", "The Rust Programming Language");

for(auto& i : CorneliusLibrary){
    string GeneratingCodeBook= GenerateCodeBook(i.Title,i.Author,i.Year);
    i.CodeBook = GeneratingCodeBook;    
}

Create(Author);
for(auto& i : CorneliusLibrary){
    InsertNode(Author,i);
}

for(auto& i:CorneliusLibrary){
    AddBook(i);
}
    int Login;

    char Home = 'y';
    while(Home == 'y'){
        system("cls");
        cout << "=========================\n";
        cout << "     Cornelius Library   \n";  
        cout << "=========================\n";
        cout << "1. Login as Librarian\n";
        cout << "2. Login as Visitor\n";
        cout << "0. Exit\n";
        cout << "> ";
        cin >> Login;
        cin.ignore();

        switch (Login){
        case 1:{
            char LoginLibrarian = 'y';
            while (LoginLibrarian == 'y'){
                int Input;
                cout << "\n=========================\n";
                cout << "   Dashboard Librarian   \n";
                cout << "=========================\n";
                cout << "1. Borrowing List\n";
                cout << "2. Insert new book\n";
                cout << "3. Sort books\n";
                cout << "4. Find book\n";
                cout << "5. Delete book\n";
                cout << "0. Exit\n";
                cout << "> ";
                cin >> Input;   
                cin.ignore();

                switch(Input){
                    case 1:{
                        char ManageBorrow;
                        string TargetedCodeBook;
                        string TargetedBorrowerName;
                        DisplayBorrowList();
                        cout << "Press enter to continue\n";
                        cin.get();
                    }
                    break;

                    case 2:{
                        char Choice = 'y';
                        while(Choice == 'y'){
                            BookData Book;
                            InputBookData(Book);
                            CorneliusLibrary.push_back(Book);
                            
                            Author = InsertNode(Author,Book);

                            AddBook(Book);
                            cout << "Insert another book? (y/n)\n";
                            cout << "> ";
                            cin >> Choice;
                            cin.ignore();
                        }
                    }
                    break;

                    case 3:{
                        SortBooksByTitle(CorneliusLibrary);
                        cout << "List of the sorted books based on title\n\n";
                        for(size_t i = 0; i < CorneliusLibrary.size(); i++){
                            cout << "Book " << i + 1 << endl;
                            cout << "    | " << CorneliusLibrary[i].Title << " | written by | " << CorneliusLibrary[i].Author << " |\n";
                            cout << "    released in " <<  CorneliusLibrary[i].Year << " with code book " << CorneliusLibrary[i].CodeBook << "\n\n";
                        }

                        cout << "Press Enter to continue\n";
                        cin.get();
                    }
                    break;

                    case 4:{
                        int InputFind;
                        cout << "   1. Find book based on title\n";
                        cout << "   2. Find book based on author\n";
                        cout << "   > ";
                        cin >> InputFind;
                        cin.ignore();

                        switch(InputFind){
                            case 1:{
                                string TargetedTitle;
                                SortBooksByTitle(CorneliusLibrary);
                                cout << "\nFind the title\n";
                                cout << "> ";
                                getline(cin, TargetedTitle);

                                int FoundTitle = BinarySearchByTitle(CorneliusLibrary, TargetedTitle);

                                if(FoundTitle != -1){
                                    cout << "\nBook was Found\n\n";
                                    cout << "Code Book: " << CorneliusLibrary[FoundTitle].CodeBook << endl;
                                    cout << "Title: " << CorneliusLibrary[FoundTitle].Title << endl;
                                    cout << "Author: " << CorneliusLibrary[FoundTitle].Author << endl;
                                    cout << "Year: " << CorneliusLibrary[FoundTitle].Year << endl; 
                                }
                                else{
                                    cout << "\nBook was not found\n";
                                }
                            }
                            break;
                            
                            case 2:{
                                string TargetedAuthor;
                                cout << "\nFind the author\n";
                                cout << "> ";
                                getline(cin, TargetedAuthor);

                                TreeBook *FoundAuthor = SearchAuthor(Author,TargetedAuthor);
                                if(FoundAuthor != nullptr){
                                    cout << "\nBook was found\n\n";
                                    cout << "Code Book: " << FoundAuthor->Data.CodeBook << endl;
                                    cout << "Title: " << FoundAuthor->Data.Title << endl;
                                    cout << "Author: " << FoundAuthor->Data.Author << endl;
                                    cout << "Year: " << FoundAuthor->Data.Year << endl; 
                                }
                                else{
                                    cout << "\nBook was not found\n";
                                }
                            }
                            break;

                            default:

                            break;
                    }
                    cout << "\nPress enter to continue\n";
                    cin.get();
                }
                break;

                case 5:{
                    string TargetedTitle;
                    cout << "\nInput the title\n";
                    cout << "> ";
                    getline(cin, TargetedTitle);
                    
                    DeleteBookData(CorneliusLibrary,TargetedTitle);
                    DeleteNode(Author,TargetedTitle);

                    cout << "\nPress enter to continue\n";
                    cin.get();
                }
                break;
                case 0:
                    char Exit;
                    cout << "\nExit librarian mode? (y/n)\n";
                    cout << "> ";
                    cin >> Exit;    

                    if(Exit == 'y' || Exit == 'Y'){
                        LoginLibrarian = 'n';
                    }  
                    else{
                        LoginLibrarian = 'y';
                    }
                break;

                default:

                break;
            }
        }
    }
    break;

    case 2:{
        char LoginVisitor = 'y';
        while (LoginVisitor == 'y'){
            int Input;
            cout << "\n===================================\n";
            cout << "    Welcome to Cornelius Library   \n";
            cout << "====================================\n";
            cout << "What can we assist you today?\n\n";
            cout << "1. See all of our collection\n";
            cout << "2. Find the book you want to borrow\n";
            cout << "0. Exit\n";
            cout << "> ";
            cin >> Input;
            cin.ignore();

            switch (Input){   
            case 1:{
            SortBooksByTitle(CorneliusLibrary);
            cout << "List of the sorted books based on title\n\n";
                for(size_t i = 0; i < CorneliusLibrary.size(); i++){
                    cout << "Book " << i + 1 << endl;
                    cout << "    | " << CorneliusLibrary[i].Title << " | written by | " << CorneliusLibrary[i].Author << " |\n";
                    cout << "    released in " <<  CorneliusLibrary[i].Year << " with code book " << CorneliusLibrary[i].CodeBook << "\n\n";
                }
                        
                cout << "\nPress enter to continue\n";
                cin.get();
            }
            break;
                
            case 2:{
                int InputFind;
                    cout << "   1. Find the book based on title\n";
                    cout << "   2. Find the book based on author\n";
                    cout << "   > ";
                    cin >> InputFind;
                    cin.ignore();

                    switch(InputFind){
                        case 1:{
                            char BorrowBook;
                            string TargetedTitle;
                            SortBooksByTitle(CorneliusLibrary);
                            cout << "\nWhat title are you looking for \n";
                            cout << "> ";
                            getline(cin, TargetedTitle);

                            int FoundTitle = BinarySearchByTitle(CorneliusLibrary, TargetedTitle);

                            if(FoundTitle != -1){
                                cout << "\nWe found the title you are looking for!!!\n\n";
                                cout << "Code Book: " << CorneliusLibrary[FoundTitle].CodeBook << endl;
                                cout << "Title: " << CorneliusLibrary[FoundTitle].Title << endl;
                                cout << "Author: " << CorneliusLibrary[FoundTitle].Author << endl;
                                cout << "Year: " << CorneliusLibrary[FoundTitle].Year << endl; 

                                cout << "\nWould you like to borrow this book? (y/n)\n";
                                cout << "> ";
                                cin >> BorrowBook;
                                cin.ignore();

                                if(BorrowBook == 'y' || BorrowBook == 'Y'){
                                    string BorrowerName;
                                    string BorrowDate = GetCurrentDate();

                                    cout << "\nWhat is your name? (We would like to manage your borrowing permission)\n";
                                    cout << "> ";
                                    getline(cin, BorrowerName);

                                    BorrowBookBasedOnTitle(TargetedTitle,BorrowerName,BorrowDate);

                                    cout << "\nYour borrowing permission has been processed, please proceed to the front office\n";
                                    cout << "so you can bring the book with you as soon as posibble\n";
                                    
                                    cout << "\nWe would also like to recommend you our suggested python learning course\n";
                                    DFS(PythonRecommend, "Python Crash Course");
                                    cout << "Finish\n";
                                    
                                    cout << "\nOr if you want to get acquainted with other programming language\n";
                                    DFS(LearnOtherRecommend, "C++: The Complete Reference");

                                    cout << "Finish\n";
                                    cout << "\nThank you and have a nice day !!\n";
                                }
                            }
                            
                            else{
                                cout << "\nUnfortunately, we did not find the title you are looking for...\n";
                            }

                            cout << "\nPress enter to continue\n";
                            cin.get();
                        }
                        break;
                            
                        case 2:{
                            char BorrowBook;
                            string TargetedAuthor;
                            cout << "\nWho is the author you are looking for\n";
                            cout << "> ";
                            getline(cin, TargetedAuthor);

                            TreeBook *FoundAuthor = SearchAuthor(Author,TargetedAuthor);
                            if(FoundAuthor != nullptr){
                                cout << "\nWe found the author you are looking for!!!\n\n";
                                cout << "Code Book: " << FoundAuthor->Data.CodeBook << endl;
                                cout << "Title: " << FoundAuthor->Data.Title << endl;
                                cout << "Author: " << FoundAuthor->Data.Author << endl;
                                cout << "Year: " << FoundAuthor->Data.Year << endl; 

                                cout << "Would you like to borrow this book? (y/n)\n";
                                cout << "> ";
                                cin >> BorrowBook;
                                cin.ignore();

                                if(BorrowBook == 'y' || BorrowBook == 'Y'){
                                    string BorrowerName;
                                    string BorrowDate = GetCurrentDate();

                                    cout << "What is your name? (We would like to manage your borrowing permission) (y/n) \n";
                                    cout << "> ";
                                    getline(cin, BorrowerName);

                                    BorrowBookBasedOnTitle(TargetedAuthor,BorrowerName,BorrowDate);

                                    cout << "Your borrowing permission has been processed, please proceed to the front office\n";
                                    cout << "so you can bring your book as soon as posibble\n";
                                    
                                    cout << "\nWe would also like to recommend you Bumi novel series written by Tere Liye, a brilliant author from Indonesia\n";
                                    DFS(TereLiyeRecommend, "Bumi");
                                    cout << "Finish\n";
                                        
                                    cout << "Thank you and have a nice day !!\n";
                                }
                            }
                            
                            else{
                                cout << "\nUnfortunately, we did not find the author you are looking for...\n";
                            }

                            cout << "\nPress enter to continue\n";
                            cin.get();
                        }
                        break;

                        default:

                        break;
                        
                    }
            }
            break;

            case 0:{
                char Exit;
                cout << "\nAre you sure you want to exit the application (y/n)\n";
                cout << "> ";
                cin >> Exit;    

                if(Exit == 'y' || Exit == 'Y'){
                    cout << "Thank you for visiting Cornelius Library\n";
                    cout << "Have a nice day !! \n";
                    LoginVisitor = 'n';
                }  
            
                else{
                    LoginVisitor = 'y';
                }
            }
            break;

            default:
                
            break;
            }
        }
    }
    break;

    case 0:{
        char Exit;
        cout << "\nExit library? (y/n)\n";
        cout << "> ";
        cin >> Exit;    

        if(Exit == 'y' || Exit == 'Y'){
                Home = 'n';
            }  
            else{
                Home = 'y';
            }
        }
    break;
    

    default:

    break;
    }

    }
    return 0;
}
void InputBookData(BookData& Book){ // fungsi memasukkan data buku baru
    cout << "\nInsert title of the Book\n";
    cout << "> ";
    getline(cin, Book.Title);
    cout << endl;

    cout << "Insert author of the Book\n";
    cout << "> ";
    getline(cin, Book.Author);
    cout << endl;

    cout << "Insert year released of the Book\n";
    cout << "> ";
    cin >> Book.Year;
    cin.ignore();
    
    Book.CodeBook = GenerateCodeBook(Book.Title,Book.Author,Book.Year); // membuat kode buku berdasarkan judul, penulis, tahun

    cout << "\nCode Book: " << Book.CodeBook << endl;
    cout << "Title: " << Book.Title << endl;
    cout << "Author: " << Book.Author << endl;
    cout << "Year: " << Book.Year << endl << endl;

    cout << Book.Title << " has been inputted into database\n";
}
string GenerateCodeBook(string Title,string Author,int Year){ // fungsi membuat kode buku di perpus
    // mengambil huruf depan dari Title dan Author 
    char FirstTitleChar = Title[0];
    char FirstAuthorChar = Author[0];

    // mengubah huruf depan menjadi angka
    int FirstTitleValue = FirstTitleChar - 'A' + 1;
    int FirstAuthorValue = FirstAuthorChar - 'A' + 1;

    // mengambil 2 digit terakhir dari tahun rilis (2 angka terakhir)
    int Last2DigitYear = Year % 100;
    
    // 2 angka awal diambil dari huruf awal judul
    // 2 angka tengah diambil dari huruf awal author
    // 2 angka terakhir diambil dari digit 2 tahun terakhir perilisan
    string GeneratedCode = to_string(FirstTitleValue) + to_string(FirstAuthorValue) + to_string(Last2DigitYear); // penggabungan 1 kode buku, 
    while (GeneratedCode.length() < 6){ // kode harus memiliki panjang 6 char
        GeneratedCode = '0' + GeneratedCode;
    }

    return GeneratedCode;
}
void DeleteBookData(vector<BookData>& Book, string &TargetedTitle){ // fungsi menghapus data buku
    for(size_t i = 0; i < Book.size(); i++){ // iterasi pencarian judul buku yang akan dihapus
        if(Book[i].Title == TargetedTitle){ // jika telah ditemukan
            Book.erase(Book.begin() + i); // maka dilakukan proses penghapusan
            cout << endl << TargetedTitle << " has been deleted from database\n";
            return;
        }
    }
    cout << endl << TargetedTitle << " was not found\n"; // jika memang tidak ditemukan, maka tidak terjadi penghapusan
}

// PENGAPLIKASIAN TREE
void Create(TreeBook *&Author){ // fungsi membuat tree
    Author = nullptr; 
}
int IsEmpty(TreeBook *Author){ // fungsi untuk memeriksa apakah tree kosong atau tidak
    if (Author == nullptr) return 1; // apabila kosong, maka mengembalikan nilai 1 
    else return 0;
}
TreeBook* InsertNode(TreeBook *&Author,  BookData &Book){  // fungsi untuk menginputkan node ke dalam tree
    if(Author == nullptr){ //jika tree masih kosong
        TreeBook *NewNode = new TreeBook; // maka membuat node pertama
        NewNode->Data = Book;
        NewNode->Left = nullptr;
        NewNode->Right = nullptr;
        Author = NewNode; 
    }
    
    else if (Book.Title < Author->Data.Title){ // jika urutan huruf depan lebih kecil dari buku saat ini, maka melakukan pencarian ke kiri
        Author->Left = InsertNode(Author->Left, Book);
    } 

    else if (Book.Title > Author->Data.Title){ // jika urutan huruf depan lebih besar dari buku saat ini, maka melakukan pencarian ke kanan
        Author->Right = InsertNode(Author->Right, Book);
    }
    return Author;
}
void DisplayInOrder(TreeBook *Author){ // fungsi untuk menampilkan daftar buku secara urut berdasarkan huruf depan buku
    if(Author == nullptr) return; // jika tree masih kosong, maka mengembalikan nilai kosong

    DisplayInOrder(Author->Left); // melakukan penelusuran ke kiri
    cout << Author->Data.Title << " written by " << Author->Data.Author << endl; // menampilkan data buku
    cout << "released in " << Author->Data.Year << " with code book " << Author->Data.CodeBook << endl << endl;
    DisplayInOrder(Author->Right); // melakukan penelusuran ke kanan
}
TreeBook* SearchAuthor(TreeBook *Author, string &TargetedAuthor){ // fungsi untuk mencari author buku menggunakkan BST (Binary Search Tree)
    if(Author == nullptr) return nullptr;
    
    else if(TargetedAuthor < Author->Data.Author){ // jika urutan huruf depan lebih kecil dari tree, maka melakukan pencarian ke kiri
        SearchAuthor(Author->Left,TargetedAuthor);
    }
    
    else if(TargetedAuthor > Author->Data.Author){
        SearchAuthor(Author->Right,TargetedAuthor); // jika urutan huruf depan lebih kecil dari tree, maka melakukan pencarian ke kiri
    }

    return Author; // jika ditemukan, maka langsung mengembalikan data buku
}
TreeBook* DeleteNode(TreeBook *Author,string &TargetedTitle){ // fungsi untuk menghapus data buku
    if(Author == nullptr) return nullptr; // jika tree kosong, maka mengembalikan nilai kosong

    else if(TargetedTitle < Author->Data.Title){ // jika data yang dicari urutan hurufnya lebih kecil dari tree
        Author->Left = DeleteNode(Author->Left,TargetedTitle); // maka bergeser ke sebelah kiri
    }
    else if(TargetedTitle > Author->Data.Title){ // jika data yang dicari urutan hurufnya lebih kecil dari tree
        Author->Right = DeleteNode(Author->Right,TargetedTitle); // maka bergeser ke sebelah kanan
    }
    // jika data memang sudah ditemukan 
    else{ // jika tree memiliki 1 child saja
        if(Author->Left == nullptr){ // jika tree tidak memiliki child di sebelah kiri 
            TreeBook *Temp = Author->Right; // maka Temp akan menyimpan child sebelah kanan
            delete Author; // menghapus data
            return Temp; // maka Temp disambungkan kembali terhadap binary tree
        }
        if(Author->Right == nullptr){ // jika tree tidak memiliki child di sebelah kanan 
            TreeBook *Temp = Author->Left; // maka Temp akan menyimpan child sebelah kiri
            delete Author; // menghapus data
            return Temp; // maka Temp disambungkan kembali terhadap binary tree
        }
        
        else{ //jika tree memiliki 2 child 
            TreeBook *Temp = FindMax(Author->Left); // maka data nilai digantikan dengan nilai terbesar dari left subtree
            Author->Data = Temp->Data; // data disimpan di Temp 
            Author->Left = DeleteNode(Author->Left,Temp->Data.Title); // maka dilakukan penghapusan 
        }
    }
    return Author; // mengembalikan tree 
}
TreeBook *FindMax(TreeBook *Author){ // fungsi untuk mencari node paling ujung kanan (yang akan membantu fungsi DeleteNode)
    if(Author == nullptr) return nullptr; // jika tree kosong, maka mengembalikan nilai kosong
    
    else{
        if(Author->Right == nullptr) return Author; // Jika sudah tidak terdapat child di sebelah kanan, maka data paling ujung kanan telah ditemukan
        else return FindMax(Author->Right); // jika belum, maka pelakukan penelusuran ke sebelah kanan
    }
}

// PENGAPLIKASIAN GRAPH
void AddLine(Graph &Recommendation, string From, string To){ // fungsi menambah edge ke dalam graph
    Recommendation.AdjList[From].push_back(To); // terdapat garis penghubung antara buku satu dengan buku yang lain
}
void DFS(const Graph &Recommendation, const string &From){ // fungsi DFS (Depth First Search) pada graph menggunakkan stack
    unordered_map<string,bool> Read; // membuat unordered_map untuk melacak node/buku yang telah dikunjungi

    for(const auto &Pair : Recommendation.AdjList){ // inisialisasi semua node sebagai belum dikunjungi
        Read[Pair.first] = false;
    }
    stack<string> ToRead; // stack untuk melacak node yang akan dikunjungi
    ToRead.push(From); // masukkan node awal ke dalam stack 

    while(!ToRead.empty()){ // selama stack tidak kosong
        string Current = ToRead.top();
        ToRead.pop(); // ambil node dari stack

        if(!Read[Current]){ // jika ada node/buku yang belum dikunjungi
            Read[Current] = true; // maka dikunjungi 
            cout << Current << "  --->  "; // dan mengeluarkan node/buku saat ini

           auto GraphRec = Recommendation.AdjList.find(Current); // auto GraphRec untuk mengetahui secara pasti graph dari rekomendasi buku
            if (GraphRec != Recommendation.AdjList.end()) { // selama GraphRec belum mencapai akhir
                for (const string &Next : GraphRec->second) {
                    if (!Read[Next]) { // Jika ada tetangga yang belum dikunjungi, masukkan ke dalam stack
                        ToRead.push(Next);
                    }
                }
            }
        }
    }
}

// PENGAPLIKASIAN SORT
void SortBooksByTitle(vector<BookData>& CorneliusLibrary){ // fungsi untuk mengurutkan buku berdasarkan judul
    int Total = CorneliusLibrary.size(); // menghitung banyaknya buku yang ada dalam perpus
    QuickSort(CorneliusLibrary,0,Total-1);
}
void QuickSort(vector<BookData>& CorneliusLibrary,int Low, int High){ // menggunakkan fungsi quick sort
    if(Low < High){ 
        int Pivot = Part(CorneliusLibrary,Low,High); // partisi pada quick sort

        QuickSort(CorneliusLibrary,Low,Pivot - 1); // rekursif quick sort
        QuickSort(CorneliusLibrary,Pivot + 1,High); // rekursif quick sort
    }   
}
int Part(vector<BookData>& CorneliusLibrary,int Low, int High){ // partisi pada quick sort
    string Pivot = CorneliusLibrary[High].Title; // buku paling terakhir pada perpus dijadikan pivot 
    int i = Low - 1;

    for(int j = Low; j < High; j++){ 
        if(CorneliusLibrary[j].Title < Pivot){ // jika terdapat judul yang secara urutan huruf lebih kecil dari Pivot
            i++;
            Swap(CorneliusLibrary[i], CorneliusLibrary[j]); // maka ditukar 
        }
    }
    Swap(CorneliusLibrary[i+1], CorneliusLibrary[High]); // pertukaran pivot ke posisi yang benar
    return i + 1;
}
void Swap(BookData& i, BookData& j){ // pertukaran posisi struct pada quick sort
    BookData Temp = i;
    i = j;
    j = Temp;
}

// PENGAPLIKASIAN SEARCH
int BinarySearchByTitle(vector<BookData>& CorneliusLibrary, string &TargetedTitle){ // fungsi untuk mencari judul menggunakkan binary search
    int Left = 0; // inisiasi batas kiri
    int Right = CorneliusLibrary.size() - 1; // inisiasi batas kanan

    while(Left <= Right){
        int Middle = (Left + Right) / 2; // pembagian tengah dynamic array 

        if(CorneliusLibrary[Middle].Title == TargetedTitle) return Middle; // judul ditemukan
        if(CorneliusLibrary[Middle].Title < TargetedTitle) Left = Middle + 1; // judul yang dicari berada di sebelah kanan
        else Right = Middle - 1; // judul yang dicari berada di sebelah kiri
    }
    return -1; // jika judul tidak ditemukan
}

string GetCurrentDate(){ // fungsi untuk mendapatkan tanggal hari ini
    time_t Now = time(0); // inisiasi waktu sekarang
    tm *LocalTime = localtime(&Now); // inisiasi waktu lokal
    
    string Day = to_string(LocalTime->tm_mday); // mendapatkan tanggal hari ini lalu diubah menjadi string 
    string Month = to_string(1 + LocalTime->tm_mon); // mendapatkan nomor bulan saat ini lalu diubah menjadi string 
    string Year = to_string(1900 + LocalTime->tm_year); // mendapatkan tahun saat ini lalu diubah menjadi string 
    
    if (Day.length() < 2) Day = "0" + Day; // jika tanggal hari ini hanya terdiri atas 1 angka, ditambahkan 0 di depan 
    if (Month.length() < 2) Month = "0" + Month;  // jika nomor bulan saat ini hanya terdiri atas 1 angka, ditambahkan 0 di depan 
    
    
    return Day + "-" + Month + "-" + Year;
}

// PENGAPLIKASIAN TABEL HASH DAN COLLISION HANDLING
int HashFunction(string &CodeBook){ // fungsi hashing
    int Hash = 0;
    for(char Code :CodeBook){ 
        Hash = (Hash % Code) % TableSize; // melakukan modulo pada kode buku, sehingga tahu dimana data buku diletakkan
    }
    return Hash;
}
void AddBook(BookData &Book){ // fungsi memasukkan data buku ke dalam table hash
    int i = HashFunction(Book.CodeBook); // hashing kode buku
    BookTable[i].push_back({Book,"", ""}); // memasukkan data buku ke dalam table hash
}
BookData* FindBookBasedOnTitle(string &TargetedTitle){ // fungsi mencari buku berdasarkan judul
    int i = HashFunction(TargetedTitle); // hashing judul
    for(auto &FindBook :BookTable[i]){ // pencarian judul buku 
        if(FindBook.Book.Title == TargetedTitle){
            return &FindBook.Book; // jika memang ditemukan, maka mengembalikan data buku tersebut
        }
    }
    return nullptr; // jika memang tidak ditemukan, maka mengembalikan pointer kosong
}
void BorrowBookBasedOnTitle(string &TargetedTitle, string &BorrowerName, string &BorrowDate){ // fungsi meminjam buku berdasarkan judul
    BookData *FindBook = FindBookBasedOnTitle(TargetedTitle); // melakukan pencarian judul dengan fungsi FindBookBasedOnTitle
    if(FindBook != nullptr){ // jika data buku ditemukan
        BorrowerData InputNewData = {*FindBook, BorrowerName, BorrowDate}; // menyimpan data buku, nama peminjam dan tanggal hari ini
        int i = HashFunction(TargetedTitle); // melakukan proses hashing untuk mengetahui pada indeks berapa data masuk
        BorrowTable[i].push_back(InputNewData); // memasukkan data peminjam ke dalam tabel hashing 
    }
    else{
        cout << "Book was not found or already borrowed\n";
    }
}
BookData* FindBookBasedOnAuthor(string &TargetedAuthor){ // fungsi mencari buku berdasarkan author
    int i = HashFunction(TargetedAuthor); // hashing judul
    for(auto &FindBook :BookTable[i]){  // pencarian author buku 
        if(FindBook.Book.Author == TargetedAuthor){
            return &FindBook.Book; // jika memang ditemukan, maka mengembalikan data buku tersebut
        }
    }
    return nullptr; // jika memang tidak ditemukan, maka mengembalikan pointer kosong
}
void BorrowBookBasedOnAuthor(string &TargetedAuthor, string &BorrowerName, string &BorrowDate){ // fungsi meminjam buku berdasarkan author
    BookData *FindBook = FindBookBasedOnAuthor(TargetedAuthor); // melakukan pencarian judul dengan fungsi FindBookBasedOnAuthpr
    if(FindBook != nullptr){ // jika data buku ditemukan
        BorrowerData InputNewData = {*FindBook, BorrowerName, BorrowDate};  // menyimpan data buku, nama peminjam dan tanggal hari ini
        int i = HashFunction(TargetedAuthor); // melakukan proses hashing untuk mengetahui pada indeks berapa data masuk
        BorrowTable[i].push_back(InputNewData); // memasukkan data peminjam ke dalam tabel hashing 
    }
    else{
        cout << "Book was not found or already borrowed\n";
    }
}
void DisplayBorrowList(){ // fungsi untuk menampilkan semua data peminjaman
    for(int i = 0;i < TableSize; i++){
        for(auto &j : BorrowTable[i]){
            cout << "\n| " << j.Book.Title << " |" << " written by " << " | " <<j.Book.Author << " |\n"; // menampilkan data buku dan data penulis
            cout << "   borrowed by " << j.BorrowerName << " from " << j.BorrowDate << endl << endl; // menampilkan nama penulis dan tanggal peminjaman
            }
        }
}

