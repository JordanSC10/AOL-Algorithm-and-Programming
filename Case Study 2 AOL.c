#include <stdio.h>
#include <string.h>

#define MAX_ROWS 3940

// Struktur data untuk menyimpan informasi properti
typedef struct {
    char location[55];
    char city[55];
    int price;
    int rooms;
    int bathroom;
    int carpark;
    char type[55];
    char furnish[55];
} Property;

// Fungsi untuk menampilkan menu pilihan yang tersedia
void menu() {
    printf("What do you want to do?\n");
    printf("1. Display data\n");
    printf("2. Search Data\n");
    printf("3. Sort Data\n");
    printf("4. Export Data\n");
    printf("5. Exit\n");
}

// Fungsi untuk membaca file CSV dan menyimpan data properti ke dalam array
int read_csv(const char *filename, Property properties[]) {
    FILE *file = fopen("file(in).csv", "r");
  
    int count = 0;
    char header[300];
    fscanf(file, "%[^\n]\n", header);  // Membaca header CSV (baris pertama)

    while (count < MAX_ROWS &&
           fscanf(file, "%49[^,],%49[^,],%d,%d,%d,%d,%49[^,],%49[^\n]\n",
                  properties[count].location,
                  properties[count].city,
                  &properties[count].price,
                  &properties[count].rooms,
                  &properties[count].bathroom,
                  &properties[count].carpark,
                  properties[count].type,
                  properties[count].furnish) == 8) {
        count++;
    }

    fclose(file);
    return count; // Mengembalikan jumlah data yang berhasil dibaca
}

// Fungsi untuk menampilkan data properti
void display_data(Property properties[], int total, int rows) {
	if (rows <= 0) { printf("Rows must be positive.\n"); return; }
    if (rows > total) rows = total;
    printf("Location             City             Price    Rooms Bathroom     Carpark      Type         Furnish\n");

    // Menampilkan data properti sesuai jumlah baris yang diminta
	for (int i = 0; i < rows; i++) {
    printf("%-20s %-16s %-8d %-5d %-12d %-12d %-12s %-12s\n",
           properties[i].location,
           properties[i].city,
           properties[i].price,
           properties[i].rooms,
           properties[i].bathroom,
           properties[i].carpark,
           properties[i].type,
           properties[i].furnish);
	}
}

// Fungsi untuk mencari data properti berdasarkan kolom tertentu
void search_data(Property properties[], int total) {
    char column[50];
    char query_str[50];
    int query_num, found = 0;

    printf("Choose column: ");
    scanf("%s", column);

    if (strcmp(column, "Location") == 0 || strcmp(column, "City") == 0 ||
        strcmp(column, "Type") == 0 || strcmp(column, "Furnish") == 0) {
        printf("What data do you want to find? ");
        scanf("%s", query_str);

        // Pencarian berdasarkan string
        for (int i = 0; i < total; i++) {
            if ((strcmp(column, "Location") == 0 && strcmp(properties[i].location, query_str) == 0) ||
                (strcmp(column, "City") == 0 && strcmp(properties[i].city, query_str) == 0) ||
                (strcmp(column, "Type") == 0 && strcmp(properties[i].type, query_str) == 0) ||
                (strcmp(column, "Furnish") == 0 && strcmp(properties[i].furnish, query_str) == 0)) {

                if (!found) {
                    printf("Data found. Detail of data:\n");
                    printf("%-20s %-16s %-8s %-5s %-9s %-8s %-12s %-12s\n",
                           "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");
                }
                
                printf("%-20s %-16s %-8d %-5d %-9d %-8d %-12s %-12s\n",
                       properties[i].location, properties[i].city,
                       properties[i].price, properties[i].rooms,
                       properties[i].bathroom, properties[i].carpark,
                       properties[i].type, properties[i].furnish);
                found = 1;
            }
        }
    }
    // Pencarian berdasarkan angka
    else if (strcmp(column, "Price") == 0 || strcmp(column, "Rooms") == 0 ||
             strcmp(column, "Bathroom") == 0 || strcmp(column, "Carpark") == 0) {
        scanf("%d", &query_num);

        for (int i = 0; i < total; i++) {
            if ((strcmp(column, "Price") == 0 && properties[i].price == query_num) ||
                (strcmp(column, "Rooms") == 0 && properties[i].rooms == query_num) ||
                (strcmp(column, "Bathroom") == 0 && properties[i].bathroom == query_num) ||
                (strcmp(column, "Carpark") == 0 && properties[i].carpark == query_num)) {

                if (!found) {
                    printf("Data found. Detail of data:\n");
                    printf("%-20s %-16s %-8s %-5s %-9s %-8s %-12s %-12s\n",
                           "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");
                }

                printf("%-20s %-16s %-8d %-5d %-9d %-8d %-12s %-12s\n",
                       properties[i].location, properties[i].city,
                       properties[i].price, properties[i].rooms,
                       properties[i].bathroom, properties[i].carpark,
                       properties[i].type, properties[i].furnish);
                found = 1;
            }
        }
    } else {
        printf("Invalid column name!\n");
        return;
    }
    if (!found) {
        printf("Data not found!\n");
    }
}

