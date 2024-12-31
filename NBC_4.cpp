#include <iostream>
#include <vector>
#include <string>

using namespace std; // namespace std ���

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
	vector<Book> books; // å ��� ����

public:
	// å �߰� �޼���
	void addBook(const string& title, const string& author) {
		books.push_back(Book(title, author)); // push_back ���
		cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
	}

	// ��� å ��� �޼���
	void displayAllBooks() const {
		if (books.empty()) {
			cout << "���� ��ϵ� å�� �����ϴ�." << endl;
			return;
		}

		cout << "���� ���� ���:" << endl;
		for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
			cout << "- " << books[i].title << " by " << books[i].author;
			cout << "���� ���: " << books[i].stock << endl;
		}
	}

	// å �������� �˻��ϱ�
	Book* searchBookByTitle(const string& title) {
		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].title == title) {
				return &books[i];
			}
		}
		return nullptr;
	}

	//�۰��� �˻��ϱ�
	vector <Book*> searchBookByAuthor(const string& author) {
		vector <Book*> result;
		for (size_t i = 0; i < books.size(); i++) {
			if (books[i].author == author) {
				result.push_back(&books[i]);
			}
		}
		return result;
	}
	// å �뿩�ϱ�

	void borrowBook() {
		cout << "�뿩 ����� �����ϱ� : " << endl;
		cout << "1���� ���� �������� �˻�" << endl;
		cout << "2���� ���� �۰��� �˻�" << endl;
		cout << "���� : ";
		int choice;
		cin >> choice;

		if (choice == 1) {
			string title;
			cout << "�뿩�� å ������ �Է��ϼ��� : ";
			cin.ignore(); // ���� �Է��� �ܿ� ���۸� �����ϴ� �ڵ��� ��?
			getline(cin, title);
			Book* book = searchBookByTitle(title);

			if (book) {
				if (book->stock > 0) {
					book->stock--;
					cout << book->title << " å�� �뿩�߽��ϴ�" << endl;
				}
				else {
					cout << book->title << "�� �뿩�� �����߽��ϴ�. ��� �����ϴ�." << endl;
				}
			}
			else {
				cout << "�ش� ������ å�� �������� �ʽ��ϴ�." << endl;
			}
		}
		else if (choice == 2) {
			string author;
			cout << "�뿩�� å �۰��� �Է��ϼ��� : ";
			cin.ignore();
			getline(cin, author);
			vector<Book*> foundbooks = searchBookByAuthor(author);
			if (foundbooks.empty()) {
				cout << "�ش� �۰��� å�� �������� �ʽ��ϴ�." << endl;
				return;
			}
			cout << "�ش� �۰�( " << author << ")�� å ��� : " << endl;
			for (size_t i = 0; i < foundbooks.size(); i++) {
				cout << i + 1 << "." << foundbooks[i]->title << "��� : " << foundbooks[i]->stock << endl;

			}
			string title;
			cout << "�뿩�� å ������ �Է��ϼ��� : ";
			getline(cin, title);
			Book* book = searchBookByTitle(title);
			if (book) {
				if (book->stock > 0) {
					book->stock--;
					cout << book->title << " å�� �뿩�߽��ϴ�" << endl;
				}
				else {
					cout << book->title << "�� �뿩�� �����߽��ϴ�. ��� �����ϴ�." << endl;
				}
			}
			else {
				cout << "�ش� ������ å�� �������� �ʽ��ϴ�." << endl;
			}
		}
		else {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
		}
	}

	// å �ݳ��ϱ�
	void returnBook() {
		string title;
		cout << "�ݳ��� å ������ �Է��ϼ��� : ";
		cin.ignore();
		getline(cin, title);
		Book* book = searchBookByTitle(title);
		if (book) {
			if (book->stock < 3) {
				book->stock++;
				cout << book->title << " å�� �ݳ��߽��ϴ�" << endl;
			}
			else {
				cout << "�ݳ��� å�� ã�� �� �����ϴ�" << endl;
			}
		}
		else {
			cout << "�ش� ������ å�� �������� �ʽ��ϴ�." << endl;
		}
	}
};
int main() {
	BookManager manager;

	// ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
	// ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
	while (true) {
		cout << "\n������ ���� ���α׷�" << endl;
		cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
		cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
		cout << "3. ����" << endl; // ���α׷� ����
		cout << "4. å �˻�" << endl; // å ���� �Ǵ� �۰��� å �˻�
		cout << "5. å �뿩" << endl; // å �뿩
		cout << "6. å �ݳ�" << endl; // å �ݳ�
		cout << "����: ";

		int choice; // ������� �޴� ������ ����
		cin >> choice;

		if (choice == 1) {
			// 1�� ����: å �߰�
			// ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
			string title, author;
			cout << "å ����: ";
			cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
			getline(cin, title); // ���� �Է� (���� ����)
			cout << "å ����: ";
			getline(cin, author); // ���ڸ� �Է� (���� ����)
			manager.addBook(title, author); // �Է¹��� å ������ �߰�
		}
		else if (choice == 2) {
			// 2�� ����: ��� å ���
			// ���� BookManager�� ����� å ����� ����մϴ�.
			manager.displayAllBooks();
		}
		else if (choice == 3) {
			// 3�� ����: ����
			// ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
			cout << "���α׷��� �����մϴ�." << endl;
			break; // while ���� ����
		}
		else if (choice == 4) {
			//4�� ���� : å �˻�
			cout << "\n�˻� ��� ����:" << endl;
			cout << "1. �������� �˻�" << endl;
			cout << "2. �۰��� �˻�" << endl;
			cout << "����: ";
			int searchChoice;
			cin >> searchChoice;

			if (searchChoice == 1) {
				string title;
				cout << "�˻��� å ������ �Է��ϼ���: ";
				cin.ignore();
				getline(cin, title);
				Book* book = manager.searchBookByTitle(title);
				if (book) {
					cout << "�˻� ���: " << book->title << endl;
					cout << "���� ���: " << book->stock << endl;

				}
				else {
					cout << "�˻� ����� �����ϴ�." << endl;
				}
			}
			else if (searchChoice == 2) {
				string author;
				cout << "�˻��� å �۰��� �Է��ϼ���: ";
				cin.ignore();
				getline(cin, author);
				vector<Book*> foundBooks = manager.searchBookByAuthor(author);
				if (foundBooks.empty()) {
					cout << "�˻� ����� �����ϴ�." << endl;
				}
				else {
					cout << "�˻� ���: " << endl;
					for (size_t i = 0; i < foundBooks.size(); i++) {
						cout << i + 1 << ". " << foundBooks[i]->title << endl;
						cout << "���� ���: " << foundBooks[i]->stock << endl;
					}
				}
			}
			else {
				// �߸��� �Է� ó��
				// �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
				cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
			}
		}
		else if (choice == 5) {
			// 5�� ����: å �뿩
			// ����ڷκ��� å ������ �Է¹޾� �ش� å�� �뿩�մϴ�.
			manager.borrowBook();
		}
		else if (choice == 6) {
			// 6�� ����: å �ݳ�
			// ����ڷκ��� å ������ �Է¹޾� �ش� å�� �ݳ��մϴ�.
			manager.returnBook();
		}
		else {
			// �߸��� �Է� ó��
			// �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
			cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
		}
	}

		return 0; // ���α׷� ���� ����
	}