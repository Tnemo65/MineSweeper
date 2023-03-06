//Bài dò mìn loang, ta sẽ sử dụng 2 mảng 2 chiều song song là bảng và bảng hiện ra
//Bảng sẽ là nơi chứa mìn -> giúp ta đếm mìn xung quanh và làm loang
//Loang thực chất là đệ quy hàm void
//Loang sẽ đếm số mìn xung quanh 1 tọa độ, sẽ gán cho bảng hiện ra và đệ quy
//Bảng hiện ra sẽ bị thay đổi trực tiếp và được in ra
#include<bits/stdc++.h>
using namespace std;

const int MAX_HANG = 100;
const int MAX_COT = 100;
const int MAX_MIN = 100;
const char MO = ' ';
const char CHUAMO = '.';
const char MIN = '*';
//Dùng để xét 8 vị trí xung quanh 1 tọa độ
const int DX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DY[] = {-1, 0, 1, -1, 1, -1, 0, 1};
//Khởi tạo tất cả đều là chưa mở
void taoBang(char bang[MAX_HANG][MAX_COT], int hang, int cot){
    for(int i = 0; i < hang; i++){
        for(int j = 0; j < cot; j++){
            bang[i][j] = CHUAMO;
        }
    }
}
//Random mìn nhớ hàm srand(time(NULL));
void taoMin(char bang[MAX_HANG][MAX_COT], int hang, int cot, int soMin){
    srand(time(NULL));
    int min = 0;
    while (min< soMin){
        int x = rand() % hang;
        int y = rand() % cot;
        if(bang[x][y] != MIN){
            bang[x][y] = MIN;
            min++;
        }
    }
}
//Bài này mình đã tối ưu hơn khi inBang sẽ in luôn các giá trị của bảng
void inBang(char bangHienRa[MAX_HANG][MAX_COT], int hang, int cot){
    cout << "   ";
    for(int i = 0; i < cot; i++){
        cout << i << " ";
    }
    cout << endl;
    for(int i = 0; i < hang; i++){
        cout << i << "  ";
        for(int j = 0; j < cot; j++){
            cout << bangHienRa[i][j] << " ";
        }
        cout << endl;
    }
}
//Đếm mìn xung quanh, nếu tọa độ được di chuyển đến thỏa mãn và nó chứa mìn thì đếm
int demMinXungQuanh(char bang[MAX_HANG][MAX_COT], int x, int y, int hang, int cot){
    int dem = 0;
    for(int i = 0; i < 8; i++){
        int xx = x + DX[i];
        int yy = y + DY[i];
        if(xx >= 0 && xx < hang && yy >= 0 && yy < cot && bang[xx][yy] == MIN){
            dem++;
        }
    }
    return dem;
}
//Đếm bom xung quanh 1 tọa độ và gán cho bangHienRa luôn
//Điều kiện dem>0 là chỉ mục đích ta liên tiếp gán giá trị 0 cho bangHienRa(không có mìn)
//Còn ví dụ như những ô gần số 0 mà Ở CẠNH MÌN, ta vẫn đếm mìn, vẫn gán cho bangHienRa nhưng hàm không được đệ quy tiếp tục
//Kết quả của hàm loang này là
//1. Đếm và gán số 0 cho những ô xung quanh tọa độ được chọn và đệ quy
//2. Các ô ở rìa cạnh các số 0 mà ở gần mìn vẫn được đếm mìn và gán vào bangHienRa
//vd  0 0 0 1 . 
//    0 0 2 . .
//    0 1 . . .
void loang(char bang[MAX_HANG][MAX_COT], char bangHienRa[MAX_HANG][MAX_COT], int x, int y, int hang, int cot ){
    if(bang[x][y] == MIN){
        return;
    }
    //Đoạn này là cách các con số 1, 2 được ra đời
    //Ô đó vẫn được đếm và gán vào bảng hiện ra nhưng k được đệ quy tiếp
    int dem = demMinXungQuanh(bang, x, y, hang, cot);
    //Dùng để gán giá trị là 1 số nhưng KIỂU CHAR (giống kiểu x1.00 ép kiểu double)
    bangHienRa[x][y] = dem + '0';
    if(dem > 0){
        return;
    }
    for(int i = 0; i < 8; i++){
        int xx = x + DX[i];
        int yy = y + DY[i];
        if(xx >= 0 && xx < hang && yy >= 0 && yy < cot && bangHienRa[xx][yy] == CHUAMO){
            //Đệ quy sẽ khiến bảng hiện ra tất cả các ô không chứa mìn xung quanh
            loang(bang, bangHienRa, xx, yy, hang, cot);
        }
    }
}