// Fungsi untuk mengurutkan data berdasarkan kolom tertentu
void sort_data(Property properties[], int total) {
    char column[20], order[10];

    // Memilih kolom untuk pengurutan
    while (1) {
        printf("Choose column: ");
        scanf("%s", column);

        if (strcmp(column, "Location") == 0 || strcmp(column, "City") == 0 ||
            strcmp(column, "Type") == 0 || strcmp(column, "Furnish") == 0 ||
            strcmp(column, "Price") == 0 || strcmp(column, "Rooms") == 0 ||
            strcmp(column, "Bathroom") == 0 || strcmp(column, "Carpark") == 0) {
            break;  // Valid, exit loop
        } else {
            printf("Invalid column name! Please try again.\n");
        }
    }

    // Memilih urutan pengurutan (ascending atau descending)
    while (1) {
        printf("Sort ascending or descending? ");
        scanf("%s", order);
        if (strcmp(order, "asc") == 0 || strcmp(order, "desc") == 0) {
            break;  // Valid, exit loop
        } else {
            printf("Invalid sort order! Please enter 'asc' or 'desc'.\n");
        }
    }

    // Bubble Sort 
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            int swap = 0;

            if (strcmp(column, "Price") == 0) {
                if ((strcmp(order, "asc") == 0 && properties[j].price > properties[j + 1].price) ||
                    (strcmp(order, "desc") == 0 && properties[j].price < properties[j + 1].price)) {
                    swap = 1;
                }
            } else if (strcmp(column, "Rooms") == 0) {
                if ((strcmp(order, "asc") == 0 && properties[j].rooms > properties[j + 1].rooms) ||
                    (strcmp(order, "desc") == 0 && properties[j].rooms < properties[j + 1].rooms)) {
                    swap = 1;
                }
            } else if (strcmp(column, "Location") == 0) {
                if ((strcmp(order, "asc") == 0 && strcmp(properties[j].location, properties[j + 1].location) > 0) ||
                    (strcmp(order, "desc") == 0 && strcmp(properties[j].location, properties[j + 1].location) < 0)) {
                    swap = 1;
                }
            } else if (strcmp(column, "City") == 0) {
                if ((strcmp(order, "asc") == 0 && strcmp(properties[j].city, properties[j + 1].city) > 0) ||
                    (strcmp(order, "desc") == 0 && strcmp(properties[j].city, properties[j + 1].city) < 0)) {
                    swap = 1;
                }
            } else if (strcmp(column, "Type") == 0) {
                if ((strcmp(order, "asc") == 0 && strcmp(properties[j].type, properties[j + 1].type) > 0) ||
                    (strcmp(order, "desc") == 0 && strcmp(properties[j].type, properties[j + 1].type) < 0)) {
                    swap = 1;
                }
            } else if (strcmp(column, "Furnish") == 0) {
                if ((strcmp(order, "asc") == 0 && strcmp(properties[j].furnish, properties[j + 1].furnish) > 0) ||
                    (strcmp(order, "desc") == 0 && strcmp(properties[j].furnish, properties[j + 1].furnish) < 0)) {
                    swap = 1;
                }
            } else if (strcmp(column, "Bathroom") == 0) {
                if ((strcmp(order, "asc") == 0 && properties[j].bathroom > properties[j + 1].bathroom) ||
                    (strcmp(order, "desc") == 0 && properties[j].bathroom < properties[j + 1].bathroom)) {
                    swap = 1;
                }
            } else if (strcmp(column, "Carpark") == 0) {
                if ((strcmp(order, "asc") == 0 && properties[j].carpark > properties[j + 1].carpark) ||
                    (strcmp(order, "desc") == 0 && properties[j].carpark < properties[j + 1].carpark)) {
                    swap = 1;
                }
            }

            if (swap) {
                Property temp = properties[j];
                properties[j] = properties[j + 1];
                properties[j + 1] = temp;
            }
        }
    }

    printf("Data found. Detail of data:\n");
    display_data(properties, total, 10); // Display 10 rows after sorting
}

    // Mengekspor data ke sebuah .csv file
void export_data(Property properties[], int total, const char *filename) {
    char full_filename[256];
    snprintf(full_filename, sizeof(full_filename), "%s.csv", filename);

    FILE *file = fopen(full_filename, "w");
    if (file == NULL) {
        printf("Error: Unable to create file %s\n", full_filename);
        return;
    }

    fprintf(file, "Location,City,Price,Rooms,Bathroom,Carpark,Type,Furnish\n");
    
    for (int i = 0; i < total; i++) {
        fprintf(file, "%s,%s,%d,%d,%d,%d,%s,%s\n",
                properties[i].location,
                properties[i].city,
                properties[i].price,
                properties[i].rooms,
                properties[i].bathroom,
                properties[i].carpark,
                properties[i].type,
                properties[i].furnish);
    }

    fclose(file);
    printf("Data successfully written to file %s!\n", full_filename);
}

// Fungsi utama untuk menjalankan aplikasi
int main() {
    Property properties[MAX_ROWS];
    int total_rows = read_csv("file(in).csv", properties);
    int choice;
    
    while (1) {
        menu();
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int rows;
                printf("Number of rows: ");
                scanf("%d", &rows);
                display_data(properties, total_rows, rows);
                break;
            }
            case 2:
                search_data(properties, total_rows);
                break;
            case 3:
                sort_data(properties, total_rows);
                break;
            case 4:
            	char filename[100];
    			printf("File name: ");
    			scanf("%s", filename);
    			export_data(properties, total_rows, filename);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
