// 25633101 - Nguyen Dang Duong
// 25631801 - Nguyen Phan Minh Duc
// 25635721 - Lam Nhat Tien

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    int maSach;
    char tenSach[50];
    int soLuong;
    struct list* next;
} list;

void add_dau(list** head, int ma, char* ten, int sl) {
    list* p = (list*)malloc(sizeof(list));
    p->maSach = ma;
    strcpy(p->tenSach, ten);
    p->soLuong = sl;
    p->next = *head;
    *head = p;
    printf("Them sach thanh cong!\n");
}

void in_danhsach(list* head) {
    if (head == NULL) {
        printf("Thu vien rong!\n");
        return;
    }
    printf("\n%-10s %-30s %-10s\n", "Ma Sach", "Ten Sach", "So Luong");
    printf("----------------------------------------------------\n");
    for (list* temp = head; temp != NULL; temp = temp->next) {
        printf("%-10d %-30s %-10d\n", temp->maSach, temp->tenSach, temp->soLuong);
    }
}

void tim_kiem(list* head, int ma) {
    for (list* temp = head; temp != NULL; temp = temp->next) {
        if (temp->maSach == ma) {
            printf("Tim thay: [%d] %s - Con lai: %d cuon\n", temp->maSach, temp->tenSach, temp->soLuong);
            return;
        }
    }
    printf("Khong tim thay sach co ma %d!\n", ma);
}

void xoa_sach(list** head, int ma) {
    if (*head == NULL) {
        printf("Danh sach rong!\n");
        return;
    }

    if ((*head)->maSach == ma) {
        list* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Da xoa sach co ma %d!\n", ma);
        return;
    }

    list* prev = *head;
    while (prev->next != NULL && prev->next->maSach != ma) {
        prev = prev->next;
    }

    if (prev->next == NULL) {
        printf("Khong tim thay ma sach %d!\n", ma);
        return;
    }

    list* target = prev->next;
    prev->next = target->next;
    free(target);
    printf("Da xoa sach co ma %d!\n", ma);
}

void sap_xep(list* head) {
    if (head == NULL || head->next == NULL) {
        printf("Danh sach khong can sap xep!\n");
        return;
    }

    for (list* i = head; i->next != NULL; i = i->next) {
        for (list* j = i->next; j != NULL; j = j->next) {
            if (i->maSach > j->maSach) {
                int tempMa = i->maSach;
                i->maSach = j->maSach;
                j->maSach = tempMa;

                char tempTen[50];
                strcpy(tempTen, i->tenSach);
                strcpy(i->tenSach, j->tenSach);
                strcpy(j->tenSach, tempTen);

                int tempSL = i->soLuong;
                i->soLuong = j->soLuong;
                j->soLuong = tempSL;
            }
        }
    }
    printf("Da sap xep sach theo ma tang dan!\n");
    in_danhsach(head);
}

int tong_sach(list* head) {
    int sum = 0;
    for (list* temp = head; temp != NULL; temp = temp->next) {
        sum += temp->soLuong;
    }
    return sum;
}

void ghi_file(list* head) {
    if (head == NULL) {
        printf("Danh sach rong, khong co gi de ghi file!\n");
        return;
    }

    FILE* f = fopen("library.txt", "w");
    if (f == NULL) {
        printf("Loi khong the mo file library.txt!\n");
        return;
    }

    for (list* temp = head; temp != NULL; temp = temp->next) {
        fprintf(f, "%d,%s,%d\n", temp->maSach, temp->tenSach, temp->soLuong);
    }

    fclose(f);
    printf("Ghi vao file library.txt thanh cong!\n");
}

void doc_file(list** head) {
    FILE* f = fopen("library.txt", "r");
    if (f == NULL) {
        add_dau(head, 101, "Lap trinh C co ban", 15);
        add_dau(head, 102, "Cau truc du lieu", 8);
        return;
    }

    int ma, sl;
    char ten[50];
    int count = 0;

    while (fscanf(f, "%d,%49[^,],%d\n", &ma, ten, &sl) == 3) {
        add_dau(head, ma, ten, sl);
        count++;
    }

    fclose(f);
    printf("Da tu dong nap %d sach tu file library.txt!\n", count);
}

int main() {
    list* head = NULL;
    int lc = 0;

    doc_file(&head);

    do {
        printf("\n========= QUAN LY THU VIEN =========\n");
        printf("1. Them sach vao dau\n");
        printf("2. In danh sach sach\n");
        printf("3. Tim kiem sach theo ma\n");
        printf("4. Xoa sach theo ma\n");
        printf("5. Sap xep sach theo ma tang dan\n");
        printf("6. Tinh tong so luong sach\n");
        printf("7. Ghi danh sach ra file library.txt\n");
        printf("0. Thoat\n");
        printf("====================================\n");
        printf("Nhap lua chon: ");
        scanf("%d", &lc);

        switch (lc) {
        case 1: {
            int ma, sl;
            char ten[50];
            printf("Nhap ma sach: ");
            scanf("%d", &ma);
            printf("Nhap ten sach: ");
            scanf(" %[^\n]", ten);
            printf("Nhap so luong: ");
            scanf("%d", &sl);
            add_dau(&head, ma, ten, sl);
            break;
        }
        case 2:
            in_danhsach(head);
            break;

        case 3: {
            int ma;
            printf("Nhap ma sach can tim: ");
            scanf("%d", &ma);
            tim_kiem(head, ma);
            break;
        }
        case 4: {
            int ma;
            printf("Nhap ma sach can xoa: ");
            scanf("%d", &ma);
            xoa_sach(&head, ma);
            break;
        }
        case 5:
            sap_xep(head);
            break;

        case 6:
            printf("Tong so luong sach: %d cuon\n", tong_sach(head));
            break;

        case 7:
            ghi_file(head);
            break;

        case 0:
            return 0;

        default:
            printf("Lua chon khong hop le!\n");
            break;
        }
    } while (lc != 0);

    return 0;
}
