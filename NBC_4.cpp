#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace std 사용

class Book {
public:
	string title;
	string author;
	int stock;

	Book(const string& title, const string& author)
		: title(title), author(author), stock(3) {
	}
};

class BookManager {
private:
	vector<Book> books; // 책 목록 저장

public:
	// 책 추가 메서드
	void addBook(const string& title, const string& author) {
		books.push_back(Book(title, author)); // push_back 사용
		cout << "책이 추가되었습니다: " << title << " by " << author << endl;
	}

	// 모든 책 출력 메서드
	void displayAllBooks() const {
		if (books.empty()) {
			cout << "현재 등록된 책이 없습니다." << endl;
			return;
		}

		cout << "현재 도서 목록:" << endl;
		for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
			cout << "- " << books[i].title << " by " << books[i].author;
			cout << "남은 재고: " << books[i].stock << endl;
		}
	}

	// 책 제목으로 검색하기
	Book* searchBookByTitle(const string& title) {
		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].title == title) {
				return &books[i];
			}
		}
		return nullptr;
	}

	//작가로 검색하기
	vector <Book*> searchBookByAuthor(const string& author) {
		vector <Book*> result;
		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].author == author) {
				result.push_back(&books[i]);
			}
		}
		return result;
	}
	// 책 대여하기

	void borrowBook() {
		cout << "대여 방식을 선택하기 : " << endl;
		cout << "1번을 눌러 제목으로 검색" << endl;
		cout << "2번을 눌러 작가로 검색" << endl;
		cout << "선택 : ";
		int choice;
		cin >> choice;

		if (choice == 1) {
			string title;
			cout << "대여할 책 제목을 입력하세요 : ";
			cin.ignore(); // 이전 입력의 잔여 버퍼를 제거하는 코드라고 함?
			getline(cin, title);
			Book* book = searchBookByTitle(title);

			if (book) {
				if (book->stock > 0) {
					book->stock--;
					cout << book->title << " 책을 대여했습니다" << endl;
				}
				else {
					cout << book->title << "의 대여를 실패했습니다. 재고가 없습니다." << endl;
				}
			}
			else {
				cout << "해당 제목의 책은 존재하지 않습니다." << endl;
			}
		}
		else if (choice == 2) {
			string author;
			cout << "대여할 책 작가를 입력하세요 : ";
			cin.ignore();
			getline(cin, author);
			vector<Book*> foundbooks = searchBookByAuthor(author);
			if (foundbooks.empty()) {
				cout << "해당 작가의 책은 존재하지 않습니다." << endl;
				return;
			}
			cout << "해당 작가( " << author << ")의 책 목록 : " << endl;
			for (size_t i = 0; i < foundbooks.size(); i++) {
				cout << i + 1 << "." << foundbooks[i]->title << "재고 : " << foundbooks[i]->stock << endl;

			}
			string title;
			cout << "대여할 책 제목을 입력하세요 : ";
			getline(cin, title);
			Book* book = searchBookByTitle(title);
			if (book) {
				if (book->stock > 0) {
					book->stock--;
					cout << book->title << " 책을 대여했습니다" << endl;
				}
				else {
					cout << book->title << "의 대여를 실패했습니다. 재고가 없습니다." << endl;
				}
			}
			else {
				cout << "해당 제목의 책은 존재하지 않습니다." << endl;
			}
		}
		else {
			cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
		}
	}

	// 책 반납하기
	void returnBook() {
		string title;
		cout << "반납할 책 제목을 입력하세요 : ";
		cin.ignore();
		getline(cin, title);
		Book* book = searchBookByTitle(title);
		if (book) {
			if (book->stock < 3) {
				book->stock++;
				cout << book->title << " 책을 반납했습니다" << endl;
			}
			else {
				cout << "반납할 책을 찾을 수 없습니다" << endl;
			}
		}
		else {
			cout << "해당 제목의 책은 존재하지 않습니다." << endl;
		}
	}
};
int main() {
	BookManager manager;

	// 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
	// 프로그램 종료를 선택하기 전까지 계속 동작합니다.
	while (true) {
		cout << "\n도서관 관리 프로그램" << endl;
		cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
		cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
		cout << "3. 종료" << endl; // 프로그램 종료
		cout << "4. 책 검색" << endl; // 책 제목 또는 작가로 책 검색
		cout << "5. 책 대여" << endl; // 책 대여
		cout << "6. 책 반납" << endl; // 책 반납
		cout << "선택: ";

		int choice; // 사용자의 메뉴 선택을 저장
		cin >> choice;

		if (choice == 1) {
			// 1번 선택: 책 추가
			// 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
			string title, author;
			cout << "책 제목: ";
			cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
			getline(cin, title); // 제목 입력 (공백 포함)
			cout << "책 저자: ";
			getline(cin, author); // 저자명 입력 (공백 포함)
			manager.addBook(title, author); // 입력받은 책 정보를 추가
		}
		else if (choice == 2) {
			// 2번 선택: 모든 책 출력
			// 현재 BookManager에 저장된 책 목록을 출력합니다.
			manager.displayAllBooks();
		}
		else if (choice == 3) {
			// 3번 선택: 종료
			// 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
			cout << "프로그램을 종료합니다." << endl;
			break; // while 루프 종료
		}
		else if (choice == 4) {
			//4번 선택 : 책 검색
			cout << "\n검색 방식 선택:" << endl;
			cout << "1. 제목으로 검색" << endl;
			cout << "2. 작가로 검색" << endl;
			cout << "선택: ";
			int searchChoice;
			cin >> searchChoice;

			if (searchChoice == 1) {
				string title;
				cout << "검색할 책 제목을 입력하세요: ";
				cin.ignore();
				getline(cin, title);
				Book* book = manager.searchBookByTitle(title);
				if (book) {
					cout << "검색 결과: " << book->title << endl;
					cout << "남은 재고: " << book->stock << endl;

				}
				else {
					cout << "검색 결과가 없습니다." << endl;
				}
			}
			else if (searchChoice == 2) {
				string author;
				cout << "검색할 책 작가를 입력하세요: ";
				cin.ignore();
				getline(cin, author);
				vector<Book*> foundBooks = manager.searchBookByAuthor(author);
				if (foundBooks.empty()) {
					cout << "검색 결과가 없습니다." << endl;
				}
				else {
					cout << "검색 결과: " << endl;
					for (size_t i = 0; i < foundBooks.size(); i++) {
						cout << i + 1 << ". " << foundBooks[i]->title << endl;
						cout << "남은 재고: " << foundBooks[i]->stock << endl;
					}
				}
			}
			else {
				// 잘못된 입력 처리
				// 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
				cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
			}
		}
		else if (choice == 5) {
			// 5번 선택: 책 대여
			// 사용자로부터 책 제목을 입력받아 해당 책을 대여합니다.
			manager.borrowBook();
		}
		else if (choice == 6) {
			// 6번 선택: 책 반납
			// 사용자로부터 책 제목을 입력받아 해당 책을 반납합니다.
			manager.returnBook();
		}
		else {
			// 잘못된 입력 처리
			// 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
			cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
		}
	}

		return 0; // 프로그램 정상 종료
	}