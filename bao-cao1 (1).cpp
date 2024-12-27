#include <iostream>
#include <string>
using namespace std;

// Cau trcc anh
struct Photo {
    int id;         // ID cua anh
    string date;    // Ngay thang nam (YYYY-MM-DD)
    string name;    // Ten anh
};

// Cau truc node trong danh sách lien ket
struct Node {
    Photo photo;    // Du lieu anh
    Node* next;     // Con tro den node tiep theo
};

// Ham them anh vao danh sach liên ket
void addPhoto(Node*& head, const Photo& photo) {
    Node* newNode = new Node;    // Tao node moi
    newNode->photo = photo;      // Gan du lieu anh vào node
    newNode->next = head;        // Lien ket node moi vao dau danh sach
    head = newNode;              // Cap nhat lai dau danh sách
    cout << "Da them anh: " << photo.name << endl;
}

// Ham xoa anh theo tên
void deletePhoto(Node*& head, const string& filename) {
    Node* current = head;
    Node* previous = NULL;
    
    while (current != NULL) {
        if (current->photo.name == filename) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            delete current;   // Xoa node
            cout << "Da xoa anh: " << filename << endl;
            return;
        }
        previous = current;
        current = current->next;
    }
    cout << "Khong tim thay anh: " << filename << endl;
}

// Ham tim kiem anh theo ten
void searchPhoto(Node* head, const string& filename) {
    Node* current = head;
    while (current != NULL) {
        if (current->photo.name == filename) {
            cout << "Tim thay anh: " << current->photo.name
                 << ", ID: " << current->photo.id
                 << ", Ngay: " << current->photo.date << endl;
            return;
        }
        current = current->next;
    }
    cout << "Khong tim thay anh: " << filename << endl;
}

// Ham hien thi tat ca anh trong album
void displayPhotos(Node* head) {
    if (head == NULL) {
        cout << "Album trong!" << endl;
        return;
    }

    Node* current = head;
    cout << "Danh sach anh trong album:" << endl;
    while (current != NULL) {
        cout << "ID: " << current->photo.id
             << ", Ngay: " << current->photo.date
             << ", Ten: " << current->photo.name << endl;
        current = current->next;
    }
}

// Ham loaii bo anh trung lap
void removeDuplicates(Node*& head) {
    if (head == NULL) {
        cout << "Album trong! Khong co anh trung lap." << endl;
        return;
    }

    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        prev = current;
        Node* checker = current->next;
        while (checker != NULL) {
            if (current->photo.name == checker->photo.name) {
                prev->next = checker->next;  // Xóa anh trùng
                delete checker;
                cout << "Da loai bo anh trung lap: " << current->photo.name << endl;
                checker = prev->next;
            } else {
                prev = checker;
                checker = checker->next;
            }
        }
        current = current->next;
    }

    cout << "Hoan tat viec loai bo anh trung lap!" << endl;
}

// Ham giai phong bo nho khi thoat chuong trình
void clearAlbum(Node*& head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
}

// Menu cho chuong trình
void displayMenu() {
    cout << "\n+----------------------------------+\n";
    cout << "|     Photo Album Manager         |\n";
    cout << "+----------------------------------+\n";
    cout << "| 1. Them anh                    |\n";
    cout << "| 2. Xoa anh theo ten            |\n";
    cout << "| 3. Tim kiem anh theo ten       |\n";
    cout << "| 4. Hien thi tat ca anh         |\n";
    cout << "| 5. Loai bo anh trung lap       |\n";
    cout << "| 6. Thoat                       |\n";
    cout << "+----------------------------------+\n";
    cout << "Chon lua: ";
}


int main() {
    Node* head = NULL;  // Khoi tao danh sách liên ket rong
    int choice;
    string filename, date_taken;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();  // Ða xu lý nhap tu bàn phim voi getline sau dó

        switch (choice) {
            case 1: {
                int id;
                string name;
                cout << "Nhap ID anh: ";
                cin >> id;
                cin.ignore();
                cout << "Nhap ten anh: ";
                getline(cin, name);
                cout << "Nhap ngay chup anh (YYYY-MM-DD): ";
                getline(cin, date_taken);
                Photo newPhoto = {id, date_taken, name};
                addPhoto(head, newPhoto);
                break;
            }
            case 2: {
                cout << "Nhap ten anh can xoa: ";
                getline(cin, filename);
                deletePhoto(head, filename);
                break;
            }
            case 3: {
                cout << "Nhap ten anh can tim: ";
                getline(cin, filename);
                searchPhoto(head, filename);
                break;
            }
            case 4: {
                displayPhotos(head);
                break;
            }
            case 5: {
                removeDuplicates(head);
                break;
            }
            case 6: {
                cout << "Dang thoat chuong trinh..." << endl;
                clearAlbum(head);  // Giai phong bo nho truoc khi thoat
                break;
            }
            default:
                cout << "Lua chon không hop ly. Vui lòng thu lai!" << endl;
        }
    } while (choice != 6);

    return 0;
}
