#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 책 구조체 정의
struct Book {
    int id;
    char title[100];
    char author[100];
    int isBorrowed;
    struct Book* next;
};

// 노드 생성 함수
struct Book* createBook(int id, const char* title, const char* author) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    if (newBook == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        return NULL;
    }
    newBook->id = id;
    strcpy_s(newBook->title, sizeof(newBook->title), title);
    strcpy_s(newBook->author, sizeof(newBook->author), author);
    newBook->isBorrowed = 0; // 초기에는 빌려지지 않은 상태
    newBook->next = NULL;
    return newBook;
}

// 책 추가 함수
void addBook(struct Book** headRef, int id, const char* title, const char* author) {
    struct Book* newBook = createBook(id, title, author);
    if (newBook == NULL) {
        return;
    }
    newBook->next = *headRef;
    *headRef = newBook;
}

// 책 검색 함수
struct Book* searchBook(struct Book* head, int id) {
    struct Book* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 책 빌리기 함수
void borrowBook(struct Book* head, int id) {
    struct Book* book = searchBook(head, id);
    if (book != NULL) {
        if (book->isBorrowed) {
            printf("이 책은 이미 대출되었습니다.\n");
        }
        else {
            book->isBorrowed = 1;
            printf("책을 성공적으로 대출했습니다.\n");
        }
    }
    else {
        printf("책을 찾을 수 없습니다.\n");
    }
}

// 책 반납하기 함수
void returnBook(struct Book* head, int id) {
    struct Book* book = searchBook(head, id);
    if (book != NULL) {
        if (!book->isBorrowed) {
            printf("이 책은 대출되지 않았습니다.\n");
        }
        else {
            book->isBorrowed = 0;
            printf("책을 성공적으로 반납했습니다.\n");
        }
    }
    else {
        printf("책을 찾을 수 없습니다.\n");
    }
}

// 책 삭제 함수
void deleteBook(struct Book** headRef, int id) {
    struct Book* temp = *headRef;
    struct Book* prev = NULL;

    if (temp != NULL && temp->id == id) {
        *headRef = temp->next;
        free(temp);
        printf("책을 성공적으로 삭제했습니다.\n");
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("책을 찾을 수 없습니다.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("책을 성공적으로 삭제했습니다.\n");
}

// 책 목록 출력 함수
void printBooks(struct Book* head) {
    struct Book* current = head;
    while (current != NULL) {
        printf("ID: %d, Title: %s, Author: %s, %s\n", current->id, current->title, current->author, current->isBorrowed ? "Borrowed" : "Available");
        current = current->next;
    }
}

// 버퍼 비우기 함수
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 메인 함수
int main() {
    struct Book* library = NULL;
    int choice, id;
    char title[100], author[100];

    while (1) {
        printf("\n1. 책 추가\n2. 책 검색\n3. 책 빌리기\n4. 책 반납하기\n5. 책 삭제하기\n6. 책 목록 출력하기\n7. 종료\n");
        printf("선택: ");
        if (scanf_s("%d", &choice) != 1) {
            clearInputBuffer();
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            continue;
        }

        switch (choice) {
        case 1:
            printf("책 ID: ");
            if (scanf_s("%d", &id) != 1) {
                clearInputBuffer();
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
                continue;
            }
            clearInputBuffer(); // 버퍼 비우기
            printf("책 제목: ");
            if (fgets(title, sizeof(title), stdin) == NULL) {
                printf("입력 오류. 다시 시도하세요.\n");
                continue;
            }
            title[strcspn(title, "\n")] = 0; // 새줄 문자 제거
            printf("책 저자: ");
            if (fgets(author, sizeof(author), stdin) == NULL) {
                printf("입력 오류. 다시 시도하세요.\n");
                continue;
            }
            author[strcspn(author, "\n")] = 0; // 새줄 문자 제거
            addBook(&library, id, title, author);
            break;
        case 2:
            printf("검색할 책 ID: ");
            if (scanf_s("%d", &id) != 1) {
                clearInputBuffer();
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
                continue;
            }
            clearInputBuffer(); // 버퍼 비우기
            {
                struct Book* book = searchBook(library, id);
                if (book != NULL) {
                    printf("ID: %d, Title: %s, Author: %s, %s\n", book->id, book->title, book->author, book->isBorrowed ? "Borrowed" : "Available");
                }
                else {
                    printf("책을 찾을 수 없습니다.\n");
                }
            }
            break;
        case 3:
            printf("빌릴 책 ID: ");
            if (scanf_s("%d", &id) != 1) {
                clearInputBuffer();
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
                continue;
            }
            clearInputBuffer(); // 버퍼 비우기
            borrowBook(library, id);
            break;
        case 4:
            printf("반납할 책 ID: ");
            if (scanf_s("%d", &id) != 1) {
                clearInputBuffer();
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
                continue;
            }
            clearInputBuffer(); // 버퍼 비우기
            returnBook(library, id);
            break;
        case 5:
            printf("삭제할 책 ID: ");
            if (scanf_s("%d", &id) != 1) {
                clearInputBuffer();
                printf("잘못된 입력입니다. 다시 시도하세요.\n");
                continue;
            }
            clearInputBuffer(); // 버퍼 비우기
            deleteBook(&library, id);
            break;
        case 6:
            printBooks(library);
            break;
        case 7:
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}