bool hopLe(int x, int y, int hang, int cot){
    if( x >=0 && x < hang && y >=0 && y < cot){
        return true;
    }
    return false;
}
//Thua khi ô ĐÃ MỞ và CHỨA MÌN
bool thua(char bang[MAX_HANG][MAX_COT], char bangHienRa[MAX_HANG][MAX_COT], int hang, int cot){
    for(int i = 0; i < hang; i++){
        for(int j = 0; j < cot; j++){
            if(bang[i][j] == MIN && bangHienRa[i][j] == MO){
                return true;
            }
        }
    }
    return false;
}

//Tháng khi số ô CHƯA MỞ = số MÌN
bool thang(char bang[MAX_HANG][MAX_COT], char bangHienRa[MAX_HANG][MAX_COT], int hang, int cot, int soMin){
    int demSoOChuaMo = 0;
    for(int i = 0; i < hang; i++){
        for(int j = 0; j < cot; j++){
            if(bangHienRa[i][j] == CHUAMO){
                demSoOChuaMo++;
            }
        }
    }
    if(demSoOChuaMo == soMin){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    int hang, cot, soMin;
    cout << "Rule: Enter 0 < m, n, k < 10" << endl;
    cout << "Enter the size of the minefield (m, n) and the number of mines (k): " << endl;
    cin >> hang >> cot >> soMin;
    char bang[MAX_HANG][MAX_COT];
    char bangHienRa[MAX_HANG][MAX_COT];
    taoBang(bang, hang, cot);
    taoBang(bangHienRa, hang, cot);
    taoMin(bang, hang, cot, soMin);
    inBang(bangHienRa, hang, cot);
    while(thua(bang, bangHienRa, hang, cot) == false){
        cout << "Please enter a place (x, y): ";
        int x, y;
        cin >> x >> y;
        if(hopLe(x, y, hang, cot) == false){
            cout << "The place is invalid, please retry!"<< endl;
            continue;
        }
        else{
            if(bangHienRa[x][y] != CHUAMO ){
            cout << "The place has been opened already, please retry!" << endl;
                continue;
            }
        }
        if(bang[x][y] == MIN){
            bangHienRa[x][y] = MIN;
            //Hiện ra mìn khi thua cho bảng hiện ra
            for(int i = 0; i < hang; i++){
                for(int j = 0; j < cot; j++){
                    if(bang[i][j] == MIN){
                        bangHienRa[i][j] = MIN;
                    }
                }
            }
            cout <<"YOU'RE DEAD!" << endl;
            inBang(bangHienRa, hang, cot);
            break;
        }
        else{
            loang(bang, bangHienRa, x, y, hang, cot);
            inBang(bangHienRa, hang, cot);
        }
        if(thang(bang, bangHienRa, hang, cot, soMin) == true){
            //Hiện ra mìn khi thắng cho bảng hiện ra
            for(int i = 0; i < hang; i++){
                for(int j = 0; j < cot; j++){
                    if(bangHienRa[i][j] == '.'){
                        bangHienRa[i][j] = '*';
                    }
                }
            }
            cout << "YOU'RE WIN!"<<endl;
            inBang(bangHienRa, hang, cot);
            break;
        }
    }
}